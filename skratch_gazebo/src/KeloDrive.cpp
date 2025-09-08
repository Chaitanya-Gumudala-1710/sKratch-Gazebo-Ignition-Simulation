#include "skratch_gazebo/KeloDrive.hpp"

KeloDrive::KeloDrive(rclcpp::Node::SharedPtr nh, std::string name, double xPos,
                     double yPos, double zPos, double pivotOrientation)
    : _name(name), _xPos(xPos), _yPos(yPos), _zPos(zPos),
      _pivotOrientation(pivotOrientation) {

  std::string ctrl_topic = "/skratch_base_controller/commands";
  hubWheelPub =
      nh->create_publisher<std_msgs::msg::Float64MultiArray>(ctrl_topic, 1);
}

void KeloDrive::getPos(double &xPos, double &yPos, double &zPos) const {
  xPos = _xPos;
  yPos = _yPos;
  zPos = _zPos;
}

void KeloDrive::setPivotOrientation(double orientation) {
  _pivotOrientation = orientation;
}

visualization_msgs::msg::Marker KeloDrive::getPivotMarker() const {
  visualization_msgs::msg::Marker marker;
  marker.header.frame_id = "base_link";
  marker.header.stamp = rclcpp::Clock().now();
  marker.id = 0;
  marker.type = visualization_msgs::msg::Marker::ARROW;
  marker.action = visualization_msgs::msg::Marker::ADD;

  getPos(marker.pose.position.x, marker.pose.position.y,
         marker.pose.position.z);
  tf2::Quaternion quat;
  quat.setRPY(0, 0, _pivotOrientation);
  quat.normalize();
  marker.pose.orientation = tf2::toMsg(quat);
  marker.scale.x = 0.25;
  marker.scale.y = 0.05;
  marker.scale.z = 0.05;

  marker.color.r = 1.0;
  marker.color.g = 0.0;
  marker.color.b = 0.0;
  marker.color.a = 1.0;
  return marker;
}

void KeloDrive::setHubWheelVelocities(const std::vector<double> &velocities) {
  std_msgs::msg::Float64MultiArray msg;
  msg.data = velocities;
  hubWheelPub->publish(msg);
}
