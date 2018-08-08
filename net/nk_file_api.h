
#ifndef __NK_FILE_API_H__
#define __NK_FILE_API_H__

#include "CommonDef.h"

namespace noko{
	namespace nk_file_api 
	{
		//
		// exception version of open ()
		//
		int32 open_ex (const char* filename, int32 flags) ;

		int32 open_ex (const char* filename, int32 flags, int32 mode) ;

		//
		// exception version of close ()
		//
		void close_ex (int32 fd) ;

		//
		// exception version of read ()
		//
		uint32 read_ex (int32 fd, void* buf, uint32 len) ;

		//
		// exception version of write ()
		//
		uint32 write_ex (int32 fd, const void* buf, uint32 len) ;

		//
		// exception version of fcntl ()
		//
		int32 fcntl_ex (int32 fd, int32 cmd) ;

		//
		// exception version of fcntl ()
		//
		int32 fcntl_ex (int32 fd, int32 cmd, LONG arg) ;

		//
		// is this stream is nonblocking?
		//
		// using fcntl_ex()
		//
		bool getfilenonblocking_ex (int32 fd) ;

		//
		// make this strema blocking/nonblocking
		//
		// using fcntl_ex()
		//
		void setfilenonblocking_ex (int32 fd, bool on) ;

		//
		// exception version of ioctl ()
		//
		void ioctl_ex (int32 fd, int32 request, void* argp);
		
		//
		// make this stream blocking/nonblocking
		//
		// using ioctl_ex()
		//
		void setfilenonblocking_ex2 (int32 fd, bool on);

		//
		// how much bytes available in this stream?
		//
		// using ioctl_ex()
		//
		uint32 availablefile_ex (int32 fd);

		//
		// exception version of dup()
		//
		int32 dup_ex (int32 fd);

		//
		// exception version of lseek()
		//
		LONG lseek_ex(int32 fd, LONG offset, int32 whence);


		LONG tell_ex( int32 fd ) ;


	};//end of namespace nk_file_api
};//end of namespace noko

#endif

