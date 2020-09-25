//
// Created by ron on 9/25/20.
//

#include "../../include/tests/Test3DScene.h"
namespace test{

    Test3DScene::Test3DScene() {
        /*
         * Compute A Sphere
         */
        titan::Sphere sphere1();

        /*
         *  Load Shaders
         */
        m_Shader = std::make_unique<Shader>();
        m_Shader->Bind();
        /*
         * Set Uniform values
         */
        float cameraDistance = 1.0f;
        /* Set Vertex Shader Uniforms */
        glm::mat4 matrixView = glm::translate(glm::mat4(), glm::vec3(0,0,-cameraDistance));
        matrixView = glm::rotate(matrixView, 0.3f, glm::vec3(1,1,0));

        glm::mat4 matrixModel;
        glm::mat4 matrixModelView = matrixView * matrixModel;
        glm::mat4 matrixProjection = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
        glm::mat4 matrixModelViewProjection = matrixProjection * matrixModelView;
        glm::mat4 matrixNormal = matrixModelView;
        matrixNormal[3] = glm::vec4(0.0f,0.0f, 0.0f, 1.0f);
        m_Shader->SetUniformMat4f("matrixModelView", matrixModelView);
        m_Shader->SetUniformMat4f("matrixNormal", matrixNormal);
        m_Shader->SetUniformMat4f("matrixModelViewProjection", matrixModelViewProjection);
        /* Set Fragment Shader Uniforms */
        m_Shader->SetUniform4f("lightPosition"  , 0.0f, 0.0f, 1.0f, 0.0f);
        m_Shader->SetUniform4f("lightAmbient"   , 0.3f, 0.3f, 0.3f, 1.0f);
        m_Shader->SetUniform4f("lightDiffuse"   , 0.7f, 0.7f, 0.7f, 1.0f);
        m_Shader->SetUniform4f("lightSpecular"  , 1.0f, 1.0f, 1.0f, 1.0f);
        m_Shader->SetUniform4f("materialAmbient", 0.5f, 0.5f, 0.5f, 1.0f);
        m_Shader->SetUniform4f("materialDiffuse", 0.7f, 0.7f, 0.7f, 1.0f);
        m_Shader->SetUniform4f("materialSpecular", 0.4f, 0.4f, 0.4f, 1.0f);
        m_Shader->SetUniformf("materialShininess", 16.0f);
    }

    Test3DScene::~Test3DScene() {

    }

    void Test3DScene::OnUpdate(float deltaTime) {
        Test::OnUpdate(deltaTime);
    }

    void Test3DScene::OnRender() {
        Test::OnRender();
    }

    void Test3DScene::OnImGuiRender() {
        Test::OnImGuiRender();
    }
}