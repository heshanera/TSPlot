/* 
 * File:   TSPlotFrame.cpp
 * Author: heshan
 * 
 * Created on April 1, 2018, 9:13 PM
 */

#include <fstream>
#include <sstream>
#include <iomanip>

#include "TSPlotFrame.h"
#include "TimeSeries.h"
#include "ChartLegendBox.h"
#include "TSPlot.h"

#include <wx/sizer.h>
#include <wx/grid.h>
#include <wx/artprov.h>
#include <wx/filedlg.h> 
#include <wx/string.h>

TSPlotFrame::TSPlotFrame() : wxFrame(NULL, wxID_ANY, "TSPlot", wxPoint(-1, -1), wxSize(950, 600)) {
    panel = new wxPanel(this, -1);
    maxPoints = 2000;
    maxPointsS1 = 0;
    maxPointsS2 = 0;
    
    minPointsS1 = 0;
    minPointsS2 = 0;
    
    dataset1Name = "";
    dataset2Name = "";
    
    /*****************************************************************************************/
//    // Create a top-level panel to hold all the contents of the frame
//    wxPanel* panel = new wxPanel(this, wxID_ANY, wxPoint(-1, -1), wxSize(950, 600));
//
//    // Create the data for the scatter plot widget
//    wxScatterPlotData chartData;
//
//    // Add the first dataset
//    wxVector<wxPoint2DDouble> points1;
//    wxVector<wxPoint2DDouble> points2;
//    
//    std::string fileName = "../LSTM/datasets/multiResults.txt";
//    std::string line;
//    std::ifstream file (fileName);
//    std::string token;
//    double margin;
//    
//    int tokenNo = 0;
//    if (file.is_open()) {
//        int i = 0;
//        while ( getline (file,line) ) {
//            i++;
//            if ( i%10 != 0) continue;
//            try{
//                std::stringstream ss(line);
//                tokenNo = 0;
//                while(std::getline(ss, token, ',')) {
//                    if (tokenNo == 0) {
//                        margin = std::stod(token);
//                    } else if (tokenNo == 1) {
//                        
//                        if (margin == 1) points1.push_back(wxPoint2DDouble(i, std::stod(token)));
//                        else if (margin == 0) points2.push_back(wxPoint2DDouble(i, std::stod(token)));
//                    }
//                    tokenNo++;
//                }
//            } catch (std::exception& e) {
//                std::cout<<std::endl<<"Error in line "<<i<<": "<<e.what()<<std::endl;
//            }    
////            if ( i == 1000 ) break; 
//            
//        }
//        file.close();
//    }
//    else std::cout << "Unable to open file '"<<fileName<<"'";
//    
//    wxScatterPlotDataset::ptr dataset1(
//        new wxScatterPlotDataset(
//            wxColor(250, 20, 20, 0x78),
//            wxColor(250, 20, 20, 0xB8),
//            points1)
//        );
//    chartData.AddDataset(dataset1);
//
//    wxScatterPlotDataset::ptr dataset2(
//        new wxScatterPlotDataset(
//            wxColor(20, 20, 20, 0x78),
//            wxColor(20, 20, 20, 0xB8),
//            points2)
//        );
//    chartData.AddDataset(dataset2);
//
//    // Create the scatter plot widget
//    wxScatterPlotCtrl* scatterPlotCtrl = new wxScatterPlotCtrl(panel, wxID_ANY, chartData);
//
//    // Set up the sizer for the panel
//    wxBoxSizer* panelSizer = new wxBoxSizer(wxHORIZONTAL);
//    panelSizer->Add(scatterPlotCtrl, 1, wxEXPAND);
//    panel->SetSizer(panelSizer);
//
//    // Set up the sizer for the frame
//    wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
//    topSizer->Add(panel, 1, wxEXPAND);
//    SetSizerAndFit(topSizer);
    
}

