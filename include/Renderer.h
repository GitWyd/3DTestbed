//
// Created by ron on 9/11/20.
//
#ifndef MYGLTUTORIAL_RENDERER_H
#define MYGLTUTORIAL_RENDERER_H

#include <GL/glew.h>
#include <iostream>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

/**
 * OpenGL callback for error messages (GL Version >4.3)
 **/
void GLAPIENTRY
MessageCallback( GLenum source,
GLenum type,
        GLuint id,
GLenum severity,
        GLsizei length,
const GLchar* message,
const void* userParam );

class Renderer{
public:
    void Clear() const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};

#endif //MYGLTUTORIAL_RENDERER_H
