#include <Windows.h>
//#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "HumanMouse.h"

int MouseSpeed = 10;

int  RandomRange( const int AFrom, const int ATo )
{
  int result = 0;
  int a = 0;
  if ( AFrom <= ATo )
    a = AFrom;
  else
    a = ATo;
  result = a + (rand() % abs(ATo - AFrom ));
  return result;
}


float  Min( float a, float b )
{
  float result = 0.0;
  if ( a < b )
    result = a;
  else
    result = b;
  return result;
}

float Random()
{
    return rand() / (RAND_MAX + 1.);
}

extern "C" _declspec(dllexport) void __cdecl SetMouseSpeed(int Speed)
{
   if (Speed>=0||Speed<=20 )
   {
       MouseSpeed = Speed;
   } else {MouseSpeed = 10;}
}
extern "C" _declspec(dllexport) int __cdecl GetMouseSpeed()
{
    return MouseSpeed;
}

extern "C" _declspec(dllexport) void __cdecl GetMousePosition( int& x, int& y )
{
  POINT MousePos;
  GetCursorPos(&MousePos );
  x = MousePos.x;
  y = MousePos.y;
}

extern "C" _declspec(dllexport) void __cdecl MoveMouse( int x, int y )
{
  SetCursorPos( x, y );
}

int rnd(double x)
{
    return static_cast<int>(floor(x+0.5));
}


extern "C" _declspec(dllexport) void __cdecl HoldMouse( int x, int y, TClickType button )
{
  TInput Input;
  Input.Itype = INPUT_MOUSE;
  memset(&Input, sizeof( Input ), 0 );
  Input.mi.dx = x;
  Input.mi.dy = y;
  switch ( button )
  {
    case mouse_Left:
      Input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN;
    break;
    case mouse_Middle:
      Input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MIDDLEDOWN;
    break;
    case mouse_Right:
      Input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_RIGHTDOWN;
    break;
  }
  SendInput( 1, Input, sizeof( Input ) );
}


extern "C" _declspec(dllexport) void __cdecl  ReleaseMouse( int x, int y, TClickType button )
{
  TInput Input;
  RECT Rect;
  Input.Itype = INPUT_MOUSE;
  memset(&Input, sizeof( Input ), 0 );
  Input.mi.dx = x + Rect.left;
  Input.mi.dy = y + Rect.top;
  switch ( button )
  {
    case mouse_Left:
      Input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP;
    break;
    case mouse_Middle:
      Input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MIDDLEUP;
    break;
    case mouse_Right:
      Input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_RIGHTUP;
    break;
  }
  SendInput( 1, Input, sizeof( Input ) );
}


extern "C" _declspec(dllexport) bool __cdecl IsMouseButtonHeld( TClickType button )
{
  bool result = false;
  switch ( button )
  {
    case mouse_Left:
      result = ( GetAsyncKeyState( VK_LBUTTON ) != 0 );
    break;
    case mouse_Middle:
      result = ( GetAsyncKeyState( VK_MBUTTON ) != 0 );
    break;
    case mouse_Right:
      result = ( GetAsyncKeyState( VK_RBUTTON ) != 0 );
    break;
  }
  return result;
}


extern "C" _declspec(dllexport) void __cdecl ClickMouse( TClickType button )
{
  int a = 0, b = 0, c = 0;
   /* Eventually, should be made to just use Integers */
  GetMousePosition( b, c );
  HoldMouse( b, c, button );
  do
  {
    Sleep( 20 + rand()% 30);
    a = a + 1;
  }
  while ( ! ( a > 4 ) );
  GetMousePosition( b, c );
  ReleaseMouse( b, c, button );
  Sleep( 50 + rand() % 50);
}

extern "C" _declspec(dllexport) void __cdecl DragMouse(int x, int y, TClickType button)
{
  GetMousePosition(x, y);
  HoldMouse(x, y, button);
  Sleep( 50 + rand()% 50);
  Mouse(x,y,0,0,button);
  GetMousePosition(x, y);
  Sleep( 50 + rand()% 50);
  ReleaseMouse(x, y, button);
}


