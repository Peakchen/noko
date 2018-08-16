#include "nk_socket_ex.h"


#if __WINDOWS__
#include <io.h>			// for _open()
#include <fcntl.h>		// for _open()/_close()/_read()/_write()...
#include <string.h>		// for memcpy()
#elif __LINUX__
#include <sys/types.h>	// for open()
#include <sys/stat.h>	// for open()
#include <unistd.h>		// for fcntl()
#include <fcntl.h>		// for fcntl()
#include <sys/ioctl.h>	// for ioctl()
#include <errno.h>		// for errno
#endif

#if __LINUX__
extern int32 errno;
#endif

namespace noko {
	namespace nk_socket_ex
	{
		int32 nk_socket_ex::open_ex(const char * filename, int32 flags)
		{

#if __LINUX__
			int32 fd = open(filename, flags);
#elif __WINDOWS__
			int32 fd = _open(filename, flags);
#endif
			if (fd < 0) {

#if __LINUX__
				switch (errno) {
				case EEXIST:
				case ENOENT:
				case EISDIR:
				case EACCES:
				case ENAMETOOLONG:
				case ENOTDIR:
				case ENXIO:
				case ENODEV:
				case EROFS:
				case ETXTBSY:
				case EFAULT:
				case ELOOP:
				case ENOSPC:
				case ENOMEM:
				case EMFILE:
				case ENFILE:
				default:
				{
					break;
				}
				}//end of switch
#elif __WINDOWS__
				// ...
#endif
			}

			return fd;
		}


		int32 nk_socket_ex::open_ex(const char * filename, int32 flags, int32 mode)
		{

#if __LINUX__
			int32 fd = open(filename, flags, mode);
#elif __WINDOWS__
			int32 fd = _open(filename, flags, mode);
#endif

			if (fd < 0) {
#if __LINUX__
				switch (errno) {
				case EEXIST:
				case EISDIR:
				case EACCES:
				case ENAMETOOLONG:
				case ENOENT:
				case ENOTDIR:
				case ENXIO:
				case ENODEV:
				case EROFS:
				case ETXTBSY:
				case EFAULT:
				case ELOOP:
				case ENOSPC:
				case ENOMEM:
				case EMFILE:
				case ENFILE:
				default:
				{
					break;
				}
				}//end of switch
#elif __WINDOWS__
				// ...
#endif
			}

			return fd;
		}

		uint32 nk_socket_ex::read_ex(int32 fd, void * buf, uint32 len)
		{

#if __LINUX__
			int32 result = read(fd, buf, len);
#elif __WINDOWS__
			int32 result = _read(fd, buf, len);
#endif

			if (result < 0) {

#if __LINUX__
				switch (errno) {
				case Eint32R:
				case EAGAIN:
				case EBADF:
				case EIO:
				case EISDIR:
				case EINVAL:
				case EFAULT:
				case ECONNRESET:
				default:
				{
					break;
				}
				}
#elif __WINDOWS__
				// ...
#endif
			}
			else if (result == 0) {
			}

			return result;
		}


		uint32 nk_socket_ex::write_ex(int32 fd, const void * buf, uint32 len)
		{

#if __LINUX__
			int32 result = write(fd, buf, len);
#elif __WINDOWS__
			int32 result = _write(fd, buf, len);
#endif

			if (result < 0) {

#if __LINUX__
				switch (errno) {
				case EAGAIN:
				case Eint32R:
				case EBADF:
				case EPIPE:
				case EINVAL:
				case EFAULT:
				case ENOSPC:
				case EIO:
				case ECONNRESET:
				default:
				{
					break;
				}
				}
#elif __WINDOWS__
				//...
#endif
			}

			return result;
		}


		void nk_socket_ex::close_ex(int32 fd)
		{
			if (close(fd) < 0) {
#if __LINUX__
				switch (errno) {
				case EBADF:
				default:
				{
					break;
				}
				}
#elif __WINDOWS__
#endif
			}
		}


