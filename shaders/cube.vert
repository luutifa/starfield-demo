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

attribute vec3 a_vertex;
uniform mat4 projection;
uniform float iGlobalTime;
uniform mat4 xRotation;
uniform mat4 yRotation;
uniform mat4 zRotation;

void main() {
    vec4 vm = vec4(a_vertex, 1.0) * xRotation;
    vm *= yRotation;
    vm *= zRotation;
    vm = vec4(vm.xy, vm.z-(sin(iGlobalTime)+4.0), vm.w);
    //vm.x += sin(iGlobalTime)*2.0;
    //vm.y += cos(iGlobalTime)*2.0;
    gl_Position = vm * projection;
    //gl_Position = vec4(vertex, 1.0);
}
