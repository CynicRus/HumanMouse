object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'libHmouse Demo'
  ClientHeight = 62
  ClientWidth = 604
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 16
    Top = 41
    Width = 3
    Height = 13
  end
  object Button1: TButton
    Left = 16
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Mouse'
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 97
    Top = 8
    Width = 75
    Height = 25
    Caption = 'MMouse'
    TabOrder = 1
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 178
    Top = 8
    Width = 75
    Height = 25
    Caption = 'MissMouse'
    TabOrder = 2
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 259
    Top = 8
    Width = 75
    Height = 25
    Caption = 'BrakeMMouse'
    TabOrder = 3
    OnClick = Button4Click
  end
  object Button5: TButton
    Left = 340
    Top = 8
    Width = 127
    Height = 25
    Caption = 'SleepAndMoveMouse'
    TabOrder = 4
    OnClick = Button5Click
  end
  object Button6: TButton
    Left = 473
    Top = 8
    Width = 123
    Height = 25
    Caption = 'HumanMMouse'
    TabOrder = 5
    OnClick = Button6Click
  end
end