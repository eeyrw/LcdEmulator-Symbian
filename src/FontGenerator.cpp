/*
 ============================================================================
 Name		: CFontGenerator.cpp
 Author	  : Yuan
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CFontGenerator implementation
 ============================================================================
 */

#include "FontGenerator.h"


CFontGenerator::CFontGenerator()
	{
	// No implementation required
	}

CFontGenerator::~CFontGenerator()
	{
	for (TInt i=0; i<mFontBitmapMain.Count(); i++)
		{
		delete mFontBitmapMain[i];
		}
	mFontBitmapMain.Close();
	for (TInt i=0; i<mFontBitmapCustom.Count(); i++)
		{
		delete mFontBitmapCustom[i];
		}
	mFontBitmapCustom.Close();
	}

CFontGenerator* CFontGenerator::NewLC(TPoint &colRowSize, TPoint &areaSize, char* customFontRawData)
	{
	CFontGenerator* self = new (ELeave) CFontGenerator();
	CleanupStack::PushL(self);
	self->ConstructL(colRowSize,areaSize,customFontRawData);
	return self;
	}

CFontGenerator* CFontGenerator::NewL(TPoint &colRowSize, TPoint &areaSize, char* customFontRawData)
	{
	CFontGenerator* self = CFontGenerator::NewLC(colRowSize,areaSize,customFontRawData);
	CleanupStack::Pop(); // self;
	return self;
	}

void CFontGenerator::ConstructL(TPoint &colRowSize, TPoint &areaSize, char* customFontRawData)
	{
	mPixelSpaceWeight = 1.3;
	mPixelWeight = 5;
	mCharSpaceWeight = 5;
	mMarginWeight = 12;

	mPixelsPerRow = 5;
	mPixelsPerCol = 8;

	mBytesPerFont = 5;


	mPositivePixelColor = KRgbWhite;
	mNegativePixelColor = KRgbGray;
	mLcdPanelColor = KRgbYellow;
	
    mColRowSize = colRowSize;
    mSurfaceWidth = areaSize.iX;
    mSurfaceHeight = areaSize.iY;
    //mCustomFontRawData = customFontRawData;
    
    //reGenFontL();
	}

