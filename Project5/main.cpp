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
using namespace  std;

ofstream ofile;

// prints to file the results of the calculations
void output(int *,double *, int, int, int);
void Output_M(int , double *);
void transaction_simple(double *, int, long&, int);
void transaction_advanced(double *, int, long&, int);
void Histogram(int *, double*, double* , int , int );


int main(int argc, char* argv[])
{
    long idum;
    int  total_runs, initializationParameter, numberofAgents, numberofBins, total_transactions, initial_cycles;
    double initialMoney;

    // Read in output file, abort if there are too few command-line arguments
    if( argc <= 7 ){
        cout << "Bad Usage: " << argv[0] << "\n" << endl;
        cout << "Usage: <./main> <outputfile> <int initalization type> <int total number of runs>  <int number of histogram bins> <int number of agents><int initial cycles><int transactions per run>" << endl;
        exit(1);
    }
    string outfilename=argv[1];
    initializationParameter = atoi(argv[2]);
    total_runs = atoi(argv[3]);
    numberofBins = atoi(argv[4]);
    numberofAgents = atoi(argv[5]);
    initial_cycles= atoi(argv[6]);
    total_transactions = atoi(argv[7]);

    double *moneyBins, *agentlist;
    int *Hist;
    moneyBins = new double[numberofBins];
    agentlist = new double[numberofAgents];
    Hist = new int[numberofBins];

    initialMoney = 1;
    idum = -1;
    for(int i=0;i<numberofAgents;i++){
        agentlist[i] = initialMoney;
    }

    double step = (double)initialMoney*(double)numberofAgents/(double)numberofBins;
    for (int h = 0; h<numberofBins; h++){
        moneyBins[h] = h*step;
    }

    ofile.open(outfilename+"init");
    //MAIN LOOP
    for ( int run= 0; run<= total_runs; run++){

        if(initializationParameter==0){
            transaction_simple(agentlist, numberofAgents, idum, total_transactions);
        }else if(initializationParameter==1){
            transaction_advanced(agentlist, numberofAgents, idum, total_transactions);
        }
        if(run>= initial_cycles){
            Histogram(Hist, moneyBins, agentlist, numberofAgents, numberofBins);
        }
        else{
            Output_M(numberofAgents,agentlist);
        }

    }
    ofile.close();
    ofile.open(outfilename);
    //output
    output(Hist, moneyBins,numberofBins, total_runs, initial_cycles);



    ofile.close();  // close output file
    return 0;
}


void transaction_simple(double *agentlist, int agents, long& idum, int total_transactions)
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

void transaction_advanced(double *agentlist, int agents, long& idum, int total_transactions)
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

void Histogram(int *Hist, double *moneyBins, double *listofAgents, int numberofAgents, int numberofBins)
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

void output(int *histogram, double *moneyBins,int bins, int total_runs, int tall)
{
    double norm = 1/(double)(total_runs-tall);
    ofile << setiosflags(ios::showpoint | ios::uppercase);
    for (int bin=0; bin<bins; bin++)
    {
        ofile << setw(15) << setprecision(8) << ((double)histogram[bin])*norm;
        ofile << setw(15) << setprecision(8) << moneyBins[bin] << endl;
    }
}


void Output_M(int numberofAgents, double *agentlist)
{
    double snittM2 = 0;
    for(int i = 0;i < numberofAgents;i++){
        snittM2 += agentlist[i]*agentlist[i];
    }
    double norm = 1/(double)numberofAgents;
    double variance = snittM2*norm-1.0;
    ofile << setw(15) << setprecision(8) << variance<< endl;
}
