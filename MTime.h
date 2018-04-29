/*
* MTime.h (For Mount) Written by Igor Ovchinnikov 23/04/2018
*/

struct sDateTime {int SS; int MM; int HH; int DD; int MH; int YY; unsigned long MS;} sDT;

bool SetDate(String STR)
{
  bool SetDate=false;
  String SubSTR="";
  if(STR.length()==6)
  {
   SubSTR=STR.substring(0,2);
   sDT.YY=SubSTR.toInt();
   SubSTR=STR.substring(2,4);
   sDT.MH=SubSTR.toInt();
   SubSTR=STR.substring(4,6);
   sDT.DD=SubSTR.toInt();
   SetDate=true;
  }
 return SetDate;
}

bool SetTime(String STR)
{
  bool SetTime=false;
  String SubSTR="";
  if(STR.length()==6)
  {
   SubSTR=STR.substring(0,2);
   sDT.HH=SubSTR.toInt();
   SubSTR=STR.substring(2,4);
   sDT.MM=SubSTR.toInt();
   SubSTR=STR.substring(4,6);
   sDT.SS=SubSTR.toInt();
   sDT.MS=millis();
   SetTime=true;
  }
 return SetTime;
}

void AskClock(void) // Заполняет структуру sDT данными о текущем времени
{
  unsigned long ulTick;
  ulTick=millis()-sDT.MS;
  if(sDT.DD==0) sDT.DD=1;
  if(sDT.MH==0) sDT.MH=1;
  if(ulTick>=1000)
   {
    sDT.MS+=ulTick; sDT.SS+=ulTick/1000;
    while (sDT.SS>=60) {sDT.MM+=1; sDT.SS-=60;}
    while (sDT.MM>=60) {sDT.HH+=1; sDT.MM-=60;}
    while (sDT.HH>=24) {sDT.DD+=1; sDT.HH-=24;}
    if(sDT.DD>28&&sDT.MH==2&&(sDT.YY%4!=0)) {sDT.MH=3; sDT.DD-=28;}
    if(sDT.DD>29&&sDT.MH==2&&(sDT.YY%4==0)) {sDT.MH=3; sDT.DD-=29;}
    if(sDT.DD>30&&(sDT.MH==4||sDT.MH==6||sDT.MH==9||sDT.MH==11)) {sDT.MH+=1; sDT.DD-=30;}
    if(sDT.DD>31&&(sDT.MH==1||sDT.MH==3||sDT.MH==5||sDT.MH==7||sDT.MH==8||sDT.MH==10||sDT.MH==12)) {sDT.MH+=1; sDT.DD-=31;}
    if(sDT.MH>12) {sDT.MH=1; sDT.YY+=1;}
   }
}

String GetTime(void)
{
  String GetTime="";
  AskClock();
  if(sDT.HH<10) GetTime+="0";
  GetTime+=String(sDT.HH);
  if(sDT.MM<10) GetTime+="0";
  GetTime+=String(sDT.MM);
  if(sDT.SS<10) GetTime+="0";
  GetTime+=String(sDT.SS);
  return GetTime;
}

String GetDate(void)
{
  String GetDate="";
  AskClock();
  if(sDT.YY<10) GetDate+="0";
  GetDate+=String(sDT.YY);
  if(sDT.MH<10) GetDate+="0";
  GetDate+=String(sDT.MH);
  if(sDT.DD<10) GetDate+="0";
  GetDate+=String(sDT.DD);
  return GetDate;
}

