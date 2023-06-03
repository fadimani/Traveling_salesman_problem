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

// Perform a 2-opt swap
void swap2opt(vector<Point> &path, int i, int j) {
    reverse(begin(path) + i + 1, begin(path) + j + 1);
}

int main() {
//    vector<Point> path = createRandomPath(7);
//    vector<Point> path{Point(93 ,312,0),Point(53 ,182,2),Point(133,217,3),Point(19 ,216,1)};
    vector<Point> path = readBerlin();
//    vector<Point> path{Point(93 ,312,0),Point(133,217,3),Point(282,129,4),Point(185,285,5),Point(19 ,216,1),Point(53 ,182,2),Point(141,281,6)};

    //      path here is the initial solution
    printPath("initial solution ", path);

    // copy path into tempPath
    vector<Point> tempPath;
    for (int i=0; i<path.size(); i++) { tempPath.push_back(path[i]); }

    int curLength = pathLength(path);

    int n = path.size();

    vector<vector<Point>> neighbours;

    bool foundImprovement = true;
    while (foundImprovement) {
        foundImprovement = false;

        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n ; j++) {
                swap2opt(tempPath, i, j);
                neighbours.push_back(tempPath);
                tempPath.clear();
                for (int i=0; i<path.size(); i++) { tempPath.push_back(path[i]); }
            }
        }
        vector<Point> daBest = bestOne(neighbours);
        if (pathLength(daBest) < curLength) {         //// better neighbor found
            curLength = pathLength(daBest);
            path.clear();
            for (int i=0; i<daBest.size(); i++) { path.push_back(daBest[i]); }
            tempPath.clear();
            for (int i=0; i<daBest.size(); i++) { tempPath.push_back(daBest[i]); }
            foundImprovement = true;
//            ::printf("found dabest: %d\n", pathLength(daBest));
            printPathShort("found better:",path);
        }
    }

    printPath("local maxima ", path);
    return 0;
}