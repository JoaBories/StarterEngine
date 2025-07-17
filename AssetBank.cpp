#include "AssetBank.h"

#include <iostream>
#include <fstream>
using std::ifstream, std::ofstream;
using std::cout, std::endl;

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

void AssetBank::SearchAFolder(fs::path folderPath)
{
	for (auto& entry : fs::directory_iterator(folderPath))
	{
		if (entry.is_directory()) 
		{
			if (entry.path().filename() == "_Fonts")
			{
				cout << "==== Start Loading Fonts ====" << endl;
				SearchAFolder(entry.path(), FontFile);
			}
			else if (entry.path().filename() == "_Textures")
			{
				cout << "=== Start Loading Textures ===" << endl;
				SearchAFolder(entry.path(), ImageFile);
			}
			else
			{
				SearchAFolder(entry.path());
			}
		}
	}
}

void AssetBank::SearchAFolder(fs::path folderPath, ForWhat forWhat)
{
	for (const auto& entry : fs::directory_iterator(folderPath))
	{
		if (entry.is_directory())
		{
			SearchAFolder(entry.path(), forWhat);
			continue;
		}

		string dotAssetPath;
		ifstream fileRead;
		ofstream fileWrite;

		switch (forWhat)
		{
		case None:
			break;
		case FontFile:
			if (entry.path().extension() == ".png")
			{
				dotAssetPath = entry.path().parent_path().string() + "\\" + entry.path().filename().replace_extension(".asset").string();
				string name = entry.path().filename().replace_extension("").string();
				
				fileRead.open(dotAssetPath);

				if (fileRead)
				{
					mFonts[name] = new FontEntry(new Font(LoadFont(entry.path().string().c_str())), name);
				}
				else
				{
					mFonts[name] = new FontEntry(new Font(LoadFont(entry.path().string().c_str())), name);

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
		case ImageFile:
			if (entry.path().extension() == ".png")
			{
				dotAssetPath = entry.path().parent_path().string() + "\\" + entry.path().filename().replace_extension(".asset").string();
				string name = entry.path().filename().replace_extension("").string();

				fileRead.open(dotAssetPath);

				if (fileRead)
				{
					Image tempImg = LoadImage(entry.path().string().c_str());
				
					string temp;
					bool tempMultiple = false;

					fileRead >> temp >> tempMultiple;

					if (tempMultiple)
					{
						int a, b, c, d;
						fileRead >> a >> b >> c >> d;
						mTextures[name] = new TextureEntry(new Texture(LoadTextureFromImage(tempImg)), name, { a,b }, { c,d });
					}
					else
					{
						mTextures[name] = new TextureEntry(new Texture(LoadTextureFromImage(tempImg)), name);
					}

					UnloadImage(tempImg);
				}
				else
				{
					Image tempImg = LoadImage(entry.path().string().c_str());
					mTextures[name] = new TextureEntry(new Texture(LoadTextureFromImage(tempImg)), name);

					UnloadImage(tempImg);

					fileWrite.open(dotAssetPath);
					if (fileWrite)
					{
						fileWrite << name << endl;
						fileWrite << mTextures[name]->multiple << endl;
						fileWrite << mTextures[name]->tileSize.x << " " << mTextures[name]->tileSize.y << endl;
						fileWrite << mTextures[name]->tileOffset.x << " " << mTextures[name]->tileSize.y << endl;
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
}

void AssetBank::LoadAll()
{
	cout << "=============================" << endl;
	cout << "==== Start loading Files ====" << endl;
	double startTime = GetTime();

	const fs::path path = fs::path(mResourcePath);
	SearchAFolder(path);

	double endTime = GetTime();
	double totalTime = endTime - startTime;
	cout << "==== Finish loading Files in : "<< totalTime << "s ====" << endl;
	cout << "=============================" << endl;
}

void AssetBank::UnloadAll()
{
	UnloadTextures();
}

void AssetBank::SaveAllInfo()
{
}

void AssetBank::LoadATexture()
{
}

void AssetBank::UnloadTextures()
{
	for (pair<string, TextureEntry*> entry : mTextures)
	{
		delete mTextures[entry.first];
	}

	mTextures.clear();
}

void AssetBank::SaveTexturesInfos()
{
}


