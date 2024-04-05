#pragma once

#include <cstdint>

struct FramebufferSpecification {
    uint32_t Width,Height;

    bool SwapChainTarget = false; // Render to screen
};

class Framebuffer {
public:
    Framebuffer(const FramebufferSpecification& spec);
    ~Framebuffer();

    void Bind() const;
    void Unbind() const;

    void Invalidate(); // Recreate framebuffer from specification

    void Resize(uint32_t width,uint32_t height);

    uint32_t GetColourAttachment() const { return m_ColourAttachment; }
    const FramebufferSpecification& GetSpecification() const { return m_Specification; }
private:
    FramebufferSpecification m_Specification;

    uint32_t m_RendererID = 0;
    uint32_t m_ColourAttachment = 0;
    uint32_t m_DepthAttachment = 0;
};