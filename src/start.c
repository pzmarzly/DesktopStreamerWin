#include "functions/common.h"
#include "functions/start.h"

int main(ARGCNV) {
    if (argc > 1) {
        if (strcmp(argv[1], "-h") == 0) {
            ManualForStart();
            return 0;
        } else if (argc % 2 == 0) {
            ErrorInvalidArgAmount();
            return 1;
        }
    }
    Configure();

    WinSockStart();

    TryStopProcess();
    RunProcess();
    PingTheReceiver(argcnv);

    WinSockClose();
    return 0;
}