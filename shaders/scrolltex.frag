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

#version 100

precision highp float;
/*precision highp vec2;
precision highp vec3;
precision highp vec4;*/

uniform vec2 iResolution;
uniform float iGlobalTime;
uniform sampler2D iChannel0;

void main() {
    /*highp*/ vec2 pos = gl_FragCoord.xy/iResolution.xy/4.0;
    gl_FragColor = vec4(texture2D(iChannel0, pos+iGlobalTime*0.2).rgb, 1.0);
}
