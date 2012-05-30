
// BlockID.cpp

// Implements the helper functions for converting Block ID string to int etc.

#include "Globals.h"
#include "BlockID.h"
#include "../iniFile/iniFile.h"





NIBBLETYPE g_BlockLightValue[256];
NIBBLETYPE g_BlockSpreadLightFalloff[256];
bool       g_BlockTransparent[256];
bool       g_BlockOneHitDig[256];
bool       g_BlockPistonBreakable[256];
bool       g_BlockIsSnowable[256];





class cBlockIDMap
{
public:
	cBlockIDMap(void) : m_Ini("items.ini")
	{
		m_Ini.ReadFile();
	}
	
	int Resolve(const AString & a_ItemName)
	{
		return m_Ini.GetValueI("Items", a_ItemName, -1);
	}
	
protected:
	cIniFile m_Ini;
} ;





static cBlockIDMap gsBlockIDMap;





int BlockStringToType(const AString & a_BlockTypeString)
{
	int res = atoi(a_BlockTypeString.c_str());
	if ((res != 0) || (a_BlockTypeString.compare("0") == 0))
	{
		// It was a valid number, return that
		return res;
	}
	
	return gsBlockIDMap.Resolve(a_BlockTypeString);
}




EMCSBiome StringToBiome(const AString & a_BiomeString)
{
	// If it is a number, return it:
	int res = atoi(a_BiomeString.c_str());
	if ((res != 0) || (a_BiomeString.compare("0") == 0))
	{
		// It was a valid number
		return (EMCSBiome)res;
	}
	
	// Convert using the built-in map:
	static struct {
		EMCSBiome    m_Biome;
		const char * m_String;
	} BiomeMap[] =
	{
		{biOcean,            "Ocean"} ,
		{biPlains,           "Plains"},
		{biDesert,           "Desert"},
		{biExtremeHills,     "ExtremeHills"},
		{biForest,           "Forest"},
		{biTaiga,            "Taiga"},
		{biSwampland,        "Swampland"},
		{biRiver,            "River"},
		{biHell,             "Hell"},
		{biHell,             "Nether"},
		{biSky,              "Sky"},
		{biFrozenOcean,      "FrozenOcean"},
		{biFrozenRiver,      "FrozenRiver"},
		{biIcePlains,        "IcePlains"},
		{biIcePlains,        "Tundra"},
		{biIceMountains,     "IceMountains"},
		{biMushroomIsland,   "MushroomIsland"},
		{biMushroomShore,    "MushroomShore"},
		{biBeach,            "Beach"},
		{biDesertHills,      "DesertHills"},
		{biForestHills,      "ForestHills"},
		{biTaigaHills,       "TaigaHills"},
		{biExtremeHillsEdge, "ExtremeHillsEdge "},
		{biJungle,           "Jungle"},
		{biJungleHills,      "JungleHills"},
	} ;
	
	for (int i = 0; i < ARRAYCOUNT(BiomeMap); i++)
	{
		if (NoCaseCompare(BiomeMap[i].m_String, a_BiomeString) == 0)
		{
			return BiomeMap[i].m_Biome;
		}
	}  // for i - BiomeMap[]
	return (EMCSBiome)-1;
}





