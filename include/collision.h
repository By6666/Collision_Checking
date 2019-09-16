//最基本的碰撞检测方法：判断是否含有两条相交的边

//判断两条边是否相交的方法：两个向量做叉乘

#ifndef COLLISION_H
#define COLLISION_H

#include <opencv2/opencv.hpp>

#include <iostream>
#include <vector>

typedef cv::Point2f Point_type;
typedef std::vector<Point_type> PointSet_type;

class Collision {
 public:
  Collision(const PointSet_type& object_1, const PointSet_type& object_2)
      : obj_1_(object_1), obj_2_(object_2) {}

  bool IsCollision();

 private:
  struct Boundary {
    Point_type pStart;
    Point_type pEnd;
  };

  PointSet_type obj_1_;
  PointSet_type obj_2_;

  int order(const Boundary& bLine, const Point_type& pt) const;
  bool onSegment(const Boundary& bLine, const Point_type& pt) const;
  bool intersection(const Boundary& bLine1, const Boundary& bLine2) const;
};

#endif