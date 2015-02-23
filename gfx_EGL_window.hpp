// Copyright 2015 Lauri Gustafsson
/*
This file is part of [DEMO NAME].

    [DEMO NAME] is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    [DEMO NAME] is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with [DEMO NAME], see COPYING. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GFX_EGL_WINDOW_HPP
#define GFX_EGL_WINDOW_HPP

#include "config.hpp"
#include "rpi_gfx.hpp"
#include <string>

class GfxEGLWindow
{
public:
    GfxEGLWindow(Config* ic);
    void swapBuffers();
    bool createWindow(GLuint flags);

protected:

    Config* c;
    EGLNativeWindowType window;
    EGLDisplay display;
    EGLContext context;
    EGLSurface buffer;
};

#endif
