//
// Created by ron on 9/22/20.
//

#include "../../../include/tests/geometries/geometry.h"

namespace titan{
    void Geometry::clearArrays(){
        std::vector<float>().swap(v_positions);
        std::vector<float>().swap(v_normals);
        //std::vector<float>().swap(v_texCoords);
        std::vector<unsigned int>().swap(v_indices);
        //std::vector<unsigned int>().swap(lineIndices);
    }
    void Geometry::addVertex(float x, float y, float z) {
        v_positions.push_back(x);
        v_positions.push_back(y);
        v_positions.push_back(z);
    }

    void Geometry::addNormal(float x, float y, float z) {
        v_normals.push_back(x);
        v_normals.push_back(y);
        v_normals.push_back(z);

    }
    void Geometry::addIndices(unsigned int i1, unsigned int i2, unsigned int i3) {
        v_indices.push_back(i1);
        v_indices.push_back(i2);
        v_indices.push_back(i3);
    }

    std::vector<float>
    Geometry::computeFaceNormal(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3,
                                float z3) {
        const float EPSILON = 1e-7;

        std::vector<float> normal(3, 0.0f);     // default return value (0,0,0)
        float nx, ny, nz;

        // find 2 edge vectors: v1-v2, v1-v3
        float ex1 = x2 - x1;
        float ey1 = y2 - y1;
        float ez1 = z2 - z1;
        float ex2 = x3 - x1;
        float ey2 = y3 - y1;
        float ez2 = z3 - z1;

        // cross product: e1 x e2
        nx = ey1 * ez2 - ez1 * ey2;
        ny = ez1 * ex2 - ex1 * ez2;
        nz = ex1 * ey2 - ey1 * ex2;

        // normalize only if the length is > 0
        float length = sqrtf(nx * nx + ny * ny + nz * nz);
        if(length > EPSILON)
        {
            // normalize
            float lengthInv = 1.0f / length;
            normal[0] = nx * lengthInv;
            normal[1] = ny * lengthInv;
            normal[2] = nz * lengthInv;
        }

        return normal;
    }


    CUDA_GEOMETRY::CUDA_GEOMETRY(titan::Geometry &object) {
        v_positions = object.v_positions.data();
        v_normals = object.v_normals.data();
        indices = object.v_indices.data();
        vertices_count = object.vertices_count;
        indices_count = object.indices_count;
        vertices_size = object.vertices_size;
        indices_size = object.indices_size;
    }

}
