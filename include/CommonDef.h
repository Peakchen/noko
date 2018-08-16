
/*
* CoptRight(C) StefanChen e-mail(2572915286@qq.com)
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#ifndef __CommonDef_h__
#define __CommonDef_h__


#include <cstdlib>
#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <cstring>
#include <typeinfo>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <memory>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>
#include <stdarg.h>
#if !defined(_WIN32) 
#include <stdint.h>
#include <inttypes.h>
#include <ext/hash_map>
using namespace __gnu_cxx;
#else
#include <hash_map>
#include <functional>
#endif

#ifdef __WINDOWS__
#pragma warning ( disable : 4786 )
#include <winsock2.h>
#include <windows.h>
#include <mbctype.h>
#include <stdio.h>   
#include <stdlib.h>   
#include <httpext.h>   
#include <windef.h>   
#include <Nb30.h>
#include <Winbase.h>
#include "crtdbg.h"
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"netapi32.lib")
#elif defined(__LINUX__)
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/types.h>
#include <pthread.h>
#include <execinfo.h>
#include <signal.h>
#include <exception>
#include <setjmp.h>
#include <sys/epoll.h>
#include <sys/types.h>			// for accept()
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>			// for inet_xxx()
#include <netinet/in.h>
#include <errno.h>				// for errno
#else
#include <netinet/in.h>
#endif

/*************************************************************/
typedef char				int8, int08;
typedef unsigned char		uchar, uint8, uint08;

typedef signed short		int16;	///< Compiler independent Signed 16-bit short
typedef unsigned short		uint16;	///< Compiler independent Unsigned 16-bit short

typedef float				float32;///< Compiler independent 32-bit float
typedef double				float64;///< Compiler independent 64-bit float

typedef unsigned long		ulong;

#if defined(_WIN32) 
typedef signed __int32		int32;	///< Compiler independent Signed 32-bit integer
typedef unsigned __int32	uint32;	///< Compiler independent Unsigned 32-bit integer

typedef __int64				int64;	///Compiler independent Unsigned 64-bit integer
typedef unsigned __int64	uint64;	///Compiler independent Unsigned 64-bit integer

#else//_WIN32

typedef int32_t				int32;	///< Compiler independent Signed 32-bit integer
typedef uint32_t			uint32;	///< Compiler independent Unsigned 32-bit integer

typedef long long			int64;
typedef unsigned long long	uint64;
#endif//_WIN32

typedef char*				p_str;
typedef const char*			pc_str;
typedef unsigned char		byte;
typedef SOCKET				nk_socket;
typedef uint32				IP_t;
// typedef unsigned char		BYTE;
// typedef unsigned short		WORD;
// typedef unsigned long		DWORD;

static const float32 Float_Pi = float32(3.14159265358979323846);			///< Constant float PI
static const float32 Float_2Pi = float32(2.0 * 3.14159265358979323846);	///< Constant float 2*PI
static const float32 Float_InversePi = float32(1.0 / 3.14159265358979323846);	///< Constant float 1 / PI
static const float32 Float_HalfPi = float32(0.5 * 3.14159265358979323846);	///< Constant float 1/2 * PI
static const float32 Float_2InversePi = float32(2.0 / 3.14159265358979323846);	///< Constant float 2 / PI
static const float32 Float_Inverse2Pi = float32(0.5 / 3.14159265358979323846);	///< Constant float 0.5 / PI

static const float32 Float_Sqrt2 = float32(1.41421356237309504880f);			///< Constant float sqrt(2)
static const float32 Float_SqrtHalf = float32(0.7071067811865475244008443f);	///< Constant float sqrt(0.5)

static const int8	int8_MIN = int8(-128);								///< Constant Min Limit int8
static const int8	int8_MAX = int8(127);								///< Constant Max Limit int8
static const uint8	uint8_MAX = uint8(255);								///< Constant Max Limit uint8

static const int16	int16_MIN = int16(-32768);							///< Constant Min Limit int16
static const int16	int16_MAX = int16(32767);								///< Constant Max Limit int16
static const uint16	uint16_MAX = uint16(65535);							///< Constant Max Limit uint16

