//
// Created by ron on 9/12/20.
//

#ifndef MYGLTUTORIAL_SHADER_H
#define MYGLTUTORIAL_SHADER_H

#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <unordered_map>
class Shader {
private:
    unsigned int m_RendererID;
    mutable std::unordered_map<std::string, int> m_UniformLocationCache;
    /**
     *  Shader Raw Code Strings
     */
    std::string vertexShader =
            R"glsl(
        #version 330 core
        layout(location = 0) in vec4 position; // we are inputing vec2, but we call it a vec4 GL handles it
        layout(location = 1) in vec2 texCoordinate; // taking in texture coordinate at location 1

        out vec2 v_texCoordinate;

        uniform mat4 u_MVP; // Model View Projection Matrix (projection onto screen canvas)

        void main()
        {
            gl_Position = u_MVP * position;
            v_texCoordinate = texCoordinate;
        }
                 )glsl";
    std::string fragmentShader =
            R"glsl(
        #version 330 core
        layout(location = 0) out vec4 color;
        in vec2 v_texCoordinate;
        uniform vec4 u_color; // uniform variable
        uniform sampler2D u_texture; // texture uniform
        void main()
        {
            vec4 texColor = texture(u_texture, v_texCoordinate);
            color = (texColor*2 + u_color)/3.0; // hardcode color vec4(r,g,b,alpha)
        }
                 )glsl";
/**
 * Shader Class
 */
public:
    Shader();

    virtual ~Shader();

    void Bind() const;

    void Unbind() const;

    // Set uniforms
    void SetUniform4f(const std::string &name, float v0, float v1, float f2, float f3);
    void SetUniformi(const std::string &name, int value);
    void SetUniformMat4f(const std::string &name, const glm::mat4 matrix);

private:
    int GetUniformLocation(const std::string &name) const;

    unsigned int CompileShader(unsigned int type, const std::string &source);

    unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader);
};

#endif //MYGLTUTORIAL_SHADER_H