int TSPlotFrame::loadWidgets(){
    
    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
    flexGrid = new wxFlexGridSizer(4, 1, 5, 25);

    wxFlexGridSizer *toolBarContainer = new wxFlexGridSizer(1, 2, 0, 0);
    toolBarContainer->AddGrowableCol(0, 1);
    toolBarContainer->AddGrowableCol(1, 1);
    
    wxFlexGridSizer *toolBar1 = new wxFlexGridSizer(1, 4, 0, 0);
//    toolBar1->AddGrowableCol(6);
    
    wxFlexGridSizer *toolBar2 = new wxFlexGridSizer(1, 4, 0, 0);
//    toolBar2->AddGrowableCol(2);
    
    ///////////////// Tool bar 1 /////////////////////////////////////////////////////////////////
    
    wxButton *addSeries1Btn = new wxButton(panel, ADD_BUTTON_1);
    addSeries1Btn->SetBitmap(wxBitmap("bitmaps/add.bmp",wxBITMAP_DEFAULT_TYPE));
    addSeries1Btn->SetMaxSize(wxSize(35,35));
    
    wxButton *removeSeries1Btn = new wxButton(panel, CLEAR_BUTTON_1);
    removeSeries1Btn->SetBitmap(wxBitmap("bitmaps/remove.bmp",wxBITMAP_DEFAULT_TYPE));
    removeSeries1Btn->SetMaxSize(wxSize(35,35));
    
    wxButton *refreshSeries1Btn = new wxButton(panel, REFRESH_BUTTON_1);
    refreshSeries1Btn->SetBitmap(wxBitmap("bitmaps/refresh.bmp",wxBITMAP_DEFAULT_TYPE));
    refreshSeries1Btn->SetMaxSize(wxSize(35,35));
    
    wxButton *settings1Btn = new wxButton(panel, RENAME_BUTTON_1);
    settings1Btn->SetBitmap(wxBitmap("bitmaps/rename.bmp",wxBITMAP_DEFAULT_TYPE));
    settings1Btn->SetMaxSize(wxSize(35,35));
    
    toolBar1->Add(addSeries1Btn, 0, wxRIGHT , 3);
    toolBar1->Add(removeSeries1Btn, 0, wxRIGHT , 3);
    toolBar1->Add(refreshSeries1Btn, 0, wxRIGHT , 3);
    toolBar1->Add(settings1Btn, 0, wxRIGHT , 6);
    
    ///////////////// Tool bar 2 /////////////////////////////////////////////////////////////////
    
    wxButton *addSeries2Btn = new wxButton(panel, ADD_BUTTON_2);
    addSeries2Btn->SetBitmap(wxBitmap("bitmaps/add.bmp",wxBITMAP_DEFAULT_TYPE));
    addSeries2Btn->SetMaxSize(wxSize(35,35));
    
    wxButton *removeSeries2Btn = new wxButton(panel, CLEAR_BUTTON_2);
    removeSeries2Btn->SetBitmap(wxBitmap("bitmaps/remove.bmp",wxBITMAP_DEFAULT_TYPE));
    removeSeries2Btn->SetMaxSize(wxSize(35,35));
    
    wxButton *refreshSeries2Btn = new wxButton(panel, REFRESH_BUTTON_2);
    refreshSeries2Btn->SetBitmap(wxBitmap("bitmaps/refresh.bmp",wxBITMAP_DEFAULT_TYPE));
    refreshSeries2Btn->SetMaxSize(wxSize(35,35));
    
    wxButton *settings2Btn = new wxButton(panel, RENAME_BUTTON_2);
    settings2Btn->SetBitmap(wxBitmap("bitmaps/rename.bmp",wxBITMAP_DEFAULT_TYPE));
    settings2Btn->SetMaxSize(wxSize(35,35));
    
    toolBar2->Add(addSeries2Btn, 0, wxLEFT , 10);
    toolBar2->Add(removeSeries2Btn, 0, wxLEFT , 3);
    toolBar2->Add(refreshSeries2Btn, 0, wxLEFT , 3);
    toolBar2->Add(settings2Btn, 0, wxRIGHT , 6);
    
    /////////////////////////////////////////////////////////////////////////////////////////////////
    
    toolBarContainer->Add(toolBar1);
    toolBarContainer->Add(toolBar2);
    
    timeSeriesBar = new wxBoxSizer(wxHORIZONTAL);
    timeSeriesBar->Add(lineChartSeries1Ctrl, 1, wxRIGHT | wxBOTTOM | wxEXPAND, 5);
    timeSeriesBar->Add(lineChartSeries2Ctrl, 1, wxLEFT | wxBOTTOM | wxEXPAND, 5);
    
    //////////////////////////// time series window /////////////////////////////////////////////////
    
    seriesSpin1 = new wxSpinCtrl( panel, wxID_ANY );
    seriesSpin1->SetMaxSize(wxSize(60,35));
    seriesSpin2 = new wxSpinCtrl( panel, wxID_ANY );
    seriesSpin2->SetMaxSize(wxSize(60,35));
    
    seriesLable = new wxStaticText(panel, wxID_ANY, "");
    
    refreshBothBtn = new wxButton(panel, REFRESH_BUTTON_3);
    refreshBothBtn->SetBitmap(wxBitmap("bitmaps/refresh.bmp",wxBITMAP_DEFAULT_TYPE));
    refreshBothBtn->SetMaxSize(wxSize(35,35));
    
    timeWindowContainer = new wxFlexGridSizer(1, 5, 0, 0);
    timeWindowContainer->AddGrowableCol(0, 1);
    
    timeWindowContainer->Add(legendCtrl, 1, wxEXPAND | wxRIGHT, 10);
    timeWindowContainer->Add(refreshBothBtn, 1, wxRIGHT, 5);
    timeWindowContainer->Add(seriesSpin1, 1, wxRIGHT, 5);
    timeWindowContainer->Add(seriesSpin2, 1, wxRIGHT);
    timeWindowContainer->Add(seriesLable, 1, wxLEFT, 5);
    
    /////////////////////////////////////////////////////////////////////////////////////////////////
    
    flexGrid->Add(toolBarContainer, 1, wxEXPAND, 15);
    flexGrid->Add(timeSeriesBar, 1, wxEXPAND);
    flexGrid->Add(lineChartCtrl, 1, wxEXPAND);
    flexGrid->Add(timeWindowContainer, 1, wxEXPAND);

    flexGrid->AddGrowableRow(1, 1);
    flexGrid->AddGrowableRow(2, 1);
    flexGrid->AddGrowableCol(0, 1);

    hbox->Add(flexGrid, 1, wxALL | wxEXPAND, 15);
    panel->SetSizer(hbox);
    Centre();
    
    Bind(wxEVT_BUTTON, &TSPlotFrame::addData1, this, ADD_BUTTON_1);
    Bind(wxEVT_BUTTON, &TSPlotFrame::clearData1, this, CLEAR_BUTTON_1);
    Bind(wxEVT_BUTTON, &TSPlotFrame::refreshData1, this, REFRESH_BUTTON_1);
    Bind(wxEVT_BUTTON, &TSPlotFrame::renameData1, this, RENAME_BUTTON_1);
    
    Bind(wxEVT_BUTTON, &TSPlotFrame::addData2, this, ADD_BUTTON_2);
    Bind(wxEVT_BUTTON, &TSPlotFrame::clearData2, this, CLEAR_BUTTON_2);
    Bind(wxEVT_BUTTON, &TSPlotFrame::refreshData2, this, REFRESH_BUTTON_2);
    Bind(wxEVT_BUTTON, &TSPlotFrame::renameData2, this, RENAME_BUTTON_2);
    
    Bind(wxEVT_BUTTON, &TSPlotFrame::refreshBoth, this, REFRESH_BUTTON_3);
    
    return 0;    
}

