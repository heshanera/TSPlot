/* 
 * File:   containerBox.h
 * Author: heshan
 *
 * Created on April 4, 2018, 12:55 PM
 */

#ifndef CHARTLEGENDBOX_H
#define CHARTLEGENDBOX_H

#include <wx/control.h>
#include <wx/charts/wxcharts.h>

class ChartLegendBox : public wxControl
{
public:
    
    ChartLegendBox(wxWindow *parent, wxWindowID id,
        const wxChartLegendData &data,
        const wxPoint &pos = wxDefaultPosition,
        const wxSize &size = wxDefaultSize,
        long style = 0
    );

private:
    void OnPaint(wxPaintEvent &evt);

private:
    wxChartLegendOptions m_options;
    wxVector<wxChartLegendLine> m_lines;

    DECLARE_EVENT_TABLE();

};

#endif /* CHARTLEGENDBOX_H */

