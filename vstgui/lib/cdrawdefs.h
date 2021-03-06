//-----------------------------------------------------------------------------
// VST Plug-Ins SDK
// VSTGUI: Graphical User Interface Framework for VST plugins
//
// Version 4.3
//
//-----------------------------------------------------------------------------
// VSTGUI LICENSE
// (c) 2015, Steinberg Media Technologies, All Rights Reserved
//-----------------------------------------------------------------------------
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistributions of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//   * Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//   * Neither the name of the Steinberg Media Technologies nor the names of its
//     contributors may be used to endorse or promote products derived from this
//     software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
// OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE  OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.
//-----------------------------------------------------------------------------

#ifndef __cdrawdefs__
#define __cdrawdefs__

#include "vstguifwd.h"

namespace VSTGUI {

//-----------
// @brief Draw Mode Flags
//-----------
enum CDrawModeFlags
{
	kAliasing = 0,					///< aliased drawing
	kAntiAliasing = 1,				///< antialised drawing
	kNonIntegralMode = 0xF0000000		///< do not round coordinates to pixel aligned values
};

//-----------
// @brief Draw Mode
//-----------
struct CDrawMode
{
public:
	CDrawMode (uint32_t mode = kAliasing) : mode (mode) {}
	CDrawMode (const CDrawMode& m) : mode (m.mode) {}

	uint32_t modeIgnoringIntegralMode () const { return (mode & ~kNonIntegralMode); }

	bool integralMode () const { return mode & kNonIntegralMode ? false : true; }

	CDrawMode& operator= (uint32_t m) { mode = m; return *this; }

	uint32_t operator() () const { return mode; }
	bool operator== (const CDrawMode& m) const { return modeIgnoringIntegralMode () == m.modeIgnoringIntegralMode (); }
	bool operator!= (const CDrawMode& m) const { return modeIgnoringIntegralMode () != m.modeIgnoringIntegralMode (); }
private:
	uint32_t mode;
};

//----------------------------
// @brief Text Alignment (Horizontal)
//----------------------------
enum CHoriTxtAlign
{
	kLeftText = 0,
	kCenterText,
	kRightText
};

//----------------------------
// @brief Draw Style
//----------------------------
enum CDrawStyle
{
	kDrawStroked = 0,
	kDrawFilled,
	kDrawFilledAndStroked
};

}

#endif // __cdrawdefs__
