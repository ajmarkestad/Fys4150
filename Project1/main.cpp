#include <iostream>
#include <cmath>
//#include <lib.h>


using namespace std;


void solver_general(double *, double *, double *, double *, double *, int);
//void solver_specified(double *, double *, int );


int main(int argc, char *argv[])
{
    double N [] = {10, 100, 1000};  //grid sizes
    int grid_size;
    double *a, *b, *c, *source_func, *u, *exact_solution; // defining the dynamic variables
    double h, a0, b0, c0; // defining the static variables


    //initialize vectors

    grid_size = N[1];
    h = 1.0/(grid_size+1.0);            //Defining the step size
    a = new double[grid_size-1];    //Defining the matrix elements for a tridiagonal matrix
    b = new double[grid_size];
    c = new double[grid_size-1];
    source_func = new double[grid_size];    //Defining the source function vector
    u = new double[grid_size];              //Defining the function vector we wish to solve

    exact_solution = new double[grid_size]; //Defining the exact analytical solution vector

    for (int i=0; i<grid_size+1; i++){
        exact_solution[i]=1.0-(1.0-exp(-10.0))*i*h-exp(-10.0*i*h);
        }



    a0 = -1.0; // Defining the matrix element values
    b0 = 2.0;
    c0 = -1.0;

    //calculates f for the grid size
    for (int i=0; i<grid_size+1; i++){
        source_func[i]=(100.0*exp(-10.0*(i*h)))*pow(h,2.0);
        }

    //Filling out the vectors with the matrix elements
    for (int i=0; i<grid_size-1; i++){
        a[i] = a0;
        b[i] = b0;
        c[i] = c0;
    }

    solver_general(a, b, c, u, source_func, grid_size);     //Solving the differential equation
    cout << "Step length: " << h << endl;
    cout << "grid size: " << grid_size << endl;



    //Printing out calculated and exact values to compare as a code test
    for(int i=0; i<grid_size; i++){
        cout << "calculated solution: " << u[i] << "  Analytical solution: " << exact_solution[i] << endl;
    }

//    int n=N[0];
//    double f[2] = {1,2}; //= vector(n)
//    for (int i = 0; i<n; i++) f[i]*=(1./pow(n,-2)); //corrects f values


//    for (int i=0; i<3; i++){
//        double value = afunction(N[i]);
//        cout << "N[" << i << "] = " << N[i] << ". f(N[i]) = " << value << endl;

//    }
    return 0;
}





void solver_general(double *a, double *b, double *c, double *u, double *source_func, int grid_size){
    //assuming a, b, c, source_func are vectors of size grid_size
    // while b,c are of size grid_size-1


    //forward substitution
    for (int i = 1; i<grid_size+1; i++)
    {
        b[i]-= a[i-1]*c[i-1]/b[i-1];
        source_func[i]-= source_func[i-1]*c[i-1]/b[i-1];
    }

    u[grid_size] = source_func[grid_size]/b[grid_size];

    //backward substitution
    for (int i = grid_size-1; i -- > 0;)
    {
        u[i]=(source_func[i]-c[i]*u[i+1])/b[i];
    }

}

//void solver_specified(target_vector, function_values, grid_size)
//{

//}

