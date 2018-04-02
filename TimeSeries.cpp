/* 
 * File:   TimeSeries.cpp
 * Author: heshan
 * 
 * Created on April 1, 2018, 11:25 PM
 */

#include "TimeSeries.h"
#include <wx/panel.h>
#include <wx/sizer.h>
#include "wxCharts/include/wx/charts/wxcharts.h"


TimeSeries::TimeSeries(const wxString& title) : wxFrame(NULL, wxID_ANY, title) {
	// Create a top-level panel to hold all the contents of the frame
	wxPanel* panel = new wxPanel(this, wxID_ANY);

	// Create the data for the line chart widget
	wxVector<wxString> labels;
	labels.push_back("January");
	labels.push_back("February");
	labels.push_back("March");
	labels.push_back("April");
	labels.push_back("May");
	labels.push_back("June");
	labels.push_back("July");
	wxLineChartData chartData(labels);
	
	// Add the first dataset
	wxVector<wxDouble> points1;
	points1.push_back(3);
	points1.push_back(-2.5);
	points1.push_back(-1.2);
	points1.push_back(3);
	points1.push_back(6);
	points1.push_back(5);
	points1.push_back(1);
	wxLineChartDataset::ptr dataset1(new wxLineChartDataset(
		"My First Dataset", wxColor(220, 220, 220), 
		wxColor(255, 255, 255), wxColor(220, 220, 220, 0x33), 
		points1));  
	chartData.AddDataset(dataset1);

	// Add the second dataset
	wxVector<wxDouble> points2;
	points2.push_back(1);
	points2.push_back(-1.33);
	points2.push_back(2.5);
	points2.push_back(7);
	points2.push_back(3);
	points2.push_back(-1.8);
	points2.push_back(0.4);
	wxLineChartDataset::ptr dataset2(new wxLineChartDataset(
		"My Second Dataset", wxColor(151, 187, 205),
		wxColor(255, 255, 255), wxColor(151, 187, 205, 0x33), 
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

	// Set up the sizer for the frame
	wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
	topSizer->Add(panel, 1, wxEXPAND);
	SetSizerAndFit(topSizer);
}
