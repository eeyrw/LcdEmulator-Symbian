/*
 ============================================================================
 Name		: LcdEmulatorApplication.cpp
 Author	  : Yuan
 Copyright   : Your copyright notice
 Description : Main application class
 ============================================================================
 */

// INCLUDE FILES
#include "LcdEmulator.hrh"
#include "LcdEmulatorDocument.h"
#include "LcdEmulatorApplication.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CLcdEmulatorApplication::CreateDocumentL()
// Creates CApaDocument object
// -----------------------------------------------------------------------------
//
CApaDocument* CLcdEmulatorApplication::CreateDocumentL()
	{
	// Create an LcdEmulator document, and return a pointer to it
	return CLcdEmulatorDocument::NewL(*this);
	}

// -----------------------------------------------------------------------------
// CLcdEmulatorApplication::AppDllUid()
// Returns application UID
// -----------------------------------------------------------------------------
//
TUid CLcdEmulatorApplication::AppDllUid() const
	{
	// Return the UID for the LcdEmulator application
	return KUidLcdEmulatorApp;
	}

// End of File
