#include "TextureSet.h"

SDL_Texture* TextureSet::GetTexture(const std::string& texture_name) noexcept
{
	if (!this->textures_map.contains(texture_name))
		return nullptr;

	return this->textures_map[texture_name];
}

bool TextureSet::AddTexture(const std::string& texture_name, SDL_Texture* texture) noexcept
{
	if (this->textures_map.contains(texture_name))
		return false;

	this->textures_map.insert({ texture_name , texture });
	
	return true;
}

bool TextureSet::LoadTexture(const std::string& texture_name, const std::string& texture_file_path)
{
	if (this->renderer == nullptr)
		return false;

	try
	{
		SDL_Surface* entity_texture_surface = IMG_Load(texture_file_path.c_str());
		this->textures_map.insert({ texture_name , SDL_CreateTextureFromSurface(this->renderer, entity_texture_surface) });
		SDL_FreeSurface(entity_texture_surface);
		return true;
	}
	catch (const std::exception& err)
	{
		std::cout << err.what() << std::endl;
		return false;
	}
}

bool TextureSet::RemoveTexture(const std::string& texture_name) noexcept
{
	if (!this->textures_map.contains(texture_name))
		return false;

	//Free Texture to avoid memory leaks
	if (this->textures_map[texture_name] != nullptr)
		SDL_DestroyTexture(this->textures_map[texture_name]);

	this->textures_map.erase(texture_name);
	return true;
}

void TextureSet::RemoveAllTextures() noexcept
{
	if (this->textures_map.size() < 1)
		return;

	for (const auto& texture : this->textures_map)
		this->RemoveTexture(texture.first);
}