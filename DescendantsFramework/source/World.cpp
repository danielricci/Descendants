#include "stdafx.h"
#include "World.h"

#include <boost/serialization/export.hpp>
BOOST_CLASS_EXPORT_GUID(World::World, "World");

World::World::World()
{

}

World::World::World(std::string fileName)
	:World()
{
	SetName(fileName);
}

World::World::~World()
{
	while (!_objects.empty()) delete _objects.back(), _objects.pop_back();
}

void World::World::Update(SDL_Event* e)
{
	for (auto object : _objects)
	{
		object->Update(e);
	}
}

void World::World::Render(SDL_Renderer* renderer)
{
	for (auto object : _objects)
	{
		if (object->RequiresLoad)
			object->SetTexture(_texturePath, renderer);
		object->Render(renderer);
	}
}

void World::World::AddObject(GameObject::GameObject* object)
{
	_objects.push_back(object);
}

void World::World::RemoveObject(GameObject::GameObject* object)
{
	DESCENDANT_UNUSED(object);
}
