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