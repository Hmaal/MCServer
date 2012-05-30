
// Trees.h

// Interfaces to helper functions used for generating trees

/*
Note that all of these functions must generate the same tree image for the same input (x, y, z, seq)
	- cStructGenTrees depends on this
To generate a random image for the (x, y, z) coords, pass an arbitrary value as (seq).
*/





#pragma once

#include "ChunkDef.h"
#include "cNoise.h"





// Blocks that don't block tree growth:
#define CASE_TREE_ALLOWED_BLOCKS \
	case E_BLOCK_AIR: \
	case E_BLOCK_LEAVES: \
	case E_BLOCK_SNOW: \
	case E_BLOCK_TALL_GRASS: \
	case E_BLOCK_DEAD_BUSH: \
	case E_BLOCK_SAPLING: \
	case E_BLOCK_VINES

// Blocks that a tree may overwrite when growing:
#define CASE_TREE_OVERWRITTEN_BLOCKS \
	case E_BLOCK_AIR: \
	case E_BLOCK_LEAVES: \
	case E_BLOCK_SNOW: \
	case E_BLOCK_TALL_GRASS: \
	case E_BLOCK_DEAD_BUSH: \
	case E_BLOCK_SAPLING: \
	case E_BLOCK_VINES





/// Generates an image of a tree at the specified coords (lowest trunk block) in the specified biome
void GetTreeImageByBiome(int a_BlockX, int a_BlockY, int a_BlockZ, cNoise & a_Noise, int a_Seq, EMCSBiome a_Biome, sSetBlockVector & a_Blocks);

/// Generates an image of a random apple tree
void GetAppleTreeImage(int a_BlockX, int a_BlockY, int a_BlockZ, cNoise & a_Noise, int a_Seq, sSetBlockVector & a_Blocks);

/// Generates an image of a small (nonbranching) apple tree
void GetSmallAppleTreeImage(int a_BlockX, int a_BlockY, int a_BlockZ, cNoise & a_Noise, int a_Seq, sSetBlockVector & a_Blocks);

/// Generates an image of a large (branching) apple tree
void GetLargeAppleTreeImage(int a_BlockX, int a_BlockY, int a_BlockZ, cNoise & a_Noise, int a_Seq, sSetBlockVector & a_Blocks);

/// Generates an image of a random birch tree
void GetBirchTreeImage(int a_BlockX, int a_BlockY, int a_BlockZ, cNoise & a_Noise, int a_Seq, sSetBlockVector & a_Blocks);

/// Generates an image of a random conifer tree
void GetConiferTreeImage(int a_BlockX, int a_BlockY, int a_BlockZ, cNoise & a_Noise, int a_Seq, sSetBlockVector & a_Blocks);

/// Generates an image of a random spruce (short conifer, two layers of leaves)
void GetSpruceTreeImage(int a_BlockX, int a_BlockY, int a_BlockZ, cNoise & a_Noise, int a_Seq, sSetBlockVector & a_Blocks);

/// Generates an image of a random pine (tall conifer, little leaves at top)
void GetPineTreeImage(int a_BlockX, int a_BlockY, int a_BlockZ, cNoise & a_Noise, int a_Seq, sSetBlockVector & a_Blocks);

/// Generates an image of a random swampland tree
void GetSwampTreeImage(int a_BlockX, int a_BlockY, int a_BlockZ, cNoise & a_Noise, int a_Seq, sSetBlockVector & a_Blocks);

/// Generates an image of a random apple bush (for jungles)
void GetAppleBushImage(int a_BlockX, int a_BlockY, int a_BlockZ, cNoise & a_Noise, int a_Seq, sSetBlockVector & a_Blocks);

/// Generates an image of a random jungle tree
void GetJungleTreeImage(int a_BlockX, int a_BlockY, int a_BlockZ, cNoise & a_Noise, int a_Seq, sSetBlockVector & a_Blocks);




