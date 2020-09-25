//
// Created by ron on 9/11/20.
//

#ifndef MYGLTUTORIAL_VERTEXARRAY_H
#define MYGLTUTORIAL_VERTEXARRAY_H
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
class VertexArray {
private:
    unsigned int m_RendererID;
public:
    VertexArray();
    ~VertexArray();

    void addBuffer(const VertexBuffer& vb, const VertexBufferLayout &layout);
    void Bind() const;
    void Unbind() const;
};


#endif //MYGLTUTORIAL_VERTEXARRAY_H
