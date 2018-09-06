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
	${OBJECTDIR}/src/LeaveRoomRequestService.o \
	${OBJECTDIR}/src/RoomChatRequestService.o \
	${OBJECTDIR}/src/LogoutRequestService.o \
	${OBJECTDIR}/src/DirectChatRequestService.o \
	${OBJECTDIR}/src/ChatServer.o \
	${OBJECTDIR}/src/ChatParticipant.o \
	${OBJECTDIR}/src/JoinRoomRequestService.o \
	${OBJECTDIR}/src/stdafx.o \
	${OBJECTDIR}/src/ini.o \
	${OBJECTDIR}/src/ChatParticipantFactory.o


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
LDLIBSOPTIONS=-Wl,-rpath ../pushframework/../output -L../pushframework/../output -lpushframework -Wl,-rpath ../xmlprotocol/../output -L../xmlprotocol/../output -lxmlprotocol -Wl,-rpath ../chatprotocol/../output -L../chatprotocol/../output -lchatprotocol

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../output/chatserver

../output/chatserver: ../pushframework/../output/libpushframework.so

../output/chatserver: ../xmlprotocol/../output/libxmlprotocol.so

../output/chatserver: ../chatprotocol/../output/libchatprotocol.so

../output/chatserver: ${OBJECTFILES}
	${MKDIR} -p ../output
	${LINK.cc} -o ../output/chatserver ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/INIReader.o: src/INIReader.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../pushframework/include -I../chatprotocol/src -I../xmlprotocol/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/INIReader.o src/INIReader.cpp

${OBJECTDIR}/src/LeaveRoomRequestService.o: src/LeaveRoomRequestService.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../pushframework/include -I../chatprotocol/src -I../xmlprotocol/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/LeaveRoomRequestService.o src/LeaveRoomRequestService.cpp

${OBJECTDIR}/src/RoomChatRequestService.o: src/RoomChatRequestService.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../pushframework/include -I../chatprotocol/src -I../xmlprotocol/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/RoomChatRequestService.o src/RoomChatRequestService.cpp

${OBJECTDIR}/src/LogoutRequestService.o: src/LogoutRequestService.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../pushframework/include -I../chatprotocol/src -I../xmlprotocol/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/LogoutRequestService.o src/LogoutRequestService.cpp

${OBJECTDIR}/src/DirectChatRequestService.o: src/DirectChatRequestService.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../pushframework/include -I../chatprotocol/src -I../xmlprotocol/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/DirectChatRequestService.o src/DirectChatRequestService.cpp

${OBJECTDIR}/src/ChatServer.o: src/ChatServer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../pushframework/include -I../chatprotocol/src -I../xmlprotocol/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ChatServer.o src/ChatServer.cpp

${OBJECTDIR}/src/ChatParticipant.o: src/ChatParticipant.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../pushframework/include -I../chatprotocol/src -I../xmlprotocol/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ChatParticipant.o src/ChatParticipant.cpp

${OBJECTDIR}/src/JoinRoomRequestService.o: src/JoinRoomRequestService.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../pushframework/include -I../chatprotocol/src -I../xmlprotocol/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/JoinRoomRequestService.o src/JoinRoomRequestService.cpp

${OBJECTDIR}/src/stdafx.o: src/stdafx.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../pushframework/include -I../chatprotocol/src -I../xmlprotocol/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/stdafx.o src/stdafx.cpp

${OBJECTDIR}/src/ini.o: src/ini.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../pushframework/include -I../chatprotocol/src -I../xmlprotocol/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ini.o src/ini.cpp

${OBJECTDIR}/src/ChatParticipantFactory.o: src/ChatParticipantFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../pushframework/include -I../chatprotocol/src -I../xmlprotocol/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ChatParticipantFactory.o src/ChatParticipantFactory.cpp

# Subprojects
.build-subprojects:
	cd ../pushframework && ${MAKE}  -f Makefile CONF=Debug
	cd ../xmlprotocol && ${MAKE}  -f Makefile CONF=Debug
	cd ../chatprotocol && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../output/chatserver

# Subprojects
.clean-subprojects:
	cd ../pushframework && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../xmlprotocol && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../chatprotocol && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
