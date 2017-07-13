#include "functions/common.h"

int main(ARGCNV) {
    if (argc == 2 && strcmp(argv[1], "-h") == 0) {
        PrintConsts();
        ManualForStop(argc, argv);
        return 0;
    }
    WinSockStart();

    TryStopProcess();

    WinSockClose();
    return 0;
}