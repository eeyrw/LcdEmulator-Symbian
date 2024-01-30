/*
 ============================================================================
 Name		: LcdEmulatorAppView.cpp
 Author	  : Yuan
 Copyright   : Your copyright notice
 Description : Application view implementation
 ============================================================================
 */

// INCLUDE FILES
#include <coemain.h>
#include "LcdEmulatorAppView.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CLcdEmulatorAppView::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CLcdEmulatorAppView* CLcdEmulatorAppView::NewL(const TRect& aRect)
	{
	CLcdEmulatorAppView* self = CLcdEmulatorAppView::NewLC(aRect);
	CleanupStack::Pop(self);
	return self;
	}

// -----------------------------------------------------------------------------
// CLcdEmulatorAppView::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CLcdEmulatorAppView* CLcdEmulatorAppView::NewLC(const TRect& aRect)
	{
	CLcdEmulatorAppView* self = new (ELeave) CLcdEmulatorAppView;
	CleanupStack::PushL(self);
	self->ConstructL(aRect);
	return self;
	}

// -----------------------------------------------------------------------------
// CLcdEmulatorAppView::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CLcdEmulatorAppView::ConstructL(const TRect& aRect)
	{
	// Create a window for this application view
	//CreateWindowL();

	// Set the windows size
	//SetRect(aRect);

	// Activate the window, which makes it ready to be drawn
	//ActivateL();


	CreateWindowL();
	/*
	 iLabel = new (ELeave) CEikLabel;
	 iLabel->SetContainerWindowL( *this );
	 iLabel->SetTextL( _L("Example View") );
	 iToDoLabel = new (ELeave) CEikLabel;
	 iToDoLabel->SetContainerWindowL( *this );
	 iToDoLabel->SetTextL( _L("Add Your controls\n here") );*/
	iCharLcmControl = CCharLcmControl::NewL(Window());
	iLabel = new (ELeave) CEikLabel;
	iLabel->SetContainerWindowL(*this);
	iLabel->SetTextL(_L("MyView 1\n\nSelect local view\nswitching from menu"));
	iCharLcmControl->clearScreen();
	iCharLcmControl->write("Haha hahahah...",sizeof("Haha hahahah..."));
	SetRect(aRect);
	SetExtentToWholeScreen();
	ActivateL();

	}

// -----------------------------------------------------------------------------
// CLcdEmulatorAppView::CLcdEmulatorAppView()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CLcdEmulatorAppView::CLcdEmulatorAppView()
	{
	// No implementation required
	}

// -----------------------------------------------------------------------------
// CLcdEmulatorAppView::~CLcdEmulatorAppView()
// Destructor.
// -----------------------------------------------------------------------------
//
CLcdEmulatorAppView::~CLcdEmulatorAppView()
	{
	// No implementation required
	delete iCharLcmControl;
	delete iLabel;
	}

// -----------------------------------------------------------------------------
// CLcdEmulatorAppView::Draw()
// Draws the display.
// -----------------------------------------------------------------------------
//
void CLcdEmulatorAppView::Draw(const TRect& /*aRect*/) const
	{
	// Get the standard graphics context
	//CWindowGc& gc = SystemGc();

	// Gets the control's extent
	//TRect drawRect(Rect());

	// Clears the screen
	//gc.Clear(drawRect);

	}
CCoeControl* CLcdEmulatorAppView::ComponentControl(TInt aIndex) const
	{
	_LIT(KMsgDebug,"ComponentControl index: %d");
	RDebug::Print(KMsgDebug, aIndex);
//	if (aIndex == 0)
		return iCharLcmControl;
//	else
//		return iLabel;
	}
TInt CLcdEmulatorAppView::CountComponentControls() const
	{
	return 1;
	}
// -----------------------------------------------------------------------------
// CLcdEmulatorAppView::SizeChanged()
// Called by framework when the view size is changed.
// -----------------------------------------------------------------------------
//
void CLcdEmulatorAppView::SizeChanged()
	{
	TRect rect = Rect();
	iCharLcmControl->SetRect(rect);
	iLabel->SetExtent(TPoint(50, 50), iLabel->MinimumSize());
	}

// -----------------------------------------------------------------------------
// CLcdEmulatorAppView::HandlePointerEventL()
// Called by framework to handle pointer touch events.
// Note: although this method is compatible with earlier SDKs, 
// it will not be called in SDKs without Touch support.
// -----------------------------------------------------------------------------
//
void CLcdEmulatorAppView::HandlePointerEventL(
		const TPointerEvent& aPointerEvent)
	{

	// Call base class HandlePointerEventL()
	CCoeControl::HandlePointerEventL(aPointerEvent);
	}

// End of File