const TUint8 mRawFontsData[] = {
    // ×ÝÏòÅÅÁÐµÄ¡£
    0x00, 0x00, 0x00, 0x00, 0x00, // ' '
    0x00, 0x00, 0x5F, 0x00, 0x00, // !
    0x00, 0x07, 0x00, 0x07, 0x00, // "
    0x14, 0x7F, 0x14, 0x7F, 0x14, // #
    0x24, 0x2A, 0x7F, 0x2A, 0x12, // $
    0x23, 0x13, 0x08, 0x64, 0x62, // %
    0x37, 0x49, 0x55, 0x22, 0x50, // &
    0x00, 0x05, 0x03, 0x00, 0x00, // '
    0x00, 0x1C, 0x22, 0x41, 0x00, // (
    0x00, 0x41, 0x22, 0x1C, 0x00, // )
    0x08, 0x2A, 0x1C, 0x2A, 0x08, // *
    0x08, 0x08, 0x3E, 0x08, 0x08, // +
    0x00, 0x50, 0x30, 0x00, 0x00, // ,
    0x08, 0x08, 0x08, 0x08, 0x08, // -
    0x00, 0x60, 0x60, 0x00, 0x00, // .
    0x20, 0x10, 0x08, 0x04, 0x02, // /
    0x3E, 0x51, 0x49, 0x45, 0x3E, // 0
    0x00, 0x42, 0x7F, 0x40, 0x00, // 1
    0x42, 0x61, 0x51, 0x49, 0x46, // 2
    0x21, 0x41, 0x45, 0x4B, 0x31, // 3
    0x18, 0x14, 0x12, 0x7F, 0x10, // 4
    0x27, 0x45, 0x45, 0x45, 0x39, // 5
    0x3C, 0x4A, 0x49, 0x49, 0x30, // 6
    0x01, 0x71, 0x09, 0x05, 0x03, // 7
    0x36, 0x49, 0x49, 0x49, 0x36, // 8
    0x06, 0x49, 0x49, 0x29, 0x1E, // 9
    0x00, 0x36, 0x36, 0x00, 0x00, // :
    0x00, 0x56, 0x36, 0x00, 0x00, // ;
    0x00, 0x08, 0x14, 0x22, 0x41, // <
    0x14, 0x14, 0x14, 0x14, 0x14, // =
    0x41, 0x22, 0x14, 0x08, 0x00, // >
    0x02, 0x01, 0x51, 0x09, 0x06, // ?
    0x32, 0x49, 0x79, 0x41, 0x3E, // @
    0x7E, 0x11, 0x11, 0x11, 0x7E, // A
    0x7F, 0x49, 0x49, 0x49, 0x36, // B
    0x3E, 0x41, 0x41, 0x41, 0x22, // C
    0x7F, 0x41, 0x41, 0x22, 0x1C, // D
    0x7F, 0x49, 0x49, 0x49, 0x41, // E
    0x7F, 0x09, 0x09, 0x01, 0x01, // F
    0x3E, 0x41, 0x41, 0x51, 0x32, // G
    0x7F, 0x08, 0x08, 0x08, 0x7F, // H
    0x00, 0x41, 0x7F, 0x41, 0x00, // I
    0x20, 0x40, 0x41, 0x3F, 0x01, // J
    0x7F, 0x08, 0x14, 0x22, 0x41, // K
    0x7F, 0x40, 0x40, 0x40, 0x40, // L
    0x7F, 0x02, 0x04, 0x02, 0x7F, // M
    0x7F, 0x04, 0x08, 0x10, 0x7F, // N
    0x3E, 0x41, 0x41, 0x41, 0x3E, // O
    0x7F, 0x09, 0x09, 0x09, 0x06, // P
    0x3E, 0x41, 0x51, 0x21, 0x5E, // Q
    0x7F, 0x09, 0x19, 0x29, 0x46, // R
    0x46, 0x49, 0x49, 0x49, 0x31, // S
    0x01, 0x01, 0x7F, 0x01, 0x01, // T
    0x3F, 0x40, 0x40, 0x40, 0x3F, // U
    0x1F, 0x20, 0x40, 0x20, 0x1F, // V
    0x7F, 0x20, 0x18, 0x20, 0x7F, // W
    0x63, 0x14, 0x08, 0x14, 0x63, // X
    0x03, 0x04, 0x78, 0x04, 0x03, // Y
    0x61, 0x51, 0x49, 0x45, 0x43, // Z
    0x00, 0x00, 0x7F, 0x41, 0x41, // [
    0x02, 0x04, 0x08, 0x10, 0x20, // "\"
    0x41, 0x41, 0x7F, 0x00, 0x00, // ]
    0x04, 0x02, 0x01, 0x02, 0x04, // ^
    0x40, 0x40, 0x40, 0x40, 0x40, // _
    0x00, 0x01, 0x02, 0x04, 0x00, // `
    0x20, 0x54, 0x54, 0x54, 0x78, // a
    0x7F, 0x48, 0x44, 0x44, 0x38, // b
    0x38, 0x44, 0x44, 0x44, 0x20, // c
    0x38, 0x44, 0x44, 0x48, 0x7F, // d
    0x38, 0x54, 0x54, 0x54, 0x18, // e
    0x08, 0x7E, 0x09, 0x01, 0x02, // f
    0x08, 0x14, 0x54, 0x54, 0x3C, // g
    0x7F, 0x08, 0x04, 0x04, 0x78, // h
    0x00, 0x44, 0x7D, 0x40, 0x00, // i
    0x20, 0x40, 0x44, 0x3D, 0x00, // j
    0x00, 0x7F, 0x10, 0x28, 0x44, // k
    0x00, 0x41, 0x7F, 0x40, 0x00, // l
    0x7C, 0x04, 0x18, 0x04, 0x78, // m
    0x7C, 0x08, 0x04, 0x04, 0x78, // n
    0x38, 0x44, 0x44, 0x44, 0x38, // o
    0x7C, 0x14, 0x14, 0x14, 0x08, // p
    0x08, 0x14, 0x14, 0x18, 0x7C, // q
    0x7C, 0x08, 0x04, 0x04, 0x08, // r
    0x48, 0x54, 0x54, 0x54, 0x20, // s
    0x04, 0x3F, 0x44, 0x40, 0x20, // t
    0x3C, 0x40, 0x40, 0x20, 0x7C, // u
    0x1C, 0x20, 0x40, 0x20, 0x1C, // v
    0x3C, 0x40, 0x30, 0x40, 0x3C, // w
    0x44, 0x28, 0x10, 0x28, 0x44, // x
    0x0C, 0x50, 0x50, 0x50, 0x3C, // y
    0x44, 0x64, 0x54, 0x4C, 0x44, // z
    0x00, 0x08, 0x36, 0x41, 0x00, // {
    0x00, 0x00, 0x7F, 0x00, 0x00, // |
    0x00, 0x41, 0x36, 0x08, 0x00, // }
    0x02, 0x01, 0x02, 0x04, 0x02, // ~
    0xff, 0xff, 0xff, 0xff, 0xff  // black
                                  // block
};

