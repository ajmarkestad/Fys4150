#include "solver.h"
#include "ensemble.h"

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


Verlet::Verlet(double dt) :
    m_dt(dt)
{

}

void Verlet::integrateOneStep(Ensemble &system)
{
    system.calculateForcesAndEnergy();

    for(Particle &body : system.bodies()) {
        //change this
        body.position += body.velocity*m_dt;
        body.velocity += body.force / body.mass * m_dt;
    }
}

