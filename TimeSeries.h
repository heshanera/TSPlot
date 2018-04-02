/* 
 * File:   TimeSeries.h
 * Author: heshan
 *
 * Created on April 1, 2018, 11:25 PM
 */

#ifndef TIMESERIES_H
#define TIMESERIES_H

#include <wx/frame.h>
#include <wx/panel.h>

class TimeSeries {
public:
    TimeSeries(const wxString& title, wxFrame *frame, wxStandardID wxID_ANY);
    int load(wxVector<wxString> labels, wxVector<wxDouble> points1, wxVector<wxDouble> points2);
private:
    wxPanel* panel;
    
};

#endif

