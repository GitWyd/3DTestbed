//
// Created by ron on 9/9/20.
//
#include "../include/VertexBuffer.h"


VertexBuffer::VertexBuffer(const void *data, unsigned int size) {
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID); // specifies also the type of buffer
    // since we know the data that goes into the buffer, we can provide it with data straight away
    // GL Doesn't know how to use those bytes we have given it yet
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    /* Tell openGL how to read our data:
     *  glVertexAttribPointer( <idx of what we are referring to e.g. position, texture, normal, etc.,
     *                         size e.g. number of elements to read,
     *                         data type we are reading e.g. GL_FLOAT
     *                         bool normalized (can normalize e.g. color data if not done beforehand)
     *                         stride = full size of one vertex in a buffer (e.g. 2*sizeof(float) here, but
     *                                    it could consist of (<size of positions data> + <size of texture> etc.)
     *                         pointer e.g. offset to the data we are reading in our case 0, but if our data were of
     *                         the form [pos_float, pos_float, text_float, text_float] we might want to read our texture
     *                         coordinates, and would have to pass 2*size(float) as our offset (there are more elegant
     *                         ways to get the offset than to just calculate sizeof(), by using macros
     */

}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID); // specifies also the type of buffer
}

void VertexBuffer::Unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0); // specifies also the type of buffer
}
