#pragma once
#include <vector>

#include <QGLViewer/qglviewer.h>
#include <QMessageBox>
#include <QMouseEvent>

#include "BSpline.h"
#include "typedefs.h"

class MyViewer : public QGLViewer { 
 public:
     MyViewer(QWidget* parent);
     Points3 points;

     bool isRemovePointMode = false;
     bool isMovePointMode = false;
     bool isSpline2Shown = false;
     bool isSpline3Shown = false;

     void removeAllPoints();

     void createCubeChain();
     void createFilledCube();
     void createFilledSphere();
     void createSphereEps();

     void buildBSpline3();
     void buildBSpline2();

 protected:  
     virtual void draw();  
     virtual void init(); 

     virtual void postSelection(const QPoint &point);
     std::vector<int> MyViewer::getSelectedPointIds(const QPoint &point);
     virtual void mousePressEvent(QMouseEvent *event);
     virtual void mouseMoveEvent(QMouseEvent *event);
     virtual void mouseReleaseEvent(QMouseEvent *event);
     int movePointIndex_;
     QPoint* oldMousePosition_;

     Point_3 getPointInSphere();

     const float CUBE_BOUND_SIZE = 1;
     const int CUBE_DIM_COUNT = 10;
     const int CUBE_POINT_COUNT = 500;
     const float SPHERE_RADIUS = 0.5;
     const int SPHERE_POINT_COUNT = 500;
     const float SPHERE_EPS = 0.05;
};