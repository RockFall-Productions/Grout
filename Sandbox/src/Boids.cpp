#include <iostream>
#include <vector>
#include <string>
#include <math.h>

#include "Boids.h"

// Global Variables for borders()

#define BORDER_X 200.0f
#define BORDER_Y 60.0f
#define BORDER_Z 200.0f
#define PI 3.141592635

// =============================================== //
// ======== Boid Functions from Boid.h =========== //
// =============================================== //

Boid::Boid(glm::vec3 pos)
{
    acceleration = glm::vec3(0.0f);
    velocity = glm::vec3(rand() % 3 - 2, rand() % 3 - 2, rand() % 3 - 2);
    position = pos;
    maxSpeed = 3.5;
    maxForce = 0.5;
}
/*
Boid::Boid(float x, float y, bool predCheck)
{
    predator = predCheck;
    if (predCheck == true) {
        maxSpeed = 7.5;
        maxForce = 0.5;
        velocity = glm::vec3(rand() % 3 - 1, rand() % 3 - 1);
    }
    else {
        maxSpeed = 3.5;
        maxForce = 0.5;
        velocity = glm::vec3(rand() % 3 - 2, rand() % 3 - 2);
    }
    acceleration = glm::vec3(0, 0);
    position = glm::vec3(x, y);
}*/

// Adds force glm::vec3 to current force glm::vec3
void Boid::applyForce(const glm::vec3& force)
{
    acceleration += force;
}

// Separation
// Keeps boids from getting too close to one another
glm::vec3 Boid::Separation(const std::vector<Boid>& boids)
{
    // Distance of field of vision for separation between boids
    float desiredseparation = 20;
    glm::vec3 steer(0.0f);
    int count = 0;
    // For every boid in the system, check if it's too close
    for (int i = 0; i < boids.size(); i++) {
        // Calculate distance from current boid to boid we're looking at
        float d = glm::distance(position, boids[i].position);
        // If this is a fellow boid and it's too close, move away from it
        if ((d > 0) && (d < desiredseparation)) {
            glm::vec3 diff(0.0f);
            diff = position - boids[i].position;
            diff = glm::normalize(diff);
            diff = diff / d;      // Weight by distance
            steer += diff;
            count++;
        }
        /*
        // If current boid is a predator and the boid we're looking at is also
        // a predator, then separate only slightly
        if ((d > 0) && (d < desiredseparation) && predator == true
            && boids[i].predator == true) {
            glm::vec3 pred2pred(0, 0);
            pred2pred = pred2pred.subTwoVector(position, boids[i].position);
            pred2pred.normalize();
            pred2pred.divScalar(d);
            steer.addVector(pred2pred);
            count++;
        }
        // If current boid is not a predator, but the boid we're looking at is
        // a predator, then create a large separation glm::vec3
        else if ((d > 0) && (d < desiredseparation + 70) && boids[i].predator == true) {
            glm::vec3 pred(0, 0);
            pred = pred.subTwoVector(position, boids[i].position);
            pred.mulScalar(900);
            steer.addVector(pred);
            count++;
        }*/
    }

    // Adds average difference of position to acceleration
    if (count > 0)
        steer = steer / (float)count;
    if (sqrt(steer.x + steer.y + steer.z) > 0) {
        // Steering = Desired - Velocity
        steer = glm::normalize(steer);
        steer *= maxSpeed;
        steer -= velocity;
        if (sqrt(steer.x + steer.y + steer.z) > maxForce)
            steer /= sqrt(steer.x + steer.y + steer.z);
    }
    return steer;
}

