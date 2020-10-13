/*
 * Titel: MyGLTutorial
 * Description: OpenGL visualization approach for Titan Simulator including instanced drawing of masses
 * Author: Philippe Wyder (philippe.wyder@columbia.edu)
 * Sources: https://www.glfw.org/documentation.html
 */
// library inclusions
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// header inclusions
#include "../include/Renderer.h"
#include "../include/VertexBuffer.h"
#include "../include/IndexBuffer.h"
#include "../include/VertexArray.h"
#include "../include/Shader.h"
#include "../include/Texture.h"
#include "../include/vendor/ImGUI/imgui.h"
#include "../include/vendor/ImGUI/imgui_impl_glfw.h"
#include "../include/vendor/ImGUI/imgui_impl_opengl3.h"

// include tests
#include "../include/tests/TestClearcolor.h"
#include "../include/tests/TestTexture2D.h"
#include "../include/tests/Test3DScene.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current (THIS MUST HAPPEN BEFORE GLEWINIT) */
    glfwMakeContextCurrent(window);

    /* synchronize swap interval with our screen update rate */
    glfwSwapInterval(1);

    /* Initialize GLEW Rendering Context */
    GLenum err = glewInit();
    if(GLEW_OK != err){
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    fprintf(stdout, "Status: Using OpenGL %s\n", glGetString(GL_VERSION));

    // During init, enable debug output
    glEnable              ( GL_DEBUG_OUTPUT );
    glDebugMessageCallback( MessageCallback, 0 );

    { /* Separate context to ensure destruction of objects before program ends */
        /*
         * Initialize OpenGL
         */
        glShadeModel(GL_SMOOTH);

        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
        glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

        glEnable(GL_DEPTH_TEST);
        glDepthRange(0.1,1.0);
        glEnable(GL_LIGHTING);
        //glEnable(GL_CULL_FACE);
        //glCullFace(GL_BACK);
        //glClearStencil(0);
        glClearDepth(1.0f);
        glDepthFunc(GL_LEQUAL);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        /*
         * Init Lights
         */
        /*
        // set up light colors (ambient, diffuse, specular)
        GLfloat lightKa[] = {.3f, .3f, .3f, 1.0f};  // ambient light
        GLfloat lightKd[] = {.7f, .7f, .7f, 1.0f};  // diffuse light
        GLfloat lightKs[] = {1, 1, 1, 1};           // specular light
        glLightfv(GL_LIGHT0, GL_AMBIENT, lightKa);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightKd);
        glLightfv(GL_LIGHT0, GL_SPECULAR, lightKs);
         */
        // position the light
        float lightPos[4] = {0, 0, 1, 0}; // directional light
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

        glEnable(GL_LIGHT0);                        // MUST enable each light source after configuration

        /*
         * Camera Settings
         */
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();


        /*
         * enable blending so alpha overlays are rendered properly
         */
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        Renderer renderer;

        /* use imGUI to make a user interface
         */
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        const char* glsl_version = "#version 130";
        ImGui_ImplOpenGL3_Init(glsl_version);

        /*
         * Run Test
         */
        test::Test * currentTest = nullptr;
        test::TestMenu * menu = new test::TestMenu(currentTest); // heap allocation
        currentTest = menu; // start off with the menu as the test to be run
        /** Populate Testt Menu */
        menu->RegisterTest<test::Test3DScene>("3D Scene");
        //menu->RegisterTest<test::TestClearColor>("Clear Color");
        //menu->RegisterTest<test::TestTexture2D>("Texture 2D");
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            /*
             * imGUI start new frame
             * */
            //New Frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            /**
             * Run Test in Window
             */
            if (currentTest){
                currentTest->OnUpdate(0.0f);
                currentTest->OnRender();
                ImGui::Begin("Test");
                if (currentTest != menu && ImGui::Button("<-")){
                    //delete currentTest; // clean up memory
                    currentTest = menu;
                }
                currentTest->OnImGuiRender();
                ImGui::End();
            }



            /*
             * imGUI render GUI
             * */
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
        delete currentTest;
        if (currentTest != menu){
            delete menu;
        }
    }
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}