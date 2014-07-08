#include <iostream>
#include "disk.h"
using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    Disk d;
    d.initialize(2.0);
    d.getTables();
    return 0;
}
