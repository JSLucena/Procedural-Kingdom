#include "voronoi.hpp"
#include <iostream>
#include <cstdlib>



void possionDiskSampling(std::vector<GamePoint> &points, int count, float radius, int maxX, int maxY)
{
    while(points.size() < count*count)
    {
        bool tryAgain = false;

        GamePoint newPoint = GamePoint(float(rand()% maxX), float(rand() % maxY));
        for (auto & element : points) 
        {
                if(newPoint.distanceTo(element.getP()) < radius)
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

void buildVoronoi(std::vector<GamePoint> &points, voronoi_diagram<double> &vd)
{
    std::vector<Point> voronoiSites;
    for (auto & element : points)
    {
        voronoiSites.push_back(element.getP());
    }
    
    
    construct_voronoi(voronoiSites.begin(),voronoiSites.end(),&vd);
    int result = 0;
    for (voronoi_diagram<double>::const_cell_iterator it = vd.cells().begin();it != vd.cells().end(); ++it) 
    {
        const voronoi_diagram<double>::cell_type &cell = *it;
        std::cout << "Cell " << cell.source_index() << " neighbors: ";
        const voronoi_diagram<double>::edge_type *edge = cell.incident_edge();
        // This is convenient way to iterate edges around Voronoi cell.
        do {
        if (edge->is_primary())
        {
            const voronoi_diagram<double>::cell_type& neighbor_cell = *edge->twin()->cell();
            std::cout << neighbor_cell.source_index() << " ";
        }
        edge = edge->next();
        } while (edge != cell.incident_edge());
        std::cout << std::endl;
    }

    
}