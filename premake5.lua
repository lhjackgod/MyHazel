workspace "MyHazel"
    architecture "x64"
    startproject "SandBox"
    configurations{
        "Debug",
        "Release",
        "Dist"
    }
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
IncludeDir = {}
IncludeDir["GLFW"] = "MyHazel/vendor/GLFW/include"
IncludeDir["GLAD"] = "MyHazel/vendor/GLAD/include"
IncludeDir["imgui"] = "MyHazel/vendor/imgui"
include "MyHazel/vendor/GLFW"
include "MyHazel/vendor/GLAD"
include "MyHazel/vendor/imgui"


project "MyHazel"
    location "MyHazel"
    kind "SharedLib"
    language "C++"
    staticruntime "off"
    targetdir ("bin/" ..outputdir.. "/%{prj.name}")
    objdir ("bin-int/" ..outputdir.. "/%{prj.name}")
    pchheader "hzpch.h"
	pchsource "MyHazel/src/hzpch.cpp"
    files{
        "{%prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }
    
    includedirs{
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLAD}",
        "%{IncludeDir.imgui}"
    }
    links {
        "ImGui",
        "Glad",
        "GLFW",
        "opengl32.lib"
    }
    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines{
            "HZ_PLATFORM_WINDOWS",
            "HZ_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }
        postbuildcommands{
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" ..outputdir.. "/SandBox")
        }
    filter "configurations:Debug"
        defines "HZ_DEBUG"
        
        runtime "Debug"
        symbols "On"
    filter "configurations:Release"
        defines "HZ_RELEASE"
        runtime "Release"
        optimize "On"
    filter "configurations:Dist"
        defines "HZ_DIST"
        runtime "Release"
        optimize "On"

project "SandBox"
        location "SandBox"
        kind "ConsoleApp"
        language "C++"
        staticruntime "off"
        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

        files{
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp"
        }
        -- 同样包含spdlog头文件
        includedirs{
            "MyHazel/vendor/spdlog/include",
            "MyHazel/src"
        }
        -- 引用hazel
        links{
            "MyHazel"
        }

        filter "system:windows"
            cppdialect "C++17"
            
            systemversion "latest"

            defines{
                "HZ_PLATFORM_WINDOWS"
            }

        filter "configurations:Debug"
            defines "HZ_DEBUG"
            runtime "Debug"
            symbols "On"

        filter "configurations:Release"
            defines "HZ_RELEASE"
            runtime "Release"
            optimize "On"

        filter "configurations:Dist"
            defines "HZ_DIST"
            runtime "Release"
            optimize "On"

