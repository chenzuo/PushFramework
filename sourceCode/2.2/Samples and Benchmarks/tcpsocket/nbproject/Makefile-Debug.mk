#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/TCPSocketImpl_Linux.o \
	${OBJECTDIR}/src/linuxcs.o \
	${OBJECTDIR}/src/TCPSocket.o \
	${OBJECTDIR}/src/ResponseHandler.o \
	${OBJECTDIR}/src/stdafx.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L../output -Wl,-rpath ../pushframework/../output -L../pushframework/../output -lpushframework

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../output/libtcpsocket.so

../output/libtcpsocket.so: ../pushframework/../output/libpushframework.so

../output/libtcpsocket.so: ${OBJECTFILES}
	${MKDIR} -p ../output
	${LINK.cc} -shared -o ../output/libtcpsocket.so -fPIC ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/TCPSocketImpl_Linux.o: src/TCPSocketImpl_Linux.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../pushframework/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TCPSocketImpl_Linux.o src/TCPSocketImpl_Linux.cpp

${OBJECTDIR}/src/linuxcs.o: src/linuxcs.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../pushframework/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/linuxcs.o src/linuxcs.cpp

${OBJECTDIR}/src/TCPSocket.o: src/TCPSocket.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../pushframework/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TCPSocket.o src/TCPSocket.cpp

${OBJECTDIR}/src/ResponseHandler.o: src/ResponseHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../pushframework/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ResponseHandler.o src/ResponseHandler.cpp

${OBJECTDIR}/src/stdafx.o: src/stdafx.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../pushframework/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/stdafx.o src/stdafx.cpp

# Subprojects
.build-subprojects:
	cd ../pushframework && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../output/libtcpsocket.so

# Subprojects
.clean-subprojects:
	cd ../pushframework && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
