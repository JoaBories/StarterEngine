#pragma once

#include "Util.h"
using Struct::Vect2I;

#include <string>
#include <unordered_map>
#include <map>

#include <filesystem>

struct TextureEntry
{
	Texture* texturePtr;
	std::string name;
	bool multiple;
	Vect2I tileSize;
	Vect2I tileOffset;
	
	TextureEntry() = default;
	inline TextureEntry(Texture* texture, std::string name, Vect2I tileSize = Vect2I::zero, Vect2I tileOffset = Vect2I::zero) :
		texturePtr{ texture }, name{ name }, multiple{ tileSize != Vect2I::zero }, tileSize{ tileSize }, tileOffset{ tileOffset } {};

	inline ~TextureEntry() {
		UnloadTexture(*texturePtr); delete texturePtr; };
};

struct FontEntry
{
	Font* fontPtr;
	std::string name;

	FontEntry() = default;
	inline FontEntry(Font* font, std::string name) :
		fontPtr{ font }, name{ name } {
	};

	inline ~FontEntry() {
		UnloadFont(*fontPtr); delete fontPtr;
	};
};


enum AssetType
{
	AssetDefault,
	AssetFont,
	AssetTexture,
};

class AssetBank
{
private:
	std::unordered_map<std::string, TextureEntry*> mLoadedTextures;
	std::unordered_map<std::string, FontEntry*> mLoadedFonts;

	std::unordered_map<std::string, std::filesystem::path> mUnloadedFonts;
	std::unordered_map<std::string, std::filesystem::path> mUnloadedTextures;

	Texture* mErrorTexture = nullptr;

	const std::string mResourcePath = "resources";

	static AssetBank* instance;

public:
	AssetBank() = default;
	~AssetBank() = default;

	void Init();

	void SearchAFolder(std::filesystem::path folderPath);
	void SearchAFolderFor(std::filesystem::path folderPath, AssetType forWhat);
	
	void FetchAll();
	void UnfetchAll();
	void LoadAll();
	void UnloadAll();
	
	inline void UnloadTextures() {
		for (auto& entry : mLoadedTextures) delete entry.second; mLoadedTextures.clear(); };

	inline TextureEntry* GetATexture(std::string textureName) {
		if (mLoadedTextures.count(textureName)) LoadATexture(textureName); return mLoadedTextures.at(textureName); };
	
	bool FetchATexture(std::filesystem::path texturePath);
	bool LoadATexture(std::string textureName);

	
	inline void UnloadFonts() {
		for (auto& entry : mLoadedFonts) delete entry.second; mLoadedFonts.clear();	};

	inline FontEntry* GetAFont(std::string fontName) {
		if (mLoadedFonts.count(fontName)) LoadAFont(fontName); return mLoadedFonts.at(fontName); };

	bool FetchAFont(std::filesystem::path fontPath);
	bool LoadAFont(std::string fontName);


	inline static AssetBank* GetInstance() {
		if (!instance) instance = new AssetBank(); return instance; };
};

