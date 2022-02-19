#include "network_resources.h"

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))

BOOL printAllDevices(LPNETRESOURCE lpnr) {
    DWORD dwResult;
    HANDLE hEnum;
    DWORD cbBuffSize = 16384;
    DWORD cEntries = 0xFFFFFFFF;

    dwResult = WNetOpenEnum(RESOURCE_GLOBALNET, RESOURCETYPE_ANY, 0, lpnr, &hEnum);

    if (dwResult != NO_ERROR) {
        NetErrorHandler(dwResult, (LPSTR)"WNetOpenEnum");
        return FALSE;
    }

    LPNETRESOURCE lpLocalResource = (LPNETRESOURCE)MALLOC(cbBuffSize);


    do {
        ZeroMemory(lpLocalResource, cbBuffSize);
        dwResult = WNetEnumResource(hEnum, &cEntries, lpLocalResource, &cbBuffSize);

        if (dwResult == NO_ERROR) {
            for (int i = 0; i < cEntries; i++)
                DisplayStruct(i, &lpLocalResource[i]);


        }
        else if (dwResult != ERROR_NO_MORE_ITEMS) {
            NetErrorHandler(dwResult, (LPSTR)"WNetEnumResource");
            break;
        }
    } while (dwResult != ERROR_NO_MORE_ITEMS);

    FREE(lpLocalResource);

    dwResult = WNetCloseEnum(hEnum);

    if (dwResult != NO_ERROR) {
        NetErrorHandler(dwResult, (LPSTR)"WNetCloseEnum");
        return FALSE;
    }

    return TRUE;
}


void NetErrorHandler(DWORD errorNum, LPSTR funcName) {
    printf("[%s][ERROR:%d] ", funcName, errorNum);

    switch (errorNum) {
    case ERROR_NOT_CONTAINER:
        printf("ERROR_NOT_CONTAINER\n");
        break;
    case ERROR_INVALID_PARAMETER:
        printf("ERROR_INVALID_PARAMETER\n");
        break;

    case ERROR_NO_NETWORK:
        printf("ERROR_NO_NETWORK\n");
        break;

    default:
        printf("UNKNOW_ERROR\n");
    }
}

void DisplayStruct(int i, LPNETRESOURCE lpnrLocal)
{
    printf("\tScope: ");
    switch (lpnrLocal->dwScope) {
    case (RESOURCE_CONNECTED):
        printf("connected\n");
        break;
    case (RESOURCE_GLOBALNET):
        printf("all resources\n");
        break;
    case (RESOURCE_REMEMBERED):
        printf("remembered\n");
        break;
    default:
        printf("unknown scope %d\n", lpnrLocal->dwScope);
        break;
    }

    printf("\tType: ");
    switch (lpnrLocal->dwType) {
    case (RESOURCETYPE_ANY):
        printf("any\n");
        break;
    case (RESOURCETYPE_DISK):
        printf("disk\n");
        break;
    case (RESOURCETYPE_PRINT):
        printf("print\n");
        break;
    default:
        printf("unknown type %d\n", lpnrLocal->dwType);
        break;
    }

    printf("\tDisplayType: ", i);
    switch (lpnrLocal->dwDisplayType) {
    case (RESOURCEDISPLAYTYPE_GENERIC):
        printf("generic\n");
        break;
    case (RESOURCEDISPLAYTYPE_DOMAIN):
        printf("domain\n");
        break;
    case (RESOURCEDISPLAYTYPE_SERVER):
        printf("server\n");
        break;
    case (RESOURCEDISPLAYTYPE_SHARE):
        printf("share\n");
        break;
    case (RESOURCEDISPLAYTYPE_FILE):
        printf("file\n");
        break;
    case (RESOURCEDISPLAYTYPE_GROUP):
        printf("group\n");
        break;
    case (RESOURCEDISPLAYTYPE_NETWORK):
        printf("network\n");
        break;
    default:
        printf("unknown display type %d\n", lpnrLocal->dwDisplayType);
        break;
    }

    printf("\tUsage: 0x%x = ", lpnrLocal->dwUsage);
    if (lpnrLocal->dwUsage & RESOURCEUSAGE_CONNECTABLE)
        printf("connectable ");
    if (lpnrLocal->dwUsage & RESOURCEUSAGE_CONTAINER)
        printf("container ");
    printf("\n");

    printf("\tLocalname: %S\n", lpnrLocal->lpLocalName);
    printf("\tRemotename: %S\n", lpnrLocal->lpRemoteName);
    printf("\tComment: %S\n", lpnrLocal->lpComment);
    printf("\tProvider: %S\n", lpnrLocal->lpProvider);
    printf("\n");
}
