// x64dbg_script_dll_retaddrfinder_project.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "x64dbg_script_dll_retaddrfinder_project.h"
#include "pluginsdk/bridgemain.h"
#include "pluginsdk/TitanEngine/TitanEngine.h"
#include <winternl.h>
#include <winnt.h>

extern "C" X64DBGSCRIPTDLLRETADDRFINDERPROJECT_API void Start() {
	duint addr = 0x1234;
	STACK_COMMENT comment;
	DbgStackCommentGet(addr, &comment);

	HANDLE debugee_hActiveThread = DbgGetThreadHandle();
	duint debugee_csp = GetContextDataEx(debugee_hActiveThread, UE_CSP);

	DWORD debugee_active_thread_tid = DbgGetThreadId();

	duint debugee_active_thread_teb_vaddr = DbgGetTebAddress(debugee_active_thread_tid);
	duint debugee_active_thread_tib_vaddr = debugee_active_thread_teb_vaddr;

	NT_TIB debugee_active_thread_tib;

	bool succeed = DbgMemRead(debugee_active_thread_tib_vaddr, &debugee_active_thread_tib, sizeof(NT_TIB));

	PVOID debugee_stack_base = debugee_active_thread_tib.StackBase;


}
