
#include "Function.h"
#include "TimerHelper.h"

#ifndef _WIN32
#include <sys/time.h>
#endif

static uint32	g_uTickCount		= 0;
static uint64	g_uTickCount64		= 0;
static uint64	g_uSystemTime		= 0;

namespace API
{

	//���ϵͳ��������
	uint32 GetTickCount()
	{
		if(g_uTickCount == 0)
			SetTickCount();
		return g_uTickCount;
	}

	//���ϵͳ��������
	uint64 GetTickCount64()
	{
		if(g_uTickCount64 == 0)
			SetTickCount64();
		return g_uTickCount64;
	}

	//���ϵͳ��������
	void SetTickCount()
	{
#ifdef _WIN32
		//ֻ��ȷ��55ms
		//GetTickCount���أ�retrieve���Ӳ���ϵͳ������������elapsed���ĺ����������ķ���ֵ��DWORD��
		g_uTickCount = ::GetTickCount();
#else //linux

		struct timeval current;
		GetTimeofday(&current, NULL);
		g_uTickCount = current.tv_sec * 1000 + current.tv_usec/1000;
#endif
	}

	__int64 GetSysTickCount64()
	{
#ifdef WIN32
		static LARGE_INTEGER TicksPerSecond = { 0 };
		LARGE_INTEGER Tick;

		if (!TicksPerSecond.QuadPart)
		{
			QueryPerformanceFrequency(&TicksPerSecond);
		}

		QueryPerformanceCounter(&Tick);

		__int64 Seconds = Tick.QuadPart / TicksPerSecond.QuadPart;
		__int64 LeftPart = Tick.QuadPart - (TicksPerSecond.QuadPart*Seconds);
		__int64 MillSeconds = LeftPart * 1000 / TicksPerSecond.QuadPart;
		__int64 Ret = Seconds * 1000 + MillSeconds;
		//    __ASSERT(Ret>0);
		return Ret;
#endif // WIN32
	}

	//���ϵͳ��������
	void SetTickCount64()
	{
#ifdef _WIN32
		g_uTickCount64 = GetSysTickCount64();
#else
		timespec _spec;
		clock_GetTime(CLOCK_MONOTONIC,&_spec);
		g_uTickCount64 = _spec.tv_sec * 1000 + _spec.tv_nsec / 1000 / 1000;

#endif
	}

	//���ϵͳ��ʱ��
	uint64	GetSecond()
	{
		return ::time(NULL);
	}

	//���ϵͳ����ʱ��
	uint64	GetMillisecond()
	{
#ifdef _WIN32
		return GetSysTickCount64();
#else
		timespec _spec;
		clock_GetTime(CLOCK_MONOTONIC,&_spec);
		uint64 uTick = _spec.tv_sec * 1000 + _spec.tv_nsec / 1000 / 1000;

		return uTick;
#endif 
	}

	//���ϵͳ΢��ʱ��
	uint64	GetMicroseconds()
	{
#ifdef _WIN32
		LARGE_INTEGER stCount;
		QueryPerformanceCounter(&stCount); 

		return uint64(stCount.QuadPart);
#else//_WIN32
		timespec _spec;
		clock_GetTime(CLOCK_MONOTONIC,&_spec);
		uint64 uTick = _spec.tv_sec * 1000 * 1000 + _spec.tv_nsec / 1000;

		return uTick;
#endif //_WIN32
	}

	//���ʱ��ʱ��(����)
	uint64 GetClockTime()
	{
#ifdef _WIN32
		uint64 uTick = uint64(GetTime()) * 1000;
#else//_WIN32
		timespec _spec;
		clock_GetTime(CLOCK_REALTIME,&_spec);

		uint64 uTick = _spec.tv_sec * 1000 + _spec.tv_nsec / 1000 / 1000;
#endif //_WIN32
		return uTick;
	}

	//���ϵͳʱ��
	uint64 GetTime()
	{
		return ::time(NULL);
	}

	uint32 GetTimeForLua()
	{
		return (uint32)GetTime();
	}

	//���������ϵͳʱ��
	uint64 SetSysTime()
	{
		static uint64 g_uTime = 0;
		
		g_uSystemTime = GetTime();

		if (g_uSystemTime > g_uTime)
			g_uSystemTime -= g_uTime;

		return g_uSystemTime;
	}

	uint64 GetSysTime()
	{
		if (!g_uSystemTime)
			SetSysTime();

		return g_uSystemTime;
	}

	//��ý��տ�ʼʱ��
	uint64	GetDayBeginTime()
	{
		static tm	_tm;
		memset(&_tm, 0, sizeof(_tm));

		GetLocalTime(&_tm,GetTime());
		_tm.tm_hour= 0;
		_tm.tm_min = 0;
		_tm.tm_sec = 0;

		return mktime(&_tm);
	}

