//******************************************************************************
//******************************************************************************
// Owner:   Andrew Forget (AndrewFo,x3438) 
//          Copyright © 1999, SOFTIMAGE, Avid Technologies
//------------------------------------------------------------------------------
//
// @doc     RICHEDITCTRLEX
//
// @module  RichEditCtrlEx.cpp |
//          This file implements the rich edit control extended class
//          <c CRichEditCtrlEx>.
//
// @version
//------------------------------------------------------------------------------
//.Version: Date:       Author:     Comments:
//.-------- ----------- ----------- --------------------------------------------
//.  1.0    01/18/99    AndrewFo    New file.
//******************************************************************************
//******************************************************************************


//******************************************************************************
//
// Includes
//
//******************************************************************************

#include "StdAfx.h"

#include "RichEditCtrlEx.h"


//******************************************************************************
//
// Debugging
//
//******************************************************************************

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//******************************************************************************
// Owner:   Andrew Forget (AndrewFo,x3438) 
//------------------------------------------------------------------------------
//
// @mfunc   | _AFX_RICHEDITEX_STATE | _AFX_RICHEDITEX_STATE |
//          Constructor for <c _AFX_RICHEDITEX_STATE>.
//
// @syntax  _AFX_RICHEDITEX_STATE() ;
//
// @version
//------------------------------------------------------------------------------
//.Version: Date:       Author:     Comments:
//.-------- ----------- ----------- --------------------------------------------
//.  1.0    01/18/99    AndrewFo    New code.
//******************************************************************************

_AFX_RICHEDITEX_STATE::_AFX_RICHEDITEX_STATE()
{
	m_hInstRichEdit20 = NULL ;
}

//******************************************************************************
// Owner:   Andrew Forget (AndrewFo,x3438) 
//------------------------------------------------------------------------------
//
// @mfunc   | _AFX_RICHEDITEX_STATE | ~_AFX_RICHEDITEX_STATE |
//          Destructor for <c _AFX_RICHEDITEX_STATE>.
//
// @syntax  ~_AFX_RICHEDITEX_STATE() ;
//
// @version
//------------------------------------------------------------------------------
//.Version: Date:       Author:     Comments:
//.-------- ----------- ----------- --------------------------------------------
//.  1.0    01/18/99    AndrewFo    New code.
//******************************************************************************

_AFX_RICHEDITEX_STATE::~_AFX_RICHEDITEX_STATE()
{
	if( m_hInstRichEdit20 != NULL )
	{
		::FreeLibrary( m_hInstRichEdit20 ) ;
	}
}


//******************************************************************************
//
// Global Data
//
//******************************************************************************

_AFX_RICHEDITEX_STATE _afxRichEditStateEx ;


//******************************************************************************
// Owner:   Andrew Forget (AndrewFo,x3438) 
//------------------------------------------------------------------------------
//
// @func    BOOL PASCAL | AfxInitRichEditEx |
//          This function must be called prior to creating any dialog which
//          uses the version 2.0 rich edit control.  For created classes, this
//          is called automatically.
//
// @syntax  BOOL PASCAL AfxInitRichEditEx() ;
//
// @rdesc   BOOL : A boolean value indicating:
// @flag        TRUE  | Success.
// @flag        FALSE | Failure.
//
// @comm    NOTE: This function will not work if AfxInitRichEdit() has been
//          called first and this will clash with the use of the CRichEditCtrl
//          class (including the CRichEditView class).
//
// @version
//------------------------------------------------------------------------------
//.Version: Date:       Author:     Comments:
//.-------- ----------- ----------- --------------------------------------------
//.  1.0    01/18/99    AndrewFo    New code.
//******************************************************************************

BOOL PASCAL AfxInitRichEditEx()
{
	if( ! ::AfxInitRichEdit() )
	{
		return FALSE ;
	}

	_AFX_RICHEDITEX_STATE* l_pState = &_afxRichEditStateEx ;

	if( l_pState->m_hInstRichEdit20 == NULL )
	{
		l_pState->m_hInstRichEdit20 = LoadLibraryA( "RICHED20.DLL" ) ;
	}

	return l_pState->m_hInstRichEdit20 != NULL ;
}



