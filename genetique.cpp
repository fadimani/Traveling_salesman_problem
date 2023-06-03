//
// Created by imani on 10-Apr-23.
//


#include <algorithm>
#include <random>
#include <stdio.h>
#include <vector>
#include <cstring>
#include <fstream>
#include "shared_Functionalities.h"
using namespace std;

//!####################  PARAMETERS
int population_NB = 100;             // make it big or our model will face premature convergence
const double max_generations = 1000;        // 1000 seems good
const double mutation_rate = 0.6;         //
string selection_strategy_parent1 = "elitism";          //  "elitism" or "roulette"  or "random"
string selection_strategy_parent2 = "roulette";
string mutation_strategy = "2optSwap";              //  "2optSwap" or "singleSwap"
bool population_grows_through_time = false;              // true or false



bool cmp(Individual a,Individual& b){
    return pathLength(a) < pathLength(b);
}
Individual selection(Population population,const string& option){
    if (option=="random"){
        int r = rand() % population_NB;
        return population[r];
    }
    if (option=="roulette"){
        double total_fitness = 0;
        for (int i = 0; i < population_NB; ++i) {
            total_fitness+=pathLength(population[i]);
        }
        double r = rand() / (double)RAND_MAX * total_fitness;
        double partial_sum = 0.0;
        for (int i = 0; i < population_NB; i++) {
            partial_sum += pathLength(population[i]);

            if (partial_sum >= r) {
                return population[i];
            }

        }
        return population[population_NB - 1];
    }
    if (option=="elitism"){
        std::sort(population.begin(), population.end(),cmp);
        Individual besto = population[0];
        population.erase(population.begin());
        return besto;
    }
    return population[0];
}

Individual crossover(Individual x, Individual y){
    Individual child(x.size());

    int index1 = rand() % (x.size()-1) ;        // [0,51]
    int index2 = rand() % (x.size()-1) ;
    int startIndex = min(index1,index2);
    int endIndex = max(index1,index2);

    vector<int> takenCities_ids;

    // Copy crossover part
    for (int i = startIndex; i <= endIndex; i++) {
        child[i] = x[i];
        takenCities_ids.push_back(x[i].z);
    }

    // Fill in the remaining genes from parent 2 in the order they appear
    int j = 0;
    for (int i = 0; i < x.size(); i++) {
        if (j == startIndex) {
            j = endIndex + 1;
        }

        if (find(takenCities_ids.begin(), takenCities_ids.end(), y[i].z) == takenCities_ids.end()) {
            child[j] = y[i];
            j++;
        }
    }
    return child;
}


void mutation(Individual &x, string option){
    int index1 = rand() % (x.size()-1) ;
    int index2 = rand() % (x.size()-1) ;

    if (option == "singleSwap"){

        std::swap(x[index1],x[index2]);
    }
    if (option == "2optSwap"){
        reverse(begin(x) + index1 + 1, begin(x) + index2 + 1);
    }

}


int averagePopulationFitness (Population population){
    int total = 0;
    for (int i = 0; i < population_NB; ++i) {
        total+=pathLength(population[i]);
    }
    int trueAvg = (int) total/population_NB;
    return trueAvg;
}

int main() {
    ofstream myfile;


    srand(time(0));

    Individual adam = readBerlin();

//    Individual adam =  createRandomPath(7);

    Population pop ;
    Population new_pop;

    // generating initial population
    for (int i = 0; i < population_NB; ++i) {
        std::random_shuffle ( adam.begin(), adam.end() );
        pop.push_back(adam);
    }



    int g =0;
    while (g<max_generations){
        //// for new population initialisation
        new_pop.clear();
        ::printf("GENERATION %d (p:%d)\n",g+1,population_NB);
        for (int p = 0; p < population_NB; ++p) {
            Individual x = selection(pop,selection_strategy_parent1);         //  random, roulette or elitism
            Individual y  = selection(pop,selection_strategy_parent2);
            Individual child = crossover(x,y);
            float nb = (float) rand()/RAND_MAX;
            if (nb<=mutation_rate) mutation(child,mutation_strategy);
            new_pop.push_back(child);
        }
        pop.clear();
        for (int y = 0; y < new_pop.size(); ++y) {
            pop.push_back(new_pop[y]);
        }
        ::printf("best one in this generation (average is %d):", averagePopulationFitness(pop));
        Individual best = bestOne(pop);
        pop.push_back(best);

        if (population_grows_through_time) population_NB++;

        printPathShort("best:",best);
        printPathTotxt("best:",best);


        g++;
    }




    return 0;
}
