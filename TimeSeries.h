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
#include <wx/charts/wxcharts.h>

class TimeSeries {
public:
    TimeSeries();
    wxLineChartData load(wxVector<wxString> labels, std::string series1Name, wxVector<wxDouble> points1, std::string series2Name, wxVector<wxDouble> points2);
    
private:  
};

#endif

