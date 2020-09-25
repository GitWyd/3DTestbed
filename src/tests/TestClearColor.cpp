//
// Created by ron on 9/18/20.
//

#include "../../include/tests/TestClearcolor.h"
namespace test{
    TestClearColor::TestClearColor():m_ClearColor{0.1f, 0.2f, 0.3f, 0.4f}{

    }
    TestClearColor::~TestClearColor(){

    }
    void TestClearColor::OnUpdate(float deltaTime){

    }
    void TestClearColor::OnRender(){
        glClearColor(m_ClearColor[0],m_ClearColor[1],m_ClearColor[2],m_ClearColor[3]);
        glClear(GL_COLOR_BUFFER_BIT);

    }
    void TestClearColor::OnImGuiRender(){
        ImGui::ColorEdit4("Clear Color", m_ClearColor);
    }
}
