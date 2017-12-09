#pragma once
#include <vector>

#include <QGLViewer/qglviewer.h>
#include <QMessageBox>
#include <QMouseEvent>

#include "typedefs.h"

class MyViewer : public QGLViewer { 
 public:
     MyViewer(QWidget* parent);
     Points3 points;

     bool isRemovePointMode = false;

     void removeAllPoints();

     void createCubeChain();
     void createFilledCube();
     void createFilledSphere();
     void createSphereEps();

 protected:  
     virtual void draw();  
     virtual void init(); 

     virtual void postSelection(const QPoint &point);
     std::vector<int> MyViewer::getSelectedPointIds(const QPoint &point);
     virtual void mousePressEvent(QMouseEvent *event);

     Point_3 getPointInSphere();

     const float CUBE_BOUND_SIZE = 1;
     const int CUBE_DIM_COUNT = 10;
     const int CUBE_POINT_COUNT = 500;
     const float SPHERE_RADIUS = 0.5;
     const int SPHERE_POINT_COUNT = 500;
     const float SPHERE_EPS = 0.05;
};