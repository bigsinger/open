// wsock32.cpp : 定义 DLL 应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>

#pragma comment(linker,"/align:4096") //减小文件大小


#pragma comment(linker, "/EXPORT:accept=ws2_32.accept,@1")
#pragma comment(linker, "/EXPORT:bind=ws2_32.bind,@2")
#pragma comment(linker, "/EXPORT:closesocket=ws2_32.closesocket,@3")
#pragma comment(linker, "/EXPORT:connect=ws2_32.connect,@4")
#pragma comment(linker, "/EXPORT:getpeername=ws2_32.getpeername,@5")
#pragma comment(linker, "/EXPORT:getsockname=ws2_32.getsockname,@6")
#pragma comment(linker, "/EXPORT:getsockopt=ws2_32.getsockopt,@7")
#pragma comment(linker, "/EXPORT:htonl=ws2_32.htonl,@8")
#pragma comment(linker, "/EXPORT:htons=ws2_32.htons,@9")
#pragma comment(linker, "/EXPORT:inet_addr=ws2_32.inet_addr,@10")
#pragma comment(linker, "/EXPORT:inet_ntoa=ws2_32.inet_ntoa,@11")
#pragma comment(linker, "/EXPORT:ioctlsocket=ws2_32.ioctlsocket,@12")
#pragma comment(linker, "/EXPORT:listen=ws2_32.listen,@13")
#pragma comment(linker, "/EXPORT:ntohl=ws2_32.ntohl,@14")
#pragma comment(linker, "/EXPORT:ntohs=ws2_32.ntohs,@15")
#pragma comment(linker,"/export:recv=_recv@16,@16")
#pragma comment(linker,"/export:recvfrom=_recvfrom@24,@17")
#pragma comment(linker,"/export:select=ws2_32.select,@18")
#pragma comment(linker,"/export:send=_send@16,@19")
#pragma comment(linker,"/export:sendto=_sendto@24,@20")
#pragma comment(linker, "/EXPORT:setsockopt=ws2_32.setsockopt,@21")
#pragma comment(linker, "/EXPORT:shutdown=ws2_32.shutdown,@22")
#pragma comment(linker, "/EXPORT:socket=ws2_32.socket,@23")

#pragma comment(linker, "/EXPORT:MigrateWinsockConfiguration=MSWSOCK.MigrateWinsockConfiguration,@24")

#pragma comment(linker, "/EXPORT:gethostbyaddr=ws2_32.gethostbyaddr,@51")
#pragma comment(linker, "/EXPORT:gethostbyname=ws2_32.gethostbyname,@52")
#pragma comment(linker, "/EXPORT:getprotobyname=ws2_32.getprotobyname,@53")
#pragma comment(linker, "/EXPORT:getprotobynumber=ws2_32.getprotobynumber,@54")
#pragma comment(linker, "/EXPORT:getservbyname=ws2_32.getservbyname,@55")
#pragma comment(linker, "/EXPORT:getservbyport=ws2_32.getservbyport,@56")
#pragma comment(linker, "/EXPORT:gethostname=ws2_32.gethostname,@57")
#pragma comment(linker, "/EXPORT:WSAAsyncSelect=ws2_32.WSAAsyncSelect,@101")
#pragma comment(linker, "/EXPORT:WSAAsyncGetHostByAddr=ws2_32.WSAAsyncGetHostByAddr,@102")
#pragma comment(linker, "/EXPORT:WSAAsyncGetHostByName=ws2_32.WSAAsyncGetHostByName,@103")
#pragma comment(linker, "/EXPORT:WSAAsyncGetProtoByNumber=ws2_32.WSAAsyncGetProtoByNumber,@104")
#pragma comment(linker, "/EXPORT:WSAAsyncGetProtoByName=ws2_32.WSAAsyncGetProtoByName,@105")
#pragma comment(linker, "/EXPORT:WSAAsyncGetServByPort=ws2_32.WSAAsyncGetServByPort,@106")
#pragma comment(linker, "/EXPORT:WSAAsyncGetServByName=ws2_32.WSAAsyncGetServByName,@107")
#pragma comment(linker, "/EXPORT:WSACancelAsyncRequest=ws2_32.WSACancelAsyncRequest,@108")
#pragma comment(linker, "/EXPORT:WSASetBlockingHook=ws2_32.WSASetBlockingHook,@109")
#pragma comment(linker, "/EXPORT:WSAUnhookBlockingHook=ws2_32.WSAUnhookBlockingHook,@110")
#pragma comment(linker, "/EXPORT:WSAGetLastError=ws2_32.WSAGetLastError,@111")
#pragma comment(linker, "/EXPORT:WSASetLastError=ws2_32.WSASetLastError,@112")
#pragma comment(linker, "/EXPORT:WSACancelBlockingCall=ws2_32.WSACancelBlockingCall,@113")
#pragma comment(linker, "/EXPORT:WSAIsBlocking=ws2_32.WSAIsBlocking,@114")
#pragma comment(linker, "/EXPORT:WSAStartup=ws2_32.WSAStartup,@115")
#pragma comment(linker, "/EXPORT:WSACleanup=ws2_32.WSACleanup,@116")
#pragma comment(linker, "/EXPORT:__WSAFDIsSet=ws2_32.__WSAFDIsSet,@151")
#pragma comment(linker, "/EXPORT:WEP=ws2_32.WEP,@500")
#pragma comment(linker, "/EXPORT:WSApSetPostRoutine=ws2_32.WSApSetPostRoutine,@1000")

