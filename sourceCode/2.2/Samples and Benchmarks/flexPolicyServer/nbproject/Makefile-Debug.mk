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
CND_DLIB_EXT=so
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
	${OBJECTDIR}/src/LicenseProtocol.o \
	${OBJECTDIR}/src/PolicyRequest.o \
	${OBJECTDIR}/src/PolicyResponse.o \
	${OBJECTDIR}/src/FlexLicenseServer.o \
	${OBJECTDIR}/src/ini.o \
	${OBJECTDIR}/src/stdafx.o \
	${OBJECTDIR}/src/FlexClientFactory.o


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
LDLIBSOPTIONS=-Wl,-rpath,../../PushFramework/../output -L../../PushFramework/../output -lpushframework

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../output/flexpolicyserver

../output/flexpolicyserver: ../../PushFramework/../output/libpushframework.so

../output/flexpolicyserver: ${OBJECTFILES}
	${MKDIR} -p ../output
	${LINK.cc} -o ../output/flexpolicyserver ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/INIReader.o: src/INIReader.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../../PushFramework/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/INIReader.o src/INIReader.cpp

${OBJECTDIR}/src/LicenseProtocol.o: src/LicenseProtocol.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../../PushFramework/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/LicenseProtocol.o src/LicenseProtocol.cpp

${OBJECTDIR}/src/PolicyRequest.o: src/PolicyRequest.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../../PushFramework/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/PolicyRequest.o src/PolicyRequest.cpp

${OBJECTDIR}/src/PolicyResponse.o: src/PolicyResponse.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../../PushFramework/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/PolicyResponse.o src/PolicyResponse.cpp

${OBJECTDIR}/src/FlexLicenseServer.o: src/FlexLicenseServer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../../PushFramework/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/FlexLicenseServer.o src/FlexLicenseServer.cpp

${OBJECTDIR}/src/ini.o: src/ini.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../../PushFramework/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ini.o src/ini.cpp

${OBJECTDIR}/src/stdafx.o: src/stdafx.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../../PushFramework/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/stdafx.o src/stdafx.cpp

${OBJECTDIR}/src/FlexClientFactory.o: src/FlexClientFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../../PushFramework/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/FlexClientFactory.o src/FlexClientFactory.cpp

# Subprojects
.build-subprojects:
	cd ../../PushFramework && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../output/flexpolicyserver

# Subprojects
.clean-subprojects:
	cd ../../PushFramework && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
