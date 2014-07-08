#include <iostream>
#include "disk.h"
#include "xorshift64.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    Disk d;
    d.initialize(4);
    d.makeTables();
    d.printTables();
    xorshift64 myrand;
    myrand.seed(232598465165);
    for(int i = 0; i<50; i++){
        pair<int,int> xy = d.disperse(myrand.get_uint64());
        cout << xy.first << " " << xy.second << endl;
    }
    return 0;
}
