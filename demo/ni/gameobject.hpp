#pragma once

#include "physical.hpp"

namespace flat::ni
{
	class DrawableObject : public Plane
	{
	private:
		GLuint vao;
		void makeupArrayObject();

	public:
		DrawableObject();
		~DrawableObject();

		GLuint getArrayObjectID() { return vao; }
	};

	class AudioObject : public MassPoint
	{
	private:
		ALuint sourceID;

	public:
		AudioObject();
		~AudioObject();

		ALuint getSourceID() { return sourceID; }
	};

	/*
	class GameObject : virtual public AudioObject, virtual public DrawableObject
	{

	};
	*/
}