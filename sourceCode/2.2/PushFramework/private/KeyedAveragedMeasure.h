/********************************************************************
	File :			KeyedAveragedMeasure.h
	Creation date :	2010/6/27

	License :			Copyright 2010 Ahmed Charfeddine, http://www.pushframework.com

				   Licensed under the Apache License, Version 2.0 (the "License");
				   you may not use this file except in compliance with the License.
				   You may obtain a copy of the License at

					   http://www.apache.org/licenses/LICENSE-2.0

				   Unless required by applicable law or agreed to in writing, software
				   distributed under the License is distributed on an "AS IS" BASIS,
				   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
				   See the License for the specific language governing permissions and
				   limitations under the License.


*********************************************************************/
#ifndef KeyedAveragedMeasure__INCLUDED
#define KeyedAveragedMeasure__INCLUDED

#pragma once
#include "Measure.h"

namespace PushFramework
{


class MKAveragedMeasureArgs : public MeasureArgs
{
public:
    int key;
    double dwValue;
};


//By Key growing measure
class KeyedAveragedMeasure :
    public Measure
{
    typedef std::map<int, double> mappedValuesT;
public:
    KeyedAveragedMeasure(std::string name);
    virtual ~KeyedAveragedMeasure(void);
private:
    virtual void addObservation(MeasureArgs& args);
    virtual std::string collectAndReset(std::string timeStamp);

private:
    mappedValuesT mappedValues;
    //
    double getMean();
    double getDispersion(double mean);
};

}

#endif // KeyedAveragedMeasure__INCLUDED
