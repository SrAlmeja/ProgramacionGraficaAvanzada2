#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>

class VBO
{
public:
    GLuint ID;

    // Constructor que genera un Elements Buffer Object y lo enlaza a los indices
    VBO(GLuint* indices, GLsizeiptr size);

    void Bind();
    void Unbind();
    void Delete();
};
#endif