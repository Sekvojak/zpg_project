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
    shaders["basic"] = new ShaderProgram(vertexBasic, fragmentBasic);   // toto by malo byt prazdne new ShaderProgram();

    // ===== CONSTANT SHADER =====

    Shader vertexConstant(GL_VERTEX_SHADER, std::string("constant.vert"));
    Shader fragmentConstant(GL_FRAGMENT_SHADER, std::string("constant.frag"));
    shaders["constant"] = new ShaderProgram(vertexConstant, fragmentConstant);

    // ===== LAMBERT SHADER =====

    Shader vertexLambert(GL_VERTEX_SHADER, std::string("lambert.vert"));
    Shader fragmentLambert(GL_FRAGMENT_SHADER, std::string("lambert.frag"));
    shaders["lambert"] = new ShaderProgram(vertexLambert, fragmentLambert);

    // ===== PHONG SHADER ====
    Shader vertexPhong(GL_VERTEX_SHADER, std::string("phong.vert"));
    Shader fragmentPhong(GL_FRAGMENT_SHADER, std::string("phong.frag"));
    shaders["phong"] = new ShaderProgram(vertexPhong, fragmentPhong);

    // ==== BLINN - PHONG SHADER ====
    Shader vertexBlinn(GL_VERTEX_SHADER, std::string("blinn.vert"));
    Shader fragmentBlinn(GL_FRAGMENT_SHADER, std::string("blinn.frag"));
    shaders["blinn"] = new ShaderProgram(vertexBlinn, fragmentBlinn);

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