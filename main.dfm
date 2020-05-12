object Glavna: TGlavna
  Left = 0
  Top = 0
  Caption = 'Aplikacija'
  ClientHeight = 620
  ClientWidth = 1115
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Slika: TImage
    Left = 8
    Top = 8
    Width = 961
    Height = 565
    OnMouseDown = SlikaMouseDown
    OnMouseMove = SlikaMouseMove
  end
  object LabelBrojTacaka: TLabel
    Left = 982
    Top = 8
    Width = 58
    Height = 13
    Caption = 'Broj tacaka:'
    OnMouseMove = SlikaMouseMove
  end
  object LabelKoordinate: TLabel
    Left = 800
    Top = 579
    Width = 52
    Height = 13
    Caption = 'Koordinate'
  end
  object TrenutnaAkcija: TLabel
    Left = 982
    Top = 96
    Width = 78
    Height = 13
    Caption = 'Trenutna akcija:'
  end
  object SlikaVidokruga: TImage
    Left = 8
    Top = 8
    Width = 961
    Height = 565
    Transparent = True
    Visible = False
    OnMouseMove = SlikaVidokrugMouseMove
  end
  object simulacijaLabela: TLabel
    Left = 984
    Top = 200
    Width = 80
    Height = 13
    Caption = 'Simulacija akcije:'
  end
  object brzinaKameraLabel: TLabel
    Left = 985
    Top = 344
    Width = 96
    Height = 13
    Caption = 'Brzina rotacije (ms):'
  end
  object ugaoRotacijeStepeni: TLabel
    Left = 985
    Top = 400
    Width = 114
    Height = 13
    Caption = 'Ugao rotacije (stepeni):'
  end
  object pocetakVidokrugaLabel: TLabel
    Left = 985
    Top = 461
    Width = 108
    Height = 13
    Caption = 'Pocetak vidokruga ('#176'):'
  end
  object krajVidokrugaLabel: TLabel
    Left = 985
    Top = 512
    Width = 89
    Height = 13
    Caption = 'Kraj vidokruga ('#176'):'
  end
  object EditBrojTacaka: TEdit
    Left = 982
    Top = 27
    Width = 60
    Height = 21
    TabOrder = 0
    Text = '6'
  end
  object GenerisanjeTacaka: TButton
    Left = 982
    Top = 54
    Width = 75
    Height = 25
    Caption = 'Generisi tacke'
    TabOrder = 1
    OnClick = GenerisanjeTacakaClick
  end
  object EditKoordinate: TEdit
    Left = 858
    Top = 579
    Width = 73
    Height = 21
    TabOrder = 2
    Text = '(0,0)'
  end
  object DugmeProstiMnogougao: TButton
    Left = 8
    Top = 589
    Width = 97
    Height = 23
    Caption = 'Prosti mnogougao'
    TabOrder = 3
    OnClick = DugmeProstiMnogougaoClick
  end
  object DodavanjeTacaka: TRadioButton
    Left = 982
    Top = 115
    Width = 113
    Height = 17
    Caption = 'Dodavanje tacaka'
    TabOrder = 4
    OnClick = DodavanjeTacakaClick
  end
  object CrtanjeMnogougla: TRadioButton
    Left = 982
    Top = 138
    Width = 113
    Height = 17
    Caption = 'Crtanje mnogougla'
    TabOrder = 5
    OnClick = CrtanjeMnogouglaClick
  end
  object Clear: TButton
    Left = 699
    Top = 579
    Width = 95
    Height = 25
    Caption = 'Clear'
    TabOrder = 6
    OnClick = ClearClick
  end
  object ZavrsiMnogougao: TButton
    Left = 582
    Top = 579
    Width = 95
    Height = 25
    Caption = 'Zavrsi mnogougao'
    TabOrder = 7
    OnClick = ZavrsiMnogougaoClick
  end
  object dodavanjeKamere: TRadioButton
    Left = 982
    Top = 161
    Width = 113
    Height = 17
    Caption = 'Dodavanje kamere'
    TabOrder = 8
    OnClick = dodavanjeKamereClick
  end
  object stanjeSimulacije: TCheckBox
    Left = 984
    Top = 219
    Width = 97
    Height = 17
    Caption = 'Stanje simulacije'
    TabOrder = 9
    OnClick = stanjeSimulacijeClick
  end
  object resetSimulaciju: TButton
    Left = 985
    Top = 304
    Width = 88
    Height = 25
    Caption = 'Reset simulaciju'
    TabOrder = 10
    OnClick = resetSimulacijuClick
  end
  object startSimulaciju: TButton
    Left = 984
    Top = 242
    Width = 89
    Height = 25
    Caption = 'Start simulaciju'
    TabOrder = 11
    OnClick = startSimulacijuClick
  end
  object stopSimulaciju: TButton
    Left = 984
    Top = 273
    Width = 88
    Height = 25
    Caption = 'Stop simulaciju'
    TabOrder = 12
    OnClick = stopSimulacijuClick
  end
  object brzinaKamera: TEdit
    Left = 985
    Top = 363
    Width = 67
    Height = 21
    TabOrder = 13
    Text = '50'
    OnChange = brzinaKameraChange
  end
  object ugaoRotacije: TEdit
    Left = 985
    Top = 419
    Width = 67
    Height = 21
    TabOrder = 14
    Text = '1'
    OnChange = ugaoRotacijeChange
  end
  object pocetakVidokrugaUgao: TEdit
    Left = 985
    Top = 480
    Width = 88
    Height = 21
    TabOrder = 15
  end
  object krajVidokrugaUgao: TEdit
    Left = 985
    Top = 539
    Width = 87
    Height = 21
    TabOrder = 16
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 496
    Top = 584
  end
end
