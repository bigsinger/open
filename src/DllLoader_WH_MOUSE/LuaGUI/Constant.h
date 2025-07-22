
#pragma once

namespace Constant {
};

#ifdef _WIN64
#define  STAR_LUA_LIB_NAME	L"star_x64.dll"
#else
#define  STAR_LUA_LIB_NAME	L"star_Win32.dll"
#endif // _WIN64

#define  STAR_LUA_INIT_NAME	"luaopen_star"

void TRACEW(const wchar_t* pFormat, ...);