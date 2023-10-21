#pragma once

namespace quick3d::test
{
	class SkyboxEntity : public quick3d::core::Entity
	{
	public:
		SkyboxEntity() = default;
		SkyboxEntity(SkyboxEntity&) = delete;
		~SkyboxEntity() = default;
	};
}