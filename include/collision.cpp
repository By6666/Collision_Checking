#include "collision.h"

/* 判断点pt在线line的那一侧
 * 输入：一条直线与一个点
 * 输出：int型能够表示状态的数值
 *  */
int Collision::order(const Boundary& bLine, const Point_type& pt) const {
  // 通过向量的外积判断
  int intOrientation = (bLine.pEnd.y - bLine.pStart.y) * (pt.x - bLine.pEnd.x) -
                       (bLine.pEnd.x - bLine.pStart.x) * (pt.y - bLine.pEnd.y);
  if (intOrientation == 0) return 0;  // colinear
  if (intOrientation > 0) return 1;   // right side
  if (intOrientation < 0) return -1;  // left side
}

/* 当点与直线共线时，判断点是否在直线上
 * 输入：一条直线与一个点
 * 输出：是否在直线上
 *  */
bool Collision::onSegment(const Boundary& bLine, const Point_type& pt) const {
  if ((pt.x <= std::max(bLine.pStart.x, bLine.pEnd.x)) &&
      (pt.x >= std::min(bLine.pStart.x, bLine.pEnd.x)) &&
      (pt.y <= std::max(bLine.pStart.y, bLine.pEnd.y)) &&
      (pt.y >= std::min(bLine.pStart.y, bLine.pEnd.y))) {
    return true;
  } else {
    return false;
  }
}

/* 判断两条直线是否相交
 * 输入：两条直线
 * 输出：true 相交，false 不相交
 *  */
bool Collision::intersection(const Boundary& bLine1,
                             const Boundary& bLine2) const {
  int order1 = order(bLine1, bLine2.pStart);
  int order2 = order(bLine1, bLine2.pEnd);
  int order3 = order(bLine2, bLine1.pStart);
  int order4 = order(bLine2, bLine1.pEnd);
  if (order1 != order2 && order3 != order4) {
    return true;
  }
  if (order1 == 0 && onSegment(bLine1, bLine2.pStart)) {
    return true;
  }
  if (order2 == 0 && onSegment(bLine1, bLine2.pEnd)) {
    return true;
  }
  if (order3 == 0 && onSegment(bLine2, bLine1.pStart)) {
    return true;
  }
  if (order4 == 0 && onSegment(bLine2, bLine1.pEnd)) {
    return true;
  }
  false;
}

// check if collide
//  pt4   pt1
//     ego
//  pt3   pt2
bool Collision::IsCollision() {
  std::vector<Boundary> bA;
  for (int16_t i = 0; i < obj_1_.size(); ++i) {
    bA.push_back(Boundary{obj_1_[i], obj_1_[(i + 1) % obj_1_.size()]});
  }

  std::vector<Boundary> bB;
  for (int16_t i = 0; i < obj_2_.size(); ++i) {
    bB.push_back(Boundary{obj_2_[i], obj_2_[(i + 1) % obj_2_.size()]});
  }

  for (int i = 0; i < bA.size(); i++) {
    for (int j = 0; j < bB.size(); j++) {
      if (intersection(bA[i], bB[j])) {
        return true;
      }
    }
  }
  return false;
}