//
// Created by Eva on 20/11/2017.
//  Dit programma zoekt contouren in een afbeelding en geeft deze terug.
//

#include "includes.h"
#include "avansvisionlib.h"
#include "Algorithms.h"

using namespace cv;
using namespace std;

int main(int argc, char *argv[]){
    //Beeldbewerking
    Mat imageOriginal;
    imageOriginal = imread("//Users//Eva//Workspace_programs//CLionProjects//Visiongev//basisfiguren.jpg", CV_LOAD_IMAGE_COLOR);

    Mat gray_image;
    cvtColor(imageOriginal, gray_image, CV_BGR2GRAY);
    imshow("Original", gray_image);
    waitKey(0);

    Mat binaryImage;
    threshold(gray_image, binaryImage, 200, 1, CV_THRESH_BINARY_INV);

    Mat binary16S;
    binaryImage.convertTo(binary16S, CV_16S);

    //Bepaal Contouren
    vector< vector<Point> > *contours = new vector<vector<Point>>();
    allContours(binary16S, *contours);

    Mat contourImage = binaryImage.clone();
    contourImage = 0;
    for (vector<Point> vectorContourImage : *contours)
    {
        for (Point i : vectorContourImage)
            contourImage.at<uchar>(Point(i.x,i.y)) = 255;
    }

    //Geef contouren weer
    namedWindow("Contours Image",WINDOW_AUTOSIZE);
    imshow("Contours Image", contourImage);
    waitKey(0);

    return 0;

}
