/*
 ============================================================================
 Name		: LcdEmulatorDocument.h
 Author	  : Yuan
 Copyright   : Your copyright notice
 Description : Declares document class for application.
 ============================================================================
 */

#ifndef __LCDEMULATORDOCUMENT_h__
#define __LCDEMULATORDOCUMENT_h__

// INCLUDES
#include <akndoc.h>

// FORWARD DECLARATIONS
class CLcdEmulatorAppUi;
class CEikApplication;

// CLASS DECLARATION

/**
 * CLcdEmulatorDocument application class.
 * An instance of class CLcdEmulatorDocument is the Document part of the
 * AVKON application framework for the LcdEmulator example application.
 */
class CLcdEmulatorDocument : public CAknDocument
	{
public:
	// Constructors and destructor

	/**
	 * NewL.
	 * Two-phased constructor.
	 * Construct a CLcdEmulatorDocument for the AVKON application aApp
	 * using two phase construction, and return a pointer
	 * to the created object.
	 * @param aApp Application creating this document.
	 * @return A pointer to the created instance of CLcdEmulatorDocument.
	 */
	static CLcdEmulatorDocument* NewL(CEikApplication& aApp);

	/**
	 * NewLC.
	 * Two-phased constructor.
	 * Construct a CLcdEmulatorDocument for the AVKON application aApp
	 * using two phase construction, and return a pointer
	 * to the created object.
	 * @param aApp Application creating this document.
	 * @return A pointer to the created instance of CLcdEmulatorDocument.
	 */
	static CLcdEmulatorDocument* NewLC(CEikApplication& aApp);

	/**
	 * ~CLcdEmulatorDocument
	 * Virtual Destructor.
	 */
	virtual ~CLcdEmulatorDocument();

public:
	// Functions from base classes

	/**
	 * CreateAppUiL
	 * From CEikDocument, CreateAppUiL.
	 * Create a CLcdEmulatorAppUi object and return a pointer to it.
	 * The object returned is owned by the Uikon framework.
	 * @return Pointer to created instance of AppUi.
	 */
	CEikAppUi* CreateAppUiL();

private:
	// Constructors

	/**
	 * ConstructL
	 * 2nd phase constructor.
	 */
	void ConstructL();

	/**
	 * CLcdEmulatorDocument.
	 * C++ default constructor.
	 * @param aApp Application creating this document.
	 */
	CLcdEmulatorDocument(CEikApplication& aApp);

	};

#endif // __LCDEMULATORDOCUMENT_h__
// End of File
