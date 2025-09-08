#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joy.hpp"
#include "skratch_gazebo/SkratchPlatformController.hpp"

std::shared_ptr<SkratchPlatformController> platformController;

void cmdVelCallback(const geometry_msgs::msg::Twist &msg) {
  if (platformController) {
    platformController->setCmdVel(msg.linear.x, msg.linear.y, msg.angular.z);
  }
}

void joyCallback(const sensor_msgs::msg::Joy &joy) {
  if (platformController) {
    platformController->setCmdVel(joy.axes[1], joy.axes[0], joy.axes[3]);
  }
}

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  rclcpp::NodeOptions options;
  options.parameter_overrides({{"use_sim_time", true}});

  rclcpp::Node::SharedPtr nh = std::make_shared<rclcpp::Node>(
      "skratch_gazebo_platform_controller", options);

  auto cmdVelSubscriber = nh->create_subscription<geometry_msgs::msg::Twist>(
      "/cmd_vel", 10, cmdVelCallback);

  auto joySubscriber =
      nh->create_subscription<sensor_msgs::msg::Joy>("/joy", 1000, joyCallback);

  double platformMaxLinVel;
  if (!nh->has_parameter("platform_max_lin_vel")) {
    platformMaxLinVel = 1.0;
  } else {
    nh->get_parameter("platform_max_lin_vel", platformMaxLinVel);
  }

  double platformMaxAngVel;
  if (!nh->has_parameter("platform_max_ang_vel")) {
    platformMaxAngVel = 1.0;
  } else {
    nh->get_parameter("platform_max_ang_vel", platformMaxAngVel);
  }

  platformController = std::make_shared<SkratchPlatformController>(nh);
  platformController->setMaxPlatformVelocity(platformMaxLinVel,
                                             platformMaxAngVel);

  rclcpp::WallRate loopRate(100);

  while (rclcpp::ok()) {
    rclcpp::spin_some(nh);
    platformController->step();
    platformController->publishOdomToBaseLinkTF();
    platformController->publishOdom();
    platformController->publishPivotMarkers();

    loopRate.sleep();
  }

  rclcpp::shutdown();
  return 0;
}
