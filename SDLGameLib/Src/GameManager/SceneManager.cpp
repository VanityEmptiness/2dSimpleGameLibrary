#include "SceneManager.h"

SceneManager::SceneManager()
{
	this->AddScene("Default_Scene");
	this->SwitchScene("Default_Scene");
}

void SceneManager::AddScene(const std::string& scene_name) noexcept
{ 
	if (this->all_scenes.contains(scene_name)) return; 

	Scene new_scene{}; 
	new_scene.scene_name = scene_name;
	this->all_scenes.insert({ scene_name , new_scene }); 
}

bool SceneManager::RemoveScene(const std::string& scene_name) noexcept
{
	if (!this->all_scenes.contains(scene_name))
		return false;

	this->all_scenes.erase(scene_name);
	
	return true;
}