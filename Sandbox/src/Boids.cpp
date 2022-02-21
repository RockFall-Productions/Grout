#include <iostream>
#include <vector>
#include <string>
#include <math.h>

#include <glm/gtx/vector_angle.hpp>

#include "Boids.h"
#include "Flock.h"

#include <Grout.h>

// Global Variables for borders()

#define BORDER_X 300.0f
#define BORDER_Y 60.0f
#define BORDER_Z 300.0f
#define PI 3.141592635

// =============================================== //
// ======== Boid Functions from Boid.h =========== //
// =============================================== //

Boid::Boid(glm::vec3 pos, BoidSettings& flock_settings, bool leader) : settings(flock_settings), leader(leader)
{
    position = pos;
    acceleration = glm::vec3(0.0f);

    if (leader) {
        velocity = glm::vec3(5.0f);
        return;
    }
    
    int gap = ceil(settings.maxSpeed) - settings.minSpeed;
    float random_x = float(rand() % (gap * 100)) / 100.0f;
    random_x += settings.minSpeed;
    float random_y = float(rand() % (gap * 100)) / 100.0f;
    random_y += settings.minSpeed;
    float random_z = float(rand() % (gap * 100)) / 100.0f;
    random_z += settings.minSpeed;
    velocity = glm::vec3(random_x, random_y, random_z);
    //velocity = glm::vec3(1.0f);
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
    float desiredseparation = settings.avoidanceRadius;
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
            //steer -= position - boids[i].position;
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
    
    //if (count > 0)
    //      steer = steer / (float)count;
    if (sqrt(steer.x + steer.y + steer.z) > 0) {
        // Steering = Desired - Velocity
        steer = glm::normalize(steer);
        steer *= settings.maxSpeed;
        steer -= velocity;
        if (sqrt(steer.x + steer.y + steer.z) > settings.maxSteerForce)
            steer /= sqrt(steer.x + steer.y + steer.z);
    }
    
    return steer;
}

