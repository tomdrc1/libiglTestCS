#include <iostream>
#include <igl/readSTL.h>
#include <igl/opengl/glfw/Viewer.h>
#include <igl/ray_mesh_intersect.h>
#include <Eigen/src/Core/Matrix.h>
#include <Eigen/src/Core/MatrixBase.h>
#include <Eigen/Dense>
#include <igl/readMESH.h>
#include <igl/raytri.c>

#include "cube.h"

#define ARGV_COUNT 2

int main(int argc, char** argv)
{

    if (argc != ARGV_COUNT)
    {
        std::cout << "Useage: ./example <path_to_stl>" << std::endl;
        return 1;
    }

    const std::string filePath = std::string(argv[1]);

    /*
        VSource - list of mesh vertex positions
        FSource - list of mesh indices into Vs (Ele)
    */
    Eigen::MatrixXd VSource, NSource;
    Eigen::MatrixXi FSource;

    // load a mesh
    std::ifstream fileStream (filePath);
    igl::readSTL(fileStream, VSource, FSource, NSource);

    // build the AABB tree for the mesh
    ///igl::AABB<Eigen::MatrixXd, 3> tree;

    // Size of the "ray"
    Eigen::Vector3d source(0,0,0);
    Eigen::Vector3d end(200,200,200);
    Eigen::Vector3d dir = end - source;
    igl::Hit h;

    bool ans = igl::ray_mesh_intersect(source, dir, V, F, h);
    std::cout << "source: " << source << std::endl;
    std::cout << "end: " << end << std::endl;
    std::cout << "dir: " << dir << std::endl;
    std::cout << "h.id: " << h.id << std::endl; 
    std::cout << "h.gid: " << h.gid << std::endl;

    // barycentric coordinates
    std::cout << "h.u: " << h.u << std::endl;
    std::cout << "h.v: " << h.v << std::endl;

    std::cout << "h.t: " << h.t << std::endl;

    if (ans == true)
    {
        std::cout << "hit!" << std::endl;
    }
    else
    {
        std::cout << "no hit" << std::endl;
    }

    // Plot the mesh
    igl::opengl::glfw::Viewer viewer;
    viewer.data().set_mesh(V, F);
    viewer.data().set_face_based(true);
    viewer.launch();

}