/*
    SPDX-FileCopyrightText: 2025 KWin Authors

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "scene/scene.h"

#include <memory>
#include <vulkan/vulkan.h>

namespace KWin
{

class VulkanBuffer;
class VulkanContext;
class VulkanFramebuffer;
class VulkanRenderPass;
class VulkanTexture;
class Output;

class CursorDelegateVulkan final : public QObject, public SceneDelegate
{
    Q_OBJECT

public:
    CursorDelegateVulkan(Scene *scene, Output *output, VulkanContext *context);
    ~CursorDelegateVulkan() override;

    void paint(const RenderTarget &renderTarget, const QRegion &region) override;

private:
    Output *const m_output;
    VulkanContext *const m_context;

    std::unique_ptr<VulkanRenderPass> m_offscreenRenderPass;
    std::unique_ptr<VulkanFramebuffer> m_offscreenFramebuffer;

    // LOAD_OP_LOAD render pass for compositing the cursor onto the main framebuffer
    std::unique_ptr<VulkanRenderPass> m_overlayRenderPass;

    std::unique_ptr<VulkanBuffer> m_vertexBuffer;
    std::unique_ptr<VulkanBuffer> m_uniformBuffer;
    std::unique_ptr<VulkanTexture> m_defaultWhiteTexture;
};

} // namespace KWin
