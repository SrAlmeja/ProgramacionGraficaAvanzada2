#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"ShaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

#include<stb/stb_image.h>



//Se Define la version, se asignan las posiciones del atributo


int main()
{
    glfwInit();

    //Se dice la versión a usar de Open GL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Apuntador de tipo window para tener referencia de la ventana (Referencia)
    GLFWwindow* window = glfwCreateWindow(1000, 1000, "Window", NULL, NULL);


    double seconds = 1.0f;
    float scale, scale2;
    float sizePercent = 0.2f;
    float NormalScale = 1.0f;

    int widthTx, heightTx, numCol;
    GLuint texture;
    glGenTextures(1, &texture);


    glfwSetTime(0);

    GLfloat squareVertices[] =
    {
     -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
     -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
     0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
     0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f
    };


    GLuint squareIndices[] =
    {
     0, 2, 1,
     0, 3, 2
    };



    //Crear un contexto para openGL
    glfwMakeContextCurrent(window);
    //Agregando el color, Se definen los colores de la pantalla
    gladLoadGL();  //Carga las funciones en la libreria de glad

    //Se Crean los Shaders
    Shader shaderProgram("D1.vert", "D1.frag");

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(squareVertices, sizeof(squareVertices));
    EBO EBO1(squareIndices, sizeof(squareIndices));

    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");


    while (!glfwWindowShouldClose(window))
    {
        GLfloat time = glfwGetTime() * (18.9f * seconds);
        GLfloat time2 = glfwGetTime() * (20.0f * seconds);


        //Asignacion de buffer
        glClearColor(0.01f, 0.05f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        scale = sin(time) * sizePercent + NormalScale;

        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        scale2 = sin(time2) * sizePercent + NormalScale;


        shaderProgram.Activate();
        glUniform1f(uniID, scale2);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        std::cout << scale << std::endl;

        glfwSwapBuffers(window);

        glfwPollEvents();

    }
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();

    shaderProgram.Delete();


    glViewport(0, 0, 1000, 1000);
    glfwSwapBuffers(window);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}