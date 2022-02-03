#pragma once

#include <glm/glm.hpp>

#include <vector>
#include <stdlib.h>
#include <iostream>


// The Boid Class
//
// Attributes
//  bool predator: flag that specifies whether a given boid is a predator.
//  glm::vec3 position: Vector that specifies a boid's position.
//  glm::vec3 velocity: Vector that specifies a boid's current velocity.
//  glm::vec3 acceleration: Vector that specifies a boid's current acceleration.
//  float maxSpeed: Limits magnitude of velocity vector.
//  float maxForce: Limits magnitude of acceleration vector. (F = m*a!)
//
// Methods
//  applyForce(glm::vec3 force): Adds the given vector to acceleration
//
//  glm::vec3 Separation(vector<Boid> Boid): If any other boids are within a
//      given distance, Separation computes a a vector that distances the
//      current boid from the boids that are too close.
//
//  glm::vec3 Alignment(vector<Boid> Boid): Computes a vector that causes the
//      velocity of the current boid to match that of boids that are nearby.
//
//  glm::vec3 Cohesion(vector<Boid> Boid): Computes a vector that causes the
//      current boid to seek the center of mass of nearby boids.

struct BoidSettings;

class Boid {
public:
    bool predator = false;
    bool leader = false;
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;

    BoidSettings& settings;

    Boid(glm::vec3 pos, BoidSettings& flock_settings, bool leader = false);
    //Boid(float x, float y, bool predCheck);
    void applyForce(const glm::vec3& force);
    // Three Laws that boids follow
    glm::vec3 Separation(const std::vector<Boid>& Boid);
    glm::vec3 Alignment(const std::vector<Boid>& Boid);
    glm::vec3 Cohesion(const std::vector<Boid>& Boid);
    glm::vec3 TowardLeader(const std::vector<Boid>& Boid);
    //Functions involving SFML and visualisation linking
    glm::vec3 seek(const glm::vec3& v);
    void run(const std::vector<Boid>& v);
    void update();
    void flock(const std::vector<Boid>& v);
    void leaderFlock(const std::vector<Boid>& v);
    void borders();
    float angle(const glm::vec3& v);
};

