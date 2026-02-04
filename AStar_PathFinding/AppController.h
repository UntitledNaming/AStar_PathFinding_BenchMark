#pragma once


class AppController
{
public:
	enum class RunMode
	{
		Manual = 0,
		Auto   = 1,
	};

	struct settings
	{
		RunMode s_mode      = RunMode::Manual;
		INT     s_mapWidth  = 150;
		INT     s_mapHeight = 100;
		INT     s_gridSize  = 10;
	};

public:
	AppController() = default;
	~AppController();

	void controller_settings(const settings& src);

	// 객체 사용 핸들러 
	void OnPaint(HWND hWnd, HDC hdc);
	void OnMouseWheel();
	void OnLButtonDown();

private:
	RunMode      m_mode; // 수동 맵 생성, 자동 맵 생성
	Map          m_map;
	MapGenerator m_generator;
	Renderer     m_renderer;
	PathFinder   m_pathfinder;
};

