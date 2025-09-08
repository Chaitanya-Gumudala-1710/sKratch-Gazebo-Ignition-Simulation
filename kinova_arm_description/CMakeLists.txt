cmake_minimum_required(VERSION 3.5.1)
project(kinova_arm_description)

find_package(ament_cmake REQUIRED)


install(DIRECTORY description meshes
	DESTINATION share/${PROJECT_NAME}/)

ament_package()