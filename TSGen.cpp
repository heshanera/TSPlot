/* 
 * File:   TSGen.cpp
 * Author: heshan
 * 
 * Created on April 1, 2018, 9:33 PM
 */

#include "TSGen.h"
#include "TimeSeries.h"

bool TSGen::OnInit()
{
    TSGenFrame *frame = new TSGenFrame();
    frame->Show(true);
    return true;
}