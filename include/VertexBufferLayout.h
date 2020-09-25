//
// Created by ron on 9/11/20.
//

#ifndef MYGLTUTORIAL_VERTEXBUFFERLAYOUT_H
#define MYGLTUTORIAL_VERTEXBUFFERLAYOUT_H
#include <vector>
#include <GL/glew.h>
struct VertexBufferElement{
    unsigned int type;
    unsigned int count;
    bool normalized;

    /* how is this any better than just calling sizeof(data_type)???? */
    static unsigned int getSizeOfType(unsigned int type){
        switch (type){
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;
        }
        return 0;
    }
};

class VertexBufferLayout {
private:
    std::vector<VertexBufferElement> m_elements;
    unsigned int m_stride;
public:
    VertexBufferLayout(): m_stride(0){}
    template<typename  T>
    void Push(unsigned int count);
    inline const std::vector<VertexBufferElement> & getElements() const { return m_elements; }
    inline unsigned int getStride() const { return m_stride; }
};


#endif //MYGLTUTORIAL_VERTEXBUFFERLAYOUT_H
