#include "hzpch.h"
#include "SceneCamera.h"
#include <glm/gtc/matrix_transform.hpp>
namespace Hazel {
	SceneCamera::SceneCamera()
	{
		RecalculateProjection();
	}
	void SceneCamera::SetOrthographic(float size, float nearClip, float farClip)
	{
		m_OrthographicSize = size;
		m_OrthographicNear = nearClip;
		m_OrthographicFar = farClip;
		RecalculateProjection();
	}
	void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
	{
		m_AspectRatio = static_cast<float>(width) / static_cast<float>(height);
		RecalculateProjection();
	}
	void SceneCamera::RecalculateProjection()
	{
		float orthoLeft = -m_AspectRatio * m_OrthographicSize * 0.5;
		float orthoRight = m_AspectRatio * m_OrthographicSize * 0.5;
		float orthoBottom = -m_OrthographicSize * 0.5;
		float orthoTop = m_OrthographicSize * 0.5;

		m_Projection = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop);
	}
}



