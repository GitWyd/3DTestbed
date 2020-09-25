//
// Created by ron on 9/22/20.
//
/**
 * Sphere Class
 * Inspired By Song Ho Ahn (song.ahn@gmail.com): http://www.songho.ca/opengl/gl_sphere.html
 */

#ifndef TITAN_SPHERE_H
#define TITAN_SPHERE_H
#include "geometry.h"

namespace titan{

class Sphere : public Geometry{
public:
    // generally you want sectorCount = 2 * stackCount for even resolution
    Sphere(float radius=1.0f, int sectorCount=16, int stackCount=8);
    ~Sphere() override {};
    void ComputeVertices() override;
    void ComputeIndices() override;
private:

    float m_rad;
    int m_sectorCount;
    int m_stackCount;

};
}


#endif //TITAN_SPHERE_H
