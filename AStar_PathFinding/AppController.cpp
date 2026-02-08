#include <windows.h>
#include <vector>
#include "Map.h"
#include "MapGenerator.h"
#include "Renderer.h"
#include "PathFinder.h"
#include "AppController.h"

AppController::~AppController()
{

}

void AppController::Init(const settings& src, HWND hWnd)
{
	m_mode = src.m_mode;

	m_map.Init(src.m_mapWidth, src.m_mapHeight);
	m_renderer.Init(hWnd);
}

void AppController::OnPaint(HWND hWnd)
{
	m_renderer.Render(hWnd, m_map);
}

void AppController::OnMouseWheel(HWND hwnd, int wheelDelta, int clientX, int clientY)
{
	int oldGridSize = m_renderer.GetGridSize();

	int step = 0;

	if (wheelDelta > 0)
		step = 2;
	else
		step = -2;

	int newGrid = oldGridSize + step;

	if (newGrid < 4)
		newGrid = 4;

	else if (newGrid > 80)
		newGrid = 80;

	if (newGrid == oldGridSize)
		return;

	// 기존 타일 좌표 계산
	int offsetX = m_renderer.GetOffsetX();
	int offsetY = m_renderer.GetOffsetY();
	int tileX = (clientX - offsetX) / oldGridSize;
	int tileY = (clientY - offsetY) / oldGridSize;

	// 새로운 GridSize와 계산한 타일 좌표를 기준으로 새로운 offset 계산
	m_renderer.SetZoomData(newGrid, clientX - tileX * newGrid, clientY - tileY * newGrid);
	InvalidateRect(hwnd, nullptr, FALSE);
}

void AppController::OnLButtonDown()
{
}

