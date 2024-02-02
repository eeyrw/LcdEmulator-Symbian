/*
 ============================================================================
 Name		: LcdEmulatorAppView.h
 Author	  : Yuan
 Copyright   : Your copyright notice
 Description : Declares view class for application.
 ============================================================================
 */

#ifndef __LCDEMULATORAPPVIEW_h__
#define __LCDEMULATORAPPVIEW_h__

// INCLUDES
#include <coecntrl.h>
#include "CharLcmControl.h"
#include <eiklabel.h>  // for example label control
// CLASS DECLARATION
class CLcdEmulatorAppView : public CCoeControl
	{
public:
	// New methods

	/**
	 * NewL.
	 * Two-phased constructor.
	 * Create a CLcdEmulatorAppView object, which will draw itself to aRect.
	 * @param aRect The rectangle this view will be drawn to.
	 * @return a pointer to the created instance of CLcdEmulatorAppView.
	 */
	static CLcdEmulatorAppView* NewL(const TRect& aRect);

	/**
	 * NewLC.
	 * Two-phased constructor.
	 * Create a CLcdEmulatorAppView object, which will draw itself
	 * to aRect.
	 * @param aRect Rectangle this view will be drawn to.
	 * @return A pointer to the created instance of CLcdEmulatorAppView.
	 */
	static CLcdEmulatorAppView* NewLC(const TRect& aRect);

	/**
	 * ~CLcdEmulatorAppView
	 * Virtual Destructor.
	 */
	virtual ~CLcdEmulatorAppView();

public:

	CCoeControl* ComponentControl(TInt aIndex) const;
	TInt CountComponentControls() const;
	// Functions from base classes

	/**
	 * From CCoeControl, Draw
	 * Draw this CLcdEmulatorAppView to the screen.
	 * @param aRect the rectangle of this view that needs updating
	 */
	void Draw(const TRect& aRect) const;

	/**
	 * From CoeControl, SizeChanged.
	 * Called by framework when the view size is changed.
	 */
	void SizeChanged();

	/**
	 * From CoeControl, HandlePointerEventL.
	 * Called by framework when a pointer touch event occurs.
	 * Note: although this method is compatible with earlier SDKs, 
	 * it will not be called in SDKs without Touch support.
	 * @param aPointerEvent the information about this event
	 */
	virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);

	
    /**
    * DoPeriodTask.
    * Called by period task static function.
    */
    void DoPeriodTask();

    /**
    * Period.
    * Call back function for a periodic timer
    * @param aPtr a parameter passed to the timer when the timer is started.
    * @return Value TRUE indicates the callback should be done again.
    */
    static TInt Period( TAny* aPtr );
    /**
    * StartTimer.
    * Start the timer.
    */
    void StartTimer();
    /**
    * StopDemo
    * Stop animation.
    */
    void StopTimer();
	void SetFullRect();
	void CalculateFullscreenRect();	
private:
	// Constructors

	/**
	 * ConstructL
	 * 2nd phase constructor.
	 * Perform the second phase construction of a
	 * CLcdEmulatorAppView object.
	 * @param aRect The rectangle this view will be drawn to.
	 */
	void ConstructL(const TRect& aRect);

	/**
	 * CLcdEmulatorAppView.
	 * C++ default constructor.
	 */
	CLcdEmulatorAppView();
	
public:
	CCharLcmControl* iCharLcmControl; // and its own status window.
	CEikLabel* iLabel; // example label
	CPeriodic* iPeriodicTimer;
	TInt counter;
	TRect iFullRect;
	TBool iIsCBAVisible;
	};

#endif // __LCDEMULATORAPPVIEW_h__
// End of File