static const int32	int32_MIN = int32(-2147483647 - 1);					///< Constant Min Limit int32
static const int32	int32_MAX = int32(2147483647);						///< Constant Max Limit int32
static const uint32	uint32_MAX = uint32(0xffffffff);						///< Constant Max Limit uint32

#ifndef NULL
#define NULL	0
#endif//NULL
																			//最小值
#ifndef MIN
#define MIN(a,b)	(a > b ? b: a)
#endif//MIN
																			//最大值
#ifndef MAX
#define MAX(a,b)	(a > b ? a: b)
#endif//MAX
#ifndef _BIT32
#define _BIT32(x) ((x < 32) ? (1 << (x)) : 0) 					///< Returns value with bit x set (2^x)
#endif//_BIT32

#ifndef _SET_BIT32
#define _SET_BIT32(mark,bit,s) (s ? (mark |= _BIT32(bit)) : (mark &=~_BIT32(bit)))
#endif//_SET_BIT32

#ifndef _CHECK_BIT
#define _CHECK_BIT(mark,bit)	((mark & bit) > 0)				///检测是否存在相同位
#endif//_CHECK_BIT
#ifndef _BIT64
#define _BIT64(x) uint64((x < 64) ? ((uint64)1 << (x)) : 0) 	///< Returns value with 64 bit x set (2^x)
#endif//_BIT64

#ifndef _SET_BIT64
#define _SET_BIT64(mark,bit,s) (s ? (mark |= _BIT64(bit)) : (mark &=~_BIT64(bit)))
#endif//_SET_BIT64

#ifndef _SET_BIT8ARRAY
#define _SET_BIT8ARRAY(arr,bit,s)	(s ? (arr[bit >> 3] |= uint8(1 << (bit & 0x7))) : (arr[bit >> 3] &= uint8(~(1 << (bit & 0x7)))))
#endif//_SET_BIT8ARRAY

#ifndef _CHECK_BIT8ARRAY
#define _CHECK_BIT8ARRAY(arr,bit)	((arr[bit >> 3] & uint8(1 << (bit & 0x7))) != 0)	///检测是否存在相同位
#endif//_CHECK_BIT8ARRAY

#define MAKE_UINT64(h,l)((uint64)( (((uint64)((uint32)(h) & 0xffffffff)) << 32) | ((uint32)((uint64)(l) & 0xffffffff)) ))
#define U64_H_U32(_v)	((uint32)(((uint64)(_v) >> 32) & 0xffffffff))
#define U64_L_U32(_v)	((uint32)((uint64)(_v) & 0xffffffff))

#define MAKE_UINT32(h,l)((uint32)( (((uint32)((uint16)(h) & 0xffff)) << 16) | ((uint16)((uint32)(l) & 0xffff)) ))
#define U32_H_U16(_v)	((uint16)(((uint32)(_v) >> 16) & 0xffff))
#define U32_L_U16(_v)	((uint16)((uint32)(_v) & 0xffff))
#define MAKEU16(a, b)	((WORD)(((BYTE)((DWORD)(a) & 0xff))		| ((WORD)((BYTE)((DWORD)(b) & 0xff))) << 8))
#define MAKEU32(a, b)	((LONG)(((WORD)((DWORD)(a) & 0xffff))	| ((DWORD)((WORD)((DWORD)(b) & 0xffff))) << 16))
#define LU16(l)			((WORD)((DWORD)(l) & 0xffff))
#define HU16(l)			((WORD)((DWORD)(l) >> 16))
#define LU8(w)			((BYTE)((DWORD)(w) & 0xff))
#define HU8(w)			((BYTE)((DWORD)(w) >> 8))

///////////////////////////////////////////////////////////////////////
//基本数据宏定义
///////////////////////////////////////////////////////////////////////

//IP地址的字符最大长度
#define IP_SIZE				24
#define KEY_SIZE			64
#define MAX_WORLDCOUNT		256
#define TIMELENTH			23

																			//↓这样在可执行文件中将是汉字显示，上线前要改成随机KEY↓KEY不得小于10个字节
