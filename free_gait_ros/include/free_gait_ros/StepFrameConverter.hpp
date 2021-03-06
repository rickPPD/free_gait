/*
 * StepFrameConverter.hpp
 *
 *  Created on: Nov 11, 2016
 *      Author: Péter Fankhauser
 *   Institute: ETH Zurich, Robotic Systems Lab
 */

#pragma once

#include <free_gait_core/free_gait_core.hpp>

// ROS
#include <ros/ros.h>
#include <tf2_ros/buffer.h>

// STD
#include <memory>
#include <string>

namespace free_gait {

class StepFrameConverter
{
 public:
  StepFrameConverter(std::shared_ptr<tf2_ros::Buffer> tfBuffer);
  virtual ~StepFrameConverter();

  bool adaptCoordinates(StepQueue& stepQueue, const std::string& sourceFrameId,
                        const std::string& targetFrameId,
                        const Transform& transformInTargetFrame = Transform(),
                        const ros::Time& time = ros::Time(0));

  bool adaptCoordinates(Step& step, const std::string& sourceFrameId,
                        const std::string& targetFrameId,
                        const Transform& transformInTargetFrame = Transform(),
                        const ros::Time& time = ros::Time(0));

  bool adaptCoordinates(Footstep& footstep, const std::string& sourceFrameId,
                        const std::string& targetFrameId,
                        const Transform& transformInTargetFrame = Transform(),
                        const ros::Time& time = ros::Time(0));

 private:

  bool getTransform(const std::string& sourceFrameId, const std::string& targetFrameId,
                    const Transform& transformInTargetFrame, const ros::Time& time,
                    Transform& transform);

  /// TF buffer used to read the transformations.
  /// Note: Needs to be updated from outside with
  /// a TF Listener!
  std::shared_ptr<tf2_ros::Buffer> tfBuffer_;

  /// Cached transform for faster conversion.
  std::string cachedTargetFrameId_, cachedSourceFrameId_;
  ros::Time cachedTime_;
  Transform cachedTransformInTargetFrame_;
  Transform cachedTransform_;
};

} /* namespace free_gait */
