#include "shader.h"
#include <iostream>

// TODO: https://open.gl/drawing
// TODO: http://www.geeks3d.com/20111115/how-to-compute-the-position-in-a-vertex-shader-glsl-opengl-part-3/
// TODO: Rename to ShaderProgram

Shader::Shader(const std::string& vertex_shader_source, const std::string& fragment_shader_source)
    : handle(0)
    , linked(false)
{
    this->handle = glCreateProgram();
    GLuint foo = this->compileAndAttachShader(GL_VERTEX_SHADER, vertex_shader_source);
    GLuint bar = this->compileAndAttachShader(GL_FRAGMENT_SHADER, fragment_shader_source);
    this->link();

    // TODO
    glDetachShader(this->handle, foo);
    glDeleteShader(foo);

    glDetachShader(this->handle, bar);
    glDeleteShader(bar);
}

Shader::Shader(Shader const& /* other */)
{
    throw "Do not use this";
}

Shader::~Shader()
{
    this->unbind();
    if (this->handle)
        glDeleteProgram(this->handle);
}

void Shader::bind()
{
    // TODO: checks
    glUseProgram(this->handle);
}

void Shader::unbind()
{
    // TODO: checks
    glUseProgram(0);
}

GLuint Shader::compileAndAttachShader(GLuint shader_type, const std::string& source)
{
    GLuint shader = glCreateShader(shader_type);
    const char *c_str = source.c_str();
    glShaderSource(shader, 1, &c_str, NULL);
    glCompileShader(shader);

    GLint result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (result != GL_TRUE)
    {
        GLsizei log_length = 0;
        GLchar message[1024];
        glGetShaderInfoLog(shader, 1024, &log_length, message); // TODO: use sizeof() ?
        std::cerr << message << std::endl;
        throw "Compilation failed";
    }

    glAttachShader(this->handle, shader);

    return shader;
}

void Shader::link()
{
    glLinkProgram(this->handle);
    // TODO: Check for errors
}

GLint Shader::getAttribLocation(const std::string &name)
{
    // TODO: Raise exception if this fails!
    const char *c_str = name.c_str();
    return glGetAttribLocation(this->handle, c_str);
}

GLint Shader::getUniformLocation(const std::string &name)
{
    // TODO: Raise exception if this fails!
    const char *c_str = name.c_str();
    return glGetUniformLocation(this->handle, c_str);
}