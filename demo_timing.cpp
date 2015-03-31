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

#include "demo_timing.hpp"
#include <cstdlib>

float const PART_TIMES[] = {
    30.9f, //Intro
    0.5f,  //Intro fade
    30.9f, //Starfield
    0.5f,  //
    0.5f,
    14.7f, //Flag
    5.0f, //pointcube
    5.0f, //pointicos
    5.0f, //pointhtorus
    0.4f,
    0.4f,
    15.3f,
    //4000000.7f,
    30.0f,
    30.0f,
    30.0f,
    30.0f,
    30.0f
};
int const PARTS = sizeof(PART_TIMES)/sizeof(PART_TIMES[0]);
