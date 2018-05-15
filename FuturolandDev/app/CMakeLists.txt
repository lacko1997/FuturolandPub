cmake_minimum_required(VERSION 3.4.1)

add_library( native-lib
             SHARED
             src/main/cpp/graphics_module.cpp)

add_library( vulkan_module
             SHARED
             src/main/cpp/vulkan_func.cpp
             src/main/cpp/vulkan_base.cpp
             src/main/cpp/vulkan_render_surface.cpp
             src/main/cpp/vulkan_render_command.cpp
             src/main/cpp/vulkan_commands.cpp
             src/main/cpp/vulkan_module.cpp)


find_library( log-lib
              log )
target_link_libraries( native-lib
                       vulkan_module
                       android
                       ${log-lib} )