int TSPlotFrame::loadTimeSeriesData(
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
        wxDefaultSize, wxBORDER_NONE
    );    
    
    wxSize * size;
    size = new wxSize(-1,25);
    // Create the legend widget
    legendCtrl = new ChartLegendBox(
        panel, wxID_ANY, 
        legendData, wxDefaultPosition, 
        *size, wxBORDER_NONE
    );
    
    return 0;
}

int TSPlotFrame::loadTimeSeriesData1(
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
        wxDefaultSize, wxBORDER_NONE
    );
    
    return 0;
}

int TSPlotFrame::loadTimeSeriesData2(
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
        wxDefaultSize, wxBORDER_NONE
    );

    return 0;
}

//void TSPlotFrame::OnExit(wxCommandEvent& event) {
//    Close(true);
//}
//
//void TSPlotFrame::OnAbout(wxCommandEvent& event) {
//    wxMessageBox("This is a wxWidgets Hello World example",
//                 "About Hello World", wxOK | wxICON_INFORMATION);
//}
//
//void TSPlotFrame::OnHello(wxCommandEvent& event) {
//    wxLogMessage("Hello world from wxWidgets!");
//}

void TSPlotFrame::addData1(wxCommandEvent& event) {
    std::cout<<"add new data series...!"<<"\n";
    wxString fileTypes = "*.txt";
    
    wxString filename = wxFileSelector("Choose a file","","","",fileTypes);
    if ( !filename.empty() ) { 
        
        dataset1Path = filename;
        dataset1Name = "Series 1";
        
        std::string line;
        std::ifstream file (filename);
        points1.clear();
        if (file.is_open()) {
            int i = 0;
            while ( getline (file,line) ) {
                try {
                    i++;
                    points1.push_back(std::stod(line)); 
                    if (i == maxPoints) break;
                } catch (std::exception& e) {
                    std::cout<<std::endl<<"Error in line "<<i<<": "<<e.what()<<std::endl;
                }    
            }
            maxPointsS1 = i;
            file.close();
        }
        else std::cout << "Unable to open file '"<<filename<<"'";
        
        int val = 0;
        std::stringstream stringStream;
        labels1.clear();
        int xLableInterval = maxPointsS1/5;
        for(int i = 0; i < maxPointsS1; i+=xLableInterval){
//            stringStream.str(std::string());
//            stringStream << std::fixed << std::setprecision(2) << val;
//            labels.push_back(stringStream.str());
            labels1.push_back(std::to_string(val));
            for (int j = 0; j < (xLableInterval-1); j++) {
                labels1.push_back("");
                val++;
                if (val > maxPointsS1) break;
            }
        }
        
        int min, max;
        if (minPointsS1 < minPointsS2) min = minPointsS1;
        else min = minPointsS2;
        if (maxPointsS1 > maxPointsS2) max = maxPointsS1;
        else max = maxPointsS2;
        
        seriesSpin1->SetRange(min, max-5);
        seriesSpin2->SetRange(min+5, max);
        
        seriesSpin1->SetValue(min);
        seriesSpin2->SetValue(max);
        
        int maxPoints;
        if (maxPointsS1 > maxPointsS2) maxPoints = maxPointsS1;
        else maxPoints = maxPointsS2;
        seriesLable->SetLabel("Data Points: " + std::to_string(maxPoints));    

        lineChartCtrl->Destroy();
        legendCtrl->Destroy();
        timeWindowContainer->Clear(false);
        flexGrid->Detach(timeWindowContainer);
        
        timeSeriesBar->Clear(false);
        lineChartSeries1Ctrl->Destroy();
        
        if (labels1.size() > labels2.size()) labels = labels1;
        else labels = labels2;
        
        loadTimeSeriesData(labels, dataset1Name, points1, dataset2Name, points2);
        loadTimeSeriesData1(labels1, dataset1Name, points1);
        
        timeWindowContainer->Add(legendCtrl, 1, wxEXPAND | wxRIGHT, 10);
        timeWindowContainer->Add(refreshBothBtn, 1, wxRIGHT, 5);
        timeWindowContainer->Add(seriesSpin1, 1, wxRIGHT, 5);
        timeWindowContainer->Add(seriesSpin2, 1, wxRIGHT);
        timeWindowContainer->Add(seriesLable, 1, wxLEFT, 5);

        timeSeriesBar->Add(lineChartSeries1Ctrl, 1, wxRIGHT | wxBOTTOM | wxEXPAND, 5);
        timeSeriesBar->Add(lineChartSeries2Ctrl, 1, wxRIGHT | wxBOTTOM | wxEXPAND, 5);
        flexGrid->Add(lineChartCtrl, 1, wxEXPAND);
        flexGrid->Add(timeWindowContainer, 1, wxEXPAND);
        
        TimeSeries *timeSeries2 = new TimeSeries();
        wxLineChartData chartData2 = timeSeries2->load(labels, dataset1Name, points1, dataset2Name, points2);
//        lineChartCtrl->updateChart(
//            panel, wxID_ANY, 
//            chartData2, wxDefaultPosition, 
//            wxDefaultSize, wxBORDER_NONE
//        );

        panel->Layout();
        panel->Refresh();
        panel->Update();
        
    }   
}

