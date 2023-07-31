/* config.h.  Generated from config.h.in by configure.  */
/* Define if building with SELinux support.  Set by --with-selinux.  */
#define HAVE_SELINUX 1

/* Defined if building with SELinux support & audit libs are detected. */
/* #undef HAVE_LIBAUDIT */

/* Defined if building with SELinux support & libcap libs are detected.  */
/* #undef HAVE_LIBCAP */

/* Define to the assembler line separator character for multiple
   assembler instructions per line.  Default is `;'  */
/* #undef ASM_LINE_SEP */

/* Define if __attribute__((section("foo"))) puts quotes around foo.  */
/* #undef HAVE_SECTION_QUOTES */

/* Define if the assembler supports the `.set' directive.  */
#define HAVE_ASM_SET_DIRECTIVE 1

/* On powerpc64, use overlapping .opd entries.  */
/* #undef USE_PPC64_OVERLAPPING_OPD */

/* On powerpc64, use @notoc.  */
/* #undef USE_PPC64_NOTOC */

/* On powerpc64, define if the compiler supports -mcpu=power10.  */
/* #undef USE_PPC64_MCPU_POWER10 */

/* On powerpc*, define if scv should be used for syscalls (when available).  */
#define USE_PPC_SCV 1

/* Define if _Unwind_Find_FDE should be exported from glibc.  */
/* #undef EXPORT_UNWIND_FIND_FDE */

/* Define if static NSS modules are wanted.  */
/* #undef DO_STATIC_NSS */

/* Assume that the compiler supports __builtin_expect.
   This macro is necessary for proper compilation of code
   shared between GNU libc and GNU gettext projects.  */
#define HAVE_BUILTIN_EXPECT 1

/* Define if the compiler supports __builtin_memset.  */
#define HAVE_BUILTIN_MEMSET 1

/* Define if compiler accepts -ftree-loop-distribute-patterns.  */
#define HAVE_CC_INHIBIT_LOOP_TO_LIBCALL 1

/* Define if compiler accepts -fno-stack-protector in an
   __attribute__ ((__optimize__)).  */
#define HAVE_CC_NO_STACK_PROTECTOR 1

/* The level of stack protection in use for glibc as a whole.
   May be overridden on a file-by-file basis.  */
#ifndef STACK_PROTECTOR_LEVEL
#define STACK_PROTECTOR_LEVEL 0
#endif

/* Define if _rtld_local structure should be forced into .sdata section.  */
/* #undef HAVE_SDATA_SECTION */

/* Define if assembler supports z10 zarch instructions as default on S390.  */
/* #undef HAVE_S390_MIN_Z10_ZARCH_ASM_SUPPORT */

/* Define if assembler supports z196 zarch instructions as default on S390.  */
/* #undef HAVE_S390_MIN_Z196_ZARCH_ASM_SUPPORT */

/* Define if assembler supports z13 zarch instructions as default on S390.  */
/* #undef HAVE_S390_MIN_Z13_ZARCH_ASM_SUPPORT */

/* Define if assembler supports arch13 zarch instruction as default on S390.  */
/* #undef HAVE_S390_MIN_ARCH13_ZARCH_ASM_SUPPORT */

/* Define if assembler supports vector instructions on S390.  */
/* #undef HAVE_S390_VX_ASM_SUPPORT */

/* Define if gcc supports vector registers as clobbers in inline assembly
   on S390.  */
/* #undef HAVE_S390_VX_GCC_SUPPORT */

/* Define if assembler supports arch13 instructions on S390.  */
/* #undef HAVE_S390_ARCH13_ASM_SUPPORT */

/* Define if the compiler\'s exception support is based on libunwind.  */
/* #undef HAVE_CC_WITH_LIBUNWIND */

/* Define if the accesses to static and hidden variables in a shared object
   need dynamic relocations.  */
/* #undef HIDDEN_VAR_NEEDS_DYNAMIC_RELOC */

/* Define this to disable the 'hidden_proto' et al macros in
   include/libc-symbols.h that avoid PLT slots in PIE.  */
/* #undef NO_HIDDEN_EXTERN_FUNC_IN_PIE */

/* Define this to disable the 'hidden_proto' et al macros in
   include/libc-symbols.h that avoid PLT slots in the shared objects.  */
/* #undef NO_HIDDEN */

/* Define this to disable in rtld the 'hidden_proto' et al macros in
   include/libc-symbols.h that avoid PLT slots in the shared objects.  */
/* #undef NO_RTLD_HIDDEN */

/* Define this to disable lazy relocations in DSOs.  */
/* #undef BIND_NOW */

/* AArch64 big endian ABI */
/* #undef HAVE_AARCH64_BE */

/* AArch64 BTI support enabled.  */
#define HAVE_AARCH64_BTI 0

/* AArch64 PAC-RET code generation is enabled.  */
#define HAVE_AARCH64_PAC_RET 0

/* Assembler support ARMv8.2-A SVE.
   This macro becomes obsolete when glibc increased the minimum
   required version of GNU 'binutils' to 2.28 or later. */
#define HAVE_AARCH64_SVE_ASM 0

/* ARC big endian ABI */
/* #undef HAVE_ARC_BE */

/* C-SKY ABI version.  */
/* #undef CSKYABI */

/* C-SKY floating-point instructions.  */
/* #undef CSKY_HARD_FLOAT */

/* C-SKY floating-point ABI.  */
/* #undef CSKY_HARD_FLOAT_ABI */

/* RISC-V integer ABI for ld.so.  */
/* #undef RISCV_ABI_XLEN */

/* RISC-V floating-point ABI for ld.so.  */
/* #undef RISCV_ABI_FLEN */

