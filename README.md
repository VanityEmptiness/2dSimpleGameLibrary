# 2dSimpleGameLibrary

A Simple 2d Game Library with some prebuilt systems to help you make simple 2d games, it use SDL for window creating and rendering (i perfectly know it is a bad practice but i wanted a simple portfolio thing to show, in a more sophisticated scenario i would have end up abstracting vulkan/directx/opengl graphic apis.

### Features

- Game Objects PreBuilt System.
- Rendering PreBuilt System (separeted from main game loop).
- Debug Mode with ImGui.
- Texture System.
- Collider System (with pyshics).
- More...

### Setup 

In order to make everything works you need to go in project solution property and add this settings.
- Download the directory files and copy it into your project folder as you see them.
- Go to **General/C++ Standard** and set to c++20
- Go to **Linker/General/AdditionalLibraryDirectories** and add the following property **$(ProjectDir)SDLGameLib\Vendors\Binaries**
- Go to **Linker/Input/AdditionalLibraries** and add the following properties **SDL2.lib;SDL2main.lib;SDL2_image.lib;**

### How It Works
- Once you downloaded it and setup, you should have something like this.

![immagine](https://user-images.githubusercontent.com/85369525/207132906-8f2d8c28-3cea-42fe-805b-11840979baeb.png)

- This is not a game engine, it is a simple game library with some prebuilt game systems made by me to help the user setting up the game
 you have also the source code in your project that can be modified at anytime. 
- Where can i start modifying the game and how it works? You have on the top of everything called game.cpp where you have the 2 main functions, OnLoad and OnUpdate, the first is called the first time when the game load the second one is called at every tick of the main game loop (render loop is executed on a different thread, you don't need to worry about it).
- The game abstraction system works like this you have a scene_manager object that helps you switching between scenes. Scenes contains scene objects (we can called it the entities of our game) a scene object can in fact have a texture ,a position and a velocity on the map. A Scene can also contains multiple cameras objects, but there is only on camera that is the one used for the rendering and it's called current_camera, you need to use the SwitchCamera method to change the Render with the camera you want. You can also bind a Camera to a SceneObject so when the object move the camera also does. 

- Now if you open game.cpp you can start editing your game, i'll leave a little example here.

```c++
#include "Game.h"

//This function gets called when the game loads
void Game::OnLoad()
{
	//Everything here it's just for testing/examples purpose

	//Here we simply add 2 images to the texture manager so we can use it later, using the texture manager prevents loading the same texture multiple times leaking memory
	Scene* current_scene = scene_manager->current_scene;
	scene_manager->texture_manager->LoadTexture("apple_tree", "SDLGameLib/Resources/ExampleAssets/AppleTree.png");
	scene_manager->texture_manager->LoadTexture("dark_mage", "SDLGameLib/Resources/ExampleAssets/DarkMage.png");

	//Here we define the tree scene object that will be used for our game
	SceneObject tree_actor{};
	tree_actor.BindTexture(scene_manager->texture_manager->GetTexture("apple_tree"));
	tree_actor.AddCollisionComponent();

	//Here i add the collider and set the physic handling to true, without doing it we can go through objects even if there is a collider
	tree_actor.collision_component->AddCollider("tree_actor", tree_actor.GetPosition(), tree_actor.GetDimensions());
	tree_actor.collision_component->GetCollider("tree_actor")->is_collider_physics_enabled = true;

	//Here we define our player (it is supposed to be a dark mage, i made the image by myself ;P ) it still be a scene object, the only things here that differ from the tree object
	//is that here we have binded the camera to the object so when the object moves the camera moves with the player, simple enough!
	SceneObject dark_mage_actor{};
	dark_mage_actor.BindTexture(scene_manager->texture_manager->GetTexture("dark_mage"));
	dark_mage_actor.BindCamera(current_scene->GetCurrentCamera());
	dark_mage_actor.SetPosition({ 1920 / 2, 1080 / 2 });
	dark_mage_actor.AddCollisionComponent();

	//Here i add the collider and set the physic handling to true, without doing it we can go through objects even if there is a collider
	dark_mage_actor.collision_component->AddCollider("dark_mage_actor", dark_mage_actor.GetPosition(), dark_mage_actor.GetDimensions());
	dark_mage_actor.collision_component->GetCollider("dark_mage_actor")->is_collider_physics_enabled = true;

	//We finally add the 2 objects defined before to our game, without those lines the objects does not exist for our game!!!
	current_scene->AddSceneObject(tree_actor, "tree_actor");
	current_scene->AddSceneObject(dark_mage_actor, "dark_mage_actor");

	//Here i've implemented a simple sort of input event handler to handle player movement so we can move around
	event_handler->AddListener([=](const SDL_Event& event) {
		SceneObject* actor = scene_manager->current_scene->GetSceneObject("dark_mage_actor");
		if (actor == nullptr)
			return;
	
		const Vec2 current_position = actor->GetPosition();
		const UINT key_pressed = event.key.keysym.sym;
		
		if (event.type == SDL_KEYDOWN)
		{
			const float player_speed = 1000.0f * game_handler->delta_time;

			if (key_pressed == SDLK_LEFT)
				actor->SetVelocity({ -player_speed, 0});
			if (key_pressed == SDLK_RIGHT)
				actor->SetVelocity({ player_speed, 0 });
			if (key_pressed == SDLK_UP)
				actor->SetVelocity({ 0, -player_speed });
			if (key_pressed == SDLK_DOWN)
				actor->SetVelocity({ 0, player_speed });
		}

		if (event.type == SDL_KEYUP)
			actor->SetVelocity({ 0, 0 });
	});
	
}

//This function gets called every game tick
void Game::OnUpdate()
{
	//Everything here it's just for testing/examples purpose

	SceneObject* dark_mage_actor = scene_manager->current_scene->GetSceneObject("dark_mage_actor");

	//Here i've added a simple sort of collide event handling
	//in this case if our player hits the tree it gets destroyed and removed from our game
	//it's just an example of usage!!
	
	/*if (dark_mage_actor != nullptr)
		if (dark_mage_actor->HasCollisionComponent())
			if (dark_mage_actor->collision_component->is_colliding)
			{
				for (const auto& colliding_boxes : dark_mage_actor->collision_component->collision_list)
				{
					for (const auto& colliding_against : colliding_boxes.second)
						scene_manager->current_scene->RemoveSceneObject(colliding_against);
				}
			}*/
	
}
```

This is how the example looks like

![immagine](https://user-images.githubusercontent.com/85369525/207296935-e79c8936-5563-4471-a9b3-81e000d5b931.png)
