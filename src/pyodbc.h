
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
// documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
// OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef PYODBC_H
#define PYODBC_H

#ifdef _MSC_VER
// The MS headers generate a ton of warnings.
#pragma warning(push, 0)
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <malloc.h>
#pragma warning(pop)
typedef __int64 INT64;
typedef unsigned __int64 UINT64;
#else
typedef unsigned char byte;
typedef unsigned int UINT;
typedef long long INT64;
typedef unsigned long long UINT64;
#define _strcmpi strcasecmp
#define _strdup strdup
  inline int max(int lhs, int rhs) { return (rhs > lhs) ? rhs : lhs; }
#endif

#ifdef __SUN__
#include <alloca.h>
#endif

#define PY_SSIZE_T_CLEAN 1

#include <Python.h>
#include <floatobject.h>
#include <longobject.h>
#include <boolobject.h>
#include <unicodeobject.h>
#include <structmember.h>
#include <bytesobject.h>

#ifdef __CYGWIN__
#include <windows.h>
#endif

#include <sql.h>
#include <sqlext.h>

#ifndef _countof
#define _countof(a) (sizeof(a) / sizeof(a[0]))
#endif

#ifndef SQL_SS_TABLE
#define SQL_SS_TABLE -153
#endif

#ifndef SQL_SOPT_SS_PARAM_FOCUS
#define SQL_SOPT_SS_PARAM_FOCUS 1236
#endif

#ifndef SQL_CA_SS_TYPE_NAME
#define SQL_CA_SS_TYPE_NAME 1227
#endif

#ifndef SQL_CA_SS_SCHEMA_NAME
#define SQL_CA_SS_SCHEMA_NAME 1226
#endif

#ifndef SQL_CA_SS_CATALOG_NAME
#define SQL_CA_SS_CATALOG_NAME 1225
#endif

#ifndef SQL_CA_SS_VARIANT_TYPE
#define SQL_CA_SS_VARIANT_TYPE 1215
#endif

inline bool IsSet(DWORD grf, DWORD flags)
{
    return (grf & flags) == flags;
}

#ifdef UNUSED
#undef UNUSED
#endif

inline void UNUSED(...) { }

#include <stdarg.h>

#if defined(__SUNPRO_CC) || defined(__SUNPRO_C) || (defined(__GNUC__) && !defined(__MINGW32__))
#ifndef __FreeBSD__
#include <alloca.h>
#endif
#define CDECL cdecl
//#define min(X,Y) ((X) < (Y) ? (X) : (Y))
//#define max(X,Y) ((X) > (Y) ? (X) : (Y))
#define _alloca alloca
inline void _strlwr(char* name)
{
    while (*name) { *name = tolower(*name); name++; }
}
#else
#define CDECL
#endif

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#ifdef PYODBC_TRACE
void DebugTrace(const char* szFmt, ...);
#else
inline void DebugTrace(const char* szFmt, ...) { UNUSED(szFmt); }
#endif
#define TRACE DebugTrace

// issue #880: entry missing from iODBC sqltypes.h
#ifndef BYTE
  typedef unsigned char BYTE;
#endif
bool PyMem_Realloc(BYTE** pp, size_t newlen);
// A wrapper around realloc with a safer interface.  If it is successful, *pp is updated to the
// new pointer value.  If not successful, it is not modified.  (It is easy to forget and lose
// the old pointer value with realloc.)

void PrintBytes(void* p, size_t len);
const char* CTypeName(SQLSMALLINT n);
const char* SqlTypeName(SQLSMALLINT n);

#endif // pyodbc_h
