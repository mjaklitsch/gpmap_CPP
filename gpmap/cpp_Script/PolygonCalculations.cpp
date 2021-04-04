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
    
    // Dont bother with more math if we know this isn't possible yet
    
    const float closestPolygonDistanceFromOrigin = polygonRadius/cos((polygonalTriangleInnerTheta/2));
    
    float xPos = cellArray->getXPos(cellIndex);
    float yPos = cellArray->getYPos(cellIndex);
    float radius = cellArray->getRadius(cellIndex);
    
    if ((distanceBetween(xPos, yPos, 0, 0) + radius) < closestPolygonDistanceFromOrigin){
        return false;
    }
    
    
    // First I need to find the x and y positions of the point on the polygon that the Cell is heading towards
    
    float theta = cellArray->getTheta(cellIndex);
    float xCoordOfPolygonAtTheta = getxCoordinateOfPolygonAtTheta(theta);
    float yCoordOfPolygonAtTheta = getyCoordinateOfPolygonAtTheta(theta);
    
    // Note: This is not necessarily the point the Cell will intersect the Polygon, The point that the Cell's circle will
    // intersect == the point on the edge of the polygon that lies at a right angle to the center of the Cell
    // when that Cell's radius == its center's distance from the edge. I'll do my best to explain the math.
    
    // Next I do 2 things, first, since a polygon is just "poly" number of triangles combined(octogon has 8, hexagon has 6, etc., like a sliced pizza)
    // I simplify the problem down to the scope of 1 triangle by modding the theta(the angle the cell travels) with the inner theta of the polygon(
    // the angle of the tip of each "pizza" slice)
    
    // Next, to get the angle at which the Cell is approaching the edge, I subtract half the inner
    // theta from the single triangle theta value and take the absolute value.
    
    // \|/
    //  a  Now I have the angle of offset from this central line "a"
    
    // Effectively, the problem space has been split in half again because of the following relation
    // angleFromEdgeAboveCenterLine(angle) == angleFromEdgeBelowCenterLine(angle)
    
    float thetaOfCellTangentWithPolygon = abs(fmod(theta, polygonalTriangleInnerTheta)-(polygonalTriangleInnerTheta / 2));
    
    // Now we're working with a right triangle with points a,b,c, with the right angle on the edge of the polygon(this corner is the center
    // of a flat side). Point a is at the center of the Cell, b is at the edge forming our right angle, and c is the target of the Cell's direction or
    // the point on the polygon the center of the Cell will intersect if it were to continue that far.
    
    // Now we just need to do some simple trigonometry to get the length of line(a,b)
    // Adjacent = cos(theta) * hypotenuse
    
    // This gets out cos(theta)
    
    float cosThetaOfTangent = cos(thetaOfCellTangentWithPolygon);
    
    // This next variable gets the hypotenuse of our triangle(a,b,c), aka line(a,c)
    
    float distanceFromTargetPointOfPolygonToCenterOfCell = distanceBetween(xPos, yPos, xCoordOfPolygonAtTheta, yCoordOfPolygonAtTheta);
    
    // This gets our Adjacent length of line(a,b)
    
    float distanceFromClosestPointOfPolygonToCenterOfCell = distanceFromTargetPointOfPolygonToCenterOfCell * cosThetaOfTangent;
    
    // Now we just check for an overlap, ie: if line(a,b) is less than or equal to the radius
    
    return distanceFromClosestPointOfPolygonToCenterOfCell <= radius;
}

