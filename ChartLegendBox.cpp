/* 
 * File:   containerBox.cpp
 * Author: heshan
 * 
 * Created on April 4, 2018, 12:55 PM
 */

#include "ChartLegendBox.h"
#include <wx/dcbuffer.h>
#include <wx/graphics.h>

ChartLegendBox::ChartLegendBox(wxWindow *parent,
                                     wxWindowID id,
                                     const wxChartLegendData &data,
                                     const wxPoint &pos,
                                     const wxSize &size,
                                     long style)
    : wxControl(parent, id, pos, size, style)
{
    
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    SetBackgroundColour(*wxWHITE);

    const wxVector<wxChartLegendItem>& items = data.GetItems();
    for (size_t i = 0; i < items.size(); ++i)
    {
        m_lines.push_back(
            wxChartLegendLine(
                items[i].GetColor(), 
                items[i].GetLabel(), 
                m_options.GetLegendLineOptions()
            )
        );
    }
    
    parent->GetWindowBorderSize();
    
}

void ChartLegendBox::OnPaint(wxPaintEvent &evt)
{
    wxAutoBufferedPaintDC dc(this);

    dc.Clear();

    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
    if (gc)
    {
        // Update the size of each line to reflect
        // the currently selected options and the
        // contents of each line.
        for (size_t i = 0; i < m_lines.size(); ++i)
        {
            m_lines[i].UpdateSize(*gc);
        }

        // Set the position of each line based on
        // the size of the lines that precede it.
        wxDouble x = 1;
        wxDouble x2 = 1;
        for (size_t i = 0; i < m_lines.size(); ++i)
        {
            m_lines[i].SetPosition(x, 5);
//            x = (m_lines[i].GetSize().GetHeight() + 5) + m_lines[1].GetSize().GetWidth() + 10;
            x = (m_lines[i].GetSize().GetHeight() + 5) + m_lines[0].GetSize().GetWidth() + 10;
//            if (x2 > x) x = x2;
        }

        // Draw the lines
        for (size_t i = 0; i < m_lines.size(); ++i)
        {
            m_lines[i].Draw(*gc);
        }

        delete gc;
    }
}

BEGIN_EVENT_TABLE(ChartLegendBox, wxControl)
    EVT_PAINT(ChartLegendBox::OnPaint)
END_EVENT_TABLE()

