#pragma once
class GlobalVariables
{

public:
	static bool EngineRunning; // engine has passed init state
	static bool TextureCulling; // Enable culling of invisible textures | Quite heavy enable it only for very huge texture
	static float CullingSizeMultiplier; // Scale the size of the CamSpace to avoid big texture false culling

};