// Alignment
// Calculates the average velocity of boids in the field of vision and
// manipulates the velocity of the current boid in order to match it
glm::vec3 Boid::Alignment(const std::vector<Boid>& Boid)
{
    float neighbordist = 50; // Field of vision

    glm::vec3 sum(0.0f);
    int count = 0;
    for (int i = 0; i < Boid.size(); i++) {
        float d = glm::distance(position, Boid[i].position);

        if ((d > 0) && (d < neighbordist)) { // 0 < d < 50
            sum += Boid[i].velocity;
            count++;
        }
    }
    // If there are boids close enough for alignment...
    if (count > 0) {
        // Divide sum by the number of close boids (average of velocity)
        sum /= (float)count;
        // Turn sum into a unit vector, and
        sum = glm::normalize(sum);
        // Multiply by maxSpeed
        sum *= maxSpeed;
        // Steer = Desired - Velocity
        glm::vec3 steer;
        //sum = desired(average)
        steer = sum - velocity;
        // steer.limit(maxForce);
        if (sqrt(steer.x + steer.y + steer.z) > maxForce)
            steer /= sqrt(steer.x + steer.y + steer.z);
        return steer;
    }
    else {
        return glm::vec3(0.0f);
    }
}

// Cohesion
// Finds the average position of nearby boids and manipulates the
// steering force to move in that direction.
glm::vec3 Boid::Cohesion(const std::vector<Boid>& Boid)
{
    float neighbordist = 50;
    glm::vec3 sum(0.0f);
    int count = 0;
    for (int i = 0; i < Boid.size(); i++) {
        float d = glm::distance(position, Boid[i].position);
        if ((d > 0) && (d < neighbordist)) {
            sum += Boid[i].position;
            count++;
        }
    }
    if (count > 0) {
        sum /= (float)count;
        return seek(sum);
    }
    else {
        return glm::vec3(0.0f);
    }
}

// Limits the maxSpeed, finds necessary steering force and
// normalizes vectors
glm::vec3 Boid::seek(const glm::vec3& v)
{
    glm::vec3 desired;
    // A vector pointing from the position to the target
    desired -= v;
    // Normalize desired and scale to maximum speed
    desired = glm::normalize(desired);
    desired *= maxSpeed;
    // Steering = Desired minus Velocity
    acceleration = desired - velocity;
    // Limit to maximum steering force
    if (sqrt(acceleration.x + acceleration.y + acceleration.z) > maxForce)
        acceleration /= sqrt(acceleration.x + acceleration.y + acceleration.z);
    return acceleration;
}

// Modifies velocity, position, and resets acceleration with values that
// are given by the three laws.
void Boid::update()
{
    //To make the slow down not as abrupt
    acceleration *= 0.4f;
    // Update velocity
    velocity += acceleration;
    // Limit speed
    if (sqrt(velocity.x + velocity.y + velocity.z) > maxForce)
        velocity /= sqrt(velocity.x + velocity.y + velocity.z);

    position += velocity;
    // Reset accelertion to 0 each cycle
    acceleration = glm::vec3(0.0f);
}

// Run flock() on the flock of boids.
// This applies the three rules, modifies velocities accordingly, updates data,
// and corrects boids which are sitting outside of the SFML window
void Boid::run(const std::vector <Boid>& v)
{
    flock(v);
    update();
    borders();
}

// Applies the three laws to the flock of boids
void Boid::flock(const std::vector<Boid>& v)
{
    glm::vec3 sep = Separation(v);
    glm::vec3 ali = Alignment(v);
    glm::vec3 coh = Cohesion(v);
    // Arbitrarily weight these forces
    sep *= 1.5f;
    ali *= 1.0f; // Might need to alter weights for different characteristics
    coh *= 1.0f;
    // Add the force vectors to acceleration
    applyForce(sep);
    applyForce(ali);
    applyForce(coh);
}

// Checks if boids go out of the window and if so, wraps them around to
// the other side.
void Boid::borders()
{
    if (position.x < -200.0f)   position.x += BORDER_X;
    if (position.x > 200.0f)    position.x -= BORDER_X;
    if (position.z < -200.0f)   position.z += BORDER_Z;
    if (position.z > 200.0f)    position.z -= BORDER_Z;
    if (position.y < 5.0f)      position.y += BORDER_Y;
    if (position.y > 80.0f)     position.y -= BORDER_Y;
}

// Calculates the angle for the velocity of a boid which allows the visual
// image to rotate in the direction that it is going in.
float Boid::angle(const glm::vec3& v)
{
    // From the definition of the dot product
    float angle = (float)(atan2(v.x, -v.y) * 180 / PI);
    return angle;
}