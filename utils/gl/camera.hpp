#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/fwd.hpp"
#include "../template.hpp"
#include "../physics/common.hpp"

namespace ni::opengl
{
	struct ViewMatrix : public utils::__Enchased<glm::mat4>
	{
		ViewMatrix(const glm::mat4& matrix = glm::mat4(1.0f)) : __Enchased(matrix) {}	
	};

	struct ProjMatrix : public utils::__Enchased<glm::mat4>
	{
		ProjMatrix(const glm::mat4& matrix = glm::mat4(1.0f)) : __Enchased(matrix) {}	
	};

	struct CamNearDistance : public utils::__Enchased<float>
	{
		CamNearDistance(const float& f = 0.01f) : __Enchased(f) {}
	};

	struct CamFarDistance : public utils::__Enchased<float>
	{
		CamFarDistance(const float& f = 20000.0f) : __Enchased(f) {}
	};

	struct CamFiledOfView : public utils::__Enchased<float>
	{
		CamFiledOfView(const float& f = 45.0f) : __Enchased(f) {}
	};

	struct CamAperture : public utils::__Enchased<float>
	{
		CamAperture(const float& f = 0.1f) : __Enchased(f) {}
	};

	struct CamFocalPlaneDistance : public utils::__Enchased<float>
	{
		CamFocalPlaneDistance(const float& f = 2.0f) : __Enchased(f) {}
	};

	struct CamDepthOfFiled : public utils::__Enchased<float>
	{
		CamDepthOfFiled(const float& f = -1.0f) : __Enchased(f) {}
	};

	struct CamLodCenter : public utils::__Enchased<glm::vec3>
	{
		CamLodCenter(const glm::vec3& vec = glm::vec3(0.0f,0.0f,-1.0f)) : __Enchased(vec) {}
	};

	struct CamLodFront : public utils::__Enchased<glm::vec3>
	{
		CamLodFront(const glm::vec3& vec = glm::vec3(0.0f,0.0f,1.0f)) : __Enchased(vec) {}
	};

	struct CamLodUp : public utils::__Enchased<glm::vec3>
	{
		CamLodUp(const glm::vec3& vec = glm::vec3(0.0f,1.0f,0.0f)) : __Enchased(vec) {}
	};

	struct CamNeedSync : public utils::__Enchased<bool>
	{
		CamNeedSync(const bool& b = false) : __Enchased(b) {}
	};

	class Camera
	{
	private:
		ViewMatrix view;
		ProjMatrix proj;
		CamNearDistance near;
		CamFarDistance far;
		CamFiledOfView fov;
		CamAperture aperture;
		CamFocalPlaneDistance focalPlaneDistance;
		CamDepthOfFiled dof;
		CamLodCenter lodCenter;
		CamLodFront lodFront;
		CamLodUp lodUp;
		CamNeedSync needSync;
		utils::Point point;

	public:
		Camera();

		template <typename T>
		const T& get() const
		{
			if constexpr (utils::anySame<T,utils::AxisCoordinateX,utils::AxisCoordinateY,utils::AxisCoordinateZ>())
				return point.get<T>();
			else if constexpr (utils::isSame<T,ViewMatrix>())
				return view;
			else if constexpr (utils::isSame<T,ProjMatrix>())
				return proj;
			else if constexpr (utils::isSame<T,CamNearDistance>())
				return near;
			else if constexpr (utils::isSame<T,CamFarDistance>())
				return far;
			else if constexpr (utils::isSame<T,CamFiledOfView>())
				return fov;
			else if constexpr (utils::isSame<T,CamAperture>())
				return aperture;
			else if constexpr (utils::isSame<T,CamFocalPlaneDistance>())
				return focalPlaneDistance;
			else if constexpr (utils::isSame<T,CamDepthOfFiled>())
				return dof;
			else if constexpr (utils::isSame<T,CamLodCenter>())
				return lodCenter;
			else if constexpr (utils::isSame<T,CamLodFront>())
				return lodFront;
			else if constexpr (utils::isSame<T,CamLodUp>())
				return lodUp;
		}
	};
}