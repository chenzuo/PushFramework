#ifndef LoginPuzzleResponse__INCLUDED
#define LoginPuzzleResponse__INCLUDED

#pragma once

#include "ProtocolIDs.h"
#include "Symbols.h"

class CHATPROTOCOL_API LoginPuzzleResponse : public XMLResponse
{
public:
    LoginPuzzleResponse(void);
    ~LoginPuzzleResponse(void);

    int PuzzleQuestion() const
    {
        return puzzleQuestion;
    }
    void PuzzleQuestion(int val)
    {
        puzzleQuestion = val;
    }

private:
    int puzzleQuestion;

protected:
    virtual bool FragmentXML();
    virtual bool ConstructXML();

    virtual void* CreateInstance();
};

#endif // LoginPuzzleResponse__INCLUDED


