#pragma once
#include <GL/glew.h>
#include "Model.h"
#include "ShaderProgram.h"
#include "AbstractTransformation.h"
#include "Light.h"
#include "Material.h"
#include "Texture.h"

// AbstractTransformation premenovat na TransformComponent?

class DrawableObject {
public:
    ~DrawableObject();
    DrawableObject(Model* model, ShaderProgram* shader, AbstractTransformation* transformation = nullptr);
    void draw();
    AbstractTransformation* getTransformation();
    void setColor(const glm::vec3& color);

    void linkLight(Light* light) { linkedLight = light; }
    Light* getLinkedLight() const { return linkedLight; }
    void setMaterial(const Material& m) { material = m; }
    void setTexture(Texture* tex);

    void setID(int newID) { this->objectID = newID; }
    int getID() const { return objectID; }

    void setSelected(bool value) { selected = value; }

    void addOffset(const glm::vec3& delta) { moveOffset += delta; }
private:
    int objectID = 0;
    bool selected = false;
    Model* model;
    ShaderProgram* shader;
    AbstractTransformation* transformation;
    glm::vec3 objectColor = glm::vec3(1.0f);
    Light* linkedLight = nullptr;
    Material material{};

    glm::vec3 moveOffset = glm::vec3(0.0f);
};
