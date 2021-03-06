cmake_minimum_required(VERSION 3.4.1)

add_library( native-lib
             SHARED
             src/main/cpp/native-lib.cpp
             src/main/cpp/graphics_module.cpp
             src/main/cpp/model_library.cpp)

add_library( vulkan_module
             SHARED
             src/main/cpp/vulkan_func.cpp
             src/main/cpp/vulkan_base.cpp
             src/main/cpp/vulkan_render_surface.cpp
             src/main/cpp/vulkan_commands.cpp
             src/main/cpp/vulkan_normal_pipeline.cpp
             src/main/cpp/vulkan_descriptors.cpp
             src/main/cpp/vulkan_sampler.cpp
             src/main/cpp/vulkan_uniform_buffer.cpp
             src/main/cpp/vulkan_vertex_buffer.cpp
             src/main/cpp/vulkan_module.cpp)


find_library( log-lib
              log )

target_link_libraries( vulkan_module
                       android
                       ${log-lib} )

target_link_libraries( native-lib
                       vulkan_module
                       android
                       ${log-lib} )