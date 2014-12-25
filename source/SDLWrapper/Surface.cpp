// Surface.cpp
// Copyright (c) 2014 - The Foreseeable Future, zhiayang@gmail.com
// Licensed under the Apache License Version 2.0.

#include "SDLWrapper.h"
namespace SDL
{
	Surface::Surface(std::string path) : Surface(AssetLoader::Load(path.c_str()))
	{
	}

	Surface::Surface(AssetLoader::Asset* ass)
	{
		using namespace AssetLoader;

		assert(ass);
		this->asset = ass;

		switch(ass->type)
		{
			case AssetType::ImagePNG:
				this->sdlSurf = IMG_LoadPNG_RW(this->asset->sdlrw);
				if(!this->sdlSurf)
					ERROR("Failed to load PNG image from asset '%s'", this->asset->path.c_str());

				break;

			default:
				ERROR("Cannot create surface from unknown type of asset");
		}
	}

	Surface::Surface(Font* font, std::string txt, Util::Colour c)
	{
		// create a surface
		// kinda cheaty with the SDL colour cast.
		this->sdlSurf = TTF_RenderText_Blended(font->ttfFont, txt.c_str(), *((SDL_Color*) c.toSDL()));
		if(!this->sdlSurf) ERROR("Failed to create surface");

		this->asset = 0;
	}

	Surface::~Surface()
	{
		SDL_FreeSurface(this->sdlSurf);

		if(this->asset)
			AssetLoader::Unload(this->asset);
	}

}
