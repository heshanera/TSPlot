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
#include <wx/charts/wxcharts.h>
#include "ChartLegendBox.h"

class TSGenFrame : public wxFrame
{
public:
    TSGenFrame();
    int loadWidgets();
    int loadTimeSeriesData(
        wxVector<wxString> labels, 
        std::string series1Name, 
        wxVector<wxDouble> points1, 
        std::string series2Name, 
        wxVector<wxDouble> points2
    );

private:
//    void OnHello(wxCommandEvent& event);
//    void OnExit(wxCommandEvent& event);
//    void OnAbout(wxCommandEvent& event);
    void clearData(wxCommandEvent& event);
    
    
    wxPanel *panel;
    wxLineChartCtrl* lineChartCtrl;
    wxLineChartCtrl* lineChartSeries1Ctrl;
    wxLineChartCtrl* lineChartSeries2Ctrl;
    
    ChartLegendBox* legendCtrl;

    wxDECLARE_EVENT_TABLE();
    
};
enum
{
    ID_Hello = 1,
    CLEAR_BUTTON = 2
};

#endif /* TSGEN_H */

