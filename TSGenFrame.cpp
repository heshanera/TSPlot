/* 
 * File:   TSGen.cpp
 * Author: heshan
 * 
 * Created on April 1, 2018, 9:13 PM
 */

#include "TSGenFrame.h"
#include "TimeSeries.h"
#include "ChartLegendBox.h"
#include "TSGen.h"

#include <wx/sizer.h>
#include <wx/grid.h>

TSGenFrame::TSGenFrame() : wxFrame(NULL, -1, "TSAnalyser", wxPoint(-1, -1), wxSize(450, 600)) {
    
    
    panel = new wxPanel(this, -1);
    
    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);

    wxFlexGridSizer *flexGrid = new wxFlexGridSizer(3, 1, 9, 25);

    wxTextCtrl *tc1 = new wxTextCtrl(panel, -1);
//    wxTextCtrl *tc2 = new wxTextCtrl(panel, -1);
//    wxTextCtrl *tc3 = new wxTextCtrl(panel, -1, wxT(""),
//        wxPoint(-1, -1), wxSize(-1, -1), wxTE_MULTILINE);

    
    loadTimeSeriesData();       
//    wxSize frameSize = this->GetSize();
//    int chartHeight = (2*frameSize.GetY())/3;
//    lineChartCtrl->SetMinSize(wxSize(-1,chartHeight));
//    hbox3->Add(lineChartCtrl, 1, wxEXPAND);
//    vbox->Add(hbox3, 1, wxLEFT | wxRIGHT | wxTOP | wxEXPAND, 10);    
//    vbox->Add(-1, 5);
//    legendCtrl->SetMaxSize(wxSize(-1,22));
    
    flexGrid->Add(tc1, 1, wxEXPAND);
    flexGrid->Add(lineChartCtrl, 1, wxEXPAND);
    flexGrid->Add(legendCtrl, 1, wxEXPAND);

    flexGrid->AddGrowableRow(1, 1);
    flexGrid->AddGrowableCol(0, 1);

    hbox->Add(flexGrid, 1, wxALL | wxEXPAND, 15);
    panel->SetSizer(hbox);
    Centre();
    
//    EVT_SIZE(TSGenFrame::resizeChart)
//    Bind(wxEVT_SIZE, &TSGenFrame::resizeChart, this);
//    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
//
//    wxBoxSizer *hbox3 = new wxBoxSizer(wxHORIZONTAL);
//    loadTimeSeriesData();       
//    
//    
//    wxSize frameSize = this->GetSize();
//    int chartHeight = (2*frameSize.GetY())/3;
//    lineChartCtrl->SetMinSize(wxSize(-1,chartHeight));
//    hbox3->Add(lineChartCtrl, 1, wxEXPAND);
//    vbox->Add(hbox3, 1, wxLEFT | wxRIGHT | wxTOP | wxEXPAND, 10);    
//    vbox->Add(-1, 5);
//    
//    
//    
//    wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);
//    legendCtrl->SetMaxSize(wxSize(-1,22));
//    hbox1->Add(legendCtrl, 1, wxEXPAND);
//    vbox->Add(hbox1, 1, wxEXPAND | wxLEFT | wxRIGHT, 10);
//    vbox->Add(-1, 5);
//    
////    wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);
////    wxButton *btn12 = new wxButton(panel, wxID_ANY, wxT("Ok"));
////    hbox1->Add(btn12, 0);
////    wxButton *btn22 = new wxButton(panel, wxID_ANY, wxT("Close"));
////    hbox1->Add(btn22, 0, wxLEFT | wxBOTTOM , 5);
////    legendCtrl->SetMaxSize(wxSize(-1,22));
////    hbox1->Add(legendCtrl, 1, wxEXPAND);
////    vbox->Add(hbox1, 0, wxALIGN_RIGHT | wxRIGHT, 10);
//    
//    wxBoxSizer *hbox6 = new wxBoxSizer(wxHORIZONTAL);
//    wxButton *series1btn = new wxButton(panel, wxID_ANY, "new");
//    wxButton *series2btn = new wxButton(panel, wxID_ANY, wxT("predictions"));
//    wxButton *series3btn = new wxButton(panel, wxID_ANY, wxT("refresh"));
//    hbox6->Add(series1btn, 1, wxEXPAND);
//    hbox6->Add(series2btn, 1, wxEXPAND);
//    hbox6->Add(series3btn, 1, wxEXPAND);
//    vbox->Add(hbox6, 1, wxLEFT | wxRIGHT | wxEXPAND, 10);
//    vbox->Add(-1, 5);
//
//    wxBoxSizer *hbox5 = new wxBoxSizer(wxHORIZONTAL);
//    wxButton *btn1 = new wxButton(panel, wxID_ANY, wxT("Ok"));
//    hbox5->Add(btn1, 0);
//    wxButton *btn2 = new wxButton(panel, wxID_ANY, wxT("Close"));
//    hbox5->Add(btn2, 0, wxLEFT | wxBOTTOM , 5);
//    vbox->Add(hbox5, 0, wxALIGN_RIGHT | wxRIGHT, 10);
//
//    panel->SetSizer(vbox);
//
//    Centre();

    
}

