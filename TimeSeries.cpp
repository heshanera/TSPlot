/* 
 * File:   TimeSeries.cpp
 * Author: heshan
 * 
 * Created on April 1, 2018, 11:25 PM
 */

#include "TimeSeries.h"
#include <wx/sizer.h>

TimeSeries::TimeSeries() {
    // Create a top-level panel to hold all the contents of the frame

}

wxLineChartData TimeSeries::load(wxVector<wxString> labels,std::string series1Name, wxVector<wxDouble> points1, std::string series2Name, wxVector<wxDouble> points2) {
    
    wxLineChartData chartData(labels);
    
    wxLineChartDataset::ptr dataset1(new wxLineChartDataset(
        series1Name, 
        wxColor(220, 220, 220), 
        wxColor(255, 255, 255), 
        wxColor(220, 220, 220, 0x33), 
        points1));  
    chartData.AddDataset(dataset1);
    
    wxLineChartDataset::ptr dataset2(new wxLineChartDataset(
        series2Name, 
        wxColor(151, 187, 205),
        wxColor(255, 255, 255), 
        wxColor(151, 187, 205, 0x33), 
        points2));
    chartData.AddDataset(dataset2);

    return chartData;
}
