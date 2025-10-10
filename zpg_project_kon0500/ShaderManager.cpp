#include "ShaderManager.h"

void ShaderManager::createShaders(Camera* camera) {
    // ===== BASIC SHADER =====
    const char* vertexShaderBasic = R"(
            #version 330 core
            layout(location = 0) in vec3 position;
            layout(location = 1) in vec3 color;
            out vec3 vColor;
            uniform mat4 modelMatrix;
            uniform mat4 viewMatrix;
            uniform mat4 projectionMatrix;
            void main() {
                gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
                vColor = color;
            })";

    const char* fragmentShaderBasic = R"(
            #version 330 core
            in vec3 vColor;
            out vec4 fragColor;
            void main() {
                fragColor = vec4(vColor, 1.0);
            })";

    Shader vertexBasic(GL_VERTEX_SHADER, vertexShaderBasic);
    Shader fragmentBasic(GL_FRAGMENT_SHADER, fragmentShaderBasic);
    shaders["basic"] = new ShaderProgram(vertexBasic, fragmentBasic);

    // ===== TRIANGLE SHADER =====
    const char* vertexShaderTriangle = R"(
            #version 330 core
            layout(location = 0) in vec3 position;
            uniform mat4 modelMatrix;
            uniform mat4 viewMatrix;
            uniform mat4 projectionMatrix;
            out vec4 pos;
            void main() {
                gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
                pos = gl_Position;
            })";

    const char* fragmentShaderTriangle = R"(
            #version 330 core
            out vec4 fragColor;
            in vec4 pos;
            void main() {
                fragColor = vec4(0.7, 1.0, 0.5, 1.0);
            })";

    Shader vertexTriangle(GL_VERTEX_SHADER, vertexShaderTriangle);
    Shader fragmentTriangle(GL_FRAGMENT_SHADER, fragmentShaderTriangle);
    shaders["triangle"] = new ShaderProgram(vertexTriangle, fragmentTriangle);

    // ===== SPHERE SHADER =====
    const char* vertexShaderSphere = R"(
            #version 330 core
            layout(location = 0) in vec3 position;
            layout(location = 1) in vec3 normal;
            uniform mat4 modelMatrix;
            uniform mat4 viewMatrix;
            uniform mat4 projectionMatrix;
            out vec3 vNormal;
            void main() {
                gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
                vNormal = normal;
            })";

    const char* fragmentShaderSphere = R"(
            #version 330 core
            in vec3 vNormal;
            out vec4 fragColor;
            void main() {
                fragColor = vec4(normalize(vNormal) * 0.5 + 0.5, 1.0);
            })";

    Shader vertexSphere(GL_VERTEX_SHADER, vertexShaderSphere);
    Shader fragmentSphere(GL_FRAGMENT_SHADER, fragmentShaderSphere);
    shaders["sphere"] = new ShaderProgram(vertexSphere, fragmentSphere);

    // ===== PREPOJENIE S KAMEROU =====
    for (auto& pair : shaders) {
        pair.second->setCamera(camera);
    }
}

ShaderProgram* ShaderManager::get(const std::string& name) {
    if (shaders.find(name) != shaders.end()) {
        return shaders[name];
    }
    return nullptr;
}



void ShaderManager::cleanup() {
    for (auto& pair : shaders)
        delete pair.second;
    shaders.clear();
}

ShaderManager::~ShaderManager() {
    cleanup();
}