#pragma once
#include "../share/../../Vendors/Include/SDL/SDL.h"
#include "../share/../../Vendors/Include/SDL/SDL_image.h"
#include "../share/../../Vendors/Include/UUIDV4/uuid_v4.h"
#include "../Utils/Math.h"
#include "Camera.h"
#include "SubComponents/Collision.h"

#include <string>
#include <iostream>
#include <Windows.h>

class SceneObject
{
public:
	UINT render_index = 0; // Render in order From Highest to Lowest
	std::string uuid;
	CollisionComponent* collision_component = nullptr;

	SceneObject(){}
	explicit SceneObject(SDL_Renderer* renderer);
	~SceneObject(){}

	void SetRenderer(SDL_Renderer* renderer) noexcept { this->renderer = renderer; }
	bool BindTexture(SDL_Texture* texture);
	void Render() noexcept;

	inline void SetRenderPosition(const Vec2& position) noexcept { this->object_render_position = position; }
	inline void SetRenderDimensions(const Vec2& dimensions) noexcept 
	{ 
		this->current_texture_render_rect.w = (int)dimensions.x;
		this->current_texture_render_rect.h = (int)dimensions.y;
	}

	inline void BindCamera(Camera* camera) noexcept { this->binded_camera = camera; this->binded_camera->is_binded = true; }
	inline void UnbindCamera() noexcept { this->binded_camera->is_binded = false; this->binded_camera = nullptr; }
 
	inline const Vec2& GetPosition() const noexcept { return this->position; }
	inline const Vec2& GetVelocity() const noexcept { return this->velocity; }
	inline const Vec2& GetDimensions() const noexcept { return this->dimensions; }
	inline void SetDimensions(const Vec2& dimensions) noexcept { 
		this->dimensions = dimensions; 
	}
	inline void SetVelocity(const Vec2& velocity) noexcept {
		this->velocity = velocity;
	}
	void SetPosition(const Vec2& position) noexcept;

	inline void AddCollisionComponent() noexcept { if (this->collision_component != nullptr) return; this->collision_component = new CollisionComponent(); }
	inline constexpr bool HasCollisionComponent() noexcept { return this->collision_component != nullptr; }

private:
	SDL_Renderer* renderer; //main renderer device
	SDL_Texture* object_texture;
	Camera* binded_camera;
	Vec2 dimensions = { 128 , 128 }; 
	Vec2 position = { 0 , 0 };
	Vec2 velocity = { 0 , 0 };
	Vec2 object_render_position = this->position;
	SDL_Rect current_texture_render_rect = { 0, 0, (int)this->dimensions.x , (int)this->dimensions.y };
	bool is_texture_loaded = false;

};
