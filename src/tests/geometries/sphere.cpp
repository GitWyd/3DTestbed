//
// Created by ron on 9/22/20.
//

#include "../../../include/tests/geometries/sphere.h"

namespace titan{
Sphere::Sphere(float radius, int sectorCount, int stackCount) :
m_rad(radius), m_sectorCount(sectorCount), m_stackCount(stackCount){}
void Sphere::ComputeVertices() {
    const float PI = acos(-1);

    // clear memory of prev arrays
    clearArrays();

    float x, y, z, xy;                              // vertex position
    float nx, ny, nz, lengthInv = 1.0f / m_rad;    // normal
    float s, t;                                     // texCoord

    float sectorStep = 2 * PI / m_sectorCount;
    float stackStep = PI / m_stackCount;
    float sectorAngle, stackAngle;

    for(int i = 0; i <= m_stackCount; ++i)
    {
        stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
        xy = m_rad * cosf(stackAngle);             // r * cos(u)
        z = m_rad * sinf(stackAngle);              // r * sin(u)

        // add (sectorCount+1) vertices per stack
        // the first and last vertices have same position and normal, but different tex coords
        for(int j = 0; j <= m_sectorCount; ++j)
        {
            sectorAngle = j * sectorStep;           // starting from 0 to 2pi

            // vertex position
            x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
            y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
            addVertex(x, y, z);

            // normalized vertex normal
            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;
            addNormal(nx, ny, nz);

            // vertex tex coord between [0, 1]
            /*  Textures omitted for now
            s = (float)j / m_sectorCount;
            t = (float)i / m_stackCount;
            m_addTexCoord(s, t);
            */
        }
    }
}

void Sphere::ComputeIndices() {
    // indices
    //  k1--k1+1
    //  |  / |
    //  | /  |
    //  k2--k2+1
    unsigned int k1, k2;
    for(int i = 0; i < m_stackCount; ++i)
    {
        k1 = i * (m_sectorCount + 1);     // beginning of current stack
        k2 = k1 + m_sectorCount + 1;      // beginning of next stack

        for(int j = 0; j < m_sectorCount; ++j, ++k1, ++k2)
        {
            // 2 triangles per sector excluding 1st and last stacks
            if(i != 0)
            {
                addIndices(k1, k2, k1+1);   // k1---k2---k1+1
            }

            if(i != (m_stackCount-1))
            {
                addIndices(k1+1, k2, k2+1); // k1+1---k2---k2+1
            }
        }
    }
}


}