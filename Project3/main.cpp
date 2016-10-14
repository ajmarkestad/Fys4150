#include <iostream>
#include <cmath>
#include <stdlib.h>
#include "ensemble.h"
#include "solver.h"
#include <ostream>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;
ofstream ifile;
void createparticles(Ensemble &system,int nargs, char **vargs);

int main(int nargs, char **vargs)
{
    double years =10;
    int numTimesteps = 10000;
    if(nargs<2){
        cout << "Incorrect usage!" << endl;
        cout << "Usage:$ ./Project3 <numTimesteps> <years> <planet1> <planet2> ..." << endl;
        return 1;
    }
    if (vargs[1]<0){
        cout << "Negative years is not good!" << endl;
        return 1;
    }else{
        years = atof(vargs[1]);
    }
    if (vargs[2]<0){
        cout << "Negative timesteps is not good!" << endl;
        return 1;
    }else{
        numTimesteps = atoi(vargs[2]);
    }

    Ensemble solarSystem;
    createparticles(solarSystem, nargs, vargs);
    vector<Particle> &bodies = solarSystem.bodies();

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
        cout << "Final status for particle with position: " << body.position << "length: " << body.position.length() << " and velociy: " << body.velocity << " and mass: " << body.mass << endl;
         }



     return 0;


}


void createparticles(Ensemble &system, int nargs, char **vargs){
    string line;
    ifstream myfile ("initial_data.txt");
    if(myfile.is_open()){
        getline(myfile,line); //skips date
        getline(myfile,line); //skips headerline

        while (getline(myfile,line))
           {
            istringstream iss(line);
            string sub;
            iss >> sub;
            for(int i = 0; i<nargs-3; i++){
                if(atoi(sub.c_str())==atoi(vargs[i+3])){
                    vec3 position(0,0,0);
                    vec3 velocity(0,0,0);
                    iss >> sub;
                    position(0)=atof(sub.c_str());
                    iss >> sub;
                    position(1)=atof(sub.c_str());
                    iss >> sub;
                    position(2)=atof(sub.c_str());
                    iss >> sub;
                    velocity(0)=atof(sub.c_str())*365;
                    iss >> sub;
                    velocity(1)=atof(sub.c_str())*365;
                    iss >> sub;
                    velocity(2)=atof(sub.c_str())*365;
                    iss >> sub;
                    system.createParticle( position, velocity, atof(sub.c_str()));
                    cout << "Created a particle with initial position: " << position << "length: " << position.length() << " and velociy: " << velocity << " and mass: " << atof(sub.c_str()) << endl;
                }
            }
           }
        myfile.close();
    }else{
        cout << "Unable to open file" << endl;
    }
}
