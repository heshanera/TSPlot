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

#include "wxdoughnutchart.h"

wxDoughnutChartData::wxDoughnutChartData()
{
}

const wxVector<wxChartSliceData>& wxDoughnutChartData::GetSlices() const
{
    return m_value;
}

void wxDoughnutChartData::AppendSlice(const wxChartSliceData &slice)
{
    m_value.push_back(slice);
    Notify();
}

void wxDoughnutChartData::UpdateSlices(const wxVector<wxChartSliceData> &slices)
{
    SetValue(slices);
}

void wxDoughnutChartData::AddSlices(const wxVector<wxChartSliceData> &slices)
{
    for(const auto &slice : slices)
        m_value.push_back(slice);

    Notify();
}

wxDoughnutChart::wxDoughnutChart(const wxDoughnutChartData &data,
                                 const wxSize &size)
{
    Initialize(data, size);
}

wxDoughnutChart::wxDoughnutChart(const wxDoughnutChartData &data,
                                 const wxDougnutChartOptions &options,
                                 const wxSize &size)
    : m_options(options)
{
    Initialize(data, size);
}

const wxChartCommonOptions& wxDoughnutChart::GetCommonOptions() const
{
    return m_options.GetCommonOptions();
}

void wxDoughnutChart::Initialize(const wxDoughnutChartData &data,
                                 const wxSize &size)
{
    const wxVector<wxChartSliceData>& slices = data.GetSlices();
    for (size_t i = 0; i < slices.size(); ++i)
    {
        Add(slices[i], size);
    }
}

const wxDoughnutAndPieChartOptionsBase& wxDoughnutChart::GetOptions() const
{
    return m_options;
}
