#ifndef DISK_H_INCLUDED
#define DISK_H_INCLUDED

#include <math.h>
#include <vector>
#include <map>
#include <iostream>
using namespace std;
typedef pair<int,int> xyCoord;
typedef map<xyCoord, double> pMap;

class Disk
{
private:
    double radius;
    double rSq;
    double halfRsq;
    pMap probMap;
    vector<double> cellRange;
    double MaxX;
    double totalArea;
    int vecDim;

    double integrate(double x1, double x2);
    vector<double> getCellRange();
    double getMaxX();
    pair<double,double> pol2xy(double theta);
    double circle(double &x);
    int getBin(double x);
    void getAreas(int i);



public:
    void initialize(double r);
    void getTables();

};

#endif // DISK_H_INCLUDED
