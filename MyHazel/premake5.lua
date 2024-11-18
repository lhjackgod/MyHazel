project "MyHazel"
    location "MyHazel"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")

    pchheader "hzpch.h"
    pchsource "src/hzpch.cpp"
    files
    {
        "src/**.h",
        "src/**.cpp",
        "vendor/glm/glm/**.hpp",
        "vendor/glm/glm/**.inl",
        "vendor/stb_image/**.h",
        "vendor/stb_image/**.cpp"
    }
    defines
    {
        "_CRT_SECURE_NO_WARNINGS",
        "GLFW_INCLUDE_NONE"
    }
    includedirs
    {
        "src",
        "vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLAD}",
        "%{IncludeDir.imgui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.entt}"
    }
    links
    {
        "ImGui",
        "Glad",
        "GLFW",
        "opengl32.lib"
    }
    filter "system:windows"
        systemversion "latest"
        defines
        {

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