#pragma comment(linker, "/EXPORT:inet_network=MSWSOCK.inet_network,@1100")
#pragma comment(linker, "/EXPORT:getnetbyname=MSWSOCK.getnetbyname,@1101")
#pragma comment(linker, "/EXPORT:rcmd=MSWSOCK.rcmd,@1102")
#pragma comment(linker, "/EXPORT:rexec=MSWSOCK.rexec,@1103")
#pragma comment(linker, "/EXPORT:rresvport=MSWSOCK.rresvport,@1104")
#pragma comment(linker, "/EXPORT:sethostname=MSWSOCK.sethostname,@1105")
#pragma comment(linker, "/EXPORT:dn_expand=MSWSOCK.dn_expand,@1106")
#pragma comment(linker, "/EXPORT:WSARecvEx=MSWSOCK.WSARecvEx,@1107")
#pragma comment(linker, "/EXPORT:s_perror=MSWSOCK.s_perror,@1108")
#pragma comment(linker, "/EXPORT:GetAddressByNameA=MSWSOCK.GetAddressByNameA,@1109")
#pragma comment(linker, "/EXPORT:GetAddressByNameW=MSWSOCK.GetAddressByNameW,@1110")
#pragma comment(linker, "/EXPORT:EnumProtocolsA=MSWSOCK.EnumProtocolsA,@1111")
#pragma comment(linker, "/EXPORT:EnumProtocolsW=MSWSOCK.EnumProtocolsW,@1112")
#pragma comment(linker, "/EXPORT:GetTypeByNameA=MSWSOCK.GetTypeByNameA,@1113")
#pragma comment(linker, "/EXPORT:GetTypeByNameW=MSWSOCK.GetTypeByNameW,@1114")
#pragma comment(linker, "/EXPORT:GetNameByTypeA=MSWSOCK.GetNameByTypeA,@1115")
#pragma comment(linker, "/EXPORT:GetNameByTypeW=MSWSOCK.GetNameByTypeW,@1116")
#pragma comment(linker, "/EXPORT:SetServiceA=MSWSOCK.SetServiceA,@1117")
#pragma comment(linker, "/EXPORT:SetServiceW=MSWSOCK.SetServiceW,@1118")
#pragma comment(linker, "/EXPORT:GetServiceA=MSWSOCK.GetServiceA,@1119")
#pragma comment(linker, "/EXPORT:GetServiceW=MSWSOCK.GetServiceW,@1120")
#pragma comment(linker, "/EXPORT:NPLoadNameSpaces=MSWSOCK.NPLoadNameSpaces,@1130")
#pragma comment(linker, "/EXPORT:TransmitFile=MSWSOCK.TransmitFile,@1140")
#pragma comment(linker, "/EXPORT:AcceptEx=MSWSOCK.AcceptEx,@1141")
#pragma comment(linker, "/EXPORT:GetAcceptExSockaddrs=MSWSOCK.GetAcceptExSockaddrs,@1142")




#define MINPACKETLEN 0
#define MAXPACKETLEN 1024

typedef int (WINAPI* PFUN)(int s, const char* buf, int len, int flags);
typedef int (WINAPI* PFUN2)(int s, char* buf, int len, int flags, int to, int tolen);

PFUN oldSend, oldRecv;
PFUN2 oldSendto, oldRecvfrom;

void Log(char* tag, int socket, char* buffer, int len);



#ifdef _MANAGED
#pragma managed(push, off)
#endif

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  dwReason, LPVOID lpReserved) {
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		OutputDebugString(L"[wsock32]DLL_PROCESS_ATTACH");
		{
			HMODULE hws2_32 = LoadLibrary(L"ws2_32.dll");	//ws2_32
			if (hws2_32) {
				oldSend = (PFUN)GetProcAddress(hws2_32, "send");
				oldRecv = (PFUN)GetProcAddress(hws2_32, "recv");
				oldSendto = (PFUN2)GetProcAddress(hws2_32, "sendto");
				oldRecvfrom = (PFUN2)GetProcAddress(hws2_32, "recvfrom");
			}
		}
		break;
	case DLL_PROCESS_DETACH:
		OutputDebugString(L"[wsock32]DLL_PROCESS_DETACH");
		break;
	}
	return TRUE;
}


extern "C" __declspec(dllexport) int WINAPI send(int s, char* buf, int len, int flags) {
	Log("send", s, buf, len);
	return oldSend(s, buf, len, flags);
}
extern "C" __declspec(dllexport) int WINAPI sendto(int s, char* buf, int len, int flags, int to, int tolen) {
	Log("sendto", s, buf, len);
	return oldSendto(s, buf, len, flags, to, tolen);
}
extern "C" __declspec(dllexport) int WINAPI recv(int s, char* buf, int len, int flags) {
	Log("recv", s, buf, len);
	return oldRecv(s, buf, len, flags);
}
extern "C" __declspec(dllexport) int WINAPI recvfrom(int s, char* buf, int len, int flags, int from, int fromlen) {
	Log("recvfrom", s, buf, len);
	return oldRecvfrom(s, buf, len, flags, from, fromlen);
}

void Log(char * tag, int socket, char* buffer, int len) {
	char msg[MAXPACKETLEN];
	int size = len >= MAXPACKETLEN ? MAXPACKETLEN - 2 : len;
	memcpy(msg, buffer, size);
	msg[size] = '\0';

	char text[0x2000];
	sprintf_s(text, "[wsock32]%s socket: %d len: %d buff: %s", tag, socket, len, msg);
	OutputDebugStringA(text);
}


#ifdef _MANAGED
#pragma managed(pop)
#endif

