/*
    Copyright (c) 2016-2018 Xavier Leclercq

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

/*
    Part of this file were copied from the Chart.js project (http://chartjs.org/)
    and translated into C++.

    The files of the Chart.js project have the following copyright and license.

    Copyright (c) 2013-2016 Nick Downie
    Released under the MIT license
    https://github.com/nnnick/Chart.js/blob/master/LICENSE.md
*/

#include "wxstackedcolumnchart.h"
#include "wxchartcategoricalaxis.h"
#include "wxchartnumericalaxis.h"
#include <sstream>

wxStackedColumnChart::Column::Column(wxDouble value,
                                     const wxChartTooltipProvider::ptr tooltipProvider,
                                     wxDouble x,
                                     wxDouble y,
                                     const wxColor &fillColor,
                                     const wxColor &strokeColor,
                                     int directions)
    : wxChartRectangle(x, y, tooltipProvider, wxChartRectangleOptions(fillColor, strokeColor, directions)),
    m_value(value)
{
}

bool wxStackedColumnChart::Column::HitTest(const wxPoint &point) const
{
    return ((point.x >= GetPosition().m_x) &&
        (point.x <= (GetPosition().m_x + GetWidth())));
}

wxDouble wxStackedColumnChart::Column::GetValue() const
{
    return m_value;
}

wxStackedColumnChart::Dataset::Dataset()
{
}

const wxVector<wxStackedColumnChart::Column::ptr>& wxStackedColumnChart::Dataset::GetColumns() const
{
    return m_columns;
}

void wxStackedColumnChart::Dataset::AppendColumn(Column::ptr column)
{
    m_columns.push_back(column);
}

wxStackedColumnChart::wxStackedColumnChart(const wxChartsCategoricalData &data,
                                           const wxSize &size)
    : m_grid(
        wxPoint2DDouble(m_options.GetPadding().GetLeft(), m_options.GetPadding().GetRight()),
        size,
        wxChartCategoricalAxis::make_shared("x", data.GetLabels(), m_options.GetGridOptions().GetXAxisOptions()),
        wxChartNumericalAxis::make_shared("y", GetCumulativeMinValue(data.GetDatasets()), GetCumulativeMaxValue(data.GetDatasets()), m_options.GetGridOptions().GetYAxisOptions()),
        m_options.GetGridOptions()
        )
{
    const wxVector<wxChartsDoubleDataset::ptr>& datasets = data.GetDatasets();
    for (size_t i = 0; i < datasets.size(); ++i)
    {
        const wxChartsDoubleDataset& dataset = *datasets[i];
        Dataset::ptr newDataset(new Dataset());

        int border = wxLEFT | wxRIGHT;
        if (i == (datasets.size() - 1))
        {
            border |= wxTOP;
        }

        const wxVector<wxDouble>& datasetData = dataset.GetData();
        for (size_t j = 0; j < datasetData.size(); ++j)
        {
            std::stringstream tooltip;
            tooltip << datasetData[j];
            wxChartTooltipProvider::ptr tooltipProvider(
                new wxChartTooltipProviderStatic(data.GetLabels()[j], tooltip.str(), dataset.GetFillColor())
                );

            newDataset->AppendColumn(Column::ptr(new Column(
                datasetData[j],
                tooltipProvider,
                25, 50,
                dataset.GetFillColor(), dataset.GetStrokeColor(),
                border
                )));
        }

        m_datasets.push_back(newDataset);
    }
}

const wxChartCommonOptions& wxStackedColumnChart::GetCommonOptions() const
{
    return m_options.GetCommonOptions();
}

wxDouble wxStackedColumnChart::GetCumulativeMinValue(const wxVector<wxChartsDoubleDataset::ptr>& datasets)
{
    wxDouble result = 0;

    size_t i = 0;
    while (true)
    {
        wxDouble sum = 0;
        bool stop = true;
        for (size_t j = 0; j < datasets.size(); ++j)
        {
            const wxChartsDoubleDataset& dataset = *datasets[j];
            if (i < dataset.GetData().size())
            {
                sum += dataset.GetData()[i];
                stop = false;
            }
        }
        if (sum < result)
        {
            result = sum;
        }
        if (stop)
        {
            break;
        }
        ++i;
    }

    return result;
}

