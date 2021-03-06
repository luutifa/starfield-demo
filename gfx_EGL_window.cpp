// Copyright 2015 Lauri Gustafsson
/*
This file is part of Low Quality is the Future.

    Low Quality is the Future is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Low Quality is the Future is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Low Quality is the Future, see COPYING. If not, see <http://www.gnu.org/licenses/>.
*/

#include "gfx_EGL_window.hpp"

GfxEGLWindow::GfxEGLWindow(Config* ic, std::string _name):
c(ic),
name(_name)
{
    #ifdef USE_X
        memset(&dummyEvent, 0, sizeof(XClientMessageEvent));
        dummyEvent.type = ClientMessage;
        dummyEvent.format = 32;
    #endif
}

#ifndef USE_X

bool GfxEGLWindow::shouldKill() {
    return false;
}

void GfxEGLWindow::swapBuffers()
{
    eglSwapBuffers(display, buffer);
}

bool GfxEGLWindow::createWindow(GLuint flags)
{
    EGLint attribList[] =
    {
        EGL_RED_SIZE,       5,
        EGL_GREEN_SIZE,     6,
        EGL_BLUE_SIZE,      5,
        EGL_ALPHA_SIZE,     (flags & GFX_WINDOW_ALPHA) ? 8 : 0,
        EGL_DEPTH_SIZE,     (flags & GFX_WINDOW_DEPTH) ? 8 : EGL_DONT_CARE,
        EGL_STENCIL_SIZE,   (flags & GFX_WINDOW_STENCIL) ? 8 : EGL_DONT_CARE,
        EGL_SAMPLE_BUFFERS, (flags & GFX_WINDOW_MULTISAMPLE) ? 1 : 0,
        EGL_NONE
    };

    /*
    Confusing :)
    I pretty much stole all of this EGL code somewhere :D
    */
    static EGL_DISPMANX_WINDOW_T nativewindow;

    DISPMANX_ELEMENT_HANDLE_T dispman_element;
    DISPMANX_DISPLAY_HANDLE_T dispman_display;
    DISPMANX_UPDATE_HANDLE_T dispman_update;
    VC_RECT_T dst_rect;
    VC_RECT_T src_rect;

    uint32_t w;
    uint32_t h;
    uint32_t x;
    uint32_t y;

    w = c->w;
    h = c->h;
    x = c->x;
    y = c->y;

    dst_rect.x = x;
    dst_rect.y = y;
    dst_rect.width = w * c->stretch;
    dst_rect.height = h * c->stretch;

    src_rect.x = x;
    src_rect.y = y;
    src_rect.width = (w) << 16;
    src_rect.height = (h) << 16;

    dispman_display = vc_dispmanx_display_open( 0 /* LCD */);
    dispman_update = vc_dispmanx_update_start( 0 );

    VC_DISPMANX_ALPHA_T alpha = {
        DISPMANX_FLAGS_ALPHA_FIXED_ALL_PIXELS,255,0 // Fixes some alpha blending issues, now the screen stays opaque all the time.
    };

    dispman_element = vc_dispmanx_element_add ( dispman_update, dispman_display,
    0/*layer*/, &dst_rect, 0/*src*/,
    &src_rect, DISPMANX_PROTECTION_NONE, &alpha, 0/*clamp*/, (DISPMANX_TRANSFORM_T)0/*transform*/);

    nativewindow.element = dispman_element;
    nativewindow.width = w;
    nativewindow.height = h;
    vc_dispmanx_update_submit_sync( dispman_update );

    window = &nativewindow;

    EGLint numConfigs;
    EGLint majorVersion;
    EGLint minorVersion;
    EGLDisplay eglDisplay;
    EGLContext eglContext;
    EGLSurface eglBuffer;
    EGLConfig config;

    EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };

    eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if ( eglDisplay == EGL_NO_DISPLAY )
        return false;

    // Initialize EGL
    if ( !eglInitialize(eglDisplay, &majorVersion, &minorVersion) )
        return false;

    if ( !eglGetConfigs(eglDisplay, NULL, 0, &numConfigs) )
        return false;

    if ( !eglChooseConfig(eglDisplay, attribList, &config, 1, &numConfigs) )
        return false;

    eglBuffer = eglCreateWindowSurface(eglDisplay, config, (EGLNativeWindowType)window, NULL);
    if ( eglBuffer == EGL_NO_SURFACE )
        return false;

    eglContext = eglCreateContext(eglDisplay, config, EGL_NO_CONTEXT, contextAttribs );
    if ( eglContext == EGL_NO_CONTEXT )
        return false;

    if ( !eglMakeCurrent(eglDisplay, eglBuffer, eglBuffer, eglContext) )
        return false;

    display = eglDisplay;
    buffer = eglBuffer;
    context = eglContext;

    //eglSwapInterval(eglDisplay, 0.0);

    return true;
}

