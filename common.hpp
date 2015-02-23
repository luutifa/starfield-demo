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

#ifndef COMMON_HPP
#define COMMON_HPP

#include "gfx_model_handler.hpp"
#include "rpi_gfx.hpp"

class CommonData {
    public:
        CommonData(unsigned int x, unsigned int y);

        float t;
        float res[2];
        float halfYRes[2];
        float beatHalfSine;
        
        GLfloat pProjMat40[16];
        
        GfxModelHandler* models;
};

#endif
