#pragma once
#include "SingletonBase.h"
#include "GImage.h"

class ImageManager : public SingletonBase<ImageManager>
{
private:
    typedef map<string, GImage*> mapImageList;
    typedef map<string, GImage*>::iterator mapImageIter;

private:
    mapImageList _mImageList;

public:
    HRESULT init(void);
    void release(void);

    GImage* addImage(string strKey, int width, int height);
    GImage* addImage(string strKey, const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
    GImage* addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

    GImage* addFrameImage(string strKey, const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
    GImage* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

    GImage* findImage(string strKey);

    bool deleteImage(string strkey);
    bool deleteAll();

    // ==============����==================
    void render(string strKey, HDC hdc);
    void render(string strKey, HDC hdc, int destX, int destY);

    // �̹��� Ŭ���� -> ���ϴ� ��ŭ �̹����� �߶� �׸���
    void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourwidth, int sourheight);
    void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sizeX, int sizeY, int sourwidth, int sourheight);

    // �˹� ����
    void alphaRender(string strKey, HDC hdc, BYTE alpha);      // BYTE �ڷ����� 0~255 ũ�⸦ ������ -> ���İ��� �� ����
    void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
    void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourwidth, int sourheight, BYTE alpha);

    //������ ����
    void frameRender(string strKey, HDC hdc, int destX, int destY);
    void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
    void frameAlphaRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

    // ���� ����
    void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
    void loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

    ImageManager()
    {}
    ~ImageManager()
    {}
};

