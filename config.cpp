// Copyright 2014 Lauri Gustafsson
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

#include "config.hpp"
#include "util.hpp"
#include "text.hpp"
#include <cstdlib>
#include <iostream>
#include <cstring>

Config::Config(int argc, char* argv[]):
w(0),
h(0),
x(0),
y(0),
stretch(1),
fpsCounter(false),
fpsIn(100)
{
    /*YAY crappy parameter checking ^__^*/
    for (int n=1; n<argc; n++)
    {
        if (!strcmp(argv[n], "-w"))
        {
            n++;
            checkValueParam(n, argc, argv);
            w = atoi(argv[n]);
        }
            else if (!strcmp(argv[n], "-h"))
            {
                n++;
                checkValueParam(n, argc, argv);
                h = atoi(argv[n]);
            }
               else if (!strcmp(argv[n], "-x"))
               {
                   n++;
                   checkValueParam(n, argc, argv);
                   x = atoi(argv[n]);
               }
                 else if (!strcmp(argv[n], "-y"))
                 {
                     n++;
                     checkValueParam(n, argc, argv);
                     y = atoi(argv[n]);
                 }
                     else if (!strcmp(argv[n], "-s"))
                     {
                         n++;
                         checkValueParam(n, argc, argv);
                         w = h = atoi(argv[n]);
                     }
                         else if (!strcmp(argv[n], "--help"))
                         {
                             std::cout << PIPE_CAT;
                             sleep(4);
                             std::cout << DOC;
                             exit(0);
                         }
                             else if (!strcmp(argv[n], "--version"))
                             {
                                 std::cout << PIPE_CAT;
                                 sleep(4);
                                 std::cout << VERSION;
                                 exit(0);
                             }
                                 else if (!strcmp(argv[n], "-f"))
                                 {
                                     std::cout << PIPE_CAT;
                                     sleep(4);
                                     fpsCounter = true;
                                     if ((n+1)!=argc)
                                     {
                                         std::string tmp = argv[n+1];
                                         if (isdigits(tmp))
                                         {
                                             n++;
                                             fpsIn = atoi(argv[n]);
                                         }
                                     }
                                 }
                                     else if (!strcmp(argv[n], "-c"))
                                     {
                                         n++;
                                         checkValueParamf(n, argc, argv);
                                         stretch = atof(argv[n]);
                                         if (stretch < 1)
                                         {
                                             std::cout << ARGERR;
                                             sleep(4);
                                             exit(4);
                                         }
                                     }
                                         else
                                         {
                                             std::cout << ARGERR;
                                             sleep(4);
                                             exit(5);
                                         }
    }
    
    int errDisp;
    uint32_t actualW, actualH;
    if ((w == 0 || h == 0) && (errDisp = graphics_get_display_size(0, &actualW, &actualH)) < 0) {
        std::cout << "Failed to get display size.\n";
        sleep(4);
        exit(errDisp);
    }
    
    if (w == 0)
        w = actualW;
        
    if (h == 0)
        h = actualH;
        
    h /= stretch;
    w /= stretch;
}
