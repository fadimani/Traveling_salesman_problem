//
// Created by imani on 01-May-23.
//
#include <algorithm>
#include <random>
#include <stdio.h>
#include <vector>
#include <cstring>
using namespace std;



class Point {
public:
    int x, y,z;

    Point(int x, int y,int z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    Point() {
        this->x = 0;
        this->y = 0;
    }

    // Distance between two points squared
    int dist2(const Point &other){
        return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y);
    }

    int dist(const Point &other){
        double rij = ::sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
        return ::round(rij) ;    }
};

typedef vector<Point> Individual;
typedef vector<vector<Point>> Population;

int pathLength(vector<Point> &path);
void printPath(string pathName, vector<Point> &path);
void printPathShort(string pathName, vector<Point> &path);
vector<Point> createRandomPath(int n);
vector<Point> readBerlin();

struct less_than_key
{
    inline bool operator() (vector<Point>& x, vector<Point>& y)
    {
        return (pathLength(x) < pathLength(y));
    }
};
vector<Point> bestOne (vector<vector<Point>> population);
void printPathTotxt (string pathName, vector<Point> &path);