// This is actually just some code that needs to run at program startup, so it is wrapped into a global var's constructor:
class cBlockPropertiesInitializer
{
public:
	cBlockPropertiesInitializer(void)
	{
		memset( g_BlockLightValue,         0x00, sizeof( g_BlockLightValue ) );
		memset( g_BlockSpreadLightFalloff, 0x0f, sizeof( g_BlockSpreadLightFalloff ) ); // 0x0f means total falloff
		memset( g_BlockTransparent,        0x00, sizeof( g_BlockTransparent ) );
		memset( g_BlockOneHitDig,          0x00, sizeof( g_BlockOneHitDig ) );
		memset( g_BlockPistonBreakable,    0x00, sizeof( g_BlockPistonBreakable ) );
		memset( g_BlockIsSnowable,         0xff, sizeof( g_BlockIsSnowable));  // Set all blocks' snowable to true

		// Emissive blocks
		g_BlockLightValue[E_BLOCK_FIRE]                 = 15;
		g_BlockLightValue[E_BLOCK_GLOWSTONE]            = 15;
		g_BlockLightValue[E_BLOCK_JACK_O_LANTERN]       = 15;
		g_BlockLightValue[E_BLOCK_LAVA]                 = 15;
		g_BlockLightValue[E_BLOCK_STATIONARY_LAVA]      = 15;
		g_BlockLightValue[E_BLOCK_END_PORTAL]           = 15;
		g_BlockLightValue[E_BLOCK_REDSTONE_LAMP_ON]     = 15;
		g_BlockLightValue[E_BLOCK_TORCH]                = 14;
		g_BlockLightValue[E_BLOCK_BURNING_FURNACE]      = 13;
		g_BlockLightValue[E_BLOCK_NETHER_PORTAL]        = 11;
		g_BlockLightValue[E_BLOCK_REDSTONE_ORE_GLOWING] = 9;
		g_BlockLightValue[E_BLOCK_REDSTONE_REPEATER_ON] = 9;
		g_BlockLightValue[E_BLOCK_REDSTONE_TORCH_ON]    = 7;
		g_BlockLightValue[E_BLOCK_BREWING_STAND]        = 1;
		g_BlockLightValue[E_BLOCK_BROWN_MUSHROOM]       = 1;
		g_BlockLightValue[E_BLOCK_DRAGON_EGG]           = 1;

		// Spread blocks
		g_BlockSpreadLightFalloff[E_BLOCK_AIR]              = 1;
		g_BlockSpreadLightFalloff[E_BLOCK_FIRE]             = 1;
		g_BlockSpreadLightFalloff[E_BLOCK_GLASS]            = 1;
		g_BlockSpreadLightFalloff[E_BLOCK_GLOWSTONE]        = 1;
		g_BlockSpreadLightFalloff[E_BLOCK_LEAVES]           = 1;
		g_BlockSpreadLightFalloff[E_BLOCK_SIGN_POST]        = 1;
		g_BlockSpreadLightFalloff[E_BLOCK_TORCH]            = 1;
		g_BlockSpreadLightFalloff[E_BLOCK_WALLSIGN]         = 1;
		// Light in water and lava dissapears faster:
		g_BlockSpreadLightFalloff[E_BLOCK_LAVA]             = 2;
		g_BlockSpreadLightFalloff[E_BLOCK_STATIONARY_LAVA]  = 2;
		g_BlockSpreadLightFalloff[E_BLOCK_STATIONARY_WATER] = 2;
		g_BlockSpreadLightFalloff[E_BLOCK_WATER]            = 2;

		// Transparent blocks
		g_BlockTransparent[E_BLOCK_AIR]            = true;
		g_BlockTransparent[E_BLOCK_BROWN_MUSHROOM] = true;
		g_BlockTransparent[E_BLOCK_FIRE]           = true;
		g_BlockTransparent[E_BLOCK_GLASS]          = true;
		g_BlockTransparent[E_BLOCK_ICE]            = true;
		g_BlockTransparent[E_BLOCK_RED_MUSHROOM]   = true;
		g_BlockTransparent[E_BLOCK_RED_ROSE]       = true;
		g_BlockTransparent[E_BLOCK_SIGN_POST]      = true;
		g_BlockTransparent[E_BLOCK_SNOW]           = true;
		g_BlockTransparent[E_BLOCK_TALL_GRASS]     = true;
		g_BlockTransparent[E_BLOCK_TORCH]          = true;
		g_BlockTransparent[E_BLOCK_WALLSIGN]       = true;
		g_BlockTransparent[E_BLOCK_YELLOW_FLOWER]  = true;

		// TODO: Any other transparent blocks?

		// One hit break blocks
		g_BlockOneHitDig[E_BLOCK_BROWN_MUSHROOM]        = true;
		g_BlockOneHitDig[E_BLOCK_CROPS]                 = true;
		g_BlockOneHitDig[E_BLOCK_FIRE]                  = true;
		g_BlockOneHitDig[E_BLOCK_LOCKED_CHEST]          = true;
		g_BlockOneHitDig[E_BLOCK_REDSTONE_REPEATER_OFF] = true;
		g_BlockOneHitDig[E_BLOCK_REDSTONE_REPEATER_ON]  = true;
		g_BlockOneHitDig[E_BLOCK_REDSTONE_TORCH_OFF]    = true;
		g_BlockOneHitDig[E_BLOCK_REDSTONE_TORCH_ON]     = true;
		g_BlockOneHitDig[E_BLOCK_REDSTONE_WIRE]         = true;
		g_BlockOneHitDig[E_BLOCK_REDSTONE_WIRE]         = true;
		g_BlockOneHitDig[E_BLOCK_RED_MUSHROOM]          = true;
		g_BlockOneHitDig[E_BLOCK_RED_ROSE]              = true;
		g_BlockOneHitDig[E_BLOCK_REEDS]                 = true;
		g_BlockOneHitDig[E_BLOCK_SAPLING]               = true;
		g_BlockOneHitDig[E_BLOCK_TNT]                   = true;
		g_BlockOneHitDig[E_BLOCK_TORCH]                 = true;
		g_BlockOneHitDig[E_BLOCK_YELLOW_FLOWER]         = true;

		// Blocks that breaks when pushed by piston
		g_BlockPistonBreakable[E_BLOCK_AIR]                   = true;
		g_BlockPistonBreakable[E_BLOCK_BED]                   = true;
		g_BlockPistonBreakable[E_BLOCK_BROWN_MUSHROOM]        = true;
		g_BlockPistonBreakable[E_BLOCK_COBWEB]                = true;
		g_BlockPistonBreakable[E_BLOCK_CROPS]                 = true;
		g_BlockPistonBreakable[E_BLOCK_DEAD_BUSH]             = true;
		g_BlockPistonBreakable[E_BLOCK_FIRE]                  = true;
		g_BlockPistonBreakable[E_BLOCK_IRON_DOOR]             = true;
		g_BlockPistonBreakable[E_BLOCK_JACK_O_LANTERN]        = true;
		g_BlockPistonBreakable[E_BLOCK_LADDER]                = true;
		g_BlockPistonBreakable[E_BLOCK_LAVA]                  = false;
		g_BlockPistonBreakable[E_BLOCK_LEVER]                 = true;
		g_BlockPistonBreakable[E_BLOCK_MELON]                 = true;
		g_BlockPistonBreakable[E_BLOCK_MELON_STEM]            = true;
		g_BlockPistonBreakable[E_BLOCK_PUMPKIN]               = true;
		g_BlockPistonBreakable[E_BLOCK_PUMPKIN_STEM]          = true;
		g_BlockPistonBreakable[E_BLOCK_REDSTONE_TORCH_OFF]    = true;
		g_BlockPistonBreakable[E_BLOCK_REDSTONE_TORCH_ON]     = true;
		g_BlockPistonBreakable[E_BLOCK_REDSTONE_WIRE]         = true;
		g_BlockPistonBreakable[E_BLOCK_RED_MUSHROOM]          = true;
		g_BlockPistonBreakable[E_BLOCK_RED_ROSE]              = true;
		g_BlockPistonBreakable[E_BLOCK_REEDS]                 = true;
		g_BlockPistonBreakable[E_BLOCK_SNOW]                  = true;
		g_BlockPistonBreakable[E_BLOCK_STATIONARY_LAVA]       = false;
		g_BlockPistonBreakable[E_BLOCK_STATIONARY_WATER]      = false;  //This gave pistons the ability to drop water :D
		g_BlockPistonBreakable[E_BLOCK_STONE_BUTTON]          = true;
		g_BlockPistonBreakable[E_BLOCK_STONE_PRESSURE_PLATE]  = true;
		g_BlockPistonBreakable[E_BLOCK_TALL_GRASS]            = true;
		g_BlockPistonBreakable[E_BLOCK_TORCH]                 = true;
		g_BlockPistonBreakable[E_BLOCK_VINES]                 = true;
		g_BlockPistonBreakable[E_BLOCK_WATER]                 = false;
		g_BlockPistonBreakable[E_BLOCK_WOODEN_DOOR]           = true;
		g_BlockPistonBreakable[E_BLOCK_WOODEN_PRESSURE_PLATE] = true;
		g_BlockPistonBreakable[E_BLOCK_YELLOW_FLOWER]         = true;

		// Blocks that can be snowed over:
		g_BlockIsSnowable[E_BLOCK_BROWN_MUSHROOM]        = false;
		g_BlockIsSnowable[E_BLOCK_CACTUS]                = false;
		g_BlockIsSnowable[E_BLOCK_CHEST]                 = false;
		g_BlockIsSnowable[E_BLOCK_CROPS]                 = false;
		g_BlockIsSnowable[E_BLOCK_FIRE]                  = false;
		g_BlockIsSnowable[E_BLOCK_FIRE]                  = false;
		g_BlockIsSnowable[E_BLOCK_GLASS]                 = false;
		g_BlockIsSnowable[E_BLOCK_ICE]                   = false;
		g_BlockIsSnowable[E_BLOCK_LAVA]                  = false;
		g_BlockIsSnowable[E_BLOCK_LOCKED_CHEST]          = false;
		g_BlockIsSnowable[E_BLOCK_REDSTONE_REPEATER_OFF] = false;
		g_BlockIsSnowable[E_BLOCK_REDSTONE_REPEATER_ON]  = false;
		g_BlockIsSnowable[E_BLOCK_REDSTONE_TORCH_OFF]    = false;
		g_BlockIsSnowable[E_BLOCK_REDSTONE_TORCH_ON]     = false;
		g_BlockIsSnowable[E_BLOCK_REDSTONE_WIRE]         = false;
		g_BlockIsSnowable[E_BLOCK_RED_MUSHROOM]          = false;
		g_BlockIsSnowable[E_BLOCK_RED_ROSE]              = false;
		g_BlockIsSnowable[E_BLOCK_REEDS]                 = false;
		g_BlockIsSnowable[E_BLOCK_SAPLING]               = false;
		g_BlockIsSnowable[E_BLOCK_SIGN_POST]             = false;
		g_BlockIsSnowable[E_BLOCK_SNOW]                  = false;
		g_BlockIsSnowable[E_BLOCK_STATIONARY_LAVA]       = false;
		g_BlockIsSnowable[E_BLOCK_STATIONARY_WATER]      = false;
		g_BlockIsSnowable[E_BLOCK_TALL_GRASS]            = false;
		g_BlockIsSnowable[E_BLOCK_TNT]                   = false;
		g_BlockIsSnowable[E_BLOCK_TORCH]                 = false;
		g_BlockIsSnowable[E_BLOCK_WALLSIGN]              = false;
		g_BlockIsSnowable[E_BLOCK_WATER]                 = false;
		g_BlockIsSnowable[E_BLOCK_YELLOW_FLOWER]         = false;
	}	
} BlockPropertiesInitializer;
		