#define GAMESERVER_TO_CLIENT_KEY "服务器端对客户端的封包密钥"
#define CLIENT_TO_GAMESERVER_KEY "服务器端对客户端的封包密钥"
#define LOGIN_TO_CLIENT_KEY      "服务器端对客户端的封包密钥"
#define CLIENT_TO_LOGIN_KEY      "服务器端对客户端的封包密钥"
#define OSTREAM_KEY              "底层全局封包流通用密钥"		
																			//↑这样在可执行文件中将是汉字显示，上线前要改成随机KEY↑KEY不得小于10个字节

#define PACK_COMPART "$-$"//封包分隔符
#define PACK_COMPART_SIZE strlen(PACK_COMPART)

#ifndef ENCRYPT
#define ENCRYPT(x,xlen,KEY,BeginPlace)	if( (x)!=NULL ) \
		{ \
		\
			CHAR* t_pBuffer = (x); \
			CHAR* pKey = {KEY}; \
			UINT KeyLen = (UINT)strlen(pKey); \
			for (UINT i = 0; i < (xlen); i++) \
			{ \
				*t_pBuffer ^= pKey[(i+BeginPlace)%KeyLen]; \
				t_pBuffer++; \
			} \
		}
#endif

#ifndef ENCRYPT_HEAD
#define ENCRYPT_HEAD(x,KEY)	if( (x)!=NULL ) \
		{ \
			CHAR* t_pBuffer = (x); \
			CHAR* pKey = {KEY}; \
			UINT KeyLen = (UINT)strlen(pKey); \
			for (UINT i = 0; i < PACKET_HEADER_SIZE; i++) \
			{ \
				*t_pBuffer ^= pKey[i%KeyLen]; \
				t_pBuffer++; \
			} \
		}
#endif

#define OVER_MAX_SERVER 256

																			//无效的句柄
#define INVALID_HANDLE	-1
																			//无效的ID值
#define INVALID_ID		-1
																			//真
#ifndef TRUE
#define TRUE 1
#endif
																			//假
#ifndef FALSE
#define FALSE 0
#endif
																			//文件路径的字符最大长度
#ifndef _MAX_PATH
#define _MAX_PATH 260
#endif

///////////////////////////////////////////////////////////////////////
//调试预定义宏定义
///////////////////////////////////////////////////////////////////////
#if defined(NDEBUG)
#define __ENTER_FUNCTION_FOXNET if(1){
#define __LEAVE_FUNCTION_FOXNET }
#else
#define __ENTER_FUNCTION_FOXNET if(1){
#define __LEAVE_FUNCTION_FOXNET }
#endif


#if defined(NDEBUG)
#define _MY_TRY try
#define _MY_CATCH catch(...)
#else
#define _MY_TRY try
#define _MY_CATCH catch(...)
#endif
																			//根据指针值删除内存
#ifndef SAFE_DELETE
#define SAFE_DELETE(x)	if( (x)!=NULL ) { delete (x); (x)=NULL; }
#endif
																			//根据指针值删除数组类型内存
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x)	if( (x)!=NULL ) { delete[] (x); (x)=NULL; }
#endif
																			//根据指针调用free接口
#ifndef SAFE_FREE
#define SAFE_FREE(x)	if( (x)!=NULL ) { free(x); (x)=NULL; }
#endif
																			//根据指针调用Release接口
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x)	if( (x)!=NULL ) { (x)->Release(); (x)=NULL; }
#endif


#define MAX_PATH 260

#ifdef _WIN32
#include <TlHelp32.h>
#include <WinBase.h>
#include <ctime>
#endif

#define _ESIZE 256
#if defined(__LINUX__)

typedef		int32		SOCKET;
#define     INVALID_SOCKET   -1
#define		SOCKET_ERROR	 -1

#endif

static const int32 SOCKET_ERROR_WOULDBLOCK = -100;
typedef struct sockaddr SOCKADDR;
typedef struct sockaddr_in SOCKADDR_IN;
static const uint32 szSOCKADDR_IN = sizeof(SOCKADDR_IN);

#define  SOCKET_LISTEN_BASE_BLOCK_SIZE 5

#endif // __CommonDef_h__