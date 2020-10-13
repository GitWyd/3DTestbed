//
// Created by ron on 9/11/20.
//

#include "../include/VertexArray.h"
#include <iostream>

VertexArray::VertexArray() {
    /* Vertex Array Objects
     * Before creating all the buffers, I create a vertex array object that will keep track of all the stuff that belongs in the same context
     * */
    glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_RendererID);
}
/*
 * Binds Vertex Buffer & sets up the buffer layout
 */
void VertexArray::addBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout) {
    Bind();
    vb.Bind();
    const auto& elements = layout.getElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); ++i){
        auto& element = elements[i];
        glEnableVertexAttribArray(i); // must enable vertex attribute array before using it
        /* We bind the above array buffer to the Vertex Array at index 0 (you could have a different buffer at location 1)*/
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void *) offset);
        fprintf(stdout,"%d\n", offset);
        offset += element.count*VertexBufferElement::getSizeOfType(element.type);
    }

}

void VertexArray::Bind() const {
    glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const {
    glBindVertexArray(0);
}
