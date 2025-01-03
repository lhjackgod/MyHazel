#pragma once
#include "Hazel/Core/Base.h"
namespace Hazel{
    enum class FrambufferTextureFormat
    {
        None = 0,

        //color 
        RGBA8,
        RED_INTEHER,
        //Depth/stencil
        DEPTH24STENCIL8,

        //Defaults

        Depth = DEPTH24STENCIL8
    };

    struct FramebufferTextureSpecification
    {
        FramebufferTextureSpecification() = default;
        FramebufferTextureSpecification(FrambufferTextureFormat format)
            :TextureFormat(format) {}
        FrambufferTextureFormat TextureFormat = FrambufferTextureFormat::None;
    };
    
    struct FrambufferAttachmentSpecification
    {
        FrambufferAttachmentSpecification() = default;
        FrambufferAttachmentSpecification(std::initializer_list<FramebufferTextureSpecification> attachments)
            : Attachments(attachments) {}
        std::vector<FramebufferTextureSpecification> Attachments;
    };

    struct FramebufferSpecification
    {   
        FrambufferAttachmentSpecification Attachments;
        uint32_t width = 0, height = 0;
        uint32_t Samples = 1;
        bool SwapChainTarget = false;
    };
    class Framebuffer{
    public:
        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual void Resize(uint32_t width, uint32_t height) = 0;
        virtual void ClearAttachment(uint32_t attachmentIndex, int value) = 0;
        virtual int ReadPixel(uint32_t attachement, int x, int y) = 0;
        virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const = 0;
        virtual const FramebufferSpecification& GetSpecification() const = 0;
        static Ref<Framebuffer> Create(const FramebufferSpecification& spec);
    };
}

