
#pragma once

namespace Constant {
};

#ifdef _WIN64
#define  STAR_LUA_LIB_NAME	_T("star_x64.dll")
#else
#define  STAR_LUA_LIB_NAME	_T("star_Win32.dll")
#endif // _WIN64