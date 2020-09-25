//
// Created by ron on 9/9/20.
//

#ifndef MYGLTUTORIAL_VERTEXBUFFER_H
#define MYGLTUTORIAL_VERTEXBUFFER_H
#include <GL/glew.h>
class VertexBuffer
{
private:
    unsigned int m_RendererID;
public:
    VertexBuffer(const void * data, unsigned int size);
    ~VertexBuffer();
    void Bind() const;
    void Unbind() const;
};
#endif //MYGLTUTORIAL_VERTEXBUFFER_H
