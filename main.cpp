#include <iostream>
#include "disk.h"
#include "xorshift64.h"
#include <fstream>
#include <string>
using namespace std;

int main()
{
    Disk d;
    float sigma;
    cout << "Sigma: ";
    cin >> sigma;
    ofstream myfile;
    myfile.open("sigma"+to_string(sigma)+".txt");
    d.initialize(2*sigma);
    d.makeTables();
    d.printTables();
    xorshift64 myrand;
    myrand.seed();
    for(int i = 0; i<10000*sigma; i++){
        pair<int,int> xy = d.disperse(myrand.get_uint64());
        myfile << xy.first << " " << xy.second << endl;
    }
    myfile.close();
    return 0;
}