extern "C" _declspec(dllexport) void __cdecl WindMouse( float xs, float ys, float xe, float ye, float gravity, float wind, float minWait, float maxWait, float maxStep, float targetArea )
{
  float veloX = 0.0, veloY = 0.0, windX = 0.0, windY = 0.0, veloMag = 0.0, dist = 0.0, randomDist = 0.0, step = 0.0;
  int lastX = 0, lastY = 0;
  float sqrt2 = 0.0, sqrt3 = 0.0, sqrt5 = 0.0;
  veloX = 0;
  veloY = 0;
  windX = 0;
  windY = 0;
  srand (static_cast <unsigned> (time(0)));
  try
  {
    sqrt2 = sqrt( 2 );
    sqrt3 = sqrt( 3 );
    sqrt5 = sqrt( 5 );
    while ( hypot( xs - xe, ys - ye ) > 1 )
    {
      dist = hypot( xs - xe, ys - ye );
      wind = Min( wind, dist );
      if ( dist >= targetArea )
      {
           windX = windX / sqrt3 + (Random() * (wind * 2.0 + 1.0) - wind) / sqrt5;
           windY = windY / sqrt3 + (Random() * (wind * 2.0 + 1.0) - wind) / sqrt5;
      }
      else
      {
        windX =  windX  / sqrt2;
        windY =  windY  / sqrt2;
        if ( maxStep < 3 )
        {
          maxStep = Random() * 3 + 3.0;
        }
        else
        {
          maxStep =  maxStep  / sqrt5;
        }
      }
      veloX = veloX + windX;
      veloY = veloY + windY;
      veloX = veloX +  gravity  * ( xe - xs ) / dist;
      veloY = veloY +  gravity  * ( ye - ys ) / dist;
      if ( hypot( veloX, veloY ) > maxStep )
      {
        randomDist =  maxStep / 2.0 + Random() * maxStep / 2.0;
        veloMag = sqrt( veloX * veloX + veloY * veloY );
        veloX = (  veloX  / veloMag ) * randomDist;
        veloY = (  veloY  / veloMag ) * randomDist;
      }
      lastX = rnd( xs );
      lastY = rnd( ys );
      xs = xs + veloX;
      ys = ys + veloY;
      if ( ( lastX != rnd( xs ) ) || ( lastY != rnd( ys ) ) )
        MoveMouse( rnd( xs ), rnd( ys ) );
      step = hypot( xs - lastX, ys - lastY );
      Sleep( rnd( ( maxWait - minWait ) * (  step / maxStep ) + minWait ) );
//      lastDist = dist;
    }
    if ( ( rnd( xe ) != rnd( xs ) ) || ( rnd( ye ) != rnd( ys ) ) )
      MoveMouse( rnd( xe ), rnd( ye ) );
  }
  catch(...)
  {
  }
}


extern "C" _declspec(dllexport) void __cdecl MMouse( int x, int y, int rx, int ry )
{
  int cx = 0, cy = 0;
  float randSpeed = 0.0;
  srand(time(NULL));
  GetMousePosition( cx, cy );
  randSpeed = (  rand()% MouseSpeed  / 2.0 + MouseSpeed ) / 10.0;
  if ( randSpeed<=0.0 )
    randSpeed = 0.1;
  x = x + rand()% rx;
  y = y + rand()% ry;
  WindMouse( cx, cy, x, y, 9.0, 3.0, 10.0 / randSpeed, 15.0 / randSpeed, 10.0 * randSpeed, 10.0 * randSpeed );
}


extern "C" _declspec(dllexport) void __cdecl Mouse( int mousex, int mousey, int ranx, int rany, TClickType button )
{
  MMouse( mousex, mousey, ranx, rany );
  Sleep( 60 + rand()% 30);
  ClickMouse( button );
  Sleep( 50 + rand()% 50 );
}


