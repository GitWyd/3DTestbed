//
// Created by ron on 9/14/20.
//
#include "../include/Texture.h"

Texture::Texture(const std::string& path) :
        m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0){
    stbi_set_flip_vertically_on_load(1);
    m_LocalBuffer = stbi_load(m_FilePath.c_str(), &m_Width, &m_Height, &m_BPP, 4);

    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);

    /*minimum of four texture settings that need to be provided to not just get a black texture*/
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    /* you could pass a null pointer here to provide a texture later*/
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
    glBindTexture(GL_TEXTURE_2D, 0); // unbind
    // free data after use
    if (m_LocalBuffer){
        stbi_image_free(m_LocalBuffer);
    }
}

Texture::~Texture() {
    glDeleteTextures(1, &m_RendererID);
}

/* Since we can bind multiple textures at once, we want to be able to set it to a slot */
void Texture::Bind(unsigned int slot = 0) const {
    glActiveTexture(GL_TEXTURE0 + slot); // select the texture slot you want to put it in
    glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::Unbind() const {

}
