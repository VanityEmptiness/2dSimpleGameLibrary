#include "Scene.h"
#include "../../../Game.h"

void Scene::Render()
{
	if (this->scene_objects_ordered_render_list.size() < 1)
		return;

	std::lock_guard<std::mutex> render_lock_guard(render_lock_mutex); //Synchronize render with game update 
	for (size_t i = 0; i < this->scene_objects_ordered_render_list.size(); i++)
	{
		SceneObject* current_scene_object_rendered = this->scene_objects_ordered_render_list[i];
		current_scene_object_rendered->SetRenderPosition(this->current_camera->viewport - (this->current_camera->position - current_scene_object_rendered->GetPosition()));
		current_scene_object_rendered->Render();
	}
}

void Scene::AddSceneObject(const std::string& object_name)
{
	if (this->scene_objects_map.contains(object_name))
		return;

	SceneObject object{ scene_manager->renderer };

	this->scene_objects_map.insert({ object_name , object });

	//Render Order Layering
	const size_t scene_objects_ordered_render_list_size = this->scene_objects_ordered_render_list.size();
	if (scene_objects_ordered_render_list_size > 0)
	{
		//If there already is an object with a render index equal, the object will be inserted before
		for (size_t i = 0; i < scene_objects_ordered_render_list_size; i++)
		{
			SceneObject* current_scene_object = this->scene_objects_ordered_render_list[i];
			if (object.render_index <= current_scene_object->render_index)
			{
				this->scene_objects_ordered_render_list.insert(this->scene_objects_ordered_render_list.begin() + i, &this->scene_objects_map[object_name]);
				return;
			}
		}
		//In any other case it gets pushed back as last rendered (first to appear)
		this->scene_objects_ordered_render_list.push_back(&this->scene_objects_map[object_name]);
	}
	else
		this->scene_objects_ordered_render_list.push_back(&this->scene_objects_map[object_name]);
}

void Scene::AddSceneObject(SceneObject& object, const std::string& object_name)
{
	if (this->scene_objects_map.contains(object_name))
		return;

	object.SetRenderer(scene_manager->renderer);

	this->scene_objects_map.insert({ object_name , object });

	//Render Order Layering
	const size_t scene_objects_ordered_render_list_size = this->scene_objects_ordered_render_list.size();
	if (scene_objects_ordered_render_list_size > 0)
	{
		//If there already is an object with a render index equal, the object will be inserted before
		for (size_t i = 0; i < scene_objects_ordered_render_list_size; i++)
		{
			SceneObject* current_scene_object = this->scene_objects_ordered_render_list[i];
			if (object.render_index <= current_scene_object->render_index)
			{
				this->scene_objects_ordered_render_list.insert(this->scene_objects_ordered_render_list.begin() + i, &this->scene_objects_map[object_name]);
				return;
			}
		}
		//In any other case it gets pushed back as last rendered (first to appear)
		this->scene_objects_ordered_render_list.push_back(&this->scene_objects_map[object_name]);
	}
	else
		this->scene_objects_ordered_render_list.push_back(&this->scene_objects_map[object_name]);
}

void Scene::RemoveSceneObject(const std::string& object_name) noexcept
{
	if (!this->scene_objects_map.contains(object_name))
		return;

	const std::string& scene_object_uuid = this->scene_objects_map[object_name].uuid;

	for (size_t i = 0; i < this->scene_objects_ordered_render_list.size(); i++)
	{
		if (this->scene_objects_ordered_render_list[i]->uuid == scene_object_uuid)
			this->scene_objects_ordered_render_list.erase(this->scene_objects_ordered_render_list.begin() + i);
	}
	
	this->scene_objects_map.erase(object_name);
}

void Scene::UpdateCollisionDetection() noexcept
{
	std::lock_guard<std::mutex> collision_detection_lock_guard(collision_detection_mutex);
	for (auto& current_scene_object : this->scene_objects_map) //Loop Every Scene Object to detect collision
	{
		bool is_colliding = false;

		if (current_scene_object.second.collision_component == nullptr)
			continue;

		if (current_scene_object.second.collision_component->GetAllCollidersBox().size() < 1)
			continue;

		current_scene_object.second.collision_component->is_colliding = false;
		current_scene_object.second.collision_component->collision_list.clear();

		for (const auto& current_possible_collider_object : this->scene_objects_map) //Loop Every Scene Object against the current one to detect the effective collision
		{
			if (current_scene_object.second.collision_component == current_possible_collider_object.second.collision_component)
				continue;

			if (current_possible_collider_object.second.collision_component == nullptr)
				continue;

			if (current_possible_collider_object.second.collision_component->GetAllCollidersBox().size() < 1)
				continue;

			//Loop Every Collider Box in the current scene object against every Collider Box of every possible collider encountered
			for (const auto& current_scene_object_collider_box : current_scene_object.second.collision_component->GetAllCollidersBox())
			{
				std::vector<std::string> colliding_objects_list;

				for (const auto& current_possible_collider_object_collider_box : current_possible_collider_object.second.collision_component->GetAllCollidersBox())
				{
					if (Physics::Collision::IsColliding(
						ColliderBox(
							current_scene_object_collider_box.second.name, 
							{ current_scene_object_collider_box.second.position.x + current_scene_object.second.GetVelocity().x, current_scene_object_collider_box.second.position.y + current_scene_object.second.GetVelocity().y },
							current_scene_object_collider_box.second.dimensions
						),
						ColliderBox(
							current_possible_collider_object_collider_box.second.name, 
							{ current_possible_collider_object_collider_box.second.position.x + current_possible_collider_object.second.GetVelocity().x, current_possible_collider_object_collider_box.second.position.y + current_possible_collider_object.second.GetVelocity().y },
							current_possible_collider_object_collider_box.second.dimensions
						)
					))
					{
						is_colliding = true;
						colliding_objects_list.push_back(current_possible_collider_object_collider_box.first);

						if (current_scene_object_collider_box.second.is_collider_physics_enabled)
							current_scene_object.second.SetVelocity({ 0 , 0 });

					}
				}

				if (is_colliding)
					current_scene_object.second.collision_component->collision_list.insert({ current_scene_object_collider_box.first , colliding_objects_list });
			}
		}

		current_scene_object.second.collision_component->is_colliding = is_colliding;
	}
}

void Scene::UpdateMovementPhysics() noexcept
{
	for (auto& current_scene_object : this->scene_objects_map) //Loop Every Scene Object to recreate movement
		current_scene_object.second.SetPosition({ 
			current_scene_object.second.GetPosition().x + current_scene_object.second.GetVelocity().x,
			current_scene_object.second.GetPosition().y + current_scene_object.second.GetVelocity().y 
		});
}