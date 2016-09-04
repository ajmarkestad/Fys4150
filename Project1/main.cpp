#include <iostream>
#include <cmath>
//#include <lib.h>


using namespace std;


void solver_general(double a [], double b [], double c [],
                   double target_vector [], double function_values [], int grid_size);
void solver_specified(double target_vector [], double function_values [], int grid_size);
double afunction(double x); //the given function in the problem
double solution(double x); // the analytic solution to the equation


int main(int argc, char *argv[])
{
    double N [] = {10, 100, 1000};  //grid sizes






    //calculates f for various N values
//    for (int i=0; i<N; i++){
//        f[i]=100*exp(-10*(i/N));
    //    }

    //initialize vectors


    int n=N[0];
    double f[2] = {1,2}; //= vector(n)
    for (int i = 0; i<n; i++) f[i]*=(1./pow(n,-2)); //corrects f values


    for (int i=0; i<3; i++){
        double value = afunction(N[i]);
        cout << "N[" << i << "] = " << N[i] << ". f(N[i]) = " << value << endl;

    }
    return 0;
}

int test1(){
    cout << "test" << endl;
    return 0;
}

double afunction(double x)
{
    double f = 100*exp(-10*x);
    return f;
}

double solution(double x){
    double f = 1-(1-exp(-10))*x-exp(-10.*x);
    return f;
}



void solver_general(double a [], double b [], double c [],
                   double u [], double f [], int grid_size){
    //assuming a, target_vector, function_values are vectors of size grid_size
    // while b,c are of size grid_size-1


    //forward substitution
    for (int i = 1; i<grid_size; i++)
    {
        a[i]-= b[i-1]*c[i-1]/a[i-1];
        f[i]-= f[i-1]*c[i-1]/a[i-1];
    }

    //backward substitution
    for (int i = grid_size-1; i>1 ; i--)
    {
        u[i]=(f[i]-b[i]*u[i+1]);
    }

}

void solver_specified(double target_vector [], double function_values [], int grid_size)
{

}