//******************************************************************************
// Owner:   Andrew Forget (AndrewFo,x3438) 
//------------------------------------------------------------------------------
//
// @mfunc   | CRichEditCtrlEx | CRichEditCtrlEx |
//          Constructor for <c CRichEditCtrlEx>.
//
// @syntax  CRichEditCtrlEx() ;
//
// @version
//------------------------------------------------------------------------------
//.Version: Date:       Author:     Comments:
//.-------- ----------- ----------- --------------------------------------------
//.  1.0    01/18/99    AndrewFo    New code.
//******************************************************************************

CRichEditCtrlEx::CRichEditCtrlEx()
{
}

//******************************************************************************
// Owner:   Andrew Forget (AndrewFo,x3438) 
//------------------------------------------------------------------------------
//
// @mfunc   | CRichEditCtrlEx | ~CRichEditCtrlEx |
//          Destructor for <c CRichEditCtrlEx>.
//
// @syntax  ~CRichEditCtrlEx() ;
//
// @version
//------------------------------------------------------------------------------
//.Version: Date:       Author:     Comments:
//.-------- ----------- ----------- --------------------------------------------
//.  1.0    01/18/99    AndrewFo    New code.
//******************************************************************************

CRichEditCtrlEx::~CRichEditCtrlEx()
{
}


//******************************************************************************
// Owner:   Andrew Forget (AndrewFo,x3438) 
//------------------------------------------------------------------------------
//
// @msgmap  CRichEditCtrl | CRichEditCtrlEx |
//          Message map for <c CRichEditCtrlEx>.
//
// @version
//------------------------------------------------------------------------------
//.Version: Date:       Author:     Comments:
//.-------- ----------- ----------- --------------------------------------------
//.  1.0    01/18/99    AndrewFo    New code.
//******************************************************************************

BEGIN_MESSAGE_MAP( CRichEditCtrlEx, CRichEditCtrl )

	//{{AFX_MSG_MAP( CRichEditCtrlEx )
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()


//******************************************************************************
// Owner:   Andrew Forget (AndrewFo,x3438) 
//------------------------------------------------------------------------------
//
// @mfunc   BOOL | CRichEditCtrlEx | Create |
//          This method is used to create the version 2.0 rich edit control.
//
// @syntax  BOOL Create(
//          			DWORD		in_dwStyle, 
//          			const RECT& in_rcRect, 
//          			CWnd*		in_pParentWnd, 
//          			UINT		in_nID ) ;
//
// @parm    DWORD | in_dwStyle |
//          The styles for the rich edit control.
//
// @parm    const RECT& | in_rcRect |
//          The rectangle for the control window.
//
// @parm    CWnd* | in_pParentWnd |
//          Pointer to the parent window.
//
// @parm    UINT | in_nID |
//          The dialog control ID for the control.
//
// @rdesc   BOOL : A boolean value indicating:
// @flag        TRUE  | Sucess.
// @flag        FALSE | Failure.
//
// @version
//------------------------------------------------------------------------------
//.Version: Date:       Author:     Comments:
//.-------- ----------- ----------- --------------------------------------------
//.  1.0    01/18/99    AndrewFo    New code.
//******************************************************************************

BOOL CRichEditCtrlEx::Create(
			DWORD		in_dwStyle, 
			const RECT& in_rcRect, 
			CWnd*		in_pParentWnd, 
			UINT		in_nID )
{
	if( ! ::AfxInitRichEditEx() )
	{
		return FALSE ;
	}

	CWnd* l_pWnd = this ;

	return l_pWnd->Create( _T( "RichEdit20A" ), NULL, in_dwStyle, in_rcRect, in_pParentWnd, in_nID ) ;
}
