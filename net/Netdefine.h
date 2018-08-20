#pragma once
#include "CommonDef.h"

#ifndef  ___NET__DEFINE__H___
#define  ___NET__DEFINE__H___

enum emBufferSize
{
	em_buffer_7 = 7,
	em_buffer_2 = 2,
	em_buffer_4 = 4,
	em_buffer_8 = 8,
	em_buffer_16 = 16,
	em_buffer_32 = 32,
	em_buffer_64 = 64,
	em_buffer_128 = 128,
	em_buffer_254 = 254,
	em_buffer_512 = 512,
	em_buffer_1024 = 1024,
	em_buffer_2048 = 2048,
	em_buffer_3072 = 3072,
	em_buffer_4096 = 4096,
};

/************************************************************************/
/* select socket define                                                 */
/************************************************************************/

#define SELECT_SOCKET_NUM 2
#define SELECT_TV_SEC 5
#define SELECT_TV_USEC 0
#define SELECT_TIME_COUT_TICK 10

enum emServerType
{
	em_SID_LOGIN = 1,
	em_SID_BIGWORLD = 2,
	em_SID_GAMELOGIC = 3,
	em_SID_DB = 4,
	em_SID_SMALLWORLD = 5,
	em_SID_TRADE = 6,

};

#pragma pack(push)
#pragma pack(1)
#pragma warning(disable:4996)

struct TESGHandler
{
	int8 nSID;
	char szbuff[em_buffer_2048];

	TESGHandler()
	{
		memset(this, 0, sizeof(*this));
	}
};


#pragma pack(pop)


#endif