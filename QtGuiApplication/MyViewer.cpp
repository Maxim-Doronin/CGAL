#include "MyViewer.h" 

MyViewer::MyViewer(QWidget * parent) : QGLViewer(parent) { 
} 

void MyViewer::draw() {
    glPointSize(3.0f);  
    glColor3f(0.0f, 1.0f, 0.0f); 
    glBegin(GL_POINTS);
    for (int i = 0; i < points.size(); ++i) {
        glVertex3f(points[i].x(), points[i].y(), points[i].z()); 
    } 
    glEnd(); 

    if (isSpline2Shown) {
        buildBSpline2();
    }
    if (isSpline3Shown) {
        buildBSpline3();
    }
} 

void MyViewer::init() {
    restoreStateFromFile();
    points.push_back(Point_3(0.1, 0.1, 0.1));
}

std::vector<int> MyViewer::getSelectedPointIds(const QPoint &point) {
    qglviewer::Vec orig, dir;
    camera()->convertClickToLine(point, orig, dir);
    std::vector<int> selected = std::vector<int>();

    for (int i = 0; i < points.size(); i++) {
        float t = (points[i].z() - orig.z) / dir.z;
        float x = orig.x + dir.x * t;
        float y = orig.y + dir.y * t;
        if (sqrt(abs(points[i].y() - y) * abs(points[i].y() - y) + 
            abs(points[i].x() - x) * abs(points[i].x() - x)) < 0.04f) {
            selected.push_back(i);
        }
    }
    return selected;
}

void MyViewer::postSelection(const QPoint & point) {  
    std::vector<int> selected = this->getSelectedPointIds(point);
    
    // Отображение результата в отдельном окне  
    QString result;  
    for (int i = 0; i < selected.size(); i++)  {
        QString tmp = "Vertex number " + QString::number(selected[i]) + ": " +
            QString::number(points[selected[i]].x()) + " " +
            QString::number(points[selected[i]].y()) + " " +
            QString::number(points[selected[i]].z()) + "\n";
        result.append(tmp);
    }  
    QMessageBox::information(this, "Selection", result);
}

void MyViewer::mousePressEvent(QMouseEvent *event) {
    if (isRemovePointMode) {
        const QPoint point = event->pos();
        std::vector<int> selected = this->getSelectedPointIds(point);

        for (int i = 0; i < selected.size(); i++) {
            points.erase(points.begin() + selected[i]);
        }

        update();
    }
    else if (isMovePointMode) {
        const QPoint point = event->pos();
        std::vector<int> selected = getSelectedPointIds(point);

        if (selected.size() > 0) {
            movePointIndex_ = selected[0];
        }
        oldMousePosition_ = new QPoint(point);
    } else {
        QGLViewer::mousePressEvent(event);
    }
}

void MyViewer::mouseMoveEvent(QMouseEvent *event) {
    if (isMovePointMode) {
        if (movePointIndex_ != -1) {
            int x = event->x();
            int y = event->y();

            int dx = x - oldMousePosition_->x();
            int dy = y - oldMousePosition_->y();

            delete oldMousePosition_;
            oldMousePosition_ = new QPoint(event->pos());

            Point_3 oldPoint = points.at(movePointIndex_);
            points.at(movePointIndex_) = Point_3(oldPoint.x() + 0.01f * dx, 
                oldPoint.y() + 0.01f * dy, oldPoint.z());

            update();
        }
    }
    else {
        QGLViewer::mouseMoveEvent(event);
    }
}

void MyViewer::mouseReleaseEvent(QMouseEvent *event) {
    if (isMovePointMode) {
        //movePoint = nullptr;
        movePointIndex_ = -1;
        oldMousePosition_ = nullptr;
    }
    else {
        QGLViewer::mouseReleaseEvent(event);
    }
}

void MyViewer::removeAllPoints() {
    points.clear();
}

void MyViewer::createCubeChain() {
    this->removeAllPoints();
    
    const float interval = static_cast <float> (CUBE_BOUND_SIZE) / CUBE_DIM_COUNT;
    for (int i = 0; i < CUBE_DIM_COUNT; i++) {
        for (int j = 0; j < CUBE_DIM_COUNT; j++) {
            for (int k = 0; k < CUBE_DIM_COUNT; k++) {
                float x = -static_cast <float> (CUBE_BOUND_SIZE) / 2 + i*interval;
                float y = -static_cast <float> (CUBE_BOUND_SIZE) / 2 + j*interval;
                float z = -static_cast <float> (CUBE_BOUND_SIZE) / 2 + k*interval;
                points.push_back(Point_3(x, y, z));
            }
        }
    }
}

void MyViewer::createFilledCube() {
    this->removeAllPoints();

    for (int i = 0; i < CUBE_POINT_COUNT; i++) { 
        float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * (CUBE_BOUND_SIZE)
            -static_cast <float> (CUBE_BOUND_SIZE) / 2;
        float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * (CUBE_BOUND_SIZE)
            -static_cast <float> (CUBE_BOUND_SIZE) / 2;
        float z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * (CUBE_BOUND_SIZE)
            -static_cast <float> (CUBE_BOUND_SIZE) / 2;
        points.push_back(Point_3(x, y, z));
    }
}

Point_3 MyViewer::getPointInSphere() {
    const float SPHERE_DIAM = SPHERE_RADIUS * 2;
    while (true) {
        float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * (SPHERE_DIAM)
            -static_cast <float> (SPHERE_RADIUS);
        float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * (SPHERE_DIAM)
            -static_cast <float> (SPHERE_RADIUS);
        float z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * (SPHERE_DIAM)
            -static_cast <float> (SPHERE_RADIUS);
        if (x * x + y * y + z * z <= SPHERE_RADIUS * SPHERE_RADIUS) {
            return Point_3(x, y, z);
        }
    }
}

void MyViewer::createFilledSphere() {
    this->removeAllPoints();

    for (int i = 0; i < SPHERE_POINT_COUNT; i++) {
        points.push_back(getPointInSphere());
    }
}

void MyViewer::createSphereEps() {
    this->removeAllPoints();

    for (int i = 0; i < SPHERE_POINT_COUNT; i++) {
        Point_3 point = getPointInSphere();
        float norm = sqrt(point.x() * point.x() + point.y() * point.y() + point.z() * point.z()) / SPHERE_RADIUS;
        float x_eps = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * SPHERE_EPS - SPHERE_EPS / 2;
        float y_eps = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * SPHERE_EPS - SPHERE_EPS / 2;
        float z_eps = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * SPHERE_EPS - SPHERE_EPS / 2;
        points.push_back(Point_3(point.x() / norm + x_eps, point.y() / norm + y_eps, point.z() / norm + z_eps));
    }
}

void MyViewer::buildBSpline3() {
    BSpline bSpline = BSpline(&points, false);
    bSpline.drawSplineCurve();
}

void MyViewer::buildBSpline2() {
    BSpline bSpline = BSpline(&points, true);
    bSpline.drawSplineCurve();
}