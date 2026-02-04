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

void AppController::controller_settings(const settings& src)
{
	m_mode = src.s_mode;


}
