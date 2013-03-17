unit HumanMouse;

interface

 type
  TClickType = (mouse_Left=1, mouse_Right=0, mouse_Middle=2);
 function GetMouseSpeed():integer; cdecl;  external 'HumanMouse.dll';
 procedure SetMouseSpeed(speed:integer); cdecl;  external 'HumanMouse.dll';
  //Internal functions
 procedure GetMousePosition(out x,y: integer);cdecl;  external 'HumanMouse.dll';
 procedure MoveMouse(x,y: integer);cdecl;  external 'HumanMouse.dll';
 procedure HoldMouse(x,y: integer; button: TClickType);cdecl;  external 'HumanMouse.dll';
 procedure ReleaseMouse(x,y: integer; button: TClickType);cdecl;  external 'HumanMouse.dll';
 function  IsMouseButtonHeld( button : TClickType) : boolean;cdecl;  external 'HumanMouse.dll';
 procedure ClickMouse(button: TClickType);cdecl;  external 'HumanMouse.dll';
 //Mouse movements implementation
 procedure WindMouse(xs, ys, xe, ye, gravity, wind, minWait, maxWait, maxStep, targetArea: extended); cdecl;  external 'HumanMouse.dll';
 procedure MMouse(x, y, rx, ry: integer); cdecl;  external 'HumanMouse.dll';
 procedure Mouse(mousex, mousey, ranx, rany: Integer; button: TClickType);cdecl;  external 'HumanMouse.dll';
 procedure SleepAndMoveMouse(Time: Integer);cdecl;  external 'HumanMouse.dll';
 procedure DragMouse(StartX, StartY, SRandX, SRandY, EndX, EndY, ERandX, ERandY: Integer);cdecl;  external 'HumanMouse.dll';

 //Human-like mouse movements
 procedure BrakeWindMouse(xs, ys, xe, ye, gravity, wind, minWait, maxWait, targetArea: extended);cdecl;  external 'HumanMouse.dll';
 procedure BrakeMMouse(eX, eY, ranX, ranY: Integer);cdecl;  external 'HumanMouse.dll';
 procedure ShiftWindMouse(xs, ys, xe, ye, gravity, wind, minWait, maxWait, maxStep, targetArea: extended);cdecl;  external 'HumanMouse.dll';
 procedure MissMouse(eX, eY, ranX, ranY: Integer);cdecl;  external 'HumanMouse.dll';
 Procedure HumanMMouse(eX, eY, ranX, ranY: Integer);cdecl;  external 'HumanMouse.dll';


implementation

end.
