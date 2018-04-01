/* 
 * File:   TSGen.h
 * Author: heshan
 *
 * Created on April 1, 2018, 9:13 PM
 */

#ifndef TSGEN_H
#define TSGEN_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class TSGenFrame : public wxFrame
{
public:
    TSGenFrame();
private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};
enum
{
    ID_Hello = 1
};

#endif /* TSGEN_H */

