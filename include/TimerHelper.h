//==========================================================================
/**
* @file	 : Timer.h
* @author : stefanchen
* created : 2018 0802
* purpose : time api
*/
//==========================================================================
#ifndef _RKT_TIMER_H__
#define _RKT_TIMER_H__

#include "CommonDef.h"

namespace API
{
	//////////////////////////////////////////////////////////////////////////
	//时间api接口：

	//获得系统启动毫秒
	extern uint32		GetTickCount();
	//获得系统启动毫秒(64位)
	extern uint64		GetTickCount64();
	//设置系统启动毫秒
	extern void		SetTickCount();
	//设置系统启动毫秒(64位)
	extern void		SetTickCount64();
	//获得系统秒时间
	extern uint64		GetSecond();
	//获得系统毫秒时间
	extern uint64		GetMillisecond();
	//获得系统微秒时间
	extern uint64		GetMicroseconds();
	//获得时钟时间(毫秒)
	extern uint64		GetClockTime();
	//获得系统时间
	extern uint64		GetTime();
	extern uint32		GetTimeForLua();
	//获得与设置系统时间
	extern uint64		SetSysTime();
	extern uint64		GetSysTime();
	//获得今日开始时间
	extern uint64		GetDayBeginTime();
	//获得本地时间
	extern int32		GetLocalTime(struct tm* _Tm, const uint64* _Time);
	extern int32		GetLocalTime(struct tm* _Tm, uint64 _Time);
	//获得时间相差天数
	extern int32		DiffTimeDay(uint64 _early, uint64 _late);
	//获得时间相差周数
	extern int32		DiffTimeWeek(uint64 _early, uint64 _late);
	//获得时间相差月数
	extern int32		DiffTimeMonth(uint64 _early, uint64 _late);
	//时间格式化(YYYY-MM-DD HH:MM:SS)
	extern pc_str		time_format(uint64 _time);
	//时间格式化(YYYY-MM-DD HH:MM:SS)
	extern uint64		time_format_to(pc_str _time);
	//时间格式化(YYYYMMDDHHMMSS)
	extern pc_str		time_format_str(uint64 _time);
	//时间格式化(YYYYMMDDHHMMSS)
	extern uint64		time_format_int(pc_str _time);
	//时间格式化(HH:MM)
	extern pc_str		time_format_hm(uint64 _time);
	//时间格式化(HH:MM:SS)
	extern pc_str		time_format_hms(uint64 _time);
	//睡眠
	extern void		dSleep(uint32 millisecond);
	//获得今天是周几
	extern int32		GetWeakDay();
	//获得今天是几号
	extern int32		GetMonthDay();

	extern double Count2Time(int64 deltaCount);

	class TimerFacade
	{
		uint64 m_uBeginCount;	/// 时钟开始时的计数

	public:
		TimerFacade();

		/// 重置时钟
		void Reset();

		/// 返回毫秒数（整数型）
		uint64 GetTime() const;

		/// 返回毫秒数（Double型）
		double GetTimeByDouble() const;
	};

#ifndef _WIN32
	struct SYSTEMTIME
	{
		uint16 wYear;
		uint16 wMonth;
		uint16 wDayOfWeek;
		uint16 wDay;
		uint16 wHour;
		uint16 wMinute;
		uint16 wSecond;
		uint16 wMilliseconds;

		SYSTEMTIME() { initSYSTEMTIME();}
		inline void initSYSTEMTIME()
		{
			wYear			= 0;
			wMonth			= 0;
			wDayOfWeek		= 0;
			wDay			= 0;
			wHour			= 0;
			wMinute			= 0;
			wSecond			= 0;
			wMilliseconds	= 0;
		}
	};
#endif //
	extern void		GetLocalTime(SYSTEMTIME&systime);
}
#endif //_RKT_TIMER_H__