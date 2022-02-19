#pragma once

#include <stdio.h>
#include <winsock2.h>
#include <iphlpapi.h>

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))

#pragma comment(lib, "IPHLPAPI.lib")

void printAdpaterInfo(PIP_ADAPTER_INFO pAdapter);
int printAdapters();