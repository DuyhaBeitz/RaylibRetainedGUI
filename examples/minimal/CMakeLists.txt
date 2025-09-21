#find_package(RaylibRetainedGUI)
add_executable(minimal minimal.cpp)
target_link_libraries(minimal PRIVATE RaylibRetainedGUI)