// x64dbg_script_dll_retaddrfinder_project.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "x64dbg_script_dll_retaddrfinder_project.h"
#include "pluginsdk/bridgemain.h"
#include "pluginsdk/TitanEngine/TitanEngine.h"

extern "C" X64DBGSCRIPTDLLRETADDRFINDERPROJECT_API void Start() {
	duint addr = 0x1234;
	STACK_COMMENT comment;
	DbgStackCommentGet(addr, &comment);

	HANDLE hActiveThread = DbgGetThreadHandle();
	duint csp = GetContextDataEx(hActiveThread, UE_CSP);

	duint size;
	duint base = DbgMemFindBaseAddr(csp, &size);

	DWORD tid = DbgGetThreadId();
}
