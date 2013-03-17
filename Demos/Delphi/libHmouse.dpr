program libHmouse;

uses
  Forms,
  main in 'main.pas' {Form1},
  HumanMouse in 'HumanMouse.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.MainFormOnTaskbar := True;
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
