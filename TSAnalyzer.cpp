/* 
 * File:   TSGen.cpp
 * Author: heshan
 * 
 * Created on April 1, 2018, 9:33 PM
 */

#include "TSAnalyzer.h"
#include "TimeSeries.h"

bool TSGen::OnInit() {
    TSGenFrame *frame = new TSGenFrame();
    
    wxVector<wxString> labels;
    for(int i = 0; i < 35; i+=3){
        int val = 1;
        labels.push_back(std::to_string(val));
        labels.push_back("");
        labels.push_back("");
        val++;
    }
    
    wxVector<wxDouble> points1;
    points1.push_back(3);
    points1.push_back(-2.5);
    points1.push_back(-1.2);
    points1.push_back(3);
    points1.push_back(6);
    points1.push_back(5);
    points1.push_back(1);
    points1.push_back(3);
    points1.push_back(-2.5);
    points1.push_back(-1.2);
    points1.push_back(3);
    points1.push_back(6);
//    points1.push_back(5);
//    points1.push_back(1);
//    points1.push_back(3);
//    points1.push_back(-2.5);
//    points1.push_back(-1.2);
//    points1.push_back(3);
//    points1.push_back(6);
//    points1.push_back(5);
//    points1.push_back(1);
//    points1.push_back(3);
//    points1.push_back(-2.5);
//    points1.push_back(-1.2);
//    points1.push_back(3);
//    points1.push_back(6);
//    points1.push_back(5);
//    points1.push_back(1);
    
    wxVector<wxDouble> points2;
    points2.push_back(1);
    points2.push_back(-1.33);
    points2.push_back(2.5);
    points2.push_back(7);
    points2.push_back(3);
    points2.push_back(-1.8);
    points2.push_back(0.4);
    points2.push_back(1);
    points2.push_back(-1.33);
    points2.push_back(2.5);
    points2.push_back(7);
    points2.push_back(3);
//    points2.push_back(-1.8);
//    points2.push_back(0.4);
//    points2.push_back(1);
//    points2.push_back(-1.33);
//    points2.push_back(2.5);
//    points2.push_back(7);
//    points2.push_back(3);
//    points2.push_back(-1.8);
//    points2.push_back(0.4);
//    points2.push_back(1);
//    points2.push_back(-1.33);
//    points2.push_back(2.5);
//    points2.push_back(7);
//    points2.push_back(3);
//    points2.push_back(-1.8);
//    points2.push_back(0.4);
//    points2.push_back(1);
//    points2.push_back(-1.33);
//    points2.push_back(2.5);
//    points2.push_back(7);
//    points2.push_back(3);
//    points2.push_back(-1.8);
//    points2.push_back(0.4);
    
    frame->loadTimeSeriesData(labels, "network traffic", points1, "predictions", points2);
    frame->loadWidgets();
    frame->Show(true); 
    return true;
}
