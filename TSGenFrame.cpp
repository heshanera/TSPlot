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

TSGenFrame::TSGenFrame() : wxFrame(NULL, -1, "TSAnalyser", wxPoint(-1, -1), wxSize(450, 400)) {
    
    panel = new wxPanel(this, -1);

    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

//    wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);
//    wxStaticText *st1 =  new wxStaticText(panel, wxID_ANY, wxT("Class Name"));
//    hbox1->Add(st1, 0, wxRIGHT, 8);
//    wxTextCtrl *tc = new wxTextCtrl(panel, wxID_ANY);
//    hbox1->Add(tc, 1);
//    vbox->Add(hbox1, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
//    vbox->Add(-1, 10);
//
    

    wxBoxSizer *hbox3 = new wxBoxSizer(wxHORIZONTAL);
    loadTimeSeriesData();       
    hbox3->Add(lineChartCtrl, 1, wxEXPAND);
    vbox->Add(hbox3, 1, wxLEFT | wxRIGHT | wxTOP | wxEXPAND, 10);    
    vbox->Add(-1, 5);
    
//    wxColour col1, col2;
//    col1.Set(wxT("#4f5049"));
//    col2.Set(wxT("#ededed"));
//    
//    wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);
//    wxStaticText *ts1 = new wxStaticText(panel, wxID_ANY, wxT("time series 1"));
//    hbox2->Add(ts1, 0, 1, 1);
//    hbox2->AddSpacer(20);
//    wxStaticText *ts2 = new wxStaticText(panel, wxID_ANY, wxT("predictions"));
//    hbox2->Add(ts2, 0);
//    vbox->Add(hbox2, 0, wxLEFT | wxTOP, 10); 
//    vbox->Add(-1, 10);
    
    
    
    wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);
    legendCtrl->SetMaxSize(wxSize(-1,22));
    int tmp = legendCtrl->GetMaxHeight();
    hbox1->Add(legendCtrl, 1, wxEXPAND);
    vbox->Add(hbox1, 1, wxEXPAND | wxLEFT | wxRIGHT, 10);
    vbox->Add(-1, 5);
    
    wxBoxSizer *hbox6 = new wxBoxSizer(wxHORIZONTAL);
    wxButton *series1btn = new wxButton(panel, wxID_ANY, std::to_string(tmp));
    wxButton *series2btn = new wxButton(panel, wxID_ANY, wxT("predictions"));
    wxButton *series3btn = new wxButton(panel, wxID_ANY, wxT("refresh"));
    hbox6->Add(series1btn, 1, wxEXPAND);
    hbox6->Add(series2btn, 1, wxEXPAND);
    hbox6->Add(series3btn, 1, wxEXPAND);
    vbox->Add(hbox6, 1, wxLEFT | wxRIGHT | wxEXPAND, 10);
    vbox->Add(-1, 5);
    
    
//    wxBoxSizer *hbox4 = new wxBoxSizer(wxHORIZONTAL);
//    hbox4->Add(legendCtrl, 1, wxEXPAND);
    
//    wxCheckBox *cb1 = new wxCheckBox(panel, wxID_ANY, wxT("Case Sensitive"));
//    hbox0->Add(cb1);
//    
//    wxCheckBox *cb2 = new wxCheckBox(panel, wxID_ANY, wxT("Nested Classes"));
//    hbox0->Add(cb2, 0, wxLEFT, 10);
//    
//    wxCheckBox *cb3 = new wxCheckBox(panel, wxID_ANY, wxT("Non-Project Classes"));
//    hbox0->Add(cb3, 0, wxLEFT, 10);
    
//    wxCheckBox *cb1 = new wxCheckBox(panel, wxID_ANY, 
//        wxT("Case Sensitive"));
//
//    hbox4->Add(cb1);
//    
//    vbox->Add(hbox4, 0, wxLEFT, 10);

//    vbox->Add(-1, 25);

    wxBoxSizer *hbox5 = new wxBoxSizer(wxHORIZONTAL);
    wxButton *btn1 = new wxButton(panel, wxID_ANY, wxT("Ok"));
    hbox5->Add(btn1, 0);
    wxButton *btn2 = new wxButton(panel, wxID_ANY, wxT("Close"));
    hbox5->Add(btn2, 0, wxLEFT | wxBOTTOM , 5);
    vbox->Add(hbox5, 0, wxALIGN_RIGHT | wxRIGHT, 10);

    panel->SetSizer(vbox);

    Centre();
    
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
    size = new wxSize(0,0);
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
