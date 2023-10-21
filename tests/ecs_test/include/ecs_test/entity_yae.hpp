#pragma once


namespace quick3d::test
{
	class YaeEntity : public quick3d::core::Entity
	{
	public:
		YaeEntity() = default;
		YaeEntity(YaeEntity&) = delete;
		~YaeEntity() = default;
	};
}