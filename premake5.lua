workspace "Grout"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Solution include directories
IncludeDir = {}
IncludeDir["GLFW"] = "Grout/third-part/GLFW/include"
IncludeDir["Glad"] = "Grout/third-part/Glad/include"
IncludeDir["ImGui"] = "Grout/third-part/imgui"
IncludeDir["glm"] = "Grout/third-part/glm"

-- Includes the GLFW and GLAD premake5's files
group "Dependencies"
	include "Grout/third-part/GLFW"
	include "Grout/third-part/Glad"
	include "Grout/third-part/imgui"
group ""

project "Grout"
	location "Grout"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "grtpch.h"
	pchsource "Grout/src/grtpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/third-part/glm/glm/**.hpp",
		"%{prj.name}/third-part/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/third-part/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"GRT_PLATAFORM_WINDOWS",
			"GRT_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir ..  "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "GRT_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "GRT_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "GRT_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Grout/third-part/spdlog/include",
		"Grout/src",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Grout"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"GRT_PLATAFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "GRT_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "GRT_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "GRT_DIST"
		runtime "Release"
		optimize "On"
