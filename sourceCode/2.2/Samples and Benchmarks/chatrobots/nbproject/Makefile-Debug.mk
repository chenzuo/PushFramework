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
	${OBJECTDIR}/src/INIReader.o \
	${OBJECTDIR}/src/ChatRobots.o \
	${OBJECTDIR}/src/stdafx.o \
	${OBJECTDIR}/src/ini.o \
	${OBJECTDIR}/src/Bot.o


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
LDLIBSOPTIONS=-L../output ../output/libchatapi.so ../output/libtcpsocket.so ../output/libpushframework.so ../output/libxmlprotocol.so ../output/libchatprotocol.so

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../output/chatrobots

../output/chatrobots: ../output/libchatapi.so

../output/chatrobots: ../output/libtcpsocket.so

../output/chatrobots: ../output/libpushframework.so

../output/chatrobots: ../output/libxmlprotocol.so

../output/chatrobots: ../output/libchatprotocol.so

../output/chatrobots: ${OBJECTFILES}
	${MKDIR} -p ../output
	${LINK.cc} -o ../output/chatrobots ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/INIReader.o: src/INIReader.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../chatapi/src -I../tcpsocket/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/INIReader.o src/INIReader.cpp

${OBJECTDIR}/src/ChatRobots.o: src/ChatRobots.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../chatapi/src -I../tcpsocket/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ChatRobots.o src/ChatRobots.cpp

${OBJECTDIR}/src/stdafx.o: src/stdafx.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../chatapi/src -I../tcpsocket/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/stdafx.o src/stdafx.cpp

${OBJECTDIR}/src/ini.o: src/ini.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../chatapi/src -I../tcpsocket/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ini.o src/ini.cpp

${OBJECTDIR}/src/Bot.o: src/Bot.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../chatapi/src -I../tcpsocket/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Bot.o src/Bot.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../output/chatrobots

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
