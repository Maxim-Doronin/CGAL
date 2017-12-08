#include <boost/foreach.hpp>
#include <CGAL/convex_hull_3.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Surface_mesh.h>
#include <vector> 
#include "Viewer.h"
#include <QtWidgets/QApplication>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Polyhedron_3<K> Polyhedron_3;
typedef CGAL::Surface_mesh<Point_3> Surface_mesh;
typedef K::Point_3 Point_3;
typedef std::vector<Point_3> Points;
typedef std::vector<Points> Faces;
typedef boost::graph_traits<Polyhedron_3>::face_descriptor face_descriptor;
typedef boost::graph_traits<Polyhedron_3>::vertex_descriptor vertex_descriptor;


int main(int argc, char** argv) {
    Points points;
    Faces result;
    points.push_back(Point_3(0, 0, 0));
    points.push_back(Point_3(0, 0, 1));
    points.push_back(Point_3(0, 1, 0));
    points.push_back(Point_3(0, 1, 1));
    points.push_back(Point_3(1, 0, 0));
    points.push_back(Point_3(1, 0, 1));
    points.push_back(Point_3(1, 1, 0));
    points.push_back(Point_3(1, 1, 1));

    points.push_back(Point_3(0.5, 0.5, 0.7));
    points.push_back(Point_3(0.3, 0.7, 0.2));

    Polyhedron_3 poly;
    CGAL::convex_hull_3(points.begin(), points.end(), poly);

    BOOST_FOREACH(face_descriptor fd, faces(poly)) {
        Points face;
        BOOST_FOREACH(vertex_descriptor vd, vertices_around_face(halfedge(fd, poly), poly)) {
             face.push_back(vd->point());
        }
        result.push_back(face);
    }

    QApplication application(argc, argv); 
    Viewer viewer; 
    viewer.points = points;
    viewer.faces = result;
    viewer.setWindowTitle("simpleViewer"); 
    viewer.show(); 
    return application.exec();
}