//
// Created by ron on 9/18/20.
//

#include "../../include/tests/TestTexture2D.h"

test::TestTexture2D::TestTexture2D():
    body_translationA(150, 100, 0),
    body_translationB(150, 100, 0){
    float positions[] = {
            -50.0f, -50.0f, 0.0f, 0.0f, // idx 0 | lower left texture coordinate
             50.0f, -50.0f, 1.0f, 0.0f, // idx 1 | right most edge
             50.0f,  50.0f, 1.0f, 1.0f, // idx 2 |
            -50.0f,  50.0f, 0.0f, 1.0f // idx 3
    };
    unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
    };

    m_VAO = std::make_unique<VertexArray>();
    /* generate OpenGL index buffer using IndexBuffer class */
    m_IBO = std::make_unique<IndexBuffer>(indices, 6);

    /* generate OpenGL vertex buffer using VertexBuffer class */
    m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));

    VertexBufferLayout layout;
    /* define the layout of our buffer in our case one data point i.e. vertex is <float> , <float>*/
    layout.Push<float>(2);
    layout.Push<float>(2);
    m_VAO->addBuffer(*m_VertexBuffer, layout);


    /** MVP */
    /* Create a projection matrix for a 16:9 aspect ratio eg. 1280 x 720
     * We map our vertices onto a [-1,1] range in both the x and y direction
     * */
    float proj_scale = 1.0;
    m_Proj = glm::ortho(0.0f   * proj_scale,
                        1280.0f   * proj_scale,
                        0.0f* proj_scale,
                        720.0f    * proj_scale,
                        -1.0f * proj_scale,
                        1.0f   * proj_scale);
    // translation of camera 100 units to the right e.g. moving model 100 units to the left
    m_View = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0,0));

    /*
     *  Load Shaders
     */
    m_Shader = std::make_unique<Shader>();
    m_Shader->Bind();
    /* How to assign value to a uniform in a shader */
    m_Shader->SetUniform4f("u_color", 0.3f, 0.4f, 0.5f, 1.0f);
    /* Bind a texture to our rectangle */
    m_Texture = std::make_unique<Texture>("../images/texture02.png");
    m_Shader->SetUniformi("u_texture", 0);
}

test::TestTexture2D::~TestTexture2D() {

}

void test::TestTexture2D::OnUpdate(float deltaTime) {
    Test::OnUpdate(deltaTime);
}

void test::TestTexture2D::OnRender() {
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    Renderer renderer;

    m_Texture->Bind(0);
    {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), body_translationA);
        m_Shader->SetUniformMat4f("u_MVP", m_Proj * m_View * model);
        renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
    }
    {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), body_translationB);
        m_Shader->SetUniformMat4f("u_MVP", m_Proj * m_View * model);
        renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
    }
}

void test::TestTexture2D::OnImGuiRender() {
    static int counter = 0;
    {
        ImGui::SliderFloat2("TranslationA", &body_translationA.x, -100.0f, 720.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::SliderFloat2("TranslationB", &body_translationB.x, -100.0f, 720.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }
}
