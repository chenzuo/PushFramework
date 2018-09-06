/*
 * File:   stdafx.h
 * Author: ahmed
 *
 * Created on 6 juin 2011, 20:06
 */

#ifndef STDAFX_H
#define	STDAFX_H

#pragma once


#include "Plateform.h"

#ifdef Plateform_Windows
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#endif





#include <stdio.h>


#include <ctype.h>
#include <iostream>
#include <fstream>


#include <string>

#include <map>
#include <vector>
#include <set>
using namespace std;

#include <PushFrameworkInc.h>
#include <TCPSocketInclude.h>
#include <XMLProtocolInc.h>
#include <ChatProtocolInc.h>








#endif	/* STDAFX_H */

