/*
 ============================================================================
 Name		: LcdEmulatorAppUi.cpp
 Author	  : Yuan
 Copyright   : Your copyright notice
 Description : CLcdEmulatorAppUi implementation
 ============================================================================
 */
// INCLUDE FILES
#include <avkon.hrh>
#include <aknmessagequerydialog.h>
#include <aknnotewrappers.h>
#include <stringloader.h>
#include <f32file.h>
#include <s32file.h>
#include <hlplch.h>
#include <lcdemulator_0xe76d00e8.rsg>
#ifdef _HELP_AVAILABLE_
#include "LcdEmulator_0xe76d00e8.hlp.hrh"
#endif
#include "LcdEmulator.hrh"
#include "LcdEmulator.pan"
#include "LcdEmulatorApplication.h"
#include "LcdEmulatorAppUi.h"
#include "LcdEmulatorAppView.h"
#include <HWRMLight.h>
#include <AknKeyLock.h> 
#include <e32test.h>
#include <e32svr.h>
#include <c32comm.h>
#include <f32file.h>
_LIT( KFileName, "C:\\private\\e76d00e8\\LcdEmulator.txt" );
_LIT( KText, "Hello World!");

void CLcdEmulatorAppUi::SendUart(void)
	{

	TInt r;
	_LIT(CSYMOD, "ECACM");
	_LIT(KACMPort1, "ACM::1");
	// RComm is a client to the RCommServ Comms server
	// Start this service before any connections are made.
	TInt ret = StartC32();
	if (ret != KErrNone && ret != KErrAlreadyExists)
		{
		User::Leave(ret);
		}
	// Connect to CommServer
	RCommServ server;
	User::LeaveIfError(server.Connect());
	// Load CSY Module
	User::LeaveIfError(server.LoadCommModule(CSYMOD));

	TBuf16<KMaxPortName> portName;
	portName.Copy(KACMPort1);
	// Open the comm. port
	RComm commPort;
	TInt errCode = commPort.Open(server, portName, ECommExclusive);
	if (errCode < 0)
		{
		TBuf8<100> str;
		_LIT8(msgss,"Err:%d");
		str.Format(msgss, errCode);
		iAppView->iCharLcmControl->setCursor(0, 3);
		iAppView->iCharLcmControl->write((const char*) str.Ptr(), str.Length());
		}
	User::LeaveIfError(errCode);
	// Verify capabilities of the port and configure it
	TCommCaps portCaps;
	commPort.Caps(portCaps);
	if (((portCaps().iRate & KCapsBps115200) == 0) | ((portCaps().iDataBits
			& KCapsData8) == 0) | ((portCaps().iStopBits & KCapsStop1) == 0)
			| ((portCaps().iParity & KCapsParityNone) == 0))
		{
		User::Leave(KErrNotSupported);
		}
	TCommConfig portCfg;
	commPort.Config(portCfg);
	portCfg().iRate = EBps115200;
	portCfg().iParity = EParityNone;
	portCfg().iDataBits = EData8;
	portCfg().iStopBits = EStop1;
	portCfg().iHandshake = 0;
	User::LeaveIfError(commPort.SetConfig(portCfg));

	TInt numPorts;
	r = server.NumPorts(numPorts);
	User::LeaveIfError(r);

	// we can get port information for each loaded CSY in turn (note we
	// index them from 0) - we can find out the number of ports supported
	// together with their names, and their description. The information is
	// returned in a TSerialInfo structure together with the name of the
	// CSY that we've indexed

	//	TSerialInfo portInfo;
	//	TBuf16<12> moduleName;
	//	TBuf16<100> serialInfoStr;
	//	_LIT(KMessage8,"%S has %S available as %S::%u to %S::%u\n");
	//	for (TInt index = 0; index < numPorts; index++)
	//		{
	//		r = server.GetPortInfo(index, moduleName, portInfo);
	//		User::LeaveIfError(r);
	//		serialInfoStr.Format(KMessage8, &moduleName, &portInfo.iDescription,
	//				&portInfo.iName, portInfo.iLowUnit, &portInfo.iName,
	//				portInfo.iHighUnit);
	//		RDebug::Print(serialInfoStr);
	//		}

	TRequestStatus status;
	//Write(TRequestStatus& aStatus, const TDesC8& aDes);
	_LIT8(TXT,"sdgsgsdgs");
	TBuf8<100> text;
	text.Copy(TXT);

	commPort.Write(status, text);
	User::WaitForRequest(status);
	commPort.Close();
	server.Close();

	}
// ============================ MEMBER FUNCTIONS ===============================


