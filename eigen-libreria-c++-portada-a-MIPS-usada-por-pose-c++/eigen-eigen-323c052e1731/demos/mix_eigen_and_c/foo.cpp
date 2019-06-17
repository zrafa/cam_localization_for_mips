
/* foo.cpp */

#include "foo.h"

#include <iostream>
// RAFA agregó la siguiente línea
#include <iostream>
#include <Eigen/Geometry>

#include <Eigen/Core>

using namespace Eigen;




extern "C" {




const double PI = 3.14159265358979323846;
const double TWOPI = 2.0*PI;

/**
 * Normalize angle to be within the interval [-pi,pi].
 */
inline double standardRad(double t) {
  if (t >= 0.) {
    t = fmod(t+PI, TWOPI) - PI;
  } else {
    t = fmod(t-PI, -TWOPI) + PI;
  }
  return t;
}



void wRo_to_euler(const Eigen::Matrix3d& wRo, double& yaw, double& pitch, double& roll) {
    yaw = standardRad(atan2(wRo(1,0), wRo(0,0)));
    double c = cos(yaw);
    double s = sin(yaw);
    pitch = standardRad(atan2(-wRo(2,0), wRo(0,0)*c + wRo(1,0)*s));
    roll  = standardRad(atan2(wRo(0,2)*s - wRo(1,2)*c, -wRo(0,1)*s + wRo(1,1)*c));
}




void foo(double m0, double m1, double m2, double m3, double m4, double m5, double m6, double m7, double m8, double t0, double t1, double t2) {
    float r_x =0, r_y=0, r_z=0;
    Eigen::Vector3d translation;
    Eigen::Matrix3d m;
    Eigen::Vector3f eulerAngle;

    translation << t0, t1, t2;
    m << (-1)*m0, m1, m2, m3, (-1)*m4, (-1)*m5, (-1)*m6, m7, m8;
    std::cout << "matrix:" << m << "\n";

   Eigen::Matrix3d F;
    F <<
      1, 0,  0,
      0,  -1,  0,
      0,  0,  1;
    Eigen::Matrix3d fixed_rot = F*m;
    double yaw, pitch, roll;
    // wRo_to_euler(m, yaw, pitch, roll);

    wRo_to_euler(fixed_rot, yaw, pitch, roll);

     std::cout   << "  matrix2=" << fixed_rot << "\n";

     std::cout   << "  yaw=" << (yaw*57.2958)  // convertido de radianes a grados
         << ", pitch=" << (pitch*57.2958)
         << ", roll=" << (roll*57.2958) << "\n";

      std::cout << "  distance=" << (translation.norm()*100) // convertido a centimentros
         << " cm, "
         << "\n"
         << "  x=" << (translation(0)*100)
         << ", y=" << (translation(1)*100)
         << ", z=" << (translation(2)*100)
         << "\n";


 //   std::cout << "m2 =" << m ;
//    eulerAngle = m.eulerAngles(0,1,2);

//    printf("ANGULO0=%f\n", eulerAngle[0]);
//    printf("ANGULO1=%f\n", eulerAngle[1]);
//    printf("ANGULO2=%f\n", eulerAngle[2]);

//    printf("ANGULO0=%f\n", eulerAngle[0] * 180 / M_PI);
//    printf("ANGULO1=%f\n", eulerAngle[1] * 180 / M_PI);
//    printf("ANGULO2=%f\n", eulerAngle[2] * 180 / M_PI);
}

} /* extern "C" */


