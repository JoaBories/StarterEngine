#pragma once

#include <raylib.h>

#include "Util.h"
using Struct::Vect2I;

#include <string>
#include <map>
using std::map, std::pair;
using std::string;

#include <filesystem>
namespace fs = std::filesystem;

#include <iostream>
using std::cout, std::endl;

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

enum AssetType
{
	None,
	FontFile,
	TextureFile,
	SoundFile,
};

class AssetBank
{
private:
	map<string, TextureEntry*> mLoadedTextures;
	map<string, FontEntry*> mLoadedFonts;

	map<string, fs::path> mUnloadedFonts;
	map<string, fs::path> mUnloadedTextures;

	Texture* mErrorTexture = nullptr;

	const string mResourcePath = "resources";

	void LoadAnAsset(fs::path filePath, AssetType type);
	void FetchAnAsset(fs::path filePath, AssetType type);

	static AssetBank* instance;

public:
	AssetBank() = default;
	~AssetBank() = default;

	void Init();

	void SearchAFolder(fs::path folderPath);
	void SearchAFolderFor(fs::path folderPath, AssetType forWhat);
	
	void FetchAll();
	void UnfetchAll();
	void LoadAll();
	void UnloadAll();

	void UnloadTextures();
	void UnloadFonts();

	TextureEntry* GetATexture(string textureName);
	bool LoadATexture(string textureName);
	FontEntry* GetAFont(string fontName);
	bool LoadAFont(string fontName);

	static AssetBank* GetInstance();
};

