#include "Map3D.h"
#include "RandomWrapper.h"

#ifdef _WIN32
//simple windows console color
#include <windows.h>
#endif

namespace world
{
	Map3D::Map3D()
	{
		dimensions.Set(0, 0, 0);
	}

	Map3D::Map3D(int x, int y, int z)
	{
		dimensions.Set(x, y, z);
		initMap();
	}

	int Map3D::getIndex(int x, int y, int z)
	{
		return x 
			+ y * dimensions.x 
			+ z * dimensions.x * dimensions.y;
	}

	dims::Point3D Map3D::getPoint(int index)
	{
		int x = index % dimensions.x;
		int y = (index / dimensions.x) % dimensions.y;
		int z = index / (dimensions.x * dimensions.y);
		return dims::Point3D(x, y, z);
	}

	bool Map3D::isOpaque(int x, int y, int z)
	{
		return tiles[getIndex(x, y, z)].isOpaque;
	}

	char Map3D::getSeenChar(int x, int y, int z, int CurrentTurn)
	{

#ifdef _WIN32  
		//simple windows console color
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

		int idx = getIndex(x, y, z);
		switch (tiles[idx].getSeenStatus(CurrentTurn))
		{
		case world::SeenStatus::Seen:
		{		

#ifdef _WIN32	  
			//simple windows console color
			SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
#endif

			if (tiles[idx].isOpaque)
			{
				return '#';
			}
			//if the tile underneath is opaque, then return '.'
			int subIdx = getIndex(x, y, z - 1);
			if (tiles[subIdx].isOpaque)
			{
				return '.';
			}
			return ' ';
		}
		case world::SeenStatus::Remembered:
		{
			return ' ';

#ifdef _WIN32	  
			//simple windows console color
			SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);
#endif

			if (tiles[idx].isOpaque)
			{
				return '#';
			}
			//if the tile underneath is opaque, then return '.'
			int subIdx = getIndex(x, y, z - 1);
			if (tiles[subIdx].isOpaque)
			{
				return '.';
			}
			//return ' ';
		}				   			
		case world::SeenStatus::Unseen:
			//return '~';
			return ' ';
			break;
		default:
			return ' ';
			break;
		}

	}

	void Map3D::initMap()
	{
		tiles.resize(dimensions.x * dimensions.y * dimensions.z);
		dims::Point3D point;
		for (int i = 0; i < tiles.size(); i++)
		{
			point = getPoint(i);
			tiles[i].initTile();
		}
	}

	void Map3D::setTile(int x, int y, int z, bool isOpaque)
	{
		tiles[getIndex(x, y, z)].initTile(isOpaque);
	}

	void Map3D::createRect(dims::Point3D BotLeft, dims::Point3D TopRight, bool IsOpaque)
	{
		for (int x = BotLeft.x; x <= TopRight.x; x++)
		{
			for (int y = BotLeft.y; y <= TopRight.y; y++)
			{
				for (int z = BotLeft.z; z <= TopRight.z; z++)
				{
					setTile(x, y, z, IsOpaque);
				}
			}
		}
	}

	void Map3D::createHollowRect(dims::Point3D BotLeft, dims::Point3D TopRight, bool IsOpaque)
	{		
		for (int x = BotLeft.x; x <= TopRight.x; x++)
		{
			for (int y = BotLeft.y; y <= TopRight.y; y++)
			{
				for (int z = BotLeft.z; z <= TopRight.z; z++)
				{
					if (z == BotLeft.z || z == TopRight.z || y == BotLeft.y || y == TopRight.y || x == BotLeft.x || x == TopRight.x)
					{
						setTile(x, y, z, true);
					}
					else
					{
						setTile(x, y, z, false);
					}
				}
			}
		}
	}

	void Map3D::createRandomRect(dims::Point3D BotLeft, dims::Point3D TopRight, int density, bool isOpaque)
	{
		int rndTst;
		for (int x = BotLeft.x; x <= TopRight.x; x++)
		{
			for (int y = BotLeft.y; y <= TopRight.y; y++)
			{
				for (int z = BotLeft.z; z <= TopRight.z; z++)
				{  
					rndTst = RND::rnd.intRand(0, 100);
					if (rndTst < density)
					{
						setTile(x, y, z, isOpaque);
					}
				}
			}
		}

	}

	void Map3D::createPillars(dims::Point3D BotLeft, dims::Point3D TopRight, int Spacing)
	{
		for (int x = BotLeft.x; x <= TopRight.x; x+=Spacing)
		{
			for (int y = BotLeft.y; y <= TopRight.y; y += Spacing)
			{
				for (int z = BotLeft.z; z <= TopRight.z; z += Spacing)
				{
					setTile(x, y, z, true);
				}
			}
		}
	}

	void Map3D::printMap(int StartZ, int EndZ, int CurTurn, dims::Point3D ViewLoc)
	{
		for (int z = StartZ; z <= EndZ; z++)
		{
			std::cout << "Z: " << z << std::endl;
			for (int y = 0; y < dimensions.y; y++)
			{
				for (int x = 0; x < dimensions.x; x++)
				{
					if (x == ViewLoc.x && y == ViewLoc.y && z == ViewLoc.z)
					{
						std::cout << "@";
						continue;
					}
					std::cout << getSeenChar(x, y, z, CurTurn);
				}
				std::cout << std::endl;
			}
		}
	}

	void Map3D::setAllSeen()
	{
		for (int i = 0; i < tiles.size(); i++)
		{
			tiles[i].setSeen(0);
		}
	}

	void Map3D::createTestMap()
	{
		dims::Point3D viewLoc = dims::Point3D(14,4,3);
		tiles[getIndex(viewLoc.x, viewLoc.y, viewLoc.z)].isOpaque = true;
		viewLoc = dims::Point3D(16, 4, 3);
		tiles[getIndex(viewLoc.x, viewLoc.y, viewLoc.z)].isOpaque = true;

		//block above

		viewLoc = dims::Point3D(14, 4, 4);
		tiles[getIndex(viewLoc.x, viewLoc.y, viewLoc.z)].isOpaque = true;
		viewLoc = dims::Point3D(15, 4, 4);
		tiles[getIndex(viewLoc.x, viewLoc.y, viewLoc.z)].isOpaque = true;
		viewLoc = dims::Point3D(16, 4, 4);
		tiles[getIndex(viewLoc.x, viewLoc.y, viewLoc.z)].isOpaque = true;


		viewLoc = dims::Point3D(14, 5, 4);
		tiles[getIndex(viewLoc.x, viewLoc.y, viewLoc.z)].isOpaque = true;
		viewLoc = dims::Point3D(15, 5, 4);
		tiles[getIndex(viewLoc.x, viewLoc.y, viewLoc.z)].isOpaque = true;
		viewLoc = dims::Point3D(16, 5, 4);
		tiles[getIndex(viewLoc.x, viewLoc.y, viewLoc.z)].isOpaque = true;


		viewLoc = dims::Point3D(14, 5, 3);
		tiles[getIndex(viewLoc.x, viewLoc.y, viewLoc.z)].isOpaque = true;
		viewLoc = dims::Point3D(16, 5, 3);
		tiles[getIndex(viewLoc.x, viewLoc.y, viewLoc.z)].isOpaque = true;

		viewLoc = dims::Point3D(14, 5, 5);
		tiles[getIndex(viewLoc.x, viewLoc.y, viewLoc.z)].isOpaque = true;
		viewLoc = dims::Point3D(15, 5, 5);
		tiles[getIndex(viewLoc.x, viewLoc.y, viewLoc.z)].isOpaque = true;
		viewLoc = dims::Point3D(16, 5, 5);
		tiles[getIndex(viewLoc.x, viewLoc.y, viewLoc.z)].isOpaque = true;

		viewLoc = dims::Point3D(14, 6, 3);
		tiles[getIndex(viewLoc.x, viewLoc.y, viewLoc.z)].isOpaque = true;
		viewLoc = dims::Point3D(16, 6, 3);
		tiles[getIndex(viewLoc.x, viewLoc.y, viewLoc.z)].isOpaque = true;

		viewLoc = dims::Point3D(14, 6, 4);
		tiles[getIndex(viewLoc.x, viewLoc.y, viewLoc.z)].isOpaque = true;
		viewLoc = dims::Point3D(15, 6, 4);
		tiles[getIndex(viewLoc.x, viewLoc.y, viewLoc.z)].isOpaque = true;
		viewLoc = dims::Point3D(16, 6, 4);
		tiles[getIndex(viewLoc.x, viewLoc.y, viewLoc.z)].isOpaque = true;

		viewLoc = dims::Point3D(14, 7, 3);
		tiles[getIndex(viewLoc.x, viewLoc.y, viewLoc.z)].isOpaque = true;
		viewLoc = dims::Point3D(16, 7, 3);
		tiles[getIndex(viewLoc.x, viewLoc.y, viewLoc.z)].isOpaque = true;

		viewLoc = dims::Point3D(14, 7, 4);
		tiles[getIndex(viewLoc.x, viewLoc.y, viewLoc.z)].isOpaque = true;
		viewLoc = dims::Point3D(15, 7, 4);
		tiles[getIndex(viewLoc.x, viewLoc.y, viewLoc.z)].isOpaque = true;
		viewLoc = dims::Point3D(16, 7, 4);
		tiles[getIndex(viewLoc.x, viewLoc.y, viewLoc.z)].isOpaque = true;


		//viewLoc = dims::Point3D(14, 8, 3);
		//tiles[getIndex(viewLoc.x, viewLoc.y, viewLoc.z)].isOpaque = true;
		viewLoc = dims::Point3D(15, 8, 3);
		tiles[getIndex(viewLoc.x, viewLoc.y, viewLoc.z)].isOpaque = true;

		viewLoc = dims::Point3D(14, 8, 4);
		tiles[getIndex(viewLoc.x, viewLoc.y, viewLoc.z)].isOpaque = true;
		viewLoc = dims::Point3D(15, 8, 4);
		tiles[getIndex(viewLoc.x, viewLoc.y, viewLoc.z)].isOpaque = true;
		viewLoc = dims::Point3D(16, 8, 4);
		tiles[getIndex(viewLoc.x, viewLoc.y, viewLoc.z)].isOpaque = true;


	}

	Map3D::~Map3D()
	{

	}
}

