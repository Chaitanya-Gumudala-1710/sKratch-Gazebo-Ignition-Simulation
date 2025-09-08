#ifndef KELO_DRIVE_HPP
#define KELO_DRIVE_HPP

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include "tf2/LinearMath/Quaternion.hpp"
#include "tf2_geometry_msgs/tf2_geometry_msgs.hpp"
#include "visualization_msgs/msg/marker.hpp"

class KeloDrive {
public:
  /**
   * @brief Construct a new Kelo Drive object
   *
   * @param nh Node handle for the ros node managing the platform controller
   * @param name Name of the Kelo drive
   * @param xPos Position of the kelo drive along the x-axis of the base_link
   * @param yPos Position of the kelo drive along the y-axis of the base_link
   * @param zPos Position of the kelo drive along the z-axis of the base_link
   * @param pivotOrientation Initial orientation of the kelo drive pivot with
   * respect to the base_link
   */
  KeloDrive(rclcpp::Node::SharedPtr nh, std::string name, double xPos,
            double yPos, double zPos, double pivotOrientation);
  /**
   * @brief Destroy the Kelo Drive object
   *
   */
  virtual ~KeloDrive() {}

  /**
   * @brief Get the position of the kelo drive w.r.t base_link
   *
   * @param xPos
   * @param yPos
   * @param zPos
   */
  void getPos(double &xPos, double &yPos, double &zPos) const;

  /**
   * @brief Set the latest pivot orientation of the kelo drive
   *
   * @param orientation Latest pivot orientation w.r.t base_link
   */

  void setPivotOrientation(double orientation);
  /**
   * @brief Get the latest pivot orientation of the kelo drive
   *
   * @return double Latest pivot orientation w.r.t base_link
   */
  double getPivotOrientation() const { return _pivotOrientation; }

  /**
   * @brief Get an RViz marker object representing the pose of the kelo drive
   * pivot for debugging purposes
   *
   * @return visualization_msgs::Marker marker representing current pose of
   * the kelo drive pivot
   */
  visualization_msgs::msg::Marker getPivotMarker() const;

  /**
   * @brief Set the desired angular velocities for each of the two hub wheels
   * of the kelo drive
   *
   * @param leftAngVel Angular velocity for the left hub wheel in rad/s
   * @param rightAngVel Angular velocity for the right hub wheel in rad/s
   */

  void setHubWheelVelocities(const std::vector<double> &velocities);

protected:
  /**
   * @brief Name of the kelo drive
   *
   */
  std::string _name;

  /**
   * @brief Position of the kelo drive along the x-axis of the base_link
   *
   */
  double _xPos;

  /**
   * @brief Position of the kelo drive along the y-axis of the base_link
   *
   */
  double _yPos;

  /**
   * @brief Position of the kelo drive along the z-axis of the base_link
   *
   */
  double _zPos;

  /**
   * @brief Orientation of the kelo drive pivot with respect to the base_link
   *
   */
  double _pivotOrientation;

  /**
   * @brief ROS publishers for setting the desired velocity for the hub wheels
   *
   */
  rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr hubWheelPub;
};

#endif // KELO_DRIVE_HPP