#include "pch.h"
#include "Asset.h"
#include "World.h"


Asset::Asset() : filesToLoad(0), filesLoaded(0)
{
}


Asset::~Asset()
{
}


void Asset::initialize()
{
}

void Asset::dispose()
{
	for (auto iter : textures)
		delete iter.second;
}

void Asset::ready(string rootFilePath)
{
	if (filesToLoad > 0) return;

	for (recursive_directory_iterator iter(rootFilePath); iter != recursive_directory_iterator(); iter++) {
		string extension = iter->path().extension().string();
		if (extension == ".png" || extension == ".dds")
			paths.push_back(iter->path().string());
	}

	filesToLoad = paths.size();
	pathIter = paths.begin();
}

void Asset::loadNext()
{
	pathIter++;
}

TextureClass* Asset::getTexture(wstring p)
{
	if (!exists(p))
		cout << "파일 없음 : " << p << endl;

	if (!textures[p]) {
		textures[p] = new TextureClass();
		D3DX11CreateShaderResourceViewFromFile(world._d3d->_device, p.data(), NULL, NULL, &textures[p]->_texture, NULL);

		++filesLoaded;
	}

	return textures[p];
}

Asset asset;