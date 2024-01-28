/*
 ============================================================================
 Name		: CharLcmControl.cpp
 Author	  : Yuan
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CCharLcmControl implementation
 ============================================================================
 */

#include "CharLcmControl.h"

CCharLcmControl::CCharLcmControl()
	{
	}

CCharLcmControl::~CCharLcmControl()
	{
	
	}


CCharLcmControl* CCharLcmControl::NewL(RWindow& aWindow)
	{
	CCharLcmControl* self=new(ELeave) CCharLcmControl;
	CleanupStack::PushL(self);
	self->ConstructL(aWindow);
	CleanupStack::Pop();
	return self;
	}
void CCharLcmControl::ConstructL(RWindow& aWindow)
				{

				SetContainerWindowL(aWindow);

				// No call to ActivateL() as the window is activated by its container
				}

void CCharLcmControl::Draw(const TRect& /*aRect*/) const
	{
	// Get the standard graphics context
	CWindowGc& gc = SystemGc();

	// Gets the control's extent
	TRect drawRect(Rect());

	// Clears the screen
	gc.SetBrushColor(KRgbBlue);
	gc.Clear(drawRect);
	
	
	// Shrink by about 15%
	drawRect.Shrink(drawRect.Width()/6, drawRect.Height()/6);
	// Pen size set to just over 10% of the shape¡¯s size
	TSize penSize(drawRect.Width()/9, drawRect.Height()/9);
	gc.SetPenSize(penSize);
	gc.SetPenStyle(CGraphicsContext::ESolidPen);

	TRgb cl(KRgbRed);
	cl.SetAlpha(0);
	gc.SetPenColor(KRgbRed);
	gc.SetBrushColor(cl);
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	gc.DrawEllipse(drawRect);
	

	}

