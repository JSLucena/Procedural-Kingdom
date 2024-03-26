#ifndef _POINT_H
#define _POINT_H

class Point
{
private:
    float x;
    float y;
    float z = 0.0f;
public:
    Point();
    Point(float x, float y);
    ~Point();
    float getX();
    float getY();
    float getZ();
    void setZ(float z);
    void setX(float x);
    void setY(float y);
    float distanceTo(Point p);
};

#endif