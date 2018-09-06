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
	${OBJECTDIR}/src/ChatClientProtocol.o \
	${OBJECTDIR}/src/ChatServerProtocol.o \
	${OBJECTDIR}/src/DirectChatRequest.o \
	${OBJECTDIR}/src/RoomsResponse.o \
	${OBJECTDIR}/src/LeaveRoomRequest.o \
	${OBJECTDIR}/src/JoinRoomRequest.o \
	${OBJECTDIR}/src/ParticipantOutResponse.o \
	${OBJECTDIR}/src/ParticipantInResponse.o \
	${OBJECTDIR}/src/RoomChatRequest.o \
	${OBJECTDIR}/src/LoginResponse.o \
	${OBJECTDIR}/src/DirectChatResponse.o \
	${OBJECTDIR}/src/LoginPuzzleResponse.o \
	${OBJECTDIR}/src/RoomChatResponse.o \
	${OBJECTDIR}/src/stdafx.o \
	${OBJECTDIR}/src/LoginRequest.o \
	${OBJECTDIR}/src/LogoutRequest.o \
	${OBJECTDIR}/src/JoinRoomResponse.o


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
LDLIBSOPTIONS=-Wl,-rpath ../pushframework/../output -L../pushframework/../output -lpushframework -Wl,-rpath ../xmlprotocol/../output -L../xmlprotocol/../output -lxmlprotocol

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../output/libchatprotocol.so

../output/libchatprotocol.so: ../pushframework/../output/libpushframework.so

../output/libchatprotocol.so: ../xmlprotocol/../output/libxmlprotocol.so

../output/libchatprotocol.so: ${OBJECTFILES}
	${MKDIR} -p ../output
	${LINK.cc} -shared -o ../output/libchatprotocol.so -fPIC ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/ChatClientProtocol.o: src/ChatClientProtocol.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../pushframework/include -I../xmlprotocol/src -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ChatClientProtocol.o src/ChatClientProtocol.cpp

${OBJECTDIR}/src/ChatServerProtocol.o: src/ChatServerProtocol.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../pushframework/include -I../xmlprotocol/src -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ChatServerProtocol.o src/ChatServerProtocol.cpp

${OBJECTDIR}/src/DirectChatRequest.o: src/DirectChatRequest.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../pushframework/include -I../xmlprotocol/src -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/DirectChatRequest.o src/DirectChatRequest.cpp

${OBJECTDIR}/src/RoomsResponse.o: src/RoomsResponse.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../pushframework/include -I../xmlprotocol/src -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/RoomsResponse.o src/RoomsResponse.cpp

${OBJECTDIR}/src/LeaveRoomRequest.o: src/LeaveRoomRequest.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../pushframework/include -I../xmlprotocol/src -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/LeaveRoomRequest.o src/LeaveRoomRequest.cpp

${OBJECTDIR}/src/JoinRoomRequest.o: src/JoinRoomRequest.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../pushframework/include -I../xmlprotocol/src -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/JoinRoomRequest.o src/JoinRoomRequest.cpp

${OBJECTDIR}/src/ParticipantOutResponse.o: src/ParticipantOutResponse.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../pushframework/include -I../xmlprotocol/src -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ParticipantOutResponse.o src/ParticipantOutResponse.cpp

${OBJECTDIR}/src/ParticipantInResponse.o: src/ParticipantInResponse.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../pushframework/include -I../xmlprotocol/src -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ParticipantInResponse.o src/ParticipantInResponse.cpp

${OBJECTDIR}/src/RoomChatRequest.o: src/RoomChatRequest.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../pushframework/include -I../xmlprotocol/src -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/RoomChatRequest.o src/RoomChatRequest.cpp

${OBJECTDIR}/src/LoginResponse.o: src/LoginResponse.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../pushframework/include -I../xmlprotocol/src -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/LoginResponse.o src/LoginResponse.cpp

${OBJECTDIR}/src/DirectChatResponse.o: src/DirectChatResponse.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../pushframework/include -I../xmlprotocol/src -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/DirectChatResponse.o src/DirectChatResponse.cpp

${OBJECTDIR}/src/LoginPuzzleResponse.o: src/LoginPuzzleResponse.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../pushframework/include -I../xmlprotocol/src -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/LoginPuzzleResponse.o src/LoginPuzzleResponse.cpp

${OBJECTDIR}/src/RoomChatResponse.o: src/RoomChatResponse.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../pushframework/include -I../xmlprotocol/src -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/RoomChatResponse.o src/RoomChatResponse.cpp

${OBJECTDIR}/src/stdafx.o: src/stdafx.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../pushframework/include -I../xmlprotocol/src -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/stdafx.o src/stdafx.cpp

${OBJECTDIR}/src/LoginRequest.o: src/LoginRequest.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../pushframework/include -I../xmlprotocol/src -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/LoginRequest.o src/LoginRequest.cpp

${OBJECTDIR}/src/LogoutRequest.o: src/LogoutRequest.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../pushframework/include -I../xmlprotocol/src -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/LogoutRequest.o src/LogoutRequest.cpp

${OBJECTDIR}/src/JoinRoomResponse.o: src/JoinRoomResponse.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../pushframework/include -I../xmlprotocol/src -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/JoinRoomResponse.o src/JoinRoomResponse.cpp

# Subprojects
.build-subprojects:
	cd ../pushframework && ${MAKE}  -f Makefile CONF=Debug
	cd ../xmlprotocol && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../output/libchatprotocol.so

# Subprojects
.clean-subprojects:
	cd ../pushframework && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../xmlprotocol && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
