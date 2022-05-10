/*
*
* Date : 2022 05 09
* modified : 2022 05 10
* Author : Jaeyong Park
* USRG
* email : yongee@kaist.ac.kr
* 
*/

#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <tf/transform_listener.h>
#include <pcl_ros/transforms.h>

class pc2_tf_changer
{
private:
  ros::NodeHandle _nh;
  ros::Subscriber _sub;
  ros::Publisher _pub;
  tf::TransformListener _listener;

public:
  pc2_tf_changer() //constructor
  {    
    _sub = _nh.subscribe<sensor_msgs::PointCloud2>("/filtered_points",1000,&pc2_tf_changer::callback,this);
    _pub = _nh.advertise<sensor_msgs::PointCloud2>("/changed_filtered_points", 1);
  }
  void callback(const sensor_msgs::PointCloud2ConstPtr& msg)
  {
  
    sensor_msgs::PointCloud2 pcl_in = *msg;
    sensor_msgs::PointCloud2 pcl_out;
    tf::StampedTransform transform;
    Eigen::Matrix4f transform_matrix;

    try
    {  
      _listener.lookupTransform("map", "base_link", ros::Time(), transform);
    } catch (tf::TransformException ex)
      {
      ROS_ERROR("%s",ex.what());
      }

    pcl_ros::transformAsMatrix(transform,transform_matrix);
    pcl_ros::transformPointCloud(transform_matrix,pcl_in,pcl_out);

    _pub.publish(pcl_out);
  }
  
};


int main(int argc, char** argv)
{
    ros::init(argc, argv, "pc2_tf_changer");
    pc2_tf_changer changer;
    std::cout<<"Starting point tf changer"<<std::endl;

    ros::spin();

    return 0; 
}