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
void transaction(double **,double *, int, long&, int, double, double, double, double, double &);
void Histogram(int *, double*, double* , int , int );


int main(int argc, char* argv[])
{
    long idum;
    int  total_runs, numberofAgents, numberofBins, total_transactions, initial_cycles;
    double initialMoney, lambda, gamma, alpha, normalization;

    // Read in output file, abort if there are too few command-line arguments
    if( argc <= 10 ){
        cout << "Bad Usage: " << argv[0] << "\n" << endl;
        cout << "Usage: <./main> <outputfile> <int total number of runs>  <int number of histogram bins> <int number of agents><int initial cycles><int transactions per run><double lambda><double gamma><double alpha><double normalization>" << endl;
        exit(1);
    }
    string outfilename=argv[1];
    total_runs = atoi(argv[2]);
    numberofBins = atoi(argv[3]);
    numberofAgents = atoi(argv[4]);
    initial_cycles= atoi(argv[5]);
    total_transactions = atoi(argv[6]);
    lambda = atof(argv[7]);
    gamma = atof(argv[8]);
    alpha = atof(argv[9]);
    normalization = 1/atof(argv[10]);


    double *moneyBins, *agentlist, **previous_interaction_counter;
    int *Hist;
    moneyBins = new double[numberofBins];
    agentlist = new double[numberofAgents];
    Hist = new int[numberofBins];
    previous_interaction_counter = (double**) matrix(numberofAgents, numberofAgents, sizeof(double));
    for(int y =0; y < numberofAgents; y++) {
            for (int x= 0; x < numberofAgents; x++){
                previous_interaction_counter[y][x] = 0; // spin orientation for the ground state;
            }
        }
    double max = 0.0001;
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
        transaction(previous_interaction_counter,agentlist, numberofAgents, idum, total_transactions, lambda, gamma, alpha,normalization, max);
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
    free_matrix((void **) previous_interaction_counter); // free memory
    ofile.close();  // close output file
    return 0;
}


void transaction(double **previous_interaction_counter,double *agentlist, int agents, long& idum, int total_transactions, double lambda, double gamma, double alpha, double normalization, double &max)
{
    double cash_exchange;
    double normalization_intercounter;
    double transaction_probability;
    for (int i=0; i<total_transactions; i++)
    {
        int agent1 = (int) (ran2(&idum)*(double)agents);
        int agent2 = (int) (ran2(&idum)*(double)agents);
        double transaction_rate = (double) (ran2(&idum));
        if(agent1!=agent2)
        {
            normalization_intercounter = pow(previous_interaction_counter[agent1][agent2] +1,gamma);
            transaction_probability = pow(abs(agentlist[agent1]-agentlist[agent2]),-alpha)*normalization_intercounter*(normalization/max);
            if (transaction_probability>1){
                transaction_probability=1.0;
            }
            double transaction_random = (double) (ran2(&idum));
            if(transaction_random<transaction_probability){
                cash_exchange = (1-lambda)*(transaction_rate*agentlist[agent1]-(1-transaction_rate)*agentlist[agent2]);
                agentlist[agent1]-=cash_exchange;
                agentlist[agent2]+=cash_exchange;
                previous_interaction_counter[agent1][agent2] += 0.01;
                previous_interaction_counter[agent2][agent1] += 0.01;
                normalization_intercounter = pow(previous_interaction_counter[agent1][agent2] +1,gamma);
                if(normalization_intercounter> max){
                    max = normalization_intercounter;
                }
            }
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
