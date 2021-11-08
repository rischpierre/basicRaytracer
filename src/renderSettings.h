/*
 *
 * Copyright (c) 2021 Pierre Risch
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * This file is part of basicRaytracer.
 *
 * Author:          Pierre Risch <rischpierre@gmail.com>
 *
 */

#ifndef RAYTRACEREXPERIMENT_RENDERSETTINGS_H
#define RAYTRACEREXPERIMENT_RENDERSETTINGS_H

#define BG_COLOR_R .1f
#define BG_COLOR_G .1f
#define BG_COLOR_B .2f

#define MAIN_RESOLUTION_W 1280
#define MAIN_RESOLUTION_H 720
#define RESOLUTION_DIVIDER 2 // should be a multiple of 2 or 1

#define RESOLUTION_W (MAIN_RESOLUTION_W / RESOLUTION_DIVIDER)
#define RESOLUTION_H (MAIN_RESOLUTION_H / RESOLUTION_DIVIDER)

#define CAM_FILM_SIZE_W 3.6f   // 24 36 film back size
#define CAM_FILM_SIZE_H 2.25f  // !6:9 ratio
#define CAM_FOCAL_LENGTH 4  // in mmm
#define WORLD_MAX_DISTANCE 9999999.f
#define RAY_TRACING_THRESHOLD 0.000001

#endif //RAYTRACEREXPERIMENT_RENDERSETTINGS_H
