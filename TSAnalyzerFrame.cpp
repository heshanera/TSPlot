/* 
 * File:   TSGen.cpp
 * Author: heshan
 * 
 * Created on April 1, 2018, 9:13 PM
 */

#include "TSAnalyzerFrame.h"
#include "TimeSeries.h"
#include "ChartLegendBox.h"
#include "TSAnalyzer.h"

#include <wx/sizer.h>
#include <wx/grid.h>
#include <wx/artprov.h>

TSGenFrame::TSGenFrame() : wxFrame(NULL, -1, "TSAnalyser", wxPoint(-1, -1), wxSize(950, 600)) {
    panel = new wxPanel(this, -1);
}

int TSGenFrame::loadWidgets(){
    
    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
    wxFlexGridSizer *flexGrid = new wxFlexGridSizer(4, 1, 5, 25);

    wxFlexGridSizer *toolBar = new wxFlexGridSizer(1, 5, 0, 0);
    toolBar->AddGrowableCol(2, 1);
    
    wxButton *addSeriesBtn = new wxButton(panel, wxID_ANY);
    addSeriesBtn->SetBitmap(wxBitmap("bitmaps/add.bmp",wxBITMAP_DEFAULT_TYPE));
    addSeriesBtn->SetMaxSize(wxSize(45,45));
    
    wxButton *removeSeriesBtn = new wxButton(panel, wxID_ANY);
    removeSeriesBtn->SetBitmap(wxBitmap("bitmaps/remove.bmp",wxBITMAP_DEFAULT_TYPE));
    removeSeriesBtn->SetMaxSize(wxSize(45,45));
    
    wxButton *refreshSeriesBtn = new wxButton(panel, wxID_ANY);
    refreshSeriesBtn->SetBitmap(wxBitmap("bitmaps/refresh.bmp",wxBITMAP_DEFAULT_TYPE));
    refreshSeriesBtn->SetMaxSize(wxSize(45,45));
    
    wxButton *settingsBtn = new wxButton(panel, wxID_ANY);
    settingsBtn->SetBitmap(wxBitmap("bitmaps/settings.bmp",wxBITMAP_DEFAULT_TYPE));
    settingsBtn->SetMaxSize(wxSize(45,45));
    
    toolBar->Add(addSeriesBtn, 0, wxRIGHT , 5);
    toolBar->Add(removeSeriesBtn, 0, wxRIGHT , 5);
    toolBar->Add(refreshSeriesBtn, 0, wxRIGHT , 5);
    toolBar->AddSpacer(20);
    toolBar->Add(settingsBtn, 0);
    
    wxBoxSizer *timeSeriesBar = new wxBoxSizer(wxHORIZONTAL);
    timeSeriesBar->Add(lineChartSeries1Ctrl, 1, wxRIGHT | wxBOTTOM | wxEXPAND, 5);
    timeSeriesBar->Add(lineChartSeries2Ctrl, 1, wxLEFT | wxBOTTOM | wxEXPAND, 5);
    
    flexGrid->Add(toolBar, 1, wxBOTTOM | wxEXPAND, 15);
    flexGrid->Add(timeSeriesBar, 1, wxEXPAND);
    flexGrid->Add(lineChartCtrl, 1, wxEXPAND);
    flexGrid->Add(legendCtrl, 1, wxEXPAND);

    flexGrid->AddGrowableRow(1, 1);
    flexGrid->AddGrowableRow(2, 1);
    flexGrid->AddGrowableCol(0, 1);

    hbox->Add(flexGrid, 1, wxALL | wxEXPAND, 15);
    panel->SetSizer(hbox);
    Centre();
    
    Bind(wxEVT_BUTTON, &TSGenFrame::clearData, this, wxID_ANY);
    
    return 0;    
}

int TSGenFrame::loadTimeSeriesData(
    wxVector<wxString> labels, 
    std::string series1Name, 
    wxVector<wxDouble> points1, 
    std::string series2Name, 
    wxVector<wxDouble> points2
) {
    
    wxVector<wxDouble> points0;
    
    TimeSeries *timeSeries = new TimeSeries();
    wxLineChartData chartData = timeSeries->load(labels, series1Name, points1, series2Name, points2);
    wxChartLegendData legendData(chartData.GetDatasets());
    
    // Create the line chart widget from the constructed data
    lineChartCtrl = new wxLineChartCtrl(
        panel, wxID_ANY, 
        chartData, wxDefaultPosition, 
        wxDefaultSize, wxBORDER_RAISED
    );    

    wxSize * size;
    size = new wxSize(-1,30);
    // Create the legend widget
    legendCtrl = new ChartLegendBox(
        panel, wxID_ANY, 
        legendData, wxDefaultPosition, 
        *size, wxBORDER_RAISED
    );
    
    //////////////////////////////////////////////////
    
    TimeSeries *timeSeries1 = new TimeSeries();
    wxLineChartData chartData1 = timeSeries1->load(labels, series1Name, points1, "", points0);
    
    // Create the line chart widget from the constructed data
    lineChartSeries1Ctrl = new wxLineChartCtrl(
        panel, wxID_ANY, 
        chartData1, wxDefaultPosition, 
        wxDefaultSize, wxBORDER_RAISED
    );
    
    ///////////////////////////////////////////////////
    
    TimeSeries *timeSeries2 = new TimeSeries();
    wxLineChartData chartData2 = timeSeries2->load(labels, "", points0, series2Name, points2);
    
    // Create the line chart widget from the constructed data
    lineChartSeries2Ctrl = new wxLineChartCtrl(
        panel, wxID_ANY, 
        chartData2, wxDefaultPosition, 
        wxDefaultSize, wxBORDER_RAISED
    );
    
    ////////////////////////////////////////////////////

    return 0;
}

//void TSGenFrame::OnExit(wxCommandEvent& event) {
//    Close(true);
//}
//
//void TSGenFrame::OnAbout(wxCommandEvent& event) {
//    wxMessageBox("This is a wxWidgets Hello World example",
//                 "About Hello World", wxOK | wxICON_INFORMATION);
//}
//
//void TSGenFrame::OnHello(wxCommandEvent& event) {
//    wxLogMessage("Hello world from wxWidgets!");
//}

void TSGenFrame::clearData(wxCommandEvent& event) {
    std::cout<<"click remove!"<<"\n";
    
    wxVector<wxString> labels;
    labels.push_back("");    
    wxVector<wxDouble> points1;
    points1.push_back(0);
    wxVector<wxDouble> points2;
    points2.push_back(0);
    loadTimeSeriesData(labels, "-", points1, "-", points2);
//    lineChartCtrl->Refresh();
//    
//    this->Refresh();
    lineChartCtrl->Refresh();
    lineChartCtrl->Update();
}

wxBEGIN_EVENT_TABLE(TSGenFrame, wxFrame)
    EVT_BUTTON(CLEAR_BUTTON, TSGenFrame::clearData)
wxEND_EVENT_TABLE()