extern "C" _declspec(dllexport) void __cdecl SleepAndMoveMouse( int atime )
{
  bool Moving = false;
  int mx = 0, my = 0;
  float x = 0.0, y = 0.0, xv = 0.0, yv = 0.0;
  float gx = 0.0, gy = 0.0;
  srand(time(NULL));
  GetMousePosition( mx, my );
  x = mx;
  y = my;
  if ( rand()%( 2 ) == 0 )
    Moving = false;
  else
    Moving = true;
  gx = 130 + rand()% 500;
  gy = 130 + rand()% 300;
  DWORD T = GetTickCount();
  do
  {
    Sleep( 10 );
    if ( Moving )
    {
      if ( gx > x )
        xv = xv + 0.1;
      else
        xv = xv - 0.1;
      if ( gy > y )
        yv = yv + 0.1;
      else
        yv = yv - 0.1;
      x = x + xv;
      y = y + yv;
      MoveMouse( rnd( x ), rnd( y ) );
    }
    if ( rand()% 100  == 0 )
      Moving = ! Moving;
    if ( rand()% 30  == 0 )
    {
      gx = 130 + rand()% 500 ;
      gy = 130 + rand()% 300 ;
    }
  }
  while ( ! ( abs( int(GetTickCount() - T) ) >= atime ) );
}


extern "C" _declspec(dllexport) void  __cdecl HumanDragMouse( int StartX, int StartY, int SRandX, int SRandY, int EndX, int EndY, int ERandX, int ERandY )
{
  MMouse( StartX, StartY, SRandX, SRandY );
  Sleep( 150 + rand()% 20  );
  GetMousePosition( StartX, StartY );
  HoldMouse( StartX, StartY, mouse_Left );
  Sleep( 250 + rand()% 320  );
  MMouse( EndX, EndY, ERandX, ERandY );
  Sleep( 250 + rand()% 120  );
  GetMousePosition( EndX, EndY );
  ReleaseMouse( EndX, EndY, mouse_Left );
}


int Distance( int x1, int y1, int x2, int y2 )
{
  return rnd( sqrt( pow( x2 - x1,2 ) + pow( y2 - y1,2 ) ) );
}

extern "C" _declspec(dllexport) void __cdecl BrakeWindMouse( float xs, float ys, float xe, float ye, float gravity, float wind, float minWait, float maxWait, float targetArea )
{
  float veloX = 0.0, veloY = 0.0, windX = 0.0, windY = 0.0, veloMag = 0.0, dist = 0.0, randomDist = 0.0;
  int lastX = 0, lastY = 0, MSP = 0, W = 0, maxStep = 0, D = 0, TDist = 0;
  float sqrt2 = 0.0, sqrt3 = 0.0, sqrt5 = 0.0, PDist = 0.0;
  veloX = 0;
  veloY = 0;
  windX = 0;
  windY = 0;
  MSP = MouseSpeed;
  sqrt2 = sqrt( 2 );
  sqrt3 = sqrt( 3 );
  sqrt5 = sqrt( 5 );
  srand(time(NULL));
  TDist = Distance( rnd( xs ), rnd( ys ), rnd( xe ), rnd( ye ) );
  if ( TDist < 1 )
    TDist = 1;
  do
  {
    dist = hypot( xs - xe, ys - ye );
    wind = Min( wind, dist );
    if ( dist < 1 )
      dist = 1;
    PDist = ( dist / TDist );
    if ( PDist < 0.01 )
      PDist = 0.01;

     /*
       These constants seem smooth to me, but
       feel free to modify these settings however
       you wish.
     */
    if ( PDist >= 0.15 )                    //15% (or higher) dist to destination
    {
      D = rnd( rnd( ( rnd( dist ) * 0.3 ) )  / 5 );
      if ( D < 20 )
        D = 20;
         //D := RandomRange(15, 25);                        {Original}
    }
    else
      if ( PDist < 0.15 )
      {
        if ( ( PDist <= 0.15 ) && ( PDist >= 0.10 ) )         //10%-15%
          D = RandomRange( 8, 13 );
        else
          if ( PDist < 0.10 )                           //< 10%
            D = RandomRange( 4, 7 );
      }
    if ( D <= rnd( dist ) )
      maxStep = D;
    else
      maxStep = rnd( dist );
    if ( dist >= targetArea )
    {
      windX =  windX  / sqrt3 +  ( rand()% rnd( wind ) * 2 + 1  - wind )  / sqrt5;
      windY = windY  / sqrt3 +  ( rand()% rnd( wind ) * 2 + 1  - wind )  / sqrt5;
    }
    else
    {
      windX =  windX  / sqrt2;
      windY =  windY  / sqrt2;
    }
    veloX = veloX + windX;
    veloY = veloY + windY;
    veloX = veloX +  gravity  * ( xe - xs ) / dist;
    veloY = veloY +  gravity  * ( ye - ys ) / dist;
    if ( hypot( veloX, veloY ) > maxStep )
    {
      randomDist =  maxStep  / 2.0 + rand()% rnd( maxStep ) / 2 ;
      veloMag = sqrt( veloX * veloX + veloY * veloY );
      veloX = (  veloX  / veloMag ) * randomDist;
      veloY = (  veloY  / veloMag ) * randomDist;
    }
    lastX = rnd( xs );
    lastY = rnd( ys );
    xs = xs + veloX;
    ys = ys + veloY;
    if ( ( lastX != rnd( xs ) ) || ( lastY != rnd( ys ) ) )
      MoveMouse( rnd( xs ), rnd( ys ) );
    W = ( rand()% rnd(  100 / MSP ) )  * 6;
    if ( W < 5 )
      W = 5;
    W = rnd( W * 1.2 );
    Sleep( W );
//    lastDist = dist;
  }
  while ( ! ( hypot( xs - xe, ys - ye ) < 1 ) );
  if ( ( rnd( xe ) != rnd( xs ) ) || ( rnd( ye ) != rnd( ys ) ) )
    MoveMouse( rnd( xe ), rnd( ye ) );
  MouseSpeed = MSP;
}


