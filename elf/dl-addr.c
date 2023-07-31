/* Locate the shared object symbol nearest a given address.
   Copyright (C) 1996-2023 Free Software Foundation, Inc.
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

#include <dlfcn.h>
#include <stddef.h>
/* #include <ldsodefs.h> */
#include "../include/ldsodefs.h"

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>


typedef struct
{
  const char *dli_fname;	/* File name of defining object.  */
  void *dli_fbase;		/* Load address of that object.  */
  const char *dli_sname;	/* Name of nearest symbol.  */
  void *dli_saddr;		/* Exact value of nearest symbol.  */
} Dl_info;

static inline void
__attribute ((always_inline))
determine_info (const ElfW(Addr) addr, struct link_map *match, Dl_info *info,
		struct link_map **mapp, const ElfW(Sym) **symbolp)
{
  /* Now we know what object the address lies in.  */
  info->dli_fname = match->l_name;
  info->dli_fbase = (void *) match->l_map_start;

  /* If this is the main program the information is incomplete.  */
  if (__builtin_expect (match->l_name[0], 'a') == '\0'
      && match->l_type == lt_executable)
    info->dli_fname = _dl_argv[0];

  const ElfW(Sym) *symtab
    = (const ElfW(Sym) *) D_PTR (match, l_info[DT_SYMTAB]);
  const char *strtab = (const char *) D_PTR (match, l_info[DT_STRTAB]);

  ElfW(Word) strtabsize = match->l_info[DT_STRSZ]->d_un.d_val;

  const ElfW(Sym) *matchsym = NULL;
  if (match->l_info[ELF_MACHINE_GNU_HASH_ADDRIDX] != NULL)
    {
      /* We look at all symbol table entries referenced by the hash
	 table.  */
      for (Elf_Symndx bucket = 0; bucket < match->l_nbuckets; ++bucket)
	{
	  Elf32_Word symndx = match->l_gnu_buckets[bucket];
	  if (symndx != 0)
	    {
	      const Elf32_Word *hasharr = &match->l_gnu_chain_zero[symndx];

	      do
		{
		  /* The hash table never references local symbols so
		     we can omit that test here.  */
		  symndx = ELF_MACHINE_HASH_SYMIDX (match, hasharr);
		  if ((symtab[symndx].st_shndx != SHN_UNDEF
		       || symtab[symndx].st_value != 0)
		      && symtab[symndx].st_shndx != SHN_ABS
		      && ELFW(ST_TYPE) (symtab[symndx].st_info) != STT_TLS
		      && DL_ADDR_SYM_MATCH (match, &symtab[symndx],
					    matchsym, addr)
		      && symtab[symndx].st_name < strtabsize)
		    matchsym = (ElfW(Sym) *) &symtab[symndx];
		}
	      while ((*hasharr++ & 1u) == 0);
	    }
	}
    }
  else if (match->l_info[DT_HASH] != NULL)
    {
      const ElfW (Sym) *symtabend
	  = (symtab + ((Elf_Symndx *) D_PTR (match, l_info[DT_HASH]))[1]);

      for (; (void *) symtab < (void *) symtabend; ++symtab)
	if ((ELFW(ST_BIND) (symtab->st_info) == STB_GLOBAL
	     || ELFW(ST_BIND) (symtab->st_info) == STB_WEAK)
	    && __glibc_likely (!dl_symbol_visibility_binds_local_p (symtab))
	    && ELFW(ST_TYPE) (symtab->st_info) != STT_TLS
	    && (symtab->st_shndx != SHN_UNDEF
		|| symtab->st_value != 0)
	    && symtab->st_shndx != SHN_ABS
	    && DL_ADDR_SYM_MATCH (match, symtab, matchsym, addr)
	    && symtab->st_name < strtabsize)
	  matchsym = (ElfW(Sym) *) symtab;
    }
  /* In the absence of a hash table, treat the object as if it has no symbol.
   */


