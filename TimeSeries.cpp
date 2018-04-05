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
        wxColor(40, 153, 193), 
        wxColor(255, 255, 255), 
        wxColor(40, 153, 193, 0x11), 
        points1));  
    chartData.AddDataset(dataset1);
    
    wxLineChartDataset::ptr dataset2(new wxLineChartDataset(
        series2Name, 
        wxColor(253, 56, 50),
        wxColor(255, 255, 255), 
        wxColor(253, 56, 50, 0x11), 
        points2));
    chartData.AddDataset(dataset2);

    return chartData;
}
