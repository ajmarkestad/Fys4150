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

void createparticles(Ensemble &system,int nargs, char **vargs, string input_file);

int main(int nargs, char **vargs)
{
    double years =10;
    int numTimesteps = 10000;
    if(nargs<5){
        cout << "Incorrect usage!" << endl;
        cout << "Usage:$ ./Project3 <input file name> <years> <numTimesteps> <planet1> <planet2> ..." << endl;
        cout << "For all bodies in initial_data.txt use <planet1> = 0" << endl;
        return 1;
    }
    if (vargs[2]<0){
        cout << "Negative years is not good!" << endl;
        return 1;
    }else{
        years = atof(vargs[2]);
    }
    if (vargs[3]<0){
        cout << "Negative timesteps is not good!" << endl;
        return 1;
    }else{
        numTimesteps = atoi(vargs[3]);
    }

    string input_file(vargs[1]);

    Ensemble solarSystem;
    createparticles(solarSystem, nargs, vargs, input_file);
    vector<Particle> &bodies = solarSystem.bodies();

    double dt = (double)years/(double)numTimesteps;

    //Euler integrator(dt);
    //Verlet integrator(dt,solarSystem);
    Verlet_GR integrator(dt,solarSystem);

    for(int timestep=0; timestep<numTimesteps; timestep++) {
        integrator.integrateOneStep(solarSystem);
        solarSystem.writeToFile("positions.txt");
    }


    cout << "The final positions are: " << endl;
    for(int i = 0; i<(int)bodies.size(); i++) {
        Particle &body = bodies[i]; // Reference to this body
        cout << "Final status for particle with position: " << body.position << "length: " << body.position.length() << " and velociy: " << body.velocity << " and mass: " << body.mass << endl;
         }



     return 0;


}


void createparticles(Ensemble &system, int nargs, char **vargs, string input_file){
    string line;
    ifstream myfile (input_file);
    if(myfile.is_open()){
        getline(myfile,line); //skips date
        getline(myfile,line); //skips headerline

        while (getline(myfile,line))
           {
            istringstream iss(line);
            string sub;
            iss >> sub;
            for(int i = 0; i<nargs-3; i++){
                if((atoi(sub.c_str())==atoi(vargs[i+3])) || ((nargs == 4) && atoi(vargs[3])==0)){
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
