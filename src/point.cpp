#include "point.hpp"
#include <cmath>
GamePoint::GamePoint()
{

};
GamePoint::~GamePoint()
{

};
GamePoint::GamePoint(float x, float y)
{
    p.x(x);
    p.y(y);
}
float GamePoint::getX() {return p.x();};
float GamePoint::getY() {return p.y();};
float GamePoint::getZ() {return z;};
Point GamePoint::getP() {return p;};
bool  GamePoint::isInvalid(){return invalid;};
void  GamePoint::setX(float x) {p.x(x);};
void  GamePoint::setY(float y) { p.y(y);};
void  GamePoint::setZ(float z) {this->z = z;};
void  GamePoint::setInvalid(bool b){invalid = b;};

float GamePoint::distanceTo(Point other)
{
    return sqrt( pow(other.x() - p.x(),2) + pow(other.y() - p.y(),2) );
}
