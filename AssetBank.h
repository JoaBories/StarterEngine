#pragma once

#include <raylib.h>

#include "Utils.h"

#include <string>
#include <map>
using std::map, std::pair;
using std::string;

#include <filesystem>
namespace fs = std::filesystem;

struct TextureEntry
{
	Texture* texturePtr;
	string name;
	bool multiple;
	Vect2I tileSize;
	Vect2I tileOffset;
	
	TextureEntry() = default;
	TextureEntry(Texture* text, string name);
	TextureEntry(Texture* text, string name, Vect2I tileSize, Vect2I tileOffset);
	~TextureEntry();
};

struct FontEntry 
{
	Font* fontPtr;
	string name;

	FontEntry() = default;
	FontEntry(Font* font, string name);
	~FontEntry();
};

enum ForWhat
{
	None,
	FontFile,
	ImageFile,
	SoundFile,
};

class AssetBank
{
private:
	map<string, TextureEntry*> mTextures;
	map<string, FontEntry*> mFonts;

	const string mResourcePath = "resources";

public:
	AssetBank() = default;
	~AssetBank() = default;

	void SearchAFolder(fs::path folderPath);
	void SearchAFolder(fs::path folderPath, ForWhat forWhat);
	
	void LoadAll();
	void UnloadAll();
	void SaveAllInfo();

	void LoadATexture();

	void UnloadTextures();
	void SaveTexturesInfos();

};