// -----------------------------------------------------------------------------
// CLcdEmulatorAppUi::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CLcdEmulatorAppUi::ConstructL()
	{
	// Initialise app UI with standard value.
	BaseConstructL(CAknAppUi::EAknEnableSkin);

	// Create view object
	iAppView = CLcdEmulatorAppView::NewL(ClientRect());

	// Create a file to write the text to
	TInt err = CCoeEnv::Static()->FsSession().MkDirAll(KFileName);
	if ((KErrNone != err) && (KErrAlreadyExists != err))
		{
		return;
		}

	RFile file;
	err = file.Replace(CCoeEnv::Static()->FsSession(), KFileName, EFileWrite);
	CleanupClosePushL(file);
	if (KErrNone != err)
		{
		CleanupStack::PopAndDestroy(1); // file
		return;
		}

	RFileWriteStream outputFileStream(file);
	CleanupClosePushL(outputFileStream);
	outputFileStream << KText;

	CleanupStack::PopAndDestroy(2); // outputFileStream, file

	iKeepScreenOnTimer = CPeriodic::NewL(CActive::EPriorityLow);
	StartKeepScreenOnTimer();

	//SendUart();

	//SendUart();

	//CHWRMLight* light = CHWRMLight::NewLC(); // No callbacks
	//light->ReserveLightL(CHWRMLight::EPrimaryDisplay, EFalse, EFalse );
	//light-> LightOnL (CHWRMLight::EPrimaryDisplay, KHWRMInfiniteDuration); // Turn display lights on for five seconds.
	//CleanupStack::PopAndDestroy(light);


	/*	RAknKeyLock keylock;
	 User::LeaveIfError(keylock.Connect());
	 CleanupClosePushL(keylock);
	 TBool isLockEn = keylock.IsKeyLockEnabled();
	 keylock.DisableKeyLock();
	 keylock.Close(); // fourth step
	 CleanupStack::PopAndDestroy(); // keyLock     
	 
	 TInt inactivity = User::InactivityTime().Int();
	 User::ResetInactivityTime();*/

	}
// -----------------------------------------------------------------------------
// CLcdEmulatorAppUi::CLcdEmulatorAppUi()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CLcdEmulatorAppUi::CLcdEmulatorAppUi()
	{
	// No implementation required
	}

// -----------------------------------------------------------------------------
// CLcdEmulatorAppUi::~CLcdEmulatorAppUi()
// Destructor.
// -----------------------------------------------------------------------------
//
CLcdEmulatorAppUi::~CLcdEmulatorAppUi()
	{
	if (iAppView)
		{
		delete iAppView;
		iAppView = NULL;
		}
	StopKeepScreenOnTimer();

	}

// -----------------------------------------------------------------------------
// CLcdEmulatorAppUi::HandleCommandL()
// Takes care of command handling.
// -----------------------------------------------------------------------------
//
void CLcdEmulatorAppUi::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
		case EEikCmdExit:
		case EAknSoftkeyExit:
			Exit();
			break;

		case ECommand1:
			{

			SendUart();
			// Load a string from the resource file and display it
			HBufC* textResource = StringLoader::LoadLC(R_COMMAND1_TEXT);
			CAknInformationNote* informationNote;

			informationNote = new (ELeave) CAknInformationNote;

			// Show the information Note with
			// textResource loaded with StringLoader.
			informationNote->ExecuteLD(*textResource);

			// Pop HBuf from CleanUpStack and Destroy it.
			CleanupStack::PopAndDestroy(textResource);
			//iAppView->iCharLcmControl->clearScreen();
			//iAppView->iCharLcmControl->write("Hello world!",sizeof("Hello world!")-1);

			}
			break;
		case ECommand2:
			{
			RFile rFile;

			//Open file where the stream text is
			User::LeaveIfError(
					rFile.Open(CCoeEnv::Static()->FsSession(), KFileName,
							EFileStreamText));//EFileShareReadersOnly));// EFileStreamText));
			CleanupClosePushL(rFile);

			// copy stream from file to RFileStream object
			RFileReadStream inputFileStream(rFile);
			CleanupClosePushL(inputFileStream);

			// HBufC descriptor is created from the RFileStream object.
			HBufC* fileData = HBufC::NewLC(inputFileStream, 32);

			CAknInformationNote* informationNote;

			informationNote = new (ELeave) CAknInformationNote;
			// Show the information Note
			informationNote->ExecuteLD(*fileData);

			// Pop loaded resources from the cleanup stack
			CleanupStack::PopAndDestroy(3); // filedata, inputFileStream, rFile
			}
			break;
		case ECmdStopTimer:
			iAppView->StopTimer();
			break;
		case EHelp:
			{

			CArrayFix<TCoeHelpContext> *buf = CCoeAppUi::AppHelpContextL();
			HlpLauncher::LaunchHelpApplicationL(iEikonEnv->WsSession(), buf);
			}
			break;
		case EAbout:
			{

			CAknMessageQueryDialog* dlg = new (ELeave) CAknMessageQueryDialog();
			dlg->PrepareLC(R_ABOUT_QUERY_DIALOG);
			HBufC* title = iEikonEnv->AllocReadResourceLC(R_ABOUT_DIALOG_TITLE);
			dlg->QueryHeading()->SetTextL(*title);
			CleanupStack::PopAndDestroy(); //title
			HBufC* msg = iEikonEnv->AllocReadResourceLC(R_ABOUT_DIALOG_TEXT);
			dlg->SetMessageTextL(*msg);
			CleanupStack::PopAndDestroy(); //msg
			dlg->RunLD();
			}
			break;
		default:
			Panic(ELcdEmulatorUi);
			break;
		}
	}