  // search the symtab
  if (matchsym == NULL)
  {
      // 
      int size = 0, fd = -1;
      ElfW(Ehdr) *elf = (ElfW(Ehdr) *) MAP_FAILED;
      void *shoff = NULL;


      /* If this is the main program the information is incomplete.  */
      if (__builtin_expect (match->l_name[0], 'a') == '\0'
          && match->l_type == lt_executable)
      {
          fd = open(info->dli_fname, O_RDONLY);
      }
      else
      {
          fd = open(match->l_name, O_RDONLY);
      }

      if (fd < 0)
      {
          /* printf("failed to open %s\n", match->l_name); */
          perror("Error:");
      }

      size = lseek(fd, 0, SEEK_END); // 将文件偏移设置到文件尾，并返回偏移（即文件大小）的字节数

      /*     printf("lseek() failed for %s\n", match->l_name); // 只有失败时，才会返回-1 */
      assert(size > 0);

      elf = (ElfW(Ehdr) *) mmap(0, size, PROT_READ, MAP_SHARED, fd, 0); // 将整个elf文件都读取到elf中，Elf_Ehdr 是 ELF 文件头结构体，用于描述 ELF 文件的基本信息
      close(fd);
      fd = -1;

      /*     printf("mmap() failed for %s\n", match->l_name); */
      assert(elf != MAP_FAILED);

      shoff = ((void *) elf) + elf->e_shoff; //e_shoff字段表示节区表（Section Header Table）在elf文件中的偏移量。节区表并不是在elf文件的开头，Elf_Ehdr在elf文件的开头，节区表在之后，节区表存放着每个section的名称、类型、大小、偏移量和属性等
      ElfW(Shdr) *shstrtab = (ElfW(Shdr) *)(shoff + elf->e_shstrndx * elf->e_shentsize); // e_shstrndx字段表示节区名称字符串表（Section Name String Table）在节区表中的索引，e_shentsize表示节区表的一个条目的大小。Elf_Shdr即为节区表的一个条目，存储一个section的描述信息，该行代码获取字符串表section在节区表中对应的条目
      char * shstr = malloc(shstrtab->sh_size); // 字符串表的大小
      memcpy(shstr, ((void *) elf) + shstrtab->sh_offset, shstrtab->sh_size); // Elf_Shdr->sh_offset表示某section在文件中的偏移量，shstr存放字符串表
      
      ElfW(Sym) *real_symtab = NULL;
      char *real_strtab = NULL;
      int symtab_num = 0, real_strtabsize = 0;
      for (int k = 0; k < elf->e_shnum/* 节区表的条目数目 */; k++, shoff += elf->e_shentsize)
      {
          ElfW(Shdr) *sh = (ElfW(Shdr) *) shoff;
          switch (sh->sh_type)
          {
              case SHT_SYMTAB:
                  /* printf("%s: duplicate SYMTAB sections\n", match->l_name); */
                  assert(real_symtab == NULL);
                  real_symtab = malloc(sh->sh_size);

                  /* printf("%s:no memory for .symtab\n", match->l_name); */
                  assert(real_symtab != NULL);
                  memcpy(real_symtab, ((void *) elf) + sh->sh_offset, sh->sh_size);
                  symtab_num = sh->sh_size / sizeof(ElfW(Sym));
                  break;

              case SHT_STRTAB:
                  if (strcmp(shstr + sh->sh_name, ".strtab") == 0)
                  {
                      /* printf("%s: duplicate STRTAB sections\n", match->l_name); */
                      assert(real_strtab == NULL);
                      real_strtab = malloc(sh->sh_size);
                      real_strtabsize = sh->sh_size;

                      /* printf("%s:no memory for .strtab\n", match->l_name); */
                      assert(real_strtab != NULL);
                      memcpy(real_strtab, ((void *) elf) + sh->sh_offset, sh->sh_size);
                  }
                  break;
              /* case SHT_PROGBITS: */
              /*     if (real_symtab == NULL || real_strtab == NULL) */
              /*     { */
              /*         break; */
              /*     } */
          }

      }

      for (int k = 0; k < symtab_num; k++, real_symtab++)
      {
          if (ELFW(ST_TYPE) (real_symtab->st_info) != STT_TLS
              && (real_symtab->st_shndx != SHN_UNDEF
              || real_symtab->st_value != 0)
              && real_symtab->st_shndx != SHN_ABS
              && DL_ADDR_SYM_MATCH (match, real_symtab, matchsym, addr)
              && real_symtab->st_name < real_strtabsize)
          matchsym = (ElfW(Sym) *) real_symtab;
      }

      munmap(elf, size);
      elf = 0;
      /* printf("symtab sections not found in %s\n", match->l_name); */
      assert(real_symtab && real_strtab);
      strtab = real_strtab;
  }

  if (mapp)
    *mapp = match;
  if (symbolp)
    *symbolp = matchsym;

  if (matchsym)
    {
      /* We found a symbol close by.  Fill in its name and exact
	 address.  */
      lookup_t matchl = LOOKUP_VALUE (match);

      info->dli_sname = strtab + matchsym->st_name;
      info->dli_saddr = DL_SYMBOL_ADDRESS (matchl, matchsym);
    }
  else
    {
      /* No symbol matches.  We return only the containing object.  */
      info->dli_sname = NULL;
      info->dli_saddr = NULL;
    }
}


int
_dl_addr (const void *address, Dl_info *info,
	  struct link_map **mapp, const ElfW(Sym) **symbolp)
{
  const ElfW(Addr) addr = DL_LOOKUP_ADDRESS (address);
  int result = 0;

  /* Protect against concurrent loads and unloads.  */
  __rtld_lock_lock_recursive (GL(dl_load_lock));

  struct link_map *l = _dl_find_dso_for_object (addr);

  if (l)
    {
      determine_info (addr, l, info, mapp, symbolp);
      result = 1;
    }

  __rtld_lock_unlock_recursive (GL(dl_load_lock));

  return result;
}
