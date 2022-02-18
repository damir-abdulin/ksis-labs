﻿#include <winsock2.h>
#include <iptypes.h>
#include <iphlpapi.h>
#include <windows.h>
#include <iostream>
#include <stdio.h>

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))

int printAdpaterInfo(PIP_ADAPTER_INFO pAdapter);

/// <summary>
/// Print network adapters MAC-addresses by GetAdaptersInfo()
/// </summary>
int printMacAddress() {
    PIP_ADAPTER_INFO pAdapterInfo;

    ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);
    pAdapterInfo = (IP_ADAPTER_INFO*)MALLOC(sizeof(IP_ADAPTER_INFO));
    if (pAdapterInfo == NULL) {
        printf("Error allocating memory needed to call GetAdaptersInfo\n");
        return 1;
    }

    // Make an initial call to GetAdaptersInfo to get
    // the necessary size into the ulOutBufLen variable
    if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) {
        FREE(pAdapterInfo);
        pAdapterInfo = (IP_ADAPTER_INFO*)MALLOC(ulOutBufLen);
        if (pAdapterInfo == NULL) {
            printf("Error allocating memory needed to call GetAdaptersInfo\n");
            return 1;
        }
    }

    if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == NO_ERROR) {
        while (pAdapterInfo) {
            printAdpaterInfo(pAdapterInfo);

            printf("\n");
            pAdapterInfo = pAdapterInfo->Next;
        }
    }
    else {
        printf("GetAdaptersInfo returns error\n");
        return 1;
    }

    if (pAdapterInfo)
        FREE(pAdapterInfo);

    return 0;
}

int printAdpaterInfo(PIP_ADAPTER_INFO pAdapter) {
    printf("\tAdapter Name: \t%s\n", pAdapter->AdapterName);
    printf("\tAdapter Desc: \t%s\n", pAdapter->Description);
    printf("\tAdapter Addr: \t");
    for (UINT i = 0; i < pAdapter->AddressLength; i++) {
        if (i != (pAdapter->AddressLength - 1))
            printf("%.2X-", (int)pAdapter->Address[i]);
        else
            printf("%.2X\n", (int)pAdapter->Address[i]);
    }

    return 0;
}

int main()
{
    std::cout << "Hello World!\n";
}