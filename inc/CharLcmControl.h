/*
 ============================================================================
 Name		: CharLcmControl.h
 Author	  : Yuan
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CCharLcmControl declaration
 ============================================================================
 */

#ifndef CHARLCMCONTROL_H
#define CHARLCMCONTROL_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <coecntrl.h>
#include <coedef.h>
#include "FontGenerator.h"
#include <w32std.h>

#define MAX_DISPLAY_CHAR_LEN 512

// CLASS DECLARATION

/**
 *  CCharLcmControl
 * 
 */
class CCharLcmControl : public CCoeControl
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CCharLcmControl();

	/**
	 * Two-phased constructor.
	 */
	static CCharLcmControl* NewL(RWindow& aWindow);

	void SizeChanged();
private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CCharLcmControl();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL(RWindow& aWindow);
	/**
	 * From CCoeControl, Draw
	 * Draw this CLcdEmulatorAppView to the screen.
	 * @param aRect the rectangle of this view that needs updating
	 */
	void Draw(const TRect& aRect) const;

	
	
private:
    // Color
    TRgb mPositivePixelColor;
    TRgb mNegativePixelColor;
    TRgb mLcdPanelColor;

    // SurfaceView
    int mSurfaceHeight;
    int mSurfaceWidth;

    // Virtual LCM property
    int mColNum;
    int mRowNum;

    int mCursorX;
    int mCursorY;

    char mLcmChars[1024];
    char mCustomCharsRaw[1024];

    // Font generation class instance
    CFontGenerator* mFontGen;

    bool mIsFullScreen;

public:
    TRgb getNegativePixelColor();
    void setNegativePixelColor(TRgb &mNegativePixelColor);
    TRgb getPositivePixelColor();
    void setPositivePixelColor(TRgb &mPositivePixelColor);
    TRgb getLcdPanelColor();
    void setLcdPanelColor(TRgb &mLcdPanelColor);
    void forceReDraw();
    void write(const char *data, int len);
    void showString(const TDes8& str);
    void setCustomFont(int index, char* rawdata, int len);
    void clearScreen();
    void setCursor(int x, int y);
    void setCursor(TPoint &cursor);
    void getCursor(int &x, int &y);
    void getCursor(TPoint &cursor);
    void reGenResoures();
    void setColRow(int col, int row);
    void getColRow(int &col, int &row);
	
	};

#endif // CHARLCMCONTROL_H
