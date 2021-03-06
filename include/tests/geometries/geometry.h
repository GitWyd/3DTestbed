//
// Created by ron on 9/22/20.
//

#ifndef TITAN_GEOMETRY_H
#define TITAN_GEOMETRY_H
#include <vector>
#include <cmath>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>

namespace titan {
class Geometry;
struct CUDA_GEOMETRY;
/*
 * geometry class representing general shapes to be rendered
 */
class Geometry {
public:
    Geometry(): m_vertices_count(0), m_indices_count(0), m_vertices_size(0), m_indices_size(0), v_positions(), v_normals(),
                v_indices(), arrayptr(nullptr){};
    virtual ~Geometry() {};
    virtual void ComputeVertices() = 0;
    virtual void ComputeIndices() = 0 ;
    virtual void InterleaveVertices();
    void addVertex(float x, float y, float z);
    void addNormal(float x, float y, float z);
    void addIndices(unsigned int i1, unsigned int i2, unsigned int i3);
    void addVertexVec3(glm::vec3 v);
    void addNormalVec3(glm::vec3 v);
    void addIndicesVec3(glm::vec3 v);
    void clearArrays();
    //void addTexCoord(float s, float t);
    std::vector<float> ComputeFaceNormal(float x1, float y1, float z1,
                                         float x2, float y2, float z2,
                                         float x3, float y3, float z3);
    unsigned int m_vertices_count;
    unsigned int m_indices_count;
    float m_vertices_size;
    float m_indices_size;
    std::vector<float> v_positions;
    std::vector<float> v_normals;
    std::vector<float> v_interleavedVertices;
    std::vector<unsigned int> v_indices;

    CUDA_GEOMETRY * arrayptr; // pointer to CUDA version of Geometry
};
/*
 * GPU memory analog of geometry class to represent shape-geometries on GPU side
 */
struct CUDA_GEOMETRY{
    CUDA_GEOMETRY(Geometry & object);
    float * v_positions;
    float * v_normals;
    unsigned int * indices;
    unsigned int vertices_count;
    unsigned int indices_count;
    float vertices_size;
    float indices_size;
};
}

#endif //TITAN_GEOMETRY_H
