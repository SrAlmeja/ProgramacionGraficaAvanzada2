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
    GLFWwindow* window = glfwCreateWindow(950, 950, "test", NULL, NULL);

    double seconds = 1.0f;
    float scale;
    float scalePercent = 0.2f;
    float scaleGoal = 1.0f;

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
        GLfloat time = glfwGetTime() * seconds;

        glClearColor(0.0f, 0.0f, 0.0f, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderExam.Activate();
        glUniform1f(examID, 0.5f);
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        scale = sin(time) * scalePercent + scaleGoal;

        shaderProgram.Activate();
        glUniform1f(uniID, scale);
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        std::cout << scale << std::endl;

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();

    shaderProgram.Delete();
    shaderExam.Delete();

    glViewport(0, 0, 950, 950);
    glfwSwapBuffers(window);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}