/*
 ============================================================================
 Name		: CharLcmControl.cpp
 Author	  : Yuan
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CCharLcmControl implementation
 ============================================================================
 */

#include "CharLcmControl.h"

CCharLcmControl::CCharLcmControl()
	{
	}

CCharLcmControl::~CCharLcmControl()
	{
	if (mFontGen)
		delete mFontGen;
	}

CCharLcmControl* CCharLcmControl::NewL(RWindow& aWindow)
	{
	CCharLcmControl* self = new (ELeave) CCharLcmControl;
	CleanupStack::PushL(self);
	self->ConstructL(aWindow);
	CleanupStack::Pop();
	return self;
	}
void CCharLcmControl::ConstructL(RWindow& aWindow)
	{

	SetContainerWindowL(aWindow);
	mIsFullScreen = false;

	// Size
	mSurfaceHeight = 150;
	mSurfaceWidth = 400;
	mCursorX = 0;
	mCursorY = 0;
	mColNum = 20;
	mRowNum = 6;

	mPositivePixelColor = KRgbRed;
	mNegativePixelColor = TRgb(0xcccccc);
	mLcdPanelColor = TRgb(0xeeeeee);

	for (int i = 0; i < 8 * 8; i++)
		{
		mCustomCharsRaw[i] = (char) 0x23; // ÌØÊâÍ¼Ñù
		}

	for (int i = 0; i < mRowNum * mColNum; i++)
		{
		mLcmChars[i] = ' '; // ¿Õ¸ñ×Ö·û
		}

	// No call to ActivateL() as the window is activated by its container
	}
void CCharLcmControl::SizeChanged()
	{
	TRect rect = Rect();
	mSurfaceHeight = rect.Height();
	mSurfaceWidth = rect.Width();
	TPoint colRowsize(mColNum, mRowNum);
	TPoint areaSize(rect.Width(), rect.Height());
	reGenResoures();
	}

void CCharLcmControl::Draw(const TRect& /*aRect*/) const
	{
	// Get the standard graphics context
	CWindowGc& gc = SystemGc();

	// Gets the control's extent
	TRect drawRect(Rect());

	// Clears the screen
	gc.SetBrushColor(mLcdPanelColor);
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	gc.Clear(drawRect);

	int dy = 0;
	TPoint postion;

	for (int y = 0; y < mRowNum; y++)
		{
		for (int x = 0; x < mColNum; x++)
			{
			mFontGen->getActualCursor(x, y, postion); // y*mColNum+x+32
			// now do what you want with it, such as blitting to the screen
			//CFbsBitmap* fontBitmap = mFontGen->genSingleFontBitmapL(43, 0.2,0.2);

			CFbsBitmap* fontBitmap = mFontGen->getCharBitmap(mLcmChars[dy + x]);
			if (fontBitmap != NULL)
				{
				gc.BitBlt(postion, fontBitmap);
				//gc.DrawBitmap(postion,fontBitmap);
				//TSize pesudoRectSize(30,30);
				//TRect pesudoRect(postion,pesudoRectSize);
				//gc.DrawRect(pesudoRect);
				}
			}
		dy += mColNum;
		}
	/*	// Shrink by about 15%
	 drawRect.Shrink(drawRect.Width() / 6, drawRect.Height() / 6);
	 // Pen size set to just over 10% of the shape¡¯s size
	 TSize penSize(drawRect.Width() / 9, drawRect.Height() / 9);
	 gc.SetPenSize(penSize);
	 gc.SetPenStyle(CGraphicsContext::ESolidPen);

	 TRgb cl(KRgbRed);
	 cl.SetAlpha(0);
	 gc.SetPenColor(KRgbRed);
	 gc.SetBrushColor(cl);
	 gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	 gc.DrawEllipse(drawRect);*/

	}

TRgb CCharLcmControl::getNegativePixelColor()
	{
	return mNegativePixelColor;
	}

void CCharLcmControl::setNegativePixelColor(TRgb &negativePixelColor)
	{
	mNegativePixelColor = negativePixelColor;
	reGenResoures();
	forceReDraw();
	}

TRgb CCharLcmControl::getPositivePixelColor()
	{
	return mPositivePixelColor;
	}

void CCharLcmControl::setPositivePixelColor(TRgb &positivePixelColor)
	{
	mPositivePixelColor = positivePixelColor;
	reGenResoures();
	forceReDraw();
	}

TRgb CCharLcmControl::getLcdPanelColor()
	{
	return mLcdPanelColor;
	}

void CCharLcmControl::setLcdPanelColor(TRgb &lcdPanelColor)
	{
	mLcdPanelColor = lcdPanelColor;
	reGenResoures();
	forceReDraw();
	}

void CCharLcmControl::forceReDraw()
	{
	DrawNow();
	}

void CCharLcmControl::write(const char *data, int len)
	{
	memcpy(
			mLcmChars + mCursorX + mCursorY * mColNum,
			data,
			len + mCursorX + mCursorY * mColNum <= mRowNum * mColNum ? len
					: mRowNum * mColNum);

	mCursorX += (mCursorX + mCursorY * mColNum + len) % mColNum;
	forceReDraw();
	}

void CCharLcmControl::setCustomFont(int index, char* rawdata, int len)
	{
	memcpy(mCustomCharsRaw + index * 8, rawdata, len);
	reGenResoures();
	forceReDraw();
	}

void CCharLcmControl::clearScreen()
	{

	for (int i = 0; i < mRowNum * mColNum; i++)
		{
		mLcmChars[i] = ' '; // ¿Õ¸ñ×Ö·û
		}
	mCursorX = 0;
	mCursorY = 0;
	forceReDraw();
	}

void CCharLcmControl::setCursor(int x, int y)
	{
	mCursorX = x;
	mCursorY = y;
	}

void CCharLcmControl::setCursor(TPoint &cursor)
	{
	mCursorX = cursor.iX;
	mCursorY = cursor.iY;
	}

void CCharLcmControl::getCursor(int &x, int &y)
	{
	x = mCursorX;
	y = mCursorY;
	}

void CCharLcmControl::getCursor(TPoint &cursor)
	{
	cursor.iX = mCursorX;
	cursor.iY = mCursorY;
	}

void CCharLcmControl::reGenResoures()
	{
	TPoint colRowsize(mColNum, mRowNum);
	TPoint areaSize(mSurfaceWidth, mSurfaceHeight);
	mFontGen = CFontGenerator::NewL(colRowsize, areaSize, mCustomCharsRaw);

	mFontGen->setLcdPanelColor(mLcdPanelColor);
	mFontGen->setNegativePixelColor(mNegativePixelColor);
	mFontGen->setPositivePixelColor(mPositivePixelColor);
	mFontGen->reGenFontL();
	}

void CCharLcmControl::setColRow(int col, int row)
	{
	mColNum = col;
	mRowNum = row;

	for (int i = 0; i < mRowNum * mColNum; i++)
		{
		mLcmChars[i] = ' '; // ¿Õ¸ñ×Ö·û
		}

	reGenResoures();
	forceReDraw();
	}

void CCharLcmControl::getColRow(int &col, int &row)
	{
	col = mColNum;
	row = mRowNum;
	}