int TSGenFrame::loadTimeSeriesData(/*
    wxVector<wxString> labels, 
    std::string series1Name, 
    wxVector<wxDouble> points1, 
    std::string series2Name, 
    wxVector<wxDouble> points2*/) {

    wxVector<wxString> labels;
    for(int i = 0; i < 35; i++){
        int val = 1;
        labels.push_back(std::to_string(val));
        val++;
    }
    
    wxVector<wxDouble> points1;
    points1.push_back(3);
    points1.push_back(-2.5);
    points1.push_back(-1.2);
    points1.push_back(3);
    points1.push_back(6);
    points1.push_back(5);
    points1.push_back(1);
    points1.push_back(3);
    points1.push_back(-2.5);
    points1.push_back(-1.2);
    points1.push_back(3);
    points1.push_back(6);
    points1.push_back(5);
    points1.push_back(1);
    points1.push_back(3);
    points1.push_back(-2.5);
    points1.push_back(-1.2);
    points1.push_back(3);
    points1.push_back(6);
    points1.push_back(5);
    points1.push_back(1);
    points1.push_back(3);
    points1.push_back(-2.5);
    points1.push_back(-1.2);
    points1.push_back(3);
    points1.push_back(6);
    points1.push_back(5);
    points1.push_back(1);
    
    wxVector<wxDouble> points2;
    points2.push_back(1);
    points2.push_back(-1.33);
    points2.push_back(2.5);
    points2.push_back(7);
    points2.push_back(3);
    points2.push_back(-1.8);
    points2.push_back(0.4);
    points2.push_back(1);
    points2.push_back(-1.33);
    points2.push_back(2.5);
    points2.push_back(7);
    points2.push_back(3);
    points2.push_back(-1.8);
    points2.push_back(0.4);
    points2.push_back(1);
    points2.push_back(-1.33);
    points2.push_back(2.5);
    points2.push_back(7);
    points2.push_back(3);
    points2.push_back(-1.8);
    points2.push_back(0.4);
    points2.push_back(1);
    points2.push_back(-1.33);
    points2.push_back(2.5);
    points2.push_back(7);
    points2.push_back(3);
    points2.push_back(-1.8);
    points2.push_back(0.4);
    points2.push_back(1);
    points2.push_back(-1.33);
    points2.push_back(2.5);
    points2.push_back(7);
    points2.push_back(3);
    points2.push_back(-1.8);
    points2.push_back(0.4);
    
    TimeSeries *timeSeries = new TimeSeries();
    wxLineChartData chartData = timeSeries->load(labels, "Time Series 1", points1, "Predictions", points2);
    wxChartLegendData legendData(chartData.GetDatasets());
    
    // Create the line chart widget from the constructed data
    lineChartCtrl = new wxLineChartCtrl(
        panel, wxID_ANY, 
        chartData, wxDefaultPosition, 
        wxDefaultSize, wxBORDER_RAISED
    );

    
    wxSize * size;
    size = new wxSize(-1,22);
    // Create the legend widget
    legendCtrl = new ChartLegendBox(
        panel, wxID_ANY, 
        legendData, wxDefaultPosition, 
        *size, wxBORDER_RAISED
    );
    
    return 0;
}

void TSGenFrame::OnExit(wxCommandEvent& event) {
    Close(true);
}

void TSGenFrame::OnAbout(wxCommandEvent& event) {
    wxMessageBox("This is a wxWidgets Hello World example",
                 "About Hello World", wxOK | wxICON_INFORMATION);
}

void TSGenFrame::OnHello(wxCommandEvent& event) {
    wxLogMessage("Hello world from wxWidgets!");
}

void TSGenFrame::resizeChart(wxSizeEvent& event) {
    wxSize frameSize = this->GetSize();
//    int chartHeight = (2*frameSize.GetY())/3;
//    lineChartCtrl->SetMinSize(wxSize(-1,chartHeight));
//    lineChartCtrl->Refresh();
    std::cout<<frameSize.GetY()<<"\n";
}