void TSPlotFrame::clearData1(wxCommandEvent& event) {
    std::cout<<"data series cleared"<<"\n";
    
    dataset1Name = "-";
    dataset1Path = "";
    
    minPointsS1 = 0;
    maxPointsS1 = 0;
    
    seriesSpin1->SetRange(minPointsS2, maxPointsS2-5);
    seriesSpin2->SetRange(minPointsS2+5, maxPointsS2);

    seriesSpin1->SetValue(minPointsS2);
    seriesSpin2->SetValue(maxPointsS2);
    
    int maxPoints;
    if (maxPointsS1 > maxPointsS2) maxPoints = maxPointsS1;
    else maxPoints = maxPointsS2;

    seriesLable->SetLabel("Data Points: " + std::to_string(maxPoints));
    
    wxVector<wxString> labels1; 
    points1.clear();
    
    lineChartCtrl->Destroy();
    legendCtrl->Destroy();
    timeWindowContainer->Clear(false);
    flexGrid->Detach(timeWindowContainer);
    
    timeSeriesBar->Clear(false);
    lineChartSeries1Ctrl->Destroy();
    
    loadTimeSeriesData(labels, dataset1Name, points1, dataset2Name, points2);
    loadTimeSeriesData1(labels1, dataset1Name, points1);
    
    timeWindowContainer->Add(legendCtrl, 1, wxEXPAND | wxRIGHT, 10);
    timeWindowContainer->Add(refreshBothBtn, 1, wxRIGHT, 5);
    timeWindowContainer->Add(seriesSpin1, 1, wxRIGHT, 5);
    timeWindowContainer->Add(seriesSpin2, 1, wxRIGHT);
    timeWindowContainer->Add(seriesLable, 1, wxLEFT, 5);
    
    timeSeriesBar->Add(lineChartSeries1Ctrl, 1, wxRIGHT | wxBOTTOM | wxEXPAND, 5);
    timeSeriesBar->Add(lineChartSeries2Ctrl, 1, wxLEFT | wxBOTTOM | wxEXPAND, 5);
    flexGrid->Add(lineChartCtrl, 1, wxEXPAND);
    flexGrid->Add(timeWindowContainer, 1, wxEXPAND);

    panel->Layout();
    panel->Refresh();
    panel->Update();
}

