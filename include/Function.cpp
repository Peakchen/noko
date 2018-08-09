
#include "Function.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <utility>

namespace noko
{

	std::string UnSerializeFromString(const std::map<int, std::string> & map, char seperator)
	{
		if (map.empty())
		{
			return "";
		}

		std::stringstream ss;
		for (auto it = map.begin(); it != map.end(); ++it)
		{
			ss << it->first << seperator << it->second;
			if (it->first != map.rbegin()->first)
			{
				ss << "|";
			}
		}

		char lastElement;
		ss >> lastElement;

		return std::move(ss.str());
	}

	std::string UnSerializeFromString(const std::map<int, std::string> & map)
	{
		return std::move(UnSerializeFromString(map, '='));
	}

	void GetReplaceString(std::string& dstStr, std::string szSrc, std::string szNeed)
	{
		// Դ�ַ�������Ϊ0��������Ҫ���ַ�������Ϊ0
		if (szSrc.length() == 0 || szNeed.length() == 0)
		{
			return;
		}

		for (std::string::size_type pos(0); pos != std::string::npos; pos += szNeed.length())
		{
			if ((pos = dstStr.find("&", pos)) != std::string::npos)
			{
				dstStr.replace(pos, szSrc.length(), szNeed);
			}
			else {
				break;
			}
		}
	}

	void DeleteStr(const char *str, const char* sub_str, std::string& dstData)
	{
		int sublen = 0;         //����Ӵ��ĳ���
		const char *t = sub_str;
		while (*t++ != '\0')
		{
			sublen++;
		}

		int pos = 0;
		int pp = 0;
		int repos = 0; // ����Ӵ�������

		char result[1024] = { 0 };

		while (*(str + pos) != '\0')
		{
			char t = *(str + pos);
			if (t == *(sub_str + pp)) // �ظ��Ӵ���ʼλ��
			{
				*(result + repos) = t;
				repos++;

				if (pp < sublen - 1) // ��δ��ȫ�ظ�
				{
					pp++;
				}
				else if (pp == sublen - 1) // ��ȫ�ظ���
				{
					pp = 0;
					repos -= sublen; // �����±�λ��
				}
			}
			else { // ����һ�����ַ�
				*(result + repos) = t;
				repos++;
			}
			pos++;
		}
		*(result + repos) = '\0';
		dstData = result;
		//std::cout << result << endl;
	}

	bool IsTwentyFourPoints()
	{
		struct tm *today;
		time_t  ltime = time(0);
		today = localtime(&ltime);
		if (today->tm_hour == 0 && today->tm_min == 0
			&& (today->tm_sec >= 0 && today->tm_sec <= 59))  // ʱ����
		{
			return true;
		}

		return false;

	}

	BOOL IsTextUTF8(const char* str, int nLength)
	{
		DWORD nBytes = 0;//UFT8����1-6���ֽڱ���,ASCII��һ���ֽ�  
		UCHAR chr;
		BOOL bAllAscii = TRUE; //���ȫ������ASCII, ˵������UTF-8  
		for (int i = 0; i < nLength; ++i)
		{
			chr = *(str + i);
			if ((chr & 0x80) != 0) // �ж��Ƿ�ASCII����,�������,˵���п�����UTF-8,ASCII��7λ����,����һ���ֽڴ�,���λ���Ϊ0,o0xxxxxxx  
				bAllAscii = FALSE;
			if (nBytes == 0) //�������ASCII��,Ӧ���Ƕ��ֽڷ�,�����ֽ���  
			{
				if (chr >= 0x80)
				{
					if (chr >= 0xFC && chr <= 0xFD)
						nBytes = 6;
					else if (chr >= 0xF8)
						nBytes = 5;
					else if (chr >= 0xF0)
						nBytes = 4;
					else if (chr >= 0xE0)
						nBytes = 3;
					else if (chr >= 0xC0)
						nBytes = 2;
					else
						return FALSE;

					nBytes--;
				}
			}
			else //���ֽڷ��ķ����ֽ�,ӦΪ 10xxxxxx  
			{
				if ((chr & 0xC0) != 0x80)
					return FALSE;

				nBytes--;
			}
		}
		if (nBytes > 0) //Υ������  
			return FALSE;
		if (bAllAscii) //���ȫ������ASCII, ˵������UTF-8  
			return FALSE;

		return TRUE;
	}

