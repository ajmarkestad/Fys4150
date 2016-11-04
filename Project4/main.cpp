/*
   Program to solve the two-dimensional Ising model
   with zero external field.
   The coupling constant J = 1
   Boltzmann's constant = 1, temperature has thus dimension energy
   Metropolis sampling is used. Periodic boundary conditions.
*/

#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "lib.h"
#include "mpi.h"
using namespace  std;

ofstream ofile;

// inline function for periodic boundary conditions
inline int periodic(int i, int limit, int add) {
    return (i+limit+add) % (limit);
}
// Function to initialise energy and magnetization
void initialize(int, double, int **, double&, double&);
// The metropolis algorithm
void Metropolis(int, int, long&, int **, double&, double&, double *);
// prints to file the results of the calculations
void output(int, int, double, double *);

int main(int argc, char* argv[])
{
    char *outfilename;
    long idum;
    int **spin_matrix, n_spins, mcs, n_spins_squared, my_rank, numprocs;
    double w[17], average[5], initial_temp, final_temp, E, M, temp_step, total_average[5] ;


    // Read in output file, abort if there are too few command-line arguments
    if( argc <= 6 ){
        cout << "Bad Usage: " << argv[0] << "\n" << endl;
        cout << "Usage: <./main <outputfile> <int max number of metropolis cycles> <int spins in 1 dim> <double initial temperature> <double final temperature>" <<
                "<int temperature steps>" << endl;
        exit(1);
    }

    MPI_Init (&argc, &argv);
    MPI_Comm_size (MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
    if (my_rank == 0 && argc <= 1) {
        cout << "Bad Usage: " << argv[0] <<
                " read output file" << endl;
        exit(1);
    }
    if (my_rank == 0 && argc > 1) {
        outfilename=argv[1];
        ofile.open(outfilename);
    }
    mcs = atoi(argv[2]);
    n_spins=atoi(argv[3]);
    initial_temp=atof(argv[4]);
    final_temp=atof(argv[5]);
    temp_step=atof(argv[6]);



//    int no_intervalls = mcs/numprocs;
//    int myloop_begin = my_rank*no_intervalls + 1;
//    int myloop_end = (my_rank+1)*no_intervalls;
//    if ( (my_rank == numprocs-1) &&( myloop_end < mcs) ) myloop_end = mcs;

    MPI_Bcast (&n_spins, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast (&initial_temp, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast (&final_temp, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast (&temp_step, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);





    //    Read in initial values such as size of lattice, temp and cycles
    spin_matrix = (int**) matrix(n_spins, n_spins, sizeof(int));
    n_spins_squared = n_spins*n_spins;
    idum = -1-my_rank; // random starting point



    double  TimeStart, TimeEnd, TotalTime;
    TimeStart = MPI_Wtime();


    for ( double temperature = initial_temp; temperature <= final_temp; temperature+=temp_step){
        //    initialise energy and magnetization
        E = M = 0.;
        // setup array for possible energy changes
        for( int de =-8; de <= 8; de++) w[de+8] = 0;
        for( int de =-8; de <= 8; de+=4) w[de+8] = exp(-de/temperature);
        // initialise array for expectation values
        for( int i = 0; i < 5; i++) average[i] = 0.;
        initialize(n_spins, temperature, spin_matrix, E, M);
        // start Monte Carlo computation
        for (int cycles = 1; cycles <= mcs; cycles++){
            Metropolis(n_spins, n_spins_squared, idum, spin_matrix, E, M, w);
            // update expectation values
            average[0] += E;    average[1] += E*E;
            average[2] += M;    average[3] += M*M; average[4] += fabs(M);
        }
        MPI_Reduce(&average, &total_average, 5, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        // print results
        if ( my_rank == 0) {
            output(n_spins, mcs*numprocs, temperature, total_average);
        }
    }
    free_matrix((void **) spin_matrix); // free memory

    ofile.close();  // close output file
    TimeEnd = MPI_Wtime();
    TotalTime = TimeEnd-TimeStart;
    if ( my_rank == 0) {
        cout << "Time = " <<  TotalTime  << " on number of processors: "  << numprocs  << endl;
    }

    // End MPI
    MPI_Finalize ();
    return 0;
}


// function to initialise energy, spin matrix and magnetization
void initialize(int n_spins, double temperature, int **spin_matrix,
                double& E, double& M)
{
    // setup spin matrix and intial magnetization
    for(int y =0; y < n_spins; y++) {
        for (int x= 0; x < n_spins; x++){
            spin_matrix[y][x] = 1; // spin orientation for the ground state
            M +=  (double) spin_matrix[y][x];
        }
    }
    // setup initial energy
    for(int y =0; y < n_spins; y++) {
        for (int x= 0; x < n_spins; x++){
            E -=  (double) spin_matrix[y][x]*
                    (spin_matrix[periodic(y,n_spins,-1)][x] +
                    spin_matrix[y][periodic(x,n_spins,-1)]);
        }
    }
}// end function initialise

void Metropolis(int n_spins, int n_spins_squared, long& idum, int **spin_matrix, double& E, double&M, double *w)
{
    // loop over all spins
    for(int i =0; i < n_spins_squared; i++) {
        int ix = (int) (ran1(&idum)*(double)n_spins);
        int iy = (int) (ran1(&idum)*(double)n_spins);
        int deltaE =  2*spin_matrix[iy][ix]*
                (spin_matrix[iy][periodic(ix,n_spins,-1)]+
                spin_matrix[periodic(iy,n_spins,-1)][ix] +
                spin_matrix[iy][periodic(ix,n_spins,1)] +
                spin_matrix[periodic(iy,n_spins,1)][ix]);
        if ( ran1(&idum) <= w[deltaE+8] ) {
            spin_matrix[iy][ix] *= -1;  // flip one spin and accept new spin config
            M += (double) 2*spin_matrix[iy][ix];
            E += (double) deltaE;
        }
    }
} // end of Metropolis sampling over spins


void output(int n_spins, int mcs, double temperature, double *average)
{
    double norm = 1/((double) (mcs));  // divided by total number of cycles
    double Eaverage = average[0]*norm;
    double E2average = average[1]*norm;
    double Maverage = average[2]*norm;
    double M2average = average[3]*norm;
    double Mabsaverage = average[4]*norm;
    // all expectation values are per spin, divide by 1/n_spins/n_spins
    double Evariance = (E2average- Eaverage*Eaverage)/n_spins/n_spins;
    double Mvariance = (M2average - Mabsaverage*Mabsaverage)/n_spins/n_spins;
    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << setw(15) << setprecision(8) << temperature;
    ofile << setw(15) << setprecision(8) << Eaverage/n_spins/n_spins;
    ofile << setw(15) << setprecision(8) << Evariance/temperature/temperature;
    ofile << setw(15) << setprecision(8) << Maverage/n_spins/n_spins;
    ofile << setw(15) << setprecision(8) << Mvariance/temperature;
    ofile << setw(15) << setprecision(8) << Mabsaverage/n_spins/n_spins << endl;
} // end output function

