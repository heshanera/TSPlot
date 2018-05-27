/* 
 * File:   TSPlotFrame.h
 * Author: heshan
 *
 * Created on April 1, 2018, 9:13 PM
 */

#ifndef TSPLOTFRAME_H
#define TSPLOTFRAME_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <wx/charts/wxcharts.h>
#include <wx/spinctrl.h>
#include "ChartLegendBox.h"

class TSPlotFrame : public wxFrame
{
public:
    TSPlotFrame();
    int loadWidgets();
    int loadTimeSeriesData(
        wxVector<wxString> labels, 
        std::string series1Name, 
        wxVector<wxDouble> points1, 
        std::string series2Name, 
        wxVector<wxDouble> points2
    );
    int loadTimeSeriesData1(
        wxVector<wxString> labels, 
        std::string series1Name, 
        wxVector<wxDouble> points1
    );
    int loadTimeSeriesData2(
        wxVector<wxString> labels, 
        std::string series2Name, 
        wxVector<wxDouble> points2
    );

private:
//    void OnHello(wxCommandEvent& event);
//    void OnExit(wxCommandEvent& event);
//    void OnAbout(wxCommandEvent& event);
    void addData1(wxCommandEvent& event);
    void clearData1(wxCommandEvent& event);
    void refreshData1(wxCommandEvent& event);
    void renameData1(wxCommandEvent& event);
    
    void addData2(wxCommandEvent& event);
    void clearData2(wxCommandEvent& event);
    void refreshData2(wxCommandEvent& event);
    void renameData2(wxCommandEvent& event);
    
    void refreshBoth(wxCommandEvent& event);
    
    wxPanel * panel;
    
    wxFlexGridSizer * flexGrid;
    wxBoxSizer * timeSeriesBar;
    
    wxLineChartCtrl * lineChartCtrl;
    wxLineChartCtrl * lineChartSeries1Ctrl;
    wxLineChartCtrl * lineChartSeries2Ctrl;
    
    wxLineChart * chart;
    
    ChartLegendBox* legendCtrl;
    
    wxVector<wxString> labels;
    
    wxVector<wxString> labels1;
    wxVector<wxString> labels2;
    
    wxVector<wxDouble> points1;
    wxVector<wxDouble> points2;
    
    std::string dataset1Path;
    std::string dataset2Path;
    
    std::string dataset1Name;
    std::string dataset2Name;
    
    int maxPoints;
    int maxPointsS1;
    int maxPointsS2;
    
    int minPointsS1;
    int minPointsS2;
    
//    wxSpinCtrl * series1Spin1;
//    wxSpinCtrl * series1Spin2;
//    wxSpinCtrl * series2Spin1;
//    wxSpinCtrl * series2Spin2;
    
    wxButton * refreshBothBtn;
    wxFlexGridSizer * timeWindowContainer;
    wxSpinCtrl * seriesSpin1;
    wxSpinCtrl * seriesSpin2;
    
    wxStaticText * seriesLable;

    wxDECLARE_EVENT_TABLE();
    
};
enum
{
    ADD_BUTTON_1 = 1,
    CLEAR_BUTTON_1 = 2,
    REFRESH_BUTTON_1 = 3,
    RENAME_BUTTON_1 = 4,
    ADD_BUTTON_2 = 5,
    CLEAR_BUTTON_2 = 6,
    REFRESH_BUTTON_2 = 7,
    RENAME_BUTTON_2 = 8,
    REFRESH_BUTTON_3 = 9,
};

#endif /* TSPLOTFRAME_H */

