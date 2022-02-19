#pragma once

#include <stdio.h>
#include <winsock2.h>
#include <iphlpapi.h>

#pragma comment(lib, "IPHLPAPI.lib")

void printAdpaterInfo(PIP_ADAPTER_INFO pAdapter);
int printAdapters();