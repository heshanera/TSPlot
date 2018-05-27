/* 
 * File:   TimeSeriesCtrl.cpp
 * Author: heshan
 * 
 * Created on May 9, 2018, 3:13 PM
 */

#include "TimeSeriesCtrl.h"
#include <wx/filedlg.h>
#include <iostream>

TimeSeriesCtrl::TimeSeriesCtrl(wxWindow *parent,
                                 wxWindowID id,
                                 const wxLineChartData &data,
                                 const wxPoint &pos,
                                 const wxSize &size,
                                 long style)
    : wxChartCtrl(parent, id, pos, size, style),
    m_lineChart(data, size)
{
    CreateContextMenu();
}

TimeSeriesCtrl::TimeSeriesCtrl(wxWindow *parent,
                                 wxWindowID id,
                                 const wxLineChartData &data,
                                 const wxLineChartOptions &options,
                                 const wxPoint &pos,
                                 const wxSize &size,
                                 long style)
    : wxChartCtrl(parent, id, pos, size, style),
    m_lineChart(data, size)
{
    CreateContextMenu();
}

wxLineChart& TimeSeriesCtrl::GetChart()
{
    return m_lineChart;
}

void TimeSeriesCtrl::CreateContextMenu()
{
    m_contextMenu.Append(wxID_SAVEAS, wxString("Save as"));

    Bind(wxEVT_CONTEXT_MENU, 
        [this](wxContextMenuEvent& evt) 
        {
            PopupMenu(&m_contextMenu, ScreenToClient(evt.GetPosition()));
        }
        );

    m_contextMenu.Bind(wxEVT_MENU,
        [this](wxCommandEvent &)
        {
            wxFileDialog saveFileDialog(this, _("Save file"), "", "",
                "JPEG files (*.jpg;*.jpeg)|*.jpg;*.jpeg|PNG files (*.png)|*.png",
                wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
            if (saveFileDialog.ShowModal() == wxID_CANCEL)
                return;

            wxString filename = saveFileDialog.GetPath();

            wxBitmapType type = wxBitmapType::wxBITMAP_TYPE_INVALID;
            switch (saveFileDialog.GetFilterIndex())
            {
            case 0:
                type = wxBitmapType::wxBITMAP_TYPE_JPEG;
                if (wxImage::FindHandler(wxBitmapType::wxBITMAP_TYPE_JPEG) == 0)
                {
                    wxImage::AddHandler(new wxJPEGHandler());
                }
                break;

            case 1:
                type = wxBitmapType::wxBITMAP_TYPE_PNG;
                if (wxImage::FindHandler(wxBitmapType::wxBITMAP_TYPE_PNG) == 0)
                {
                    wxImage::AddHandler(new wxPNGHandler());
                }
                break;
            }
            
            m_lineChart.Save(filename, type, GetSize());
        },
        wxID_SAVEAS
        );
}

int TimeSeriesCtrl::updateChart(wxWindow *parent,
                                 wxWindowID id,
                                 const wxLineChartData &data,
                                 const wxLineChartOptions &options,
                                 const wxPoint &pos,
                                 const wxSize &size,
                                 long style)
{
    std::cout<<"chart updated...!";
    //CreateContextMenu();
    return 0;
}