	std::string StringToUTF8(const std::string& str)
	{
		if (IsTextUTF8(str.c_str(), str.length()))
			return str;
		int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

		wchar_t * pwBuf = new wchar_t[nwLen + 1];//һ��Ҫ��1����Ȼ�����β��  
		ZeroMemory(pwBuf, nwLen * 2 + 2);

		::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

		int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

		char * pBuf = new char[nLen + 1];
		ZeroMemory(pBuf, nLen + 1);

		::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

		std::string retStr(pBuf);

		delete[] pwBuf;
		delete[] pBuf;

		pwBuf = nullptr;
		pBuf = nullptr;

		return retStr;
	}

	std::string UTF8ToString(const std::string& str)
	{
		int nwLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);

		//һ��Ҫ��1����Ȼ�����β��  
		wchar_t * pwBuf = new wchar_t[nwLen + 1];
		memset(pwBuf, 0, nwLen * 2 + 2);

		MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), pwBuf, nwLen);

		int nLen = WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

		char * pBuf = new char[nLen + 1];
		memset(pBuf, 0, nLen + 1);

		WideCharToMultiByte(CP_ACP, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

		std::string retStr = pBuf;

		delete[] pBuf;
		delete[] pwBuf;

		pBuf = nullptr;
		pwBuf = nullptr;

		return retStr;
	}

	std::string UnicodeToANSI(const std::wstring &unicodeStr)
	{
		char* pBuf = nullptr;
		int textlen = 0;
		textlen = WideCharToMultiByte(CP_ACP, 0, unicodeStr.c_str(), -1, NULL, 0, NULL, NULL);
		pBuf = new char[(textlen + 1) * sizeof(char)];
		memset(pBuf, 0, sizeof(char)* (textlen + 1));

		WideCharToMultiByte(CP_ACP, 0, unicodeStr.c_str(), -1, pBuf, textlen, NULL, NULL);

		std::string retStr(pBuf);

		delete[] pBuf;

		return retStr;
	}

	std::wstring UTF8ToUnicode(const std::string &utf8Str)
	{
		int textlen = 0;
		wchar_t * pBuf = nullptr;
		textlen = MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, NULL, 0);
		pBuf = new wchar_t[(textlen + 1) * sizeof(wchar_t)];
		memset(pBuf, 0, (textlen + 1) * sizeof(wchar_t));

		MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, (LPWSTR)pBuf, textlen);

		std::wstring retStr(pBuf);

		delete[] pBuf;

		return retStr;
	}

	std::string UnicodeToUtf8(const std::wstring &unicodeStr)
	{
		int len = ::WideCharToMultiByte(CP_UTF8, 0, unicodeStr.c_str(), -1, NULL, 0, NULL, NULL);
		if (len == 0)
		{
			return "";
		}

		char* pBuf = new char[(len + 1) * sizeof(char)];
		memset(pBuf, 0, sizeof(char)* (len + 1));

		::WideCharToMultiByte(CP_UTF8, 0, unicodeStr.c_str(), -1, pBuf, len, NULL, NULL);

		std::string retStr(pBuf);

		delete[] pBuf;

		return retStr;
	}

	std::string UTF8ToANSI(const std::string &utf8Str)
	{
		std::wstring wstr = UTF8ToUnicode(utf8Str);
		return UnicodeToANSI(wstr);
	}

	std::string ANSIToUTF8(const std::string &ansiStr)
	{
		std::wstring wstr = ANSIToUnicode(ansiStr);
		return UnicodeToUtf8(wstr);
	}

	std::wstring ANSIToUnicode(const std::string &ansiStr)
	{
		int len = ::MultiByteToWideChar(CP_ACP, 0, ansiStr.c_str(), -1, NULL, 0);
		if (len == 0)
		{
			return L"";
		}

		wchar_t * pBuf = new wchar_t[(len + 1) * sizeof(wchar_t)];
		memset(pBuf, 0, (len + 1) * sizeof(wchar_t));

		::MultiByteToWideChar(CP_ACP, 0, ansiStr.c_str(), -1, pBuf, len);

		std::wstring retStr(pBuf);

		delete[] pBuf;

		return retStr;
	}

	void SetWorkDirectory(const std::string strPath)
	{
		if (strPath.empty())
			return;

#ifdef _WIN32
		::SetCurrentDirectoryA(strPath.c_str());
#else//_WIN32
		::chdir(strPath.c_str());
#endif///_WIN32
	}

	std::string GetCurrentPath()
	{
		std::string strPath;
		char path[280] = { 0 };
		int32 len = 0;

#ifdef _WIN32
		len = ::GetModuleFileNameA(0, path, MAX_PATH);
#else
		FILE* stream = fopen("/proc/self/cmdline", "r");
		fgets(path, 280, stream);
		fclose(stream);
		len = strlen(path);

		//std::cout << "server path: " << path << std::endl;
#endif

		if (len > 0)
		{
			while (len > 0 && path[len] != '\\')
			{
				len--;
			}

			if (path[len] == '\\')
				path[len + 1] = 0;

			strPath.assign(path, len + 1);
		}

		return strPath;
	}


	void TruncationString(const std::string& str, std::string& res1, std::string& res2, char c)
	{
		bool bFind = false;

		for (auto it = str.begin(); it != str.end(); ++it)
		{
			if (*it == c)
			{
				bFind = true;
			}
			else if (bFind)
			{
				res2 += *it;
			}
			else
			{
				res1 += *it;
			}
		}

	}

	std::string ExtractString(const std::string& str, char begin, char end)
	{
		std::string result = "";
		bool bFind = false;

		for (auto it = str.begin(); it != str.end(); ++it)
		{
			if (*it == begin)
			{
				result += *it;
				bFind = true;
			}
			else if (*it == end)
			{
				result += *it;
				break;
			}
			else if (bFind)
				result += *it;
		}

		return result;
	}

	int SafeSnprintf(char *dest, int size, const char *fmt, ...)
	{
		va_list ap;
		va_start(ap, fmt);
		int n = vsnprintf(dest, size, fmt, ap);
		va_end(ap);

		assert(n >= 0);
		return n;
	}

	//--- �ַ�����ʽ��
	int dSprintf(char* string, size_t sizeInBytes, const char* format, ...)
	{
		if (!string || !sizeInBytes || !format)
			return 0;

		int iRes = 0;
		va_list	argptr;
		va_start(argptr, format);
#ifdef _WIN32
		iRes = ::vsprintf_s(string, sizeInBytes, format, argptr);
#else //_WIN32
		iRes = ::vsprintf(string, format, argptr);
#endif //_WIN32
		va_end(argptr);

		return iRes;
	}

	//--- �����ַ���
	extern	int32 dStrcpyMax(char* dst, uint32 _size, const char* src, uint32 len)
	{
		if (len >= _size)
			len = _size - 1;

		dMemcpy(dst, _size, src, len);

		return len;
	}