wxDouble wxStackedColumnChart::GetCumulativeMaxValue(const wxVector<wxChartsDoubleDataset::ptr>& datasets)
{
    wxDouble result = 0;

    size_t i = 0;
    while (true)
    {
        wxDouble sum = 0;
        bool stop = true;
        for (size_t j = 0; j < datasets.size(); ++j)
        {
            const wxChartsDoubleDataset& dataset = *datasets[j];
            if (i < dataset.GetData().size())
            {
                sum += dataset.GetData()[i];
                stop = false;
            }
        }
        if (sum > result)
        {
            result = sum;
        }
        if (stop)
        {
            break;
        }
        ++i;
    }

    return result;
}

void wxStackedColumnChart::DoSetSize(const wxSize &size)
{
    m_grid.Resize(size);
}

void wxStackedColumnChart::DoFit()
{
    wxVector<wxDouble> heightOfPreviousDatasets;
    for (size_t i = 0; i < m_datasets[0]->GetColumns().size(); ++i)
    {
        heightOfPreviousDatasets.push_back(0);
    }

    for (size_t i = 0; i < m_datasets.size(); ++i)
    {
        Dataset& currentDataset = *m_datasets[i];
        for (size_t j = 0; j < currentDataset.GetColumns().size(); ++j)
        {
            Column& column = *(currentDataset.GetColumns()[j]);

            wxPoint2DDouble upperLeftCornerPosition = m_grid.GetMapping().GetWindowPositionAtTickMark(j, column.GetValue());
            upperLeftCornerPosition.m_x += m_options.GetColumnSpacing();
            upperLeftCornerPosition.m_y -= heightOfPreviousDatasets[j];
            wxPoint2DDouble upperRightCornerPosition = m_grid.GetMapping().GetWindowPositionAtTickMark(j + 1, column.GetValue());
            upperRightCornerPosition.m_x -= m_options.GetColumnSpacing();
            upperRightCornerPosition.m_y -= heightOfPreviousDatasets[j];

            wxPoint2DDouble bottomLeftCornerPosition = m_grid.GetMapping().GetXAxis().GetTickMarkPosition(j);

            column.SetPosition(upperLeftCornerPosition);
            column.SetSize(upperRightCornerPosition.m_x - upperLeftCornerPosition.m_x,
                (bottomLeftCornerPosition.m_y - heightOfPreviousDatasets[j]) - upperLeftCornerPosition.m_y);

            heightOfPreviousDatasets[j] = bottomLeftCornerPosition.m_y - upperLeftCornerPosition.m_y;
        }
    }
}

void wxStackedColumnChart::DoDraw(wxGraphicsContext &gc,
                                  bool suppressTooltips)
{
    m_grid.Fit(gc);
    m_grid.Draw(gc);

    Fit();

    for (size_t i = 0; i < m_datasets.size(); ++i)
    {
        Dataset& currentDataset = *m_datasets[i];
        for (size_t j = 0; j < currentDataset.GetColumns().size(); ++j)
        {
            currentDataset.GetColumns()[j]->Draw(gc);
        }
    }

    if (!suppressTooltips)
    {
        DrawTooltips(gc);
    }
}

wxSharedPtr<wxVector<const wxChartElement*> > wxStackedColumnChart::GetActiveElements(const wxPoint &point)
{
    wxSharedPtr<wxVector<const wxChartElement*> > activeElements(new wxVector<const wxChartElement*>());

    // Dataset are iterated in reverse order so that the tooltip items
    // are in the same order as the stacked columns
    for (int i = m_datasets.size() - 1; i >= 0; --i)
    {
        const wxVector<Column::ptr>& columns = m_datasets[i]->GetColumns();
        for (size_t j = 0; j < columns.size(); ++j)
        {
            if (columns[j]->HitTest(point))
            {
                activeElements->push_back(columns[j].get());
            }
        }
    }

    return activeElements;
}
