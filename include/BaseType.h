/////////////////////////////////////////////////////////////////////////////////
//�ļ����ƣ�BaseType.h
//����������ϵͳ�ײ����ͻ����ļ�������Ȩ��Ա�����޸Ĵ��ļ�����
//�汾˵����Windows����ϵͳ��Ҫ����꣺__WINDOWS__
//			Linux����ϵͳ��Ҫ����꣺__LINUX__
//�޸������
//
/////////////////////////////////////////////////////////////////////////////////
#ifndef __BASETYPE_H__
#define __BASETYPE_H__



/////////////////////////////////////////////////////////////////////////////////
//������ϢԤ�����
/////////////////////////////////////////////////////////////////////////////////
#ifndef FD_SETSIZE
#define FD_SETSIZE      1024
#endif /* FD_SETSIZE */


/////////////////////////////////////////////////////////////////////////////////
//��ǰ������ϵͳͷ�ļ�����
/////////////////////////////////////////////////////////////////////////////////
#if defined(__WINDOWS__)
	#pragma warning ( disable : 4786 )
	#include <Windows.h>
	#include "crtdbg.h"
#elif defined(__LINUX__)
	#include <sys/types.h>
	#include <pthread.h>
	#include <execinfo.h>
	#include <signal.h>
	#include <exception>
	#include <setjmp.h>
	#include <sys/epoll.h>
#endif

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <math.h>
#include <stdarg.h>

using namespace std;




#endif
