/*************************************************************************/
/*  crash_handler_windows.h                                              */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2020 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2020 Godot Engine contributors (cf. AUTHORS.md).   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

// ------------------------- USAGE ------------------------
// 
// #include "crash_handler_windows.h"
// 
// int _main(int argc, char** argv)
// {
//     char* cp = NULL;
//     *cp = 0xff;
//     return 0;
// }
// 
// int main(int argc, char** argv)
// {
// #ifdef CRASH_HANDLER_EXCEPTION
//     __try {
//         return _main(argc, argv);
//     } __except (CrashHandlerException(GetExceptionInformation())) {
//         return 1;
//     }
// #else
//     return _main(argc, argv);
// #endif
//     return 0;
// }
// --------------------------------------------------------

#ifndef CRASH_HANDLER_WINDOWS_H
#define CRASH_HANDLER_WINDOWS_H

#include <windows.h>

#if defined(DEBUG_BUILD) && defined(_MSC_VER)
#define CRASH_HANDLER_EXCEPTION 1
extern DWORD CrashHandlerException(EXCEPTION_POINTERS* ep);
#endif

#endif // CRASH_HANDLER_WINDOWS_H