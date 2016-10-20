#ifndef ENSEMBLE_H
#define ENSEMBLE_H

#include "particle.h"
#include <vector>
#include <string>
#include <fstream>

class Ensemble
{
public:
    Ensemble();
    Particle &createParticle(vec3 position, vec3 velocity, double mass);
    void calculateForces();
    void calculateForces_GR();
    void calculateEnergy();
    int numberOfBodies() const;

    double totalEnergy() const;
    double potentialEnergy() const;
    double kineticEnergy() const;
    void writeToFile(std::string filename);
    void writeEnergiesToFile(std::string filename);
    vec3 angularMomentum() const;
    std::vector<Particle> &bodies();


private:
    std::vector<Particle> m_bodies;
    vec3 m_angularMomentum;
    std::ofstream m_file;
    double m_kineticEnergy;
    double m_potentialEnergy;
    double c;
};

#endif // ENSEMBLE_H
