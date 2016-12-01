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

// prints to file the results of the calculations
void output(double*, int, int, int);
void Output_M(int, double);
void transaction_simple(double *, int, long&, int);
void transaction_advanced(double *, int, long&, int);
void Histogram(int &, double , double , int , int );


int main(int argc, char* argv[])
{
    long idum;
    int  total_runs, initializationParameter, cycles_per_run, numberofAgents, numberofBins, total_transactions, tall;
    double initialMoney;

    // Read in output file, abort if there are too few command-line arguments
    if( argc <= 7 ){
        cout << "Bad Usage: " << argv[0] << "\n" << endl;
        cout << "Usage: <./main> <initalization type> <outputfile> <int total number of runs> <int cycles per run> <int number of histogram bins> <int number of agents><tall>" << endl;
        exit(1);
    }
    string outfilename=argv[1];
    initializationParameter = atoi(argv[2]);
    total_runs = atoi(argv[3]);
    cycles_per_run = atoi(argv[4]);
    numberofBins = atoi(argv[5]);
    numberofAgents = atoi(argv[6]);
    tall = atoi(argv[7]);

    double moneyBins[numberofBins], *agentlist[numberofAgents];
    int *Hist[numberofBins];

    double step = initialMoney*numberofAgents/numberofBins;
    for (int h = 0; h<numberofBins; h++){
        moneyBins[h] = h*step;
    }

    initialMoney = 1;
    idum = -1;

            for(int i=0;i<numberofAgents;i++){
        *agentlist[i] = initialMoney;
    }

    int MaxGate = 1000;
    for(int a=0;a<MaxGate;a++){
        Histogram(Hist, moneyBins, agentlist, numberofAgents, numberofBins);
        int Hist_prevous[numberofBins];
        for(int j=0;j<numberofBins;j++){
            Hist_prevous[j] = Hist[j];
        }
    }



    ofile.open(outfilename+"init");
    //MAIN LOOP
    for ( int run= 0; run<= total_runs; run++){

        // start Monte Carlo computation
        if(initializationParameter==0){
            transaction_simple(agentlist, numberofAgents, idum, total_transactions);
        }else if(initializationParameter==1){
            transaction_advanced(agentlist, numberofAgents, idum, total_transactions);
        }
        if(run>= tall){
            Histogram(Hist, moneyBins, agentlist, numberofAgents, numberofBins);
        }
        else{
            Output_M(numberofAgents,agentlist);
        }
        //cumulative histogram?

    }
    ofile.close();
    ofile.open(outfilename);
    //output
    output(Hist, numberofBins, total_runs, tall);



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

void output(double *histogram, int bins, int total_runs, int tall)
{
    double norm = 1/(total_runs-tall);
    for (int bin=0; bin<bins; bin++)
    {
        ofile << setw(15) << setprecision(8) << histogram[bin]*norm << endl;
    }
}


void Output_M(int numberofAgents, double agentlist)
{
    int snittM2 = 0;
for(int i = 0;i < numberofAgents;i++){
    snittM2 += (agentlist[i])*agentlist[i];
}
double norm = 1/numberofAgents;
double variance = snittM2*norm-1;
ofile << setw(15) << setprecision(8) << variance<< endl;
}
