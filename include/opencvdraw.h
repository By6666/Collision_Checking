#ifndef OPENCVDRAW_H
#define OPENCVDRAW_H

#include <opencv2/opencv.hpp>

#include <cmath>
#include <iostream>
#include <vector>

#include "collision.h"

void OpencvDraw();

void MoseHandle(int event, int x, int y, int flags, void* param);

void DrawSin();

inline void DrawObject(const cv::Mat& img, const PointSet_type& obj,
                const cv::Scalar& color) {
  for (int16_t i = 0; i < obj.size(); ++i) {
    cv::line(img, obj[i], obj[(i + 1) % obj.size()], color, 2, cv::LINE_AA);
  }
}

#endif