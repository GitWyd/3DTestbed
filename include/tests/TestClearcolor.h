//
// Created by ron on 9/18/20.
//

#ifndef MYGLTUTORIAL_TESTCLEARCOLOR_H
#define MYGLTUTORIAL_TESTCLEARCOLOR_H
#include "Test.h"
#include "../Renderer.h"
#include "../../include/vendor/ImGUI/imgui.h"

namespace test {
    class TestClearColor: public Test {
    public:
        TestClearColor();
        ~TestClearColor();
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
    private:
        float m_ClearColor[4];
    };

}
#endif //MYGLTUTORIAL_TESTCLEARCOLOR_H
