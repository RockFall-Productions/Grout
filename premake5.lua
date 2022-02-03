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
IncludeDir["GLFW"] = "%{wks.location}/Grout/third-part/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/Grout/third-part/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/Grout/third-part/imgui"
IncludeDir["glm"] = "%{wks.location}/Grout/third-part/glm"
IncludeDir["stb"] = "%{wks.location}/Grout/third-part/stb"
IncludeDir["assimp"] = "%{wks.location}/Grout/third-part/assimp/include"
IncludeDir["imGuIZMO"] = "%{wks.location}/Grout/third-part/imgui/widgets/imGuIZMO"

-- Includes the GLFW and GLAD premake5's files
group "Dependencies"
	include "Grout/third-part/GLFW"
	include "Grout/third-part/Glad"
	include "Grout/third-part/imgui"
	include "Grout/third-part/assimp"
	include "Grout/third-part/imgui/widgets/imGuIZMO"
group ""

project "Grout"
	location "Grout"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "grtpch.h"
	pchsource "Grout/src/grtpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/third-part/stb/stb_image.h",
		"%{prj.name}/third-part/stb/stb_image.cpp",
		"%{prj.name}/third-part/glm/glm/**.hpp",
		"%{prj.name}/third-part/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLM_ENABLE_EXPERIMENTAL"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/third-part/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb}",
		"%{IncludeDir.assimp}",
		"%{IncludeDir.imGuIZMO}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib",
		"assimp",
		"imGuIZMO"
	}

	disablewarnings  {
		"26451"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"GRT_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "GRT_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "GRT_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "GRT_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"Grout/third-part",
		"%{IncludeDir.glm}",
		"%{IncludeDir.assimp}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.imGuIZMO}"
	}

	links
	{
		"Grout"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "GRT_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "GRT_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "GRT_DIST"
		runtime "Release"
		optimize "on"
