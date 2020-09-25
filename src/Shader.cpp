//
// Created by ron on 9/12/20.
//

#include "../include/Shader.h"

Shader::Shader(): m_RendererID(0) {
    m_RendererID = CreateShader(vertexShader, fragmentShader);
}

Shader::~Shader(){
    glDeleteProgram(m_RendererID);
}
unsigned int Shader::CompileShader(unsigned int type, const std::string & source){
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    /* (id of shader, nr_of shaders provided, ptr to source, specifies an array of string lengths
     * if multiple shaders are passed in or can be nullptr for a single null terminated string)
     */
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // TODO: Error handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE){
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        // we query the lengnth of the error message and now go retrieve the error message
        // to avoid data allocation issue from variable, we do the below
        char * message = (char *) alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;
        // cleanup failed shader
        glDeleteShader(id);
        return 0;
    }

    return id;
}
unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader){
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    /* attach shaders to the program */
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program); // link program
    glValidateProgram(program); // validate program

    // TODO: glDetachShader after linking
    /* clean up intermediate shader files after linking */
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

void Shader::Bind() const {
    glUseProgram(m_RendererID);
}

void Shader::Unbind() const {
    glUseProgram(0);
}

void Shader::SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3) {
    int location = GetUniformLocation(name);
    if (location != -1)
        glUniform4f(location , v0, v1, v2, v3);
}
void Shader::SetUniformi(const std::string &name, int value) {
    int location = GetUniformLocation(name);
    if (location != -1)
        glUniform1i(location, value);
}
void Shader::SetUniformMat4f(const std::string &name, const glm::mat4 matrix) {
    // (uniform location, nr_matrices provided, transpose_matrix?, pointer to first element)
    int location = GetUniformLocation(name);
    if (location != -1)
        glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}

int Shader::GetUniformLocation(const std::string &name) const {
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()){
        return m_UniformLocationCache[name];
    }
    int location = glGetUniformLocation(m_RendererID, name.c_str());
    if (location == -1){
        std::cout << "Warning: uniform '" << name << "' doesn't exists!" << std::endl;
    }
    m_UniformLocationCache[name] = location;
    return location;
}