#include "disk.h"

void Disk::initialize(double r)
{
    radius = r;
    rSq = r*r;
    halfRsq = rSq/2.0;
    cellRange = getCellRange();
    vecDim = cellRange.size()-1;
    MaxX = getMaxX();
    totalArea = M_PI*rSq;

}

double Disk::integrate(double x1, double x2)
{
    return (0.5 * sqrt(rSq-x2*x2) * x2 * asin(x2/radius)) - (0.5 * sqrt(rSq-x1*x1) * x1 * asin(x1/radius));
}

vector<double> Disk::getCellRange()
{
    vector<double> cellRange;
    cellRange.push_back(0.0);
    for(int i=0; i < radius; i++)
    {
        double x = i + 0.5;
        if (x<radius)
            cellRange.push_back(x);
            cout << x << endl;
    }
    cellRange.push_back(radius);
    return cellRange;
}

double Disk::getMaxX(){
    double maxX = pol2xy(M_PI/4.0).first;
    for (int i=vecDim; i=1; i--){
        if(maxX <= cellRange[i] && maxX > cellRange[i-1])
            return i;
    }
}

pair<double,double> Disk::pol2xy(double theta)
{
    double x = radius*cos(theta);
    double y = radius*sin(theta);
    return make_pair(x,y);
}

double Disk::circle(double &x)
{
    //assert(0<=x && x<=radius);
    return (double)sqrt(radius*radius-x*x);

}

int Disk::getBin(double x){
    for (int i=0; i<vecDim; i++){
        if(x <= i+0.5)
            return i;
    }
}



void Disk::getAreas(int i){
    double x1 = cellRange[i];
    double x2 = cellRange[i+1];
    cout << x1 << x2 << endl;
    do{
        //double x2 = cellRange[i+1];
        double yx1 = circle(x1);
        double yx2 = circle(x2);
        if(getBin(yx1)!=getBin(yx2))
            x2 = circle(cellRange[getBin(yx2)]);
        double A = integrate(x1,x2);
        double y1 = 0.0;
        for(int y=0; y<vecDim; y++)
        {
            double y2 = cellRange[y+1];
            double a = (x2-x1)*(y2-y1);
            if(a<A){
                probMap[make_pair(i,y)] += a;
                //vProb[i][y] += a;
                A -= a;
            }
            else{
                probMap[make_pair(i,y)] += A;
                //vProb[i][y] += A;
                break;
            }
            y1 = y2;
        }
        x1 = x2;
    } while(x2!=cellRange[i+1]);
}

void Disk::getTables(){
    cout << "before get areas" << endl;
    for(int i=0; i<MaxX; i++)
        getAreas(i);
    cout << "AFter get areas" << endl;
    for(int x=MaxX; x<=vecDim; x++){
        for(int y=0; y<vecDim; y++){
            probMap[make_pair(x,y)] = probMap[make_pair(y,x)];
            //vProb[x][y] = vProb[y][x];
        }
    }

    for(int x=0; x<vecDim; x++){
        for(int y=0; y<vecDim; y++){
            double prob = probMap[make_pair(x,y)]/totalArea;
            probMap[make_pair(x,y)] = prob;
            probMap[make_pair(x*-1,y*-1)] += prob;
            probMap[make_pair(x*-1,y)] += prob;
            probMap[make_pair(x,y*-1)] += prob;
            cout << "xy: " << x << " " << y;
            cout << "prob: " << prob << endl;
        }
    }
}




