/*
    Copyright (c) 2018 Xavier Leclercq

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#include "wxchartstestsframe.h"
#include "wxchartstestsmenubar.h"
#include "wxchartstestswindowids.h"
#include "wxchartrectanglepanel.h"
#include "wxchartlabelseriespanel.h"
#include "wxchartcategoricalaxispanel.h"
#include "wxchartnumericalaxispanel.h"
#include "wxchartgridpanel.h"
#include "wxareachartpanel.h"
#include "wxbarchartpanel.h"
#include "wxbubblechartpanel.h"
#include "wxcandlestickchartpanel.h"
#include "wxcolumnchartpanel.h"
#include "wxpiechartpanel.h"
#include "wxpolarareachartpanel.h"
#include "tests/testsuite.h"
#include <wx/sizer.h>
#include <wx/splitter.h>

wxChartsTestsFrame::wxChartsTestsFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(1280, 720)), 
    m_currentPanel(0),
    m_chartRectanglePanel(0), m_chartGridPanel(0),
    m_chartCategoricalAxisPanel(0), m_chartNumericalAxisPanel(0),
    m_columnChartPanel(0), m_pieChartPanel(0)
{
    SetMenuBar(new wxChartsTestsMenuBar());

    wxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    wxSplitterWindow* splitterWindow = new wxSplitterWindow(this, wxID_ANY);
    splitterWindow->SetMinimumPaneSize(50);

    m_mainPanel = new wxPanel(splitterWindow);

    wxSizer* mainPanelSizer = new wxBoxSizer(wxVERTICAL);
    m_mainPanel->SetSizer(mainPanelSizer);

    m_chartRectanglePanel = new wxChartRectanglePanel(m_mainPanel);
    mainPanelSizer->Add(m_chartRectanglePanel, 1, wxEXPAND);
    m_chartRectanglePanel->Hide();

    m_chartLabelPanel = new wxChartLabelSeriesPanel(m_mainPanel);
    mainPanelSizer->Add(m_chartLabelPanel, 1, wxEXPAND);
    m_chartLabelPanel->Hide();

    m_chartCategoricalAxisPanel = new wxChartCategoricalAxisPanel(m_mainPanel);
    mainPanelSizer->Add(m_chartCategoricalAxisPanel, 1, wxEXPAND);
    m_chartCategoricalAxisPanel->Hide();

    m_chartNumericalAxisPanel = new wxChartNumericalAxisPanel(m_mainPanel);
    mainPanelSizer->Add(m_chartNumericalAxisPanel, 1, wxEXPAND);
    m_chartNumericalAxisPanel->Hide();

    m_chartGridPanel = new wxChartGridPanel(m_mainPanel);
    mainPanelSizer->Add(m_chartGridPanel, 1, wxEXPAND);
    m_chartGridPanel->Hide();

    m_areaChartPanel = new wxAreaChartPanel(m_mainPanel);
    mainPanelSizer->Add(m_areaChartPanel, 1, wxEXPAND);
    m_areaChartPanel->Hide();

    m_barChartPanel = new wxBarChartPanel(m_mainPanel);
    mainPanelSizer->Add(m_barChartPanel, 1, wxEXPAND);
    m_barChartPanel->Hide();

    m_bubbleChartPanel = new wxBubbleChartPanel(m_mainPanel);
    mainPanelSizer->Add(m_bubbleChartPanel, 1, wxEXPAND);
    m_bubbleChartPanel->Hide();

    m_candlestickChartPanel = new wxCandlestickChartPanel(m_mainPanel);
    mainPanelSizer->Add(m_candlestickChartPanel, 1, wxEXPAND);
    m_candlestickChartPanel->Hide();

    m_columnChartPanel = new wxColumnChartPanel(m_mainPanel);
    mainPanelSizer->Add(m_columnChartPanel, 1, wxEXPAND);
    m_columnChartPanel->Hide();

    m_pieChartPanel = new wxPieChartPanel(m_mainPanel);
    mainPanelSizer->Add(m_pieChartPanel, 1, wxEXPAND);
    m_pieChartPanel->Hide();

    m_polarAreaChartPanel = new wxPolarAreaChartPanel(m_mainPanel);
    mainPanelSizer->Add(m_polarAreaChartPanel, 1, wxEXPAND);
    m_polarAreaChartPanel->Hide();

    wxPanel* outputPanel = new wxPanel(splitterWindow);
    wxSizer* outputPanelSizer = new wxBoxSizer(wxVERTICAL);
    outputPanel->SetSizer(outputPanelSizer);

    m_output = new wxTextCtrl(outputPanel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    outputPanelSizer->Add(m_output, 1, wxEXPAND);

    splitterWindow->SplitHorizontally(m_mainPanel, outputPanel);
    sizer->Add(splitterWindow, 1, wxEXPAND);

    m_currentPanel = m_columnChartPanel;
    m_currentPanel->Show();

    SetSizer(sizer);
}

void wxChartsTestsFrame::OnExit(wxCommandEvent& evt)
{
    Close();
}

void wxChartsTestsFrame::OnChartRectangleElement(wxCommandEvent& evt)
{
    SwitchPanel(m_chartRectanglePanel);
}

void wxChartsTestsFrame::OnChartLabelElement(wxCommandEvent& evt)
{
    SwitchPanel(m_chartLabelPanel);
}

void wxChartsTestsFrame::OnChartCategoricalAxisElement(wxCommandEvent& evt)
{
    SwitchPanel(m_chartCategoricalAxisPanel);
}

void wxChartsTestsFrame::OnChartNumericalAxisElement(wxCommandEvent& evt)
{
    SwitchPanel(m_chartNumericalAxisPanel);
}

void wxChartsTestsFrame::OnChartGridElement(wxCommandEvent& evt)
{
    SwitchPanel(m_chartGridPanel);
}

void wxChartsTestsFrame::OnAreaChart(wxCommandEvent& evt)
{
    SwitchPanel(m_areaChartPanel);
}

void wxChartsTestsFrame::OnBarChart(wxCommandEvent& evt)
{
    SwitchPanel(m_barChartPanel);
}

void wxChartsTestsFrame::OnBubbleChart(wxCommandEvent& evt)
{
    SwitchPanel(m_bubbleChartPanel);
}

void wxChartsTestsFrame::OnCandlestickChart(wxCommandEvent& evt)
{
    SwitchPanel(m_candlestickChartPanel);
}

void wxChartsTestsFrame::OnColumnChart(wxCommandEvent& evt)
{
    SwitchPanel(m_columnChartPanel);
}

void wxChartsTestsFrame::OnPieChart(wxCommandEvent& evt)
{
    SwitchPanel(m_pieChartPanel);
}

void wxChartsTestsFrame::OnPolarAreaChart(wxCommandEvent& evt)
{
    SwitchPanel(m_polarAreaChartPanel);
}

void wxChartsTestsFrame::OnRunAllTests(wxCommandEvent& evt)
{
    wxStreamToTextRedirector redirect(m_output);

    TestSuite tests;
    tests.run();
}

void wxChartsTestsFrame::SwitchPanel(wxPanel* newPanel)
{
    m_currentPanel->Hide();
    m_currentPanel = newPanel;
    m_currentPanel->Show();
    m_mainPanel->Layout();
}

wxBEGIN_EVENT_TABLE(wxChartsTestsFrame, wxFrame)
    EVT_MENU(wxID_EXIT, wxChartsTestsFrame::OnExit)
    EVT_MENU(wxID_RECTANGLE_ELEMENT, wxChartsTestsFrame::OnChartRectangleElement)
    EVT_MENU(wxID_LABEL_ELEMENT, wxChartsTestsFrame::OnChartLabelElement)
    EVT_MENU(wxID_CATEGORICALAXIS_ELEMENT, wxChartsTestsFrame::OnChartCategoricalAxisElement)
    EVT_MENU(wxID_NUMERICALAXIS_ELEMENT, wxChartsTestsFrame::OnChartNumericalAxisElement)
    EVT_MENU(wxID_GRID_ELEMENT, wxChartsTestsFrame::OnChartGridElement)
    EVT_MENU(wxID_AREA_CHART, wxChartsTestsFrame::OnAreaChart)
    EVT_MENU(wxID_BAR_CHART, wxChartsTestsFrame::OnBarChart)
    EVT_MENU(wxID_BUBBLE_CHART, wxChartsTestsFrame::OnBubbleChart)
    EVT_MENU(wxID_CANDLESTICK_CHART, wxChartsTestsFrame::OnCandlestickChart)
    EVT_MENU(wxID_COLUMN_CHART, wxChartsTestsFrame::OnColumnChart)
    EVT_MENU(wxID_PIE_CHART, wxChartsTestsFrame::OnPieChart)
    EVT_MENU(wxID_POLARAREA_CHART, wxChartsTestsFrame::OnPolarAreaChart)
    EVT_MENU(wxID_ALL_TESTS, wxChartsTestsFrame::OnRunAllTests)
wxEND_EVENT_TABLE()
