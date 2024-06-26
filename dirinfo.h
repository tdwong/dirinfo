//
// dirinfo.h
//
// Module Name:
//   FDS Deliver Daemon
//
// Description:
//
// Copyright (c) 2002 by PowerTV, Inc.  All Rights Reserved.
//
// Revision History:
//   T. David Wong		07-03-2002    Original Author
//   T. David Wong		03-30-2012    Compiled on Mac OS/X
//

#ifndef	_DIRINFO_H_
#define	_DIRINFO_H_

#ifdef	__cplusplus
extern "C" {
#endif

// #include "fds_pp_defs.h"
// #include "fds_common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>       /* file statistics. */
#include <errno.h>
#include <stdarg.h>         /* for va_args, va_list */
#ifdef	_MSC_VER
#include <winsock.h>
#include <io.h>                /* for _close */
#include <direct.h>            /* for _mkdir */
#include "MSConfig.h"
#else
	// 2012-03-30
#define	BOOL	boolean
#undef	TRUE
#define	TRUE	1
#define	FALSE	(!TRUE)
#endif


/* public data structures
 */
typedef int (*FILEPROC)(const char *filename, const char *fullpath, struct stat *statp, void *opaquep);
typedef int (*OutputFunc)(const int level, const char *format, ...);
// typedef void (*VOIDPROC)(int);
// typedef int  (*FINTPROC)(FILE *, void *);
// typedef int  (*Mon_OutputFunc)(const ui8 * str, ...);

/*
 * dirinfo
 * */
typedef struct dirInfo {
        int  num_of_directories;
        int  num_of_files;
        int  num_of_others;
} dirInfo_t;
typedef struct matchCriteria {
		int      type;		/* NO predefined constants for this field */
		union {				/* comparison parameters */
			char    *str;
			time_t  time;
			void    *ptr;
		} cparam;
		/* information to be carried along to every entry */
		FILEPROC	proc;		// callback for every directory entries
		FILEPROC	postFunc;	// callback after all directory entries were visited
		OutputFunc	printf;		// output function (e.g. printf)
		void		*iblock;	// embedded other information
} matchCriteria_t;


/* public functions
 */
	///TODO: maxLevel > 1 implies recursive == 1
extern int dirinfo_Find(const char *dirname, dirInfo_t *dip, matchCriteria_t *mcbuf, int recursive, int maxLevel, int curLevel);
extern void dirinfo_Report(dirInfo_t *dip, char *name);
extern int IsValidPath(const char *path);
extern int IsDirectory(const char *path);
extern int IsFile(const char *path);
extern int condense_path(char *rootdir);

#ifdef	__cplusplus
}
#endif

#endif	/* _DIRINFO_H_ */

