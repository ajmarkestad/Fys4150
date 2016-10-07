#include "solver.h"
#include "ensemble.h"
#include <math.h>

Euler::Euler(double dt) :
    m_dt(dt)
{

}

void Euler::integrateOneStep(Ensemble &system)
{
    system.calculateForcesAndEnergy();

    for(Particle &body : system.bodies()) {
        body.position += body.velocity*m_dt;
        body.velocity += body.force / body.mass * m_dt;
    }
}

Verlet::Verlet(double dt){
    m_dt=dt;
    constant1 = pow(dt,2)/2;
    constant2 = dt/2;

}

void Verlet::integrateOneStep(Ensemble &system)
{
    system.calculateForcesAndEnergy();
    system.numberOfBodies();
    for(Particle &body : system.bodies()) {
        body.position += body.velocity*m_dt+constant1*body.force;
    }

    for(Particle &body : system.bodies()) {
        body.velocity += body.force / body.mass * m_dt;
    }
}

