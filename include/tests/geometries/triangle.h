//
// Created by ron on 9/30/20.
//

#ifndef INC_3DTESTBED_TRIANGLE_H
#define INC_3DTESTBED_TRIANGLE_H

#include <glm/vec3.hpp>
#include "geometry.h"

namespace titan{
class Triangle : public Geometry{
public:
    // generally you want sectorCount = 2 * stackCount for even resolution
    Triangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2) : m_v0(v0), m_v1(v1), m_v2(v2){}

    ~Triangle() override {};
    void ComputeVertices() override;
    void ComputeIndices() override;

private:
    glm::vec3 m_v0, m_v1, m_v2;
};
}

#endif //INC_3DTESTBED_TRIANGLE_H
