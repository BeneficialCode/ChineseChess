#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glad/glad.h>

Texture::Texture(int32_t width, int32_t height) : m_Width(width), m_Height(height) {
    glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
    glTextureStorage2D(m_TextureID, 1, GL_RGBA8, m_Width, m_Height);
    // 缩小纹理时的纹理过滤为线性过滤
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // 放大纹理时的过滤方式为线性过滤
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 纹理坐标X会被约束在0-1之间，超出的部分会重复纹理坐标的边缘,产生一种边缘被拉伸的效果
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    // 纹理坐标Y会被约束在0-1之间，超出的部分会重复纹理坐标的边缘,产生一种边缘被拉伸的效果
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

Texture::Texture(const uint8_t* data, int32_t width, int32_t height) : m_Width(width), m_Height(height) {
    glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
    glTextureStorage2D(m_TextureID, 1, GL_RGBA8, m_Width, m_Height);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, GL_RGBA, GL_UNSIGNED_BYTE, data);
}

Texture::Texture(const std::filesystem::path& image) {
    stbi_set_flip_vertically_on_load(1);
    uint8_t* data = stbi_load(image.u8string().c_str(), &m_Width, &m_Height, &m_BBP, 4);

    glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
    glTextureStorage2D(m_TextureID, 1, GL_RGBA8, m_Width, m_Height);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, GL_RGBA, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
}

Texture::Texture(const uint8_t* pngData, size_t size) {
    stbi_set_flip_vertically_on_load(1);
    uint8_t* data = stbi_load_from_memory(pngData, (int)size, &m_Width, &m_Height, &m_BBP, 4);

    glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
    glTextureStorage2D(m_TextureID, 1, GL_RGBA8, m_Width, m_Height);

    // 纹理图片又分辨率不够高的时候，就需要通过设置纹理过滤让纹理看起来更适合你要表现的效果
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, GL_RGBA, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
}

Texture::~Texture() {
    glDeleteTextures(1, &m_TextureID);
}

void Texture::Bind(uint32_t slot) {
    m_Slot = slot;
    glBindTextureUnit(slot, m_TextureID);
}

void Texture::SetData(void* data) {
    glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, GL_RGBA, GL_UNSIGNED_BYTE, data);
}
