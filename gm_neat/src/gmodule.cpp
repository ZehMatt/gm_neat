#include "GarrysMod/Lua/Interface.h"
#include <stdio.h>
#include <windows.h>
#include <conio.h>

#include "LuaBlackbox.h"
#include "LuaIndividual.h"

GMOD_MODULE_OPEN()
{
	AllocConsole();
	_cprintf("-- Neat --\n");

	LuaBlackbox::Register(state);
	LuaIndividual::Register(state);

	return 0;
}

GMOD_MODULE_CLOSE()
{

	return 0;
}