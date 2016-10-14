#include "solver.h"
#include "ensemble.h"
#include <math.h>
#include "vec3.h"
#include <armadillo>
#include <iostream>

Euler::Euler(double dt){
    m_dt=dt;
}

void Euler::integrateOneStep(Ensemble &system)
{
    system.calculateForcesAndEnergy();

    for(Particle &body : system.bodies()) {
        body.position += body.velocity*m_dt;
        body.velocity += body.force*(m_dt / body.mass);
    }
}

Verlet::Verlet(double dt,Ensemble &system){
    m_dt=dt;
    constant1 = pow(dt,2)/2;
    constant2 = dt/2;
    force = arma::zeros(system.numberOfBodies(),3);
    system.calculateForcesAndEnergy();
}

void Verlet::integrateOneStep(Ensemble &system)
{
    int i=0;
    for(Particle &body : system.bodies()) {
        body.position += body.velocity*m_dt+body.force*constant1;
        force(i,0)=body.force(0);
        force(i,1)=body.force(1);
        force(i,2)=body.force(2);
        i++;
    }
    system.calculateForcesAndEnergy();
    i=0;
    for(Particle &body : system.bodies()) {
        body.velocity += constant2*(body.force+vec3(force(i,0),force(i,1),force(i,2)))/body.mass;
        i++;
    }
}

