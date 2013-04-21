#ifndef MAP_H
#define MAP_H

#include <utility>
#include <map>
#include <memory>

#include "point.h"

#define BLOCKSIZE 8

class Map
{
	public:
		struct Sector {
			Point points[BLOCKSIZE][BLOCKSIZE];
		};

	protected:
		typedef std::pair<int32_t, int32_t> Coord;
		typedef std::map<Coord, Sector> SectorMap;
		SectorMap sectors;

	public:
		inline SectorMap::const_iterator begin(){ return sectors.begin(); }
		inline SectorMap::const_iterator end(){ return sectors.end(); }
		inline size_t size(){ return sectors.size(); }

		inline Point* getPoint(int32_t x, int32_t y)
		{
			Coord value(x/BLOCKSIZE,y/BLOCKSIZE);
			return &(sectors[value].points[y % BLOCKSIZE][x % BLOCKSIZE]);
		}

		inline Point* getPoint(int32_t x, int32_t y, int32_t ix, int32_t iy)
		{
			Coord value(x,y);
			return &(sectors[value].points[iy][ix]);
		}

		inline Sector* getSector(int32_t x, int32_t y)
		{
			Coord value(x,y);
			return &(sectors[value]);
		}

};

#endif
