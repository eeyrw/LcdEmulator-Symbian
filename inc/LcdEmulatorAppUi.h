/*
 ============================================================================
 Name		: LcdEmulatorAppUi.h
 Author	  : Yuan
 Copyright   : Your copyright notice
 Description : Declares UI class for application.
 ============================================================================
 */

#ifndef __LCDEMULATORAPPUI_h__
#define __LCDEMULATORAPPUI_h__

// INCLUDES
#include <aknappui.h>

// FORWARD DECLARATIONS
class CLcdEmulatorAppView;

// CLASS DECLARATION
/**
 * CLcdEmulatorAppUi application UI class.
 * Interacts with the user through the UI and request message processing
 * from the handler class
 */
class CLcdEmulatorAppUi : public CAknAppUi
	{
public:
	// Constructors and destructor

	/**
	 * ConstructL.
	 * 2nd phase constructor.
	 */
	void ConstructL();

	/**
	 * CLcdEmulatorAppUi.
	 * C++ default constructor. This needs to be public due to
	 * the way the framework constructs the AppUi
	 */
	CLcdEmulatorAppUi();

	/**
	 * ~CLcdEmulatorAppUi.
	 * Virtual Destructor.
	 */
	virtual ~CLcdEmulatorAppUi();

private:
	// Functions from base classes

	/**
	 * From CEikAppUi, HandleCommandL.
	 * Takes care of command handling.
	 * @param aCommand Command to be handled.
	 */
	void HandleCommandL(TInt aCommand);

	/**
	 *  HandleStatusPaneSizeChange.
	 *  Called by the framework when the application status pane
	 *  size is changed.
	 */
	void HandleStatusPaneSizeChange();
	
	virtual void HandleResourceChangeL( TInt aType );

	/**
	 *  From CCoeAppUi, HelpContextL.
	 *  Provides help context for the application.
	 *  size is changed.
	 */
	CArrayFix<TCoeHelpContext>* HelpContextL() const;
	void SendUart(void);
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
    void StartKeepScreenOnTimer();
    /**
    * StopDemo
    * Stop animation.
    */
    void StopKeepScreenOnTimer();
private:
	// Data

	/**
	 * The application view
	 * Owned by CLcdEmulatorAppUi
	 */
	CLcdEmulatorAppView* iAppView;
	CPeriodic* iKeepScreenOnTimer;

	};

#endif // __LCDEMULATORAPPUI_h__
// End of File
