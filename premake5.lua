workspace "MyHazel"
    architecture "x64"
    configurations{
        "Debug",
        "Release",
        "Dist"
    }
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "MyHazel"
    location "MyHazel"
    kind "SharedLib"
    language "C++"
    targetdir ("bin/" ..outputdir.. "/%{prj.name}")
    objdir ("bin-int/" ..outputdir.. "/%{prj.name}")
    pchheader "hzpch.h"
	pchsource "MyHazel/src/hzpch.cpp"
    files{
        "{%prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }
    
    includedirs{
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines{
            "HZ_PLATFORM_WINDOWS",
            "HZ_BUILD_DLL"
        }
        postbuildcommands{
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" ..outputdir.. "/SandBox")
        }
    filter "configurations:Debug"
        defines "HZ_DEBUG"
        symbols "On"
    filter "configurations:Release"
        defines "HZ_RELEASE"
        optimize "On"
    filter "configurations:Dist"
        defines "HZ_DIST"
        optimize "On"

project "SandBox"
        location "SandBox"
        kind "ConsoleApp"
        language "C++"

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
            staticruntime "On"
            systemversion "latest"

            defines{
                "HZ_PLATFORM_WINDOWS"
            }

        filter "configurations:Debug"
            defines "HZ_DEBUG"
            symbols "On"

        filter "configurations:Release"
            defines "HZ_RELEASE"
            optimize "On"

        filter "configurations:Dist"
            defines "HZ_DIST"
            optimize "On"

