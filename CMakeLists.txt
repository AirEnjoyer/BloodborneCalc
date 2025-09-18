cmake_minimum_required(VERSION 3.25)


project(BloodborneDB C)


set(CMAKE_C_STANDARD 99)


add_executable(BloodborneDB 
        main.c
        weapon_data.c
        damage.c)

target_link_libraries(BloodborneDB m)
