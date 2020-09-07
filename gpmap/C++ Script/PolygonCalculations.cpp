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

float getyCoordinateOfPolygonAtTheta(float theta) { // all y values are negated due to originally working in Processing3 where the
    // y coordinate plane is inverse.
    float yCoordOfPolygon = -getPolygonDistanceFromOriginAtTheta(theta) * sin(theta);
    return yCoordOfPolygon;
}

bool isCellOverlappingWithPolygon(int cellIndex, CellArray* cellArray) {
    // First I need to find the x and y positions of the point on the polygon that the Cell is heading towards
    
    float theta = cellArray->getTheta(cellIndex);
    float xCoordOfPolygonAtTheta = getxCoordinateOfPolygonAtTheta(theta);
    float yCoordOfPolygonAtTheta = getyCoordinateOfPolygonAtTheta(theta);
    
    // Note: This is not necessarily the point the Cell will intersect the Polygon, The point the circle will
    // intersect will be the point on the edge of the polygon that lies at a right angle to the center of the Cell
    // when the Cell's radius is also its center's distance from the edge. I'll do my best to explain the math.
    
    // Next I do 2 things, first, since a polygon is just "poly" triangles combined(octogon has 8, hexagon has 6, etc.)
    // I simplify the problem down to the scope of 1 triangle by modding the theta with the inner theta of the polygon.
    // Next, to get the angle at which the Cell is approaching the edge, I subtract half the inner theta from
    // the single triangle theta value and take the absolute value.
    
    float thetaOfCellTangentWithPolygon = abs(fmod(theta, polygonalTriangleInnerTheta)-(polygonalTriangleInnerTheta / 2));
    
    // Now we're working with a right triangle with points a,b,c, with the right angle on the edge of the polygon,
    // point a at the center oc the Cell, b at the edge forming our right angle, and c being the target of the Cell's direction or
    // the point on the polygon the center of the Cell will intersect if it were to continue that far.
    
    // Now we just need to do some simple trig to get the length of line(a,b)
    // Adjacent = cos(theta) * hypotenuse
    
    // This gets out cos(theta)
    
    float cosThetaOfTangent = cos(thetaOfCellTangentWithPolygon);
    
    // This next variable gets the hypotenuse of our triangle(a,b,c), also known as line(a,c)
    
    float distanceFromTargetPointOfPolygonToCenterOfCell = distanceBetween(cellArray->getXPos(cellIndex), cellArray->getYPos(cellIndex), xCoordOfPolygonAtTheta, yCoordOfPolygonAtTheta);
    
    // This gets our Adjacent length of line(a,b)
    
    float distanceFromClosestPointOfPolygonToCenterOfCell = distanceFromTargetPointOfPolygonToCenterOfCell * cosThetaOfTangent;
    
    // Now we just check if line(a,b) is less than or equal to the radius which would be an overlap
    
    if (distanceFromClosestPointOfPolygonToCenterOfCell <= cellArray->getRadius(cellIndex)) {
        return true;
    } else {
        return false;
    }
}

