#pragma once
#include "SceneObject.h"
#include "Camera.h"
#include "SubComponents/Collision.h"

#include <map>
#include <vector>
#include <mutex>

inline std::mutex render_lock_mutex;
inline std::mutex collision_detection_mutex;

class Scene
{
public:
	std::string scene_name = "default_1";

	Scene(){}
	~Scene(){}

	void Render();

	void AddSceneObject(const std::string& object_name);
	void AddSceneObject(SceneObject& object, const std::string& object_name);
	void RemoveSceneObject(const std::string& object_name) noexcept;
	inline SceneObject* GetSceneObject(const std::string& object_name) noexcept 
	{ 
		if (!this->scene_objects_map.contains(object_name))
			return nullptr;
		return &this->scene_objects_map[object_name]; 
	}

	inline bool HasSceneObject(const std::string& object_name) noexcept
	{
		if (!this->scene_objects_map.contains(object_name))
			return false;
		return true;
	}

	inline void SwitchCamera(const std::string& camera_name) noexcept 
	{ 
		if (this->all_cameras.contains(camera_name)) 
			this->current_camera = &this->all_cameras[camera_name]; 
	}

	inline void SwitchCamera(Camera* camera) noexcept 
	{ 
		if (camera != nullptr && (this->current_camera != camera)) 
			this->current_camera = camera; 
	}

	inline void AddCamera(const std::string& camera_name) noexcept 
	{ 
		if (this->all_cameras.contains(camera_name)) 
			return; 
		this->all_cameras.insert({ camera_name , Camera() }); 
	}

	inline void AddCamera(const Camera& camera, const std::string& camera_name) noexcept 
	{ 
		if (this->all_cameras.contains(camera_name)) 
			return; 
		this->all_cameras.insert({ camera_name , camera }); 
	}

	inline Camera* GetCurrentCamera() noexcept 
	{ 
		return this->current_camera; 
	}

	inline Camera* GetCamera(const std::string& camera_name) noexcept 
	{ 
		if (this->all_cameras.contains(camera_name)) 
			return &this->all_cameras[camera_name];  
		return nullptr; 
	}

	inline const std::map<std::string, Camera>& GetAllCameras() const noexcept { return this->all_cameras; }

	inline const std::vector<SceneObject*>& GetSceneObjectsRenderList() const noexcept { return this->scene_objects_ordered_render_list; }
	inline const std::map<std::string, SceneObject>& GetSceneObjectsMap() const noexcept { return this->scene_objects_map; }

	void UpdateCollisionDetection() noexcept;
	void UpdateMovementPhysics() noexcept;

private:
	Camera* current_camera = new Camera();
	std::vector<SceneObject*> scene_objects_ordered_render_list;
	std::map<std::string, SceneObject> scene_objects_map;
	std::map<std::string, Camera> all_cameras;
	
};

