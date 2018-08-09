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

	// 不包括max=> [0, max)
	inline unsigned long ulrand(unsigned long max) {
		return max == 0 ? max : ulrand() % max;
	}

	// 不包括to=> (from, to]
	inline unsigned long ulrand(unsigned long from, unsigned long to) {
		return from >= to ? to : (ulrand() % (to - from) + from + 1);
	}

	std::string UnSerializeFromString(const std::map<int, std::string> & map);
	std::string UnSerializeFromString(const std::map<int, std::string> & map, char seperator);

	/* 取得 替换字符串
	@param 1:	std::string& dstStr  目标字符串
	@param 2:   std::string szSrc	 查找的字符串
	@param 3:	std::string szNeed	 最终替换的字符串
	return void
	*/

	void GetReplaceString(std::string& dstStr, std::string szSrc, std::string szNeed);

	void DeleteStr(const char *str, const char* sub_str, std::string& dstData);

	bool IsTwentyFourPoints();

	void SafeMemcpy(char* szDst, int nLenDst, const char* szSrc, int nLenDrc);

	BOOL IsTextUTF8(const char* str, int nLength);

	//普通sting类型 转UTF-8编码格式字符串
	std::string StringToUTF8(const std::string& str);

	//UTF-8编码格式字符串  转普通sting类型
	std::string UTF8ToString(const std::string& str);

	//ansi先转到Unicode，再到UTF-8,反过来亦然。
	std::string UnicodeToANSI(const std::wstring &unicodeStr);
	std::wstring ANSIToUnicode(const std::string &ansiStr);

	std::wstring UTF8ToUnicode(const std::string &utf8Str);
	std::string UnicodeToUtf8(const std::wstring &unicodeStr);

	std::string UTF8ToANSI(const std::string &utf8Str);
	std::string ANSIToUTF8(const std::string &ansiStr);

	//设置工作目录
	extern void			SetWorkDirectory(const std::string strPath);
	//读取服务器所在的路径
	extern std::string	GetCurrentPath();

	//提取字符串
	std::string ExtractString(const std::string& str, char begin, char end);
	//截断字符串
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

	//字符串格式化
	int		dSprintf(char *string, size_t sizeInBytes, const char *format, ...);
	int		dVsprintf(char *string, size_t sizeInBytes, const char *format, va_list _Args);
	//拷贝字符串
	int32	dStrcpyMax(char *dest, uint32 size, const char *src, uint32 len);
	//从buf所指内存区域的前count个字节查找字符ch位置
	void*	dMemchr(void *buf, char ch, uint32 count);
	//字符串中查找第一次出现c的位置
	char*	dStrchr(char *s, char c);
	pc_str	dStrchr(const char *s, char c);
	//分解字符串为一组标记串
	char*	dStrtok(char *s, const char *delim);
	//将字符串转换为小写形式
	char*	dStrlwr(char *s);
	//将字符串转换为大写形式
	char*	dStrupr(char *s);
	//是否宽字节
	int32	ismbblead(char c);
	//字符串比较(区分大小写)
	int		dStrncmp(const char *s1, const char * s2, int n);
	//字符串比较(不区分大小写)
	int		dStrnicmp(const char *s1, const char * s2, int n);
	//字符串查找第一次出现的位置(区分大小写)
	char*	dStrstr(char *haystack, char *needle);
	//字符串查找第一次出现的位置(不区分大小写)
	char*	dStristr(char *haystack, char *needle);

	//计算字符串长度
	uint32	dStrlen(const char* s);

#ifdef _WIN32
	//内存拷贝
	extern int32	dMemcpy(void *dest, size_t destSize, const void* src, size_t maxCount);
	//内存移动
	extern int32	dMemmove(void *dest, size_t destSize, const void* src, size_t maxCount);
#else
	//内存拷贝
	extern void*	dMemcpy(void *dest, size_t destSize, const void* src, size_t maxCount);
	//内存移动
	extern void*	dMemmove(void *dest, size_t destSize, const void* src, size_t maxCount);

#endif

	//http解析使用
	bool IsChar(int c);
	bool IsCtl(int c);
	bool IsTspecial(int c);
	bool IsDigit(int c);
}