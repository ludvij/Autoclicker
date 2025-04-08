#include "Texture.hpp"

#include <imgui.h>

#include <ludutils/lud_assert.hpp>

ImTextureID Renderer::ITexture::ToImGui() const
{
	// not implemented
	Lud::assert::that(false, "Unimplemented");
	return nullptr;
}
