//
// Created by ron on 9/30/20.
//

#include "../../../include/tests/geometries/triangle.h"
namespace titan{
    void Triangle::ComputeVertices() {
        m_vertices_count = 3;
        m_vertices_size = 3 * 3 * sizeof(float);
        addVertexVec3(m_v0);
        addVertexVec3(m_v1);
        addVertexVec3(m_v2);
        std::vector<float> normals = ComputeFaceNormal(m_v0.x, m_v0.y, m_v0.z,m_v1.x, m_v1.y, m_v1.z,m_v2.x, m_v2.y, m_v2.z);
        addNormalVec3(glm::vec3(normals[0], normals[1], normals[2]));
        addNormalVec3(glm::vec3(normals[0], normals[1], normals[2]));
        addNormalVec3(glm::vec3(normals[0], normals[1], normals[2]));
        this->InterleaveVertices();
}

void Triangle::ComputeIndices() {
    addIndices(0, 1, 2);
    m_indices_count = v_indices.size();
    m_indices_size = m_indices_count * sizeof(unsigned int);
}

}
