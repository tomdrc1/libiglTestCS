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

Eigen::MatrixXd C;
Eigen::MatrixXd P;
Eigen::MatrixXd V;
Eigen::MatrixXi F;

float a,b,c;
float x,y,z;
Eigen::MatrixXd getPositionInTexture(const igl::Hit& hit, const Eigen::MatrixXd& VSource, const Eigen::MatrixXi& FSource);
bool key_down(igl::opengl::glfw::Viewer& viewer, unsigned char key, int modifier);
void generateHit(Eigen::Vector3d source, Eigen::Vector3d end);

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
    Eigen::MatrixXd NSource;

    #ifndef USE_CUBE
    Eigen::MatrixXd VSource;
    Eigen::MatrixXi FSource;

    // load a mesh
    std::ifstream fileStream (filePath);
    igl::readSTL(fileStream, VSource, FSource, NSource);
    #endif

    V = VSource;
    F = FSource;

    a = 0;
    b = 0;
    c = 0;

    x = 0.5;
    y = 0.5;
    z = 0.5;
    // Size of the "ray"
    Eigen::Vector3d source(0.3, 0, 0.5);
    Eigen::Vector3d end(0.4, 0.6, -1);

    generateHit(source, end);

    // Plot the mesh
    igl::opengl::glfw::Viewer viewer;
    viewer.callback_key_down = &key_down;
    viewer.data().set_mesh(VSource, FSource);
    viewer.data().set_colors(C);
    viewer.data().add_points(P,Eigen::RowVector3d(0,0,255));
    viewer.data().set_face_based(true);
    viewer.launch();

}

Eigen::MatrixXd getPositionInTexture(const igl::Hit& hit, const Eigen::MatrixXd& VSource_m, const Eigen::MatrixXi& FSource_m)
{
    return VSource_m.row(FSource_m(hit.id, 0)) * (1 - hit.u - hit.v) + VSource_m.row(FSource_m(hit.id, 1)) * hit.u + VSource_m.row(FSource_m(hit.id, 2)) * hit.v;
}

bool key_down(igl::opengl::glfw::Viewer& viewer, unsigned char key, int modifier)
{
    std::cout << "Clicked!: " << key << " Modifier: " << modifier << std::endl;
    if (key == 'X')
    {
        Eigen::Vector3d source(a, b, c);
        Eigen::Vector3d end(x, y, z);

        generateHit(source, end);
        viewer.data().clear();
        viewer.data().set_mesh(V, F);
        viewer.data().set_colors(C);
        viewer.data().add_points(P,Eigen::RowVector3d(0,0,255));
        viewer.data().set_face_based(true);

        a += 0.1;
        b += 0.2;
        c += 0.3;

        x += 0.1;
        y += 0.2;
        z += 0.3;
    }

    return false;
}

void generateHit(Eigen::Vector3d source, Eigen::Vector3d end)
{
    Eigen::Vector3d dir = end - source;
    igl::Hit h;

    bool ans = igl::ray_mesh_intersect(source, dir, V, F, h);
    C = Eigen::MatrixXd::Constant(F.rows(), F.cols(), 1);
    P = Eigen::MatrixXd::Constant(F.rows(), F.cols(), 1);
    

    std::cout << "source: " << source << std::endl;
    std::cout << "end: " << end << std::endl;
    std::cout << "dir: " << dir << std::endl;
    std::cout << "h.id: " << h.id << std::endl; 
    std::cout << "h.gid: " << h.gid << std::endl;

    // barycentric coordinates
    std::cout << "h.u: " << h.u << std::endl;
    std::cout << "h.v: " << h.v << std::endl;

    std::cout << "h.t: " << h.t << std::endl;

    std::cout << "XYZ Pos in texture: ";
    std::cout << getPositionInTexture(h, V, F) << std::endl;

    if (ans == true)
    {
        std::cout << "hit!" << std::endl;
        C.row(h.id) << 1,0,0;
        P.row(h.id) << getPositionInTexture(h, V, F);
    }
    else
    {
        std::cout << "no hit" << std::endl;
    }
}