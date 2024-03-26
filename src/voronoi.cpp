#include "voronoi.hpp"
#include <cstdlib>
void possionDiskSampling(std::vector<Point> &points, int count, float radius, int maxX, int maxY)
{
    while(points.size() < count*count)
    {
        bool tryAgain = false;

        Point newPoint = Point(float(rand()% maxX), float(rand() % maxY));
        for (auto & element : points) 
        {
                if(newPoint.distanceTo(element) < radius)
                {
                    tryAgain = true;
                    break;
                }
        }
        if(!tryAgain)
        {
            points.push_back(newPoint);
        }
    }
    return ;
};