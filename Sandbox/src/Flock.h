#pragma once

#include <iostream>
#include <vector>

#include "Boids.h"



// Brief description of Flock Class:
// This file contains the class needed to create a flock of boids. It utilizes
// the boids class and initializes boid flocks with parameters that can be
// specified. This class will be utilized in main.

class Flock {
public:
    //Constructors
    Flock() {}

    // Accessor functions
    int getSize();
    //Read only and read/write methods.
    Boid& getBoid(int i);
    // Mutator Functions
    void addBoid(glm::vec3 pos);
    void flocking();
    std::vector<Boid> flock;
    glm::vec3 flock_position;
private:
};
