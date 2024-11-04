// ws2_32.cpp : 定义 DLL 应用程序的入口点。
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
#pragma comment(linker, "/EXPORT:ioctlsocket=ws2_32.ioctlsocket,@10")
#pragma comment(linker, "/EXPORT:inet_addr=ws2_32.inet_addr,@11")
#pragma comment(linker, "/EXPORT:inet_ntoa=ws2_32.inet_ntoa,@12")
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
#pragma comment(linker, "/EXPORT:WSApSetPostRoutine=ws2_32.WSApSetPostRoutine,@24")
#pragma comment(linker, "/EXPORT:FreeAddrInfoEx=ws2_32.FreeAddrInfoEx,@25")
#pragma comment(linker, "/EXPORT:FreeAddrInfoExW=ws2_32.FreeAddrInfoExW,@26")
#pragma comment(linker, "/EXPORT:FreeAddrInfoW=ws2_32.FreeAddrInfoW,@27")
#pragma comment(linker, "/EXPORT:GetAddrInfoExA=ws2_32.GetAddrInfoExA,@28")
#pragma comment(linker, "/EXPORT:GetAddrInfoExCancel=ws2_32.GetAddrInfoExCancel,@29")
#pragma comment(linker, "/EXPORT:GetAddrInfoExOverlappedResult=ws2_32.GetAddrInfoExOverlappedResult,@30")
#pragma comment(linker, "/EXPORT:GetAddrInfoExW=ws2_32.GetAddrInfoExW,@31")
#pragma comment(linker, "/EXPORT:GetAddrInfoW=ws2_32.GetAddrInfoW,@32")
#pragma comment(linker, "/EXPORT:GetHostNameW=ws2_32.GetHostNameW,@33")
#pragma comment(linker, "/EXPORT:GetNameInfoW=ws2_32.GetNameInfoW,@34")
#pragma comment(linker, "/EXPORT:InetNtopW=ws2_32.InetNtopW,@35")
#pragma comment(linker, "/EXPORT:InetPtonW=ws2_32.InetPtonW,@36")
#pragma comment(linker, "/EXPORT:SetAddrInfoExA=ws2_32.SetAddrInfoExA,@37")
#pragma comment(linker, "/EXPORT:SetAddrInfoExW=ws2_32.SetAddrInfoExW,@38")
#pragma comment(linker, "/EXPORT:WPUCompleteOverlappedRequest=ws2_32.WPUCompleteOverlappedRequest,@39")
#pragma comment(linker, "/EXPORT:WPUGetProviderPathEx=ws2_32.WPUGetProviderPathEx,@40")
#pragma comment(linker, "/EXPORT:WSAAccept=ws2_32.WSAAccept,@41")
#pragma comment(linker, "/EXPORT:WSAAddressToStringA=ws2_32.WSAAddressToStringA,@42")
#pragma comment(linker, "/EXPORT:WSAAddressToStringW=ws2_32.WSAAddressToStringW,@43")
#pragma comment(linker, "/EXPORT:WSAAdvertiseProvider=ws2_32.WSAAdvertiseProvider,@44")
#pragma comment(linker, "/EXPORT:WSACloseEvent=ws2_32.WSACloseEvent,@45")
#pragma comment(linker, "/EXPORT:WSAConnect=ws2_32.WSAConnect,@46")
#pragma comment(linker, "/EXPORT:WSAConnectByList=ws2_32.WSAConnectByList,@47")
#pragma comment(linker, "/EXPORT:WSAConnectByNameA=ws2_32.WSAConnectByNameA,@48")
#pragma comment(linker, "/EXPORT:WSAConnectByNameW=ws2_32.WSAConnectByNameW,@49")
#pragma comment(linker, "/EXPORT:WSACreateEvent=ws2_32.WSACreateEvent,@50")
#pragma comment(linker, "/EXPORT:gethostbyaddr=ws2_32.gethostbyaddr,@51")
#pragma comment(linker, "/EXPORT:gethostbyname=ws2_32.gethostbyname,@52")
#pragma comment(linker, "/EXPORT:getprotobyname=ws2_32.getprotobyname,@53")
#pragma comment(linker, "/EXPORT:getprotobynumber=ws2_32.getprotobynumber,@54")
#pragma comment(linker, "/EXPORT:getservbyname=ws2_32.getservbyname,@55")
#pragma comment(linker, "/EXPORT:getservbyport=ws2_32.getservbyport,@56")
#pragma comment(linker, "/EXPORT:gethostname=ws2_32.gethostname,@57")
#pragma comment(linker, "/EXPORT:WSADuplicateSocketA=ws2_32.WSADuplicateSocketA,@58")
#pragma comment(linker, "/EXPORT:WSADuplicateSocketW=ws2_32.WSADuplicateSocketW,@59")
#pragma comment(linker, "/EXPORT:WSAEnumNameSpaceProvidersA=ws2_32.WSAEnumNameSpaceProvidersA,@60")
#pragma comment(linker, "/EXPORT:WSAEnumNameSpaceProvidersExA=ws2_32.WSAEnumNameSpaceProvidersExA,@61")
#pragma comment(linker, "/EXPORT:WSAEnumNameSpaceProvidersExW=ws2_32.WSAEnumNameSpaceProvidersExW,@62")
#pragma comment(linker, "/EXPORT:WSAEnumNameSpaceProvidersW=ws2_32.WSAEnumNameSpaceProvidersW,@63")
#pragma comment(linker, "/EXPORT:WSAEnumNetworkEvents=ws2_32.WSAEnumNetworkEvents,@64")
#pragma comment(linker, "/EXPORT:WSAEnumProtocolsA=ws2_32.WSAEnumProtocolsA,@65")
#pragma comment(linker, "/EXPORT:WSAEnumProtocolsW=ws2_32.WSAEnumProtocolsW,@66")
#pragma comment(linker, "/EXPORT:WSAEventSelect=ws2_32.WSAEventSelect,@67")
#pragma comment(linker, "/EXPORT:WSAGetOverlappedResult=ws2_32.WSAGetOverlappedResult,@68")
#pragma comment(linker, "/EXPORT:WSAGetQOSByName=ws2_32.WSAGetQOSByName,@69")
#pragma comment(linker, "/EXPORT:WSAGetServiceClassInfoA=ws2_32.WSAGetServiceClassInfoA,@70")
#pragma comment(linker, "/EXPORT:WSAGetServiceClassInfoW=ws2_32.WSAGetServiceClassInfoW,@71")
#pragma comment(linker, "/EXPORT:WSAGetServiceClassNameByClassIdA=ws2_32.WSAGetServiceClassNameByClassIdA,@72")
#pragma comment(linker, "/EXPORT:WSAGetServiceClassNameByClassIdW=ws2_32.WSAGetServiceClassNameByClassIdW,@73")
#pragma comment(linker, "/EXPORT:WSAHtonl=ws2_32.WSAHtonl,@74")
#pragma comment(linker, "/EXPORT:WSAHtons=ws2_32.WSAHtons,@75")
#pragma comment(linker, "/EXPORT:WSAInstallServiceClassA=ws2_32.WSAInstallServiceClassA,@76")
#pragma comment(linker, "/EXPORT:WSAInstallServiceClassW=ws2_32.WSAInstallServiceClassW,@77")
#pragma comment(linker, "/EXPORT:WSAIoctl=ws2_32.WSAIoctl,@78")
#pragma comment(linker, "/EXPORT:WSAJoinLeaf=ws2_32.WSAJoinLeaf,@79")
#pragma comment(linker, "/EXPORT:WSALookupServiceBeginA=ws2_32.WSALookupServiceBeginA,@80")
#pragma comment(linker, "/EXPORT:WSALookupServiceBeginW=ws2_32.WSALookupServiceBeginW,@81")
#pragma comment(linker, "/EXPORT:WSALookupServiceEnd=ws2_32.WSALookupServiceEnd,@82")
#pragma comment(linker, "/EXPORT:WSALookupServiceNextA=ws2_32.WSALookupServiceNextA,@83")
#pragma comment(linker, "/EXPORT:WSALookupServiceNextW=ws2_32.WSALookupServiceNextW,@84")
#pragma comment(linker, "/EXPORT:WSANSPIoctl=ws2_32.WSANSPIoctl,@85")
#pragma comment(linker, "/EXPORT:WSANtohl=ws2_32.WSANtohl,@86")
#pragma comment(linker, "/EXPORT:WSANtohs=ws2_32.WSANtohs,@87")
#pragma comment(linker, "/EXPORT:WSAPoll=ws2_32.WSAPoll,@88")
#pragma comment(linker, "/EXPORT:WSAProviderCompleteAsyncCall=ws2_32.WSAProviderCompleteAsyncCall,@89")
#pragma comment(linker, "/EXPORT:WSAProviderConfigChange=ws2_32.WSAProviderConfigChange,@90")
#pragma comment(linker, "/EXPORT:WSARecv=ws2_32.WSARecv,@91")
#pragma comment(linker, "/EXPORT:WSARecvDisconnect=ws2_32.WSARecvDisconnect,@92")
#pragma comment(linker, "/EXPORT:WSARecvFrom=ws2_32.WSARecvFrom,@93")
#pragma comment(linker, "/EXPORT:WSARemoveServiceClass=ws2_32.WSARemoveServiceClass,@94")
#pragma comment(linker, "/EXPORT:WSAResetEvent=ws2_32.WSAResetEvent,@95")
#pragma comment(linker, "/EXPORT:WSASend=ws2_32.WSASend,@96")
#pragma comment(linker, "/EXPORT:WSASendDisconnect=ws2_32.WSASendDisconnect,@97")
#pragma comment(linker, "/EXPORT:WSASendMsg=ws2_32.WSASendMsg,@98")
#pragma comment(linker, "/EXPORT:WSASendTo=ws2_32.WSASendTo,@99")
#pragma comment(linker, "/EXPORT:WSASetEvent=ws2_32.WSASetEvent,@100")
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
#pragma comment(linker, "/EXPORT:WSASetServiceA=ws2_32.WSASetServiceA,@117")
#pragma comment(linker, "/EXPORT:WSASetServiceW=ws2_32.WSASetServiceW,@118")
#pragma comment(linker, "/EXPORT:WSASocketA=ws2_32.WSASocketA,@119")
#pragma comment(linker, "/EXPORT:WSASocketW=ws2_32.WSASocketW,@120")
#pragma comment(linker, "/EXPORT:WSAStringToAddressA=ws2_32.WSAStringToAddressA,@121")
#pragma comment(linker, "/EXPORT:WSAStringToAddressW=ws2_32.WSAStringToAddressW,@122")
#pragma comment(linker, "/EXPORT:WSAUnadvertiseProvider=ws2_32.WSAUnadvertiseProvider,@123")
#pragma comment(linker, "/EXPORT:WSAWaitForMultipleEvents=ws2_32.WSAWaitForMultipleEvents,@124")
#pragma comment(linker, "/EXPORT:WSCDeinstallProvider=ws2_32.WSCDeinstallProvider,@125")
#pragma comment(linker, "/EXPORT:WSCDeinstallProvider32=ws2_32.WSCDeinstallProvider32,@126")
#pragma comment(linker, "/EXPORT:WSCDeinstallProviderEx=ws2_32.WSCDeinstallProviderEx,@127")
#pragma comment(linker, "/EXPORT:WSCEnableNSProvider=ws2_32.WSCEnableNSProvider,@128")
#pragma comment(linker, "/EXPORT:WSCEnableNSProvider32=ws2_32.WSCEnableNSProvider32,@129")
#pragma comment(linker, "/EXPORT:WSCEnumNameSpaceProviders32=ws2_32.WSCEnumNameSpaceProviders32,@130")
#pragma comment(linker, "/EXPORT:WSCEnumNameSpaceProvidersEx32=ws2_32.WSCEnumNameSpaceProvidersEx32,@131")
#pragma comment(linker, "/EXPORT:WSCEnumProtocols=ws2_32.WSCEnumProtocols,@132")
#pragma comment(linker, "/EXPORT:WSCEnumProtocols32=ws2_32.WSCEnumProtocols32,@133")
#pragma comment(linker, "/EXPORT:WSCEnumProtocolsEx=ws2_32.WSCEnumProtocolsEx,@134")
#pragma comment(linker, "/EXPORT:WSCGetApplicationCategory=ws2_32.WSCGetApplicationCategory,@135")
#pragma comment(linker, "/EXPORT:WSCGetApplicationCategoryEx=ws2_32.WSCGetApplicationCategoryEx,@136")
#pragma comment(linker, "/EXPORT:WSCGetProviderInfo=ws2_32.WSCGetProviderInfo,@137")
#pragma comment(linker, "/EXPORT:WSCGetProviderInfo32=ws2_32.WSCGetProviderInfo32,@138")
#pragma comment(linker, "/EXPORT:WSCGetProviderPath=ws2_32.WSCGetProviderPath,@139")
#pragma comment(linker, "/EXPORT:WSCGetProviderPath32=ws2_32.WSCGetProviderPath32,@140")
#pragma comment(linker, "/EXPORT:WSCInstallNameSpace=ws2_32.WSCInstallNameSpace,@141")
#pragma comment(linker, "/EXPORT:WSCInstallNameSpace32=ws2_32.WSCInstallNameSpace32,@142")
#pragma comment(linker, "/EXPORT:WSCInstallNameSpaceEx=ws2_32.WSCInstallNameSpaceEx,@143")
#pragma comment(linker, "/EXPORT:WSCInstallNameSpaceEx2=ws2_32.WSCInstallNameSpaceEx2,@144")
#pragma comment(linker, "/EXPORT:WSCInstallNameSpaceEx32=ws2_32.WSCInstallNameSpaceEx32,@145")
#pragma comment(linker, "/EXPORT:WSCInstallProvider=ws2_32.WSCInstallProvider,@146")
#pragma comment(linker, "/EXPORT:WSCInstallProvider64_32=ws2_32.WSCInstallProvider64_32,@147")
#pragma comment(linker, "/EXPORT:WSCInstallProviderAndChains64_32=ws2_32.WSCInstallProviderAndChains64_32,@148")
#pragma comment(linker, "/EXPORT:WSCInstallProviderEx=ws2_32.WSCInstallProviderEx,@149")
#pragma comment(linker, "/EXPORT:WSCSetApplicationCategory=ws2_32.WSCSetApplicationCategory,@150")
#pragma comment(linker, "/EXPORT:__WSAFDIsSet=ws2_32.__WSAFDIsSet,@151")
#pragma comment(linker, "/EXPORT:WSCSetApplicationCategoryEx=ws2_32.WSCSetApplicationCategoryEx,@152")
#pragma comment(linker, "/EXPORT:WSCSetProviderInfo=ws2_32.WSCSetProviderInfo,@153")
#pragma comment(linker, "/EXPORT:WSCSetProviderInfo32=ws2_32.WSCSetProviderInfo32,@154")
#pragma comment(linker, "/EXPORT:WSCUnInstallNameSpace=ws2_32.WSCUnInstallNameSpace,@155")
#pragma comment(linker, "/EXPORT:WSCUnInstallNameSpace32=ws2_32.WSCUnInstallNameSpace32,@156")
#pragma comment(linker, "/EXPORT:WSCUnInstallNameSpaceEx2=ws2_32.WSCUnInstallNameSpaceEx2,@157")
#pragma comment(linker, "/EXPORT:WSCUpdateProvider=ws2_32.WSCUpdateProvider,@158")
#pragma comment(linker, "/EXPORT:WSCUpdateProvider32=ws2_32.WSCUpdateProvider32,@159")
#pragma comment(linker, "/EXPORT:WSCUpdateProviderEx=ws2_32.WSCUpdateProviderEx,@160")
#pragma comment(linker, "/EXPORT:WSCWriteNameSpaceOrder=ws2_32.WSCWriteNameSpaceOrder,@161")
#pragma comment(linker, "/EXPORT:WSCWriteNameSpaceOrder32=ws2_32.WSCWriteNameSpaceOrder32,@162")
#pragma comment(linker, "/EXPORT:WSCWriteProviderOrder=ws2_32.WSCWriteProviderOrder,@163")
#pragma comment(linker, "/EXPORT:WSCWriteProviderOrder32=ws2_32.WSCWriteProviderOrder32,@164")
#pragma comment(linker, "/EXPORT:WSCWriteProviderOrderEx=ws2_32.WSCWriteProviderOrderEx,@165")
#pragma comment(linker, "/EXPORT:WahCloseApcHelper=ws2_32.WahCloseApcHelper,@166")
#pragma comment(linker, "/EXPORT:WahCloseHandleHelper=ws2_32.WahCloseHandleHelper,@167")
#pragma comment(linker, "/EXPORT:WahCloseNotificationHandleHelper=ws2_32.WahCloseNotificationHandleHelper,@168")
#pragma comment(linker, "/EXPORT:WahCloseSocketHandle=ws2_32.WahCloseSocketHandle,@169")
#pragma comment(linker, "/EXPORT:WahCloseThread=ws2_32.WahCloseThread,@170")
#pragma comment(linker, "/EXPORT:WahCompleteRequest=ws2_32.WahCompleteRequest,@171")
#pragma comment(linker, "/EXPORT:WahCreateHandleContextTable=ws2_32.WahCreateHandleContextTable,@172")
#pragma comment(linker, "/EXPORT:WahCreateNotificationHandle=ws2_32.WahCreateNotificationHandle,@173")
#pragma comment(linker, "/EXPORT:WahCreateSocketHandle=ws2_32.WahCreateSocketHandle,@174")
#pragma comment(linker, "/EXPORT:WahDestroyHandleContextTable=ws2_32.WahDestroyHandleContextTable,@175")
#pragma comment(linker, "/EXPORT:WahDisableNonIFSHandleSupport=ws2_32.WahDisableNonIFSHandleSupport,@176")
#pragma comment(linker, "/EXPORT:WahEnableNonIFSHandleSupport=ws2_32.WahEnableNonIFSHandleSupport,@177")
#pragma comment(linker, "/EXPORT:WahEnumerateHandleContexts=ws2_32.WahEnumerateHandleContexts,@178")
#pragma comment(linker, "/EXPORT:WahInsertHandleContext=ws2_32.WahInsertHandleContext,@179")
#pragma comment(linker, "/EXPORT:WahNotifyAllProcesses=ws2_32.WahNotifyAllProcesses,@180")
#pragma comment(linker, "/EXPORT:WahOpenApcHelper=ws2_32.WahOpenApcHelper,@181")
#pragma comment(linker, "/EXPORT:WahOpenCurrentThread=ws2_32.WahOpenCurrentThread,@182")
#pragma comment(linker, "/EXPORT:WahOpenHandleHelper=ws2_32.WahOpenHandleHelper,@183")
#pragma comment(linker, "/EXPORT:WahOpenNotificationHandleHelper=ws2_32.WahOpenNotificationHandleHelper,@184")
#pragma comment(linker, "/EXPORT:WahQueueUserApc=ws2_32.WahQueueUserApc,@185")
#pragma comment(linker, "/EXPORT:WahReferenceContextByHandle=ws2_32.WahReferenceContextByHandle,@186")
#pragma comment(linker, "/EXPORT:WahRemoveHandleContext=ws2_32.WahRemoveHandleContext,@187")
#pragma comment(linker, "/EXPORT:WahWaitForNotification=ws2_32.WahWaitForNotification,@188")
#pragma comment(linker, "/EXPORT:WahWriteLSPEvent=ws2_32.WahWriteLSPEvent,@189")
#pragma comment(linker, "/EXPORT:freeaddrinfo=ws2_32.freeaddrinfo,@190")
#pragma comment(linker, "/EXPORT:getaddrinfo=ws2_32.getaddrinfo,@191")
#pragma comment(linker, "/EXPORT:getnameinfo=ws2_32.getnameinfo,@192")
#pragma comment(linker, "/EXPORT:inet_ntop=ws2_32.inet_ntop,@193")
#pragma comment(linker, "/EXPORT:inet_pton=ws2_32.inet_pton,@194")
#pragma comment(linker, "/EXPORT:WEP=ws2_32.WEP,@500")



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
		OutputDebugString(L"[ws2_32]DLL_PROCESS_ATTACH");
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
		OutputDebugString(L"[ws2_32]DLL_PROCESS_DETACH");
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
	sprintf_s(text, "[ws2_32]%s socket: %d len: %d buff: %s", tag, socket, len, msg);
	OutputDebugStringA(text);
}


#ifdef _MANAGED
#pragma managed(pop)
#endif

