#include"VAO.h"

// Constructor que genera un VAO ID
VAO::VAO()
{
    glGenVertexArrays(1, &ID);
}

// Enlaza un VBO a VAO mediante layouts
void VAO::LinkVBO(VBO& VBO, GLuint layout)
{
    VBO.Bind();
    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(layout);
    VBO.Unbind();
}

void VAO::Bind()
{
    glBindVertexArray(ID);
}

void VAO::Unbind()
{
    glBindVertexArray(0);
}

void VAO::Delete()
{
    glDeleteVertexArrays(1, &ID);
}