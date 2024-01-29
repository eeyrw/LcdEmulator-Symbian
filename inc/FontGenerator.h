/*
 ============================================================================
 Name		: FontGenerator.h
 Author	  : Yuan
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CFontGenerator declaration
 ============================================================================
 */

#ifndef FONTGENERATOR_H
#define FONTGENERATOR_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <bitdev.h>

// CLASS DECLARATION

/**
 *  CFontGenerator
 * 
 */
class CFontGenerator : public CBase
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CFontGenerator();

	/**
	 * Two-phased constructor.
	 */
	static CFontGenerator* NewL(TPoint &colRowSize, TPoint &areaSize, char* customFontRawData);

	/**
	 * Two-phased constructor.
	 */
	static CFontGenerator* NewLC(TPoint &colRowSize, TPoint &areaSize, char* customFontRawData);

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CFontGenerator();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL(TPoint &colRowSize, TPoint &areaSize, char* customFontRawData);
public:
	//FontGenerator(QPoint colRowSize, QPoint areaSize, QVector<uint8_t> customFontRawData);
	CFbsBitmap* genSingleCustomFontBitmapL(char* raw, double unitWidth,
			double unitHeight);

	CFbsBitmap* genSingleFontBitmapL(int fontIndex, double unitWidth,
			double unitHeight);
	void genMainFontBitmapL(double unitWidth, double unitHeight);
	void genCustomFontBitmapL(char*  allRawData, double unitWidth,
			double unitHeight);
	void setColRowSize(TPoint &size);
	TPoint getColRowSize();
	void getActualCursor(TPoint &cursor, TPoint &actualCursor);

	void getActualCursor(int x, int y, TPoint &actualCursor);
	CFbsBitmap* getCharBitmap(char charNum);
	TRgb getNegativePixelColor();
	void setNegativePixelColor(TRgb &negativePixelColor);
	TRgb getPositivePixelColor();
	void setPositivePixelColor(TRgb &positivePixelColor);
	TRgb getLcdPanelColor();
	void setLcdPanelColor(TRgb &lcdPanelColor);
	void reGenFontL();

private:
	double mUnitWidth;
	double mUnitHeight;

	double mCharWidthOffset;
	double mCharHeightOffset;

	double mSurfaceWidth;
	double mSurfaceHeight;

	RPointerArray<CFbsBitmap> mFontBitmapMain;
	RPointerArray<CFbsBitmap> mFontBitmapCustom;

	char mCustomFontRawData[512];

	double mPixelSpaceWeight;
	double mPixelWeight;
	double mCharSpaceWeight;
	double mMarginWeight;

	double mPixelsPerRow;
	double mPixelsPerCol;

	int mBytesPerFont;

	TPoint mColRowSize;

	TRgb mPositivePixelColor;
	TRgb mNegativePixelColor;
	TRgb mLcdPanelColor;
	};

#endif // FONTGENERATOR_H
