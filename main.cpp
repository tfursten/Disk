#include <iostream>
#include "disk.h"
using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    Disk d;
    d.initialize(.1);
    d.getTables();
    d.printTables();
    return 0;
}
