#pragma once

class TestSuiteBase
{
public:
    TestSuiteBase(void);
    ~TestSuiteBase(void);
    
    virtual void DoTest() = 0;
    virtual const char* GetTitle() = 0;
    virtual const char* GetDescription() =0;
 
};
