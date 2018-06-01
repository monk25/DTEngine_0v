#include "pch.h"
#include "Asset.h"


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
}

void Asset::ready(string rootFilePath)
{
	if (filesToLoad > 0) return;

	for (recursive_directory_iterator iter(rootFilePath); iter != recursive_directory_iterator(); iter++) {
		
	}

	filesToLoad = paths.size();
	pathIter = paths.begin();
}

void Asset::loadNext()
{
	pathIter++;
}

Asset asset;