void TSPlotFrame::refreshData1(wxCommandEvent& event) {
    std::cout<<"refresh data series...!"<<"\n";
    
    int min = minPointsS1;
    int max = maxPointsS1;
    if (( dataset1Path.size() > 0) && ((max - min) > 5)) { 
        
        std::string filename = dataset1Path;
        
        std::string line;
        std::ifstream file (filename);
        points1.clear();
        if (file.is_open()) {
            int i = 0;
            while ( getline (file,line) ) {
                try {
                    if (( i >= min) && ( i <= max)) {
                        points1.push_back(std::stod(line));
                    }    
                    i++;
                    if (i == maxPoints) break;
                } catch (std::exception& e) {
                    std::cout<<std::endl<<"Error in line "<<i<<": "<<e.what()<<std::endl;
                }
            }
            maxPointsS1 = i;
            file.close();
        }
        else std::cout << "Unable to open file '"<<filename<<"'";
        
        int val = min;
//        std::stringstream stringStream;
        labels1.clear();
        int xLableInterval = (max-min)/5;
        for(int i = min; i < max; i+=xLableInterval){
//            stringStream.str(std::string());
//            stringStream << std::fixed << std::setprecision(2) << val;
//            labels.push_back(stringStream.str());
            labels1.push_back(std::to_string(val));
            for (int j = 0; j < xLableInterval; j++) {
                labels1.push_back("");
                val++;
                if (val > max) break;
            }
        }
        
        int maxPoints;
        if (maxPointsS1 > maxPointsS2) maxPoints = maxPointsS1;
        else maxPoints = maxPointsS2;
        seriesLable->SetLabel("Data Points: " + std::to_string(maxPoints));
        
        lineChartCtrl->Destroy();
        legendCtrl->Destroy();
        timeWindowContainer->Clear(false);
        flexGrid->Detach(timeWindowContainer);
        
        timeSeriesBar->Clear(false);
        lineChartSeries1Ctrl->Destroy();

        if (labels1.size() > labels2.size()) labels = labels1;
        else labels = labels2;
        
        loadTimeSeriesData(labels, dataset1Name, points1, dataset2Name, points2);
        loadTimeSeriesData1(labels1, dataset1Name, points1);
        
        timeWindowContainer->Add(legendCtrl, 1, wxEXPAND | wxRIGHT, 10);
        timeWindowContainer->Add(refreshBothBtn, 1, wxRIGHT, 5);
        timeWindowContainer->Add(seriesSpin1, 1, wxRIGHT, 5);
        timeWindowContainer->Add(seriesSpin2, 1, wxRIGHT);
        timeWindowContainer->Add(seriesLable, 1, wxLEFT, 5);

        timeSeriesBar->Add(lineChartSeries1Ctrl, 1, wxRIGHT | wxBOTTOM | wxEXPAND, 5);
        timeSeriesBar->Add(lineChartSeries2Ctrl, 1, wxRIGHT | wxBOTTOM | wxEXPAND, 5);
        flexGrid->Add(lineChartCtrl, 1, wxEXPAND);
        flexGrid->Add(timeWindowContainer, 1, wxEXPAND);

        panel->Layout();
        panel->Refresh();
        panel->Update();
        
    }   
}

void TSPlotFrame::renameData1(wxCommandEvent& event) {
    std::cout<<"data series renamed"<<"\n";
    
    wxString seriesName = wxGetTextFromUser("Enter time series name");
    if (!seriesName.IsEmpty()) {
        dataset1Name = seriesName;
        legendCtrl->Destroy();
        timeWindowContainer->Clear(false);
        flexGrid->Detach(timeWindowContainer);
        
        wxVector<wxString> labels;
        wxVector<wxDouble> points1;
        wxVector<wxDouble> points2;
        TimeSeries *timeSeries = new TimeSeries();
        wxLineChartData chartData = timeSeries->load(labels, dataset1Name, points1, dataset2Name, points2);
        wxChartLegendData legendData(chartData.GetDatasets());

        wxSize * size;
        size = new wxSize(-1,25); 
        legendCtrl = new ChartLegendBox(
            panel, wxID_ANY, 
            legendData, wxDefaultPosition, 
            *size, wxBORDER_NONE
        );

        timeWindowContainer->Add(legendCtrl, 1, wxEXPAND | wxRIGHT, 10);
        timeWindowContainer->Add(refreshBothBtn, 1, wxRIGHT, 5);
        timeWindowContainer->Add(seriesSpin1, 1, wxRIGHT, 5);
        timeWindowContainer->Add(seriesSpin2, 1, wxRIGHT);
        timeWindowContainer->Add(seriesLable, 1, wxLEFT, 5);
        
        flexGrid->Add(timeWindowContainer, 1, wxEXPAND);

        panel->Layout();
        panel->Refresh();
        panel->Update();
    }
    
}