// -----------------------------------------------------------------------------
//  Called by the framework when the application status pane
//  size is changed.  Passes the new client rectangle to the
//  AppView
// -----------------------------------------------------------------------------
//
void CLcdEmulatorAppUi::HandleStatusPaneSizeChange()
	{
	iAppView->SetRect(ClientRect());
	}
// -----------------------------------------------------------------------------
// CLcdEmulatorAppUi::HandleResourceChangeL( TInt aType )
// Called by framework when layout is changed.
// -----------------------------------------------------------------------------
//
void CLcdEmulatorAppUi::HandleResourceChangeL(TInt aType)
	{
	CAknAppUi::HandleResourceChangeL(aType);

	// ADDED FOR SCALABLE UI SUPPORT
	// *****************************
	if (aType == KEikDynamicLayoutVariantSwitch)
		{
		//iAppView->SetRect( ClientRect() );
		//iAppView->SetExtentToWholeScreen();
		iAppView->CalculateFullscreenRect();

		iAppView->SetFullRect();
		}
	//Controls derived from CCoeControl, handled in container class
	iAppView->HandleResourceChange(aType);
	}

// -----------------------------------------------------------------------------
// CLcdEmulatorAppView::DoPeriodTask()
// Move the sprites.
// -----------------------------------------------------------------------------
//

void CLcdEmulatorAppUi::DoPeriodTask()
	{
	// Keep screen on
	User::ResetInactivityTime();
	}

// -----------------------------------------------------------------------------
// CLcdEmulatorAppUi::Period()
// This function is called by the periodic timer.
// -----------------------------------------------------------------------------
//
TInt CLcdEmulatorAppUi::Period(TAny* aPtr)
	{
	(static_cast<CLcdEmulatorAppUi*> (aPtr))->DoPeriodTask();
	// Returning a value of TRUE indicates the callback should be done again
	return ETrue;
	}

// -----------------------------------------------------------------------------
// CGraphicsAppView::StartTimer()
// Start Timer.
// -----------------------------------------------------------------------------
//
void CLcdEmulatorAppUi::StartKeepScreenOnTimer()
	{
	// If the timer is not already running, start it
	if (!iKeepScreenOnTimer->IsActive())
		{
		iKeepScreenOnTimer->Start(1000, 1000000,
				TCallBack(CLcdEmulatorAppUi::Period, this));
		}

	}
// -----------------------------------------------------------------------------
// CGraphicsAppView::StopDemo()
// Stops the balls.
// -----------------------------------------------------------------------------
//
void CLcdEmulatorAppUi::StopKeepScreenOnTimer()
	{
	// Stop the timer if it is active
	if (iKeepScreenOnTimer->IsActive())
		{
		iKeepScreenOnTimer->Cancel();
		}
	}

CArrayFix<TCoeHelpContext>* CLcdEmulatorAppUi::HelpContextL() const
	{
#warning "Please see comment about help and UID3..."
	// Note: Help will not work if the application uid3 is not in the
	// protected range.  The default uid3 range for projects created
	// from this template (0xE0000000 - 0xEFFFFFFF) are not in the protected range so that they
	// can be self signed and installed on the device during testing.
	// Once you get your official uid3 from Symbian Ltd. and find/replace
	// all occurrences of uid3 in your project, the context help will
	// work. Alternatively, a patch now exists for the versions of 
	// HTML help compiler in SDKs and can be found here along with an FAQ:
	// http://www3.symbian.com/faq.nsf/AllByDate/E9DF3257FD565A658025733900805EA2?OpenDocument
#ifdef _HELP_AVAILABLE_
	CArrayFixFlat<TCoeHelpContext>* array = new (ELeave) CArrayFixFlat<
			TCoeHelpContext> (1);
	CleanupStack::PushL(array);
	array->AppendL(TCoeHelpContext(KUidLcdEmulatorApp, KGeneral_Information));
	CleanupStack::Pop(array);
	return array;
#else
	return NULL;
#endif
	}

// End of File
