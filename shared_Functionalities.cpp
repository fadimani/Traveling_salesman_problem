#include <algorithm>
#include <random>
#include <stdio.h>
#include <vector>
#include <cstring>
#include <fstream>
#include "shared_Functionalities.h"



int pathLength(vector<Point> &path) {
    int length = 0;
    for (int i = 0; i < path.size(); i++) {
        length += path[i].dist(path[(i + 1) % path.size()]);
    }
    return length;
}



vector<Point> createRandomPath(int n) {
    vector<Point> path;
    for (int i = 0; i < n; i++) {
        path.push_back(Point(rand() % 1000, rand() % 1000,i));
    }
    return path;
}


vector<Point> readBerlin(){

    vector<Point> path ;

    FILE* fe = fopen ("../berlin52", "r");
    int id,x,y;
    char str[80];
    while (fgets(str, 80, fe) != NULL){
        if (::strcmp(str,"52\n")==0) continue;
        sscanf(str, "%d %d %d", &id, &x, &y);
        path.push_back(Point(x,y,id));
    }
    return path;
}




vector<Point> bestOne (vector<vector<Point>> population){
    std::sort(population.begin(), population.end(), less_than_key());

    return population[0];
}

ofstream myfile ("../berlin52_Solutions.txt");
void printPathTotxt (string pathName, vector<Point> &path){

    myfile << pathName.c_str() << " = [" ;
    for (int i = 0; i < path.size(); i++) {

        if (i < path.size() - 1) {
            myfile << path[i].z  << "->";
        }
        else {
            myfile <<  path[i].z  ;
        }
    }
    myfile << "  ]====> "<<pathLength(path) << "\n\n";
}



void printPath(string pathName, vector<Point> &path) {
    printf("%s = [", pathName.c_str());
    for (int i = 0; i < path.size(); i++) {

        if (i < path.size() - 1) {
//            printf("(%3d,%3d), ", path[i].x, path[i].y);
            printf("(%d), ", path[i].z);
        }
        else {
//            printf("(%3d,%3d)", path[i].x, path[i].y);
            printf("(%d)", path[i].z);
        }
    }
    printf("  ]====>%d;\n",pathLength(path));
}
void printPathShort(string pathName, vector<Point> &path) {
    printf("%s = [", pathName.c_str());
    printf("  ]====>%d;\n",pathLength(path));
}
