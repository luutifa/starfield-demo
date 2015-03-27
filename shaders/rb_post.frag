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

precision highp float;

uniform float iGlobalTime;
uniform vec2 iResolution;
uniform sampler2D iChannel0;

void main() {
    vec2 pos = (gl_FragCoord.xy/iResolution.xy)/2.0;
    gl_FragColor = vec4(texture2D(iChannel0, pos+vec2(0.006, 0.0)).r, texture2D(iChannel0, pos).g, texture2D(iChannel0, pos-vec2(0.006, 0.0)).b, 1.0);
}
