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
	${OBJECTDIR}/src/ChatAPI.o \
	${OBJECTDIR}/src/ResponseHandlers.o \
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
LDLIBSOPTIONS=-L../output ../output/libpushframework.so ../output/libtcpsocket.so ../output/libxmlprotocol.so ../output/libchatprotocol.so

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../output/libchatapi.so

../output/libchatapi.so: ../output/libpushframework.so

../output/libchatapi.so: ../output/libtcpsocket.so

../output/libchatapi.so: ../output/libxmlprotocol.so

../output/libchatapi.so: ../output/libchatprotocol.so

../output/libchatapi.so: ${OBJECTFILES}
	${MKDIR} -p ../output
	${LINK.cc} -shared -o ../output/libchatapi.so -fPIC ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/ChatAPI.o: src/ChatAPI.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../pushframework/include -I../tcpsocket/src -I../xmlprotocol/src -I../chatprotocol/src -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ChatAPI.o src/ChatAPI.cpp

${OBJECTDIR}/src/ResponseHandlers.o: src/ResponseHandlers.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../pushframework/include -I../tcpsocket/src -I../xmlprotocol/src -I../chatprotocol/src -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ResponseHandlers.o src/ResponseHandlers.cpp

${OBJECTDIR}/src/stdafx.o: src/stdafx.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../pushframework/include -I../tcpsocket/src -I../xmlprotocol/src -I../chatprotocol/src -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/stdafx.o src/stdafx.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../output/libchatapi.so

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
