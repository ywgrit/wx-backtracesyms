/* Support macros for making weak and strong aliases for symbols,
   and for using symbol sets and linker warnings with GNU ld.
   Copyright (C) 1995-2023 Free Software Foundation, Inc.
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

#ifndef _LIBC_SYMBOLS_H
#define _LIBC_SYMBOLS_H	1

/* This file is included implicitly in the compilation of every source file,
   using -include.  It includes config.h.  */

/* Enable declarations of GNU extensions, since we are compiling them.  */
#define _GNU_SOURCE 1

#ifdef MODULE_NAME

/* Use `#if IS_IN (module)` to detect what component is being compiled.  */
#define PASTE_NAME1(a,b) a##b
#define PASTE_NAME(a,b)	 PASTE_NAME1 (a,b)
#define IN_MODULE	 PASTE_NAME (MODULE_, MODULE_NAME)
#define IS_IN(lib)	 (IN_MODULE == MODULE_##lib)

/* True if the current module is a versioned library.  Versioned
   library names culled from shlib-versions files are assigned a
   MODULE_* value greater than MODULE_LIBS_BEGIN.  */
#define IS_IN_LIB	 (IN_MODULE > MODULE_LIBS_BEGIN)

/* The testsuite, and some other ancillary code, should be compiled against
   as close an approximation to the installed headers as possible.
   Defining this symbol disables most internal-use-only declarations
   provided by this header, and all those provided by other internal
   wrapper headers.  */
#if IS_IN (testsuite) || defined IS_IN_build || defined __cplusplus
# define _ISOMAC 1
#endif

#else
/* The generation process for a few files created very early in the
   build (notably libc-modules.h itself) involves preprocessing this
   header without defining MODULE_NAME.  Under these conditions,
   internal declarations (especially from config.h) must be visible,
   but IS_IN should always evaluate as false.  */
# define IS_IN(lib) 0
# define IS_IN_LIB 0
# define IN_MODULE (-1)
#endif

#ifndef _ISOMAC

/* This is defined for the compilation of all C library code.  features.h
   tests this to avoid inclusion of stubs.h while compiling the library,
   before stubs.h has been generated.  Some library code that is shared
   with other packages also tests this symbol to see if it is being
   compiled as part of the C library.  We must define this before including
   config.h, because it makes some definitions conditional on whether libc
   itself is being compiled, or just some generator program.  */
#define _LIBC	1

/* Some files must be compiled with optimization on.  */
/* #if !defined __ASSEMBLER__ && !defined __OPTIMIZE__ */
/* # error "glibc cannot be compiled without optimization" */
/* #endif */

/* -ffast-math cannot be applied to the C library, as it alters the ABI.
   Some test components that use -ffast-math are currently not part of
   IS_IN (testsuite) for technical reasons, so we have a secondary override.  */
#if defined __FAST_MATH__ && !defined TEST_FAST_MATH
# error "glibc must not be compiled with -ffast-math"
#endif

#include "config.h"

/* Obtain the definition of symbol_version_reference.  */
/* #include <libc-symver.h> */

/* When PIC is defined and SHARED isn't defined, we are building PIE
   by default.  */
#if defined PIC && !defined SHARED
# define BUILD_PIE_DEFAULT 1
#else
# define BUILD_PIE_DEFAULT 0
#endif

/* Define this for the benefit of portable GNU code that wants to check it.
   Code that checks with #if will not #include <config.h> again, since we've
   already done it (and this file is implicitly included in every compile,
   via -include).  Code that checks with #ifdef will #include <config.h>,
   but that file should always be idempotent (i.e., it's just #define/#undef
   and nothing else anywhere should be changing the macro state it touches),
   so it's harmless.  */
#define HAVE_CONFIG_H	0

/* Define these macros for the benefit of portable GNU code that wants to check
   them.  Of course, STDC_HEADERS is never false when building libc!  */
#define STDC_HEADERS	1
#define HAVE_MBSTATE_T	1
#define HAVE_MBSRTOWCS	1
#define HAVE_LIBINTL_H	1
#define HAVE_WCTYPE_H	1
#define HAVE_ISWCTYPE	1
#define ENABLE_NLS	1

/* The symbols in all the user (non-_) macros are C symbols.  */

#ifndef __SYMBOL_PREFIX
# define __SYMBOL_PREFIX
#endif

#ifndef C_SYMBOL_NAME
# define C_SYMBOL_NAME(name) name
#endif

#ifndef ASM_LINE_SEP
# define ASM_LINE_SEP ;
#endif

#ifndef __attribute_copy__
/* Provide an empty definition when cdefs.h is not included.  */
# define __attribute_copy__(arg)
#endif

#ifndef __ASSEMBLER__
/* GCC understands weak symbols and aliases; use its interface where
   possible, instead of embedded assembly language.  */

