#ifndef MAP_H
#define MAP_H

#include <utility>
#include <map>
#include <memory>

#include "point.h"

class Map
{
	public:
		struct Sector {
			Point points[256][256];
		};

	protected:
		typedef std::pair<int32_t, int32_t> Coord;
		typedef std::map<Coord, Sector> SectorMap;
		SectorMap sectors;

	public:
		Map();

		inline SectorMap::const_iterator begin(){ return sectors.begin(); }
		inline SectorMap::const_iterator end(){ return sectors.end(); }
		inline size_t size(){ return sectors.size(); }

		inline Point &getPoint(int32_t x, int32_t y)
		{
			Coord value(x/256,y/256);
			return sectors[value].points[y % 256][x % 256];
		}

		inline Sector* getSector(int32_t x, int32_t y)
		{
			return &sectors[std::make_pair(x / 256,y / 256)];
		}

};

#endif
