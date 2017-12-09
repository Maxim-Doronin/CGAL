#pragma once 
#include "typedefs.h" 
#include <math.h> 

class BSpline { 
 protected:  
     std::vector<double*> coefs;  
     int stepCount;  
     Points3* points; 
     bool isBSpline2_;

     double* calcSplineCoef3(double t); 
     double* calcSplineCoef2(double t);
     void drawSegment3(int segNum);
     void drawSegment2(int segNum);
 public: 
     bool closed;  
     inline int clamp(int val, int minVal, int maxVal) {
         return std::min(std::max(val, minVal), maxVal); 
     }  
     
     void drawSplineCurve();  
     
     BSpline(Points3* _points, bool isBSpline2 = false, int _stepCount = 10, bool _closed = false); 
     ~BSpline() {};
};