find_package(OpenCV REQUIRED)

add_library(Utilities SHARED Utilities.cpp)

add_library(RobotSimulator SHARED RobotSimulator.cpp)
target_link_libraries(RobotSimulator
  Utilities
  ${OpenCV_LIBS})

add_executable(main main.cpp)
target_link_libraries(main
  Utilities
  RobotSimulator
  ${OpenCV_LIBS}
  )
