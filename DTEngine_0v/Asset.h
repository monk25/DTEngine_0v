#pragma once
#include "Define.h"

class Asset
{
public:
	Asset();
	~Asset();

	void initialize();
	void dispose();
	void ready(string rootFilePath);
	void loadNext();

	map<string, int> textures;

	vector<string> paths;
	vector<string>::iterator pathIter;

	int filesToLoad;
	int filesLoaded;
};

extern Asset asset;