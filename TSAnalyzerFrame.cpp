/* 
 * File:   TSGen.cpp
 * Author: heshan
 * 
 * Created on April 1, 2018, 9:13 PM
 */

#include <fstream>
#include <sstream>
#include <iomanip>

#include "TSAnalyzerFrame.h"
#include "TimeSeries.h"
#include "ChartLegendBox.h"
#include "TSAnalyzer.h"

#include <wx/sizer.h>
#include <wx/grid.h>
#include <wx/artprov.h>
#include <wx/filedlg.h> 
#include <wx/string.h>



TSGenFrame::TSGenFrame() : wxFrame(NULL, -1, "TSAnalyser", wxPoint(-1, -1), wxSize(950, 600)) {
    panel = new wxPanel(this, -1);
    maxPoints = 600;
    dataset1Name = "";
    dataset2Name = "";
}

int TSGenFrame::loadWidgets(){
    
    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
    flexGrid = new wxFlexGridSizer(4, 1, 5, 25);

    wxFlexGridSizer *toolBarContainer = new wxFlexGridSizer(1, 2, 0, 0);
    toolBarContainer->AddGrowableCol(0, 1);
    toolBarContainer->AddGrowableCol(1, 1);
    
    wxFlexGridSizer *toolBar1 = new wxFlexGridSizer(1, 5, 0, 0);
    toolBar1->AddGrowableCol(2);
    
    wxFlexGridSizer *toolBar2 = new wxFlexGridSizer(1, 5, 0, 0);
    toolBar2->AddGrowableCol(2);
    
    wxButton *addSeries1Btn = new wxButton(panel, ADD_BUTTON_1);
    addSeries1Btn->SetBitmap(wxBitmap("bitmaps/add.bmp",wxBITMAP_DEFAULT_TYPE));
    addSeries1Btn->SetMaxSize(wxSize(45,45));
    
    wxButton *removeSeries1Btn = new wxButton(panel, CLEAR_BUTTON_1);
    removeSeries1Btn->SetBitmap(wxBitmap("bitmaps/remove.bmp",wxBITMAP_DEFAULT_TYPE));
    removeSeries1Btn->SetMaxSize(wxSize(45,45));
    
    wxButton *refreshSeries1Btn = new wxButton(panel, REFRESH_BUTTON_1);
    refreshSeries1Btn->SetBitmap(wxBitmap("bitmaps/refresh.bmp",wxBITMAP_DEFAULT_TYPE));
    refreshSeries1Btn->SetMaxSize(wxSize(45,45));
    
    wxButton *settings1Btn = new wxButton(panel, RENAME_BUTTON_1);
    settings1Btn->SetBitmap(wxBitmap("bitmaps/settings.bmp",wxBITMAP_DEFAULT_TYPE));
    settings1Btn->SetMaxSize(wxSize(45,45));
    
    toolBar1->Add(addSeries1Btn, 0, wxRIGHT , 5);
    toolBar1->Add(removeSeries1Btn, 0, wxRIGHT , 5);
    toolBar1->Add(refreshSeries1Btn, 0, wxRIGHT , 5);
    toolBar1->Add(settings1Btn, 0);
    
    wxButton *addSeries2Btn = new wxButton(panel, ADD_BUTTON_2);
    addSeries2Btn->SetBitmap(wxBitmap("bitmaps/add.bmp",wxBITMAP_DEFAULT_TYPE));
    addSeries2Btn->SetMaxSize(wxSize(45,45));
    
    wxButton *removeSeries2Btn = new wxButton(panel, CLEAR_BUTTON_2);
    removeSeries2Btn->SetBitmap(wxBitmap("bitmaps/remove.bmp",wxBITMAP_DEFAULT_TYPE));
    removeSeries2Btn->SetMaxSize(wxSize(45,45));
    
    wxButton *refreshSeries2Btn = new wxButton(panel, REFRESH_BUTTON_2);
    refreshSeries2Btn->SetBitmap(wxBitmap("bitmaps/refresh.bmp",wxBITMAP_DEFAULT_TYPE));
    refreshSeries2Btn->SetMaxSize(wxSize(45,45));
    
    wxButton *settings2Btn = new wxButton(panel, RENAME_BUTTON_2);
    settings2Btn->SetBitmap(wxBitmap("bitmaps/settings.bmp",wxBITMAP_DEFAULT_TYPE));
    settings2Btn->SetMaxSize(wxSize(45,45));
    
    toolBar2->Add(addSeries2Btn, 0, wxLEFT , 5);
    toolBar2->Add(removeSeries2Btn, 0, wxLEFT , 5);
    toolBar2->Add(refreshSeries2Btn, 0, wxLEFT , 5);
    toolBar2->Add(settings2Btn, 0, wxLEFT , 5);
    
    toolBarContainer->Add(toolBar1);
    toolBarContainer->Add(toolBar2);
    
    timeSeriesBar = new wxBoxSizer(wxHORIZONTAL);
    timeSeriesBar->Add(lineChartSeries1Ctrl, 1, wxRIGHT | wxBOTTOM | wxEXPAND, 5);
    timeSeriesBar->Add(lineChartSeries2Ctrl, 1, wxLEFT | wxBOTTOM | wxEXPAND, 5);
    
    flexGrid->Add(toolBarContainer, 1, wxEXPAND, 15);
    flexGrid->Add(timeSeriesBar, 1, wxEXPAND);
    flexGrid->Add(lineChartCtrl, 1, wxEXPAND);
    flexGrid->Add(legendCtrl, 1, wxEXPAND);

    flexGrid->AddGrowableRow(1, 1);
    flexGrid->AddGrowableRow(2, 1);
    flexGrid->AddGrowableCol(0, 1);

    hbox->Add(flexGrid, 1, wxALL | wxEXPAND, 15);
    panel->SetSizer(hbox);
    Centre();
    
    Bind(wxEVT_BUTTON, &TSGenFrame::addData1, this, ADD_BUTTON_1);
    Bind(wxEVT_BUTTON, &TSGenFrame::clearData1, this, CLEAR_BUTTON_1);
    Bind(wxEVT_BUTTON, &TSGenFrame::refreshData1, this, REFRESH_BUTTON_1);
    Bind(wxEVT_BUTTON, &TSGenFrame::renameData1, this, RENAME_BUTTON_1);
    
    Bind(wxEVT_BUTTON, &TSGenFrame::addData2, this, ADD_BUTTON_2);
    Bind(wxEVT_BUTTON, &TSGenFrame::clearData2, this, CLEAR_BUTTON_2);
    Bind(wxEVT_BUTTON, &TSGenFrame::refreshData2, this, REFRESH_BUTTON_2);
    Bind(wxEVT_BUTTON, &TSGenFrame::renameData2, this, RENAME_BUTTON_2);
    
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
        wxDefaultSize, wxBORDER_THEME
    );    
    
    wxSize * size;
    size = new wxSize(-1,30);
    // Create the legend widget
    legendCtrl = new ChartLegendBox(
        panel, wxID_ANY, 
        legendData, wxDefaultPosition, 
        *size, wxBORDER_THEME
    );
    
    return 0;
}

