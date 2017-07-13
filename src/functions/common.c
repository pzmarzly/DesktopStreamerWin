#include "common.h"

void TryStopProcess() {
    TrySend(
        LOCALHOST_L, PROGRAM_CONFIG.LOCAL_CONTROL_PORT,
        "quit",
        PROGRAM_CONFIG.MAX_PING
    );
}