/* LOONGARCH integer ABI for ld.so.  */
/* #undef LOONGARCH_ABI_GRLEN */

/* LOONGARCH floating-point ABI for ld.so.  */
/* #undef LOONGARCH_ABI_FRLEN */

/* Assembler support LoongArch LASX/LSX vector instructions.
   This macro becomes obsolete when glibc increased the minimum
   required version of GNU 'binutils' to 2.41 or later. */
#define HAVE_LOONGARCH_VEC_ASM 0

/* Linux specific: minimum supported kernel version.  */
#define __LINUX_KERNEL_VERSION (3 * 65536 + 2 * 256 + 0)

/* Linux specific: __LINUX_KERNEL_VERSION as a string.  */
#define __LINUX_KERNEL_VERSION_STR "3.2.0"

/* Override abi-tags ABI version if necessary.  */
#define __ABI_TAG_VERSION 3,2,0

/* Mach specific: define if the `host_page_size' RPC is available.  */
/* #undef HAVE_HOST_PAGE_SIZE */

/* Mach/i386 specific: define if the `i386_io_perm_*' RPCs are available.  */
/* #undef HAVE_I386_IO_PERM_MODIFY */

/* Mach/i386 specific: define if the `i386_set_gdt' RPC is available.  */
/* #undef HAVE_I386_SET_GDT */

/* Define if inlined system calls are available.  */
#define HAVE_INLINED_SYSCALLS 1

/* Define if memory tagging support should be enabled.  */
/* #undef USE_MTAG */

/* Package description.  */
#define PKGVERSION "(GNU libc) "

/* Bug reporting address.  */
#define REPORT_BUGS_TO "<https://www.gnu.org/software/libc/bugs.html>"

/* Define if multi-arch DSOs should be generated.  */
#define USE_MULTIARCH 1

/* Define if Systemtap <sys/sdt.h> probes should be defined.  */
/* #undef USE_STAP_PROBE */

/* Define if library functions should try to contact the nscd daemon.  */
#define USE_NSCD 1

/* Define if the dynamic linker should consult an ld.so.cache file.  */
#define USE_LDCONFIG 1

/* Define to 1 if STT_GNU_IFUNC support actually works.  */
#define HAVE_IFUNC 1

/* Define if gcc supports attribute ifunc.  */
#define HAVE_GCC_IFUNC 1

/* Define if CC supports attribute retain.  */
/* #undef HAVE_GNU_RETAIN */

/* Define to 1 if the assembler needs intermediate aliases to define
   multiple symbol versions for one symbol.  */
#define SYMVER_NEEDS_ALIAS 1

/* Define to 1 if libpthread actually resides in libc.  */
#define PTHREAD_IN_LIBC 1

/* An integer used to scale the timeout of test programs.  */
#define TIMEOUTFACTOR 1

/*
 */

#ifndef	_LIBC

/* These symbols might be defined by some sysdeps configures.
   They are used only in miscellaneous generator programs, not
   in compiling libc itself.   */

/* sysdeps/generic/configure.ac */
/* #undef HAVE_PSIGNAL */

/* sysdeps/unix/configure.ac */
/* #undef HAVE_STRERROR */

/* sysdeps/unix/common/configure.ac */
/* #undef HAVE_SYS_SIGLIST */
/* #undef HAVE__SYS_SIGLIST */
/* #undef HAVE__CTYPE_ */
/* #undef HAVE___CTYPE_ */
/* #undef HAVE___CTYPE */
/* #undef HAVE__CTYPE__ */
/* #undef HAVE__CTYPE */
/* #undef HAVE__LOCP */

#endif

/*
 */

#ifdef	_LIBC

/* The zic and zdump programs need these definitions.  */

#define	HAVE_STRERROR	1

/* The locale code needs these definitions.  */

#define HAVE_REGEX 1

/* The ARM hard-float ABI is being used.  */
/* #undef HAVE_ARM_PCS_VFP */

/* The ARM movw/movt instructions using PC-relative relocs work right.  */
#define ARM_PCREL_MOVW_OK 0

/* The pt_chown binary is being built and used by grantpt.  */
#define HAVE_PT_CHOWN 0

/* Define if the compiler supports __builtin_trap without
   any external dependencies such as making a function call.  */
#define HAVE_BUILTIN_TRAP 1

/* ports/sysdeps/mips/configure.in  */
/* Define if using the IEEE 754-2008 NaN encoding on the MIPS target.  */
/* #undef HAVE_MIPS_NAN2008 */

/* The PowerPC64 ELFv2 ABI is being used.  */
/* #undef HAVE_ELFV2_ABI */

/* PowerPC32 uses fcfid for integer to floating point conversions.  */
#define HAVE_PPC_FCFID 0

/* PowerPC32 uses fctidz for floating point to long long conversions.  */
#define HAVE_PPC_FCTIDZ 0

/* Define if PIE is unsupported.  */
/* #undef PIE_UNSUPPORTED */

/* Define if static PIE is supported.  */
#define SUPPORT_STATIC_PIE 1

/* Define if static PIE is enabled.  */
#define ENABLE_STATIC_PIE 1

/* The default value of x86 CET control.  */
#define DEFAULT_DL_X86_CET_CONTROL cet_elf_property

/* Define if x86 ISA level should be included in shared libraries.  */
#define INCLUDE_X86_ISA_LEVEL 1

/* Define if -msahf is enabled by default on x86.  */
/* #undef HAVE_X86_LAHF_SAHF */

/* Define if -mmovbe is enabled by default on x86.  */
/* #undef HAVE_X86_MOVBE */

#endif