// Alignment
// Calculates the average velocity of boids in the field of vision and
// manipulates the velocity of the current boid in order to match it
glm::vec3 Boid::Alignment(const std::vector<Boid>& Boid)
{
    float neighbordist = settings.perceptionRadius; // Field of vision

    glm::vec3 sum(0.0f);
    int count = 0;
    for (int i = 0; i < Boid.size(); i++) {
        float d = glm::distance(position, Boid[i].position);

        if ((d > 0) && (d < neighbordist)) { // 0 < d < 50
            sum += Boid[i].velocity;
            if (i == 0) {
                sum += Boid[i].velocity;
                sum += Boid[i].velocity;
                sum += Boid[i].velocity;
                sum += Boid[i].velocity;
                count += 4;
            }
            count++;
        }
    }
    // If there are boids close enough for alignment...
    
    if (count > 0) {

        
        // Divide sum by the number of close boids (average of velocity)
        sum /= (float)count;
        // Turn sum into a unit vector, and
        //sum = glm::normalize(sum);
        // Multiply by maxSpeed
        //sum *= settings.maxSpeed;
        // Steer = Desired - Velocity
        glm::vec3 steer;
        //sum = desired(average)
        steer = sum - velocity;
        // steer.limit(maxForce);
        if (sqrt(steer.x + steer.y + steer.z) > settings.maxSteerForce)
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
    float neighbordist = settings.perceptionRadius;;
    glm::vec3 sum(0.0f);
    int count = 0;
    for (int i = 0; i < Boid.size(); i++) {
        float d = glm::distance(position, Boid[i].position);

        float angle_to_flock = glm::degrees(glm::angle(glm::normalize(velocity), glm::normalize(Boid[i].position - position)));
        if ((d > 0) && (d < neighbordist) && angle_to_flock < 80) {
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
    glm::vec3 desired, steer;
    // A vector pointing from the position to the target
    desired = v - position;
    // Weighted by distance
    //desired *= glm::distance(v, position) / (100.0f);
    
    // Normalize desired and scale to maximum speed
    //desired = glm::normalize(desired);
    //desired *= settings.maxSpeed;
    
    // Steering = Desired minus Velocity
    steer = desired - velocity;
    // Limit to maximum steering force
    if (sqrt(steer.x + steer.y + steer.z) > settings.maxSteerForce)
        steer /= sqrt(steer.x + steer.y + steer.z);
    return steer / 400.0f;
}

glm::vec3 Boid::TowardLeader(const std::vector<Boid>& Boid)
{
    float distance_to_leader = glm::distance(Boid[0].position, position);

    if (distance_to_leader < settings.leaderCloseRadius) {
        return glm::vec3(0.0f);
    }

    glm::vec3 desired = Boid[0].position - position;
    // A vector pointing from the position to the target
    //desired -= Boid[0].position;
    //desired = glm::normalize(desired);
    //desired *= settings.leaderAttractionSpeed;
    glm::vec3 steer = desired - velocity;
    return steer * (settings.leaderAttractionWeight / 100.0f) * (1.0f / distance_to_leader);
}

glm::vec3 Boid::Collision(const std::vector<Boid>& boids) {
    // Distance of field of vision for separation between boids
    float desiredseparation = settings.avoidanceRadius;
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
            //steer -= position - boids[i].position;
            count++;
        }
    }

    // Adds average difference of position to acceleration

    //if (count > 0)
    //      steer = steer / (float)count;
    if (sqrt(steer.x + steer.y + steer.z) > 0) {
        // Steering = Desired - Velocity
        steer = glm::normalize(steer);
        steer *= settings.maxSpeed;
        steer -= velocity;
        if (sqrt(steer.x + steer.y + steer.z) > settings.maxSteerForce)
            steer /= sqrt(steer.x + steer.y + steer.z);
    }

    return steer;
}

// Modifies velocity, position, and resets acceleration with values that
// are given by the three laws.
void Boid::update()
{
    //To make the slow down not as abrupt
    acceleration *= 0.4f;
    // Update velocity
    velocity += acceleration;
    
    if (leader)
        position += velocity * Grout::Time::delta_time_f() * settings.speedScaler * (settings.leaderSpeed/10.0f);
    else {
        // Limit speed
        if (sqrt(velocity.x + velocity.y + velocity.z) > settings.maxSpeed)
            velocity /= sqrt(velocity.x + velocity.y + velocity.z);

        position += velocity * Grout::Time::delta_time_f() * settings.speedScaler;
    }
        
    // Reset accelertion to 0 each cycle
    acceleration = glm::vec3(0.0f);
}

// Run flock() on the flock of boids.
// This applies the three rules, modifies velocities accordingly, updates data,
// and corrects boids which are sitting outside of the SFML window
void Boid::run(const std::vector <Boid>& v)
{
    acceleration *= 0;

    if (!leader)
        flock(v);
    else
        leaderFlock(v);
    borders();
    update();
}

// Applies the three laws to the flock of boids
void Boid::flock(const std::vector<Boid>& v)
{
    glm::vec3 sep = Separation(v);
    glm::vec3 ali = Alignment(v);
    glm::vec3 coh = Cohesion(v);
    glm::vec3 tlead = glm::vec3(0.0f);
    if (v[0].leader)
        tlead = TowardLeader(v);
    glm::vec3 col = Collision(v);
    // Arbitrarily weight these forces
    sep *= settings.separationWeight;
    ali *= settings.alignWeight; // Might need to alter weights for different characteristics
    coh *= settings.cohesionWeight;
    tlead *= settings.leaderAttractionWeight;
    col *= 10.0f;
    // Add the force vectors to acceleration
    applyForce(sep);
    applyForce(ali);
    applyForce(coh);
    applyForce(tlead);
    applyForce(col);
}

// Applies the three laws to the flock of boids
void Boid::leaderFlock(const std::vector<Boid>& v) {
    // TODO: Change slightly and randomly the direction
}

// Limits the movement of boids on borders
void Boid::borders()
{
    /*
    if (position.x < -settings.borderRadius) {
        glm::vec3 normal = glm::vec3(-settings.borderRadius, position.y, position.z) - position;
        normal = glm::normalize(normal);
        acceleration.x = (velocity - ((2 * (glm::dot(velocity, normal)) ) * normal)).x;
    }
    else if (position.x > settings.borderRadius) {
        glm::vec3 normal = glm::vec3(settings.borderRadius, position.y, position.z) - position;
        normal = glm::normalize(normal);
        acceleration.x = (velocity - ((2 * (glm::dot(velocity, normal))) * normal)).x;
    }

    if (position.z < -settings.borderRadius) {
        glm::vec3 normal = glm::vec3(position.x, position.y ,-settings.borderRadius) - position;
        normal = glm::normalize(normal);
        acceleration.z = (velocity - ((2 * (glm::dot(velocity, normal))) * normal)).z;
    }
    else if (position.z > settings.borderRadius) {
        glm::vec3 normal = glm::vec3(position.x, position.y, settings.borderRadius) - position;
        normal = glm::normalize(normal);
        acceleration.z = (velocity - ((2 * (glm::dot(velocity, normal))) * normal)).z;
    }

    if (position.y < settings.minHeight) {
        glm::vec3 normal = glm::vec3(position.x, settings.minHeight, position.z) - position;
        normal = glm::normalize(normal);
        acceleration.y = (velocity - ((2 * (glm::dot(velocity, normal))) * normal)).y;
    }
    else if (position.y > settings.maxHeight) {
        glm::vec3 normal = glm::vec3(position.x, settings.maxHeight, position.z) - position;
        normal = glm::normalize(normal);
        acceleration.y = (velocity - ((2 * (glm::dot(velocity, normal))) * normal)).y;
    }*/

    if (position.x < -settings.borderRadius) {
        acceleration.x = (-settings.borderRadius) - position.x;
    }
    else if (position.x > settings.borderRadius) {
        acceleration.x = settings.borderRadius - position.x;
    }

    if (position.z < -settings.borderRadius) {
        acceleration.z = (-settings.borderRadius) - position.z;
    }
    else if (position.z > settings.borderRadius) {
        acceleration.z = settings.borderRadius - position.z;
    }

    if (position.y < settings.minHeight) {
        acceleration.y = settings.minHeight - position.y;
    }
    else if (position.y > settings.maxHeight) {
        acceleration.y = settings.maxHeight - position.y;
    }
}

// Calculates the angle for the velocity of a boid which allows the visual
// image to rotate in the direction that it is going in.
float Boid::angle(const glm::vec3& v)
{
    // From the definition of the dot product
    float angle = (float)(atan2(v.x, -v.y) * 180.0f / PI);
    return angle;
}