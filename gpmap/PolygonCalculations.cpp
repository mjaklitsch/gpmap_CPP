#include "PolygonCalculations.hpp"
#include "SensorArray.hpp"
#include <cmath>
#include <iostream>

int polygonRadius = 300;

float polygonalTriangleInnerTheta = (2*M_PI) / numberOfSensors;
float polygonalTriangleOuterTheta = (M_PI - polygonalTriangleInnerTheta) / 2; //see below
//   center (Inner Angle)
//     /\
//    /  \
//   /    \
//  /______\
//  ^ these ^ angles (Outer Angles)

float radians(float degrees){
    return degrees * M_PI / 180;
}

float degrees(float radians){
    return radians * 180 / M_PI;
}

float polarXAngle(float angle) { // takes theta(polar coordinate) and returns the corresponding cartesian X coordinate for the global polygon size
    return cos(radians(angle))*polygonRadius;
}

float polarYAngle(float angle) { // takes theta(polar coordinate) and returns the corresponding cartesian Y coordinate for the global polygon size
    return sin(radians(angle))*polygonRadius;
}

float polarXTheta(float theta) { // takes theta(polar coordinate) and returns the corresponding cartesian X coordinate for the global polygon size
    return cos(theta)*polygonRadius;
}

float polarYTheta(float theta) { // takes theta(polar coordinate) and returns the corresponding cartesian Y coordinate for the global polygon size
    return sin(theta)*polygonRadius;
}

float distanceBetween(float xPos1, float yPos1, float xPos2, float yPos2) {
    float distance = sqrt(pow(xPos2 - xPos1, 2) + pow(yPos2 - yPos1, 2));
    return distance;
}

float getPolygonDistanceFromOriginAtTheta(float theta) {
    
    float scaledTheta = fmod(theta, polygonalTriangleInnerTheta); // reduce problem to single triangle
    float edgeTheta = M_PI - (scaledTheta + polygonalTriangleOuterTheta); // get angle produced by cell's angle of incident on polygon's outer edge
    float polygonDistanceFromOrigin = (polygonRadius * sin(polygonalTriangleOuterTheta)) / (sin(edgeTheta)); // law of sines to get length from center to edge of polygon at that angle
    return polygonDistanceFromOrigin;
}

int getIndexOfClosestSensorDotToTheta(float theta) {
    int inverseIndex = round(theta / polygonalTriangleInnerTheta);// the sensors are indexed incrementally clockwise whereas...
    if (inverseIndex == 0) { // ...angles increase counterclockwise (in an attempt to mimick the unit circle)...
        return 0;
    } else {
        return numberOfSensors - inverseIndex; // ...which makes this inverse measurement necessary
    }
}

float getxCoordinateOfPolygonAtTheta(float theta) {
    float xCoordOfPolygon = getPolygonDistanceFromOriginAtTheta(theta) * cos(theta);
    return xCoordOfPolygon;
}

float getyCoordinateOfPolygonAtTheta(float theta) {
    float yCoordOfPolygon = -getPolygonDistanceFromOriginAtTheta(theta) * sin(theta);
    return yCoordOfPolygon;
}

bool isCellOverlappingWithPolygon(int cellIndex, CellArray* cellArray) {
    float theta = cellArray->getTheta(cellIndex);
    float xCoordOfPolygonAtTheta = getxCoordinateOfPolygonAtTheta(theta);
    float yCoordOfPolygonAtTheta = getyCoordinateOfPolygonAtTheta(theta);
    float thetaOfCircleTangentWithPolygon = abs(fmod(theta, polygonalTriangleInnerTheta)-(polygonalTriangleInnerTheta / 2));
    
    float cosThetaOfTangent = cos(thetaOfCircleTangentWithPolygon);
    
    float distanceFromTargetPointOfPolygonToCenterOfCell = distanceBetween(cellArray->getXPos(cellIndex), cellArray->getYPos(cellIndex), xCoordOfPolygonAtTheta, yCoordOfPolygonAtTheta);
    float distanceFromClosestPointOfPolygonToCenterOfCell = distanceFromTargetPointOfPolygonToCenterOfCell * cosThetaOfTangent;
    
    if (distanceFromClosestPointOfPolygonToCenterOfCell <= cellArray->getRadius(cellIndex)) {
        return true;
    } else {
        return false;
    }
}

float *getMidpoint(float x1, float y1, float x2, float y2) {
    float *midpoint = new float[2];
    
    float x3 = (x1 + x2) / 2;
    float y3 = (y1 + y2) / 2;
    
    midpoint[0] = x3;
    midpoint[1] = y3;
    
    return midpoint;
}
