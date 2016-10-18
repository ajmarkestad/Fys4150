#ifndef SOLVER_H
#define SOLVER_H

#include <armadillo>

class Euler
{
public:
    double m_dt;
    Euler(double dt);
    void integrateOneStep(class Ensemble &system);
};

class Verlet{
public:
    double constant1;
    double constant2;
    double m_dt;
    arma::mat force;
    Verlet(double dt, Ensemble &system);
    void integrateOneStep(class Ensemble &system);
};



class Verlet_GR{
public:
    double constant1;
    double constant2;
    double m_dt;
    arma::mat force;
    Verlet_GR(double dt, Ensemble &system);
    void integrateOneStep(class Ensemble &system);
};

#endif // SOLVER_H
