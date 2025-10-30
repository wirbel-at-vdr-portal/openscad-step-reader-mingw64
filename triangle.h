/*
 * Copyright 2019 Assaf Gordon <assafgordon@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 */
#pragma once
#include <vector>   // std::vector
#include <iostream> // std::ostream

class Point {
private:
  double px, py, pz;
public:
  Point() : px(0.0d), py(0.0d), pz(0.0d) {};
  Point(double X, double Y, double Z) : px(X), py(Y), pz(Z) {}
  Point(const gp_Pnt& point) : px(point.X()), py(point.Y()), pz(point.Z()) {}
  double x(void) const { return px; }
  double y(void) const { return py; }
  double z(void) const { return pz; }
  void write_ascii_stl(std::ostream& os) const {
     os << "vertex " << px << " " << py << " " << pz;
     }
};


static std::ostream& operator <<(std::ostream& os, const Point& p) {
  os << "[" << p.x() << "," << p.y() << "," << p.z() << "]";
  return os;
}


class Triangle {
private:
  Point p1, p2, p3;
public:
  Triangle() {} ;
  Triangle(const Point& P1, const Point& P2, const Point& P3) : p1(P1), p2(P2), p3(P3) {}
  void write_points_vector(std::ostream& os) const {
     os << p1 << "," << p2 << "," << p3;
     }
  void write_ascii_stl(std::ostream& os) const {
     os << "    ";
     p1.write_ascii_stl(os);
     os << std::endl;

     os << "    ";
     p2.write_ascii_stl(os);
     os << std::endl;

     os << "    ";
     p3.write_ascii_stl(os);
     os << std::endl;
     }
};


class Face {
private:
  std::vector<Triangle> triangles;
public:
  Face() {};
  void add(const Triangle& tr) {
     triangles.push_back(tr);
     }
  void add(const Face& f) {
     triangles.insert(triangles.end(),
                      f.triangles.begin(),
                      f.triangles.end());
     }
  void write_ascii_stl(std::ostream& os) const {
     for(auto& t:triangles) {
        os << " facet normal 42 42 42" << std::endl;
        os << "   outer loop" << std::endl;
        t.write_ascii_stl(os);
        os << "   endloop" << std::endl;
        os << " endfacet" << std::endl;
        }
     }
  void write_points_vector(std::ostream& os) const {
     int i = 1;
     os << "[" << std::endl;
     for(auto& t:triangles) {
        os << "  ";
        t.write_points_vector(os);
        os << ",";
        if (i==1 || (i%10==0 && triangles.size()>10))
           os << " // Triangle " << i << " / " << triangles.size();
        os << std::endl;
        i++;
        }
     os << "];" << std::endl;
     }
  void write_face_vector(std::ostream& os) const {
     os << "[" << std::endl;
     for(int i=0; i<triangles.size(); i++) {
        int idx = i*3;
        os << "  [" << idx << "," << (idx+1) << "," << (idx+2) << "],";
        if (i==0 || ((i+1)%10==0 && triangles.size()>10))
           os << " // Triangle " << (i+1) << " / " << triangles.size();
        os << std::endl;
        }
     os << "];" << std::endl;
     }
};
