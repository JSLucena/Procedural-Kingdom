#ifndef _POINT_H
#define _POINT_H
#include <boost/polygon/voronoi.hpp>

typedef boost::polygon::point_data<double> Point;

class GamePoint
{
private:
    Point p;
    //boost::polygon::voronoi_cell<double>* cell;
    float z = 0.0f;
public:
    GamePoint();
    GamePoint(float x, float y);
    ~GamePoint();
    float getX();
    float getY();
    float getZ();
    Point getP();
    void setZ(float z);
    void setX(float x);
    void setY(float y);
    float distanceTo(Point p);
};

#endif