void TSPlotFrame::addData2(wxCommandEvent& event) {
    std::cout<<"add new data series...!"<<"\n";
    wxString fileTypes = "*.txt";
    
    wxString filename = wxFileSelector("Choose a file","","","",fileTypes);
    if ( !filename.empty() ) { 
        
        dataset2Path = filename;
        dataset2Name = "Series 2";
        
        std::string line;
        std::ifstream file (filename);
        points2.clear();
        if (file.is_open()) {
            int i = 0;
            while ( getline (file,line) ) {
                try {
                    i++;
                    points2.push_back(std::stod(line));
                    if (i == maxPoints) break;
                } catch (std::exception& e) {
                    std::cout<<std::endl<<"Error in line "<<i<<": "<<e.what()<<std::endl;
                }
            }
            maxPointsS2 = i;
            file.close();
        }
        else std::cout << "Unable to open file '"<<filename<<"'";
        
        int val = 0;
        std::stringstream stringStream;
        labels2.clear();
        int xLableInterval = maxPointsS2/6;
        for(int i = 0; i < maxPointsS2; i+=xLableInterval){
//            stringStream.str(std::string());
//            stringStream << std::fixed << std::setprecision(2) << val;
//            labels2.push_back(stringStream.str());
            labels2.push_back(std::to_string(val));
            for (int j = 0; j < xLableInterval-1; j++) {
                labels2.push_back("");
                val++;
                if (val > maxPointsS2) break;
            }
        }
        
        int min, max;
        if (minPointsS1 < minPointsS2) min = minPointsS1;
        else min = minPointsS2;
        if (maxPointsS1 > maxPointsS2) max = maxPointsS1;
        else max = maxPointsS2;
        
        seriesSpin1->SetRange(min, max-5);
        seriesSpin2->SetRange(min+5, max);
        
        seriesSpin1->SetValue(min);
        seriesSpin2->SetValue(max);
        int maxPoints;
        if (maxPointsS1 > maxPointsS2) maxPoints = maxPointsS1;
        else maxPoints = maxPointsS2;
        seriesLable->SetLabel("Data Points: " + std::to_string(maxPoints));
        
        lineChartCtrl->Destroy();
        legendCtrl->Destroy();
        timeWindowContainer->Clear(false);
        flexGrid->Detach(timeWindowContainer);
        
        timeSeriesBar->Clear(false);
        lineChartSeries2Ctrl->Destroy();

        if (labels1.size() > labels2.size()) labels = labels1;
        else labels = labels2;
        
        loadTimeSeriesData(labels, dataset1Name, points1, dataset2Name, points2);
        loadTimeSeriesData2(labels2, dataset2Name, points2);
        
        timeWindowContainer->Add(legendCtrl, 1, wxEXPAND | wxRIGHT, 10);
        timeWindowContainer->Add(refreshBothBtn, 1, wxRIGHT, 5);
        timeWindowContainer->Add(seriesSpin1, 1, wxRIGHT, 5);
        timeWindowContainer->Add(seriesSpin2, 1, wxRIGHT);
        timeWindowContainer->Add(seriesLable, 1, wxLEFT, 5);

        timeSeriesBar->Add(lineChartSeries1Ctrl, 1, wxRIGHT | wxBOTTOM | wxEXPAND, 5);
        timeSeriesBar->Add(lineChartSeries2Ctrl, 1, wxRIGHT | wxBOTTOM | wxEXPAND, 5);
        flexGrid->Add(lineChartCtrl, 1, wxEXPAND);
        flexGrid->Add(timeWindowContainer, 1, wxEXPAND);

        panel->Layout();
        panel->Refresh();
        panel->Update();
        
    }
    
}

void TSPlotFrame::clearData2(wxCommandEvent& event) {
    std::cout<<"data series cleared"<<"\n";
    
    dataset2Name = "-";
    dataset2Path = "";
    
    minPointsS2 = 0;
    maxPointsS2 = 0;
    
    seriesSpin1->SetRange(minPointsS1, maxPointsS1-5);
    seriesSpin2->SetRange(minPointsS1+5, maxPointsS1);

    seriesSpin1->SetValue(minPointsS1);
    seriesSpin2->SetValue(maxPointsS1);
    
    int maxPoints;
    if (maxPointsS1 > maxPointsS2) maxPoints = maxPointsS1;
    else maxPoints = maxPointsS2;
    seriesLable->SetLabel("Data Points: " + std::to_string(maxPoints));
    
    wxVector<wxString> labels2; 
    points2.clear();
    
    lineChartCtrl->Destroy();
    legendCtrl->Destroy();
    
    timeWindowContainer->Clear(false);
    flexGrid->Detach(timeWindowContainer);
    
    timeSeriesBar->Clear(false);
    lineChartSeries2Ctrl->Destroy();
    
    loadTimeSeriesData(labels, dataset1Name, points1, dataset2Name, points2);
    loadTimeSeriesData2(labels2, dataset2Name, points2);
    
    timeWindowContainer->Add(legendCtrl, 1, wxEXPAND | wxRIGHT, 10);
    timeWindowContainer->Add(refreshBothBtn, 1, wxRIGHT, 5);
    timeWindowContainer->Add(seriesSpin1, 1, wxRIGHT, 5);
    timeWindowContainer->Add(seriesSpin2, 1, wxRIGHT);
    timeWindowContainer->Add(seriesLable, 1, wxLEFT, 5);
    
    timeSeriesBar->Add(lineChartSeries1Ctrl, 1, wxRIGHT | wxBOTTOM | wxEXPAND, 5);
    timeSeriesBar->Add(lineChartSeries2Ctrl, 1, wxLEFT | wxBOTTOM | wxEXPAND, 5);
    flexGrid->Add(lineChartCtrl, 1, wxEXPAND);
    flexGrid->Add(timeWindowContainer, 1, wxEXPAND);

    panel->Layout();
    panel->Refresh();
    panel->Update();
}

