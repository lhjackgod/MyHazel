project "SandBox"
	kind "ConsoleApp"
    language "C++"
    staticruntime "on"
    cppdialect "C++17"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "src/**.h",
        "src/**.cpp"
    }
    includedirs
    {
        "%{wks.location}/MyHazel/vendor/spdlog/include",
        "%{wks.location}/MyHazel/src",
		"%{wks.location}/MyHazel/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}"
    }
    links
    {
        "MyHazel"
    }
    filter "system:windows"
		systemversion "latest"
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