#else

bool GfxEGLWindow::shouldKill() {
    /*XSendEvent(xdisplay, xwindow, 0, 0, (XEvent*)&dummyEvent);
    XNextEvent(xdisplay, &event);
    if (event.type == KeyPress) {
        XCloseDisplay(xdisplay);
        return true;
    }*/ //This "approach" sucks, huge perf hit.
    return false;
}

void GfxEGLWindow::swapBuffers()
{
    eglSwapBuffers(display, surface);
}

// X11 related local variables
static Display *x_display = NULL;

bool GfxEGLWindow::createWindow(GLuint flags)
{
    EGLint attribList[] =
    {
        EGL_RED_SIZE,       5,
        EGL_GREEN_SIZE,     6,
        EGL_BLUE_SIZE,      5,
        EGL_ALPHA_SIZE,     (flags & GFX_WINDOW_ALPHA) ? 8 : EGL_DONT_CARE,
        EGL_DEPTH_SIZE,     (flags & GFX_WINDOW_DEPTH) ? 8 : EGL_DONT_CARE,
        EGL_STENCIL_SIZE,   (flags & GFX_WINDOW_STENCIL) ? 8 : EGL_DONT_CARE,
        EGL_SAMPLE_BUFFERS, (flags & GFX_WINDOW_MULTISAMPLE) ? 1 : 0,
        EGL_NONE
    };

    /*
    Confusing :)
    I pretty much stole all of this EGL code somewhere :D
    */
    
    Window root;
    XSetWindowAttributes swa;
    XSetWindowAttributes  xattr;
    Atom wm_state;
    XWMHints hints;
    XEvent xev;
    EGLConfig ecfg;
    EGLint num_config;
    Window win;

    /*
     * X11 native display initialization
     */

    x_display = XOpenDisplay(NULL);
    if ( x_display == NULL ) {
        return false;
    }

    root = DefaultRootWindow(x_display);

    swa.event_mask  =  ExposureMask | PointerMotionMask | KeyPressMask;
    win = XCreateWindow(
               x_display, root,
               0, 0, c->w, c->h, 0,
               CopyFromParent, InputOutput,
               CopyFromParent, CWEventMask,
               &swa );

    xattr.override_redirect = FALSE;
    XChangeWindowAttributes ( x_display, win, CWOverrideRedirect, &xattr );

    hints.input = TRUE;
    hints.flags = InputHint;
    XSetWMHints(x_display, win, &hints);

    // make the window visible on the screen
    XMapWindow (x_display, win);
    XStoreName (x_display, win, name.c_str()); //WIN NAME

    Atom WM_DELETE_WINDOW = XInternAtom(x_display, "WM_DELETE_WINDOW", False); 
    XSetWMProtocols(x_display, win, &WM_DELETE_WINDOW, 1);
    // get identifiers for the provided atom name strings
    wm_state = XInternAtom (x_display, "_NET_WM_STATE", FALSE);

    memset ( &xev, 0, sizeof(xev) );
    xev.type                 = ClientMessage;
    xev.xclient.window       = win;
    xev.xclient.message_type = wm_state;
    xev.xclient.format       = 32;
    xev.xclient.data.l[0]    = 1;
    xev.xclient.data.l[1]    = FALSE;
    XSendEvent (
       x_display,
       DefaultRootWindow ( x_display ),
       FALSE,
       SubstructureNotifyMask,
       &xev );
    
    //hWnd = (EGLNativeWindowType) win;
    xwindow = win;
    dummyEvent.window = xwindow;
    xdisplay = x_display;
    
   EGLint numConfigs;
   EGLint majorVersion;
   EGLint minorVersion;
   //EGLDisplay display;
   //EGLContext context;
   //EGLSurface surface;
   EGLConfig config;
   EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };

   // Get Display
   display = eglGetDisplay((EGLNativeDisplayType)x_display);
   if ( display == EGL_NO_DISPLAY ) {
      return false;
   }

   // Initialize EGL
   if ( !eglInitialize(display, &majorVersion, &minorVersion) ) {
      return false;
   }

   // Get configs
   if ( !eglGetConfigs(display, NULL, 0, &numConfigs) ) {
      return false;
   }

   // Choose config
   if ( !eglChooseConfig(display, attribList, &config, 1, &numConfigs) ) {
      return false;
   }

   // Create a surface
   surface = eglCreateWindowSurface(display, config, (EGLNativeWindowType)win, NULL);
   if ( surface == EGL_NO_SURFACE ) {
      return false;
   }

   // Create a GL context
   context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs );
   if ( context == EGL_NO_CONTEXT ) {
      return false;
   }   
   
   // Make the context current
   if ( !eglMakeCurrent(display, surface, surface, context) ) {
      return false;
   }
   
   /*eglDisplay = display;
   *eglSurface = surface;
   *eglContext = context;*/
   return true;
}
#endif
