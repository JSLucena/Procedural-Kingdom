#ifndef _VORONOI_H
#define _VORONOI_H
#include <vector>

#include "point.hpp"

using namespace boost::polygon;
//voronoi_diagram<double> vd;

void possionDiskSampling(std::vector<GamePoint> &points, int count, float radius, int maxX, int maxY);
void buildVoronoi(std::vector<GamePoint> &points,voronoi_diagram<double> &vd);

#endif