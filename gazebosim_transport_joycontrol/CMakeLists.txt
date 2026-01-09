cmake_minimum_required(VERSION 3.28.3) # the current version used in this project
project(gazebosim_transport_joycontrol)


  find_package(gz-transport QUIET REQUIRED OPTIONAL_COMPONENTS log)

  find_package(sdformat REQUIRED)
 
add_executable(joypub src/joystick.cpp)
add_executable(joysub src/joysub.cpp)

target_link_libraries(joysub
    gz-transport::core
   
    )

target_link_libraries(joypub
    gz-transport::core
   
    )


