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

uniform float iGlobalTime;
uniform sampler2D iChannel0;
varying vec2 texpos;

void main() {
    //float mov = sin(texpos.x*40.0-iGlobalTime*2.0)*0.5+0.5;
    float alpha = texture2D(iChannel0, vec2(texpos.x, texpos.y/*(mov+1.0)-(mov*0.5)*/)).r;
    vec3 col = vec3(sin(texpos.x*20.0+iGlobalTime), sin(texpos.x*20.0+iGlobalTime*1.5), sin(texpos.x*20.0+iGlobalTime*0.5))*0.5+0.5;
    gl_FragColor = vec4(col, alpha);
}