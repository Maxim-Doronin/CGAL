#include "Viewer.h" 

using namespace std;

void Viewer::draw() { 
    glColor3f(1.0f, 0.0f, 0.0f);  
    for each (Points points in this->faces) {
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < points.size(); ++i) {
            glVertex3f(points[i].x(), points[i].y(), points[i].z());
        }
        glEnd();
    }

    glPointSize(3.0f);  
    glColor3f(0.0f, 1.0f, 0.0f);  
    glBegin(GL_POINTS);  
    for (int i = 0; i < points.size(); ++i) { 
        glVertex3f(points[i].x(), points[i].y(), points[i].z()); 
    }  
    glEnd(); 
}

void Viewer::init() { 
    restoreStateFromFile(); 
}