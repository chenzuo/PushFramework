#pragma once

#include "Plateform.h"

#ifdef Plateform_Windows
#include "targetver.h"
#include <atlcomtime.h>

#define sleep Sleep
#endif


#include <stdio.h>
#include <stdlib.h>

#include <ctype.h>


#include <string.h>
#include <sstream>
#include <iostream>
#include <fstream>



#include <time.h>

#include <map>
#include <vector>
#include <set>
using namespace std;

#include <TCPSocketInclude.h>
#include <ChatAPI.h>

extern string fixedMessage;


