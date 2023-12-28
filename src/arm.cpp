#include <iostream>
#include "../include/GLFW/glfw3.h"
#include "../include/imgui/backends/imgui.h"
#include "../include/imgui/backends/imgui_impl_glfw.h"
#include "../include/imgui/backends/imgui_impl_opengl2.h"
#include <stdlib.h>

#define WIDTH 400
#define HEIGHT 700

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

char *todoText;

int main()
{
    todoText = (char *) malloc(25);
    memset(todoText, '\0', 25);
    if (!glfwInit())
    {
        std::cout << "Failed to init glfw\n";
        return 0;
    }

    glfwSetErrorCallback(error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "armsim", 0, NULL);

    if (!window)
    {
        std::cout << "Failed to make a window\n";
        return 0;
    }

    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL2_Init();

    ImVec4 clear_color = ImVec4(0.28f, 0.28f, 0.28f, 1.00f);

    bool show_demo_window = true;
    bool show = true;
    bool completed = false;

    while (!glfwWindowShouldClose(window))
    {
        glfwSetKeyCallback(window, key_callback);

        glfwPollEvents();

        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        static int width, height;
        static float f = 0.0f;
        static int counter = 0;

        glfwGetWindowSize(window, &width, &height);

        ImGui::SetNextWindowSize(ImVec2(width, height));
        ImGui::SetNextWindowPos(ImVec2(0, 0));

        // Imgui
        if(show)
        {
            ImGui::Begin("ARM chip", &show);
            ImGui::Text("This is how arm chip works");


            if(completed)
            {
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(255,0,0,255));
                ImGui::Text(todoText);
                ImGui::PopStyleColor();
            }
            else
            {
                ImGui::Text(todoText);
            }

            ImGui::InputText("Enter a something", todoText, sizeof(todoText));

            ImGui::Checkbox("Done", &completed);

            if(ImGui::Button("Clear"))
            {
                memset(todoText, '\0', 25);
            }

            ImGui::SameLine();
            if(ImGui::Button("Click to close me"))
            {
                show = false;
            }

            ImGui::End();
        }

        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui::Render();
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
