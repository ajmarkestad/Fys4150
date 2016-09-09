#include <iostream>
#include <cmath>
#include <time.h>
//#include <armadillo>
//#include <lib.h>


using namespace std;


void solver_general(double *, double *, double *, double *, double *, int);
void solver_specified(double *, double *, int );


int main(int argc, char *argv[])
{
    //DEFINING VARIABLES
    int powers, grid_size, *N;
    double *max_error, *time_special, *time_lu, *time_general;

    //FILLING VALUES
    powers = 7;                                             //Maximal power of 10 minus 1
    N = new int[powers];
    for (int i = 0; i<powers; i++) N[i]=(int)pow(10,i);     //Fills N
    max_error = new double[powers];                        //sparer på max_feil
    for (int i = 0; i<powers; i++) max_error[i]=0;
    time_special = new double[powers];
    time_general = new double[powers];
    time_lu = new double[powers];

    //LOOPS FOR ALL GRID_SIZES
    for (int i = 0; i<powers; i++)
    {

        grid_size = N[i];


        //DEFINING VARIABLES
        double *a, *b, *c, *source_func, *u, *u_specific, *exact_solution; // defining the dynamic variables
        double h, a0, b0, c0; // defining the static variables

        //ALLOCATION IN MEMORY
        h = 1.0/(grid_size+1.0);                    //Defining the step size
        a = new double[grid_size-1];                //Defining the matrix elements for a tridiagonal matrix
        b = new double[grid_size];
        c = new double[grid_size-1];
        source_func = new double[grid_size];        //Defining the source function vector
        u = new double[grid_size];                  //Defining the function vector we wish to solve
        u_specific = new double[grid_size];
        exact_solution = new double[grid_size];     //Defining the exact analytical solution vector


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

        //
        //SOLVING PROBLEM
        //General solver
        clock_t start_general, finish_general;
        start_general = clock();
        solver_general(a, b, c, u, source_func, grid_size);
        finish_general = clock();
        time_general[i] = (finish_general-start_general)/CLOCKS_PER_SEC;


        //Specified solver
        clock_t start_speficied, finish_specified; //Times the function
        start_speficied = clock();
        solver_specified(u_specific, source_func, grid_size);
        finish_specified = clock();
        time_special[i]=(finish_specified-start_speficied)/CLOCKS_PER_SEC;

        //LU decomposition
        clock_t start_lu, finish_lu; //Times the function
        start_lu = clock();
        //DO THE LU DECOMPOSITION
        finish_lu = clock();
        time_lu[i]=(finish_lu-start_lu)/CLOCKS_PER_SEC;

        cout << i << endl;
        //DEBUG PRINTING & RESULTS
        double intermediate_error = 0;
//        for(int i=0; i<grid_size; i++)
//        {

//            intermediate_error = abs(u[i]-exact_solution[i]);
//            if (intermediate_error> max_error[i]) max_error[i] = intermediate_error;
//        }


    }

    for (int i = 0; i<powers; i++){
        cout << "N=10^" << i << endl;
        cout << "Max_error: " << max_error[i] << endl;
        cout << "Time used by specified: " << time_special[i] << ". By general: " << time_general[i] << endl;
        cout << endl;
    }

    delete[] time_general;
    delete[] time_special;
    delete[] time_lu;
    delete[] max_error;
    delete[] N;
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
    delete[] b;
}

