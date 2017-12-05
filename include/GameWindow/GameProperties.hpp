#pragma once

enum class WindowMode
{
	Windowed,
	Fullscreen,
	HighestResolutionFullscreen
};

// TODO: Use Point and Size
struct GameProperties
{
	int Major = 3;
	int Minor = 3;
    int ResolutionWidth = 640;
	int ResolutionHeight = 320;
	int WindowPosX = 0;
	int WindowPosY = 0;
	WindowMode Mode = WindowMode::Windowed;
	const char* Title;
};
