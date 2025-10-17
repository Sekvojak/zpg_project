#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include "Shader.h"
#include "ICameraObserver.h"
#include "ILightObserver.h"

class Camera;
class Light;

class ShaderProgram : public ICameraObserver, public ILightObserver {
private:
    GLuint shaderProgram;
    Camera* camera;
    Light* light;

public:
    ShaderProgram(const Shader& vertex, const Shader& fragment);
    ~ShaderProgram();

    void setCamera(Camera* cam); // odkaz na kameru, ktorá shader pozoruje
    void onCameraChanged(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const glm::vec3& eye) override;

    void setLight(Light* l);
    void onLightChanged(const glm::vec3& position, const glm::vec3& color) override;

    void setUniform(const std::string& name, float value);
    void setUniform(const std::string& name, int value);
    void setUniform(const std::string& name, const glm::vec3& value);
    void setUniform(const std::string& name, const glm::mat4& value);

    void use();
};

