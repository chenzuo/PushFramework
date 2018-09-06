##----------------------------------------------------------------------------
# Created with genmake.pl v1.1 on Wed Feb 25 23:06:11 2009
# genmake.pl home: http://muquit.com/muquit/software/
# Copryright: GNU GPL (http://www.gnu.org/copyleft/gpl.html)
##----------------------------------------------------------------------------
rm=/bin/rm -f
CC= g++
DEFS=  
PROGNAME= sockport
INCLUDES=  -I. \
           -I/usr/include
LIBS=


DEFINES= $(INCLUDES) $(DEFS) -DSYS_UNIX=1 -DBSD_SOCKET=1
CFLAGS= -g $(DEFINES)

SRCS = sockport.cpp SocketHandle.cpp

OBJS = sockport.o SocketHandle.o

.cpp.o:
	$(rm) $@
	$(CC) $(CFLAGS) -c $*.cpp

all: $(PROGNAME)

$(PROGNAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $(PROGNAME) $(OBJS) $(LIBS)
#       you may need to add (-pthread) to build

clean:
	$(rm) $(OBJS) $(PROGNAME) core *~
