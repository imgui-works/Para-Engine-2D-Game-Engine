#pragma once
#include <unordered_map>
#include <vector>
#include "stb_image.h"
class TextureManager
{
public:
	TextureManager() = delete;
	TextureManager(const TextureManager&) = delete;
	static void getRawImageDataFromFile(const std::string& path, std::vector<unsigned char>& data, int &width, int &height, bool flipImage);
	static unsigned int loadTextureFromFile(const std::string& path, const std::string& referenceString, bool gamma);
	static unsigned int getTextureFromReference(const std::string& referenceString);
	static void unloadTexture(const std::string& referenceName);
	static void unloadTexturesFromMemory();
private:
	static std::unordered_map<std::string, unsigned int> textureIdMap;
};