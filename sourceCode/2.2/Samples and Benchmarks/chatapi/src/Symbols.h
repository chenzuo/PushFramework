/*
 * File:   Symbols.h
 * Author: ahmed
 *
 * Created on 6 juin 2011, 20:07
 */


#ifndef SYMBOLS_H
#define	SYMBOLS_H


#include "Plateform.h"

//Export/Import symbols :
#ifdef Plateform_Windows

#ifdef CHATAPI_EXPORTS
#define CHATAPI_API __declspec(dllexport)
#else
#define CHATAPI_API __declspec(dllimport)
#endif

#else

#ifdef CHATAPI_EXPORTS
#define CHATAPI_API
#else
#define CHATAPI_API
#endif

#endif


#endif	/* SYMBOLS_H */

