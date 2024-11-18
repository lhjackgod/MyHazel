#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Hazel/Scene/SceneCamera.h"
#include "Hazel/Scene/ScriptableEntity.h"
namespace Hazel {
	struct NativeScriptComponent
	{
		ScriptableEntity* Instance = nullptr;

		ScriptableEntity* (*InstantiateScript)();
		void (*DestroyScript) (NativeScriptComponent*);
		template<typename T>
		void Bind()
		{
			InstantiateScript = []() {return static_cast<ScriptableEntity*>(new T()); };

			DestroyScript = [](NativeScriptComponent* nsc) {delete nsc->Instance; nsc->Instance = nullptr; };
		}
	};
	struct CameraComponent
	{
		bool Primary = true;
		bool FIxedApectRatio = false;
		SceneCamera Camera;
		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};
	struct TagComponent
	{
		std::string Tag;
		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			:Tag(tag) {}
	};
	struct TransformComponent
	{
		glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };
		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3& translation)
			:Translation(translation){}
		glm::mat4 GetTransform() const
		{
			HZ_CORE_INFO("x: {0}, y {1} z {2} ", Rotation.x, Rotation.y, Rotation.z);
			glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), Rotation.x, glm::vec3(1, 0, 0)) *
				glm::rotate(glm::mat4(1.0f), Rotation.y, { 0, 1, 0 }) *
				glm::rotate(glm::mat4(1.0f), Rotation.z, { 0, 0, 1 });
			return glm::translate(glm::mat4(1.0f), Translation)
					* rotation
					* glm::scale(glm::mat4(1.0f), Scale);
		}
	};
	struct SpriteRendererComponent
	{
		glm::vec4 Color{ 1.0f,1.0f,1.0f,1.0f };

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color)
			:Color(color){}
	};
}