/*CFontGenerator::CFontGenerator(QPoint colRowSize, QPoint areaSize, QVector<uint8_t> customFontRawData)
{

    mColRowSize = colRowSize;
    mSurfaceWidth = areaSize.x();
    mSurfaceHeight = areaSize.y();
    mCustomFontRawData = customFontRawData;
    // reGenFont();
}*/

void CFontGenerator::reGenFontL()
{
	
	_LIT(KMsgDebug,"Regenerate font.");
	RDebug::Print(KMsgDebug);
	
    double colNum = mColRowSize.iX;
    double rowNum = mColRowSize.iY;

    // mMarginWeight*2+colNum*(mPixelWeight*mPixelsPerRow+mPixelSpaceWeight*(mPixelsPerRow-1))+(colNum-1)*mCharSpaceWeight
    mUnitWidth = mSurfaceWidth / (mMarginWeight * 2 + colNum * (mPixelWeight * mPixelsPerRow + mPixelSpaceWeight * (mPixelsPerRow - 1)) + (colNum - 1) * mCharSpaceWeight);
    // mMarginWeight*2+rowNum*(mPixelWeight*mPixelsPerCol+mPixelSpaceWeight*(mPixelsPerCol-1))+(rowNum-1)*2*mCharSpaceWeight
    mUnitHeight = mSurfaceHeight / (mMarginWeight * 2 + rowNum * (mPixelWeight * mPixelsPerCol + mPixelSpaceWeight * (mPixelsPerCol - 1)) + (rowNum - 1) * 2 * mCharSpaceWeight);

    genMainFontBitmapL(mUnitWidth, mUnitHeight);
    genCustomFontBitmapL(mCustomFontRawData, mUnitWidth, mUnitHeight);

    mCharWidthOffset = mUnitWidth * (mPixelWeight * mPixelsPerRow + mPixelSpaceWeight * (mPixelsPerRow - 1) + mCharSpaceWeight);
    mCharHeightOffset = mUnitHeight * (mPixelWeight * mPixelsPerCol + mPixelSpaceWeight * (mPixelsPerCol - 1) + mCharSpaceWeight * 2);
}

