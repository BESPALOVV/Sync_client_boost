
add_executable (client  "client.h" "client.cpp"  "main.cpp")

find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

link_libraries(${Boost_LIBRARIES})
