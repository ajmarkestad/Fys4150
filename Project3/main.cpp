#include <iostream>
#include <cmath>
#include <stdlib.h>
#include "ensemble.h"
#include "solver.h"
#include <ostream>
#include <istream>
#include <fstream>
#include <sstream>
using namespace std;
ofstream ifile;
void createparticles(Ensemble &system,int nargs, char **vargs);

int main(int nargs, char **vargs)
{
    double years =10;
    int numTimesteps = 400000;
    if(nargs<2){
        cout << "Incorrect usage!" << endl;
        cout << "Usage:$ ./Project3 <numTimesteps> <years> <planet1> <planet2> ..." << endl;
        return 1;
    }
    if (vargs[1]<0){
        cout << "Negative years is not good!" << endl;
        return 1;
    }else{
        double years = *vargs[1];
    }
    if (vargs[2]<0){
        cout << "Negative timesteps is not good!" << endl;
        return 1;
    }else{
        double numTimesteps = *vargs[2];
    }

    Ensemble solarSystem;
    Particle &sun = solarSystem.createParticle( vec3(0.0,0.0,0.0), vec3(0.0,0.0,0.0), 1.0 );
    createparticles(solarSystem, nargs, vargs);

    vector<Particle> &bodies = solarSystem.bodies();

    for(int i = 0; i<bodies.size(); i++) {
        Particle &body = bodies[i]; // Reference to this body
        cout << "The position of this object is " << body.position << " with velocity " << body.velocity << endl;
    }

    double dt = (double)years/(double)numTimesteps;

    //Euler integrator(dt);
    Verlet integrator(dt,solarSystem);

    for(int timestep=0; timestep<numTimesteps; timestep++) {
        integrator.integrateOneStep(solarSystem);
        solarSystem.writeToFile("positions.xyz");
    }

    cout << "The final positions are: " << endl;
    for(int i = 0; i<bodies.size(); i++) {
        Particle &body = bodies[i]; // Reference to this body
        cout << "The position of this object is " << body.position << "with distance from sun" << body.position.length() << " with velocity " << body.velocity << endl;
    }


     return 0;
}


void createparticles(Ensemble &system, int nargs, char **vargs){
    ifile.open("initial_data.txt");

    for (int i=0; i<nargs-2; i++){


        solarSystem.createParticle( vec3(1.0, 0.0, 0.0), vec3(0.0, 2*M_PI, 0.0), 3e-6 );
    }
    ifile.close()

}