/* Define ALIASNAME as a strong alias for NAME.  */
# define strong_alias(name, aliasname) _strong_alias(name, aliasname)
# define _strong_alias(name, aliasname) \
  extern __typeof (name) aliasname __attribute__ ((alias (#name))) \
    __attribute_copy__ (name);

/* This comes between the return type and function name in
   a function definition to make that definition weak.  */
# define weak_function __attribute__ ((weak))
# define weak_const_function __attribute__ ((weak, __const__))

/* Define ALIASNAME as a weak alias for NAME.
   If weak aliases are not available, this defines a strong alias.  */
# define weak_alias(name, aliasname) _weak_alias (name, aliasname)
# define _weak_alias(name, aliasname) \
  extern __typeof (name) aliasname __attribute__ ((weak, alias (#name))) \
    __attribute_copy__ (name);

/* Declare SYMBOL as weak undefined symbol (resolved to 0 if not defined).  */
# define weak_extern(symbol) _weak_extern (weak symbol)
# define _weak_extern(expr) _Pragma (#expr)

/* In shared builds, the expression call_function_static_weak
   (FUNCTION-SYMBOL, ARGUMENTS) invokes FUNCTION-SYMBOL (an
   identifier) unconditionally, with the (potentially empty) argument
   list ARGUMENTS.  In static builds, if FUNCTION-SYMBOL has a
   definition, the function is invoked as before; if FUNCTION-SYMBOL
   is NULL, no call is performed.  */
# ifdef SHARED
#  define call_function_static_weak(func, ...) func (__VA_ARGS__)
# else	/* !SHARED */
#  define call_function_static_weak(func, ...)		\
  ({							\
    extern __typeof__ (func) func weak_function;	\
    (func != NULL ? func (__VA_ARGS__) : (void)0);	\
  })
# endif

#else /* __ASSEMBLER__ */

# ifdef HAVE_ASM_SET_DIRECTIVE
#  define strong_alias(original, alias)				\
  .globl C_SYMBOL_NAME (alias) ASM_LINE_SEP		\
  .set C_SYMBOL_NAME (alias),C_SYMBOL_NAME (original)
#  define strong_data_alias(original, alias) strong_alias(original, alias)
# else
#  define strong_alias(original, alias)				\
  .globl C_SYMBOL_NAME (alias) ASM_LINE_SEP		\
  C_SYMBOL_NAME (alias) = C_SYMBOL_NAME (original)
#  define strong_data_alias(original, alias) strong_alias(original, alias)
# endif

# define weak_alias(original, alias)					\
  .weak C_SYMBOL_NAME (alias) ASM_LINE_SEP				\
  C_SYMBOL_NAME (alias) = C_SYMBOL_NAME (original)

# define weak_extern(symbol)						\
  .weak C_SYMBOL_NAME (symbol)

#endif /* __ASSEMBLER__ */

/* Determine the return address.  */
#define RETURN_ADDRESS(nr) \
  __builtin_extract_return_addr (__builtin_return_address (nr))

/* When a reference to SYMBOL is encountered, the linker will emit a
   warning message MSG.  */
/* We want the .gnu.warning.SYMBOL section to be unallocated.  */
#define __make_section_unallocated(section_string)	\
  asm (".section " section_string "\n\t.previous");

/* Tacking on "\n\t#" to the section name makes gcc put it's bogus
   section attributes on what looks like a comment to the assembler.  */
#ifdef HAVE_SECTION_QUOTES
# define __sec_comment "\"\n\t#\""
#else
# define __sec_comment "\n\t#"
#endif
#define link_warning(symbol, msg) \
  __make_section_unallocated (".gnu.warning." #symbol) \
  static const char __evoke_link_warning_##symbol[]	\
    __attribute__ ((used, section (".gnu.warning." #symbol __sec_comment))) \
    = msg;

/* A canned warning for sysdeps/stub functions.  */
#define	stub_warning(name) \
  __make_section_unallocated (".gnu.glibc-stub." #name) \
  link_warning (name, #name " is not implemented and will always fail")

/* Warning for linking functions calling dlopen into static binaries.  */
#ifdef SHARED
#define static_link_warning(name)
#else
#define static_link_warning(name) static_link_warning1(name)
#define static_link_warning1(name) \
  link_warning(name, "Using '" #name "' in statically linked applications \
requires at runtime the shared libraries from the glibc version used \
for linking")
#endif

/* Declare SYMBOL to be TYPE (`function' or `object') of SIZE bytes
   alias to ORIGINAL, when the assembler supports such declarations
   (such as in ELF).
   This is only necessary when defining something in assembly, or playing
   funny alias games where the size should be other than what the compiler
   thinks it is.  */
#define declare_object_symbol_alias(symbol, original, size) \
  declare_object_symbol_alias_1 (symbol, original, size)
#ifdef __ASSEMBLER__
# define declare_object_symbol_alias_1(symbol, original, s_size) \
   strong_alias (original, symbol) ASM_LINE_SEP \
   .type C_SYMBOL_NAME (symbol), %object ASM_LINE_SEP \
   .size C_SYMBOL_NAME (symbol), s_size ASM_LINE_SEP
#else /* Not __ASSEMBLER__.  */
# ifdef HAVE_ASM_SET_DIRECTIVE
#  define declare_object_symbol_alias_1(symbol, original, size) \
     asm (".global " __SYMBOL_PREFIX # symbol "\n" \
	  ".type " __SYMBOL_PREFIX # symbol ", %object\n" \
	  ".set " __SYMBOL_PREFIX #symbol ", " __SYMBOL_PREFIX original "\n" \
	  ".size " __SYMBOL_PREFIX #symbol ", " #size "\n");
# else
#  define declare_object_symbol_alias_1(symbol, original, size) \
     asm (".global " __SYMBOL_PREFIX # symbol "\n" \
	  ".type " __SYMBOL_PREFIX # symbol ", %object\n" \
	  __SYMBOL_PREFIX #symbol " = " __SYMBOL_PREFIX original "\n" \
	  ".size " __SYMBOL_PREFIX #symbol ", " #size "\n");
# endif /* HAVE_ASM_SET_DIRECTIVE */
#endif /* __ASSEMBLER__ */


/*

*/

#ifdef HAVE_GNU_RETAIN
# define attribute_used_retain __attribute__ ((__used__, __retain__))
#else
# define attribute_used_retain __attribute__ ((__used__))
#endif

/* Symbol set support macros.  */

/* Make SYMBOL, which is in the text segment, an element of SET.  */
#define text_set_element(set, symbol)	_elf_set_element(set, symbol)
/* Make SYMBOL, which is in the data segment, an element of SET.  */
#define data_set_element(set, symbol)	_elf_set_element(set, symbol)
/* Make SYMBOL, which is in the bss segment, an element of SET.  */
#define bss_set_element(set, symbol)	_elf_set_element(set, symbol)

/* These are all done the same way in ELF.
   There is a new section created for each set.  */
#ifdef SHARED
/* When building a shared library, make the set section writable,
   because it will need to be relocated at run time anyway.  */
# define _elf_set_element(set, symbol) \
    static const void *__elf_set_##set##_element_##symbol##__ \
      attribute_used_retain __attribute__ ((section (#set))) = &(symbol)
#else
# define _elf_set_element(set, symbol) \
    static const void *const __elf_set_##set##_element_##symbol##__ \
      attribute_used_retain __attribute__ ((section (#set))) = &(symbol)
#endif

/* Define SET as a symbol set.  This may be required (it is in a.out) to
   be able to use the set's contents.  */
#define symbol_set_define(set)	symbol_set_declare(set)

/* Declare SET for use in this module, if defined in another module.
   In a shared library, this is always local to that shared object.
   For static linking, the set might be wholly absent and so we use
   weak references.  */
#define symbol_set_declare(set) \
  extern char const __start_##set[] __symbol_set_attribute; \
  extern char const __stop_##set[] __symbol_set_attribute;
#ifdef SHARED
# define __symbol_set_attribute attribute_hidden
#else
# define __symbol_set_attribute __attribute__ ((weak))
#endif

/* Return a pointer (void *const *) to the first element of SET.  */
#define symbol_set_first_element(set)	((void *const *) (&__start_##set))

/* Return true iff PTR (a void *const *) has been incremented
   past the last element in SET.  */
#define symbol_set_end_p(set, ptr) ((ptr) >= (void *const *) &__stop_##set)

#ifdef SHARED
# define symbol_version(real, name, version) \
  symbol_version_reference(real, name, version)
# define default_symbol_version(real, name, version) \
     _default_symbol_version(real, name, version)
/* See <libc-symver.h>.  */
# ifdef __ASSEMBLER__
#  define _default_symbol_version(real, name, version) \
  _set_symbol_version (real, name@@version)
# else
#  define _default_symbol_version(real, name, version) \
  _set_symbol_version (real, #name "@@" #version)
# endif

/* Evalutes to a string literal for VERSION in LIB.  */
# define symbol_version_string(lib, version) \
  _symbol_version_stringify_1 (VERSION_##lib##_##version)
# define _symbol_version_stringify_1(arg) _symbol_version_stringify_2 (arg)
# define _symbol_version_stringify_2(arg) #arg

#else /* !SHARED */
# define symbol_version(real, name, version)
# define default_symbol_version(real, name, version) \
  strong_alias(real, name)
#endif

#if defined SHARED || defined LIBC_NONSHARED \
  || (BUILD_PIE_DEFAULT && IS_IN (libc))
# define attribute_hidden __attribute__ ((visibility ("hidden")))
#else
# define attribute_hidden
#endif


#endif /* !_ISOMAC */
#endif /* libc-symbols.h */
