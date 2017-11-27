//
// Created by Eva on 24/11/2017.
// Dit bestand bevat alle functies, gebruikt om de contourpunten te bepalen en toe te voegen aan de vector<vector<Point>> contours
//

#include "Algorithms.h"
#include "avansvisionlib.h"

using namespace cv;
using namespace std;


vector<Point> chainCoordinate = {{ -1, 0 }, { -1, -1 }, { 0, -1 }, { 1, -1 }, { 1, 0 },{ 1, 1 }, { 0, 1 },{ -1, 1 }};
const int neighbourCount = 8;
vector<Point> Coordinate;
Point2d *firstPixel;

int allContours(Mat binaryImage, vector<vector<Point>> &contours)
{   int columns = binaryImage.cols;
    int Rows = binaryImage.rows;
    int imageSizeN = columns * Rows;
    Point westNeighbourCoordinate;

    if( imageSizeN != 0) {
        Mat labeledImage;
        vector<Point2d *> firstpixelVector;
        vector<Point2d *> positionVector;
        vector<int> areaVector;
        int blobNr = labelBLOBsInfo(binaryImage, labeledImage, firstpixelVector, positionVector, areaVector);
        cout << "--------------------------------" << endl;
        cout << "Aantal objecten in de afbeelding:\t" << blobNr << endl;
        cout << "--------------------------------" << endl;

        for (Point2d *p: firstpixelVector){
            //Switchen van x en y, aangezien columns en rows anders gedefinieerd zijn in de lib

            firstPixel = p;
            Point2d pixelCoordinate = Point(firstPixel -> y, firstPixel -> x);
            cout << "--------------------------" << endl;
            cout << "--------------------------" << endl;
            cout <<"Eerste punt is gevonden op:\t" << pixelCoordinate <<endl;
            cout << "--------------------------" << endl;
            Coordinate.push_back(pixelCoordinate);
            westNeighbourCoordinate = Point(pixelCoordinate.x - 1, pixelCoordinate.y) ;
            findNextBoundaryPoint(binaryImage, pixelCoordinate, westNeighbourCoordinate, Coordinate);
            contours.push_back(Coordinate);
            cout << "---------------------------------------" << endl;
            cout << "Het aantal contourpunten in dit object:\t" << Coordinate.size()<<endl;
            cout << "----------------------------------------" << endl;
            cout << "Bending Energy van dit object:" << bendingEnergy(binaryImage, Coordinate) << endl;
        }
        return contours.size();
    }
}

void findNextBoundaryPoint(Mat binaryImage, Point pixelCoordinate, Point westNeighbourCoordinate, vector<Point> &coordinateVector){

    int getFreemanDirection; //dir
    Point nextBoundaryPoint; //nextPoint
    int currentDirection = getDirection(pixelCoordinate,westNeighbourCoordinate); //currentDir
    bool freemanBoundaryTracking = true; //looping

    while(freemanBoundaryTracking){
        getFreemanDirection = getDirectionNextBoundaryPoint(binaryImage, pixelCoordinate,currentDirection); //getDirectionClosest
        nextBoundaryPoint = getNextBoundaryPoint(pixelCoordinate,getFreemanDirection);

        if((!containsBoundaryPoint(coordinateVector,nextBoundaryPoint)) && (getFreemanDirection!=-1)) {
            if (getFreemanDirection > 0)
                currentDirection = getFreemanDirection - 1;
            else if (getFreemanDirection == 0)
                currentDirection = 7;

            freemanBoundaryTracking = false;
        }

        else{
            if(currentDirection <7)
                currentDirection++;
            else currentDirection = 0;
        }

        if (nextBoundaryPoint.x == firstPixel->y&&nextBoundaryPoint.y == firstPixel->x){
            return;
        }

    }

    if (!containsBoundaryPoint(coordinateVector,nextBoundaryPoint)) {
        //Calculate the coords of the last 0 preceding nextPoint
        Point newWestNeighbour = getNextBoundaryPoint(pixelCoordinate, currentDirection);
        cout << "--------------------------" << endl;
        cout << "Westneighbour " << newWestNeighbour << endl;
        cout << "Current Boundary Point " << nextBoundaryPoint << endl;
        cout << "--------------------------" << endl;
        coordinateVector.push_back(nextBoundaryPoint);
        //contours.at<uchar>(Point(nextPoint.y, nextPoint.x)) = 255;
        findNextBoundaryPoint(binaryImage, nextBoundaryPoint, newWestNeighbour, coordinateVector);


    }
    return;
}

bool containsBoundaryPoint(vector<Point> vectorPoints, Point nextBCoordinate){
    for(Point backtrackPixel : vectorPoints){
        if(backtrackPixel == nextBCoordinate){
            return true;
        }
        return false;
    }
}


int getDirection(Point coordinateB, Point coordinateC){

    if(coordinateC == (coordinateB + chainCoordinate[0])) return 0;
    else if(coordinateC == (coordinateB + chainCoordinate[1]))return 1;
    else if(coordinateC == (coordinateB + chainCoordinate[2]))return 2;
    else if(coordinateC == (coordinateB + chainCoordinate[3]))return 3;
    else if(coordinateC == (coordinateB + chainCoordinate[4]))return 4;
    else if(coordinateC == (coordinateB + chainCoordinate[5]))return 5;
    else if(coordinateC == (coordinateB + chainCoordinate[6]))return 6;
    else if(coordinateC == (coordinateB + chainCoordinate[7]))return 7;

    return -1;
}


Point getNextBoundaryPoint(Point followingPoint, int direction){
    Point getNextPoint(0,0);
    switch(direction){
        case 0: getNextPoint = followingPoint +chainCoordinate[0]; break;
        case 1: getNextPoint = followingPoint +chainCoordinate[1]; break;
        case 2: getNextPoint = followingPoint +chainCoordinate[2]; break;
        case 3: getNextPoint = followingPoint +chainCoordinate[3]; break;
        case 4: getNextPoint = followingPoint +chainCoordinate[4]; break;
        case 5: getNextPoint = followingPoint +chainCoordinate[5]; break;
        case 6: getNextPoint = followingPoint +chainCoordinate[6]; break;
        case 7: getNextPoint = followingPoint +chainCoordinate[7]; break;
    }
    return getNextPoint;
}

int getDirectionNextBoundaryPoint(Mat binaryImage, Point pixelCoordinateStart, int startDirection){
    for (int i = startDirection; i < neighbourCount; i++)
    {
        Point getNextPoint = getNextBoundaryPoint(pixelCoordinateStart,i);
        int valueImage = getEntryImage(binaryImage, getNextPoint.y, getNextPoint.x);
        if (valueImage ==1)
        {

            return i;
        }
    }
    return -1;
}

double bendingEnergy(Mat binaryImage, vector<Point>& Coordinate) {
    float lengthBetweenX;
    float lengthBetweenY;
    float angleBetween;
    float arrow;
    vector<int> chainCode;
    double curvature;
    double bendingEnergySum;

    for (int i = 0; i < Coordinate.size(); i++) {
        bendingEnergySum = 0;
        lengthBetweenX = (Coordinate[i + 1].x - Coordinate[i].x);
        lengthBetweenY = (Coordinate[i + 1].y - Coordinate[i].y);
        angleBetween = atan2(Coordinate[i].y - Coordinate[i + 1].y, Coordinate[i].x - Coordinate[i + 1].x);
        arrow = sqrt(pow(lengthBetweenX, 2) + pow(lengthBetweenY, 2));
        curvature = angleBetween / arrow;
        bendingEnergySum += pow((curvature), 2);
        return bendingEnergySum;
    }
}
