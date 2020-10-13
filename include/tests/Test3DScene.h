//
// Created by ron on 9/25/20.
//

#ifndef INC_3DTESTBED_TEST3DSCENE_H
#define INC_3DTESTBED_TEST3DSCENE_H
#include "Test.h"
#include "../Renderer.h"
#include "geometries/sphere.h"
#include "geometries/triangle.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

namespace test{


class Test3DScene : public Test{
public:
    Test3DScene();
    ~Test3DScene();

    void OnUpdate(float deltaTime) override;
    void OnRender() override;
    void OnImGuiRender() override;
private:
    float m_theta;

    glm::vec3 body_translationA;
    glm::vec3 body_translationB;

    glm::mat4 m_matrixView, m_matrixModel, m_matrixModelView, m_matrixNormal;
    glm::mat4 m_Proj, m_View, m_MVP;

    std::unique_ptr<VertexArray> m_VAO;
    std::unique_ptr<VertexBuffer> m_VertexBuffer;
    std::unique_ptr<IndexBuffer> m_IBO;
    std::unique_ptr<Shader> m_Shader;
};

}

#endif //INC_3DTESTBED_TEST3DSCENE_H
