#include "ensemble.h"
#include <iostream>
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

    for(Particle &body : m_bodies) {
        // Reset forces on all bodies
        body.force.zeros();
    }

    for(int i=0; i<numberOfBodies(); i++) {
        Particle &body1 = m_bodies[i];
        for(int j=i+1; j<numberOfBodies(); j++) {
            Particle &body2 = m_bodies[j];
            vec3 deltaRVector = body1.position - body2.position;
            double dr = deltaRVector.length();
            // Calculate the force and potential energy here
        }

        m_kineticEnergy += 0.5*body1.mass*body1.velocity.lengthSquared();
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
    m_file << numberOfBodies() << endl;
    m_file << "Comment line that needs to be here. Balle." << endl;
    for(Particle &body : m_bodies) {
        m_file << "1 " << body.position.x() << " " << body.position.y() << " " << body.position.z() << "\n";
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