		int32 nk_socket_ex::fcntl_ex(int32 fd, int32 cmd)
		{
#if __LINUX__
			int32 result = fcntl(fd, cmd);
			if (result < 0) {
				switch (errno) {
				case Eint32R:
				case EBADF:
				case EACCES:
				case EAGAIN:
				case EDEADLK:
				case EMFILE:
				case ENOLCK:
				default:
				{
					break;
				}
				}
			}
			return result;
#elif __WINDOWS__
			return 0;
#endif
		}


		int32 nk_socket_ex::fcntl_ex(int32 fd, int32 cmd, LONG arg)
		{

#if __LINUX__
			int32 result = fcntl(fd, cmd, arg);
			if (result < 0) {
				switch (errno) {
				case Eint32R:
				case EINVAL:
				case EBADF:
				case EACCES:
				case EAGAIN:
				case EDEADLK:
				case EMFILE:
				case ENOLCK:
				default:
				{
					break;
				}
				}
			}
			return result;
#elif __WINDOWS__
			return 0;
#endif
		}

		bool nk_socket_ex::getfilenonblocking_ex(int32 fd)
		{

#if __LINUX__
			int32 flags = fcntl_ex(fd, F_GETFL, 0);
			return flags | O_NONBLOCK;
#elif __WINDOWS__
			return FALSE;
#endif
		}

		void nk_socket_ex::setfilenonblocking_ex(int32 fd, bool on)
		{
#if __LINUX__
			int32 flags = fcntl_ex(fd, F_GETFL, 0);

			if (on)
				// make nonblocking fd
				flags |= O_NONBLOCK;
			else
				// make blocking fd
				flags &= ~O_NONBLOCK;

			fcntl_ex(fd, F_SETFL, flags);
#elif __WINDOWS__
#endif
		}


		void nk_socket_ex::ioctl_ex(int32 fd, int32 request, void * argp)
		{

#if __LINUX__
			if (ioctl(fd, request, argp) < 0) {
				switch (errno) {
				case EBADF:
				case ENOTTY:
				case EINVAL:
				default:
				{
					break;
				}
				}
			}
#elif __WINDOWS__
#endif
		}


		void nk_socket_ex::setfilenonblocking_ex2(int32 fd, bool on)
		{

#if __LINUX__
			ULONG arg = (on == TRUE ? 1 : 0);
			ioctl_ex(fd, FIONBIO, &arg);
#elif __WINDOWS__
#endif
		}


		uint32 nk_socket_ex::availablefile_ex(int32 fd)
		{

#if __LINUX__
			uint32 arg = 0;
			ioctl_ex(fd, FIONREAD, &arg);
			return arg;
#elif __WINDOWS__
			return 0;
#endif
		}


		int32 nk_socket_ex::dup_ex(int32 fd)
		{

#if __LINUX__
			int32 newfd = dup(fd);
#elif __WINDOWS__
			int32 newfd = _dup(fd);
#endif

			if (newfd < 0) {
#if __LINUX__
				switch (errno) {
				case EBADF:
				case EMFILE:
				default:
				{
					break;
				}
				}//end of switch
#elif __WINDOWS__
#endif
			}

			return newfd;
		}


		LONG nk_socket_ex::lseek_ex(int32 fd, LONG offset, int32 whence)
		{

#if __LINUX__
			LONG result = lseek(fd, offset, whence);
			if (result < 0) {
				switch (errno) {
				case EBADF:
				case ESPIPE:
				case EINVAL:
				default:
				{
					break;
				}
				}
			}
#elif __WINDOWS__
			LONG result = _lseek(fd, offset, whence);
			if (result < 0) {
			}
#endif

			return result;
		}

		LONG nk_socket_ex::tell_ex(int32 fd)
		{

#if __LINUX__
			LONG result;
#elif __WINDOWS__
			LONG result = _tell(fd);
			if (result < 0) {
			}
#endif

			return result;
		}

	}
}