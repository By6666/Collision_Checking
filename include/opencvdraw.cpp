#include "opencvdraw.h"

/* opencv碰撞检测画图
 * 输入：无
 * 输出：图像
 *  */
void OpencvDraw() {
  cv::Mat img(800, 800, CV_8UC3, cv::Scalar::all(0));
  cv::namedWindow("OBB");
  cv::setMouseCallback("OBB", MoseHandle, (void*)&img);

  while (1) {
    cv::imshow("OBB", img);

    if (cv::waitKey(20) == 27) break;
  }
}

/* 鼠标处理事件函数
 * 备注：鼠标左键单击画出点，
 * 单击鼠标中建构建图像，当画幅中含有两个检测对象时自动进行碰撞检测
 * 若边线为绿色，则无碰撞，若边线为红色，则发生碰撞
 * 单击鼠标右键即为清零操作
 * */
void MoseHandle(int event, int x, int y, int flags, void* param) {
  cv::Mat& img = *(cv::Mat*)param;

  static int state = 0;
  static PointSet_type obj_1, obj_2;
  static PointSet_type temp_obj;
  cv::Scalar color(0, 255, 0);

  /* 鼠标单击事件 */
  if (event == cv::EVENT_LBUTTONDOWN) {
    if (state == 3) {
      obj_1.clear();
      obj_2.clear();
      img = cv::Mat(800, 800, CV_8UC3, cv::Scalar::all(0));
      state = 0;
    } else {
      std::cout << "starting draw rect " << std::endl;
      Point_type temp(static_cast<float>(x), static_cast<float>(y));
      temp_obj.push_back(temp);
      cv::circle(img, temp, 3, cv::Scalar(255, 200, 0), cv::FILLED);
      std::cout << temp << std::endl;
    }
  }

  /* 双击左键画图 */
  if (event == cv::EVENT_MBUTTONDOWN) {
    if (temp_obj.size() < 2) return;
    std::cout << "mind button down ! !" << std::endl;
    if (state == 1) {
      obj_2 = temp_obj;
      temp_obj.clear();
      DrawObject(img, obj_2, color);
      state = 2;
    }
    if (state == 0) {
      obj_1 = temp_obj;
      temp_obj.clear();
      DrawObject(img, obj_1, color);
      state = 1;
    }
  }

  /* state=2 则进行碰撞检测 */
  if (state == 2) {
    /* 清空画幅 */
    img = cv::Mat(800, 800, CV_8UC3, cv::Scalar::all(0));

    /* 碰撞检测 */
    Collision collision_check(obj_1, obj_2);

    /* 颜色设置 */
    if (collision_check.IsCollision()) color = cv::Scalar(0, 0, 255);

    DrawObject(img, obj_1, color);
    DrawObject(img, obj_2, color);

    state = 3;
  }

  /* 单击右键复原 */
  if (event == cv::EVENT_RBUTTONDOWN) {
    obj_1.clear();
    obj_2.clear();
    temp_obj.clear();
    state = 0;
    img = cv::Mat(800, 800, CV_8UC3, cv::Scalar::all(0));
  }
}

/* 动态画sin曲线 */
void DrawSin() {
  cv::Mat img(800, 800, CV_8UC3, cv::Scalar::all(0));
  std::vector<cv::Point> stg;
  double cnt = 0;
  double omiga = 5;
  int opencv_x = 0;
  while (1) {
    if (opencv_x >= 800) {
      opencv_x = 0;
      stg.clear();
      img = cv::Mat(800, 800, CV_8UC3, cv::Scalar::all(0));
    }
    stg.push_back(cv::Point(opencv_x++, 400 - sin(omiga * cnt) * 100));
    cnt += 0.01;
    cv::polylines(img, stg, false, cv::Scalar(0, 0, 255), 1, cv::LINE_AA);
    cv::imshow("OBB", img);
    if (cv::waitKey(60) == 27) break;
  }
}