#include "ros/ros.h"
#include "scrub_robot_msgs/CleaningControllerPropertySetSrv.h"

/*
string controller_id
scrub_robot_msgs/BrushProperty[] brush_array
  string cleaning_mode_id
  string controller_id
  string brush_id
  int8 brush_height
  int8 brush_speed
  int8 brush_motor_power
  uint32 brush_threshold
scrub_robot_msgs/SuctionControllerProperty[] suction_array
  uint32 seq
  string cleaning_mode_id
  string controller_id
  string suction_motor_id
  int8 suction_level
  int8 suction_power
scrub_robot_msgs/SprayWaterControllerProperty[] spray_array
  uint32 seq
  string cleaning_mode_id
  string controller_id
  string spray_motor_id
  int8 spray_water_level
  int8 spray_motor_power
bool detergent_motor
int8 detergent_level
*/

int main(int argc, char ** argv)
{
	ros::init(argc, argv, "mysend_srv");
	ros::NodeHandle n;


  ros::ServiceClient client = n.serviceClient<scrub_robot_msgs::CleaningControllerPropertySetSrv>("/cleaning_controller/srv/property/set");
  scrub_robot_msgs::CleaningControllerPropertySetSrv srv;

    ROS_INFO("1");

  srv.request.controller_id = "controllerid";

    ROS_INFO("2");
    scrub_robot_msgs::BrushProperty brush_property;
  brush_property.cleaning_mode_id = "cleaningmodeid";
  brush_property.controller_id = "contrlllerid";
  brush_property.brush_id = "brushid";
  brush_property.brush_height = 1;
  brush_property.brush_speed = 1;
  brush_property.brush_motor_power = 1;
  brush_property.brush_threshold = 1;
  srv.request.brush_array.push_back(brush_property);

    ROS_INFO("3");
    scrub_robot_msgs::SuctionControllerProperty suction_controller_property;
  suction_controller_property.seq = 1;
  suction_controller_property.cleaning_mode_id = "cleaningmode";
  suction_controller_property.controller_id = "controllerid";
  suction_controller_property.suction_motor_id = "suctionid";
  suction_controller_property.suction_level = 1;
  suction_controller_property.suction_power = 1;
  srv.request.suction_array.push_back(suction_controller_property);

    ROS_INFO("4");
    scrub_robot_msgs::SprayWaterControllerProperty spray_water_controller_property;
  spray_water_controller_property.seq = 1;
  spray_water_controller_property.cleaning_mode_id = "cleaningid";
  spray_water_controller_property.controller_id = "controllerid";
  spray_water_controller_property.spray_motor_id = "spraypower";
  spray_water_controller_property.spray_water_level = 1;
  spray_water_controller_property.spray_motor_power = 1;
  srv.request.spray_array.push_back(spray_water_controller_property);

    ROS_INFO("5");
  srv.request.detergent_motor = 1;
  srv.request.detergent_level = 1;

    ROS_INFO("6");
  client.call(srv);

    ROS_INFO("7");




	return 0;
}
