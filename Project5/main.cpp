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
// Function to initialise energy and magnetization
void initialize(int, int, int **, double&, double&);
// prints to file the results of the calculations
void output();

int main(int argc, char* argv[])
{
    char *outfilename;
    long idum;
    int **spin_matrix, n_spins, mcs, n_spins_squared, my_rank, numprocs, initializationParameter, acceptanceCounter;
    double w[17], average[5], initial_temp, final_temp, E, M, temp_step, total_average[5] ;


    // Read in output file, abort if there are too few command-line arguments
    if( argc <= 6 ){
        cout << "Bad Usage: " << argv[0] << "\n" << endl;
        cout << "Usage: <./main> <initalization type> <outputfile> <int max number of metropolis cycles> <int spins in 1 dim> <double initial temperature> <double final temperature>" <<
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
    initializationParameter = atoi(argv[2]);
    mcs = atoi(argv[3]);
    n_spins=atoi(argv[4]);
    initial_temp=atof(argv[5]);
    final_temp=atof(argv[6]);
    temp_step=atof(argv[7]);

    acceptanceCounter = 0;


    if (initializationParameter == 0){
        MPI_Bcast (&n_spins, 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast (&initial_temp, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        MPI_Bcast (&final_temp, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        MPI_Bcast (&temp_step, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

        //    Read in initial values such as size of lattice, temp and cycles
        n_spins_squared = n_spins*n_spins;
        idum = -1-my_rank; // random starting point

        double  TimeStart, TimeEnd, TotalTime;
        TimeStart = MPI_Wtime();


        for ( double temperature = initial_temp; temperature <= final_temp; temperature+=temp_step){

            // start Monte Carlo computation
            initialize();
            for (int cycles = 1; cycles <= mcs; cycles++){
                // update expectation values
                average[0] += E;    average[1] += E*E;
                average[2] += M;    average[3] += M*M; average[4] += fabs(M);
            }
            cout << temperature << "  "<< my_rank << endl;
            MPI_Reduce(&average, &total_average, 5, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
            // print results
            if ( my_rank == 0) {
                output(e);
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
    }


    return 0;
}


void Histogram(int &Hist, double moneyBins, double listofAgents, int numberofAgents, int numberofBins)
{
    int i, j;
    for(i=0;i<numberofBins;i++){
        for(j=0;j<numberofAgents;j++){
            if(listofAgents[j]<moneyBins[i+1] && listofAgents[j]>moneyBins[i]){
                Hist[i] += 1;
            }
        }
    }
}


void initialize()
{

}


void output()
{

}

