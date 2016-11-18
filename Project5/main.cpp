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
//#include "mpi.h"
using namespace  std;

ofstream ofile;
// Function to initialise energy and magnetization
void initialize(int, int, int **, double&, double&);
// prints to file the results of the calculations
void output(double*, int);
void transaction_simple(double *, int, long&, int);
void transaction_advanced(double *, int, long&, int);


int main(int argc, char* argv[])
{
    char *outfilename;
    long idum;
    int  my_rank, numprocs, total_runs, initializationParameter, cycles_per_run, *Hist[numberofBins], numberofAgents, numberofBins, total_transactions, initialMoney;
    double *agentlist[numberofAgents], moneyBins[numberofBins];


    // Read in output file, abort if there are too few command-line arguments
    if( argc <= 5 ){
        cout << "Bad Usage: " << argv[0] << "\n" << endl;
        cout << "Usage: <./main> <initalization type> <outputfile> <int total number of runs> <int cycles per run> " << endl;
        exit(1);
    }

    //    MPI_Init (&argc, &argv);
    //    MPI_Comm_size (MPI_COMM_WORLD, &numprocs);
    //    MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
    //    if (my_rank == 0 && argc <= 1) {
    //        cout << "Bad Usage: " << argv[0] <<
    //                " read output file" << endl;
    //        exit(1);
    //    }
    //    if (my_rank == 0 && argc > 1) {

    //    }
    outfilename=argv[1];
    ofile.open(outfilename);
    initializationParameter = atoi(argv[2]);
    total_runs = atoi(argv[3]);
    cycles_per_run = atoi(argv[4]);
    my_rank = 0;

    double step = initialMoney*numberofAgents/numberofBins;
    for (int h = 0; h<numberofBins; h++){
        moneyBins[h] = h*step;
    }





    //    if (initializationParameter == 0){
    //        MPI_Bcast (&n_spins, 1, MPI_INT, 0, MPI_COMM_WORLD);
    //        MPI_Bcast (&initial_temp, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    //        MPI_Bcast (&final_temp, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    //        MPI_Bcast (&temp_step, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    //    Read in initial values such as size of lattice, temp and cycles
    idum = -1-my_rank; // random starting point

    //    double  TimeStart, TimeEnd, TotalTime;
    //        TimeStart = MPI_Wtime();
    //INITIALIZATION
    for(int i=0;i<numberofAgents;i++){
        listofAgents[i] = initialMoney;
    }

    for(int a=0;a<MaxGate;a++){
        Histogram(Hist, moneyBins, agentlist, numberofAgents, numberofBins);
        int Hist_prevous[numberofBins];

        for(int j=0;j<numberofBins;j++){
            Hist_prevous[j] = Hist[j];
        }

        if(initializationParameter==0){
            transaction_simple(agentlist, numberofAgents, idum, total_transactions);
        }else if(initializationParameter==1){
            transaction_advanced(agentlist, numberofAgents, idum, total_transactions);
        }

        int Criterium;
        for(int k=0;k<numberofBins;k++){
            Criterium += abs(Hist[k]-Hist_prevous[k]);
        }
        if(Criterium <= epsilon){
            cout << "Steady state reached!" << endl;
            break
        }
    }

    //MAIN LOOP
    for ( int run= 0; run<= total_runs; run++){

        // start Monte Carlo computation
        if(initializationParameter==0){
            transaction_simple(agentlist, numberofAgents, idum, total_transactions);
        }else if(initializationParameter==1){
            transaction_advanced(agentlist, numberofAgents, idum, total_transactions);
        }

        //cumulative histogram?

    }

    //output
    output(histogram, bins);
    //            MPI_Reduce(&average, &total_average, 5, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    free_matrix((void *) histogram); // free memory


    //        TimeEnd = MPI_Wtime();
    //        TotalTime = TimeEnd-TimeStart;
    //        if ( my_rank == 0) {
    //            cout << "Time = " <<  TotalTime  << " on number of processors: "  << numprocs  << endl;
    //        }

    // End MPI
    //        MPI_Finalize ();
    //    }


    ofile.close();  // close output file
    return 0;
}


void transaction_simple(double * agentlist, int agents, long& idum, int total_transactions)
{
    for (int i=0; i<total_transactions; i++)
    {
        int agent1 = (int) (ran2(&idum)*(double)agents);
        int agent2 = (int) (ran2(&idum)*(double)agents);
        if(agent1!=agent2)
        {
            double transaction_rate = (double) (ran2(&idum));
            double totalcash = agentlist[agent1]+agentlist[agent2];
            agentlist[agent1]=transaction_rate*totalcash;
            agentlist[agent2]=(1-transaction_rate)*totalcash;
        }
    }
}

void transaction_advanced(double * agentlist, int agents, long& idum, int total_transactions)
{
    for (int i=0; i<total_transactions; i++)
    {
        int agent1 = (int) (ran2(&idum)*(double)agents);
        int agent2 = (int) (ran2(&idum)*(double)agents);
        if(agent1!=agent2)
        {
            double transaction_rate = (double) (ran2(&idum));
            double totalcash = agentlist[agent1]+agentlist[agent2];
            agentlist[agent1]=transaction_rate*totalcash;
            agentlist[agent2]=(1-transaction_rate)*totalcash;
        }
    }
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

void output(double *histogram, int bins)
{
    for (int bin=0, bin<bins, bin++)
    {
        ofile << setw(15) << setprecision(8) << histogram[bin] << endl;
    }
}