CFbsBitmap* CFontGenerator::genSingleCustomFontBitmapL(char* raw, double unitWidth, double unitHeight)
{

    int bitmapWidth = (int)(unitWidth * (mPixelWeight * mPixelsPerRow + mPixelSpaceWeight * (mPixelsPerRow - 1)));
    int bitmapHeight = (int)(unitHeight * (mPixelWeight * mPixelsPerCol + mPixelSpaceWeight * (mPixelsPerCol - 1)));

    // create a bitmap to be used off-screen
    CFbsBitmap* fontBitmap = new (ELeave) CFbsBitmap();
    User::LeaveIfError(fontBitmap->Create(TSize(bitmapWidth,bitmapHeight),EColor16M));
    CleanupStack::PushL(fontBitmap);
    
    // create an off-screen device and context
    CGraphicsContext* bitmapContext= NULL;
    CFbsBitmapDevice* bitmapDevice = CFbsBitmapDevice::NewL(fontBitmap);
    CleanupStack::PushL(bitmapDevice);
    User::LeaveIfError(bitmapDevice->CreateContext(bitmapContext));
    CleanupStack::PushL(bitmapContext);
    
    bitmapContext->SetBrushStyle(CGraphicsContext::ESolidBrush);
    bitmapContext->SetBrushColor(mLcdPanelColor);
    bitmapContext->SetPenStyle(CGraphicsContext::ENullPen);
    bitmapContext->DrawRect(TRect(TPoint(0,0),TSize(bitmapWidth,bitmapHeight)));

    double charPixelWidth = mUnitWidth * mPixelWeight;
    double charPixelHeight = mUnitHeight * mPixelWeight;


    for (int y = 0; y < mPixelsPerCol; ++y)
    {
        for (int x = 0; x < mPixelsPerRow; ++x)
        {

            int pixelRectLeft = (int)(x * (charPixelWidth + mPixelSpaceWeight * mUnitWidth)+0.5);
            int pixelRectTop = (int)(y * (charPixelHeight + mPixelSpaceWeight * mUnitHeight)+0.5);

            TRect pixelRect = TRect(TPoint(pixelRectLeft, pixelRectTop),
                                      TSize(charPixelWidth, charPixelHeight));
            if ((raw[y] & (1 << x)) != 0)
                {
                	bitmapContext->SetBrushColor(mPositivePixelColor);
                }
                else
                {
                	bitmapContext->SetBrushColor(mNegativePixelColor);
                }
            bitmapContext->DrawRect(pixelRect);
        }
    }
    // cleanup
    CleanupStack::PopAndDestroy(2);
    CleanupStack::Pop(fontBitmap);
    return fontBitmap;
}

CFbsBitmap* CFontGenerator::genSingleFontBitmapL(int fontIndex, double unitWidth, double unitHeight)
{
    int bitmapWidth = (int)(unitWidth * (mPixelWeight * mPixelsPerRow + mPixelSpaceWeight * (mPixelsPerRow - 1)));
    int bitmapHeight = (int)(unitHeight * (mPixelWeight * mPixelsPerCol + mPixelSpaceWeight * (mPixelsPerCol - 1)));

    // create a bitmap to be used off-screen
    CFbsBitmap* fontBitmap = new (ELeave) CFbsBitmap();
    User::LeaveIfError(fontBitmap->Create(TSize(bitmapWidth,bitmapHeight),EColor16M));
    CleanupStack::PushL(fontBitmap);
    
    // create an off-screen device and context
    CGraphicsContext* bitmapContext= NULL;
    CFbsBitmapDevice* bitmapDevice = CFbsBitmapDevice::NewL(fontBitmap);
    CleanupStack::PushL(bitmapDevice);
    User::LeaveIfError(bitmapDevice->CreateContext(bitmapContext));
    CleanupStack::PushL(bitmapContext);
    
    bitmapContext->SetBrushStyle(CGraphicsContext::ESolidBrush);
    bitmapContext->SetBrushColor(mLcdPanelColor);
    bitmapContext->SetPenStyle(CGraphicsContext::ENullPen);
    bitmapContext->DrawRect(TRect(TPoint(0,0),TSize(bitmapWidth,bitmapHeight)));
    
   
    double charPixelWidth = mUnitWidth * mPixelWeight;
    double charPixelHeight = mUnitHeight * mPixelWeight;

    for (int y = 0; y < mPixelsPerCol; ++y)
    {
        for (int x = 0; x < mPixelsPerRow; ++x)
        {

            int pixelRectLeft = (int)(x * (charPixelWidth + mPixelSpaceWeight * mUnitWidth)+0.5);
            int pixelRectTop = (int)(y * (charPixelHeight + mPixelSpaceWeight * mUnitHeight)+0.5);

            TRect pixelRect = TRect(TPoint(pixelRectLeft, pixelRectTop),
                                      TSize(charPixelWidth, charPixelHeight));
            if ((mRawFontsData[(int)(fontIndex * mPixelsPerRow + x)] & (1 << y)) != 0)
            {
            	bitmapContext->SetBrushColor(mPositivePixelColor);
            }
            else
            {
            	bitmapContext->SetBrushColor(mNegativePixelColor);
            }
            bitmapContext->DrawRect(pixelRect);
        }
    }
    // cleanup
    CleanupStack::PopAndDestroy(2);
    CleanupStack::Pop(fontBitmap);
    return fontBitmap;
}

