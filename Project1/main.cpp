#include <iostream>
#include <cmath>
//#include <lib.h>


using namespace std;


void solver_general(double *, double *, double *, double *, double *, int);
void solver_specified(double *, double *, int );


int main(int argc, char *argv[])
{
    //DEFINING VARIABLES
    double N [] = {10, 100, 1000000};  //grid sizes
    int grid_size;
    double *a, *b, *c, *source_func, *u, *u_specific, *exact_solution; // defining the dynamic variables
    double h, a0, b0, c0; // defining the static variables


    //ALLOCATION IN MEMORY
    grid_size = N[2];
    h = 1.0/(grid_size+1.0);            //Defining the step size
    a = new double[grid_size-1];    //Defining the matrix elements for a tridiagonal matrix
    b = new double[grid_size];
    c = new double[grid_size-1];
    source_func = new double[grid_size];    //Defining the source function vector
    u = new double[grid_size];              //Defining the function vector we wish to solve
    u_specific = new double[grid_size];
    exact_solution = new double[grid_size]; //Defining the exact analytical solution vector


    //FILLING VECTORS
    a0 = -1.0; // Defining the matrix element values
    b0 = 2.0;
    c0 = -1.0;
    for (int i=0; i<grid_size+1; i++)
    {
        exact_solution[i]=1.0-(1.0-exp(-10.0))*i*h-exp(-10.0*i*h); //Exact solution
        source_func[i]=(100.0*exp(-10.0*(i*h)))*pow(h,2.0);        //Source function
        a[i] = a0;                                                 //matrix elements
        b[i] = b0;
        c[i] = c0;
    }



    cout << "Step length: " << h << endl;
    cout << "grid size: " << grid_size << endl;

    //SOLVING PROBLEM
    solver_general(a, b, c, u, source_func, grid_size);     //Solving the differential equation
    solver_specified(u_specific, source_func, grid_size);


    //DEBUG PRINTING & RESULTS
    double rms = 0;
    for(int i=0; i<grid_size; i++)
    {
        rms += pow(u[i]-exact_solution[i],2);
        //cout << "calculated solution: " << u[i] << "  Analytical solution: " << exact_solution[i] << endl;
    }
    rms /=grid_size;
    rms = sqrt(rms)*100;
    cout << "Results: " << endl;
    cout << "RMS difference between analytic and calculated:" << rms << endl;

    return 0;
}





void solver_general(double *a, double *b, double *c, double *u, double *source_func, int grid_size){
    //assuming a, b, c, source_func are vectors of size grid_size
    // while b,c are of size grid_size-1

    double intermediate;
    //forward substitution
    for (int i = 1; i<grid_size+1; i++)
    {
        intermediate = a[i-1]/b[i-1];   //1 flop
        b[i]-= a[i-1]* intermediate;    //2 flop
        source_func[i]-= source_func[i-1]*intermediate; // 2 flop
    }

    //backward substitution
    u[grid_size] = source_func[grid_size]/b[grid_size];
    for (int i = grid_size-1; i -- > 0;)
    {
        u[i]=(source_func[i]-c[i]*u[i+1])/b[i]; //3 flop
    }

}

void solver_specified(double *u, double *source_func, int grid_size)
{
    //allocate b-vector.
    double *b = new double[grid_size];

    b[0]=2;
    //forward substitution
    for (int i = 1; i<grid_size+1; i++)
    {
        b[i] = (i+1)/i;     //2 flops
        source_func[i]+= source_func[i-1]/b[i-1];   // 2 flops
    }

    //backward substitution
    u[grid_size] = source_func[grid_size]/b[grid_size];
    for (int i = grid_size-1; i -- > 0;)
    {
        u[i]=(source_func[i]+u[i+1])/b[i];  // 2 flops
    }
}

