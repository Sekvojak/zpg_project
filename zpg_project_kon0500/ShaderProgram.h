#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include "Shader.h"
#include "ICameraObserver.h"
#include "ILightObserver.h"
#include "LightManager.h"

class Camera;
class Light;

class ShaderProgram : public ICameraObserver, public ILightObserver {
private:
    GLuint shaderProgram;
    Camera* camera;
    LightManager* lightManager;

public:
    ShaderProgram(const Shader& vertex, const Shader& fragment);
    ~ShaderProgram();

    void setCamera(Camera* cam); // odkaz na kameru, ktorá shader pozoruje
    void onCameraChanged(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const glm::vec3& eye) override;

    void setLightManager(LightManager* lm);
    void onLightsChanged(const std::vector<Light*>& lights) override;

    void setUniform(const std::string& name, float value);
    void setUniform(const std::string& name, int value);
    void setUniform(const std::string& name, const glm::vec3& value);
    void setUniform(const std::string& name, const glm::mat4& value);

    void use();
};

