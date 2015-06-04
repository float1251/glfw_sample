#include <GLFW/glfw3.h>
#include <OpenGL/gl.h>
#include <stdio.h>

int main(){
    printf("hello world\n");
    GLFWwindow* window;

    if(!glfwInit())
    {
        return -1;
    }

    // http://stackoverflow.com/questions/19658745/why-is-my-opengl-version-always-2-1-on-mac-os-x
    // これを入れると4.1になる
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

    if(!window)
    {
        glfwTerminate();
        return -1;
    }

    printf("%s", glGetString(GL_VERSION));
    glfwSwapInterval(2);
    
    glfwMakeContextCurrent(window);

    while(!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
