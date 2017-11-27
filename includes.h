//
// Created by Eva on 25/09/2017.
//

#ifndef VISIONC_INCLUDES_H
#define VISIONC_INCLUDES_H

#include <math.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <stdint.h>
#include <stdio.h>
#include <cmath>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/calib3d.hpp"

#ifdef __APPLE__
typedef int16_t _int16; // want avans gebruikt types die niet in stdint.h zijn gedefined..
#endif

#endif //VISIONC_INCLUDES_H
