#ifndef FUTUROLANDDEV_VULKAN_DRAW_COMMAND_H
#define FUTUROLANDDEV_VULKAN_DRAW_COMMAND_H

#include "vulkan_func.h"
#include "vulkan_render_command.h"

class VulkanDrawCommand: VulkanRenderCommand {
private:
    Model3D *model3D;
    void createBuffers();
public:
    void cmd(VkCommandBuffer cmd_buff) override;
    VulkanDrawCommand(int instanceCount,Model3D);
};


#endif //FUTUROLANDDEV_VULKAN_DRAW_COMMAND_H
