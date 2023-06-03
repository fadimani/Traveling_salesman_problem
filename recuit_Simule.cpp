//
// Created by imani on 10-Apr-23.
//

#include <algorithm>
#include <random>
#include <stdio.h>
#include <vector>
#include <cstring>
#include "shared_Functionalities.h"


using namespace std;

const double initial_temperature = 10000;
const double cooling_factor = 0.99;
const double stop_temperature = 0.01;
const int max_iterations = 1000;  //676
const int n = 52;




int main() {
    srand( (unsigned)time( NULL ) );

    vector<Point> path = readBerlin() ;

    std::random_shuffle ( path.begin(), path.end() );


    // this is the initial state. the cities by order
    printPath("path1: ", path);



    vector<Point> currentPath;
    for (int j=0; j<path.size(); j++) { currentPath.push_back(path[j]); }

    double current_temperature = initial_temperature;

    while (current_temperature > stop_temperature ){
        for (int i = 0; i < max_iterations; ++i) {

            // cost for current path
            double old_cost = pathLength(currentPath);

            //generate new path
            std::random_shuffle ( path.begin(), path.end() );

            //cost of new path
            double new_cost = pathLength(path);

            double dE =  new_cost - old_cost;

            if (new_cost < old_cost){       // same as if dE < 0    meaning we found an improvement
                currentPath.clear();
                for (int k=0; k<path.size(); k++) { currentPath.push_back(path[k]); }


            } else{                         // this is a supposedly "bad" move
                float nb = (float) rand()/RAND_MAX;
                float p = exp((-dE) / current_temperature);
                if (nb<=p){
                    currentPath.clear();
                    for (int l=0; l<path.size(); l++) { currentPath.push_back(path[l]); }

                }
            }


        }

        current_temperature*=cooling_factor;

    }


    ::printf("\n\n");
    printPath("solution : ", currentPath);

    return 0;
}