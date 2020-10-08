#pragma once 

#include "../Renderer/VkIncludes.h"


struct Point_light{
    glm::vec4 position;

    glm::vec4 ambient;
    glm::vec4 diffuse;
    glm::vec4 specular;
    glm::vec4 light_color;

    glm::vec4 visible; 

    glm::vec4 radius;
};

struct Spot_light {
    glm::vec4 position;
    glm::vec4 direction;
    glm::vec4 cutOff;
    glm::vec4 outerCutOff;

    glm::vec4 radius;

    glm::vec4 ambient;
    glm::vec4 diffuse;
    glm::vec4 specular;  
    glm::vec4 light_color;   

    glm::vec4 visible {false};   
};

struct Directional_light {
    glm::vec4 direction;
	
    glm::vec4 ambient;
    glm::vec4 diffuse;
    glm::vec4 specular;
    glm::vec4 light_color;

    glm::vec4 visible {false}; 
};