#include <iostream>
#include <cmath>
#include <string>
#include <fstream> // For reading to file
#include <iomanip>
#include <sstream>
#include <time.h>
#include <armadillo>
//#include "lib.cpp"
//#include "lib.h"




using namespace std;
using namespace arma;


void solver_general(double *, double *, double *, double *, double *, int);
void solver_specified(double *, double *, int , double *);
void output( double *, double *, double *, int);
void output_general( double *, double *, double *, double *, int);

ofstream ofile;
int main()
{
    //DEFINING VARIABLES

    int powers, grid_size, *N;
    double *max_error, *time_special, *time_lu, *time_general;

    //FILLING VALUES
    powers = 8;                                             //Maximal power of 10
    N = new int[powers];
    for (int i = 0; i<powers; i++) N[i]=(int)pow(10,i+1);     //Fills N
    max_error = new double[powers];                         //sparer på max_feil
    for (int i = 0; i<powers; i++) max_error[i]=0;
    time_special = new double[powers];
    time_general = new double[powers];
    time_lu = new double[powers];

    //LOOPS FOR ALL GRID_SIZES
    for (int i = 0; i<powers; i++)
    {
        grid_size = N[i];

        //DEFINING VARIABLES
        double *a, *b, *c, *source_func, *u, *u_specific, *exact_solution, *x_list; // defining the dynamic variables
        double h, a0, b0, c0; // defining the static variables
        //matrix(grid_size,grid_size,sizeof((double)4));

        //ALLOCATION IN MEMORY
        h = 1.0/(grid_size+1.0);                    //Defining the step size
        a = new double[grid_size-1];                //Defining the matrix elements for a tridiagonal matrix
        b = new double[grid_size];
        c = new double[grid_size-1];
        source_func = new double[grid_size];        //Defining the source function vector
        u = new double[grid_size];                  //Defining the function vector we wish to solve
        u_specific = new double[grid_size];
        exact_solution = new double[grid_size];     //Defining the exact analytical solution vector
        x_list = new double[grid_size];

        //FILLING VECTORS
        a0 = -1.0;                                                              // Defining the matrix element values
        b0 = 2.0;
        c0 = -1.0;
        for (int k=0; k<grid_size; k++)
        {
            exact_solution[k]=1.0-(1.0-exp(-10.0))*(k+1)*h-exp(-10.0*(k+1)*h);  //Exact solution
            source_func[k]=100.0*exp(-10.0*(k+1)*h)*pow(h,2.0);                 //Source function
            x_list[k] = (1.0+k)*h;
            b[k] = b0;
        }
        for (int k=0; k<grid_size-1; k++) {
            c[k] = c0;
            a[k] = a0;
        }

        //
        //SOLVING PROBLEM
        //General solver
        clock_t start_general, finish_general;
        start_general = clock();
        solver_general(a, b, c, u, source_func, grid_size);
        finish_general = clock();
        time_general[i] = (double)(finish_general-start_general)/CLOCKS_PER_SEC;


        //Specified solver
        double *diagonal = new double[grid_size];
        diagonal[0]=2;
        for (int i = 1; i<grid_size; i++)
        {
            diagonal[i] = (i+1)/i;
        }
        clock_t start_speficied, finish_specified; //Times the function
        start_speficied = clock();
        solver_specified(u_specific, source_func, grid_size, diagonal);
        finish_specified = clock();
        time_special[i]=(double)(finish_specified-start_speficied)/CLOCKS_PER_SEC;

        //LU decomposition
        if (grid_size<=1000){
            //Creates matrices for the LU-decomposition
            vec y(grid_size), arma_solution(grid_size); mat a = zeros<mat>(grid_size, grid_size);
            for (int k = 0; k<grid_size-1; k++)
                {

                y(k)=source_func[k];
                a(k+1,k)=-1;
                a(k,k+1)=-1;
                a(k,k)=2;
            }
            y(grid_size-1)=source_func[grid_size-1];
            a(grid_size-1,grid_size-1)=2;

            //DO THE LU DECOMPOSITION
            clock_t start_lu, finish_lu;
            start_lu = clock();
            arma_solution=solve( a, y);
            finish_lu = clock();
            time_lu[i]=(double)(finish_lu-start_lu)/CLOCKS_PER_SEC;
        } else
        {
            time_lu[i]=0;
        }


        //CALCULATE MAX ERROR
        double intermediate_error = 0;
        for(int j=0; j<grid_size; j++)
        {
            intermediate_error =  (double)abs(u[j]-exact_solution[j]);
            if (intermediate_error> max_error[i]) max_error[i] = intermediate_error;
        }

        if(grid_size <= 1000){
            //SAVE DATA TO FILE
            string str1 = "Project_1_exact_and_computed_values_for_grid_size_";
            string outfilename;
            outfilename.append(str1);
            int number1 = grid_size;
            stringstream ss;
            ss << number1;
            outfilename.append(ss.str());
            ofile.open(outfilename);
            output(x_list, u, exact_solution, grid_size);

            // close output file
            ofile.close();
        }{

        }
    }


    //SAVES GENERAL FOR ALL RUNS
    output_general(max_error, time_general, time_special, time_lu, powers);

    //FREEING MEMORY
    delete[] time_general; delete[] time_special; delete[] time_lu; delete[] max_error; delete[] N;
    return 0;
}


