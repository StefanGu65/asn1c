#ifndef	_ASN1_COMPILER_INTERNAL_H_
#define	_ASN1_COMPILER_INTERNAL_H_

#ifdef	HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>		/* for fstat(2) */
#include <unistd.h>		/* for unlink(2) */
#include <fcntl.h>		/* for open(2) */
#include <glob.h>		/* for glob(3) */
#include <string.h>
#include <ctype.h>		/* for isalnum(3) */
#include <stdarg.h>
#include <errno.h>
#include <assert.h>

#include "asn1compiler.h"

typedef struct arg_s {

	enum asn1c_flags flags;

	void (*logger_cb)(int _severity, const char *fmt, ...);

	int (*default_cb)(struct arg_s *);

	struct compiler_streams *target;

	asn1p_t		*asn;
	asn1p_module_t	*mod;
	asn1p_expr_t	*expr;

	int indent_level;
	int indented;
	int embed;
} arg_t;

#include "asn1c_lang.h"		/* Target language initialization */
#include "asn1c_misc.h"		/* Miscellaneous functions */
#include "asn1c_out.h"		/* Handle output during compilation */
#include "asn1c_save.h"		/* Save compiled output */

/*
 * Logging.
 */
#define	LOG(ll, fmt, args...)	do {			\
		arg->logger_cb(ll, fmt, ##args);	\
	} while(0)
#define	DEBUG(fmt, args...)	do {		\
		if(arg->flags & A1C_DEBUG)	\
			LOG(-1, fmt, ##args);	\
	} while(0)
#define	WARNING(fmt, args...)	LOG(0, fmt, ##args);
#define	FATAL(fmt, args...)	LOG(1, fmt, ##args);

#endif	/* _ASN1_COMPILER_INTERNAL_H_ */
