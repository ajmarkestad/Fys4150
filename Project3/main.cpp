#include <iostream>
#include <cmath>
#include <stdlib.h>
#include "ensemble.h"
#include "solver.h"
using namespace std;

int main(int numArguments, char **arguments)
{
    int numTimesteps = 1000;
    if(numArguments >= 2) numTimesteps = atoi(arguments[1]);

    Ensemble solarSystem;

    Particle &sun = solarSystem.createParticle( vec3(0,0,0), vec3(0,0,0), 1.0 );

    // We don't need to store the reference, but just call the function without a left hand side
    solarSystem.createParticle( vec3(1, 0, 0), vec3(0, 2*M_PI, 0), 3e-6 );

    // To get a list (a reference, not copy) of all the bodies in the solar system, we use the .bodies() function
    vector<Particle> &bodies = solarSystem.bodies();

    for(int i = 0; i<bodies.size(); i++) {
        Particle &body = bodies[i]; // Reference to this body
        cout << "The position of this object is " << body.position << " with velocity " << body.velocity << endl;
    }

    double dt = 0.001;
    Euler integrator(dt);

    //Precalculates to speed up the algorithm
    //solarSystem.preCalculate();

    for(int timestep=0; timestep<numTimesteps; timestep++) {
        integrator.integrateOneStep(solarSystem);
        solarSystem.writeToFile("positions.xyz");
    }


    cout << "The final positions are: " << endl;
    for(int i = 0; i<bodies.size(); i++) {
        Particle &body = bodies[i]; // Reference to this body
        cout << "The position of this object is " << body.position << " with velocity " << body.velocity << endl;
    }


     return 0;
}

