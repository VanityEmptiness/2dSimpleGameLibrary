#pragma once
#include "../share/../../Vendors/Include/SDL/SDL.h"
#include "../share/../../Vendors/Include/SDL/SDL_image.h"

#include <map>
#include <string>
#include <iostream>

class TextureSet
{
public:
	TextureSet(){}
	TextureSet(SDL_Renderer* renderer) : renderer{ renderer } {}
	~TextureSet(){}

	SDL_Texture* GetTexture(const std::string& texture_name) noexcept;
	bool AddTexture(const std::string& texture_name, SDL_Texture* texture) noexcept;
	bool LoadTexture(const std::string& texture_name, const std::string& texture_file_path);
	bool RemoveTexture(const std::string& texture_name) noexcept;
	void RemoveAllTextures() noexcept;
	inline void SetRenderer(SDL_Renderer* renderer) noexcept { this->renderer = renderer; }

private:
	std::map<std::string, SDL_Texture*> textures_map;
	SDL_Renderer* renderer;

};
