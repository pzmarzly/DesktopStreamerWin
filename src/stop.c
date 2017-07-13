#include "functions/common.h"

int main(ARGCNV) {
    if (argc == 2 && strcmp(argv[1], "-h") == 0) {
        ManualForStop(argcnv);
        return 0;
    }
    Configure();

    WinSockStart();

    TryStopProcess();

    WinSockClose();
    return 0;
}