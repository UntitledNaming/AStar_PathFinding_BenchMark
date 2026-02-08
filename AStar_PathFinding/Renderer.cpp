#include <windows.h>
#include <vector>
#include "framework.h"
#include "Map.h"
#include "Renderer.h"

Renderer::~Renderer()
{
	// 메모리 DC에 연결된 기존 BITMAP 연결 제거
	SelectObject(m_memDC, m_bitMapOld);

	// 메모리 DC에서 연결 끊은 비트맵 제거
	DeleteObject(m_bitMap);

	// 메모리 DC 제거
	DeleteObject(m_memDC);

	// 펜, 브러시 제거
	DeleteObject(m_gridPen);
	DeleteObject(m_wallBrush);
	DeleteObject(m_startBrush);
	DeleteObject(m_goalBrush);
	DeleteObject(m_pathPen);
}

void Renderer::Init(HWND hWnd)
{
	HDC hdc = GetDC(hWnd); // 윈도우 클라이언트 영역에 그릴 수 있는 hdc를 받기(대여)
	GetClientRect(hWnd, &m_rc);

	m_gridSize = 16;
	m_offsetX = 0;
	m_offsetY = 0;
	m_bitMap = CreateCompatibleBitmap(hdc, m_rc.right, m_rc.bottom);
	m_memDC = CreateCompatibleDC(hdc);
	ReleaseDC(hWnd, hdc); // hdc os에게 반납

	// 메모리 DC에 생성한 비트맵을 연결하고 기존에 연결되어 있던 비트맵을 리턴해서 받음
	m_bitMapOld = (HBITMAP)SelectObject(m_memDC, m_bitMap);

	// 펜 및 브러시 생성
	m_gridPen = CreatePen(PS_SOLID, 1, RGB(200, 200, 200));
	m_pathPen = CreatePen(PS_SOLID, 0, RGB(255, 0, 0));
	m_wallBrush = CreateSolidBrush((RGB(100, 100, 100)));
	m_startBrush = CreateSolidBrush((RGB(0, 255, 0)));
	m_goalBrush = CreateSolidBrush((RGB(0, 0, 255)));
	
}

void Renderer::Render(HWND hWnd, const Map& map)
{
	HDC hdc = GetDC(hWnd);

	PatBlt(m_memDC, 0, 0, m_rc.right, m_rc.bottom, WHITENESS);

	RenderPen(m_memDC, map);
	RenderBrush(m_memDC, map);

	BitBlt(hdc, 0, 0, m_rc.right, m_rc.bottom, m_memDC, 0, 0, SRCCOPY);

	ReleaseDC(hWnd, hdc);
}

void Renderer::RenderPen(HDC memdc, const Map& map)
{
	HPEN hOldPen = (HPEN)SelectObject(memdc, m_gridPen);

	int w = map.GetWidth();
	int h = map.GetHeight();
	int tileWPixel = w * m_gridSize;
	int tileHPixel = h * m_gridSize;

	// 타일 맵의 가로 타일 갯수 만큼 세로선 긋기
	for (int tx = 0; tx <= w; tx++)
	{
		int cx = m_offsetX + tx * m_gridSize;
		int y0 = m_offsetY;
		int y1 = m_offsetY + tileHPixel;

		MoveToEx(m_memDC, cx, y0, NULL);
		LineTo(memdc, cx, y1);
	}

	// 타일 맵의 세로 타일 갯수 만큼 가로선 긋기
	for (int ty = 0; ty <= h; ty++)
	{
		int cy = m_offsetY + ty * m_gridSize;
		int x0 = m_offsetX;
		int x1 = m_offsetX + tileWPixel;

		MoveToEx(m_memDC, x0, cy, NULL);
		LineTo(m_memDC, x1, cy);
	}


	// todo : 경로 줄 그리기
}

void Renderer::RenderBrush(HDC memdc, const Map& map)
{

}

