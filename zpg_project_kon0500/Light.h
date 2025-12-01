#pragma once
#include <glm/glm.hpp>
#include <vector>

enum class LightType { 
	Point = 0, 
	Directional = 1, 
	Spot = 2 
};

class Light
{
private:
	glm::vec3 position{ 0.0f };
	glm::vec3 lightColor{ 1.0f };
	glm::vec3 direction{ 0.0f, -1.0f, 0.0f };

	float intensity{ 1.0f };

	float constant{ 1.0f };
	float linear{ 0.0f };
	float quadratic{ 0.0f };

	float cutOff{ 0.7f };
	LightType type{ LightType::Point };
	bool active{ true }; 

public:
	Light(glm::vec3 pos, glm::vec3 color);
	Light(glm::vec3 pos, glm::vec3 color, float c, float l, float q);
	Light(glm::vec3 vector, glm::vec3 color, LightType t);
	Light(glm::vec3 pos, glm::vec3 color, LightType t,
		float c, float l, float q, float cut);	// flashlight constructor

	void setIntensity(float i) { intensity = i; }
	float getIntensity() const { return intensity; }

	void setPosition(const glm::vec3& p);
	void setColor(const glm::vec3& c);
	void setDirection(const glm::vec3& d);
	void setAttenuation(float c, float l, float q);
	void setCutOff(float c);
	void setType(LightType t);
	void setActive(bool a);


	const glm::vec3& getPosition() const;
	const glm::vec3& getColor() const;
	const glm::vec3& getDirection() const;
	LightType getType() const;
	bool isActive() const;

	float getConstant() const;
	float getLinear() const;
	float getQuadratic() const;
	float getCutOff() const;



};

