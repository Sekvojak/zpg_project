#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include "Shader.h"

class ShaderProgram {
private:
    GLuint shaderProgram;

public:
    ShaderProgram(const Shader& vertex, const Shader& fragment);
    ~ShaderProgram();

    void setUniform(const std::string& name, float value);
    void setUniform(const std::string& name, int value);
    void setUniform(const std::string& name, const glm::vec3& value);
    void setUniform(const std::string& name, const glm::mat4& value);

    void use();
};

