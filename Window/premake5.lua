project "Window"
	kind "StaticLib"
	language "C++"
	cppdialect "C++latest"
	staticruntime "on"
	
	targetdir ("%{wks.location}/bin/" .. outputDir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin/intermediates/" .. outputDir .. "/%{prj.name}")

	platform = 'win32'

	files { 
		"include/Window/*.hpp", 
		"src/*.cpp",
		"include/Window/" .. platform .. "/**.hpp",
		"src/" .. platform .. "/**.cpp"
	}

	flags {
		"FatalWarnings"
	}

	includedirs {
		"src",
		"include/Window/",
		"%{IncludeDir.VulkanSDK}",
		"%{IncludeDir.lud_utils}",
		"%{IncludeDir.imgui}",

	}

	filter "system:windows"
		systemversion "latest"
		defines {
			"WINDOW_PLATFORM_WINDOWS",
			"VK_USE_PLATFORM_WIN32_KHR"

		}
	

	filter "configurations:Debug"
		defines { 
			"WINDOW_DEBUG" 
		}
		runtime "debug"
		symbols "On"

	filter "configurations:Release"
		defines { 
			"WINDOW_NDEBUG" 
		}
		runtime "release"
		symbols "Off"
		optimize "On"

