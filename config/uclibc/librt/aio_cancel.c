/* Cancel requests associated with given file descriptor.  Stub version.
   Copyright (C) 2001 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */


/* We use an UGLY hack to prevent gcc from finding us cheating.  The
   implementation of aio_cancel and aio_cancel64 are identical and so
   we want to avoid code duplication by using aliases.  But gcc sees
   the different parameter lists and prints a warning.  We define here
   a function so that aio_cancel64 has no prototype.  */
#define aio_cancel64 XXX
#include <aio.h>
/* And undo the hack.  */
#undef aio_cancel64

#include <errno.h>
#include <pthread.h>

int aio_cancel (int fd, struct aiocb *cb)
{
	if (!cb) {
		/* FIXME: for correctness, we should return AIO_ALLDONE
		 * if there are no outstanding aio operations on this
		 * file descriptor, but that would require making aio
		 * much slower, and seems to have little advantage since
		 * we don't support cancellation anyway. */
		return AIO_NOTCANCELED;
	}
	return cb->__err==EINPROGRESS ? AIO_NOTCANCELED : AIO_ALLDONE;
}
weak_alias (aio_cancel, aio_cancel64)
