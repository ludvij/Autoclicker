VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["VulkanSDK"]     = "%{wks.location}/%{VULKAN_SDK}/Include"
IncludeDir["glm"]           = "%{wks.location}/%{VULKAN_SDK}/Include"
IncludeDir["imgui"]         = "%{wks.location}/vendor/ImGui"
IncludeDir["lud_utils"]     = "%{wks.location}/vendor/lud_utils"
IncludeDir["vk_bootrstrap"] = "%{wks.location}/Renderer/vendor/vk_bootstrap"
IncludeDir["freetype"]      = "%{wks.location}/vendor/freetype/include"
IncludeDir["Renderer"]      = "%{wks.location}/Renderer/src"
IncludeDir["Input"]         = "%{wks.location}/Input/include"
IncludeDir["Window"]        = "%{wks.location}/Window/include"
IncludeDir["FileManager"]   = "%{wks.location}/FileManager/include"

LibraryDir = {}
LibraryDir["VulkanSDK"]  = "%{wks.location}/%{VULKAN_SDK}/Lib"
LibraryDir["gtest_d"]    = "%{wks.location}/NesEmu/vendor/gtest/lib/debug"
LibraryDir["gtest_r"]    = "%{wks.location}/NesEmu/vendor/gtest/lib/release"
LibraryDir["freetype_d"] = "%{wks.location}/vendor/freetype/lib/debug"
LibraryDir["freetype_r"] = "%{wks.location}/vendor/freetype/lib/release"

Library = {}
Library["Vulkan"]     = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
Library["gtest_d"]    = "%{LibraryDir.gtest_d}/gtest"
Library["gtest_r"]    = "%{LibraryDir.gtest_r}/gtest"
Library["freetype_r"] = "%{LibraryDir.freetype_r}/freetype"
Library["freetype_d"] = "%{LibraryDir.freetype_d}/freetype"

if (sdl3) then
	IncludeDir["sdl"]    = "%{wks.location}/vendor/sdl3/include"
	LibraryDir["sdl_d"]  = "%{wks.location}/vendor/sdl3/lib/Debug"
	LibraryDir["sdl_r"]  = "%{wks.location}/vendor/sdl3/lib/Release"
	Library["sdl_d"]     = "%{LibraryDir.sdl_d}/SDL3-static"
	Library["sdl_r"]     = "%{LibraryDir.sdl_r}/SDL3-static"
else
	IncludeDir["sdl"]    = "%{wks.location}/vendor/sdl2/include"
	LibraryDir["sdl_d"]  = "%{wks.location}/vendor/sdl2/lib/debug"
	LibraryDir["sdl_r"]  = "%{wks.location}/vendor/sdl2/lib/release"
	Library["sdl_d"]     = "%{LibraryDir.sdl_d}/SDL2-staticd"
	Library["sdl_r"]     = "%{LibraryDir.sdl_r}/SDL2-static"
end
