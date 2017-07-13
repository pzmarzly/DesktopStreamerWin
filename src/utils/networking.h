#pragma once

#include "macros.h"

#include <stdio.h>
#include <limits.h>

#include <winsock2.h>
#include <iphlpapi.h>

#include <omp.h>

#if DEBUG
    #include <time.h>
#endif

// inetaddr("127.0.0.1") on x86
#define LOCALHOST_L 0x0100007FUL

void WinSockStart();
void WinSockClose();

int TrySend(ZL_ulong IP, ZL_ushort port, ZL_cstring message, ZL_ulong max_ping);
void TryBroadcastNetwork(ZL_ulong start, ZL_ulong len, ZL_ushort port, ZL_cstring message, ZL_ulong max_ping);
void TryBroadcastAllNetworks(ZL_ushort port, ZL_cstring message, ZL_ulong max_ping);
