#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtGuiApplication.h"

#include "typedefs.h"

class QtGuiApplication : public QMainWindow
{
    Q_OBJECT

public:
    QtGuiApplication(QWidget *parent = Q_NULLPTR);

    public slots: 
    void addPoint();
    void addPoint(Point_3 point);
    void removePoint();
    void removeAllPoints();

    void createCubeChain();
    void createFilledCube();
    void createFilledSphere();
    void createSphereEps();
private:
    Ui::QtGuiApplicationClass ui;
};
