#pragma once
#include <glm/glm.hpp>
#include <vector>


class Light
{
private:
	glm::vec3 position;
	glm::vec3 lightColor;
	float constant;
	float linear;
	float quadratic;

public:
	Light(glm::vec3 pos, glm::vec3 color);
	Light(glm::vec3 pos, glm::vec3 color, float c, float l, float q);


	void setPosition(const glm::vec3& p);
	void setColor(const glm::vec3& c);


	const glm::vec3& getPosition() const { return position; }
	const glm::vec3& getColor() const { return lightColor; }
	float getConstant() const { return constant; }
	float getLinear() const { return linear; }
	float getQuadratic() const { return quadratic; }

	void setAttenuation(float c, float l, float q);


};

