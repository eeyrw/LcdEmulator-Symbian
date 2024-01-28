/*
 ============================================================================
 Name		: LcdEmulatorDocument.cpp
 Author	  : Yuan
 Copyright   : Your copyright notice
 Description : CLcdEmulatorDocument implementation
 ============================================================================
 */

// INCLUDE FILES
#include "LcdEmulatorAppUi.h"
#include "LcdEmulatorDocument.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CLcdEmulatorDocument::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CLcdEmulatorDocument* CLcdEmulatorDocument::NewL(CEikApplication& aApp)
	{
	CLcdEmulatorDocument* self = NewLC(aApp);
	CleanupStack::Pop(self);
	return self;
	}

// -----------------------------------------------------------------------------
// CLcdEmulatorDocument::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CLcdEmulatorDocument* CLcdEmulatorDocument::NewLC(CEikApplication& aApp)
	{
	CLcdEmulatorDocument* self = new (ELeave) CLcdEmulatorDocument(aApp);

	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

// -----------------------------------------------------------------------------
// CLcdEmulatorDocument::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CLcdEmulatorDocument::ConstructL()
	{
	// No implementation required
	}

// -----------------------------------------------------------------------------
// CLcdEmulatorDocument::CLcdEmulatorDocument()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CLcdEmulatorDocument::CLcdEmulatorDocument(CEikApplication& aApp) :
	CAknDocument(aApp)
	{
	// No implementation required
	}

// ---------------------------------------------------------------------------
// CLcdEmulatorDocument::~CLcdEmulatorDocument()
// Destructor.
// ---------------------------------------------------------------------------
//
CLcdEmulatorDocument::~CLcdEmulatorDocument()
	{
	// No implementation required
	}

// ---------------------------------------------------------------------------
// CLcdEmulatorDocument::CreateAppUiL()
// Constructs CreateAppUi.
// ---------------------------------------------------------------------------
//
CEikAppUi* CLcdEmulatorDocument::CreateAppUiL()
	{
	// Create the application user interface, and return a pointer to it;
	// the framework takes ownership of this object
	return new (ELeave) CLcdEmulatorAppUi;
	}

// End of File
