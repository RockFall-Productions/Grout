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

project "Grout"
	location "Grout"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/third-part/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"GRT_PLATAFORM_WINDOWS",
			"GRT_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ..\\bin\\" .. outputdir ..  "\\Sandbox")
		}
	
	filter "configurations:Debug"
		defines "GRT_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "GRT_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "GRT_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		"Grout/src"
	}

	links
	{
		"Grout"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"GRT_PLATAFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "GRT_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "GRT_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "GRT_DIST"
		optimize "On"