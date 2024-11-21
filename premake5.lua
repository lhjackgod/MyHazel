include "./vendor/premake/premake_customization/solution_items.lua"
workspace "MyHazel"
    architecture "x86_64"
    startproject "Hazelnut"
    configurations{
        "Debug",
        "Release",
        "Dist"
    }
    solution_items
	{
		".editorconfig"
	}
    flags
	{
		"MultiProcessorCompile"
	}
    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    IncludeDir = {}
    IncludeDir["GLFW"] = "%{wks.location}/MyHazel/vendor/GLFW/include"
    IncludeDir["GLAD"] = "%{wks.location}/MyHazel/vendor/GLAD/include"
    IncludeDir["imgui"] = "%{wks.location}/MyHazel/vendor/imgui"
    IncludeDir["glm"] = "%{wks.location}/MyHazel/vendor/glm"
    IncludeDir["stb_image"] = "%{wks.location}/MyHazel/vendor/stb_image"
    IncludeDir["entt"] = "%{wks.location}/MyHazel/vendor/entt/include"
    IncludeDir["yaml_cpp"] = "%{wks.location}/MyHazel/vendor/yaml/include"
    IncludeDir["ImGuizmo"] = "%{wks.location}/MyHazel/vendor/ImGuizmo"
    group "Denpendencies"
        include "vendor/premake"
        include "MyHazel/vendor/GLFW"
        include "MyHazel/vendor/GLAD"
        include "MyHazel/vendor/imgui"
        include "MyHazel/vendor/yaml"
    group ""
    include "MyHazel"
    include "SandBox"
    include "Hazelnut"