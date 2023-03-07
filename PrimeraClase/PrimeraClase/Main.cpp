#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //apuntador de refrencia a la ventana que se usara en la gpu
    GLFWwindow* window = glfwCreateWindow(800, 800, "test", NULL, NULL);

    double seconds = 0.0f;
    float anim = 0.1f;
    glfwSetTime(0);

    GLfloat vertices[] =
    {
        0.5f, -0.5f * float(sqrt(3)) / 3 , 0.0f, 0.7804f, 0.5098f, 0.5137f, //esquina inferior izquierda
        -0.5f, -0.5f * float(sqrt(3)) / 3 , 0.0f, 0.9922f, 0.9922f, 0.5882f, //esquina inferior derecha
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3 , 0.0f, 0.3412f, 0.1373f, 0.3922f, //punta de la trifuerza
        0.5f / 2, 0.5f * float(sqrt(3)) / 6 , 0.0f, 1.0f, 1.0f, 1.0f, //esquina superior izquierda
        -0.5f / 2, 0.5f * float(sqrt(3)) / 6 , 0.0f, 0.4549f, 0.2588f, 0.3255f, //esquina superior derecha
        0.0f, -0.5f * float(sqrt(3)) / 3 , 0.0f, 0.9059f, 0.1137f, 0.2118f, //Base
    };

    GLuint indices[] =
    {
    0, 3, 5, // Triangulo inferior izq
    3, 2, 4, // Triangulo inferior der
    5, 4, 1, // Triangulo superior
    };

    glfwMakeContextCurrent(window);
    gladLoadGL();

    //se crean shaders

    Shader shaderProgram("examenOne.vert", "examenOne.frag");
    Shader shaderExam("examTwo.vert", "examTwo.frag");
    Shader shaderInside("inner.vert", "inner.frag");

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));

    EBO EBO1(indices, sizeof(indices));

    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");
    GLuint examID = glGetUniformLocation(shaderExam.ID, "scale");

    while (!glfwWindowShouldClose(window))
    {
        seconds = glfwGetTime();
        //std::cout << seconds << std::endl;
       
        if (seconds <= 1) anim++;

        if (seconds > 1) anim--;

        if (seconds >= 2) glfwSetTime(0);

        glClearColor(0.0f, 0.0f, 0.0f, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderExam.Activate();
        glUniform1f(examID, 0.5f);
        VAO1.Bind();

        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        shaderProgram.Activate();
        glUniform1f(uniID, 1.0f * (anim/25));

        std::cout << 1.0f * (anim / 25) << std::endl;

        VAO1.Bind();

        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();

    shaderProgram.Delete();
    shaderExam.Delete();

    glViewport(0, 0, 800, 800);
    glfwSwapBuffers(window);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}