extern "C" _declspec(dllexport) void __cdecl BrakeMMouse( int eX, int eY, int ranx, int rany )
{
  float randSpeed = 0.0;
  int x = 0, y = 0, MS = 0;
  srand(time(NULL));
  MS = MouseSpeed;
  randSpeed = ( double( rand()% MouseSpeed  ) / 2.0 + MouseSpeed ) / 10.0;
  GetMousePosition( x, y );
  BrakeWindMouse( x, y, eX, eY, 9, 5, 10.0 / randSpeed, 15.0 / randSpeed, 10.0 * randSpeed );
  MouseSpeed = MS;
}

extern "C" _declspec(dllexport) void __cdecl ShiftWindMouse( float xs, float ys, float xe, float ye, float gravity, float wind, float minWait, float maxWait, float maxStep, float targetArea )
{
  float veloX = 0.0, veloY = 0.0, windX = 0.0, windY = 0.0, veloMag = 0.0, dist = 0.0, randomDist = 0.0, step = 0.0;
  int lastX = 0, lastY = 0, MS = 0;
  float sqrt2 = 0.0, sqrt3 = 0.0, sqrt5 = 0.0;
  veloX = 0;
  veloY = 0;
  windX = 0;
  windY = 0;
  srand(time(NULL));
  MS = MouseSpeed;
  sqrt2 = sqrt( 2 );
  sqrt3 = sqrt( 3 );
  sqrt5 = sqrt( 5 );
  while ( hypot( xs - xe, ys - ye ) > 1 )
  {
    dist = hypot( xs - xe, ys - ye );
    wind = Min( wind, dist );
    if ( dist >= targetArea )
    {
      windX =  windX  / sqrt3 +  ( rand()% rnd( wind ) * 2 + 1  - wind )  / sqrt5;
      windY =  windY  / sqrt3 +  ( rand()% rnd( wind ) * 2 + 1  - wind )  / sqrt5;
    }
    else
    {
      windX =  windX  / sqrt2;
      windY =  windY  / sqrt2;
      if ( maxStep < 3 )
      {
        maxStep = rand()% 3  + 3.0;
      }
      else
      {
        maxStep =  maxStep  / sqrt5;
      }
    }
    veloX = veloX + windX;
    veloY = veloY + windY;
    veloX = veloX +  gravity  * ( xe - xs ) / dist;
    veloY = veloY +  gravity  * ( ye - ys ) / dist;
    if ( hypot( veloX, veloY ) > maxStep )
    {
      randomDist =  maxStep  / 2.0 + rand()% rnd( maxStep ) / 2 ;
      veloMag = sqrt( veloX * veloX + veloY * veloY );
      veloX = (  veloX  / veloMag ) * randomDist;
      veloY = (  veloY  / veloMag ) * randomDist;
    }
    lastX = rnd( xs );
    lastY = rnd( ys );
    xs = xs + veloX;
    ys = ys + veloY;
    switch ( rand()% 2  )
    {
      case 1:
        MouseSpeed = ( MS + ( RandomRange( 2, 5 ) ) );
      break;
      case 2:
        MouseSpeed = ( MS - ( RandomRange( 2, 5 ) ) );
      break;
    }
    if ( MouseSpeed < 4 )
      MouseSpeed = 4;
    if ( ( lastX != rnd( xs ) ) || ( lastY != rnd( ys ) ) )
      MoveMouse( rnd( xs ), rnd( ys ) );
    step = hypot( xs - lastX, ys - lastY );
    Sleep( rnd( ( maxWait - minWait ) * (  step  / maxStep ) + minWait ) );
//    lastDist = dist;
    MouseSpeed = MS;
  }
  switch ( rand()% 2  )
  {
    case 1:
      MouseSpeed = ( MS + ( RandomRange( 2, 5 ) ) );
    break;
    case 2:
      MouseSpeed = ( MS - ( RandomRange( 2, 5 ) ) );
    break;
  }
  if ( MouseSpeed < 4 )
    MouseSpeed = 4;
  if ( ( rnd( xe ) != rnd( xs ) ) || ( rnd( ye ) != rnd( ys ) ) )
    MoveMouse( rnd( xe ), rnd( ye ) );
  MouseSpeed = MS;
}

