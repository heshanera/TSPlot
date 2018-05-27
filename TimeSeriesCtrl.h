/* 
 * File:   TimeSeriesCtrl.h
 * Author: heshan
 *
 * Created on May 9, 2018, 3:13 PM
 */

#ifndef TIMESERIESCTRL_H
#define TIMESERIESCTRL_H

#include <wx/charts/wxchartctrl.h>
#include <wx/charts/wxlinechart.h>
#include <wx/menu.h>

class TimeSeriesCtrl : public wxChartCtrl {
public:
    
    /// Constructs a wxLineChartCtrl control.
    /// @param parent Pointer to a parent window.
    /// @param id Control identifier. If wxID_ANY, will automatically
    /// create an identifier.
    /// @param data The data that will be used to initialize the chart.
    /// @param pos Control position. wxDefaultPosition indicates that
    /// wxWidgets should generate a default position for the control.
    /// @param size Control size. wxDefaultSize indicates that wxWidgets
    /// should generate a default size for the window. If no suitable
    /// size can  be found, the window will be sized to 20x20 pixels
    /// so that the window is visible but obviously not correctly sized.
    /// @param style Control style. For generic window styles, please
    /// see wxWindow.
    TimeSeriesCtrl(wxWindow *parent, wxWindowID id, const wxLineChartData &data,
        const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize,
        long style = 0);
    
    /// Constructs a wxLineChartCtrl control.
    /// @param parent Pointer to a parent window.
    /// @param id Control identifier. If wxID_ANY, will automatically
    /// create an identifier.
    /// @param data The data that will be used to initialize the chart.
    /// @param options The settings to be used for this chart.
    /// @param pos Control position. wxDefaultPosition indicates that
    /// wxWidgets should generate a default position for the control.
    /// @param size Control size. wxDefaultSize indicates that wxWidgets
    /// should generate a default size for the window. If no suitable
    /// size can  be found, the window will be sized to 20x20 pixels
    /// so that the window is visible but obviously not correctly sized.
    /// @param style Control style. For generic window styles, please
    /// see wxWindow.
    TimeSeriesCtrl(wxWindow *parent, wxWindowID id, const wxLineChartData &data,
        const wxLineChartOptions &options, const wxPoint &pos = wxDefaultPosition,
        const wxSize &size = wxDefaultSize, long style = 0);
    
    int updateChart(wxWindow *parent, wxWindowID id, const wxLineChartData &data,
        const wxLineChartOptions &options, const wxPoint &pos = wxDefaultPosition,
        const wxSize &size = wxDefaultSize, long style = 0);
    
private:
    virtual wxLineChart& GetChart();

    void CreateContextMenu();
    
private:
    wxLineChart m_lineChart;
    wxMenu m_contextMenu;

};

#endif /* TIMESERIESCTRL_H */



