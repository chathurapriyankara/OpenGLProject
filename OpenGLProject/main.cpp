#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

int main() {
    //INIT GLFW
    glfwInit();
    
    //CREATE WINDOW
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
    
    glfwGetFramebufferSize(window, 0, 0);
    glViewport(0, 0, 0, 0); //Canvas
    glfwMakeContextCurrent(window);
    
    //INIT GLEW
    glewExperimental = GL_TRUE;
    
    if(glewInit() != GLEW_OK) {
        std::cout<<"ERROR::MAIN.CPP::GLEW_INIT_FAILED"<<"\n";
        glfwTerminate();
    }
    
    //MAIN LOOP
    while(!glfwWindowShouldClose(window)) {
        //UPDATE INPUT
        glfwPollEvents();
        
        //CLEAR
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        
        //END DRAW
        glfwSwapBuffers(window);
        glFlush();
    }
    glfwTerminate();
    return 0;
}
