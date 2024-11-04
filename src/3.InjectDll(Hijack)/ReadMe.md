工具：[AheadLib-x86-x64: hijack dll Source Code Generator. support x86/x64](https://github.com/strivexjun/AheadLib-x86-x64)

1. 假设想要劫持的 DLL 为 `xyz.dll`，原始文件重新命名为 `xyz_old.dll`。

2. 使用 `AheadLib-x86-x64` 对需要劫持的 DLL 自动生成源码文件。

3. 参考其他劫持工程的实现方式，做一些修改。

4. 批量替换转发的名称需要修改下，修改规则：

   1. 如果名称不与需要劫持的 DLL 名称相同，则不需要修改。
   2. 如果名称为 `AheadLib_` 为前缀，则修改为 `xyz_old.` 为前缀。

5. 如果需要拦截某个函数，只需要按照如下格式修改即可：

   ```c
   #pragma comment(linker,"/export:recv=_recv@16,@16")
   ```

   函数实现代码：

   ```c
   typedef int (WINAPI* PFUN)(int s, const char* buf, int len, int flags);
   typedef int (WINAPI* PFUN2)(int s, char* buf, int len, int flags, int to, int tolen);
   
   PFUN oldSend, oldRecv;
   PFUN2 oldSendto, oldRecvfrom;
   
   
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
   
   
   extern "C" __declspec(dllexport) int WINAPI recv(int s, char* buf, int len, int flags) {
   	Log("recv", s, buf, len);
   	return oldRecv(s, buf, len, flags);
   }
   ```

6. 编译，生成的 DLL 和  `xyz_old.dll` 都放到目标程序的同级目录下。

7. 运行`dbgview`，运行目标程序，查看日志输出情况。