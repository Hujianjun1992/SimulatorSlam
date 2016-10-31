#include <fstream>
#include <cmath>
#include "Utilities.h"

namespace Simulator {

  void Utilities::ReadData(std::string file_path, std::vector<OdometryData> &odom_data, std::vector<LaserData> &laser_data)
  {
    std::ifstream fin(file_path.c_str());
    if (!fin) {
      std::cerr << "Error : Unable to open file : " << file_path << std::endl;
      return;
    }
    std::string data_type;
    fin >> data_type;
    long cnt = 0;
    while (fin) {

      if (data_type.compare("self_time_stamp") == 0) {

      }
      else if (data_type.compare("L") == 0) {

        laser_data.push_back(LaserData());
        unsigned int new_laser_data_idx = laser_data.size()-1;
        //        fin >> laser_data[new_laser_data_idx].ts;
        // fin >> laser_data[new_laser_data_idx].odom_robot.x;
        // fin >> laser_data[new_laser_data_idx].odom_robot.y;
        // fin >> laser_data[new_laser_data_idx].odom_robot.theta;
        // fin >> laser_data[new_laser_data_idx].odom_laser.x;
        // fin >> laser_data[new_laser_data_idx].odom_laser.y;
        // fin >> laser_data[new_laser_data_idx].odom_laser.theta;
        laser_data[new_laser_data_idx].readings.resize(720);

        // BearLine bearline;
        // double length;

        for (unsigned int i = 0; i < 720; i++) {
          fin >> laser_data[new_laser_data_idx].readings[i];
          //          std::cout << laser_data[new_laser_data_idx].readings[i] << " ";
          // fin >> bearline.start_point.x;
          // fin >> bearline.start_point.y;
          // fin >> bearline.end_point.x;
          // fin >> bearline.end_point.y;

          // length = sqrt(pow(bearline.end_point.x-bearline.start_point.x, 2) + pow(bearline.end_point.y-bearline.start_point.x, 2));
          // laser_data[new_laser_data_idx].readings[i] = length;
        }
        //        std::cout << std::endl;
        //        laser_data[new_laser_data_idx].odom_robot.ts = laser_data[new_laser_data_idx].ts;
        //        laser_data[new_laser_data_idx].odom_robot.ts = laser_data[new_laser_data_idx].ts;
      }
      else if (data_type.compare("O") == 0) {
        odom_data.push_back(OdometryData());
        unsigned int new_odom_data_idx = odom_data.size()-1;
        fin >> odom_data[new_odom_data_idx].ts;
        fin >> odom_data[new_odom_data_idx].x;
        fin >> odom_data[new_odom_data_idx].y;
        fin >> odom_data[new_odom_data_idx].theta;
      }
      else {
        //   std::cerr << "Error : Unrecognized measurement type : " << data_type << std::endl;
      }
      fin >> data_type;
    }
    fin.close();
    return ;
  }

  void  Utilities::DataConvert(std::string file_path, std::vector<OdometryData> &odom_data, std::vector<LaserData> &laser_data){

    std::ofstream fout(file_path.c_str());
    if (!fout) {
      std::cerr << "Error : Unable to open file : " << file_path << std::endl;
      return;
    }

    for (uint i = 0; i < laser_data.size(); i++) {
      fout << "L " << laser_data[i].ts << " ";
      for (uint j = 0; j < laser_data[i].readings.size(); j++) {
        fout << laser_data[i].readings[j] << " ";
      }
      fout << "\n";
      fout << "O ";
      fout << odom_data[i].ts << " ";
      fout << odom_data[i].x << " ";
      fout << odom_data[i].y << " ";
      fout << odom_data[i].theta << "\n";
    }
    fout.close();
    return ;
  }

}
