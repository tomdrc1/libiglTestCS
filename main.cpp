#include <iostream>
#include <igl/readSTL.h>
#include <igl/opengl/glfw/Viewer.h>
#include <igl/ray_mesh_intersect.h>
#include <Eigen/src/Core/Matrix.h>
#include <Eigen/src/Core/MatrixBase.h>

Eigen::MatrixXd Vs, Ns;
Eigen::MatrixXi Fs;

int main(int argc, char *argv[])
{
  // load a mesh
  std::ifstream fileStream ("/home/magshimim/CellStudio_Work/libigl_tutorial/libigl-example-project/Microatlas_real_dim.stl");
  igl::readSTL(fileStream, Vs, Fs, Ns);

  //Load a mesh in OFF format
  //Vs, Fs = igl::read_triangle_mesh("/home/magshimim/CellStudio_Work/libigl_tutorial/libigl-example-project/Microatlas_real_dim.stl");
  
  std::string dir,_1,_2,name;
  igl::read_triangle_mesh("/home/magshimim/CellStudio_Work/libigl_tutorial/libigl-example-project/Microatlas_real_dim.stl" ,Vs ,Fs,dir,_1,_2,name);

  std::cout << "DIR:" << dir << std::endl;
  std::cout << "_1:" << _1 << std::endl;
  std::cout << "_2:" << _2 << std::endl;
  std::cout << "name:" << name << std::endl;

  Eigen::MatrixBase< Eigen::Matrix<int, 1, 1 ,1> > *source;
  //Eigen::MatrixBase< Eigen::Matrix<int, 1, 1 ,1> > *dir;
  

  /*## Print the vertices and faces matrices 
  print("Vertices: ", len(v))
  print("Faces: ", len(f))*/

  // Plot the mesh
  igl::opengl::glfw::Viewer viewer;
  viewer.data().set_mesh(Vs, Fs);
  viewer.data().set_face_based(true);
  viewer.launch();

  /*// Inline mesh of a cube
  const Eigen::MatrixXd V= (Eigen::MatrixXd(8,3)<<
    0.0,0.0,0.0,
    0.0,0.0,1.0,
    0.0,1.0,0.0,
    0.0,1.0,1.0,
    1.0,0.0,0.0,
    1.0,0.0,1.0,
    1.0,1.0,0.0,
    1.0,1.0,1.0).finished();
  const Eigen::MatrixXi F = (Eigen::MatrixXi(12,3)<<
    1,7,5,
    1,3,7,
    1,4,3,
    1,2,4,
    3,8,7,
    3,4,8,
    5,7,8,
    5,8,6,
    1,5,6,
    1,6,2,
    2,6,8,
    2,8,4).finished().array()-1;

  // Plot the mesh
  igl::opengl::glfw::Viewer viewer;
  viewer.data().set_mesh(V, F);
  viewer.data().set_face_based(true);
  viewer.launch();*/
}
