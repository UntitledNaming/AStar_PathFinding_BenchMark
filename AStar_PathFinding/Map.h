#pragma once
class Map
{
public:
	enum class TileType
	{
		Empty = 0,
		Wall,
		Start,
		Goal
	};

	struct st_TilePos
	{
		INT s_xpos = -1;
		INT s_ypos = -1;
	}typedef TilePos;

public:
	Map();
	~Map();


private:
	std::vector<std::vector<CHAR>> m_tileMap; // 시작점과 종점
	INT                            m_width;
	INT                            m_height;
	TilePos                        m_start;
	TilePos                        m_goal;
};