void solver_general(double *a, double *b, double *c, double *u, double *source_func, int grid_size){
    //assuming a, b, c, source_func are vectors of size grid_size
    // while b,c are of size grid_size-1

    double intermediate;
    //forward substitution
    for (int i = 1; i<grid_size; i++)
    {
        intermediate = a[i-1]/b[i-1];                       //1 flop
        b[i]-= a[i-1]* intermediate;                        //2 flop
        source_func[i]-= source_func[i-1]*intermediate;     //2 flop
    }

    //backward substitution
    u[grid_size-1] = source_func[grid_size-1]/b[grid_size-1];
    for (int i = grid_size-2; i >= 0; i--)
    {
        u[i]=(source_func[i]-c[i]*u[i+1])/b[i];             //3 flop
    }
}

void solver_specified(double *u, double *source_func, int grid_size, double *diagonal)
{
    //allocate b-vector.
    //forward substitution
    for (int i = 1; i<grid_size; i++)
    {
        source_func[i]+= source_func[i-1]/diagonal[i-1];           //2 flops
    }

    //backward substitution
    u[grid_size-1] = source_func[grid_size-1]/diagonal[grid_size-1];
    for (int i = grid_size-2; i >= 0;i--)
    {
        u[i]=(source_func[i]+u[i+1])/diagonal[i];                  //2 flops
    }
}


void output(double *x_axis, double *u_general, double *exact_solution, int grid_size )
{
    ofile << setiosflags(ios::uppercase | ios::uppercase | ios::uppercase);
    for(int i=0; i < grid_size; i++)
    {
        ofile << setw(15) << setprecision(8) << u_general[i];
        ofile << setw(15) << setprecision(8) << exact_solution[i];
        ofile << setw(15) << setprecision(8) << x_axis[i] << endl;
    }
}


void output_general(double *max_error, double *time_general, double *time_special, double *time_lu, int powers)
{

    //HEADER
    ofile.open("Results_General");
    ofile << "Results for all runs:" << endl;
    ofile << setiosflags(ios::showpoint | ios::uppercase | ios::uppercase | ios::uppercase | ios::uppercase);
    ofile << setw(8) << "log10(N)" << setw(16) << "log10(maxerror)" << setw(16) << "Time general(s)";
    ofile << setw(16) << "Time special(s)" << setw(16) << "Time LU (s)" << endl;

    //FILLS NUMBERS
    for (int i = 0; i<powers; i++){
        ofile << setiosflags(ios::showpoint | ios::uppercase | ios::uppercase | ios::uppercase | ios::uppercase);
        ofile << setw(8) << i+1;
        ofile << setw(16) << setprecision(4) << log10(max_error[i]);
        ofile << setw(16) << setprecision(4) << time_general[i];
        ofile << setw(16) << setprecision(4) << time_special[i];
        ofile << setw(16) << setprecision(4) << time_lu[i] << endl;
    }
    ofile.close();
}

