#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>

#include "app/App.hpp"
#include "tower/tower.hpp"
#include "enemy/enemy.hpp"
#include "graph/graph.hpp"

#include "draw/draw.hpp"

namespace {
    App& window_as_app(GLFWwindow* window)
    {
        return *static_cast<App*>(glfwGetWindowUserPointer(window));
    }
}

// Optional: limit the frame rate
constexpr double TARGET_TIME_FOR_FRAME { 1.0 / 60.0 };

// Window properties
static const unsigned int WINDOW_WIDTH = 1280;
static const unsigned int WINDOW_HEIGHT = 720;
static const char WINDOW_TITLE[] = "Tower Defense";

// Initialisation de la liste d'adjacence et du graph de la map
std::vector<std::vector<float>> adjacency_matrix_map {} ;
Graph::WeightedGraph adjacency_list_map { Graph::adjacency_list_from_adjacency_matrix(adjacency_matrix_map) };

// Initialisation de la liste d'enemis et de tours
std::vector<enemy> enemies {};
std::vector<tower> towers {};

int main() {

    // Set an error callback to display glfw errors
    glfwSetErrorCallback([](int error, const char* description) {
        std::cerr << "Error " << error << ": " << description << std::endl;
    });

    // Initialize glfw
    if (!glfwInit()) {
        return -1;
    }

    // Create window
    GLFWwindow* window { glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL) };
    if (!window) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Intialize glad (loads the OpenGL functions)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize OpenGL context" << std::endl;
        glfwTerminate();
        return -1;
    }

    App app {};

    glfwSetWindowUserPointer(window, &app);

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        window_as_app(window).key_callback(key, scancode, action, mods);
    });
    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
        window_as_app(window).mouse_button_callback(window, button, action, mods);
    });
    glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
        window_as_app(window).scroll_callback(xoffset, yoffset);
    });
    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
        window_as_app(window).cursor_position_callback(xpos, ypos);
    });
    glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
        window_as_app(window).size_callback(width, height);
    });
    
    // Force calling the size_callback of the game to set the right viewport and projection matrix
    {
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        app.size_callback(width, height);
    }

    app.setup();

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {

        // Get time (in second) at loop beginning
		double startTime { glfwGetTime() };

        app.update();

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();

        // Optional: limit the frame rate
		double elapsedTime { glfwGetTime() - startTime };
        // wait the remaining time to match the target wanted frame rate
		if(elapsedTime < TARGET_TIME_FOR_FRAME)
		{
			glfwWaitEventsTimeout(TARGET_TIME_FOR_FRAME-elapsedTime);
		}
    }

    glfwTerminate();
    return 0;
}
