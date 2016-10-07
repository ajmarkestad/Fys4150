#ifndef SOLVER_H
#define SOLVER_H


class Euler
{
public:
    double m_dt;
    Euler(double dt);
    void integrateOneStep(class Ensemble &system);
};

class Verlet{
public:
    double m_dt;
    Verlet(double dt);
    void integrateOneStep(class Ensemble &system);
};

#endif // SOLVER_H
