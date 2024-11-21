#include "hzpch.h"
#include "Hazel/Math/Math.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>
namespace Hazel::Math
{
	bool DecomposeTransform(const glm::mat4& transform, glm::vec3& outTranslation, glm::vec3& outRotation, glm::vec3& outScale)
	{
		using namespace glm;
		using T = float;

		mat4 LocationMatrix(transform);
		if (epsilonEqual(LocationMatrix[3][3], static_cast<float>(0), epsilon<T>()))
			return false;
		if (
			epsilonNotEqual(LocationMatrix[0][3], static_cast<float>(0), epsilon<T>()) ||
			epsilonNotEqual(LocationMatrix[1][3], static_cast<float>(0), epsilon<T>()) ||
			epsilonNotEqual(LocationMatrix[2][3], static_cast<float>(0), epsilon<T>())
			)
		{
			LocationMatrix[0][3] = LocationMatrix[1][3] = LocationMatrix[2][3] = static_cast<T>(0);
			LocationMatrix[3][3] = static_cast<T>(1);
		}
		outTranslation = vec3(LocationMatrix[3]);
		LocationMatrix[3] = vec4(0, 0, 0, LocationMatrix[3].w);
		vec3 Row[3], Pdum3;
		for (length_t i = 0; i < 3; i++)
		{
			for (length_t j = 0; j < 3; j++)
			{
				Row[i][j] = LocationMatrix[i][j];
			}
		}
		outScale.x = length(Row[0]);
		Row[0] = detail::scale(Row[0], static_cast<T>(1));
		outScale.y = length(Row[1]);
		Row[1] = detail::scale(Row[1], static_cast<T>(1));
		outScale.z = length(Row[2]);
		Row[2] = detail::scale(Row[2], static_cast<T>(1));
		outScale.z = length(Row[2]);
#if 0
		Pdum3 = cross(Row[1], Row[2]); // v3Cross(row[1], row[2], Pdum3);
		if (dot(Row[0], Pdum3) < 0)
		{
			for (length_t i = 0; i < 3; i++)
			{
				scale[i] *= static_cast<T>(-1);
				Row[i] *= static_cast<T>(-1);
			}
		}
#endif
		outRotation.y = asin(-Row[0][2]);
		if (cos(outRotation.y) != 0) {
			outRotation.x = atan2(Row[1][2], Row[2][2]);
			outRotation.z = atan2(Row[0][1], Row[0][0]);
		}
		else {
			outRotation.x = atan2(-Row[2][0], Row[1][1]);
			outRotation.z = 0;
		}
		
		return true;
	}
}