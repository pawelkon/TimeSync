#include "timesync.h"

int main(int argc, char *argv[])
{
    ts::TimeSync ts(argc, argv);
    ts.start();

    return ts.retMain();
}
