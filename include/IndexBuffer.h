//
// Created by ron on 9/9/20.
//

#ifndef MYGLTUTORIAL_INDEXBUFFER_H
#define MYGLTUTORIAL_INDEXBUFFER_H
#include <GL/glew.h>
class IndexBuffer
{
private:
    unsigned int m_RendererID;
    unsigned int m_count;
public:
    IndexBuffer(const unsigned int* data, unsigned int size);
    ~IndexBuffer();
    void Bind() const;
    void Unbind() const;

    inline unsigned int GetCount() const { return m_count;}
};
#endif //MYGLTUTORIAL_INDEXBUFFER_H