void TSPlotFrame::refreshData2(wxCommandEvent& event) {
    std::cout<<"refresh data series...!"<<"\n";
    
    int min = minPointsS2;
    int max = maxPointsS2;
    if ( ( dataset2Path.size() > 0) && ((max - min) > 5) ) { 
        
        std::string filename = dataset2Path;
        std::string line;
        std::ifstream file (filename);
        points2.clear();
        if (file.is_open()) {
            int i = 0;
            while ( getline (file,line) ) {
                try {
                    if (( i >= min) && ( i <= max)) {
                        points2.push_back(std::stod(line));
                    }    
                    i++;
                    if (i == maxPoints) break;
                } catch (std::exception& e) {
                    std::cout<<std::endl<<"Error in line "<<i<<": "<<e.what()<<std::endl;
                }
            }
            maxPointsS2 = i;
            file.close();
        }
        else std::cout << "Unable to open file '"<<filename<<"'";
        
        int val = min;
        labels2.clear();
        int xLableInterval = (max-min)/5;
        for(int i = min; i < max; i+=xLableInterval){
            labels2.push_back(std::to_string(val));
            for (int j = 0; j < xLableInterval; j++) {
                labels2.push_back("");
                val++;
                if (val > max) break;
            }
        }
        
        int maxPoints;
        if (maxPointsS1 > maxPointsS2) maxPoints = maxPointsS1;
        else maxPoints = maxPointsS2;
        seriesLable->SetLabel("Data Points: " + std::to_string(maxPoints));
        
        lineChartCtrl->Destroy();
        legendCtrl->Destroy();
        timeWindowContainer->Clear(false);
        flexGrid->Detach(timeWindowContainer);
        
        timeSeriesBar->Clear(false);
        lineChartSeries2Ctrl->Destroy();

        if (labels1.size() > labels2.size()) labels = labels1;
        else labels = labels2;
        
        loadTimeSeriesData(labels, dataset1Name, points1, dataset2Name, points2);
        loadTimeSeriesData2(labels2, dataset2Name, points2);
        
        timeWindowContainer->Add(legendCtrl, 1, wxEXPAND | wxRIGHT, 10);
        timeWindowContainer->Add(refreshBothBtn, 1, wxRIGHT, 5);
        timeWindowContainer->Add(seriesSpin1, 1, wxRIGHT, 5);
        timeWindowContainer->Add(seriesSpin2, 1, wxRIGHT);
        timeWindowContainer->Add(seriesLable, 1, wxLEFT, 5);

        timeSeriesBar->Add(lineChartSeries1Ctrl, 1, wxRIGHT | wxBOTTOM | wxEXPAND, 5);
        timeSeriesBar->Add(lineChartSeries2Ctrl, 1, wxRIGHT | wxBOTTOM | wxEXPAND, 5);
        flexGrid->Add(lineChartCtrl, 1, wxEXPAND);
        flexGrid->Add(timeWindowContainer, 1, wxEXPAND);

        panel->Layout();
        panel->Refresh();
        panel->Update();
        
    }   
}

void TSPlotFrame::renameData2(wxCommandEvent& event) {
    std::cout<<"data series renamed"<<"\n";
    
    wxString seriesName = wxGetTextFromUser("Enter time series name");
    if (!seriesName.IsEmpty()) {
        dataset2Name = seriesName;
        legendCtrl->Destroy();
        timeWindowContainer->Clear(false);
        flexGrid->Detach(timeWindowContainer);
        
        wxVector<wxString> labels;
        wxVector<wxDouble> points1;
        wxVector<wxDouble> points2;
        TimeSeries *timeSeries = new TimeSeries();
        wxLineChartData chartData = timeSeries->load(labels, dataset1Name, points1, dataset2Name, points2);
        wxChartLegendData legendData(chartData.GetDatasets());

        wxSize * size;
        size = new wxSize(-1,25); 
        legendCtrl = new ChartLegendBox(
            panel, wxID_ANY, 
            legendData, wxDefaultPosition, 
            *size, wxBORDER_NONE
        );

        timeWindowContainer->Add(legendCtrl, 1, wxEXPAND | wxRIGHT, 10);
        timeWindowContainer->Add(refreshBothBtn, 1, wxRIGHT, 5);
        timeWindowContainer->Add(seriesSpin1, 1, wxRIGHT, 5);
        timeWindowContainer->Add(seriesSpin2, 1, wxRIGHT);
        timeWindowContainer->Add(seriesLable, 1, wxLEFT, 5);
        
        flexGrid->Add(timeWindowContainer, 1, wxEXPAND);

        panel->Layout();
        panel->Refresh();
        panel->Update();
    }
    
}

