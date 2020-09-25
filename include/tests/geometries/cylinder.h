//
// Created by ron on 9/22/20.
//
/**
 * Cylinder Class
 * Inspired By Song Ho Ahn (song.ahn@gmail.com): http://www.songho.ca/opengl/gl_cylinder.html
 */
#ifndef TITAN_CYLINDER_H
#define TITAN_CYLINDER_H
#include "geometry.h"
namespace titan{

const int MIN_SECTOR_COUNT = 3;
const int MIN_STACK_COUNT = 1;

class Cylinder: Geometry {
public:
    Cylinder(float baseRadius=1.0f, float topRadius=1.0f, float height=1.0f,
    int sectorCount=36, int stackCount=1);
    ~Cylinder() override {};

    void ComputeVertices() override;
    void ComputeIndices() override;
private:
    std::vector<float> getSideNormals();

    float m_baseRadius;
    float m_topRadius;
    float m_height;
    int m_sectorCount;
    int m_stackCount;
    unsigned int m_baseIndex;
    unsigned int m_topIndex;
    std::vector<float> m_unitCircleVertices;
};
}


#endif //TITAN_CYLINDER_H
