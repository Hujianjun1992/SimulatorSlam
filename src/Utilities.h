#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "DataType.h"

namespace Simulator {
    class Utilities{
    public:
        static void ReadData(std::string file_path, std::vector<OdometryData> &odom_data, std::vector<LaserData> &laser_data);
            static void DataConvert(std::string file_path, std::vector<OdometryData> &odom_data, std::vector<LaserData> &laser_data);
    };
}
