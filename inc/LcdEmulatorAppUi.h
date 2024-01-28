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

	/**
	 *  From CCoeAppUi, HelpContextL.
	 *  Provides help context for the application.
	 *  size is changed.
	 */
	CArrayFix<TCoeHelpContext>* HelpContextL() const;

private:
	// Data

	/**
	 * The application view
	 * Owned by CLcdEmulatorAppUi
	 */
	CLcdEmulatorAppView* iAppView;

	};

#endif // __LCDEMULATORAPPUI_h__
// End of File
