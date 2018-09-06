#pragma once

class CChatInboxManager
{
public:

    CChatInboxManager(CEdit& _chatHistoryEdit, CComboBox& _viewsList)
        :chatHistoryEdit(_chatHistoryEdit), viewsList(_viewsList)
    {
        curView = "";
    }

    ~CChatInboxManager(void)
    {
    }

    void OnViewChanged()
    {
        int nIndex = viewsList.GetCurSel();
        CString strView;
        viewsList.GetLBText(nIndex, strView);
        curView = CT2CA(strView);

        //
        historyMapT::iterator it = historyMap.find(curView);
        historyVectT* pHistoryVect = NULL;
        if (it == historyMap.end())
        {
            pHistoryVect = new historyVectT;
            historyMap[curView] = pHistoryVect;
        }
        else
            pHistoryVect = it->second;


        chatHistoryEdit.SetSel(0, -1);
        chatHistoryEdit.ReplaceSel(_T(""));
        //
        for (int i=0; i < pHistoryVect->size(); i++)
        {
            std::string msg = pHistoryVect->at(i);
            PrintToHistory(msg);
        }
    }


    void DeliverChatToView(std::string msg, std::string view ="" )
    {
        if(view == "")
            view = curView;
        //
        historyMapT::iterator it = historyMap.find(view);
        if (it != historyMap.end())
        {
            historyVectT* pHistoryVect = it->second;
            pHistoryVect->push_back(msg);
            if (curView == view)
            {
                PrintToHistory(msg);
            }
        }
    }


    void AddView(std::string view)
    {
        if (historyMap.find(view) != historyMap.end())
            return;

        historyMap[view] = new historyVectT;
        viewsList.InsertString(viewsList.GetCount(), CA2CT(view.c_str()));
    }

    std::string getCurView() const
    {
        return curView;
    }
private:
    CEdit& chatHistoryEdit;
    CComboBox& viewsList;
    //
    typedef std::vector<std::string> historyVectT;
    typedef std::map<std::string, historyVectT*> historyMapT;
    //
    historyMapT historyMap;
    std::string curView;

    void PrintToHistory(std::string msg)
    {
        CString str = CA2CT(msg.c_str());
        str+= _T("\n");

        chatHistoryEdit.SetSel(-1);
        chatHistoryEdit.ReplaceSel(str);
    }
};
