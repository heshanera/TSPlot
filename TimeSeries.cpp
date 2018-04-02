/* 
 * File:   TimeSeries.cpp
 * Author: heshan
 * 
 * Created on April 1, 2018, 11:25 PM
 */

#include "TimeSeries.h"
#include <wx/sizer.h>
#include <wx/charts/wxcharts.h>


TimeSeries::TimeSeries(const wxString& title, wxFrame *frame, wxStandardID wxID_ANY) {
    // Create a top-level panel to hold all the contents of the frame
    panel = new wxPanel(frame, wxID_ANY);
}

int TimeSeries::load(wxVector<wxString> labels, wxVector<wxDouble> points1, wxVector<wxDouble> points2) {
    
    wxLineChartData chartData(labels);
    
    wxLineChartDataset::ptr dataset1(new wxLineChartDataset(
        "My First Dataset", 
        wxColor(220, 220, 220), 
        wxColor(255, 255, 255), 
        wxColor(220, 220, 220, 0x33), 
        points1));  
    chartData.AddDataset(dataset1);
    
    wxLineChartDataset::ptr dataset2(new wxLineChartDataset(
        "My Second Dataset", 
        wxColor(151, 187, 205),
        wxColor(255, 255, 255), 
        wxColor(151, 187, 205, 0x33), 
        points2));
    chartData.AddDataset(dataset2);

    // Create the line chart widget from the constructed data
    wxLineChartCtrl* lineChartCtrl = new wxLineChartCtrl(panel, wxID_ANY, chartData,
            wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);

    // Create the legend widget
    wxChartLegendData legendData(chartData.GetDatasets());
    wxChartLegendCtrl* legendCtrl = new wxChartLegendCtrl(panel, wxID_ANY, legendData,
            wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);

    // Set up the sizer for the panel
    wxBoxSizer* panelSizer = new wxBoxSizer(wxHORIZONTAL);
    panelSizer->Add(lineChartCtrl, 1, wxEXPAND);
    panelSizer->Add(legendCtrl, 1, wxEXPAND);
    panel->SetSizer(panelSizer);
}

