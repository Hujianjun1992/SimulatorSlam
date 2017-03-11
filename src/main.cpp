#include <iostream>
#include <fstream>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "RobotSimulator.h"
#include "Utilities.h"

using namespace Simulator;

int main(int argc, char *argv[])
{
  SimulatorConfig sim_config;
  //  sim_config.file_path = "./data/localized.txt";
  sim_config.file_path = "./data/data.txt";
  sim_config.map_size_x = 800;
  sim_config.map_size_y = 800;
  sim_config.resulotion = 50;

  RobotSimulator robot_sim(sim_config);

  int data_flag = 1;

  while (data_flag) {
    data_flag = robot_sim.OneStepForward();
    cv::imshow("Laser Beam", robot_sim.wean_drawing_copy);
    if(cv::waitKey(2) == 'q')
      {
        break;
      }
      //      break;
  }

  return 0;
}
