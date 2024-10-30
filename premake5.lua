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
IncludeDir["glm"] = "MyHazel/vendor/glm"
include "MyHazel/vendor/GLFW"
include "MyHazel/vendor/GLAD"
include "MyHazel/vendor/imgui"


project "MyHazel"
    location "MyHazel"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    targetdir ("bin/" ..outputdir.. "/%{prj.name}")
    objdir ("bin-int/" ..outputdir.. "/%{prj.name}")
    pchheader "hzpch.h"
	pchsource "MyHazel/src/hzpch.cpp"
    files{
        "{%prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl"
    }
    defines{
        "_CRT_SECURE_NO_WARNINGS"
    }
    includedirs{
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLAD}",
        "%{IncludeDir.imgui}",
        "%{IncludeDir.glm}"
    }
    links {
        "ImGui",
        "Glad",
        "GLFW",
        "opengl32.lib"
    }
    filter "system:windows"

        systemversion "latest"

        defines{
            "HZ_PLATFORM_WINDOWS",
            "HZ_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }
        
    filter "configurations:Debug"
        defines "HZ_DEBUG"
        
        runtime "Debug"
        symbols "on"
    filter "configurations:Release"
        defines "HZ_RELEASE"
        runtime "Release"
        optimize "on"
    filter "configurations:Dist"
        defines "HZ_DIST"
        runtime "Release"
        optimize "on"

project "SandBox"
        location "SandBox"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"
        staticruntime "on"
        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

        files{
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp"
        }
        -- 同样包含spdlog头文件
        includedirs{
            "MyHazel/vendor/spdlog/include",
            "MyHazel/src",
            "%{IncludeDir.glm}",
            "MyHazel/vendor"
        }
        -- 引用hazel
        links{
            "MyHazel"
        }

        filter "system:windows"

            
            systemversion "latest"

            defines{
                "HZ_PLATFORM_WINDOWS"
            }

        filter "configurations:Debug"
            defines "HZ_DEBUG"
            runtime "Debug"
            symbols "on"

        filter "configurations:Release"
            defines "HZ_RELEASE"
            runtime "Release"
            optimize "on"

        filter "configurations:Dist"
            defines "HZ_DIST"
            runtime "Release"
            optimize "on"