extern "C" _declspec(dllexport) void __cdecl MissMouse( int eX, int eY, int ranx, int rany )
{
  float randSpeed = 0.0;
  int x = 0, y = 0, x2 = 0, y2 = 0, a = 0, dist = 0, MP = 0;
  a = MouseSpeed;
  GetMousePosition( x, y );
  dist = Distance( x, y, eX, eY );
  MP = rnd(  dist  / 150 );
  if ( MP < 0 )
    MP = 1;
  randSpeed = (  rand()% MouseSpeed / 2.0 + MouseSpeed ) / 10.0;
  x2 = RandomRange( eX - ( a * MP ), eX + ( a * MP ) );
  y2 = RandomRange( eY - ( a * MP ), eY + ( a * MP ) );
  ShiftWindMouse( x, y, x2, y2, 11, 8, 10.0 / randSpeed, 12.0 / randSpeed, 10.0 * randSpeed, 10.0 * randSpeed );
  GetMousePosition( x, y );
  MMouse( eX, eY, ranx, rany );
  MouseSpeed = a;
}


extern "C" _declspec(dllexport) void __cdecl FastClick( TClickType button )
{
  int x = 0, y = 0;
  GetMousePosition( x, y );
  HoldMouse( x, y, button );
  Sleep( RandomRange( 60, 150 ) );
  GetMousePosition( x, y );
  ReleaseMouse( x, y, button );
}

extern "C" _declspec(dllexport) void __cdecl HumanMMouse( int eX, int eY)
{
    int A = MouseSpeed;
    int x = 0; int y = 0;
    GetMousePosition(x,y);
    int Dist = Distance(x,y,eX,eY);
    int MP = rnd(Dist/100);
     if (MP < 0)
       MP =1;
    float randSpeed = ((rand()%MouseSpeed) / 2.0 + MouseSpeed) / 10.0;
    WindMouse(x, y, RandomRange(eX-(A*MP), eX+(A*MP)), RandomRange(eY-(A*MP), eY+(A*MP)),
            30, 55, 10.0 / randSpeed, 12.0 / randSpeed, 10.0 * randSpeed, 10.0 * randSpeed);
    GetMousePosition(x, y);
    WindMouse(x, y, eX, eY, 30, 55, 10.0 / randSpeed, 12.0 / randSpeed, 10.0 * randSpeed, 10.0 * randSpeed);

    MouseSpeed = A;
}

