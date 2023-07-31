/* Run-time dynamic linker data structures for loaded ELF shared objects.
   Copyright (C) 2001-2023 Free Software Foundation, Inc.
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
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#ifndef	_LDSODEFS_H

/* We have the auxiliary vector.  */
#define HAVE_AUX_VECTOR

/* Get the real definitions.  */
/* #include_next <ldsodefs.h> */
/* #include "../../../microblaze/ldsodefs.h" */
/* #include "../../../arc/ldsodefs.h" */
/* #include "../../../sparc/ldsodefs.h" */
/* #include "../../../alpha/ldsodefs.h" */
/* #include "../../../unix/sysv/linux/mips/ldsodefs.h" */
/* #include "../../../unix/sysv/linux/powerpc/powerpc64/ldsodefs.h" */
/* #include "../../../unix/sysv/linux/arm/ldsodefs.h" */
#include "../../../x86/ldsodefs.h"

#endif /* ldsodefs.h */
