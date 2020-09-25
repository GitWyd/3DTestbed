//
// Created by ron on 9/18/20.
//

#include "../../include/tests/Test.h"
namespace test{

    TestMenu::TestMenu(Test *&currentTestPointer): m_CurrentTest(currentTestPointer) {}

    TestMenu::~TestMenu() {

    }

    void TestMenu::OnImGuiRender() {
        for (auto& t: m_Tests){
            if (ImGui::Button(t.first.c_str())) {
                m_CurrentTest = t.second();
            }
        }
        Test::OnImGuiRender();
    }
}