int TSGenFrame::loadTimeSeriesData1(
    wxVector<wxString> labels, 
    std::string series1Name, 
    wxVector<wxDouble> points1
) {
    
    wxVector<wxDouble> points0;
    
    TimeSeries *timeSeries1 = new TimeSeries();
    wxLineChartData chartData1 = timeSeries1->load(labels, dataset1Name, points1, dataset2Name, points0);
    
    // Create the line chart widget from the constructed data
    lineChartSeries1Ctrl = new wxLineChartCtrl(
        panel, wxID_ANY, 
        chartData1, wxDefaultPosition, 
        wxDefaultSize, wxBORDER_THEME
    );
    
    return 0;
}

int TSGenFrame::loadTimeSeriesData2(
    wxVector<wxString> labels,  
    std::string series2Name, 
    wxVector<wxDouble> points2
) {
    
    wxVector<wxDouble> points0;
    
    TimeSeries *timeSeries2 = new TimeSeries();
    wxLineChartData chartData2 = timeSeries2->load(labels, "", points0, series2Name, points2);
    
    // Create the line chart widget from the constructed data
    lineChartSeries2Ctrl = new wxLineChartCtrl(
        panel, wxID_ANY, 
        chartData2, wxDefaultPosition, 
        wxDefaultSize, wxBORDER_THEME
    );

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

void TSGenFrame::addData1(wxCommandEvent& event) {
    std::cout<<"add new data series...!"<<"\n";
    wxString fileTypes = "*.txt";
    
    wxString filename = wxFileSelector("Choose a file","","","",fileTypes);
    if ( !filename.empty() ) { 
        
        dataset1Path = filename;
        dataset1Name = "Series 1";
        
        float val = 0;
        std::stringstream stringStream;
        labels.clear();
        for(int i = 0; i < maxPoints; i+=100){
            stringStream.str(std::string());
            stringStream << std::fixed << std::setprecision(2) << val;
            labels.push_back(stringStream.str());
            for (int j = 0; j < 99; j++) {
                labels.push_back("");
                val+=0.5;
            }
        }

        std::string line;
        std::ifstream file (filename);
        points1.clear();
        if (file.is_open()) {
            int i = 0;
            while ( getline (file,line) ) {
                i++;
                points1.push_back(std::stod(line));
                if (i == maxPoints) break;
            }
            file.close();
        }
        else std::cout << "Unable to open file '"<<filename<<"'";
        
        lineChartCtrl->Destroy();
        legendCtrl->Destroy();
        
        timeSeriesBar->Clear(false);
        lineChartSeries1Ctrl->Destroy();

        loadTimeSeriesData(labels, dataset1Name, points1, dataset2Name, points2);
        loadTimeSeriesData1(labels, dataset1Name, points1);

        timeSeriesBar->Add(lineChartSeries1Ctrl, 1, wxRIGHT | wxBOTTOM | wxEXPAND, 5);
        timeSeriesBar->Add(lineChartSeries2Ctrl, 1, wxRIGHT | wxBOTTOM | wxEXPAND, 5);
        flexGrid->Add(lineChartCtrl, 1, wxEXPAND);
        flexGrid->Add(legendCtrl, 1, wxEXPAND);

        panel->Layout();
        panel->Refresh();
        panel->Update();
        
    }   
}

void TSGenFrame::clearData1(wxCommandEvent& event) {
    std::cout<<"data series cleared"<<"\n";
    
    dataset1Name = "-";
    
    wxVector<wxString> labels1; 
    points1.clear();
    
    lineChartCtrl->Destroy();
    legendCtrl->Destroy();
    
    timeSeriesBar->Clear(false);
    lineChartSeries1Ctrl->Destroy();
    
    loadTimeSeriesData(labels, dataset1Name, points1, dataset2Name, points2);
    loadTimeSeriesData1(labels1, dataset1Name, points1);
    
    timeSeriesBar->Add(lineChartSeries1Ctrl, 1, wxRIGHT | wxBOTTOM | wxEXPAND, 5);
    timeSeriesBar->Add(lineChartSeries2Ctrl, 1, wxLEFT | wxBOTTOM | wxEXPAND, 5);
    flexGrid->Add(lineChartCtrl, 1, wxEXPAND);
    flexGrid->Add(legendCtrl, 1, wxEXPAND);

    panel->Layout();
    panel->Refresh();
    panel->Update();
}

void TSGenFrame::refreshData1(wxCommandEvent& event) {
    std::cout<<"refresh data series...!"<<"\n";
    
    if ( dataset1Path.size() > 0) { 
        
        std::string filename = dataset1Path;
        float val = 0;
        std::stringstream stringStream;
        labels.clear();
        for(int i = 0; i < maxPoints; i+=100){
            stringStream.str(std::string());
            stringStream << std::fixed << std::setprecision(2) << val;
            labels.push_back(stringStream.str());
            for (int j = 0; j < 99; j++) {
                labels.push_back("");
                val+=0.5;
            }
        }

        std::string line;
        std::ifstream file (filename);
        points1.clear();
        if (file.is_open()) {
            int i = 0;
            while ( getline (file,line) ) {
                i++;
                points1.push_back(std::stod(line));
                if (i == maxPoints) break;
            }
            file.close();
        }
        else std::cout << "Unable to open file '"<<filename<<"'";
        
        lineChartCtrl->Destroy();
        legendCtrl->Destroy();
        
        timeSeriesBar->Clear(false);
        lineChartSeries1Ctrl->Destroy();

        loadTimeSeriesData(labels, dataset1Name, points1, dataset2Name, points2);
        loadTimeSeriesData1(labels, dataset1Name, points1);

        timeSeriesBar->Add(lineChartSeries1Ctrl, 1, wxRIGHT | wxBOTTOM | wxEXPAND, 5);
        timeSeriesBar->Add(lineChartSeries2Ctrl, 1, wxRIGHT | wxBOTTOM | wxEXPAND, 5);
        flexGrid->Add(lineChartCtrl, 1, wxEXPAND);
        flexGrid->Add(legendCtrl, 1, wxEXPAND);

        panel->Layout();
        panel->Refresh();
        panel->Update();
        
    }   
}

void TSGenFrame::renameData1(wxCommandEvent& event) {
    std::cout<<"data series renamed"<<"\n";
    
    wxString seriesName = wxGetTextFromUser("Enter time series name");
    if (!seriesName.IsEmpty()) {
        dataset1Name = seriesName;
        legendCtrl->Destroy();
        wxVector<wxString> labels;
        wxVector<wxDouble> points1;
        wxVector<wxDouble> points2;
        TimeSeries *timeSeries = new TimeSeries();
        wxLineChartData chartData = timeSeries->load(labels, dataset1Name, points1, dataset2Name, points2);
        wxChartLegendData legendData(chartData.GetDatasets());

        wxSize * size;
        size = new wxSize(-1,30); 
        legendCtrl = new ChartLegendBox(
            panel, wxID_ANY, 
            legendData, wxDefaultPosition, 
            *size, wxBORDER_THEME
        );

        flexGrid->Add(legendCtrl, 1, wxEXPAND);

        panel->Layout();
        panel->Refresh();
        panel->Update();
    }
    
}

void TSGenFrame::addData2(wxCommandEvent& event) {
    std::cout<<"add new data series...!"<<"\n";
    wxString fileTypes = "*.txt";
    
    wxString filename = wxFileSelector("Choose a file","","","",fileTypes);
    if ( !filename.empty() ) { 
        
        dataset2Path = filename;
        dataset2Name = "Series 2";
        
        float val = 0;
        std::stringstream stringStream;
        labels.clear();
        for(int i = 0; i < maxPoints; i+=100){
            stringStream.str(std::string());
            stringStream << std::fixed << std::setprecision(2) << val;
            labels.push_back(stringStream.str());
            for (int j = 0; j < 99; j++) {
                labels.push_back("");
                val+=0.5;
            }
        }

        std::string line;
        std::ifstream file (filename);
        points2.clear();
        if (file.is_open()) {
            int i = 0;
            while ( getline (file,line) ) {
                i++;
                points2.push_back(std::stod(line));
                if (i == maxPoints) break;
            }
            file.close();
        }
        else std::cout << "Unable to open file '"<<filename<<"'";
        
        lineChartCtrl->Destroy();
        legendCtrl->Destroy();
        
        timeSeriesBar->Clear(false);
        lineChartSeries2Ctrl->Destroy();

        loadTimeSeriesData(labels, dataset1Name, points1, dataset2Name, points2);
        loadTimeSeriesData2(labels, dataset2Name, points2);

        timeSeriesBar->Add(lineChartSeries1Ctrl, 1, wxRIGHT | wxBOTTOM | wxEXPAND, 5);
        timeSeriesBar->Add(lineChartSeries2Ctrl, 1, wxRIGHT | wxBOTTOM | wxEXPAND, 5);
        flexGrid->Add(lineChartCtrl, 1, wxEXPAND);
        flexGrid->Add(legendCtrl, 1, wxEXPAND);

        panel->Layout();
        panel->Refresh();
        panel->Update();
        
    }
    
}

void TSGenFrame::clearData2(wxCommandEvent& event) {
    std::cout<<"data series cleared"<<"\n";
    
    dataset2Name = "-";
    
    wxVector<wxString> labels2; 
    points2.clear();
    
    lineChartCtrl->Destroy();
    legendCtrl->Destroy();
    
    timeSeriesBar->Clear(false);
    lineChartSeries2Ctrl->Destroy();
    
    loadTimeSeriesData(labels, dataset1Name, points1, dataset2Name, points2);
    loadTimeSeriesData2(labels2, dataset2Name, points2);
    
    timeSeriesBar->Add(lineChartSeries1Ctrl, 1, wxRIGHT | wxBOTTOM | wxEXPAND, 5);
    timeSeriesBar->Add(lineChartSeries2Ctrl, 1, wxLEFT | wxBOTTOM | wxEXPAND, 5);
    flexGrid->Add(lineChartCtrl, 1, wxEXPAND);
    flexGrid->Add(legendCtrl, 1, wxEXPAND);

    panel->Layout();
    panel->Refresh();
    panel->Update();
}

void TSGenFrame::refreshData2(wxCommandEvent& event) {
    std::cout<<"refresh data series...!"<<"\n";
    
    if ( dataset2Path.size() > 0) { 
        
        std::string filename = dataset2Path;
        float val = 0;
        std::stringstream stringStream;
        labels.clear();
        for(int i = 0; i < maxPoints; i+=100){
            stringStream.str(std::string());
            stringStream << std::fixed << std::setprecision(2) << val;
            labels.push_back(stringStream.str());
            for (int j = 0; j < 99; j++) {
                labels.push_back("");
                val+=0.5;
            }
        }

        std::string line;
        std::ifstream file (filename);
        points2.clear();
        if (file.is_open()) {
            int i = 0;
            while ( getline (file,line) ) {
                i++;
                points2.push_back(std::stod(line));
                if (i == maxPoints) break;
            }
            file.close();
        }
        else std::cout << "Unable to open file '"<<filename<<"'";
        
        lineChartCtrl->Destroy();
        legendCtrl->Destroy();
        
        timeSeriesBar->Clear(false);
        lineChartSeries2Ctrl->Destroy();

        loadTimeSeriesData(labels, dataset1Name, points1, dataset2Name, points2);
        loadTimeSeriesData2(labels, dataset2Name, points2);

        timeSeriesBar->Add(lineChartSeries1Ctrl, 1, wxRIGHT | wxBOTTOM | wxEXPAND, 5);
        timeSeriesBar->Add(lineChartSeries2Ctrl, 1, wxRIGHT | wxBOTTOM | wxEXPAND, 5);
        flexGrid->Add(lineChartCtrl, 1, wxEXPAND);
        flexGrid->Add(legendCtrl, 1, wxEXPAND);

        panel->Layout();
        panel->Refresh();
        panel->Update();
        
    }   
}

void TSGenFrame::renameData2(wxCommandEvent& event) {
    std::cout<<"data series renamed"<<"\n";
    
    wxString seriesName = wxGetTextFromUser("Enter time series name");
    if (!seriesName.IsEmpty()) {
        dataset2Name = seriesName;
        legendCtrl->Destroy();
        wxVector<wxString> labels;
        wxVector<wxDouble> points1;
        wxVector<wxDouble> points2;
        TimeSeries *timeSeries = new TimeSeries();
        wxLineChartData chartData = timeSeries->load(labels, dataset1Name, points1, dataset2Name, points2);
        wxChartLegendData legendData(chartData.GetDatasets());

        wxSize * size;
        size = new wxSize(-1,30); 
        legendCtrl = new ChartLegendBox(
            panel, wxID_ANY, 
            legendData, wxDefaultPosition, 
            *size, wxBORDER_THEME
        );

        flexGrid->Add(legendCtrl, 1, wxEXPAND);

        panel->Layout();
        panel->Refresh();
        panel->Update();
    }
    
}

wxBEGIN_EVENT_TABLE(TSGenFrame, wxFrame)
    EVT_BUTTON(ADD_BUTTON_1, TSGenFrame::addData1)    
    EVT_BUTTON(CLEAR_BUTTON_1, TSGenFrame::clearData1)
    EVT_BUTTON(REFRESH_BUTTON_1, TSGenFrame::refreshData1)
    EVT_BUTTON(RENAME_BUTTON_1, TSGenFrame::renameData1)    
    EVT_BUTTON(ADD_BUTTON_2, TSGenFrame::addData2)    
    EVT_BUTTON(CLEAR_BUTTON_2, TSGenFrame::clearData2)    
    EVT_BUTTON(REFRESH_BUTTON_2, TSGenFrame::refreshData2)   
    EVT_BUTTON(RENAME_BUTTON_2, TSGenFrame::renameData2)       
wxEND_EVENT_TABLE()
