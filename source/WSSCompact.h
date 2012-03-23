
// WSSCompact.h

// Interfaces to the cWSSCompact class representing the "Compact" storage schema (PAK-files)





#pragma once
#ifndef WSSCOMPACT_H_INCLUDED
#define WSSCOMPACT_H_INCLUDED

#include "WorldStorage.h"
#include "Vector3i.h"





class cWSSCompact :
	public cWSSchema
{
public:
	cWSSCompact(cWSInterface * a_WSI) : cWSSchema(a_WSI) {}
	virtual ~cWSSCompact();
	
protected:

	struct sChunkHeader;
	typedef std::vector<sChunkHeader *> sChunkHeaders;
	
	/// Implements a cache for a single PAK file; implements lazy-write in order to be able to write multiple chunks fast
	class cPAKFile
	{
	public:
	
		cPAKFile(const AString & a_FileName, int a_LayerX, int a_LayerZ);
		~cPAKFile();

		bool GetChunkData(const cChunkCoords & a_Chunk, int & a_UncompressedSize, AString & a_Data);
		bool SetChunkData(const cChunkCoords & a_Chunk, int a_UncompressedSize, const AString & a_Data);
		bool EraseChunkData(const cChunkCoords & a_Chunk);
		
		bool SaveChunk(const cChunkCoords & a_Chunk, cWSInterface * a_WSI);
		
		int GetLayerX(void) const {return m_LayerX; }
		int GetLayerZ(void) const {return m_LayerZ; }
		
		static const int PAK_VERSION = 1;
#if AXIS_ORDER == AXIS_ORDER_XZY
		static const int CHUNK_VERSION = 3;
#elif AXIS_ORDER == AXIS_ORDER_YZX
		static const int CHUNK_VERSION = 2;
#endif
	protected:
	
		AString m_FileName;
		int     m_LayerX;
		int     m_LayerZ;
		
		sChunkHeaders m_ChunkHeaders;
		AString       m_DataContents;  // Data contents of the file, cached
		
		int           m_NumDirty;  // Number of chunks that were written into m_DataContents but not into the file

		Vector3i      m_ChunkSize; // Is related to m_ChunkVersion
		char          m_ChunkVersion;
		char          m_PakVersion;
		
		bool SaveChunkToData(const cChunkCoords & a_Chunk, cWSInterface * a_WSI);  // Saves the chunk to m_DataContents, updates headers and m_NumDirty
		void SynchronizeFile(void);  // Writes m_DataContents along with the headers to file, resets m_NumDirty

		void UpdateChunk1To2(void); // Height from 128 to 256
		void UpdateChunk2To3(void); // Axis order from YZX to XZY
	} ;
	
	typedef std::list<cPAKFile *> cPAKFiles;
	
	cCriticalSection m_CS;
	cPAKFiles m_PAKFiles;  // A MRU cache of PAK files
	
	/// Loads the correct PAK file either from cache or from disk, manages the m_PAKFiles cache
	cPAKFile * LoadPAKFile(const cChunkCoords & a_Chunk);
	
	/// Gets chunk data from the correct file; locks CS as needed
	bool GetChunkData(const cChunkCoords & a_Chunk, int & a_UncompressedSize, AString & a_Data);
	
	/// Sets chunk data to the correct file; locks CS as needed
	bool SetChunkData(const cChunkCoords & a_Chunk, int a_UncompressedSize, const AString & a_Data);
	
	/// Erases chunk data from the correct file; locks CS as needed
	bool EraseChunkData(const cChunkCoords & a_Chunk);
	
	/// Loads the chunk from the data (no locking needed)
	bool LoadChunkFromData(const cChunkCoords & a_Chunk, int & a_UncompressedSize, const AString & a_Data, cWSInterface * a_WSI);
		
	void LoadEntitiesFromJson(Json::Value & a_Value, cEntityList & a_Entities, cBlockEntityList & a_BlockEntities, cWSInterface * a_WSI);

	// cWSSchema overrides:
	virtual bool LoadChunk(const cChunkCoords & a_Chunk) override;
	virtual bool SaveChunk(const cChunkCoords & a_Chunk) override;
	virtual const AString GetName(void) const override {return "compact"; }
} ;





#endif  // WSSCOMPACT_H_INCLUDED




