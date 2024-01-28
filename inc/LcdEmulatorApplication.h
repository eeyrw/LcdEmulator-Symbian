/*
 ============================================================================
 Name		: LcdEmulatorApplication.h
 Author	  : Yuan
 Copyright   : Your copyright notice
 Description : Declares main application class.
 ============================================================================
 */

#ifndef __LCDEMULATORAPPLICATION_H__
#define __LCDEMULATORAPPLICATION_H__

// INCLUDES
#include <aknapp.h>
#include "LcdEmulator.hrh"

// UID for the application;
// this should correspond to the uid defined in the mmp file
const TUid KUidLcdEmulatorApp =
	{
	_UID3
	};

// CLASS DECLARATION

/**
 * CLcdEmulatorApplication application class.
 * Provides factory to create concrete document object.
 * An instance of CLcdEmulatorApplication is the application part of the
 * AVKON application framework for the LcdEmulator example application.
 */
class CLcdEmulatorApplication : public CAknApplication
	{
public:
	// Functions from base classes

	/**
	 * From CApaApplication, AppDllUid.
	 * @return Application's UID (KUidLcdEmulatorApp).
	 */
	TUid AppDllUid() const;

protected:
	// Functions from base classes

	/**
	 * From CApaApplication, CreateDocumentL.
	 * Creates CLcdEmulatorDocument document object. The returned
	 * pointer in not owned by the CLcdEmulatorApplication object.
	 * @return A pointer to the created document object.
	 */
	CApaDocument* CreateDocumentL();
	};

#endif // __LCDEMULATORAPPLICATION_H__
// End of File
