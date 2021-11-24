// x64dbg_script_dll_retaddrfinder_project.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "x64dbg_script_dll_retaddrfinder_project.h"
#include "pluginsdk/bridgemain.h"
#include "pluginsdk/TitanEngine/TitanEngine.h"
#include <winternl.h>
#include <winnt.h>
#include <cstring>

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
	if (!succeed) {
		GuiAddLogMessage("Fail to read debugee TIB.\n");
		return;
	}



	duint debugee_stack_base = (duint)debugee_active_thread_tib.StackBase;

	int dump_size = debugee_stack_base - debugee_csp;
	char* stack_dump = new char[dump_size];

	succeed = DbgMemRead(debugee_csp, stack_dump, dump_size);
	if (!succeed) {
		GuiAddLogMessage("Fail to read debugee stack dump.\n");
		return;
	}

	void* tmp;
	int ptr_size = sizeof(tmp);
	char msg[100+ MAX_COMMENT_SIZE];
	STACK_COMMENT sc;
	duint stack_addr;

	for (int i = dump_size % ptr_size; i < dump_size; i += ptr_size) {
		stack_addr = debugee_csp + i;
		succeed = DbgStackCommentGet(stack_addr, &sc);
		if (strcmp(sc.color, "!rtnclr") == 0) {
			tmp = *(void**)(&stack_dump[i]);
			sprintf_s(msg, "%p\t%s\n", tmp, sc.comment);
			GuiAddLogMessage(msg);
		}
	}
}
