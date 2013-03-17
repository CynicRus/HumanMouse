/** © 2013, CynicRus All Rights Reserved.
*
* This file is part of the HumanMouse Library.
* HumanMouse is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* HumanMouse is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with HumanMouse. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef HUMANMOUSE_H_INCLUDED
#define HUMANMOUSE_H_INCLUDED
#include <Windows.h>

struct TBox;
struct tagHARDWAREINPUT;
struct tagINPUT;
struct tagKEYBDINPUT;
struct tagMOUSEINPUT;

struct TBox {
  int x1, y1, x2, y2;
};


enum TClickType {mouse_Left = 1,
                 mouse_Right = 0,
                 mouse_Middle = 2 };


struct tagMOUSEINPUT {
  int dx;
  int dy;
  DWORD mouseData;
  DWORD dwFlags;
  DWORD time;
  DWORD dwExtraInfo;
};


typedef tagMOUSEINPUT TMouseInput;
typedef TMouseInput* PMouseInput;

struct tagKEYBDINPUT {
  WORD wVk;
  WORD wScan;
  DWORD dwFlags;
  DWORD time;
  DWORD dwExtraInfo;
};

typedef tagKEYBDINPUT TKeybdInput;
typedef TKeybdInput* PKeybdInput;

struct tagHARDWAREINPUT {
  DWORD uMsg;
  WORD wParamL;
  WORD wParamH;
};


typedef tagHARDWAREINPUT THardwareInput;
typedef THardwareInput* PHardwareInput;

struct tagINPUT {
  DWORD Itype;
  /*# case Integer */
  union {
    /*# 0 */
    struct {
    TMouseInput mi;
    };
    /*# 1 */
    struct {
    TKeybdInput ki;
    };
    /*# 2 */
    struct {
    THardwareInput hi;
    };
  }; //union
};


typedef tagINPUT TInput;
typedef TInput* PInput;
const int INPUT_MOUSE = 0;
const int INPUT_KEYBOARD = 1;
const int INPUT_HARDWARE = 2;
 //WinApi
extern "C" __declspec(dllimport) /*# user32 name "SendInput" */
UINT __stdcall SendInput( UINT cInputs, TInput& pInputs, int cbSize );

 //Internal functions

extern "C" _declspec(dllexport) void __cdecl SetMouseSpeed(int Speed);
extern "C" _declspec(dllexport) int __cdecl GetMouseSpeed();


extern "C" _declspec(dllexport) void __cdecl GetMousePosition( int& x, int& y );
extern "C" _declspec(dllexport) void __cdecl MoveMouse( int x, int y );
extern "C" _declspec(dllexport) void __cdecl HoldMouse( int x, int y, TClickType button );
extern "C" _declspec(dllexport) void __cdecl ReleaseMouse( int x, int y, TClickType button );
extern "C" _declspec(dllexport) bool __cdecl IsMouseButtonHeld( TClickType button );
extern "C" _declspec(dllexport) void __cdecl ClickMouse( TClickType button );
 //Mouse movements implementation

extern "C" _declspec(dllexport) void __cdecl WindMouse( float xs, float ys, float xe, float ye, float gravity, float wind, float minWait, float maxWait, float maxStep, float targetArea );
extern "C" _declspec(dllexport) void __cdecl MMouse( int x, int y, int rx, int ry );
extern "C" _declspec(dllexport) void __cdecl Mouse( int mousex, int mousey, int ranx, int rany, TClickType button );
extern "C" _declspec(dllexport) void __cdecl SleepAndMoveMouse( int atime );
extern "C" _declspec(dllexport) void __cdecl DragMouse( int StartX, int StartY, int SRandX, int SRandY, int EndX, int EndY, int ERandX, int ERandY );

 //Human-like mouse movements

extern "C" _declspec(dllexport) void __cdecl BrakeWindMouse( float xs, float ys, float xe, float ye, float gravity, float wind, float minWait, float maxWait, float targetArea );
extern "C" _declspec(dllexport) void __cdecl BrakeMMouse( int eX, int eY, int ranx, int rany );
extern "C" _declspec(dllexport) void __cdecl ShiftWindMouse( float xs, float ys, float xe, float ye, float gravity, float wind, float minWait, float maxWait, float maxStep, float targetArea );
extern "C" _declspec(dllexport) void __cdecl MissMouse( int eX, int eY, int ranx, int rany );
extern "C" _declspec(dllexport) void __cdecl HumanMMouse( int eX, int eY, int ranX, int ranY);
extern int MouseSpeed;

#endif // HUMANMOUSE_H_INCLUDED
