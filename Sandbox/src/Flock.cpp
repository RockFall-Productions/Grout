#include "Flock.h"

#include <Grout.h>

// =============================================== //
// ======== Flock Functions from Flock.h ========= //
// =============================================== //

void Flock::OnImGuiRender()
{
    ImGui::Text("Boid Settings");
    ImGui::Checkbox("Pausar", &on_pause_);

    if (on_pause_) {
         ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Press the Middle Mouse Button to jump a frame");
    }

    ImGui::Text("Flock Position: %.1f %.1f %.1f", flock_position.x, flock_position.y, flock_position.z);
    ImGui::SliderFloat("Leader Speed", &settings.leaderSpeed, 0.0f, 15.0f);
    ImGui::SliderFloat("Leader Attraction Speed", &settings.leaderAttractionSpeed, 0.0f, 100.0f);
    ImGui::SliderFloat("Leader Attraction Weight", &settings.leaderAttractionWeight, 0.0f, 10.0f);
    ImGui::SliderFloat("Leader Close Radius", &settings.leaderCloseRadius, 0.0f, 50.0f);
    ImGui::Spacing();
    //ImGui::SliderFloat("Min Speed", &settings.minSpeed, 0.0f, 100.0f);
    ImGui::SliderFloat("Max Speed", &settings.maxSpeed, 0.0f, 100.0f);
    if (settings.minSpeed > settings.maxSpeed)
        settings.minSpeed = settings.maxSpeed;
    ImGui::SliderFloat("General Speed Scaler", &settings.speedScaler, 0.0f, 30.0f);
    ImGui::Spacing();
    ImGui::SliderFloat("Perception Radius", &settings.perceptionRadius, 0.0f, 10.0f);
    ImGui::SliderFloat("Avoidance Radius", &settings.avoidanceRadius, 0.0f, 10.0f);
    ImGui::Spacing();
    ImGui::SliderFloat("Max Steer Force", &settings.maxSteerForce, 0.0f, 50.0f);
    ImGui::Spacing();
    ImGui::SliderFloat("Align Weight", &settings.alignWeight, 0.0f, 10.0f);
    ImGui::SliderFloat("Cohesion Weight", &settings.cohesionWeight, 0.0f, 10.0f);
    ImGui::SliderFloat("Separation Weight", &settings.separationWeight, 0.0f, 10.0f);
    //ImGui::SliderFloat("Target Weight", &settings.targetWeight, 0.0f, 10.0f);
    ImGui::Spacing();
    //ImGui::SliderFloat("Bounds Radius", &settings.boundsRadius, 0.0f, 2.0f);
    //ImGui::SliderFloat("Avoid Collision Weight", &settings.avoidCollisionWeight, 0.0f, 100.0f);
    //ImGui::SliderFloat("Collision Avoid Distance", &settings.collisionAvoidDst, 0.0f, 20.0f);
    ImGui::Spacing();
    ImGui::SliderFloat("Border Radius", &settings.borderRadius, 1.0f, 500.0f);
    ImGui::SliderFloat("Min Height", &settings.minHeight, 0.0f, 80.0f);
    ImGui::SliderFloat("Max Height", &settings.maxHeight, 0.0f, 80.0f);
    if (settings.minHeight > settings.maxHeight)
        settings.minHeight = settings.maxHeight;
    ImGui::Spacing();
}

//Read/write method that returns a reference of the Boid.
Boid& Flock::getBoid(int i)
{
    return flock[i];
}

void Flock::addBoid(glm::vec3 pos, bool leader)
{
    flock.push_back(Boid(pos, settings, leader));
}

void Flock::removeBoid()
{
    flock.pop_back();
}

// Runs the run function for every boid in the flock checking against the flock
// itself. Which in turn applies all the rules to the flock.
void Flock::flocking()
{
    if (on_pause_) {
        if (!Grout::Input::is_mouse_button_pressed(GRT_MOUSE_BUTTON_MIDDLE))
            return;
    }

    glm::vec3 sum_pos = glm::vec3(0.0f);
    for (int i = 0; i < flock.size(); i++) {
        flock[i].run(flock);
        
        if (glm::distance(flock[i].position, flock_position) < MAX_CENTER_DISTANCE){
            sum_pos += flock[i].position;
        }
    }

    flock_position = sum_pos / float(flock.size());
}