void TSPlotFrame::refreshBoth(wxCommandEvent& event) {
    std::cout<<"refresh data series...!"<<"\n";
    
    int min = seriesSpin1->GetValue();
    int max = seriesSpin2->GetValue();;
    if ( ( dataset2Path.size() > 0) && ((max - min) > 5) ) { 
        
        std::string filename = dataset2Path;
        std::string line;
        std::ifstream file (filename);
        points2.clear();
        if (file.is_open()) {
            int i = 0;
            while ( getline (file,line) ) {
                try {
                    if (( i >= min) && ( i <= max)) {
                        points2.push_back(std::stod(line));
                    }    
                    i++;
                    if (i == maxPoints) break;
                } catch (std::exception& e) {
                    std::cout<<std::endl<<"Error in line "<<i<<": "<<e.what()<<std::endl;
                }
            }
            maxPointsS2 = i;
            file.close();
        }
        else std::cout << "Unable to open file '"<<filename<<"'";
        
        filename = dataset1Path;
        std::ifstream file2 (filename);
        points1.clear();
        if (file2.is_open()) {
            int i = 0;
            while ( getline (file2,line) ) {
                try {
                    if (( i >= min) && ( i <= max)) {
                        points1.push_back(std::stod(line));
                    }    
                    i++;
                    if (i == maxPoints) break;
                } catch (std::exception& e) {
                    std::cout<<std::endl<<"Error in line "<<i<<": "<<e.what()<<std::endl;
                }
            }
            maxPointsS1 = i;
            file2.close();
        }
        else std::cout << "Unable to open file '"<<filename<<"'";
        
        int val = min;
        labels2.clear();
        int xLableInterval = (max-min)/5;
        for(int i = min; i < max; i+=xLableInterval){
            labels2.push_back(std::to_string(val));
            for (int j = 0; j < xLableInterval; j++) {
                labels2.push_back("");
                val++;
                if (val > max) break;
            }
        }
        
        seriesLable->SetLabel("Data Points: " + std::to_string(max-min));
        
        lineChartCtrl->Destroy();
        legendCtrl->Destroy();
        timeWindowContainer->Clear(false);
        flexGrid->Detach(timeWindowContainer);
        
        timeSeriesBar->Clear(false);
        lineChartSeries2Ctrl->Destroy();

        loadTimeSeriesData(labels2, dataset1Name, points1, dataset2Name, points2);
        loadTimeSeriesData2(labels2, dataset2Name, points2);
        loadTimeSeriesData1(labels2, dataset2Name, points1);
        
        timeWindowContainer->Add(legendCtrl, 1, wxEXPAND | wxRIGHT, 10);
        timeWindowContainer->Add(refreshBothBtn, 1, wxRIGHT, 5);
        timeWindowContainer->Add(seriesSpin1, 1, wxRIGHT, 5);
        timeWindowContainer->Add(seriesSpin2, 1, wxRIGHT);
        timeWindowContainer->Add(seriesLable, 1, wxLEFT, 5);

        timeSeriesBar->Add(lineChartSeries1Ctrl, 1, wxRIGHT | wxBOTTOM | wxEXPAND, 5);
        timeSeriesBar->Add(lineChartSeries2Ctrl, 1, wxRIGHT | wxBOTTOM | wxEXPAND, 5);
        flexGrid->Add(lineChartCtrl, 1, wxEXPAND);
        flexGrid->Add(timeWindowContainer, 1, wxEXPAND);

        panel->Layout();
        panel->Refresh();
        panel->Update();
        
    }   
}

wxBEGIN_EVENT_TABLE(TSPlotFrame, wxFrame)
    EVT_BUTTON(ADD_BUTTON_1, TSPlotFrame::addData1)    
    EVT_BUTTON(CLEAR_BUTTON_1, TSPlotFrame::clearData1)
    EVT_BUTTON(REFRESH_BUTTON_1, TSPlotFrame::refreshData1)
    EVT_BUTTON(RENAME_BUTTON_1, TSPlotFrame::renameData1)    
    EVT_BUTTON(ADD_BUTTON_2, TSPlotFrame::addData2)    
    EVT_BUTTON(CLEAR_BUTTON_2, TSPlotFrame::clearData2)    
    EVT_BUTTON(REFRESH_BUTTON_2, TSPlotFrame::refreshData2)   
    EVT_BUTTON(RENAME_BUTTON_2, TSPlotFrame::renameData2)
    EVT_BUTTON(REFRESH_BUTTON_3, TSPlotFrame::refreshBoth)    
wxEND_EVENT_TABLE()
