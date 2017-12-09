#include "QtGuiApplication.h"

QtGuiApplication::QtGuiApplication(QWidget *parent): QMainWindow(parent) {
    ui.setupUi(this);
    connect(ui.addButton, SIGNAL(clicked()), this, SLOT(addPoint()));
    connect(ui.removeAllPointsButton, SIGNAL(clicked()), this, SLOT(removeAllPoints()));
    connect(ui.removePointButton, SIGNAL(clicked()), this, SLOT(removePoint()));
    connect(ui.createCubeChain, SIGNAL(clicked()), this, SLOT(createCubeChain()));
    connect(ui.createFilledCube, SIGNAL(clicked()), this, SLOT(createFilledCube()));
    connect(ui.createFilledSphere, SIGNAL(clicked()), this, SLOT(createFilledSphere()));
    connect(ui.createSphereEps, SIGNAL(clicked()), this, SLOT(createSphereEps()));
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

void QtGuiApplication::removePoint() {
    ui.movePointButton->setChecked(false);
    ui.widget->isRemovePointMode = ui.removePointButton->isChecked();
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