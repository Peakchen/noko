#pragma once
#include <stdlib.h>
#include <string>
#include <map>
#include "CommonDef.h"


namespace noko
{
	template <typename T>
	T StringToNumber(const std::string &Text)
	{
		std::istringstream ss(Text);
		T result;
		return ss >> result ? result : 0;
	}

	template <typename T>
	bool StringToNumber(const std::string &Text, T & ret)
	{
		std::istringstream ss(Text);
		return ss >> ret;
	}

	inline unsigned long ulrand() {
		return (
			((static_cast<unsigned long>(rand()) << 24) & 0xFF000000ul)
			| ((static_cast<unsigned long>(rand()) << 12) & 0x00FFF000ul)
			| (static_cast<unsigned long>(rand()) & 0x00000FFFul));
	}

	// ������max=> [0, max)
	inline unsigned long ulrand(unsigned long max) {
		return max == 0 ? max : ulrand() % max;
	}

	// ������to=> (from, to]
	inline unsigned long ulrand(unsigned long from, unsigned long to) {
		return from >= to ? to : (ulrand() % (to - from) + from + 1);
	}

	std::string UnSerializeFromString(const std::map<int, std::string> & map);
	std::string UnSerializeFromString(const std::map<int, std::string> & map, char seperator);

	/* ȡ�� �滻�ַ���
	@param 1:	std::string& dstStr  Ŀ���ַ���
	@param 2:   std::string szSrc	 ���ҵ��ַ���
	@param 3:	std::string szNeed	 �����滻���ַ���
	return void
	*/

	void GetReplaceString(std::string& dstStr, std::string szSrc, std::string szNeed);

	void DeleteStr(const char *str, const char* sub_str, std::string& dstData);

	bool IsTwentyFourPoints();

	void SafeMemcpy(char* szDst, int nLenDst, const char* szSrc, int nLenDrc);

	BOOL IsTextUTF8(const char* str, int nLength);

	//��ͨsting���� תUTF-8�����ʽ�ַ���
	std::string StringToUTF8(const std::string& str);

	//UTF-8�����ʽ�ַ���  ת��ͨsting����
	std::string UTF8ToString(const std::string& str);

	//ansi��ת��Unicode���ٵ�UTF-8,��������Ȼ��
	std::string UnicodeToANSI(const std::wstring &unicodeStr);
	std::wstring ANSIToUnicode(const std::string &ansiStr);

	std::wstring UTF8ToUnicode(const std::string &utf8Str);
	std::string UnicodeToUtf8(const std::wstring &unicodeStr);

	std::string UTF8ToANSI(const std::string &utf8Str);
	std::string ANSIToUTF8(const std::string &ansiStr);

	//���ù���Ŀ¼
	extern void			SetWorkDirectory(const std::string strPath);
	//��ȡ���������ڵ�·��
	extern std::string	GetCurrentPath();

	//��ȡ�ַ���
	std::string ExtractString(const std::string& str, char begin, char end);
	//�ض��ַ���
	void TruncationString(const std::string& str, std::string& res1, std::string& res2, char c);

	/// fromat string
	template <int bufLen>
	inline int SafeSprintf(char(&Destination)[bufLen], const char *format, ...)
	{
		va_list args;
		va_start(args, format);
		int n = _vsnprintf_s(Destination, bufLen - 1, format, args);
		va_end(args);
		Destination[bufLen - 1] = '\0';
		if (n < 0) {
			assert(false);
			return bufLen - 1;
		}
		return n;
	}

	inline std::string Int64ToString(int64 text)
	{
		std::stringstream  ss;
		ss << text;
		return ss.str();
	}

	inline double Round(double number)
	{
		return (number > 0.0) ? floor(number + 0.5) : ceil(number - 0.5);
	}

	//the null-terminated output has been completely written 
	//if and only if the returned value is nonnegative and less than n
	//truncated if n >= size Buffer was too small
	//You can give complete buffer size to vsnprintf
	int SafeSnprintf(char *dest, int size, const char *fmt, ...);

	void SafeMemcpy(char* szDst, int nLenDst, const char* szSrc, int nLenDrc);

	int64 GetPerformanceCount();

	//�ַ�����ʽ��
	int		dSprintf(char *string, size_t sizeInBytes, const char *format, ...);
	int		dVsprintf(char *string, size_t sizeInBytes, const char *format, va_list _Args);
	//�����ַ���
	int32	dStrcpyMax(char *dest, uint32 size, const char *src, uint32 len);
	//��buf��ָ�ڴ������ǰcount���ֽڲ����ַ�chλ��
	void*	dMemchr(void *buf, char ch, uint32 count);
	//�ַ����в��ҵ�һ�γ���c��λ��
	char*	dStrchr(char *s, char c);
	pc_str	dStrchr(const char *s, char c);
	//�ֽ��ַ���Ϊһ���Ǵ�
	char*	dStrtok(char *s, const char *delim);
	//���ַ���ת��ΪСд��ʽ
	char*	dStrlwr(char *s);
	//���ַ���ת��Ϊ��д��ʽ
	char*	dStrupr(char *s);
	//�Ƿ���ֽ�
	int32	ismbblead(char c);
	//�ַ����Ƚ�(���ִ�Сд)
	int		dStrncmp(const char *s1, const char * s2, int n);
	//�ַ����Ƚ�(�����ִ�Сд)
	int		dStrnicmp(const char *s1, const char * s2, int n);
	//�ַ������ҵ�һ�γ��ֵ�λ��(���ִ�Сд)
	char*	dStrstr(char *haystack, char *needle);
	//�ַ������ҵ�һ�γ��ֵ�λ��(�����ִ�Сд)
	char*	dStristr(char *haystack, char *needle);

	//�����ַ�������
	uint32	dStrlen(const char* s);

#ifdef _WIN32
	//�ڴ濽��
	extern int32	dMemcpy(void *dest, size_t destSize, const void* src, size_t maxCount);
	//�ڴ��ƶ�
	extern int32	dMemmove(void *dest, size_t destSize, const void* src, size_t maxCount);
#else
	//�ڴ濽��
	extern void*	dMemcpy(void *dest, size_t destSize, const void* src, size_t maxCount);
	//�ڴ��ƶ�
	extern void*	dMemmove(void *dest, size_t destSize, const void* src, size_t maxCount);

#endif

	//http����ʹ��
	bool IsChar(int c);
	bool IsCtl(int c);
	bool IsTspecial(int c);
	bool IsDigit(int c);
}