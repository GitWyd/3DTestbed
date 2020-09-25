//
// Created by ron on 9/18/20.
//

#ifndef MYGLTUTORIAL_TESTTEXTURE2D_H
#define MYGLTUTORIAL_TESTTEXTURE2D_H

#include "Test.h"
#include "../Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>
namespace test{
    class TestTexture2D: public Test {
    public:
        TestTexture2D();
        ~TestTexture2D();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
    private:
        glm::vec3 body_translationA;
        glm::vec3 body_translationB;

        glm::mat4 m_Proj, m_View;

        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<IndexBuffer> m_IBO;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Texture> m_Texture;
    };
}


#endif //MYGLTUTORIAL_TESTTEXTURE2D_H
