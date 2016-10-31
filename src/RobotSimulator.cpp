#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "RobotSimulator.h"
#include "Utilities.h"

namespace Simulator {

    RobotSimulator::RobotSimulator(SimulatorConfig &sim_config){

        wean.map_size_x = sim_config.map_size_x;
        wean.map_size_y = sim_config.map_size_y;
        wean.resulotion = sim_config.resulotion;
        wean.env_map.create(wean.map_size_x, wean.map_size_y, CV_8UC3);
        wean.env_map.copyTo(wean_drawing_copy);
        Utilities::ReadData(sim_config.file_path, odom_data, laser_data);

        x_start = wean.map_size_x/4;
        y_start = wean.map_size_y/2;

        next_laser_data = 0;
        next_odom_data = 0;
        return;
    }

    int RobotSimulator::OneStepForward(){

        if (next_laser_data > laser_data.size()-1) {
            return 0;
        }
        else {
            // for (uint i = 0; i < laser_data[next_laser_data].readings.size(); i++) {
            //   std::cout << laser_data[next_laser_data].readings[i] << " ";
            // }
            // std::cout << std::endl;
            DrawLaserBeam(laser_data[next_laser_data]);
            //      DrawPath(odom_data[next_odom_data]);

            next_laser_data++;
            next_odom_data++;
            return 1;
        }

    }

    void RobotSimulator::DrawLaserBeam(LaserData &_laser_data){

        wean.env_map.setTo(cv::Scalar(0));
        wean_drawing_copy.setTo(cv::Scalar(0));

        float delta_theta = 0.25f;
        int x_origin = wean.map_size_x/2;
        int y_origin = wean.map_size_y/2;
        //x_origin = 0;
        //y_origin = 0;

        int x_pose = 0;
        int y_pose = 0;

        cv::circle(wean.env_map,cv::Point(x_origin, y_origin), 5, CV_RGB(0, 0, 255));

        for (uint i = 0; i < _laser_data.readings.size(); i++) {

            double curr_th = (double)(-90.0f + (float)i*delta_theta)*(double)DEGREE2RAD;
            //      std::cout << curr_th << std::endl;
            x_pose = (int)(_laser_data.readings[i]*sin(-curr_th)*wean.resulotion) + x_origin;
            y_pose = (int)(_laser_data.readings[i]*cos(-curr_th)*wean.resulotion) + y_origin;

            if (x_pose >= 0 && x_pose < wean.map_size_x && y_pose >= 0 && y_pose < wean.map_size_y) {

                wean.env_map.at<cv::Vec3b>(x_pose,y_pose)[0] = 0;
                wean.env_map.at<cv::Vec3b>(x_pose,y_pose)[1] = 0;
                wean.env_map.at<cv::Vec3b>(x_pose,y_pose)[2] = 255;
            }
        }
        //    cv::flip(wean.env_map, wean_drawing_copy, -1);
        //    cv::transpose(wean.env_map, wean_drawing_copy);
        wean.env_map.copyTo(wean_drawing_copy);
    }


    void RobotSimulator::DrawPath( Simulator::OdometryData &_odom_data )
    {

        //    wean.env_map.setTo(cv::Scalar(0));
        //    wean_drawing_copy.setTo(cv::Scalar(0));

        x_loc = (int)_odom_data.x*30 + x_start;
        y_loc = (int)_odom_data.y*30 + y_start;

        if(!next_odom_data)
        {
            x_end = x_loc;
            y_end = y_loc;
        }

        if (x_end >= 0 && x_end < wean.map_size_x && y_end >= 0 && y_end < wean.map_size_x && x_start >= 0 && x_start < wean.map_size_x && y_start >= 0 && y_start < wean.map_size_y) {
            cv::line(wean.env_map,cv::Point(x_end, y_end), cv::Point(x_loc ,y_loc), CV_RGB(0, 255, 0), 1, 8, 0);
        }

        x_end = x_loc;
        y_end = y_loc;

        cv::transpose(wean.env_map, wean_drawing_copy);
        //    cv::flip(wean.env_map, wean_drawing_copy, 1);
        //    wean.env_map.copyTo(wean_drawing_copy);
    }
}
