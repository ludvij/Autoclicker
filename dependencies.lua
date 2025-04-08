VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["VulkanSDK"]     = "%{wks.location}/%{VULKAN_SDK}/Include"
IncludeDir["glm"]           = "%{wks.location}/%{VULKAN_SDK}/Include"
IncludeDir["imgui"]         = "%{wks.location}/vendor/ImGui"
IncludeDir["lud_utils"]     = "%{wks.location}/lud_utils/include"
IncludeDir["vk_bootrstrap"] = "%{wks.location}/Renderer/vendor/vk_bootstrap"
IncludeDir["freetype"]      = "%{wks.location}/vendor/freetype/include"
IncludeDir["Renderer"]      = "%{wks.location}/Renderer/src"
IncludeDir["Input"]         = "%{wks.location}/Input/include"
IncludeDir["Window"]        = "%{wks.location}/Window/include"
IncludeDir["FileManager"]   = "%{wks.location}/FileManager/include"

LibraryDir = {}
LibraryDir["VulkanSDK"]  = "%{wks.location}/%{VULKAN_SDK}/Lib"
LibraryDir["freetype_d"] = "%{wks.location}/vendor/freetype/lib/debug"
LibraryDir["freetype_r"] = "%{wks.location}/vendor/freetype/lib/release"

Library = {}
Library["Vulkan"]     = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
Library["freetype_r"] = "%{LibraryDir.freetype_r}/freetype"
Library["freetype_d"] = "%{LibraryDir.freetype_d}/freetype"
