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

	};

#endif // CHARLCMCONTROL_H