#ifdef _WIN32
	//--- �ڴ濽��
	int32 dMemcpy(void* dest, size_t destSize, const void* src, size_t maxCount)
	{
		return ::memcpy_s(dest, destSize, src, maxCount);
	}


	//--- �ڴ��ƶ�
	int32 dMemmove(void *dest, size_t destSize, const void* src, size_t maxCount)
	{
		return ::memmove_s(dest, destSize, src, maxCount);
	}
#else
	//--- �ڴ濽��
	void* dMemcpy(void* dest, size_t destSize, const void* src, size_t maxCount)
	{
		if (!dest || !destSize || !src || !maxCount)
			return dest;

		if (maxCount > destSize)
			maxCount = destSize;

		return ::memcpy((char*)dest, (char*)src, maxCount);
	}

	//--- �ڴ��ƶ�
	void* dMemmove(void *dest, size_t destSize, const void* src, size_t maxCount)
	{
		if (!dest || !destSize || !src || !maxCount)
			return dest;

		if (maxCount > destSize)
			maxCount = destSize;

		return ::memmove((char*)dest, (char*)src, maxCount);
	}
#endif
	//--- ��buf��ָ�ڴ������ǰcount���ֽڲ����ַ�chλ��
	void* dMemchr(void *buf, char ch, uint32 count)
	{
		return ::memchr(buf, ch, count);
	}

	//--- �ַ����в��ҵ�һ�γ���c��λ��
	char* dStrchr(char* s, char c)
	{
		return ::strchr(s, c);
	}

	const char* dStrchr(const char* s, char c)
	{
		return ::strchr(s, c);
	}

	//--- �ֽ��ַ���Ϊһ���Ǵ�
	char* dStrtok(char* s, const char* delim)
	{
		return ::strtok(s, delim);
	}

	//--- ���ַ���ת��ΪСд��ʽ
	char* dStrlwr(char* s)
	{
#ifdef _WIN32
		return ::_strlwr(s);
#else //_WIN32
		if (s)
		{
			char* cp;
			for (cp = s; *cp; ++cp)
			{
				if ('A' <= *cp && *cp <= 'Z')
					*cp += 'a' - 'A';
			}
		}
		return(s);
#endif //_WIN32
	}

	//--- ���ַ���ת��Ϊ��д��ʽ
	char* dStrupr(char* s)
	{
#ifdef _WIN32
		return ::_strupr(s);
#else //_WIN32
		if (s)
		{
			char* cp;
			for (cp = s; *cp; ++cp)
			{
				if (('a' <= *cp) && (*cp <= 'z'))
					*cp -= 'a' - 'A';
			}
		}

		return(s);
#endif //_WIN32
	}

	//--- �Ƿ���ֽ�
	int32	ismbblead(char c)
	{
		/*�Ƿ���ֽ�*/
#ifdef _WIN32
		return ::_ismbblead(c);
#else //_WIN32
		return ((unsigned char)(c) & 0x04);
		/*if (( (unsigned char )test_array[k]>=0xA1 && (unsigned char )test_array[k]<=0xF7)
		&&
		((unsigned char )test_array[k+1]>=0xA1&&(unsigned char )test_array[k+1]<=0xFE))
		{
		if (begin==0)
		begin=k;
		tmp_array[i]=test_array[k];
		tmp_array[i+1]=test_array[k+1];
		k=k+2;
		i=i+2;
		have_chinese=1;
		if (flag==1)
		have_chinese=2;
		}*/
#endif //_WIN32
	}

	//--- �ַ����Ƚ�(���ִ�Сд)
	int dStrncmp(const char* s1, const char* s2, int n)
	{
		return ::strncmp(s1, s2, n);
	}

	//--- �ַ����Ƚ�(�����ִ�Сд)
	int dStrnicmp(const char* s1, const char* s2, int n)
	{
#ifdef _WIN32
		return ::_strnicmp(s1, s2, n);
#else //_WIN32
		//return strcasecmp(s1, s2);
		if (s1 && s2 && n > 0)
		{
			int f = 0;
			int l = 0;

			do
			{

				if (((f = (unsigned char)(*(s1++))) >= 'A') &&
					(f <= 'Z'))
					f -= 'A' - 'a';

				if (((l = (unsigned char)(*(s2++))) >= 'A') &&
					(l <= 'Z'))
					l -= 'A' - 'a';

			} while (--n && f && (f == l));

			return (f - l);
		}
		return 0;
#endif //_WIN32
	}

	//--- �ַ������ҵ�һ�γ��ֵ�λ��(���ִ�Сд)
	char* dStrstr(char* haystack, char* needle)
	{
		return ::strstr(haystack, needle);
	}

	//--- �����ַ�������
	uint32 dStrlen(const char* s)
	{
		return (uint32)::strlen(s);
	}

	//--- �ַ������ҵ�һ�γ��ֵ�λ��(�����ִ�Сд)
	char* dStristr(char* haystack, char* needle)
	{
		//strcasestr(haystack, needle);
		int len = dStrlen(needle);
		if (len == 0)
			return haystack;										/* �����Ҳ�δ��strstrһ������str�����Ƿ���NULL*/

		while (*haystack)
		{
			/* ����ʹ���˿��޶��Ƚϳ��ȵ�strnicmp*/
			if (dStrnicmp(haystack, needle, len) == 0)
				return haystack;
			haystack++;
		}
		return NULL;
	}

	//--- �ַ�����ӡ
	int dPrintf(const char* format, ...)
	{
		if (!format)
			return 0;

		int iRes = 0;
		va_list	argptr;
		va_start(argptr, format);
#ifdef _WIN32
		iRes = ::vprintf_s(format, argptr);
#else //_WIN32
		iRes = ::vprintf(format, argptr);
#endif //_WIN32
		va_end(argptr);

		return iRes;
	}

	//---
	int dVprintf(const char* format, va_list _Args)
	{
		if (!format)
			return 0;

		int iRes = 0;
#ifdef _WIN32
		iRes = ::vprintf_s(format, _Args);
#else //_WIN32
		iRes = ::vprintf(format, _Args);
#endif //_WIN32

		return iRes;
	}

	int64 GetPerformanceCount()
	{
#ifdef _WIN32
		LARGE_INTEGER litmp;
		::QueryPerformanceCounter(&litmp);
		return (int64)litmp.QuadPart;
#else
		register int64 ticks;
		__asm__ volatile (".byte 0x0f, 0x31" : "=A" (ticks));
		return ticks;
#endif
	}

	int dVsprintf(char* string, size_t sizeInBytes, const char* format, va_list _Args)
	{
		if (!string || !sizeInBytes || !format)
			return 0;

		int iRes = 0;
#ifdef _WIN32
		iRes = ::vsprintf_s(string, sizeInBytes, format, _Args);
#else //_WIN32
		iRes = ::vsprintf(string, format, _Args);
#endif //_WIN32

		return iRes;
	}

	void SafeMemcpy(char* szDst, int nLenDst, const char* szSrc, int nLenDrc)
	{
		int nLenToCopy = 0;

		do {
			if ((nullptr == szDst) || (nullptr == szSrc))
			{
				break;
			}

			nLenToCopy = (nLenDrc < nLenDst) ? nLenDrc : nLenDst;
			memset(szDst, 0, nLenDst);

			if (nLenToCopy <= 0)
			{
				break;
			}

			memcpy(szDst, szSrc, nLenToCopy);
		} while (0);
	}


	bool IsChar(int c)
	{
		return c >= 0 && c <= 127;
	}

	bool IsCtl(int c)
	{
		return (c >= 0 && c <= 31) || (c == 127);
	}

	bool IsTspecial(int c)
	{
		switch (c)
		{
		case '(': case ')': case '<': case '>': case '@':
		case ',': case ';': case ':': case '\\': case '"':
		case '/': case '[': case ']': case '?': case '=':
		case '{': case '}': case ' ': case '\t':
			return true;
		default:
			return false;
		}
	}

	bool IsDigit(int c)
	{
		return c >= '0' && c <= '9';
	}

}