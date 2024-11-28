#include "Map3D.h"
#include <iostream>
#include "Fov3D_3.h"


int main()
{
	//define a world 30x30x20
	world::Map3D map = world::Map3D(30,30,20);
	//view location begins at (3,3,3)
	dims::Point3D viewLoc = dims::Point3D(3, 3, 3);
	//curTurn to determine what is seen vs remembered
	int curTurn = 0;

	//create a flat plane to walk on
	map.createRect(dims::Point3D(2, 2, 2), dims::Point3D(28, 28, 2), true);
	////fill 20% of the map with random obstructions
	//map.createRandomRect(dims::Point3D(2, 2, 3), dims::Point3D(28, 28, 3), 20, true);	
	////create a hallway with diagonal exits to test viewing at angles
	//map.createTestMap();
	//create pillars
	map.createPillars(dims::Point3D(8, 8, 3), dims::Point3D(22, 22, 3), 2);
	//create a room
	map.createHollowRect(dims::Point3D(1, 1, 2), dims::Point3D(7, 7, 4), true);
	//create a door in the room
	map.setTile(7, 4, 3, false);

	//create a room in the sky
	map.createHollowRect(dims::Point3D(7, 3, 6), dims::Point3D(12, 12, 8), true);
	//add a hole to the bottom
	map.setTile(8, 4, 6, false);
	map.setTile(8, 5, 6, false);
	map.setTile(8, 6, 6, false);
	map.setTile(8, 7, 6, false);
	//ensure the initial view location is free
	map.tiles[map.getIndex(viewLoc.x, viewLoc.y, viewLoc.z)].isOpaque = false;

	
	//map.setAllSeen();
	
	//display levels 1-4
	map.printMap(1, 4, curTurn++, viewLoc);

	//init fov and provide the map
	world::Fov3D_3 fov = world::Fov3D_3(&map);
	//compute the initial fov from the viewLoc with a 30 tile radius
	fov.computeFov(viewLoc, 30, curTurn);

	map.printMap(3, 3, curTurn++, viewLoc);

	char quitter;
	std::cin >> quitter;

	//simple movement (wasd) and up/down (<>) to move up and down levels
	//press m to print levels 3-8
	while (quitter != 'q')
	{
		if (quitter == 'w')
		{
			dims::Point3D newLoc = viewLoc;
			newLoc.y--;
			if (!map.isOpaque(newLoc.x, newLoc.y, newLoc.z))
			{
				viewLoc = newLoc;
			}			
		}
		else if (quitter == 'a')
		{
			dims::Point3D newLoc = viewLoc;
			newLoc.x--;
			if (!map.isOpaque(newLoc.x, newLoc.y, newLoc.z))
			{
				viewLoc = newLoc;
			}
		}
		else if (quitter == 'd')
		{
			dims::Point3D newLoc = viewLoc;
			newLoc.x++;
			if (!map.isOpaque(newLoc.x, newLoc.y, newLoc.z))
			{
				viewLoc = newLoc;
			}
		}
		else if (quitter == 's')
		{
			dims::Point3D newLoc = viewLoc;
			newLoc.y++;
			if (!map.isOpaque(newLoc.x, newLoc.y, newLoc.z))
			{
				viewLoc = newLoc;
			}
		}
		else if (quitter == '<')
		{
			dims::Point3D newLoc = viewLoc;
			newLoc.z++;
			if (!map.isOpaque(newLoc.x, newLoc.y, newLoc.z))
			{
				viewLoc = newLoc;
			}
		}
		else if (quitter == '>')
		{
			dims::Point3D newLoc = viewLoc;
			newLoc.z--;
			if (!map.isOpaque(newLoc.x, newLoc.y, newLoc.z))
			{
				viewLoc = newLoc;
			}
		}
		fov.computeFov(viewLoc, 30, curTurn);
		//type m to see a couple levels above you
		map.printMap(quitter == 'm' ? 3 : viewLoc.z, (quitter == 'm' ? 8 : viewLoc.z), curTurn++, viewLoc);

		std::cin >> quitter;

	}

	//print levels 2-6 before quitting
	map.printMap(2, 6, --curTurn, viewLoc);


	std::cin >> quitter;

	return 0;
}