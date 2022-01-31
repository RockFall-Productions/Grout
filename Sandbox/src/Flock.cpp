#include "Flock.h"


// =============================================== //
// ======== Flock Functions from Flock.h ========= //
// =============================================== //

int Flock::getSize()
{
    return flock.size();
}

//Read/write method that returns a reference of the Boid.
Boid& Flock::getBoid(int i)
{
    return flock[i];
}

void Flock::addBoid(glm::vec3 pos)
{
    flock.push_back(Boid(pos));
}

// Runs the run function for every boid in the flock checking against the flock
// itself. Which in turn applies all the rules to the flock.
void Flock::flocking()
{
    glm::vec3 sum_pos = glm::vec3(0.0f);
    for (int i = 0; i < flock.size(); i++) {
        flock[i].run(flock);
        sum_pos += flock[i].position;
    }

    flock_position = sum_pos / float(flock.size());
}