#pragma once
#ifndef map3d_h
#define map3d_h

#include <vector>
#include "Tile3D.h"


namespace world
{
	/// <summary>
	/// simple 3d map
	/// </summary>
	class Map3D
	{
	public:
		Map3D();
		~Map3D();
		Map3D(int x, int y, int z);

		dims::Point3D dimensions;
		std::vector<Tile3D> tiles;

		int getIndex(int x, int y, int z);
		dims::Point3D getPoint(int index);
		bool isOpaque(int x, int y, int z);
		char getSeenChar(int x, int y, int z, int CurrentTurn);

		void initMap();
		void setTile(int x, int y, int z, bool isOpaque);
		void createRect(dims::Point3D BotLeft, dims::Point3D TopRight, bool IsOpaque);
		void createHollowRect(dims::Point3D BotLeft, dims::Point3D TopRight, bool IsOpaque);
		void createRandomRect(dims::Point3D BotLeft, dims::Point3D TopRight, int density, bool isOpaque);
		void createPillars(dims::Point3D BotLeft, dims::Point3D TopRight, int Spacing);
		void printMap(int StartZ, int EndZ, int CurTurn, dims::Point3D ViewLoc);
		void setAllSeen();
		void createTestMap();
	};
}

#endif
