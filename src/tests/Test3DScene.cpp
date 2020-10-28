//
// Created by ron on 9/25/20.
//
#include<iomanip>
#include "../../include/tests/Test3DScene.h"
#define FIXED_FLOAT(x) std::fixed << std::setprecision(3) << x
namespace test{

    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
    };

    Test3DScene::Test3DScene() {
        /*
         * Initialize OpenGL
         */
        /*
        glShadeModel(GL_SMOOTH);

        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
        glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
        */
        glEnable(GL_DEPTH_TEST);
        glDepthRange(0.1,1.0);
        //glEnable(GL_LIGHTING);
        //glEnable(GL_CULL_FACE);
        //glCullFace(GL_BACK);
        //glClearStencil(0);
        glClearDepth(1.0f);
        glDepthFunc(GL_LEQUAL);

        // could set to GL_FILL/GL_LINE e.g. colored in or wireframe
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        /*
         * Compute A Sphere
         */
        //titan::Sphere s1(300.0,16,4);
        int s_res = 2;
        titan::Sphere s1(300.0,s_res*16,s_res*4);
        //titan::Triangle s1(glm::vec3(300, 0, 0), glm::vec3(300, 300, 0), glm::vec3(0, 300,0));
        s1.ComputeVertices();
        s1.ComputeIndices();
        m_matrixModel = glm::translate(glm::mat4(1.0f), glm::vec3(300,300,0));

        // debug printout
        /*
        std::cout << "nr_vertices: " << s1.m_vertices_count << "\t nr_indices: " << s1.m_indices_count << std::endl;
        std::cout << "s1.v_interleavedVertices.size(): " << s1.v_interleavedVertices.size() << std::endl;       
        for (int j = 0; j < s1.v_interleavedVertices.size()/6; j++){
            std::cout << "[";
            for (int i = j*6; i < (j*6+6); i++){
                std::cout << FIXED_FLOAT(s1.v_interleavedVertices[i]) << "\t";
            }
            std::cout << "]" << std::endl;
        }
         */

        m_VAO = std::make_unique<VertexArray>();
        m_IBO = std::make_unique<IndexBuffer>(s1.v_indices.data(), s1.m_indices_count);
        m_VertexBuffer = std::make_unique<VertexBuffer>(s1.v_interleavedVertices.data(),
                                                        s1.m_vertices_size*2);
        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(3);
        m_VAO->addBuffer(*m_VertexBuffer, layout);

        /*
         *  Load Shaders
         */
        m_Shader = std::make_unique<Shader>();
        m_Shader->Bind();
        /*
         * Set Uniform values
         */

        float cameraDistance = 1000.0f;
        /* Set Vertex Shader Uniforms */
        m_matrixView = glm::translate(glm::mat4(1.0f), glm::vec3(0,0,-cameraDistance));
        m_theta = 0;
        m_View = glm::rotate(m_matrixView, m_theta, glm::vec3(0,0,1));

        m_matrixModelView = m_matrixView * m_matrixModel;
        m_Proj = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, 1.0f, 2000.0f);
        m_MVP = m_Proj * m_matrixModelView;

        m_matrixNormal = m_matrixModelView;
        m_matrixNormal[3] = glm::vec4(0.0f,0.0f, 0.0f, 1.0f);
        /*
        float width = 1280;
        float height = 720;
        float aspect = (float)width / (float)height;
        glm::vec3 cameraPosition(0, 0, -1000);
        aspect = (float)width / (float)height;
        glm::mat4 pMat = glm::perspective(1.0472f, aspect, 1.f, 2000.0f);
        glm::mat4 vMat = glm::lookAt(cameraPosition, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
        glm::mat4 mMat = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
        glm::mat4 mvpMat = pMat * vMat * mMat;
        m_View = vMat;
        m_Proj = pMat;
        m_MVP = mvpMat;
        m_matrixModelView = vMat*mMat;
        m_matrixNormal = m_matrixModelView;
        m_matrixNormal[3] = glm::vec4(0.0f,0.0f, 0.0f, 1.0f);
        */
        m_Shader->SetUniformMat4f("matrixModelView", m_matrixModelView);
        m_Shader->SetUniformMat4f("matrixNormal", m_matrixNormal);
        m_Shader->SetUniformMat4f("matrixModelViewProjection", m_MVP);
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
        Renderer renderer;
        {
            renderer.Draw(*m_VAO, *m_IBO, *m_Shader);

           // glBindVertexArray(VAO);
           // glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
           // glBindVertexArray(0);

            // glBegin(GL_TRIANGLES);
            // glColor3f(1,1,1);
            // glVertex3f(300,0,0);
            // glVertex3f(300,300,0);
            // glVertex3f(0,300,0);
            // glEnd();
        }
    }

    void Test3DScene::OnImGuiRender() {
        {
        }
    }
}