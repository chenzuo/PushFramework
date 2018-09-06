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
	${OBJECTDIR}/src/XMLProtocol.o \
	${OBJECTDIR}/src/OutgoingXMLPacket.o \
	${OBJECTDIR}/src/XMLRequest.o \
	${OBJECTDIR}/src/IncomingXMLPacket.o \
	${OBJECTDIR}/src/XMLResponse.o \
	${OBJECTDIR}/src/XMLProtocolImpl.o \
	${OBJECTDIR}/src/xmlParser.o \
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
LDLIBSOPTIONS=-Wl,-rpath ../pushframework/../output -L../pushframework/../output -lpushframework

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../output/libxmlprotocol.so

../output/libxmlprotocol.so: ../pushframework/../output/libpushframework.so

../output/libxmlprotocol.so: ${OBJECTFILES}
	${MKDIR} -p ../output
	${LINK.cc} -shared -o ../output/libxmlprotocol.so -fPIC ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/XMLProtocol.o: src/XMLProtocol.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../pushframework/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/XMLProtocol.o src/XMLProtocol.cpp

${OBJECTDIR}/src/OutgoingXMLPacket.o: src/OutgoingXMLPacket.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../pushframework/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/OutgoingXMLPacket.o src/OutgoingXMLPacket.cpp

${OBJECTDIR}/src/XMLRequest.o: src/XMLRequest.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../pushframework/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/XMLRequest.o src/XMLRequest.cpp

${OBJECTDIR}/src/IncomingXMLPacket.o: src/IncomingXMLPacket.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../pushframework/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/IncomingXMLPacket.o src/IncomingXMLPacket.cpp

${OBJECTDIR}/src/XMLResponse.o: src/XMLResponse.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../pushframework/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/XMLResponse.o src/XMLResponse.cpp

${OBJECTDIR}/src/XMLProtocolImpl.o: src/XMLProtocolImpl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../pushframework/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/XMLProtocolImpl.o src/XMLProtocolImpl.cpp

${OBJECTDIR}/src/xmlParser.o: src/xmlParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../pushframework/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/xmlParser.o src/xmlParser.cpp

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
	${RM} ../output/libxmlprotocol.so

# Subprojects
.clean-subprojects:
	cd ../pushframework && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
