#include "AssetBank.h"

#include <fstream>
using std::ifstream, std::ofstream;

AssetBank* AssetBank::instance = nullptr;

TextureEntry::TextureEntry(Texture* text, string name):
	texturePtr{text},
	name{name},
	multiple{false},
	tileSize{ 0,0 },
	tileOffset{ 0,0 }
{
}

TextureEntry::TextureEntry(Texture* text, string name, Vect2I tileSize, Vect2I tileOffset):
	texturePtr{ text },
	name{ name },
	multiple{ true },
	tileSize{ tileSize },
	tileOffset{ tileOffset }
{
}

TextureEntry::~TextureEntry()
{
	UnloadTexture(*texturePtr);
	delete texturePtr;
}

FontEntry::FontEntry(Font* font, string name):
	fontPtr{ font },
	name{ name }
{
}

FontEntry::~FontEntry()
{
	UnloadFont(*fontPtr);
	delete fontPtr;
}

void AssetBank::LoadAnAsset(fs::path filePath, AssetType type)
{
	string dotAssetPath;
	ifstream fileRead;
	
	double startTime = GetTime();

	switch (type)
	{
	case None:
		break;
	case FontFile:
		if (filePath.extension() == ".png")
		{
			dotAssetPath = filePath.parent_path().string() + "\\" + filePath.filename().replace_extension(".asset").string();
			string name = filePath.filename().replace_extension("").string();

			fileRead.open(dotAssetPath);

			if (fileRead)
			{
				mLoadedFonts[name] = new FontEntry(new Font(LoadFont(filePath.string().c_str())), name);
			}
			else
			{
				cout << "Failed to read .asset file : " << dotAssetPath << endl;
			}

			fileRead.close();
		}

		break;
	case TextureFile:
		if (filePath.extension() == ".png")
		{
			dotAssetPath = filePath.parent_path().string() + "\\" + filePath.filename().replace_extension(".asset").string();
			string name = filePath.filename().replace_extension("").string();

			fileRead.open(dotAssetPath);

			if (fileRead)
			{
				Image tempImg = LoadImage(filePath.string().c_str());

				string temp;
				bool tempMultiple = false;

				fileRead >> temp >> tempMultiple;

				if (tempMultiple)
				{
					int a, b, c, d;
					fileRead >> a >> b >> c >> d;
					mLoadedTextures[name] = new TextureEntry(new Texture(LoadTextureFromImage(tempImg)), name, { a,b }, { c,d });
				}
				else
				{
					mLoadedTextures[name] = new TextureEntry(new Texture(LoadTextureFromImage(tempImg)), name);
				}

				UnloadImage(tempImg);
			}
			else
			{
				cout << "Failed to read .asset file : " << dotAssetPath << endl;
			}
			fileRead.close();
		}

		break;
	case SoundFile:
		break;
	}

	double endTime = GetTime();
	double totalTime = endTime - startTime;
	cout << "======== Finish loading " << filePath.filename().replace_extension("") << " in " << totalTime << "s" << endl;
}

void AssetBank::FetchAnAsset(fs::path filePath, AssetType type)
{
	string dotAssetPath;
	ifstream fileRead;
	ofstream fileWrite;

	switch (type)
	{
	case None:
		break;
	case FontFile:
		if (filePath.extension() == ".png")
		{
			dotAssetPath = filePath.parent_path().string() + "\\" + filePath.filename().replace_extension(".asset").string();
			string name = filePath.filename().replace_extension("").string();

			mUnloadedFonts[name] = filePath;

			fileRead.open(dotAssetPath);

			if (!fileRead)
			{
				fileWrite.open(dotAssetPath);
				if (fileWrite)
				{
					fileWrite << name << endl;
				}

				fileWrite.close();
			}

			fileRead.close();
		}

		break;
	case TextureFile:
		if (filePath.extension() == ".png")
		{
			dotAssetPath = filePath.parent_path().string() + "\\" + filePath.filename().replace_extension(".asset").string();
			string name = filePath.filename().replace_extension("").string();

			mUnloadedTextures[name] = filePath;

			fileRead.open(dotAssetPath);

			if (!fileRead)
			{
				fileWrite.open(dotAssetPath);
				if (fileWrite)
				{
					fileWrite << name << endl;
					fileWrite << false << endl;
					fileWrite << 0 << " " << 0 << endl;
					fileWrite << 0 << " " << 0 << endl;
				}

				fileWrite.close();
			}

			fileRead.close();
		}

		break;
	case SoundFile:
		break;
	}
}

