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
	//ʱ��api�ӿڣ�

	//���ϵͳ��������
	extern uint32		GetTickCount();
	//���ϵͳ��������(64λ)
	extern uint64		GetTickCount64();
	//����ϵͳ��������
	extern void		SetTickCount();
	//����ϵͳ��������(64λ)
	extern void		SetTickCount64();
	//���ϵͳ��ʱ��
	extern uint64		GetSecond();
	//���ϵͳ����ʱ��
	extern uint64		GetMillisecond();
	//���ϵͳ΢��ʱ��
	extern uint64		GetMicroseconds();
	//���ʱ��ʱ��(����)
	extern uint64		GetClockTime();
	//���ϵͳʱ��
	extern uint64		GetTime();
	extern uint32		GetTimeForLua();
	//���������ϵͳʱ��
	extern uint64		SetSysTime();
	extern uint64		GetSysTime();
	//��ý��տ�ʼʱ��
	extern uint64		GetDayBeginTime();
	//��ñ���ʱ��
	extern int32		GetLocalTime(struct tm* _Tm, const uint64* _Time);
	extern int32		GetLocalTime(struct tm* _Tm, uint64 _Time);
	//���ʱ���������
	extern int32		DiffTimeDay(uint64 _early, uint64 _late);
	//���ʱ���������
	extern int32		DiffTimeWeek(uint64 _early, uint64 _late);
	//���ʱ���������
	extern int32		DiffTimeMonth(uint64 _early, uint64 _late);
	//ʱ���ʽ��(YYYY-MM-DD HH:MM:SS)
	extern pc_str		time_format(uint64 _time);
	//ʱ���ʽ��(YYYY-MM-DD HH:MM:SS)
	extern uint64		time_format_to(pc_str _time);
	//ʱ���ʽ��(YYYYMMDDHHMMSS)
	extern pc_str		time_format_str(uint64 _time);
	//ʱ���ʽ��(YYYYMMDDHHMMSS)
	extern uint64		time_format_int(pc_str _time);
	//ʱ���ʽ��(HH:MM)
	extern pc_str		time_format_hm(uint64 _time);
	//ʱ���ʽ��(HH:MM:SS)
	extern pc_str		time_format_hms(uint64 _time);
	//˯��
	extern void		dSleep(uint32 millisecond);
	//��ý������ܼ�
	extern int32		GetWeakDay();
	//��ý����Ǽ���
	extern int32		GetMonthDay();

	extern double Count2Time(int64 deltaCount);

	class TimerFacade
	{
		uint64 m_uBeginCount;	/// ʱ�ӿ�ʼʱ�ļ���

	public:
		TimerFacade();

		/// ����ʱ��
		void Reset();

		/// ���غ������������ͣ�
		uint64 GetTime() const;

		/// ���غ�������Double�ͣ�
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