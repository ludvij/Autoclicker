project "Application"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++latest"
	staticruntime "on"
	targetdir ("%{wks.location}/bin/" .. outputDir .. "/%{prj.name}")
	targetname ("emoo")
	objdir ("%{wks.location}/bin/intermediates/" .. outputDir .. "/%{prj.name}")

	files { 
		"src/**.hpp", 
		"src/**.h", 
		"src/**.cpp",

		"src/**.embed",

		"assets/resource.rc"
	}

	flags {
	}



	includedirs {
		"src",
		"%{IncludeDir.sdl}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.VulkanSDK}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.lud_utils}",
		"%{IncludeDir.vk_bootrstrap}",

		"%{IncludeDir.Input}",
		"%{IncludeDir.Window}",
		"%{IncludeDir.Renderer}",
		"%{IncludeDir.FileManager}",
	}


	links {
		"ImGui",
		"Input",
		"Window",
		"FileManager",
		"Renderer",
		"%{Library.Vulkan}",
		-- sdl complains
		"winmm",
		"setupapi",
		"version",
		"Imm32"
	}

	defines {
		"SDL_MAIN_HANDLED",
		"IMGUI_DEFINE_MATH_OPERATORS"
	}

	filter "system:windows"
		systemversion "latest"
		defines {
			"NES_EMU_PLATFORM_WINDOWS",
			"WIN32",
		}
		
	

	filter "configurations:Debug"
		defines { 
			"GRAPHICS_DEBUG",
			"TRACE_UUID_LIFETIMES",
		}
		runtime "debug"
		symbols "On"

		links {
			"%{Library.freetype_d}",
			"%{Library.sdl_d}",
		}
	
	filter "configurations:Release"
		kind "WindowedApp"
		defines { 
			"GRAPHICS_NDEBUG",
			"NDEBUG"
		}
		links {
			"%{Library.freetype_r}",
			"%{Library.sdl_r}",
		}

		runtime "release"
		optimize "On"



	