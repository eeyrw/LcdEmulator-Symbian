/*
 ============================================================================
 Name		: LcdEmulator.pan
 Author	  : Yuan
 Copyright   : Your copyright notice
 Description : This file contains panic codes.
 ============================================================================
 */

#ifndef __LCDEMULATOR_PAN__
#define __LCDEMULATOR_PAN__

/** LcdEmulator application panic codes */
enum TLcdEmulatorPanics
	{
	ELcdEmulatorUi = 1
	// add further panics here
	};

inline void Panic(TLcdEmulatorPanics aReason)
	{
	_LIT(applicationName, "LcdEmulator");
	User::Panic(applicationName, aReason);
	}

#endif // __LCDEMULATOR_PAN__
