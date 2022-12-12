#pragma once
#include "Scene.h"
#include "TextureSet.h"
#include "Events.h"

#include <map>
#include <string>

class SceneManager
{
public:
	Scene* current_scene;
	SDL_Renderer* renderer;
	TextureSet* texture_manager;

	SceneManager();
	~SceneManager(){}

	Scene* GetScene(const std::string& scene_name) noexcept { if (!this->all_scenes.contains(scene_name)) return nullptr; return &this->all_scenes[scene_name]; };
	void SwitchScene(const std::string& scene_name) noexcept { if (this->all_scenes.contains(scene_name)) this->current_scene = &this->all_scenes[scene_name]; };
	void SwitchScene(Scene* scene) noexcept { if (scene != nullptr) this->current_scene = scene; };
	void AddScene(const std::string& scene_name) noexcept;
	bool RemoveScene(const std::string& scene_name) noexcept;
	const std::map<std::string, Scene>& GetAllScenes() const noexcept { return this->all_scenes; }

private:
	std::map<std::string, Scene> all_scenes{};
	
};

inline SceneManager* scene_manager = new SceneManager();