void AssetBank::Init()
{
	mErrorTexture = new Texture(LoadTexture("resources/Error.png"));
	FetchAll();
}

void AssetBank::SearchAFolder(fs::path folderPath)
{
	for (auto& entry : fs::directory_iterator(folderPath))
	{
		if (entry.is_directory()) 
		{
			if (entry.path().filename() == "_Fonts")
			{
				cout << "======== Fetching Fonts" << endl;
				SearchAFolderFor(entry.path(), FontFile);
			}
			else if (entry.path().filename() == "_Textures")
			{
				cout << "======== Fetching Textures" << endl;
				SearchAFolderFor(entry.path(), TextureFile);
			}
			else
			{
				SearchAFolder(entry.path());
			}
		}
	}
}

void AssetBank::SearchAFolderFor(fs::path folderPath, AssetType forWhat)
{
	for (const auto& entry : fs::directory_iterator(folderPath))
	{
		if (entry.is_directory())
		{
			SearchAFolderFor(entry.path(), forWhat);
			continue;
		}

		FetchAnAsset(entry.path(), forWhat);
	}
}

void AssetBank::FetchAll()
{
	cout << "==========| Start fetching Files" << endl;
	double startTime = GetTime();

	UnfetchAll();

	const fs::path path = fs::path(mResourcePath);
	SearchAFolder(path);

	double endTime = GetTime();
	double totalTime = endTime - startTime;
	cout << "==========| Finish fetching Files in : "<< totalTime << "s" << endl;
}

void AssetBank::UnfetchAll()
{
	mUnloadedFonts.clear();
	mUnloadedTextures.clear();
}

void AssetBank::LoadAll()
{
	cout << "==========| Start loading Files" << endl;
	double startTime = GetTime();

	UnloadAll();

	for (pair<string, fs::path> unloadedPath : mUnloadedFonts)
	{
		LoadAnAsset(unloadedPath.second, FontFile);
	}

	for (pair<string, fs::path> unloadedPath : mUnloadedTextures)
	{
		LoadAnAsset(unloadedPath.second, TextureFile);
	}

	double endTime = GetTime();

	double totalTime = endTime - startTime;
	cout << "==========| Finish loading Files in : " << totalTime << "s" << endl;
}

void AssetBank::UnloadAll()
{
	UnloadTextures();
	UnloadFonts();
}

void AssetBank::UnloadTextures()
{
	for (pair<string, TextureEntry*> entry : mLoadedTextures)
	{
		delete mLoadedTextures[entry.first];
	}

	mLoadedTextures.clear();
}

void AssetBank::UnloadFonts()
{
	for (pair<string, FontEntry*> entry : mLoadedFonts) 
	{
		delete mLoadedFonts[entry.first];
	}

	mLoadedFonts.clear();
}

TextureEntry* AssetBank::GetATexture(string textureName)
{
	if (mLoadedTextures.find(textureName) == mLoadedTextures.end())
	{
		LoadATexture(textureName);
	}

	return mLoadedTextures[textureName];
}

bool AssetBank::LoadATexture(string textureName)
{
	if (mUnloadedTextures.find(textureName) == mUnloadedTextures.end())
	{
		return false;
	}
	else
	{
		LoadAnAsset(mUnloadedTextures[textureName], TextureFile);
		return true;
	}
}

FontEntry* AssetBank::GetAFont(string fontName)
{
	if (mLoadedFonts.find(fontName) == mLoadedFonts.end())
	{
		LoadAFont(fontName);
	}

	return mLoadedFonts[fontName];
}

bool AssetBank::LoadAFont(string fontName)
{
	if (mUnloadedFonts.find(fontName) == mUnloadedFonts.end())
	{
		return false;
	}
	else
	{
		LoadAnAsset(mUnloadedFonts[fontName], FontFile);
		return true;
	}
}

AssetBank* AssetBank::GetInstance()
{
	if (!instance)
	{
		instance = new AssetBank();
	}

	return instance;
}