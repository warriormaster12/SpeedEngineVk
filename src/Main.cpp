#include "Engine/ApplicationLoop.h"


Application application;

void cursor_enter_callback(GLFWwindow* window, int entered);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void run()
{
    application.InitApplication();  
    glfwSetCursorEnterCallback(application.win.window, cursor_enter_callback);
    glfwSetCursorPosCallback(application.win.window, mouse_callback);
    application.UpdateApplication();
}

int main()
{
    run();
}
    
void cursor_enter_callback(GLFWwindow* window, int entered) {
    application.cursor_enter_callback(window, entered);
}   

 
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    application.mouse_callback(window, xpos, ypos);
}

