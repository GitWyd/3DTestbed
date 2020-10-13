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
    std::string fs_code =
            R"glsl(
#version 330 core

// uniforms
uniform vec4 lightPosition;     // should be in the eye space
uniform vec4 lightAmbient;      // light ambient color
uniform vec4 lightDiffuse;      // lightDiffuse
uniform vec4 lightSpecular;     // light specular color
uniform vec4 materialAmbient;   // material ambient color
uniform vec4 materialDiffuse;   // material diffuse color
uniform vec4 materialSpecular;  // material specular color
uniform float materialShininess;// material specular shiny
// inputs
in vec3 esVertex;
in vec3 esNormal;

// outputs
layout(location = 0) out vec4 frag_color;

void main()
{
    vec3 normal = normalize(esNormal);
    vec3 light;
    if (lightPosition.w == 0.0)
    {
        light = normalize(lightPosition.xyz);
    }
    else
    {
        light = normalize(lightPosition.xyz - esVertex);
    }
    vec3 view = normalize(-esVertex);
    vec3 halfv = normalize(light + view);

    vec3 color = lightAmbient.rgb * materialAmbient.rgb; // begin with ambient
    float dotNL = max(dot(normal, light), 0.0);
    color += lightDiffuse.rgb * materialDiffuse.rgb * dotNL;
    float dotNH = max(dot(normal, halfv), 0.0);
    color += pow(dotNH, materialShininess) * lightSpecular.rgb * materialSpecular.rgb;

    // set frag color
    frag_color = vec4(color, materialDiffuse.a);
    //frag_color = vec4(1,1,1, 1.0);
}
)glsl";

    std::string vs_code =
            R"glsl(
#version 330 core

// uniforms
uniform mat4 matrixModelView;
uniform mat4 matrixNormal;
uniform mat4 matrixModelViewProjection;

// vertex attributes (intput)
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;

// varying (output)
out vec3 esVertex;
out vec3 esNormal;

void main()
{
    esVertex = vec3(matrixModelView * vec4(vertexPosition, 1.0));
    esNormal = vec3(matrixNormal * vec4(vertexNormal, 1.0));
    gl_Position = matrixModelViewProjection * vec4(vertexPosition, 1.0);
}
)glsl";

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
    void SetUniformf(const std::string &name, float value);
    void SetUniformi(const std::string &name, int value);
    void SetUniform4f(const std::string &name, float v0, float v1, float f2, float f3);
    void SetUniformMat4f(const std::string &name, const glm::mat4 matrix);

private:
    int GetUniformLocation(const std::string &name) const;

    unsigned int CompileShader(unsigned int type, const std::string &source);

    unsigned int CreateShader(const std::string &str_vs, const std::string &str_fs);
};

#endif //MYGLTUTORIAL_SHADER_H
