//**************************************************************
// Name:      local.cpp
// Purpose:   Defines the application palettes and the lists of ages, constraint names and table types
// Author:    Nuku Systems (gabygabygaby@gmail.com)
// Created:   2009-01-01
// Copyright: Nuku Systems ()
// License:   Proprietary
//**************************************************************

// C++ includes

// Qt includes

// Local includes

#include <windows.h>
#include "architecturehelper.h"

//******************************************************************************************************
// Verifies that the current build his authenticated
//******************************************************************************************************
bool is64BitWindows()
{
#if defined (_WIN64)
 return true;  // 64-bit programs run only on Win64
#elif defined (_WIN32)
 // 32-bit programs run on both 32-bit and 64-bit Windows
 // so must sniff
 bool f64 = false;
// return IsWow64Process(GetCurrentProcess(), &f64) && f64;
#endif
 return false; // Win64 does not support Win16
}
