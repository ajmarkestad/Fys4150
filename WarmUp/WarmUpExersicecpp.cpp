// Program to find derivative of a function at a point, using two-pont and three-point
// derivation methods, and then find the relative error to the exact solution.


using namespace std;
#include <cmath> //math functions
#include <iostream> // input and output
#include <fstream> // For reading to file
#include <iomanip>
#include <cstdlib> //For the exit function

void initialize (double *, double *, int *);
void first_derivative_2p( int, double, double, double *, double *);
void first_derivative_3p( int, double, double, double *, double *);
void output( double *, double *, double *, double, int);

ofstream ofile;


int main(int argc, char* argv[])
{
  // Declaring variables
  char *outfilename;
  int number_of_steps;
  double x, initial_step;
  double *h_step, *computed_derivative_2p, *computed_derivative_3p;

  // Read in output file, abort if there are too few command-line arguments
  if( argc <= 1){
    cout << "Bad Usage: " << argv[0] << " read aslo output file om same line" << endl;
    exit(1);
  }
  else{
    outfilename=argv[1];
  }
  ofile.open(outfilename);

  // read in input data

  initialize (&initial_step, &x, &number_of_steps);

  //allocate space in memory for the one-dimensional arrays
  //h_step and computed_derivative
  h_step = new double[number_of_steps];
  computed_derivative_3p = new double[number_of_steps];
  computed_derivative_2p = new double[number_of_steps];
  
  //compute the first derivative
  first_derivative_2p( number_of_steps, x, initial_step, h_step, computed_derivative_2p);
  first_derivative_3p( number_of_steps, x, initial_step, h_step, computed_derivative_3p);
  //Print to file

  output(h_step, computed_derivative_2p, computed_derivative_3p, x, number_of_steps );

  //free memory
  delete [] h_step;
  delete [] computed_derivative_2p;
  delete [] computed_derivative_3p;
 
  // close output file
  ofile.close();

  return 0;
  //end program
}


// Reads in initial step, number of steps and value of x

void initialize (double *initial_step, double *x, int *number_of_steps)
{
  printf("Read in from screen initial step, x, and number of steps\n");
  scanf("%lf %lf %d",initial_step, x, number_of_steps);
  return;
}


// Function computes first derivative using the 3 point method

void first_derivative_3p( int number_of_steps, double x, double initial_step, double *h_step, double *computed_derivative_3p)
{
  int counter;
  double h;

  //calculate the step size, initialize the derivative and iteration counter
  h = initial_step;

  for (counter=0; counter < number_of_steps; counter++ )
  {
  
    // setup arrays with derivatives and step sizes
    h_step[counter] = h;
    computed_derivative_3p[counter] = (atan(x + h) - atan(x-h))/(2*h);
    h = h*0.1;
  }

  return;
}


// Function computes first derivative using the 2 point method

void first_derivative_2p( int number_of_steps, double x, double initial_step, double *h_step, double *computed_derivative_2p)
{
  int counter;
  double h;

  //calculate the step size, initialize the derivative and iteration counter
  h = initial_step;

  for (counter=0; counter < number_of_steps; counter++ )
  {
  
    // setup arrays with derivatives and step sizes
    h_step[counter] = h;
    computed_derivative_2p[counter] = (atan(x + h) - atan(x))/(h);
    h = h*0.1;
  }

  return;
}

// function to write out the final results

void output(double *h_step, double *computed_derivative_2p, double *computed_derivative_3p, double x, int number_of_steps )
{
  int i;
  ofile << " RESULTS:" << endl;
  ofile << setiosflags(ios::showpoint | ios::uppercase | ios::uppercase);
  for( i=0; i < number_of_steps; i++)
    {
      ofile << setw(15) << setprecision(8) << log10(h_step[i]);
      ofile << setw(15) << setprecision(8) << log10(fabs(computed_derivative_2p[i]-(1/(pow(x,2) + 1)))/(1/(pow(x,2)+1)));
      ofile << setw(15) << setprecision(8) << log10(fabs(computed_derivative_3p[i]-(1/(pow(x,2) + 1)))/(1/(pow(x,2)+1))) << endl;
}
}

