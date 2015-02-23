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

#ifndef GFX_SCREEN_MOVABLE_HPP
#define GFX_SCREEN_MOVABLE_HPP

#include "rpi_gfx.hpp"
#include "gfx_shader.hpp"
#include "gfx_texture_2D.hpp"
#include "common.hpp"
#include <string>

class GfxScreenMovable {
    public:
        GfxScreenMovable(CommonData* icommon, std::string fs, unsigned int x, unsigned int y, unsigned int w, unsigned int h, std::string i0="", float c=1.0);
        ~GfxScreenMovable();
        void draw();
        void setWH(unsigned int w, unsigned int h);
        void setW(unsigned int w);
        void setH(unsigned int h);
        void setXY(unsigned int x, unsigned int y);
        void setX(unsigned int x);
        void setY(unsigned int y);
        void setXYWH(unsigned int x, unsigned int y, unsigned int w, unsigned int h);
    private:
        GfxTexture2D* i;
        unsigned short iCount;
        GfxShader shaderProgram;
        CommonData* common;
        GLfloat vertices[16];

        float store_x;
        float store_y;
        float store_w;
        float store_h;
};

#endif
