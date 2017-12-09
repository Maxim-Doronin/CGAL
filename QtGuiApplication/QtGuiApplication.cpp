#include "QtGuiApplication.h"

QtGuiApplication::QtGuiApplication(QWidget *parent): QMainWindow(parent) {
    ui.setupUi(this);
    connect(ui.addButton, SIGNAL(clicked()), this, SLOT(addPoint()));
    connect(ui.moveButton, SIGNAL(clicked()), this, SLOT(movePoint()));
    connect(ui.removeAllPointsButton, SIGNAL(clicked()), this, SLOT(removeAllPoints()));
    connect(ui.removePointButton, SIGNAL(clicked()), this, SLOT(removePoint()));
    connect(ui.createCubeChain, SIGNAL(clicked()), this, SLOT(createCubeChain()));
    connect(ui.createFilledCube, SIGNAL(clicked()), this, SLOT(createFilledCube()));
    connect(ui.createFilledSphere, SIGNAL(clicked()), this, SLOT(createFilledSphere()));
    connect(ui.createSphereEps, SIGNAL(clicked()), this, SLOT(createSphereEps()));
    connect(ui.buildBSpline3Button, SIGNAL(clicked()), this, SLOT(buildBSpline3()));
    connect(ui.buildBSpline2Button, SIGNAL(clicked()), this, SLOT(buildBSpline2()));
}

void QtGuiApplication::addPoint(Point_3 point) {
    ui.widget->points.push_back(point);
}

void QtGuiApplication::addPoint() {
    float x = QString(ui.xCoord->text()).toFloat();  
    float y = QString(ui.yCoord->text()).toFloat();  
    float z = QString(ui.zCoord->text()).toFloat();  
    this->addPoint(Point_3(x, y, z));
}

void QtGuiApplication::movePoint() {
    ui.widget->isMovePointMode = ui.moveButton->isChecked();
    ui.widget->isRemovePointMode = false;
    ui.removePointButton->setChecked(false);
}

void QtGuiApplication::removePoint() {
    ui.widget->isRemovePointMode = ui.removePointButton->isChecked();
    ui.widget->isMovePointMode = false;
    ui.moveButton->setChecked(false);
}

void QtGuiApplication::removeAllPoints() {
    ui.widget->removeAllPoints();
}

void QtGuiApplication::createCubeChain() {
    ui.widget->createCubeChain();
}

void QtGuiApplication::createFilledCube() {
    ui.widget->createFilledCube();
}

void QtGuiApplication::createFilledSphere() {
    ui.widget->createFilledSphere();
}

void QtGuiApplication::createSphereEps() {
    ui.widget->createSphereEps();
}

void QtGuiApplication::buildBSpline3() {
    if (ui.buildBSpline3Button->isChecked()) {
        ui.widget->isSpline3Shown = true;
    } else {
        ui.widget->isSpline3Shown = false;
    }
}

void QtGuiApplication::buildBSpline2() {
    if (ui.buildBSpline2Button->isChecked()) {
        ui.widget->isSpline2Shown = true;
    } else {
        ui.widget->isSpline2Shown = false;
    }
}