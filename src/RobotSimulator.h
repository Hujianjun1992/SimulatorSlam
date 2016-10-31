#pragma once

#include "DataType.h"
#include <iostream>
#include <vector>
#include <string>

namespace Simulator {

  class RobotSimulator {

  private:

    std::vector<OdometryData> odom_data;
    std::vector<LaserData> laser_data;

    WorldMap wean;
    uint next_laser_data;
    uint next_odom_data;
  public:

    cv::Mat wean_drawing_copy;
    RobotSimulator(){}
    RobotSimulator(SimulatorConfig &sim_config);
    ~RobotSimulator(){}

    int OneStepForward();
    void DrawLaserBeam(LaserData &_laser_data);

    int x_start, y_start;
    int x_end, y_end;
    int x_loc, y_loc;

    void DrawPath(OdometryData &_odom_data);
  };

}
