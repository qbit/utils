PREFIX ?=	/usr/local
MANDIR ?=	${PREFIX}/man/man
BINDIR ?=	${PREFIX}/bin

PROG=	ac
SRCS=	ac.c

CFLAGS+=	-Wall
CFLAGS+=	-Wstrict-prototypes -Wmissing-prototypes
CFLAGS+=	-Wmissing-declarations
CFLAGS+=	-Wshadow -Wpointer-arith
CFLAGS+=	-Wsign-compare -Wcast-qual

.include <bsd.prog.mk>
