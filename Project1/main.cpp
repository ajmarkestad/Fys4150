#include <iostream>
#include <cmath>
#include <string>
#include <fstream> // For reading to file
#include <iomanip>
#include <sstream>
//#include <lib.h>


using namespace std;


void solver_general(double *, double *, double *, double *, double *, int);
void solver_specified(double *, double *, int );
void output( double *, double *, double *, int);

ofstream ofile;

int main()
{
    //DEFINING VARIABLES
    int N [] = {10, 100, 1000000};  //grid sizes
    int grid_size;
    string str1 = "Project_1_exact_and_computed_values_for_grid_size_";
    string outfilename;



    double *a, *b, *c, *source_func, *u, *u_specific, *exact_solution, *x_list; // defining the dynamic variables
    double h, a0, b0, c0; // defining the static variables


    //ALLOCATION IN MEMORY
    grid_size = N[1];
    h = 1.0/(grid_size+1.0);            //Defining the step size
    a = new double[grid_size-1];    //Defining the matrix elements for a tridiagonal matrix
    b = new double[grid_size];
    c = new double[grid_size-1];
    source_func = new double[grid_size];    //Defining the source function vector
    u = new double[grid_size];              //Defining the function vector we wish to solve
    u_specific = new double[grid_size];
    exact_solution = new double[grid_size]; //Defining the exact analytical solution vector
    x_list = new double[grid_size];


    //FILLING VECTORS
    a0 = -1.0; // Defining the matrix element values
    b0 = 2.0;
    c0 = -1.0;
    for (int i=0; i<grid_size+1; i++)
    {
        exact_solution[i]=1.0-(1.0-exp(-10.0))*i*h-exp(-10.0*i*h);  //Exact solution
        source_func[i]=(100.0*exp(-10.0*(i*h)))*pow(h,2.0);         //Source function
        x_list[i] = i*h;
        a[i] = a0;                                                  //matrix elements
        b[i] = b0;
        c[i] = c0;
    }



    //SOLVING PROBLEM
    solver_general(a, b, c, u, source_func, grid_size);     //Solving the differential equation
    solver_specified(u_specific, source_func, grid_size);


    outfilename.append(str1);

    int number1 = N[1];
    stringstream ss;
    ss << number1;

    outfilename.append(ss.str());

    ofile.open(outfilename);

    output(x_list, u, exact_solution, grid_size);


    // close output file
    ofile.close();


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




void output(double *x_axis, double *u_general, double *exact_solution, int grid_size )
{
  int i;
  ofile << " RESULTS:" << endl;
  ofile << setiosflags(ios::showpoint | ios::uppercase | ios::uppercase);
  for( i=0; i < grid_size+1; i++)
    {
      ofile << setw(15) << setprecision(8) << u_general[i];
      ofile << setw(15) << setprecision(8) << exact_solution[i];
      ofile << setw(15) << setprecision(8) << x_axis[i] << endl;
}
}


