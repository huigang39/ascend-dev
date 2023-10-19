/*
 * @file flashgo_client.cpp
 * @author huigang39
 * @brief ROS2 client for FlashGo
 * @date 2023-10-19
 * @version 0.0.1
 * @note ROS2 client for FlashGo
 * @warning None.
 * @bug None.
 */

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"

#define RAD2DEG(x) ((x) * 180. / M_PI)

int round_double(double number)
{
    return (number > 0.0) ? (number + 0.5) : (number - 0.5);
}

void scanCallback(const sensor_msgs::msg::LaserScan::SharedPtr scan)
{
    int count = round_double(scan->scan_time / scan->time_increment);
    RCLCPP_INFO(rclcpp::get_logger("eai_info"), "I heard a laser scan %s[%d]:", scan->header.frame_id.c_str(), count);
    RCLCPP_INFO(rclcpp::get_logger("eai_info"), "angle_range, %f, %f", RAD2DEG(scan->angle_min), RAD2DEG(scan->angle_max));

    for (int i = 0; i < count; i++)
    {
        float degree = RAD2DEG(scan->angle_min + scan->angle_increment * i);
        RCLCPP_INFO(rclcpp::get_logger("eai_info"), ": [%f, %f]", degree, scan->ranges[i]);
    }
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("flash_lidar_client");

    auto subscription = node->create_subscription<sensor_msgs::msg::LaserScan>(
        "/scan", 1000, scanCallback);

    rclcpp::spin(node);

    rclcpp::shutdown();

    return 0;
}
