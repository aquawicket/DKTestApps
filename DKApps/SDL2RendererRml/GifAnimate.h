#ifndef GIFANIMATE_H
#define GIFANIMATE_H
#include <SDL_image.h>
#include <map>
#include <RmlUi/Core/Types.h>

struct GifData {
	IMG_Animation* anim;
	SDL_Texture** textures;
	int current_frame, delay, lastTime, currentTime;
};

static std::map<Rml::TextureHandle, GifData> gif_map;
bool LoadGifAnimation(SDL_Renderer* renderer, const Rml::String& source, Rml::TextureHandle& texture_handle, Rml::Vector2i& texture_dimensions);
SDL_Texture* GetGifAnimation(const Rml::TextureHandle texture);

#endif