void CFontGenerator::genMainFontBitmapL(double unitWidth, double unitHeight)
{

    int fontNum = sizeof(mRawFontsData) / mBytesPerFont;

    for (int fontIndex = 0; fontIndex < fontNum; ++fontIndex)
    {
    	User::LeaveIfError(mFontBitmapMain.Append(
    			genSingleFontBitmapL(fontIndex,unitWidth, unitHeight)));
    }
    //Log.i(TAG, "Custom font generated.");
}

void CFontGenerator::genCustomFontBitmapL(char* allRawData, double unitWidth, double unitHeight)
{

    int fontNum = 8;

    char temp[8];

    for (int fontIndex = 0; fontIndex < fontNum; ++fontIndex)
    {
        memcpy(temp, allRawData + fontIndex * 8, 8);
        User::LeaveIfError(mFontBitmapMain.Append(
        				genSingleCustomFontBitmapL(temp,unitWidth, unitHeight)));
    }
    //Log.i(TAG, "Main font generated.");
}

void CFontGenerator::setColRowSize(TPoint &size)
{
    mColRowSize = size;
}

TPoint CFontGenerator::getColRowSize()
{
    return mColRowSize;
}

void CFontGenerator::getActualCursor(TPoint &cursor, TPoint &actualCursor)
{
    actualCursor.SetXY(mMarginWeight * mUnitWidth + mCharWidthOffset * cursor.iX,
    		mMarginWeight * mUnitHeight + mCharHeightOffset * cursor.iY);
}

void CFontGenerator::getActualCursor(int x, int y, TPoint &actualCursor)
{
    TPoint t = TPoint(x, y);
    getActualCursor(t, actualCursor);
}

CFbsBitmap* CFontGenerator::getCharBitmap(char charNum)
{
    // ' ' in ASCII is 32
    if (charNum >= 32 && charNum <= 127)
    {
        charNum -= 32;
    }
    else if (charNum >= 0 && charNum <= 7)
    {
        return mFontBitmapCustom[charNum];
    }
    else
    {
        charNum = 32;
    }

    return mFontBitmapMain[charNum];
}

TRgb CFontGenerator::getNegativePixelColor()
{
    return mNegativePixelColor;
}

void CFontGenerator::setNegativePixelColor(TRgb &negativePixelColor)
{
    mNegativePixelColor = negativePixelColor;
}

TRgb CFontGenerator::getPositivePixelColor()
{
    return mPositivePixelColor;
}

void CFontGenerator::setPositivePixelColor(TRgb &positivePixelColor)
{
    mPositivePixelColor = positivePixelColor;
}

TRgb CFontGenerator::getLcdPanelColor()
{
    return mLcdPanelColor;
}

void CFontGenerator::setLcdPanelColor(TRgb &lcdPanelColor)
{
    mLcdPanelColor = lcdPanelColor;
}


/*// create a bitmap to be used off-screen
CFbsBitmap* offScreenBitmap = new (ELeave) CFbsBitmap();
User::LeaveIfError(offScreenBitmap->Create(TSize(100,100),EColor256));
CleanupStack::PushL(offScreenBitmap);

// create an off-screen device and context
CGraphicsContext* bitmapContext=NULL;
CFbsBitmapDevice* bitmapDevice = CFbsBitmapDevice::NewL(offScreenBitmap);
CleanupStack::PushL(bitmapDevice);
User::LeaveIfError(bitmapDevice->CreateContext(bitmapContext));
CleanupStack::PushL(bitmapContext);

// draw something on the bitmap
TRect rect(0,0,100,100);
bitmapContext->SetBrushColor(KRgbRed);
bitmapContext->SetBrushStyle(CGraphicsContext::ESolidBrush);
bitmapContext->DrawRect(rect); // a filled red rectangle

// now do what you want with it, such as blitting to the screen
gc.BitBlt(TPoint(20,20),offScreenBitmap);

// cleanup
CleanupStack::PopAndDestroy(3);
...*/
