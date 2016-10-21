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

void Ensemble::calculateForces()
{
    vec3 force(0,0,0);
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
            force =pow(2*M_PI,2)*deltaRVector*(body1.mass*body2.mass/pow(dr,3));
            body1.force -= force;
            body2.force += force;
        }

    }
}

void Ensemble::calculateForces_GR()
{
    c = 63198;
    m_angularMomentum.zeros();
    vec3 force(0,0,0);
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
            m_angularMomentum = deltaRVector.cross(body2.velocity);
            force =pow(2*M_PI,2)*deltaRVector*(body1.mass*body2.mass/pow(dr,3))*(1 + (3* pow(m_angularMomentum.length(),2))/(pow(dr,2)*pow(c,2)));
            body1.force -= force;
            body2.force += force;
        }

    }
}

void Ensemble::calculateEnergy()
{
    m_kineticEnergy = 0;
        m_potentialEnergy = 0;
        m_angularMomentum.zeros();
        double mm_potentialEnergy = 0;
        for(Particle &body : m_bodies) {
            // Reset kinetic and potential energy on all bodies
            body.kineticEnergy = 0;
            body.potensialEnergy = 0;
    }
    for(int i=0; i<numberOfBodies(); i++) {
        Particle &body1 = m_bodies[i];
        for(int j=i+1; j<numberOfBodies(); j++) {
            Particle &body2 = m_bodies[j];
            vec3 deltaRVector = body1.position - body2.position;
            double dr = deltaRVector.length();
            mm_potentialEnergy = body1.mass*body2.mass/dr;
            body1.potensialEnergy += mm_potentialEnergy;
            body2.potensialEnergy += mm_potentialEnergy;
            m_potentialEnergy += mm_potentialEnergy;
        }
        body1.kineticEnergy =  0.5*body1.mass*body1.velocity.lengthSquared();
        m_kineticEnergy += body1.kineticEnergy;

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
    int counter = 0;
    for(Particle &body : m_bodies) {
        string s = to_string(counter);
        filename.append(s);
        m_file.open(filename.c_str(), ofstream::app);
        m_file << body.position.x() << " " << body.position.y() << " " << body.position.z() << "\n";
        m_file.close();
        filename.pop_back();
        counter += 1;
    }
}

void Ensemble::writeEnergiesToFile(string filename)
{
    if(!m_file.good()){
        m_file.open(filename.c_str(), ofstream::out);
        if(!m_file.good()){
            cout << "Bad Usage! " << endl;
            terminate();
        }
    }
    m_file << m_kineticEnergy + m_potentialEnergy << " " << m_kineticEnergy << " " << m_potentialEnergy << "\n";
}



vec3 Ensemble::angularMomentum() const
{
    return m_angularMomentum;
}

std::vector<Particle> &Ensemble::bodies()
{
    return m_bodies;
}
