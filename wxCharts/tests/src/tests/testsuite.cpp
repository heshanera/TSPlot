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

#include "testsuite.h"
#include "wxchartbackgroundoptionstests.h"
#include "wxchartfontoptionstests.h"
#include "wxchartlabeloptionstests.h"
#include "wxchartaxisoptionstests.h"
#include "wxchartgridoptionstests.h"
#include "wxcolumnchartoptionstests.h"
#include "wxpiechartoptionstests.h"
#include <cppunit/CompilerOutputter.h>

TestSuite::TestSuite()
{
    m_controller.addListener(&m_result);
    m_runner.addTest(wxChartBackgroundOptionsTests::suite());
    m_runner.addTest(wxChartFontOptionsTests::suite());
    m_runner.addTest(wxChartLabelOptionsTests::suite());
    m_runner.addTest(wxChartAxisOptionsTests::suite());
    m_runner.addTest(wxChartGridOptionsTests::suite());
    m_runner.addTest(wxColumnChartOptionsTests::suite());
    m_runner.addTest(wxPieChartOptionsTests::suite());
}

void TestSuite::run()
{
    m_runner.run(m_controller);

    CppUnit::CompilerOutputter outputter(&m_result, std::cout);
    outputter.write();
}
