#include "ensemble.h"
#include <iostream>
#include <math.h>
using namespace std;

Ensemble::Ensemble() :
    m_kineticEnergy(0),
    m_potentialEnergy(0)
{
}

Particle& Ensemble::createParticle(vec3 position, vec3 velocity, double mass) {
    m_bodies.push_back( Particle(position, velocity, mass) );
    return m_bodies.back(); // Return reference to the newest added celstial body
}

void Ensemble::calculateForcesAndEnergy()
{
    m_kineticEnergy = 0;
    m_potentialEnergy = 0;
    m_angularMomentum.zeros();
    double mm_potentialEnergy = 0;
    vec3 force(0,0,0);
    for(Particle &body : m_bodies) {
        // Reset forces, kinetic and potential energy on all bodies
        body.force.zeros();
        body.kineticEnergy = 0;
        body.potensialEnergy = 0;
    }

    for(int i=0; i<numberOfBodies(); i++) {
        Particle &body1 = m_bodies[i];
        for(int j=i+1; j<numberOfBodies(); j++) {
            Particle &body2 = m_bodies[j];
            vec3 deltaRVector = body1.position - body2.position;
            double dr = deltaRVector.length();
            force =pow(2*M_PI,2)*deltaRVector*(body1.mass*body2.mass/pow(dr,3));
            body1.force -= force;
            body2.force += force;
            //Not currently needed
            //mm_potentialEnergy = -body1.mass*body2.mass/dr;
            //body1.potensialEnergy += mm_potentialEnergy;
            //body2.potensialEnergy += mm_potentialEnergy;
            //m_potentialEnergy += mm_potentialEnergy;
        }
        //body1.kineticEnergy =  0.5*body1.mass*body1.velocity.lengthSquared();
        //m_kineticEnergy += body1.kineticEnergy;

    }
}

int Ensemble::numberOfBodies() const
{
    return m_bodies.size();
}

double Ensemble::totalEnergy() const
{
    return m_kineticEnergy + m_potentialEnergy;
}

double Ensemble::potentialEnergy() const
{
    return m_potentialEnergy;
}

double Ensemble::kineticEnergy() const
{
    return m_kineticEnergy;
}

void Ensemble::writeToFile(string filename)
{
    if(!m_file.good()) {
        m_file.open(filename.c_str(), ofstream::out);
        if(!m_file.good()) {
            cout << "Error opening file " << filename << ". Aborting!" << endl;
            terminate();
        }
    }
        m_file << "New position update:" << "\n";
    for(Particle &body : m_bodies) {
        m_file << body.position.x() << " " << body.position.y() << " " << body.position.z() << " " << body.velocity(0) << " " << body.velocity(1) << " " << body.velocity(2) << "\n";
    }
}

vec3 Ensemble::angularMomentum() const
{
    return m_angularMomentum;
}

std::vector<Particle> &Ensemble::bodies()
{
    return m_bodies;
}
