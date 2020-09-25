//
// Created by ron on 9/18/20.
//

#ifndef MYGLTUTORIAL_TEST_H
#define MYGLTUTORIAL_TEST_H

#include "../Renderer.h"
#include "../vendor/ImGUI/imgui.h"
#include <functional>

namespace test {
    class Test{
    public:
        Test(){}
        virtual ~Test() {}
        virtual void OnUpdate(float deltaTime) {}
        virtual void OnRender() {}
        virtual void OnImGuiRender() {}

    };
    class TestMenu : public Test {
    public:
        TestMenu(Test*& currentTestPointer);
        ~TestMenu();
        void OnImGuiRender() override;

        template<typename T>
        void RegisterTest(const std::string& name){
            std::cout << "Registering test " << name << std::endl;
            /*
             * inserts the constructor of whatever class is being passed in
             */
            m_Tests.push_back(std::make_pair(name, [](){return new T();}));
        }
    private:
        /*
         * Create a vector of pairs [test_name], [test_constructor]
         *  This way I can construct new test elements on the fly from the vector element,
         *      rather than pre-instantiate each test.
         */
        Test*& m_CurrentTest;
        std::vector<std::pair<std::string, std::function<Test *()>>> m_Tests;


    };
}


#endif //MYGLTUTORIAL_TEST_H
