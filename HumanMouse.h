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
//установить скорость мыши
extern "C" _declspec(dllexport) void __cdecl SetMouseSpeed(int Speed);
//получить текущую
extern "C" _declspec(dllexport) int __cdecl GetMouseSpeed();

//текущие координаты мыши
extern "C" _declspec(dllexport) void __cdecl GetMousePosition( int& x, int& y );
//простое движение мышь.
extern "C" _declspec(dllexport) void __cdecl MoveMouse( int x, int y );
//нажатие и удержание кнопки мыши
extern "C" _declspec(dllexport) void __cdecl HoldMouse( int x, int y, TClickType button );
//отпустить нажатую клавишу
extern "C" _declspec(dllexport) void __cdecl ReleaseMouse( int x, int y, TClickType button );
//определяем, нажата ли клавиша мыши
extern "C" _declspec(dllexport) bool __cdecl IsMouseButtonHeld( TClickType button );
//стандартный клик
extern "C" _declspec(dllexport) void __cdecl ClickMouse( TClickType button );
//перетащить мышью
extern "C" _declspec(dllexport) void __cdecl DragMouse(int x, int y, TClickType button);

//реализация простых действий с мышью
//
extern "C" _declspec(dllexport) void __cdecl WindMouse( float xs, float ys, float xe, float ye, float gravity, float wind, float minWait, float maxWait, float maxStep, float targetArea );
extern "C" _declspec(dllexport) void __cdecl MMouse( int x, int y, int rx, int ry );
extern "C" _declspec(dllexport) void __cdecl Mouse( int mousex, int mousey, int ranx, int rany, TClickType button );
extern "C" _declspec(dllexport) void __cdecl SleepAndMoveMouse( int atime );

//Реалистичные движения мышью
extern "C" _declspec(dllexport) void __cdecl HumanDragMouse( int StartX, int StartY, int SRandX, int SRandY, int EndX, int EndY, int ERandX, int ERandY );
extern "C" _declspec(dllexport) void __cdecl BrakeWindMouse( float xs, float ys, float xe, float ye, float gravity, float wind, float minWait, float maxWait, float targetArea );
extern "C" _declspec(dllexport) void __cdecl BrakeMMouse( int eX, int eY, int ranx, int rany );
extern "C" _declspec(dllexport) void __cdecl ShiftWindMouse( float xs, float ys, float xe, float ye, float gravity, float wind, float minWait, float maxWait, float maxStep, float targetArea );
extern "C" _declspec(dllexport) void __cdecl MissMouse( int eX, int eY, int ranx, int rany );
extern "C" _declspec(dllexport) void __cdecl HumanMMouse( int eX, int eY);

extern int MouseSpeed;

#endif // HUMANMOUSE_H_INCLUDED
