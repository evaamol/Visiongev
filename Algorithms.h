//
// Created by Eva on 24/11/2017.
//

#ifndef VISIONGEV_ALGORITHMS_H
#define VISIONGEV_ALGORITHMS_H

#endif //VISIONGEV_ALGORITHMS_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <iostream>
#include <string>
#include "includes.h"

using namespace cv;
using namespace std;

//Gedeclareerde functies
int allContours(Mat binaryImage, vector< vector<Point> > & contourVecVec);
void findNextBoundaryPoint(Mat img, Point b, Point c, vector<Point> &vec);
int getDirection(Point pixelCoordinate, Point westNeighbourCoordinate);
Point getNextBoundaryPoint(Point followingPoint, int direction);
int getDirectionNextBoundaryPoint(Mat binaryImage, Point pixelCoordinateStart, int startDirection = 0);
bool containsBoundaryPoint(vector<Point> vectorPoints, Point nextBCoordinate);
double bendingEnergy(Mat binaryImage, vector<Point>& Coordinate);
