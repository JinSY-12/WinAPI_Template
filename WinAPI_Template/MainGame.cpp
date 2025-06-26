#include "Stdafx.h"

#include "MainGame.h"

// 역슬래시 말고 슬래시로 경로를 적어라
// 절대경로 ex) "C:/User/Desktop/user/....../WinAPI"
// 상대경로 ex) "../WinAPI/"

HRESULT MainGame::init(void)
{
	GameNode::init(true);

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();

}

void MainGame::update(void)
{
	GameNode::update();

}

void MainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);

	this->getBackBuffer()->render(getHDC());
}