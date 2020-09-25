//
// Created by ron on 9/22/20.
//


#include "../../../include/tests/geometries/cylinder.h"

namespace titan{
    Cylinder::Cylinder(float baseRadius, float topRadius, float height, int sectorCount, int stackCount) :
        m_baseRadius(baseRadius), m_topRadius(topRadius), m_height(height), m_sectorCount(sectorCount),
        m_stackCount(stackCount){

    }

    void Cylinder::ComputeVertices() {
    }

    void Cylinder::ComputeIndices() {
    }


    std::vector<float> Cylinder::getSideNormals() {
        return std::vector<float>();
    }

}