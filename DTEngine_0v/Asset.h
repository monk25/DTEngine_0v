#pragma once
#include "Define.h"
#include "TextureClass.h"

class Asset
{
public:
	Asset();
	~Asset();

	void initialize();
	void dispose();
	void ready(string rootFilePath);
	void loadNext();

	TextureClass* getTexture(wstring p);

	map<wstring, TextureClass*> textures;

	vector<string> paths;
	vector<string>::iterator pathIter;

	int filesToLoad;
	int filesLoaded;
};

extern Asset asset;