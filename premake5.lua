outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
sdl3 = false
include "dependencies.lua"

workspace "AutoClicker"	
	architecture "x86_64"
	startproject "Application"

	configurations { 
		"Debug", 
		"Release"
	}

	ignoredefaultlibraries {
		"MSVCRT",
		"MSVCRTd",
		"MDd_DynamicDebug",
	}

	flags {
		"MultiProcessorCompile",
	}




group "Dependencies"
	include "vendor/premake"
	include "vendor/imgui"
group ""


group "Core"
	include "Application"
	include "Window"
	include "Input"
	include "Renderer"
group ""

group "Utility"
	include "FileManager"
group ""