	//��ñ���ʱ��
	int32 GetLocalTime(struct tm* _Tm, const uint64* _Time)
	{
		if (!_Tm || !_Time)
			return -1;

		time_t _time = *_Time;

#ifdef _WIN32
		return ::localtime_s(_Tm,&_time);
#else
		if (_Tm)
			memset(_Tm, 0xff, sizeof(struct tm));

		struct tm* tmp = ::localtime(&_time);
		if (tmp && _Tm)
			dMemcpy(_Tm, sizeof(struct tm), tmp, sizeof(struct tm));
		
		return 0;
#endif
	}

	//��ñ���ʱ��
	int32 GetLocalTime(struct tm* _Tm, uint64 _Time)
	{
		if (!_Tm || !_Time)
			return -1;

		return GetLocalTime(_Tm, &_Time);
	}

	//���ʱ���������
	int32 DiffTimeDay(uint64 _early, uint64 _late)
	{
		if (_early == 0 || _late == 0)
			return 0;

		static tm	tm_early;
		static tm	tm_late;
		memset(&tm_early, 0, sizeof(tm_early));
		memset(&tm_late, 0, sizeof(tm_late));

		GetLocalTime(&tm_early, _early);
		GetLocalTime(&tm_late, _late);

		if (tm_early.tm_year > tm_late.tm_year)
			return 0;

		//ͬ��ͬ��
		if (tm_early.tm_year == tm_late.tm_year && tm_early.tm_yday == tm_late.tm_yday)
			return 0;

		//ͬ���ж�
		if (tm_early.tm_year == tm_late.tm_year)
		{
			if (tm_early.tm_yday >= tm_late.tm_yday)
				return 0;

			return (tm_late.tm_yday - tm_early.tm_yday);
		}

		int32 iDay = 0;
		//��ͬ��ʱ
		if (tm_early.tm_year != tm_late.tm_year)
		{
			tm tm_temp = tm_early;

			//��ȡ12��31��ʱ��
			tm_temp.tm_mon	= 11;
			tm_temp.tm_mday = 31;
			tm_temp.tm_yday = 0;
			uint64 _temp	= mktime(&tm_temp);

			GetLocalTime(&tm_temp,_temp);
			iDay = tm_temp.tm_yday - tm_early.tm_yday;

			//����+1
			iDay += 1;

			//������������
			for (int32 i = tm_early.tm_year + 1;i < tm_late.tm_year;++i)
			{
				tm_temp.tm_year++;
				tm_temp.tm_yday = 0;

				_temp	= mktime(&tm_temp);
				GetLocalTime(&tm_temp,_temp);

				iDay += tm_temp.tm_yday;
				//����+1
				iDay+=1;
			}
		}

		return (iDay + tm_late.tm_yday);
	}

	//���ʱ���������
	int32 diffTimeWeek(uint64 _early, uint64 _late)
	{
		if (_early == 0 || _late == 0)
			return 0;

		static tm	tm_early;
		static tm	tm_late;
		memset(&tm_early, 0, sizeof(tm_early));
		memset(&tm_late, 0, sizeof(tm_late));

		GetLocalTime(&tm_early,_early);
		GetLocalTime(&tm_late,_late);

		if (tm_early.tm_year > tm_late.tm_year)
			return 0;

		//ͬ��ͬ��
		if (tm_early.tm_year == tm_late.tm_year && tm_early.tm_yday == tm_late.tm_yday)
			return 0;

		//�����������ڵ�ÿһ��������������
		if (tm_early.tm_wday != 6)
			tm_early.tm_mday +=(6 - tm_early.tm_wday);
	
		if (tm_late.tm_wday != 6)
			tm_late.tm_mday +=(6 - tm_late.tm_wday);

		int32 iDay = DiffTimeDay(mktime(&tm_early),mktime(&tm_late));

		int32 iWeek = 0;
		if (iDay > 0)
		{//�϶�����7�ı�����Ϊ��������
			iWeek = iDay / 7;
		}

		return iWeek;
	}

	int32 DiffTimeMonth(uint64 _early, uint64 _late)
	{
		if (_early == 0 || _late == 0)
			return 0;

		static tm	tm_early;
		static tm	tm_late;
		memset(&tm_early, 0, sizeof(tm_early));
		memset(&tm_late, 0, sizeof(tm_late));

		GetLocalTime(&tm_early,_early);
		GetLocalTime(&tm_late,_late);

		if (tm_early.tm_year > tm_late.tm_year)
			return 0;

		//ͬ��ͬ��
		if (tm_early.tm_year == tm_late.tm_year && tm_early.tm_mon == tm_late.tm_mon)
			return 0;

		//�����������ڵ�ÿһ��������������
		if (tm_early.tm_wday != 6)
			tm_early.tm_mday +=(6 - tm_early.tm_wday);

		if (tm_late.tm_wday != 6)
			tm_late.tm_mday +=(6 - tm_late.tm_wday);

		//ͬ��:
		if (tm_late.tm_year == tm_early.tm_year)
			return tm_late.tm_mon - tm_early.tm_mon;

		//��ͬ��:
		int32 diffYear = (tm_late.tm_year - tm_late.tm_year);

		return diffYear*12 + (tm_late.tm_mon - tm_early.tm_mon);
	}

