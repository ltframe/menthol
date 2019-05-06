#include "stdafx.h"
#include "Keyboard.h"
namespace Keyboard
{
	StackState NextField(VmState* vmstate)
	{
		return Object_CreateObject(IupNextField(static_cast<Ihandle*>(GetParam(1,vmstate).p)));
	}
	StackState PreviousField(VmState* vmstate)
	{
		return Object_CreateObject(IupPreviousField(static_cast<Ihandle*>(GetParam(1,vmstate).p)));
	}
	StackState GetFocus(VmState* vmstate)
	{
		IupGetFocus();
		return Null_CreateNull();
	}
	StackState SetFocus(VmState* vmstate)
	{
		return Object_CreateObject(IupSetFocus(static_cast<Ihandle*>(GetParam(1,vmstate).p)));
	}

	StackState GetKeyCodeString(VmState* vmstate)
	{
		int keycode = GetParam(1,vmstate).d;
		if (keycode==K_SP)
		{
			return String_CreateString("K_SP",vmstate);
		}
          
		if (keycode==K_exclam)
		{
			return String_CreateString("K_exclam",vmstate);
		}
      
		if (keycode==K_quotedbl)
		{
			return String_CreateString("K_quotedbl",vmstate);
		}
    
		if (keycode==K_numbersign)
		{
			return String_CreateString("K_numbersign",vmstate);
		}
  
		if (keycode==K_dollar)
		{
			return String_CreateString("K_dollar",vmstate);
		}
      
		if (keycode==K_percent)
		{
			return String_CreateString("K_percent",vmstate);
		}
     
		if (keycode==K_ampersand)
		{
			return String_CreateString("K_ampersand",vmstate);
		}
   
		if (keycode==K_apostrophe)
		{
			return String_CreateString("K_apostrophe",vmstate);
		}
  
		if (keycode==K_parentleft)
		{
			return String_CreateString("K_parentleft",vmstate);
		}
  
		if (keycode==K_parentright)
		{
			return String_CreateString("K_parentright",vmstate);
		}
 
		if (keycode==K_asterisk)
		{
			return String_CreateString("K_asterisk",vmstate);
		}
    
		if (keycode==K_plus)
		{
			return String_CreateString("K_plus",vmstate);
		}
        
		if (keycode==K_comma)
		{
			return String_CreateString("K_comma",vmstate);
		}
       
		if (keycode==K_minus)
		{
			return String_CreateString("K_minus",vmstate);
		}
       
		if (keycode==K_period)
		{
			return String_CreateString("K_period",vmstate);
		}
      
		if (keycode==K_slash)
		{
			return String_CreateString("K_slash",vmstate);
		}
       
		if (keycode==K_0)
		{
			return String_CreateString("K_0",vmstate);
		}

		if (keycode==K_1)
		{
			return String_CreateString("K_1",vmstate);
		}

		if (keycode==K_2)
		{
			return String_CreateString("K_2",vmstate);
		}

		if (keycode==K_3)
		{
			return String_CreateString("K_3",vmstate);
		}

		if (keycode==K_4)
		{
			return String_CreateString("K_4",vmstate);
		}

		if (keycode==K_5)
		{
			return String_CreateString("K_5",vmstate);
		}

		if (keycode==K_6)
		{
			return String_CreateString("K_6",vmstate);
		}

		if (keycode==K_7)
		{
			return String_CreateString("K_7",vmstate);
		}

		if (keycode==K_8)
		{
			return String_CreateString("K_8",vmstate);
		}

		if (keycode==K_9)
		{
			return String_CreateString("K_9",vmstate);
		}

		if (keycode==K_colon)
		{
			return String_CreateString("K_colon",vmstate);
		}
    
		if (keycode==K_semicolon)
		{
			return String_CreateString("K_semicolon",vmstate);
		}

		if (keycode==K_less)
		{
			return String_CreateString("K_less",vmstate);
		}
     
		if (keycode==K_equal)
		{
			return String_CreateString("K_equal",vmstate);
		}
    
		if (keycode==K_greater)
		{
			return String_CreateString("K_greater",vmstate);
		}
  
		if (keycode==K_question)
		{
			return String_CreateString("K_question",vmstate);
		}
 
		if (keycode==K_at)
		{
			return String_CreateString("K_at",vmstate);
		}
       
		if (keycode==K_A)
		{
			return String_CreateString("K_A",vmstate);
		}

		if (keycode==K_B)
		{
			return String_CreateString("K_B",vmstate);
		}

		if (keycode==K_C)
		{
			return String_CreateString("K_C",vmstate);
		}

		if (keycode==K_D)
		{
			return String_CreateString("K_D",vmstate);
		}

		if (keycode==K_E)
		{
			return String_CreateString("K_E",vmstate);
		}

		if (keycode==K_F)
		{
			return String_CreateString("K_F",vmstate);
		}

		if (keycode==K_G)
		{
			return String_CreateString("K_G",vmstate);
		}

		if (keycode==K_H)
		{
			return String_CreateString("K_H",vmstate);
		}

		if (keycode==K_I)
		{
			return String_CreateString("K_I",vmstate);
		}

		if (keycode==K_J)
		{
			return String_CreateString("K_J",vmstate);
		}

		if (keycode==K_K)
		{
			return String_CreateString("K_K",vmstate);
		}

		if (keycode==K_L)
		{
			return String_CreateString("K_L",vmstate);
		}

		if (keycode==K_M)
		{
			return String_CreateString("K_M",vmstate);
		}

		if (keycode==K_N)
		{
			return String_CreateString("K_N",vmstate);
		}

		if (keycode==K_O)
		{
			return String_CreateString("K_O",vmstate);
		}

		if (keycode==K_P)
		{
			return String_CreateString("K_P",vmstate);
		}

		if (keycode==K_Q)
		{
			return String_CreateString("K_Q",vmstate);
		}

		if (keycode==K_R)
		{
			return String_CreateString("K_R",vmstate);
		}

		if (keycode==K_S)
		{
			return String_CreateString("K_S",vmstate);
		}

		if (keycode==K_T)
		{
			return String_CreateString("K_T",vmstate);
		}

		if (keycode==K_U)
		{
			return String_CreateString("K_U",vmstate);
		}

		if (keycode==K_V)
		{
			return String_CreateString("K_V",vmstate);
		}

		if (keycode==K_W)
		{
			return String_CreateString("K_W",vmstate);
		}

		if (keycode==K_X)
		{
			return String_CreateString("K_X",vmstate);
		}

		if (keycode==K_Y)
		{
			return String_CreateString("K_Y",vmstate);
		}

		if (keycode==K_Z)
		{
			return String_CreateString("K_Z",vmstate);
		}

		if (keycode==K_bracketleft)
		{
			return String_CreateString("K_bracketleft",vmstate);
		}

		if (keycode==K_backslash)
		{
			return String_CreateString("K_backslash",vmstate);
		}
  
		if (keycode==K_bracketright)
		{
			return String_CreateString("K_bracketright",vmstate);
		}

		if (keycode==K_circum)
		{
			return String_CreateString("K_circum",vmstate);
		}
      
		if (keycode==K_underscore)
		{
			return String_CreateString("K_underscore",vmstate);
		}
  
		if (keycode==K_grave)
		{
			return String_CreateString("K_grave",vmstate);
		}
       
		if (keycode==K_a)
		{
			return String_CreateString("K_a",vmstate);
		}

		if (keycode==K_b)
		{
			return String_CreateString("K_b",vmstate);
		}

		if (keycode==K_c)
		{
			return String_CreateString("K_c",vmstate);
		}

		if (keycode==K_d)
		{
			return String_CreateString("K_d",vmstate);
		}

		if (keycode==K_e)
		{
			return String_CreateString("K_e",vmstate);
		}

		if (keycode==K_f)
		{
			return String_CreateString("K_f",vmstate);
		}

		if (keycode==K_g)
		{
			return String_CreateString("K_g",vmstate);
		}

		if (keycode==K_h)
		{
			return String_CreateString("K_h",vmstate);
		}

		if (keycode==K_i)
		{
			return String_CreateString("K_i",vmstate);
		}

		if (keycode==K_j)
		{
			return String_CreateString("K_j",vmstate);
		}

		if (keycode==K_k)
		{
			return String_CreateString("K_k",vmstate);
		}

		if (keycode==K_l)
		{
			return String_CreateString("K_l",vmstate);
		}

		if (keycode==K_m)
		{
			return String_CreateString("K_m",vmstate);
		}

		if (keycode==K_n)
		{
			return String_CreateString("K_n",vmstate);
		}

		if (keycode==K_o)
		{
			return String_CreateString("K_o",vmstate);
		}

		if (keycode==K_p)
		{
			return String_CreateString("K_p",vmstate);
		}

		if (keycode==K_q)
		{
			return String_CreateString("K_q",vmstate);
		}

		if (keycode==K_r)
		{
			return String_CreateString("K_r",vmstate);
		}

		if (keycode==K_s)
		{
			return String_CreateString("K_s",vmstate);
		}

		if (keycode==K_t)
		{
			return String_CreateString("K_t",vmstate);
		}

		if (keycode==K_u)
		{
			return String_CreateString("K_u",vmstate);
		}

		if (keycode==K_v)
		{
			return String_CreateString("K_v",vmstate);
		}

		if (keycode==K_w)
		{
			return String_CreateString("K_w",vmstate);
		}

		if (keycode==K_x)
		{
			return String_CreateString("K_x",vmstate);
		}

		if (keycode==K_y)
		{
			return String_CreateString("K_y",vmstate);
		}

		if (keycode==K_z)
		{
			return String_CreateString("K_z",vmstate);
		}

		if (keycode==K_braceleft)
		{
			return String_CreateString("K_braceleft",vmstate);
		}
  
		if (keycode==K_bar)
		{
			return String_CreateString("K_bar",vmstate);
		}
        
		if (keycode==K_braceright)
		{
			return String_CreateString("K_braceright",vmstate);
		}
 
		if (keycode==K_tilde)
		{
			return String_CreateString("K_tilde",vmstate);
		}
      
		if (keycode==K_BS)
		{
			return String_CreateString("K_BS",vmstate);
		}
  
		if (keycode==K_TAB)
		{
			return String_CreateString("K_TAB",vmstate);
		}
 
		if (keycode==K_LF)
		{
			return String_CreateString("K_LF",vmstate);
		}
  
		if (keycode==K_CR)
		{
			return String_CreateString("K_CR",vmstate);
		}
  
		if (keycode==K_quoteleft)
		{
			return String_CreateString("K_quoteleft",vmstate);
		}
 
		if (keycode==K_quoteright)
		{
			return String_CreateString("K_quoteright",vmstate);
		}

		if (keycode==K_PAUSE)
		{
			return String_CreateString("K_PAUSE",vmstate);
		}
  
		if (keycode==K_ESC)
		{
			return String_CreateString("K_ESC",vmstate);
		}
    
		if (keycode==K_HOME)
		{
			return String_CreateString("K_HOME",vmstate);
		}
     
		if (keycode==K_LEFT)
		{
			return String_CreateString("K_LEFT",vmstate);
		}
   
		if (keycode==K_UP)
		{
			return String_CreateString("K_UP",vmstate);
		}
     
		if (keycode==K_RIGHT)
		{
			return String_CreateString("K_RIGHT",vmstate);
		}
  
		if (keycode==K_DOWN)
		{
			return String_CreateString("K_DOWN",vmstate);
		}
   
		if (keycode==K_PGUP)
		{
			return String_CreateString("K_PGUP",vmstate);
		}
   
		if (keycode==K_PGDN)
		{
			return String_CreateString("K_PGDN",vmstate);
		}
   
		if (keycode==K_END)
		{
			return String_CreateString("K_END",vmstate);
		}
    
		if (keycode==K_MIDDLE)
		{
			return String_CreateString("K_MIDDLE",vmstate);
		}
 
		if (keycode==K_Print)
		{
			return String_CreateString("K_Print",vmstate);
		}
  
		if (keycode==K_INS)
		{
			return String_CreateString("K_INS",vmstate);
		}
    
		if (keycode==K_Menu)
		{
			return String_CreateString("K_Menu",vmstate);
		}
   
		if (keycode==K_DEL)
		{
			return String_CreateString("K_DEL",vmstate);
		}
    
		if (keycode==K_F1)
		{
			return String_CreateString("K_F1",vmstate);
		}
     
		if (keycode==K_F2)
		{
			return String_CreateString("K_F2",vmstate);
		}
     
		if (keycode==K_F3)
		{
			return String_CreateString("K_F3",vmstate);
		}
     
		if (keycode==K_F4)
		{
			return String_CreateString("K_F4",vmstate);
		}
     
		if (keycode==K_F5)
		{
			return String_CreateString("K_F5",vmstate);
		}
     
		if (keycode==K_F6)
		{
			return String_CreateString("K_F6",vmstate);
		}
     
		if (keycode==K_F7)
		{
			return String_CreateString("K_F7",vmstate);
		}
     
		if (keycode==K_F8)
		{
			return String_CreateString("K_F8",vmstate);
		}
     
		if (keycode==K_F9)
		{
			return String_CreateString("K_F9",vmstate);
		}
     
		if (keycode==K_F10)
		{
			return String_CreateString("K_F10",vmstate);
		}
    
		if (keycode==K_F11)
		{
			return String_CreateString("K_F11",vmstate);
		}
    
		if (keycode==K_F12)
		{
			return String_CreateString("K_F12",vmstate);
		}
    
		if (keycode==K_LSHIFT)
		{
			return String_CreateString("K_LSHIFT",vmstate);
		}
 
		if (keycode==K_RSHIFT)
		{
			return String_CreateString("K_RSHIFT",vmstate);
		}
 
		if (keycode==K_LCTRL)
		{
			return String_CreateString("K_LCTRL",vmstate);
		}
  
		if (keycode==K_RCTRL)
		{
			return String_CreateString("K_RCTRL",vmstate);
		}
  
		if (keycode==K_LALT)
		{
			return String_CreateString("K_LALT",vmstate);
		}
   
		if (keycode==K_RALT)
		{
			return String_CreateString("K_RALT",vmstate);
		}
   
		if (keycode==K_NUM)
		{
			return String_CreateString("K_NUM",vmstate);
		}
    
		if (keycode==K_SCROLL)
		{
			return String_CreateString("K_SCROLL",vmstate);
		}
 
		if (keycode==K_CAPS)
		{
			return String_CreateString("K_CAPS",vmstate);
		}
   
		if (keycode==K_ccedilla)
		{
			return String_CreateString("K_ccedilla",vmstate);
		}
  
		if (keycode==K_Ccedilla)
		{
			return String_CreateString("K_Ccedilla",vmstate);
		}
  
		if (keycode==K_acute)
		{
			return String_CreateString("K_acute",vmstate);
		}
     
		if (keycode==K_diaeresis)
		{
			return String_CreateString("K_diaeresis",vmstate);
		}
 
		if (keycode==K_sHOME)
		{
			return String_CreateString("K_sHOME",vmstate);
		}
    
		if (keycode==K_sUP)
		{
			return String_CreateString("K_sUP",vmstate);
		}
      
		if (keycode==K_sPGUP)
		{
			return String_CreateString("K_sPGUP",vmstate);
		}
    
		if (keycode==K_sLEFT)
		{
			return String_CreateString("K_sLEFT",vmstate);
		}
    
		if (keycode==K_sMIDDLE)
		{
			return String_CreateString("K_sMIDDLE",vmstate);
		}
  
		if (keycode==K_sRIGHT)
		{
			return String_CreateString("K_sRIGHT",vmstate);
		}
   
		if (keycode==K_sEND)
		{
			return String_CreateString("K_sEND",vmstate);
		}
     
		if (keycode==K_sDOWN)
		{
			return String_CreateString("K_sDOWN",vmstate);
		}
    
		if (keycode==K_sPGDN)
		{
			return String_CreateString("K_sPGDN",vmstate);
		}
    
		if (keycode==K_sINS)
		{
			return String_CreateString("K_sINS",vmstate);
		}
     
		if (keycode==K_sDEL)
		{
			return String_CreateString("K_sDEL",vmstate);
		}
     
		if (keycode==K_sSP)
		{
			return String_CreateString("K_sSP",vmstate);
		}
      
		if (keycode==K_sTAB)
		{
			return String_CreateString("K_sTAB",vmstate);
		}
     
		if (keycode==K_sCR)
		{
			return String_CreateString("K_sCR",vmstate);
		}
      
		if (keycode==K_sBS)
		{
			return String_CreateString("K_sBS",vmstate);
		}
      
		if (keycode==K_sPAUSE)
		{
			return String_CreateString("K_sPAUSE",vmstate);
		}
   
		if (keycode==K_sESC)
		{
			return String_CreateString("K_sESC",vmstate);
		}
     
		if (keycode==K_sF1)
		{
			return String_CreateString("K_sF1",vmstate);
		}
      
		if (keycode==K_sF2)
		{
			return String_CreateString("K_sF2",vmstate);
		}
      
		if (keycode==K_sF3)
		{
			return String_CreateString("K_sF3",vmstate);
		}
      
		if (keycode==K_sF4)
		{
			return String_CreateString("K_sF4",vmstate);
		}
      
		if (keycode==K_sF5)
		{
			return String_CreateString("K_sF5",vmstate);
		}
      
		if (keycode==K_sF6)
		{
			return String_CreateString("K_sF6",vmstate);
		}
      
		if (keycode==K_sF7)
		{
			return String_CreateString("K_sF7",vmstate);
		}
      
		if (keycode==K_sF8)
		{
			return String_CreateString("K_sF8",vmstate);
		}
      
		if (keycode==K_sF9)
		{
			return String_CreateString("K_sF9",vmstate);
		}
      
		if (keycode==K_sF10)
		{
			return String_CreateString("K_sF10",vmstate);
		}
     
		if (keycode==K_sF11)
		{
			return String_CreateString("K_sF11",vmstate);
		}
     
		if (keycode==K_sF12)
		{
			return String_CreateString("K_sF12",vmstate);
		}
     
		if (keycode==K_sPrint)
		{
			return String_CreateString("K_sPrint",vmstate);
		}
   
		if (keycode==K_sMenu)
		{
			return String_CreateString("K_sMenu",vmstate);
		}
    
		if (keycode==K_cHOME)
		{
			return String_CreateString("K_cHOME",vmstate);
		}
    
		if (keycode==K_cUP)
		{
			return String_CreateString("K_cUP",vmstate);
		}
      
		if (keycode==K_cPGUP)
		{
			return String_CreateString("K_cPGUP",vmstate);
		}
    
		if (keycode==K_cLEFT)
		{
			return String_CreateString("K_cLEFT",vmstate);
		}
    
		if (keycode==K_cMIDDLE)
		{
			return String_CreateString("K_cMIDDLE",vmstate);
		}
  
		if (keycode==K_cRIGHT)
		{
			return String_CreateString("K_cRIGHT",vmstate);
		}
   
		if (keycode==K_cEND)
		{
			return String_CreateString("K_cEND",vmstate);
		}
     
		if (keycode==K_cDOWN)
		{
			return String_CreateString("K_cDOWN",vmstate);
		}
    
		if (keycode==K_cPGDN)
		{
			return String_CreateString("K_cPGDN",vmstate);
		}
    
		if (keycode==K_cINS)
		{
			return String_CreateString("K_cINS",vmstate);
		}
     
		if (keycode==K_cDEL)
		{
			return String_CreateString("K_cDEL",vmstate);
		}
     
		if (keycode==K_cSP)
		{
			return String_CreateString("K_cSP",vmstate);
		}
      
		if (keycode==K_cTAB)
		{
			return String_CreateString("K_cTAB",vmstate);
		}
     
		if (keycode==K_cCR)
		{
			return String_CreateString("K_cCR",vmstate);
		}
      
		if (keycode==K_cBS)
		{
			return String_CreateString("K_cBS",vmstate);
		}
      
		if (keycode==K_cPAUSE)
		{
			return String_CreateString("K_cPAUSE",vmstate);
		}
   
		if (keycode==K_cESC)
		{
			return String_CreateString("K_cESC",vmstate);
		}
     
		if (keycode==K_cCcedilla)
		{
			return String_CreateString("K_cCcedilla",vmstate);
		}

		if (keycode==K_cF1)
		{
			return String_CreateString("K_cF1",vmstate);
		}
      
		if (keycode==K_cF2)
		{
			return String_CreateString("K_cF2",vmstate);
		}
      
		if (keycode==K_cF3)
		{
			return String_CreateString("K_cF3",vmstate);
		}
      
		if (keycode==K_cF4)
		{
			return String_CreateString("K_cF4",vmstate);
		}
      
		if (keycode==K_cF5)
		{
			return String_CreateString("K_cF5",vmstate);
		}
      
		if (keycode==K_cF6)
		{
			return String_CreateString("K_cF6",vmstate);
		}
      
		if (keycode==K_cF7)
		{
			return String_CreateString("K_cF7",vmstate);
		}
      
		if (keycode==K_cF8)
		{
			return String_CreateString("K_cF8",vmstate);
		}
      
		if (keycode==K_cF9)
		{
			return String_CreateString("K_cF9",vmstate);
		}
      
		if (keycode==K_cF10)
		{
			return String_CreateString("K_cF10",vmstate);
		}
     
		if (keycode==K_cF11)
		{
			return String_CreateString("K_cF11",vmstate);
		}
     
		if (keycode==K_cF12)
		{
			return String_CreateString("K_cF12",vmstate);
		}
     
		if (keycode==K_cPrint)
		{
			return String_CreateString("K_cPrint",vmstate);
		}
   
		if (keycode==K_cMenu)
		{
			return String_CreateString("K_cMenu",vmstate);
		}
    
		if (keycode==K_mHOME)
		{
			return String_CreateString("K_mHOME",vmstate);
		}
    
		if (keycode==K_mUP)
		{
			return String_CreateString("K_mUP",vmstate);
		}
      
		if (keycode==K_mPGUP)
		{
			return String_CreateString("K_mPGUP",vmstate);
		}
    
		if (keycode==K_mLEFT)
		{
			return String_CreateString("K_mLEFT",vmstate);
		}
    
		if (keycode==K_mMIDDLE)
		{
			return String_CreateString("K_mMIDDLE",vmstate);
		}
  
		if (keycode==K_mRIGHT)
		{
			return String_CreateString("K_mRIGHT",vmstate);
		}
   
		if (keycode==K_mEND)
		{
			return String_CreateString("K_mEND",vmstate);
		}
     
		if (keycode==K_mDOWN)
		{
			return String_CreateString("K_mDOWN",vmstate);
		}
    
		if (keycode==K_mPGDN)
		{
			return String_CreateString("K_mPGDN",vmstate);
		}
    
		if (keycode==K_mINS)
		{
			return String_CreateString("K_mINS",vmstate);
		}
     
		if (keycode==K_mDEL)
		{
			return String_CreateString("K_mDEL",vmstate);
		}
     
		if (keycode==K_mSP)
		{
			return String_CreateString("K_mSP",vmstate);
		}
      
		if (keycode==K_mTAB)
		{
			return String_CreateString("K_mTAB",vmstate);
		}
     
		if (keycode==K_mCR)
		{
			return String_CreateString("K_mCR",vmstate);
		}
      
		if (keycode==K_mBS)
		{
			return String_CreateString("K_mBS",vmstate);
		}
      
		if (keycode==K_mPAUSE)
		{
			return String_CreateString("K_mPAUSE",vmstate);
		}
   
		if (keycode==K_mESC)
		{
			return String_CreateString("K_mESC",vmstate);
		}
     
		if (keycode==K_mCcedilla)
		{
			return String_CreateString("K_mCcedilla",vmstate);
		}

		if (keycode==K_mF1)
		{
			return String_CreateString("K_mF1",vmstate);
		}
      
		if (keycode==K_mF2)
		{
			return String_CreateString("K_mF2",vmstate);
		}
      
		if (keycode==K_mF3)
		{
			return String_CreateString("K_mF3",vmstate);
		}
      
		if (keycode==K_mF4)
		{
			return String_CreateString("K_mF4",vmstate);
		}
      
		if (keycode==K_mF5)
		{
			return String_CreateString("K_mF5",vmstate);
		}
      
		if (keycode==K_mF6)
		{
			return String_CreateString("K_mF6",vmstate);
		}
      
		if (keycode==K_mF7)
		{
			return String_CreateString("K_mF7",vmstate);
		}
      
		if (keycode==K_mF8)
		{
			return String_CreateString("K_mF8",vmstate);
		}
      
		if (keycode==K_mF9)
		{
			return String_CreateString("K_mF9",vmstate);
		}
      
		if (keycode==K_mF10)
		{
			return String_CreateString("K_mF10",vmstate);
		}
     
		if (keycode==K_mF11)
		{
			return String_CreateString("K_mF11",vmstate);
		}
     
		if (keycode==K_mF12)
		{
			return String_CreateString("K_mF12",vmstate);
		}
     
		if (keycode==K_mPrint)
		{
			return String_CreateString("K_mPrint",vmstate);
		}
   
		if (keycode==K_mMenu)
		{
			return String_CreateString("K_mMenu",vmstate);
		}
    
		if (keycode==K_yHOME)
		{
			return String_CreateString("K_yHOME",vmstate);
		}
    
		if (keycode==K_yUP)
		{
			return String_CreateString("K_yUP",vmstate);
		}
      
		if (keycode==K_yPGUP)
		{
			return String_CreateString("K_yPGUP",vmstate);
		}
    
		if (keycode==K_yLEFT)
		{
			return String_CreateString("K_yLEFT",vmstate);
		}
    
		if (keycode==K_yMIDDLE)
		{
			return String_CreateString("K_yMIDDLE",vmstate);
		}
  
		if (keycode==K_yRIGHT)
		{
			return String_CreateString("K_yRIGHT",vmstate);
		}
   
		if (keycode==K_yEND)
		{
			return String_CreateString("K_yEND",vmstate);
		}
     
		if (keycode==K_yDOWN)
		{
			return String_CreateString("K_yDOWN",vmstate);
		}
    
		if (keycode==K_yPGDN)
		{
			return String_CreateString("K_yPGDN",vmstate);
		}
    
		if (keycode==K_yINS)
		{
			return String_CreateString("K_yINS",vmstate);
		}
     
		if (keycode==K_yDEL)
		{
			return String_CreateString("K_yDEL",vmstate);
		}
     
		if (keycode==K_ySP)
		{
			return String_CreateString("K_ySP",vmstate);
		}
      
		if (keycode==K_yTAB)
		{
			return String_CreateString("K_yTAB",vmstate);
		}
     
		if (keycode==K_yCR)
		{
			return String_CreateString("K_yCR",vmstate);
		}
      
		if (keycode==K_yBS)
		{
			return String_CreateString("K_yBS",vmstate);
		}
      
		if (keycode==K_yPAUSE)
		{
			return String_CreateString("K_yPAUSE",vmstate);
		}
   
		if (keycode==K_yESC)
		{
			return String_CreateString("K_yESC",vmstate);
		}
     
		if (keycode==K_yCcedilla)
		{
			return String_CreateString("K_yCcedilla",vmstate);
		}

		if (keycode==K_yF1)
		{
			return String_CreateString("K_yF1",vmstate);
		}
      
		if (keycode==K_yF2)
		{
			return String_CreateString("K_yF2",vmstate);
		}
      
		if (keycode==K_yF3)
		{
			return String_CreateString("K_yF3",vmstate);
		}
      
		if (keycode==K_yF4)
		{
			return String_CreateString("K_yF4",vmstate);
		}
      
		if (keycode==K_yF5)
		{
			return String_CreateString("K_yF5",vmstate);
		}
      
		if (keycode==K_yF6)
		{
			return String_CreateString("K_yF6",vmstate);
		}
      
		if (keycode==K_yF7)
		{
			return String_CreateString("K_yF7",vmstate);
		}
      
		if (keycode==K_yF8)
		{
			return String_CreateString("K_yF8",vmstate);
		}
      
		if (keycode==K_yF9)
		{
			return String_CreateString("K_yF9",vmstate);
		}
      
		if (keycode==K_yF10)
		{
			return String_CreateString("K_yF10",vmstate);
		}
     
		if (keycode==K_yF11)
		{
			return String_CreateString("K_yF11",vmstate);
		}
     
		if (keycode==K_yF12)
		{
			return String_CreateString("K_yF12",vmstate);
		}
     
		if (keycode==K_yPrint)
		{
			return String_CreateString("K_yPrint",vmstate);
		}
   
		if (keycode==K_yMenu)
		{
			return String_CreateString("K_yMenu",vmstate);
		}
    
		if (keycode==K_sPlus)
		{
			return String_CreateString("K_sPlus",vmstate);
		}
    
		if (keycode==K_sComma)
		{
			return String_CreateString("K_sComma",vmstate);
		}
   
		if (keycode==K_sMinus)
		{
			return String_CreateString("K_sMinus",vmstate);
		}
   
		if (keycode==K_sPeriod)
		{
			return String_CreateString("K_sPeriod",vmstate);
		}
  
		if (keycode==K_sSlash)
		{
			return String_CreateString("K_sSlash",vmstate);
		}
   
		if (keycode==K_sAsterisk)
		{
			return String_CreateString("K_sAsterisk",vmstate);
		}
              
		if (keycode==K_cA)
		{
			return String_CreateString("K_cA",vmstate);
		}

		if (keycode==K_cB)
		{
			return String_CreateString("K_cB",vmstate);
		}

		if (keycode==K_cC)
		{
			return String_CreateString("K_cC",vmstate);
		}

		if (keycode==K_cD)
		{
			return String_CreateString("K_cD",vmstate);
		}

		if (keycode==K_cE)
		{
			return String_CreateString("K_cE",vmstate);
		}

		if (keycode==K_cF)
		{
			return String_CreateString("K_cF",vmstate);
		}

		if (keycode==K_cG)
		{
			return String_CreateString("K_cG",vmstate);
		}

		if (keycode==K_cH)
		{
			return String_CreateString("K_cH",vmstate);
		}

		if (keycode==K_cI)
		{
			return String_CreateString("K_cI",vmstate);
		}

		if (keycode==K_cJ)
		{
			return String_CreateString("K_cJ",vmstate);
		}

		if (keycode==K_cK)
		{
			return String_CreateString("K_cK",vmstate);
		}

		if (keycode==K_cL)
		{
			return String_CreateString("K_cL",vmstate);
		}

		if (keycode==K_cM)
		{
			return String_CreateString("K_cM",vmstate);
		}

		if (keycode==K_cN)
		{
			return String_CreateString("K_cN",vmstate);
		}

		if (keycode==K_cO)
		{
			return String_CreateString("K_cO",vmstate);
		}

		if (keycode==K_cP)
		{
			return String_CreateString("K_cP",vmstate);
		}

		if (keycode==K_cQ)
		{
			return String_CreateString("K_cQ",vmstate);
		}

		if (keycode==K_cR)
		{
			return String_CreateString("K_cR",vmstate);
		}

		if (keycode==K_cS)
		{
			return String_CreateString("K_cS",vmstate);
		}

		if (keycode==K_cT)
		{
			return String_CreateString("K_cT",vmstate);
		}

		if (keycode==K_cU)
		{
			return String_CreateString("K_cU",vmstate);
		}

		if (keycode==K_cV)
		{
			return String_CreateString("K_cV",vmstate);
		}

		if (keycode==K_cW)
		{
			return String_CreateString("K_cW",vmstate);
		}

		if (keycode==K_cX)
		{
			return String_CreateString("K_cX",vmstate);
		}

		if (keycode==K_cY)
		{
			return String_CreateString("K_cY",vmstate);
		}

		if (keycode==K_cZ)
		{
			return String_CreateString("K_cZ",vmstate);
		}

		if (keycode==K_c1)
		{
			return String_CreateString("K_c1",vmstate);
		}

		if (keycode==K_c2)
		{
			return String_CreateString("K_c2",vmstate);
		}

		if (keycode==K_c3)
		{
			return String_CreateString("K_c3",vmstate);
		}

		if (keycode==K_c4)
		{
			return String_CreateString("K_c4",vmstate);
		}

		if (keycode==K_c5)
		{
			return String_CreateString("K_c5",vmstate);
		}

		if (keycode==K_c6)
		{
			return String_CreateString("K_c6",vmstate);
		}

		if (keycode==K_c7)
		{
			return String_CreateString("K_c7",vmstate);
		}

		if (keycode==K_c8)
		{
			return String_CreateString("K_c8",vmstate);
		}

		if (keycode==K_c9)
		{
			return String_CreateString("K_c9",vmstate);
		}

		if (keycode==K_c0)
		{
			return String_CreateString("K_c0",vmstate);
		}

		if (keycode==K_cPlus)
		{
			return String_CreateString("K_cPlus",vmstate);
		}
         
		if (keycode==K_cComma)
		{
			return String_CreateString("K_cComma",vmstate);
		}
        
		if (keycode==K_cMinus)
		{
			return String_CreateString("K_cMinus",vmstate);
		}
        
		if (keycode==K_cPeriod)
		{
			return String_CreateString("K_cPeriod",vmstate);
		}
       
		if (keycode==K_cSlash)
		{
			return String_CreateString("K_cSlash",vmstate);
		}
        
		if (keycode==K_cSemicolon)
		{
			return String_CreateString("K_cSemicolon",vmstate);
		}
    
		if (keycode==K_cEqual)
		{
			return String_CreateString("K_cEqual",vmstate);
		}
        
		if (keycode==K_cBracketleft)
		{
			return String_CreateString("K_cBracketleft",vmstate);
		}
  
		if (keycode==K_cBracketright)
		{
			return String_CreateString("K_cBracketright",vmstate);
		}
 
		if (keycode==K_cBackslash)
		{
			return String_CreateString("K_cBackslash",vmstate);
		}
    
		if (keycode==K_cAsterisk)
		{
			return String_CreateString("K_cAsterisk",vmstate);
		}
     
		if (keycode==K_mA)
		{
			return String_CreateString("K_mA",vmstate);
		}

		if (keycode==K_mB)
		{
			return String_CreateString("K_mB",vmstate);
		}

		if (keycode==K_mC)
		{
			return String_CreateString("K_mC",vmstate);
		}

		if (keycode==K_mD)
		{
			return String_CreateString("K_mD",vmstate);
		}

		if (keycode==K_mE)
		{
			return String_CreateString("K_mE",vmstate);
		}

		if (keycode==K_mF)
		{
			return String_CreateString("K_mF",vmstate);
		}

		if (keycode==K_mG)
		{
			return String_CreateString("K_mG",vmstate);
		}

		if (keycode==K_mH)
		{
			return String_CreateString("K_mH",vmstate);
		}

		if (keycode==K_mI)
		{
			return String_CreateString("K_mI",vmstate);
		}

		if (keycode==K_mJ)
		{
			return String_CreateString("K_mJ",vmstate);
		}

		if (keycode==K_mK)
		{
			return String_CreateString("K_mK",vmstate);
		}

		if (keycode==K_mL)
		{
			return String_CreateString("K_mL",vmstate);
		}

		if (keycode==K_mM)
		{
			return String_CreateString("K_mM",vmstate);
		}

		if (keycode==K_mN)
		{
			return String_CreateString("K_mN",vmstate);
		}

		if (keycode==K_mO)
		{
			return String_CreateString("K_mO",vmstate);
		}

		if (keycode==K_mP)
		{
			return String_CreateString("K_mP",vmstate);
		}

		if (keycode==K_mQ)
		{
			return String_CreateString("K_mQ",vmstate);
		}

		if (keycode==K_mR)
		{
			return String_CreateString("K_mR",vmstate);
		}

		if (keycode==K_mS)
		{
			return String_CreateString("K_mS",vmstate);
		}

		if (keycode==K_mT)
		{
			return String_CreateString("K_mT",vmstate);
		}

		if (keycode==K_mU)
		{
			return String_CreateString("K_mU",vmstate);
		}

		if (keycode==K_mV)
		{
			return String_CreateString("K_mV",vmstate);
		}

		if (keycode==K_mW)
		{
			return String_CreateString("K_mW",vmstate);
		}

		if (keycode==K_mX)
		{
			return String_CreateString("K_mX",vmstate);
		}

		if (keycode==K_mY)
		{
			return String_CreateString("K_mY",vmstate);
		}

		if (keycode==K_mZ)
		{
			return String_CreateString("K_mZ",vmstate);
		}

		if (keycode==K_m1)
		{
			return String_CreateString("K_m1",vmstate);
		}

		if (keycode==K_m2)
		{
			return String_CreateString("K_m2",vmstate);
		}

		if (keycode==K_m3)
		{
			return String_CreateString("K_m3",vmstate);
		}

		if (keycode==K_m4)
		{
			return String_CreateString("K_m4",vmstate);
		}

		if (keycode==K_m5)
		{
			return String_CreateString("K_m5",vmstate);
		}

		if (keycode==K_m6)
		{
			return String_CreateString("K_m6",vmstate);
		}

		if (keycode==K_m7)
		{
			return String_CreateString("K_m7",vmstate);
		}

		if (keycode==K_m8)
		{
			return String_CreateString("K_m8",vmstate);
		}

		if (keycode==K_m9)
		{
			return String_CreateString("K_m9",vmstate);
		}

		if (keycode==K_m0)
		{
			return String_CreateString("K_m0",vmstate);
		}

		if (keycode==K_mPlus)
		{
			return String_CreateString("K_mPlus",vmstate);
		}
         
		if (keycode==K_mComma)
		{
			return String_CreateString("K_mComma",vmstate);
		}
        
		if (keycode==K_mMinus)
		{
			return String_CreateString("K_mMinus",vmstate);
		}
        
		if (keycode==K_mPeriod)
		{
			return String_CreateString("K_mPeriod",vmstate);
		}
       
		if (keycode==K_mSlash)
		{
			return String_CreateString("K_mSlash",vmstate);
		}
        
		if (keycode==K_mSemicolon)
		{
			return String_CreateString("K_mSemicolon",vmstate);
		}
    
		if (keycode==K_mEqual)
		{
			return String_CreateString("K_mEqual",vmstate);
		}
        
		if (keycode==K_mBracketleft)
		{
			return String_CreateString("K_mBracketleft",vmstate);
		}
  
		if (keycode==K_mBracketright)
		{
			return String_CreateString("K_mBracketright",vmstate);
		}
 
		if (keycode==K_mBackslash)
		{
			return String_CreateString("K_mBackslash",vmstate);
		}
    
		if (keycode==K_mAsterisk)
		{
			return String_CreateString("K_mAsterisk",vmstate);
		}
     
		if (keycode==K_yA)
		{
			return String_CreateString("K_yA",vmstate);
		}

		if (keycode==K_yB)
		{
			return String_CreateString("K_yB",vmstate);
		}

		if (keycode==K_yC)
		{
			return String_CreateString("K_yC",vmstate);
		}

		if (keycode==K_yD)
		{
			return String_CreateString("K_yD",vmstate);
		}

		if (keycode==K_yE)
		{
			return String_CreateString("K_yE",vmstate);
		}

		if (keycode==K_yF)
		{
			return String_CreateString("K_yF",vmstate);
		}

		if (keycode==K_yG)
		{
			return String_CreateString("K_yG",vmstate);
		}

		if (keycode==K_yH)
		{
			return String_CreateString("K_yH",vmstate);
		}

		if (keycode==K_yI)
		{
			return String_CreateString("K_yI",vmstate);
		}

		if (keycode==K_yJ)
		{
			return String_CreateString("K_yJ",vmstate);
		}

		if (keycode==K_yK)
		{
			return String_CreateString("K_yK",vmstate);
		}

		if (keycode==K_yL)
		{
			return String_CreateString("K_yL",vmstate);
		}

		if (keycode==K_yM)
		{
			return String_CreateString("K_yM",vmstate);
		}

		if (keycode==K_yN)
		{
			return String_CreateString("K_yN",vmstate);
		}

		if (keycode==K_yO)
		{
			return String_CreateString("K_yO",vmstate);
		}

		if (keycode==K_yP)
		{
			return String_CreateString("K_yP",vmstate);
		}

		if (keycode==K_yQ)
		{
			return String_CreateString("K_yQ",vmstate);
		}

		if (keycode==K_yR)
		{
			return String_CreateString("K_yR",vmstate);
		}

		if (keycode==K_yS)
		{
			return String_CreateString("K_yS",vmstate);
		}

		if (keycode==K_yT)
		{
			return String_CreateString("K_yT",vmstate);
		}

		if (keycode==K_yU)
		{
			return String_CreateString("K_yU",vmstate);
		}

		if (keycode==K_yV)
		{
			return String_CreateString("K_yV",vmstate);
		}

		if (keycode==K_yW)
		{
			return String_CreateString("K_yW",vmstate);
		}

		if (keycode==K_yX)
		{
			return String_CreateString("K_yX",vmstate);
		}

		if (keycode==K_yY)
		{
			return String_CreateString("K_yY",vmstate);
		}

		if (keycode==K_yZ)
		{
			return String_CreateString("K_yZ",vmstate);
		}

		if (keycode==K_y1)
		{
			return String_CreateString("K_y1",vmstate);
		}

		if (keycode==K_y2)
		{
			return String_CreateString("K_y2",vmstate);
		}

		if (keycode==K_y3)
		{
			return String_CreateString("K_y3",vmstate);
		}

		if (keycode==K_y4)
		{
			return String_CreateString("K_y4",vmstate);
		}

		if (keycode==K_y5)
		{
			return String_CreateString("K_y5",vmstate);
		}

		if (keycode==K_y6)
		{
			return String_CreateString("K_y6",vmstate);
		}

		if (keycode==K_y7)
		{
			return String_CreateString("K_y7",vmstate);
		}

		if (keycode==K_y8)
		{
			return String_CreateString("K_y8",vmstate);
		}

		if (keycode==K_y9)
		{
			return String_CreateString("K_y9",vmstate);
		}

		if (keycode==K_y0)
		{
			return String_CreateString("K_y0",vmstate);
		}

		if (keycode==K_yPlus)
		{
			return String_CreateString("K_yPlus",vmstate);
		}
         
		if (keycode==K_yComma)
		{
			return String_CreateString("K_yComma",vmstate);
		}
        
		if (keycode==K_yMinus)
		{
			return String_CreateString("K_yMinus",vmstate);
		}
        
		if (keycode==K_yPeriod)
		{
			return String_CreateString("K_yPeriod",vmstate);
		}
       
		if (keycode==K_ySlash)
		{
			return String_CreateString("K_ySlash",vmstate);
		}
        
		if (keycode==K_ySemicolon)
		{
			return String_CreateString("K_ySemicolon",vmstate);
		}
    
		if (keycode==K_yEqual)
		{
			return String_CreateString("K_yEqual",vmstate);
		}
        
		if (keycode==K_yBracketleft)
		{
			return String_CreateString("K_yBracketleft",vmstate);
		}
  
		if (keycode==K_yBracketright)
		{
			return String_CreateString("K_yBracketright",vmstate);
		}
 
		if (keycode==K_yBackslash)
		{
			return String_CreateString("K_yBackslash",vmstate);
		}
    
		if (keycode==K_yAsterisk)
		{
			return String_CreateString("K_yAsterisk",vmstate);
		}   
		return Null_CreateNull();
	}
};

