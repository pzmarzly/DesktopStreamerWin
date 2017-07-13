#pragma once

#include "../utils/macros.h"
#include "../utils/networking.h"
#include "../config.h"

#include <process.h>

void PingTheReceiverAllNetworks();
void PingTheReceiverSingleNetwork(ZL_cstring start, ZL_ulong length);
void PingTheReceiver(ARGCNV);
void RunProcess();
