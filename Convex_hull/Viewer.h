#pragma once
#include <QGLViewer/qglviewer.h> 
#include <Qstring> 
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h> 


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_3 Point_3;
typedef std::vector<Point_3> Points;
typedef std::vector<Points> Faces;

class Viewer : public QGLViewer { 
 public:  
     Points points; 
     Faces faces;
 protected: 
     virtual void draw();
     virtual void init();
};