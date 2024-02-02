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
// INCLUDES
#include <aknutils.h>

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
	iIsCBAVisible = EFalse;
	iCharLcmControl = CCharLcmControl::NewL(Window());
	iLabel = new (ELeave) CEikLabel;
	iLabel->SetContainerWindowL(*this);
	iLabel->SetTextL(_L("MyView 1\n\nSelect local view\nswitching from menu"));
	iCharLcmControl->clearScreen();
	//iCharLcmControl->write("Haha hahahah...", sizeof("Haha hahahah..."));
	//SetRect(aRect);
	// Calculate actual full-screen mode rect
	CalculateFullscreenRect();
	// Set view extent
	SetRect(iFullRect);

	//SetExtentToWholeScreen();
	ActivateL();
	// Create a periodic timer but don't start it yet
	counter = 0;
	iPeriodicTimer = CPeriodic::NewL(CActive::EPriorityStandard);
	StartTimer();

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
	//_LIT(KMsgDebug,"ComponentControl index: %d");
	//RDebug::Print(KMsgDebug, aIndex);
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
	//iLabel->SetExtent(TPoint(50, 50), iLabel->MinimumSize());
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
	
	if(aPointerEvent.iType==TPointerEvent::EButton1Up)
		{
			if(iIsCBAVisible)
				iIsCBAVisible=EFalse;
			else
				iIsCBAVisible=ETrue;
	    	CalculateFullscreenRect();
	    	SetFullRect();
		}
	}
// -----------------------------------------------------------------------------
// CGraphicsAppView::DoPeriodTask()
// Move the sprites.
// -----------------------------------------------------------------------------
//

void CLcdEmulatorAppView::DoPeriodTask()
	{
	User::ResetInactivityTime();
	counter++;

	TBuf8<256> strBuf;
	_LIT8(KFormat1,"This is an example of using LCD Char Emulator Counter:%d");
	strBuf.Format(KFormat1, counter);
	iCharLcmControl->setCursor(0, 0);
	iCharLcmControl->showString(strBuf);

	}

// -----------------------------------------------------------------------------
// CGraphicsAppView::Period()
// This function is called by the periodic timer.
// -----------------------------------------------------------------------------
//
TInt CLcdEmulatorAppView::Period(TAny* aPtr)
	{
	(static_cast<CLcdEmulatorAppView*> (aPtr))->DoPeriodTask();
	// Returning a value of TRUE indicates the callback should be done again
	return ETrue;
	}

// -----------------------------------------------------------------------------
// CGraphicsAppView::StartTimer()
// Start Timer.
// -----------------------------------------------------------------------------
//
void CLcdEmulatorAppView::StartTimer()
	{
	// If the timer is not already running, start it
	if (!iPeriodicTimer->IsActive())
		{
		iPeriodicTimer->Start(1000, 33333,
				TCallBack(CLcdEmulatorAppView::Period, this));
		}

	}
// -----------------------------------------------------------------------------
// CGraphicsAppView::StopDemo()
// Stops the balls.
// -----------------------------------------------------------------------------
//
void CLcdEmulatorAppView::StopTimer()
	{
	// Stop the timer if it is active
	if (iPeriodicTimer->IsActive())
		{
		iPeriodicTimer->Cancel();
		}
	}

void CLcdEmulatorAppView::SetFullRect()
	{
	SetRect(iFullRect);
	}

void CLcdEmulatorAppView::CalculateFullscreenRect()
	{

	// Window that fills the entire screen
	TRect temp_rect;
	AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EApplicationWindow,
			temp_rect);
	iFullRect = temp_rect;

	if (iIsCBAVisible)
		{
		// Rect that occupied by control pane (i.e. CBA)
		AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EControlPane,
				temp_rect);

		// Calculate final rect which depends on CBA location
		AknLayoutUtils::TAknCbaLocation cba_location =
				AknLayoutUtils::CbaLocation();

		switch (cba_location)
			{
			case AknLayoutUtils::EAknCbaLocationBottom:
				iFullRect.iBr.iY -= temp_rect.Height();
				break;

			case AknLayoutUtils::EAknCbaLocationLeft:
				iFullRect.iTl.iX += temp_rect.Width();
				break;

			case AknLayoutUtils::EAknCbaLocationRight:
				iFullRect.iBr.iX -= temp_rect.Width();
				break;

			default:
				break;
			}
		}

	}

// End of File
