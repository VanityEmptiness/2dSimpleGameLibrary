#include "SceneObject.h"

SceneObject::SceneObject(SDL_Renderer* renderer)
	: renderer{ renderer }
{
	UUIDv4::UUIDGenerator<std::mt19937_64> uuid_generator;
	UUIDv4::UUID uuid = uuid_generator.getUUID();
	this->uuid = uuid.bytes();
}


bool SceneObject::BindTexture(SDL_Texture* texture)
{
	this->object_texture = texture;
	this->is_texture_loaded = true;
	return true;
}

void SceneObject::Render() noexcept
{
	if (!this->is_texture_loaded)
		return;

	this->current_texture_render_rect.x = this->object_render_position.x;
	this->current_texture_render_rect.y = this->object_render_position.y;
	SDL_RenderCopy(this->renderer, this->object_texture, NULL, &this->current_texture_render_rect);
}

void SceneObject::SetPosition(const Vec2& position) noexcept
{
	if (this->binded_camera != nullptr)
		this->binded_camera->position = { position.x + (this->current_texture_render_rect.w / 2) , position.y + (this->current_texture_render_rect.h / 2) };

	if (this->collision_component != nullptr)
		if (this->collision_component->GetAllCollidersBox().size() > 0)
		{
			const Vec2& delta_position = (Vec2&)position - this->position;
			for (auto& current_box_collider : this->collision_component->GetAllCollidersBox())
				current_box_collider.second.position = current_box_collider.second.position + delta_position;
		}

	this->position = { position.x , position.y };
}