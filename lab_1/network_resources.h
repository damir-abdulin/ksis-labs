#pragma once

#include <winsock2.h>
#include <iptypes.h>
#include <iphlpapi.h>
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <winnetwk.h>

#pragma comment(lib, "IPHLPAPI.lib")
#pragma comment(lib, "mpr.lib")
#pragma comment(lib, "netapi32.lib")

void NetErrorHandler(DWORD, LPSTR);
void DisplayStruct(LPNETRESOURCE);
BOOL printNetworkResources(LPNETRESOURCE);