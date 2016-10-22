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
    double years;
    int numTimesteps;
    if(nargs<7){
        cout << "Incorrect usage!" << endl;
        cout << "Usage:$ ./Project3 <Choose method> <input file name> <output file name> <years> <numTimesteps> <planet1> <planet2> ..." << endl;
        cout << "Choose method: 0 for Euler, 1 for Verlet, 2 for Verlet with GR corrections" << endl;
        cout << "3 for Energies using Euler, and 4 for energies using Verlet" << endl;
        cout << "For all bodies in initial_data.txt use <planet1> = 0" << endl;
        return 1;
    }
    if (vargs[4]<0){
        cout << "Negative years is not good!" << endl;
        return 1;
    }else{
        years = atof(vargs[4]);
    }
    if (vargs[5]<0){
        cout << "Negative timesteps is not good!" << endl;
        return 1;
    }else{
        numTimesteps = atoi(vargs[5]);
    }

    string input_file(vargs[2]);
    string output_file(vargs[3]);

    Ensemble solarSystem;
    createparticles(solarSystem, nargs, vargs, input_file);
    vector<Particle> &bodies = solarSystem.bodies();

    double dt = (double)years/(double)numTimesteps;

    if (atoi(vargs[1]) == 0){
        Euler integrator(dt);
        for(int timestep=0; timestep<numTimesteps; timestep++) {
            integrator.integrateOneStep(solarSystem);
            solarSystem.writeToFile(output_file);
        }
    }else if(atoi(vargs[1]) == 1){
        Verlet integrator(dt,solarSystem);
        for(int timestep=0; timestep<numTimesteps; timestep++) {
            integrator.integrateOneStep(solarSystem);
            solarSystem.writeToFile(output_file);
        }
    }else if (atoi(vargs[1]) == 2){
        // Set some helper variables before we start the time integration.
        double rPreviousPrevious = 0;	// Mercury-Sun-distance two times steps ago.
        double rPrevious = 0;	// Mercury-Sun-distance of the previous time step.
        double angle = 0;

        vec3   previousPosition(0,0,0);		// Mercury-Sun position vector of the previous time step.
        Verlet_GR integrator(dt, solarSystem);
        // This is the integration loop, in which you advance the solution (usually via a integrateOneStep()
        // function located in an integrator object, e.g. the Verlet class).
        for (int timeStep = 0; timeStep < numTimesteps; timeStep++) {

            // Integrate the solution one step forward in time, using the GR corrected force calcuation
            // and the Verlet algorithm.
            integrator.integrateOneStep(solarSystem);

            // Compute the current Mercury-Sun distance. This assumes there is a vector of planets,
            // called m_bodies, available, in which the Sun is m_bodies[0] and Mercury is m_bodies[1].
            double rCurrent = (solarSystem.bodies()[1].position - solarSystem.bodies()[0].position).length();

            // Check if the *previous* time step was a minimum for the Mercury-Sun distance. I.e. check
            // if the previous distance is smaller than the current one *and* the previous previous one.
            if ( rCurrent > rPrevious && rPrevious < rPreviousPrevious ) {

                // If we are perihelion, print *previous* angle (in radians) to terminal.
                double x = previousPosition.x();
                double y = previousPosition.y();
                angle = atan2(y,x);
                solarSystem.writeAngleToFile(output_file, angle);
            }

            // Update the helper variables (current, previous, previousPrevious).
            rPreviousPrevious 	= rPrevious;
            rPrevious		= rCurrent;
            previousPosition	= solarSystem.bodies()[1].position - solarSystem.bodies()[0].position;

    }else if (atoi(vargs[1]) == 3){
        solarSystem.calculateEnergy();
        solarSystem.writeEnergiesToFile(output_file);
        Euler integrator(dt);
        for(int timestep=0; timestep<numTimesteps; timestep++) {
            integrator.integrateOneStep(solarSystem);
            solarSystem.calculateEnergy();
            solarSystem.writeEnergiesToFile(output_file);

        }
    }else if (atoi(vargs[1]) == 4){
        solarSystem.calculateEnergy();
        solarSystem.writeEnergiesToFile(output_file);
        Verlet integrator(dt,solarSystem);
        for(int timestep=0; timestep<numTimesteps; timestep++) {
            integrator.integrateOneStep(solarSystem);
            solarSystem.calculateEnergy();
            solarSystem.writeEnergiesToFile(output_file);

        }
    }else{
        cout << "Choose method: 0 for Euler, 1 for Verlet, 2 for Verlet with GR corrections" << endl;
        return 1;
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
            for(int i = 0; i<(nargs-6); i++){
                if((atoi(sub.c_str())==atoi(vargs[i+6])) || ((nargs == 7) && atoi(vargs[6])==0)){
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
