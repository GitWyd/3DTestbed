//
// Created by ron on 9/11/20.
//
#include "../include/Renderer.h"

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
                 const void* userParam )
{
// if low-severity, then don't print it is an error
if (severity == GL_DEBUG_SEVERITY_NOTIFICATION){
fprintf( stdout, "[NOTIFICATION] GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
type, severity, message );

} else if (severity == GL_DEBUG_SEVERITY_LOW) {
    fprintf( stdout, "[Low Priority] GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
             ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
             type, severity, message );

} else {
    fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
             ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
             type, severity, message );

}
}

void Renderer::Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const {
    shader.Bind();
    va.Bind();
    ib.Bind();

    // glDrawArrays(GL_TRIANGLES,0, 6);
    glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0); // nullptr e.g. we already bound ibo
}

void Renderer::Clear() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
