workspace "Labyrinth"
    architecture "x64"
    targetdir "build"
    startproject "Labyrinth"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" 

-- Include directories relative to solution directory
includeDir = {}
includeDir["SDL2"] = "Cretaceous/vendor/SDL2"
includeDir["glm"] = "Cretaceous/vendor/glm"

project "Labyrinth"
    location "Labyrinth"
	kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
	staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("intermediate/" .. outputdir .. "/%{prj.name}")

    files
	{
		"%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp" --,
        -- "%{prj.name}/vendor/SDL2/include/**.h"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/SDL2/include",
        "%{prj.name}/vendor/glm"
    }

    links 
	{  
		"Labyrinth/vendor/SDL2/lib/x64/SDL2.lib"
	}

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "LABYRINTH_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
		defines "LABYRINTH_DEBUG"
		runtime "Debug"
		symbols "on"

    filter "configurations:Release"
		defines "LABYRINTH_RELEASE"
		runtime "Release"
		optimize "on"

    filter "configurations:Dist"
		defines "LABYRINTH_DIST"
		runtime "Release"
		optimize "on"
 