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
uniform float startTime;
uniform float minusTime;
uniform sampler2D iChannel0;
varying vec2 texpos;

void main() {
    float t = iGlobalTime-startTime-minusTime;
    vec2 pos = vec2(clamp(pos.x, 0.0, t), pos.y);
    gl_FragColor = texture2D(iChannel0, pos);
}
