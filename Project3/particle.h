#ifndef PARTICLE_H
#define PARTICLE_H

#include "vec3.h"

class Particle
{
public:
    vec3 position;
    vec3 velocity;
    vec3 force;
    double mass;
    double kineticEnergy;
    double potensialEnergy;

    Particle(vec3 position, vec3 velocity, double mass);
    Particle(double x, double y, double z, double vx, double vy, double vz, double mass);
    void resetForce();
};

#endif // PARTICLE_H
