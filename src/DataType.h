#pragma once

#include <vector>
#include <string>
#include <opencv2/opencv.hpp>

#define DEGREE2RAD 0.0174533f

typedef unsigned int uint;


namespace Simulator {

  struct WorldMap
  {
    int map_size_x;
    int map_size_y;

    int resulotion;

    int auto_shifted_x;
    int auto_shifted_y;

    cv::Mat env_map;
  };
  struct SimulatorConfig
  {
    std::string file_path;

    int map_size_x;
    int map_size_y;
    int resulotion;
  };
  struct Pose
  {
    double x;
    double y;
    double theta;
  };
  struct Point
  {
    double x;
    double y;
  };
  struct BearLine
  {
    Point start_point;
    Point end_point;
  };
  struct RangeData {
    std::vector<double> ranges;
    std::vector<double> xs;
    std::vector<double> ys;
  };
  struct OdometryData {
    double x;
    double y;
    double theta;
    double ts;
  };
  struct LaserData {
    OdometryData odom_robot;
    OdometryData odom_laser;
    std::vector<double> readings;
    double ts;
  };
}
