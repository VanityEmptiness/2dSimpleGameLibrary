//Collision is handled with a simple AABB, rotation is not considered (for now)
#pragma once
#include "../../Utils/Math.h"

#include <string>
#include <map>
#include <vector>

class ColliderBox
{
public:
	Vec2 position;
	Vec2 dimensions;
	const std::string name;
	bool is_collider_physics_enabled = false;

	ColliderBox(){}
	ColliderBox(const std::string& name, const Vec2& position, const Vec2& dimensions) 
		: name{ name }, position{ position }, dimensions{ dimensions } 
	{
	}
	~ColliderBox(){}

private:
	
};

class CollisionComponent
{
public:
	bool is_colliding = false;
	std::map<std::string, std::vector<std::string>> collision_list;

	CollisionComponent(){}
	~CollisionComponent(){}

	inline bool AddCollider(const std::string& collider_name, const Vec2& position, const Vec2& dimensions) noexcept
	{
		if (this->colliders_box_map.contains(collider_name))
			return false;
		this->colliders_box_map.insert({ collider_name , ColliderBox(collider_name, position, dimensions) });
		return true;
	}

	inline bool RemoveCollider(const std::string& collider_name) noexcept
	{
		if (!this->colliders_box_map.contains(collider_name))
			return false;
		this->colliders_box_map.erase(collider_name);
		return true;
	}

	inline ColliderBox* GetCollider(const std::string& collider_name) noexcept
	{
		if (!this->colliders_box_map.contains(collider_name))
			return nullptr;
		return &this->colliders_box_map[collider_name];
	}

	inline std::map<std::string, ColliderBox>& GetAllCollidersBox() noexcept
	{
		return this->colliders_box_map;
	}

private:
	std::map<std::string, ColliderBox> colliders_box_map;
};

namespace Physics
{
	class Collision
	{
	public:

		Collision(){}
		~Collision(){}

		static const bool IsColliding(const ColliderBox& first_collider_box, const ColliderBox& second_collider_box) noexcept
		{
			return (
				first_collider_box.position.x + first_collider_box.dimensions.x >= second_collider_box.position.x &&
				second_collider_box.position.x + second_collider_box.dimensions.x >= first_collider_box.position.x &&
				first_collider_box.position.y + first_collider_box.dimensions.y >= second_collider_box.position.y &&
				second_collider_box.position.y + second_collider_box.dimensions.y >= first_collider_box.position.y
			);
		}

	private:

	};

}





