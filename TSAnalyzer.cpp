/* 
 * File:   TSGen.cpp
 * Author: heshan
 * 
 * Created on April 1, 2018, 9:33 PM
 */

#include <fstream>
#include <sstream>
#include <iomanip>
#include "TSAnalyzer.h"
#include "TimeSeries.h"

bool TSGen::OnInit() {
    TSGenFrame *frame = new TSGenFrame();
    
    wxVector<wxString> labels;
    float val = 0;
    
    std::stringstream stringStream;
    for(int i = 0; i < 800; i+=100){
        stringStream.str(std::string());
        stringStream << std::fixed << std::setprecision(2) << val;
        labels.push_back(stringStream.str());
        for (int j = 0; j < 99; j++) {
            labels.push_back("");
            val+=0.5;
        }
    }
    
    
    
    wxVector<wxDouble> points1;
    std::string fileName = "datasets/hr.txt";
    std::string line;
    std::ifstream file (fileName);
    if (file.is_open()) {
        int i = 0;
        while ( getline (file,line) ) {
            i++;
            points1.push_back(std::stod(line));
            if (i == 800) break;
        }
        file.close();
    }
    else std::cout << "Unable to open file '"<<fileName<<"'";
    
    wxVector<wxDouble> points2;
    fileName = "datasets/hr2.txt";
    std::string line2;
    std::ifstream file2 (fileName);
    if (file2.is_open()) {
        int i = 0;
        while ( getline (file2,line2) ) {
            i++;
            points2.push_back(std::stod(line2));
            if (i == 800) break;
        }
        file2.close();
    }
    else std::cout << "Unable to open file '"<<fileName<<"'";
    
//    wxVector<wxDouble> points1;
//    for(int i = 0; i < 70; i += 7) {
//        points1.push_back(3);
//        points1.push_back(-2.5);
//        points1.push_back(-1.2);
//        points1.push_back(3);
//        points1.push_back(6);
//        points1.push_back(5);
//        points1.push_back(1);
//    }
//    
//    wxVector<wxDouble> points2;
//    for(int i = 0; i < 70; i += 7) {
//        points2.push_back(1);
//        points2.push_back(-1.33);
//        points2.push_back(2.5);
//        points2.push_back(7);
//        points2.push_back(3);
//        points2.push_back(-1.8);
//        points2.push_back(0.4);
//    }    
    
    
    
    frame->loadTimeSeriesData(labels, "Heart Rate 1", points1, "Heart Rate 2", points2);
    frame->loadWidgets();
    frame->Show(true); 
    return true;
}
