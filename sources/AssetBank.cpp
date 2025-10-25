#include "AssetBank.h"

#include <fstream>
using clk = std::chrono::high_resolution_clock;
using std::filesystem::path;

AssetBank* AssetBank::instance = nullptr;

void AssetBank::Init()
{
	mErrorTexture = new Texture(LoadTexture("resources/Error.png"));
	FetchAll();
}

void AssetBank::SearchAFolder(path folderPath)
{
	for (auto& entry : std::filesystem::directory_iterator(folderPath))
	{
		if (entry.is_directory()) 
		{
			if (entry.path().filename() == "_Fonts")
			{
				cout << "======== Fetching Fonts" << endl;
				SearchAFolderFor(entry.path(), AssetFont);
			}
			else if (entry.path().filename() == "_Textures")
			{
				cout << "======== Fetching Textures" << endl;
				SearchAFolderFor(entry.path(), AssetTexture);
			}
			else
			{
				SearchAFolder(entry.path());
			}
		}
	}
}

void AssetBank::SearchAFolderFor(path folderPath, AssetType forWhat)
{
	for (const auto& entry : std::filesystem::directory_iterator(folderPath))
	{
		if (entry.is_directory())
		{
			SearchAFolderFor(entry.path(), forWhat);
			continue;
		}

		switch (forWhat)
		{
		case AssetFont:
			FetchAFont(folderPath);
			break;

		case AssetTexture:
			FetchATexture(folderPath);
			break;

		default:
			break;
		}
	}
}

void AssetBank::FetchAll()
{
	cout << "==========| Start fetching Files" << endl;
	auto startTime = clk::now();

	UnfetchAll();

	const path rootPath = path(mResourcePath);
	SearchAFolder(rootPath);

	auto endTime = clk::now();
	cout << "==========| Finish fetching Files in : "<< std::chrono::duration<double>(endTime - startTime).count() << "s" << endl;
}

void AssetBank::UnfetchAll()
{
	mUnloadedFonts.clear();
	mUnloadedTextures.clear();
}

void AssetBank::LoadAll()
{
	cout << "==========| Start loading Files" << endl;
	auto startTime = clk::now();

	UnloadAll();

	for (auto& unloadedPath : mUnloadedFonts)
	{
		LoadAFont(unloadedPath.first);
	}

	for (auto& unloadedPath : mUnloadedTextures)
	{
		LoadATexture(unloadedPath.first);
	}

	auto endTime = clk::now();
	cout << "==========| Finish loading Files in : " << std::chrono::duration<double>(endTime - startTime).count() << "s" << endl;
}

void AssetBank::UnloadAll()
{
	UnloadTextures();
	UnloadFonts();
}

bool AssetBank::FetchATexture(std::filesystem::path texturePath)
{
	if (texturePath.extension() == ".png")
	{
		std::string dotAssetPath;
		dotAssetPath = texturePath.parent_path().string() + "\\" + texturePath.filename().replace_extension(".asset").string();
		std::string name = texturePath.filename().replace_extension("").string();

		mUnloadedTextures[name] = texturePath;

		std::ifstream fileRead;
		fileRead.open(dotAssetPath);

		if (!fileRead) // file do not exist so i create one
		{
			std::ofstream fileWrite;

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

		return true;
	}

	return false;
}

bool AssetBank::LoadATexture(std::string textureName)
{
	if (!mUnloadedTextures.count(textureName)) return false;

	else 
	{ 
		std::string dotAssetPath;
		std::ifstream fileRead;
		path filePath = mUnloadedTextures.at(textureName);

		if (filePath.extension() == ".png")
		{
			dotAssetPath = filePath.parent_path().string() + "\\" + filePath.filename().replace_extension(".asset").string();
			std::string name = filePath.filename().replace_extension("").string();

			fileRead.open(dotAssetPath);

			if (fileRead)
			{
				Image tempImg = LoadImage(filePath.string().c_str());

				std::string temp;
				bool tempMultiple = false;

				fileRead >> temp >> tempMultiple;

				if (tempMultiple)
				{
					int tileSizeX, tileSizeY, tileOffsetX, tileOffsetY;
					fileRead >> tileSizeX >> tileSizeY >> tileOffsetX >> tileOffsetY;
					mLoadedTextures[name] = new TextureEntry(new Texture(LoadTextureFromImage(tempImg)), name, { tileSizeX,tileSizeY }, { tileOffsetX,tileOffsetY });
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

		return true; 
	}
}

bool AssetBank::FetchAFont(std::filesystem::path fontPath)
{
	if (fontPath.extension() == ".png")
	{
		std::string dotAssetPath;
		dotAssetPath = fontPath.parent_path().string() + "\\" + fontPath.filename().replace_extension(".asset").string();
		std::string name = fontPath.filename().replace_extension("").string();

		mUnloadedFonts[name] = fontPath;

		std::ifstream fileRead;
		fileRead.open(dotAssetPath);

		if (!fileRead) // file do not exist so i create one
		{
			std::ofstream fileWrite;
			fileWrite.open(dotAssetPath);
			if (fileWrite)
			{
				fileWrite << name << endl;
			}

			fileWrite.close();
		}

		fileRead.close();

		return true;
	}

	return false;
}

bool AssetBank::LoadAFont(std::string fontName)
{
	if (!mUnloadedFonts.count(fontName)) return false;

	else 
	{ 
		std::string dotAssetPath;
		std::ifstream fileRead;
		path filePath = mUnloadedFonts.at(fontName);

		if (filePath.extension() == ".png")
		{
			dotAssetPath = filePath.parent_path().string() + "\\" + filePath.filename().replace_extension(".asset").string();
			std::string name = filePath.filename().replace_extension("").string();

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

		return true; 
	}
};
