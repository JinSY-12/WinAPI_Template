#include "Stdafx.h"

#include "MainGame.h"

// �������� ���� �����÷� ��θ� �����
// ������ ex) "C:/User/Desktop/user/....../WinAPI"
// ����� ex) "../WinAPI/"

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