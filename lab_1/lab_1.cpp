#include <stdio.h>

#include "MAC_address.h"
#include "network_resources.h"

int main()
{
    printf("Get Adapters MAC addresses:\n");
    printAdapters();

    printf("Enumerate network resources");
    LPNETRESOURCE lpnr = NULL;
    printAllDevices(lpnr);
}

