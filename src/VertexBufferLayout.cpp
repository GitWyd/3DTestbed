//
// Created by ron on 9/11/20.
//

#include "../include/VertexBufferLayout.h"
template<>
void VertexBufferLayout::Push<float>(unsigned int count){
    m_elements.push_back({GL_FLOAT, count, false});
    m_stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
}
template<>
void VertexBufferLayout::Push<unsigned int>(unsigned int count){
    m_elements.push_back({GL_UNSIGNED_INT, count, false});
    m_stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
}
template<>
void VertexBufferLayout::Push<unsigned char>(unsigned int count){
    m_elements.push_back({GL_UNSIGNED_BYTE, count, true});
    m_stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
}