	int32 getWeakDay()
	{
		static tm	_tm;
		int64 nTime = GetTime();
		memset(&_tm, 0, sizeof(_tm));

		GetLocalTime(&_tm, nTime);

		return _tm.tm_wday;
	}

	int32 getMonthDay()
	{
		static tm	_tm;
		int64 nTime = GetTime();
		memset(&_tm, 0, sizeof(_tm));

		GetLocalTime(&_tm, nTime);

		return _tm.tm_mday;
	}

	//ʱ���ʽ��(YYYY-MM-DD HH:MM:SS)
	pc_str time_format(uint64 _time)
	{
		tm	tmTime;
		memset(&tmTime, 0, sizeof(tmTime));
		if (GetLocalTime(&tmTime,_time) != 0)
			return "";

		static char szDate[32] = {0};
		dSprintf(szDate,sizeof(szDate),"%.4d-%.2d-%.2d %.2d:%.2d:%.2d",tmTime.tm_year + 1900,tmTime.tm_mon + 1,tmTime.tm_mday,tmTime.tm_hour,tmTime.tm_min,tmTime.tm_sec);

		return szDate;
	}

	pc_str time_format_hm(uint64 _time)
	{
		tm	tmTime;
		memset(&tmTime, 0, sizeof(tmTime));
		if (GetLocalTime(&tmTime, _time) != 0)
			return "";

		static char szDate[32] = { 0 };
		dSprintf(szDate, sizeof(szDate), "%.2d:%.2d", tmTime.tm_hour, tmTime.tm_min);

		return szDate;
	}

	pc_str time_format_hms(uint64 _time)
	{
		tm	tmTime;
		memset(&tmTime, 0, sizeof(tmTime));
		if (GetLocalTime(&tmTime, _time) != 0)
			return "";

		static char szDate[32] = { 0 };
		dSprintf(szDate, sizeof(szDate), "%.2d:%.2d:%.2d", tmTime.tm_hour, tmTime.tm_min, tmTime.tm_sec);

		return szDate;
	}

	//ʱ���ʽ��(YYYYMMDDHHMMSS)
	pc_str time_format_str(uint64 _time)
	{
		tm	tmTime;
		memset(&tmTime, 0, sizeof(tmTime));
		if (GetLocalTime(&tmTime,_time) != 0)
			return "";

		static char szDate[32] = {0};
		dSprintf(szDate,sizeof(szDate),"%4d%2d%2d%2d%2d%2d",tmTime.tm_year + 1900,tmTime.tm_mon + 1,tmTime.tm_mday,tmTime.tm_hour,tmTime.tm_min,tmTime.tm_sec);

		return szDate;
	}

	//ʱ���ʽ��(YYYYMMDDHHMMSS)
	uint64 time_format_int(pc_str _time)
	{
		uint64 uTime = 0;

		while (_time)
		{
			uTime += atoi(_time);
			_time++;
		}

		return uTime;
	}

	// ˯��
	void dSleep(uint32 millisecond)
	{
#ifdef _WIN32
		::Sleep(millisecond);
#else//_WIN32
		usleep( millisecond * 1000);
#endif //_WIN32
	}

	void	GetLocalTime(SYSTEMTIME&systime)
	{
#ifdef _WIN32
		::GetLocalTime(&systime);
#else//_WIN32
		systime.initSYSTEMTIME();
		time_t _time = GetTime();
		struct tm* tmp = ::localtime(&_time);
		if (tmp)
		{
			timespec _spec;
			clock_GetTime(CLOCK_REALTIME,&_spec);

			systime.wYear			= tmp->tm_year + 1900;
			systime.wMonth			= tmp->tm_mon + 1;
			systime.wDayOfWeek		= tmp->tm_wday;
			systime.wDay			= tmp->tm_mday;
			systime.wHour			= tmp->tm_hour;
			systime.wMinute			= tmp->tm_min;
			systime.wSecond			= tmp->tm_sec;
			systime.wMilliseconds	= _spec.tv_nsec / 1000 / 1000;
		}
#endif //_WIN32
	}

	static double initPerformanceTimer()
	{
#ifdef _WIN32
		LARGE_INTEGER litmp;
		if (!::QueryPerformanceFrequency(&litmp))
		{
			//Error("the computer not support QueryPerformanceFrequency!\n");
		}
		return (double)litmp.QuadPart;
#else
		struct timeval start;  
		GetTimeofday(&start, NULL);  

		return start.tv_usec;
#endif
	}

	static double gPerformanceFrequency = 1000 / initPerformanceTimer();

	double count2Time(int64 deltaCount)
	{
		return deltaCount * gPerformanceFrequency;
	}

	TimerFacade::TimerFacade()
	{
		Reset();
	}

	void TimerFacade::Reset()
	{
		m_uBeginCount = GetPerformanceCount();
	}

	uint64 TimerFacade::GetTime() const
	{
		return (uint64)count2Time(GetPerformanceCount() - m_uBeginCount);
	}

	double TimerFacade::GetTimeByDouble() const
	{
		return count2Time(GetPerformanceCount() - m_uBeginCount);
	}
}