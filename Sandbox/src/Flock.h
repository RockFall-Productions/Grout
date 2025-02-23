#pragma once

#include "Boids.h"

#include <imgui.h>

#include <iostream>
#include <vector>

struct BoidSettings {
    // Settings
    float leaderSpeed = 7.0f;
    float leaderAttractionSpeed = 1;
    float leaderAttractionWeight = 1.9f;
    float leaderCloseRadius = 0.0f;

    float speedScaler = 1;
    float minSpeed = 4;
    float maxSpeed = 6;
    float perceptionRadius = 10.0f;
    float avoidanceRadius = 2.5f;
    float maxSteerForce = 0.4f;


    float alignWeight = 1.7f;
    float cohesionWeight = 2.2;
    float separationWeight = 3.0f;

    float targetWeight = 1;

    //LayerMask obstacleMask;
    float boundsRadius = .27f;
    float avoidCollisionWeight = 10;
    float collisionAvoidDst = 5;

    float borderRadius = 220.0f;
    float minHeight = 20.0f;
    float maxHeight = 170.0f;
};

/*
bool SliderFloatClamp(const char* label, float* v, float v_min, float v_max)
{
    float v_backup = *v;
    if (!ImGui::SliderFloat(label, v, v_min, v_max))
        return false;
    if (*v < v_min) *v = v_min;
    else if (*v > v_max) *v = v_max;
    return v_backup != *v;
}*/

// Keeps track of a union of boids
class Flock {
public:
    //Constructors
    Flock() {}

    void OnImGuiRender();

    //Read only and read/write methods.
    Boid& getBoid(int i);

    const BoidSettings& get_settings() { return settings; }

    // Mutator Functions
    void addBoid(glm::vec3 pos, bool leader = false);

    void removeBoid();

    void flocking();

    std::vector<Boid> flock;
    glm::vec3 flock_position = glm::vec3(0.0f);
private:
    BoidSettings settings = BoidSettings();
    float MAX_CENTER_DISTANCE = 50.0f;

    bool on_pause_ = false;
};
