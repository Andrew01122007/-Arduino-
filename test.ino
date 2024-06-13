#define C0 16.352
#define C1 32.703
#define C2 65.406
#define C3 130.81
#define C4 261.63
#define C5 523.25
#define C6 1046.5
#define C7 2093.0
#define C8 4186.0
#define C9 8372.0
#define Csharp0 17.324
#define Csharp1 34.648
#define Csharp2 69.296
#define Csharp3 138.59
#define Csharp4 277.18
#define Csharp5 554.37
#define Csharp6 1108.7
#define Csharp7 2217.5
#define Csharp8 4434.9
#define Csharp9 8869.8
#define D0 18.354
#define D1 36.708
#define D2 73.416
#define D3 146.83
#define D4 293.66
#define D5 587.33
#define D6 1174.7
#define D7 2349.3
#define D8 4698.6
#define D9 9397.3
#define Dsharp0 19.445
#define Dsharp1 38.891
#define Dsharp2 77.782
#define Dsharp3 155.56
#define Dsharp4 311.13
#define Dsharp5 622.25
#define Dsharp6 1244.5
#define Dsharp7 2489.0
#define Dsharp8 4978.0
#define Dsharp9 9956.1
#define E0 20.602
#define E1 41.203
#define E2 82.407
#define E3 164.81
#define E4 329.63
#define E5 659.26
#define E6 1318.5
#define E7 2637.0
#define E8 5274.0
#define E9 10548
#define F0 21.827
#define F1 43.654
#define F2 87.307
#define F3 174.61
#define F4 349.23
#define F5 698.46
#define F6 1396.9
#define F7 2793.8
#define F8 5587.7
#define F9 11175
#define Fsharp0 23.125
#define Fsharp1 46.249
#define Fsharp2 92.499
#define Fsharp3 185.00
#define Fsharp4 369.99
#define Fsharp5 739.99
#define Fsharp6 1480.0
#define Fsharp7 2960.0
#define Fsharp8 5919.9
#define Fsharp9 11840
#define G0 24.500
#define G1 48.999
#define G2 97.999
#define G3 196.00
#define G4 392.00
#define G5 783.99
#define G6 1568.0
#define G7 3136.0
#define G8 6271.9
#define G9 12544
#define Gsharp0 25.957
#define Gsharp1 51.913
#define Gsharp2 103.83
#define Gsharp3 207.65
#define Gsharp4 415.30
#define Gsharp5 830.61
#define Gsharp6 1661.2
#define Gsharp7 3322.4
#define Gsharp8 6644.9
#define Gsharp9 13290
#define A0 27.500
#define A1 55.000
#define A2 110.00
#define A3 220.00
#define A4 440.00
#define A5 880.00
#define A6 1760.0
#define A7 3520.0
#define A8 7040.0
#define A9 14080
#define Asharp0 29.135
#define Asharp1 58.270
#define Asharp2 116.54
#define Asharp3 233.08
#define Asharp4 466.16
#define Asharp5 932.33
#define Asharp6 1864.7
#define Asharp7 3729.3
#define Asharp8 7458.6
#define Asharp9 14917
#define B0 30.868
#define B1 61.735
#define B2 123.47
#define B3 246.94
#define B4 493.88
#define B5 987.77
#define B6 1975.5
#define B7 3951.1
#define B8 7902.1
#define B9 15804
//上面很簡單，就是我懶得開另一個檔案放 :D
#include<Servo.h>
#define stop 90 //360度mg90 停止速度
#define open 90 //180度 sg90開門狀態(視servo安裝狀態)
#define close 50 //180度sg90關門狀態(視servo安裝狀態)
#define ToggleSW 5
#define MicroSW 6
#define LED 7
#define SG 10
#define MG 9
#define sp 2
Servo mg90; //擺臂馬達(360度)
Servo sg90; //門把馬達(360度)
int limit; // 限位開關狀，亂數模式
int ram, t;
double sganl = 0;

struct note{
    float hz;
    float beat;
};
struct song {
    short bpm;
    short length;
    struct note *sheet;
};

// Unwelcome School 譜
struct note UnwelcomeSchool_sheet[] = {
    {A4,1}, {C5,1},  {Dsharp5,0.75},  {E5,0.25},  {0,0.5},  {Gsharp4,0.5},
    {A4,0.25},{0,0.5-0.25},  {C5,0.25},{0,0.5-0.25}, {D5,0.25},{0,0.5-0.25} ,{C5,0.25},{0,0.5-0.25},{Dsharp5,0.25},{0,0.5-0.25},{Dsharp5,0.25},{E5,0.25},{0,1},
    {G5,0.25},{0,0.5-0.25}, {Fsharp5,0.25},{0,0.5-0.25}, {F5,0.25},{0,0.5-0.25},{Dsharp5,0.25},{0,0.5-0.25},{D5,0.25},{0,0.5-0.25},{C5,0.25},{0,0.5-0.25},{B4,0.25},{0,0.5-0.25},{Asharp4,0.25},{0,0.5-0.25},
    {B4,0.25},{0,0.5-0.25},{C5,0.25},{0,0.5-0.25},{D5,0.25},{0,0.5-0.25},{Dsharp5,0.25},{0,0.5-0.25},{E5,0.25},{0,1-0.25},{E4,1},
    {A4,1}, {C5,1},  {Dsharp5,0.75},  {E5,0.25},  {0,0.5},  {Gsharp4,0.5},
    {A4,0.25},{0,0.5-0.25},  {C5,0.25},{0,0.5-0.25}, {D5,0.25},{0,0.5-0.25} ,{C5,0.25},{0,0.5-0.25},{Dsharp5,0.25},{0,0.5-0.25},{Dsharp5,0.25},{E5,0.25},{0,1},
    {G5,0.25},{0,0.5-0.25}, {Fsharp5,0.25},{0,0.5-0.25}, {F5,0.25},{0,0.5-0.25},{Dsharp5,0.25},{0,0.5-0.25},{E5,0.25},{0,0.5-0.25},{F5,0.25},{0,0.5-0.25},{Fsharp5,0.25},{0,0.5-0.25},{G5,0.25},{0,0.5-0.25},
    {Gsharp5,0.25},{0,0.5-0.25},{Gsharp5,0.25},{0,0.5-0.25},{A5,0.25},{0,0.5-0.25},{A5,0.25},{0,0.5-0.25},{B5,1},{E4,1.25}
};

// 校歌譜
struct note school[] =
{ {G4 ,1},{C4 ,0.75},{D4 ,0.25},{E4 ,1},{G4 ,1},{
C5 ,1},{B4 ,0.75},{A4 ,0.25},{G4 ,1},{0 ,1},{
A4 ,1},{ G4 ,0.75},{ A4 ,0.25},{ E4 ,1},{ G4 ,1},{
D4 ,1},{C4 ,0.75},{D4 ,0.25},{E4 ,1},{0 ,1},{
E4 ,1.5},{D4 ,0.5},{G4 ,1},{E4 ,1},{
D5 ,1.5},{C5 ,0.5},{B4 ,1},{A4 ,1},{
C4 ,1},{D4 ,0.75},{E4 ,0.25},{G4 ,1},{A4 ,0.75},{G4 ,0.25},{
F4 ,1},{E4 ,0.5},{G4 ,0.5},{C4 ,0.5},{D4 ,0.5},{E4 ,1},{
G4 ,1},{Fsharp4 ,0.75},{G4 ,0.25},{A4 ,1},{B4 ,0.75},{C5 ,0.25},{
E5 ,1},{D5 ,0.75},{G4 ,0.25},{A4 ,0.5},{B4 ,0.5},{C5 ,1},{
E4 ,1},{C4 ,0.75},{D4 ,0.25},{E4 ,1},{F4 ,1},{G4 ,0.5},{
C5 ,0.5},{B4 ,0.5},{A4 ,0.5},{A4 ,0.5},{G4 ,0.5},{
C4 ,0.5},{0 ,0.5},{E4 ,0.5},{0 ,0.5},{G4 ,0.5},{0 ,0.5},{C5 ,0.5},{0 ,0.5},{
D5 ,0.5},{0 ,0.5},{C5 ,1},{0 ,0.75},{B4 ,0.25},{0 ,1},{A4 ,0.75},{0 ,0.25},{
C4 ,1},{D4 ,0.5},{E4 ,0.5},{G4 ,0.5},{A4 ,0.5},{G4 ,1},{
F4 ,1},{E4 ,0.75},{D4 ,0.25},{A4 ,1},{D4 ,0.5},{E4 ,0.5},{
G4 ,1},{Fsharp4 ,0.75},{G4 ,0.25},{A4 ,0.5},{B4 ,0.5},{C5 ,1},{
E5 ,1},{D5 ,0.75},{G4 ,0.25},{A4 ,0.5},{B4 ,0.5},{C5 ,1},{
E5 ,1},{D5 ,0.75},{C5 ,0.25},{B4 ,0.5},{A4 ,0.5},{G4 ,1},{
G4 ,1},{Fsharp4 ,0.75},{G4 ,0.25},{C5 ,0.5},{D5 ,0.5},{E5 ,1},{
E5 ,1},{0 ,2},{E5 ,1},{
D5 ,1.5},{D5 ,0.5},{A4 ,1},{B4 ,1},{
C4 ,1.5},{0 ,2.5}};
struct song Songs[] = {
    {180, sizeof(UnwelcomeSchool_sheet)/8, UnwelcomeSchool_sheet},
};

struct song Songs1[] = {
    {120, sizeof(school)/8, school},
};

void setup() {
limit=0; 
pinMode(sp, OUTPUT); //設定蜂鳴器在A2
sg90.attach(SG); //起動 sg90在D10
mg90.attach(MG);  //起動 mg90在D9
sg90.write(close); //設定門把關閉中
mg90.write(stop);   //設定擺臂停止中
pinMode(LED,OUTPUT);  
Serial.begin(9600);
Serial.print(Songs[0].length);
randomSeed(analogRead(A1));
}

void loop()
{
 if(digitalRead(ToggleSW)==LOW) //搖擺開關上撥
 {  
   ram=random(5);  //取0-4亂數整數
  switch(ram) 
  {
   case 0:
    t=random(2,7);
     mg90BandF(60,120,t);//來回白爛2~6次
     break;
   case 1:
     mg90WforOP(2000); //等2秒後才動作
     break;
   case 2:
     mg90WforOP2(5000); // 花費5秒抬頭後才動作
     break;
   case 3:
    sganl = close;
    SGMove(open+20-close,3000); // 花費3秒抬頭
    playsong(); // 播放Unwelcome School
    LEDblink(20);//閃爍間隔
    sg90.write(close);
    delay(500);
     break;
   case 4:
    sganl = close;
    SGMove(open+20-close,3000); // 花費3秒抬頭
    playsong1(); // 播放校歌
    LEDblink(20);//閃爍間隔
    sg90.write(close);
    delay(500);
    break;
   default:

     break; 
    */
  }
  Serial.print(ram);  //Debug用
 }
}

void mg90BandF(int cwspeed, int ccwspeed,int times) //反覆無常 
{
  mg90.attach(MG);
  sg90.attach(SG);
  pacinBandF(cwspeed,ccwspeed,times);//擺臂來回動times次
  limit=1; //擺臂離開限位開關(限位空)
 while(digitalRead(ToggleSW)==LOW)  //擺臂上撥
  {
  sg90.write(open);
  mg90.write(120);
  }
 
  while((digitalRead(ToggleSW)==HIGH) && (limit==1)) //擺臂下撥且限位上
  {
   mg90goback(cwspeed); //擺臂用cwspeed速度回
    }
}

// 播放 Unwelcome School
void playsong(){
  for(int i =0;i<Songs[0].length;i++){
    tone(sp, Songs[0].sheet[i].hz,(Songs[0].sheet[i].beat)*333);
    delay((Songs[0].sheet[i].beat)*333);
  }
  digitalWrite(sp, LOW);
}

// 播放 校歌        如果你問我為何不把兩首歌寫在一起成一個函式，我只能回答: 我懶~ 
void playsong1(){
  for(int i =0;i<Songs1[0].length;i++){
    tone(sp, Songs1[0].sheet[i].hz,(Songs1[0].sheet[i].beat)*600);
    delay((Songs1[0].sheet[i].beat)*600);
  }
  digitalWrite(sp, LOW);
}

void pacinBandF(int cw,int ccw,int t) //來回擺動t次
{
  sg90.write(open);
  for (int i=0;i<t;i++)
     {
       mg90.write(ccw);
       delay(150);
       mg90.write(cw);
       delay(150);
     }
  sg90.write(close);
}

void mg90WforOP(int waiting) //伺機而動
{
  mg90.attach(MG);
  sg90.attach(SG);
  delay(waiting);
  sg90.write(open);
  delay(150);
  mg90.write(150);//擺臂快速衝出
  delay(150);
  while(digitalRead(MicroSW)==LOW ) //限位空
   {
  mg90.write(0); //擺臂快速縮回
  sg90.write(close); //關門 
   }
  mg90.write(stop); //擺臂暫停(蟄伏)
  delay(1000); //蟄伏1秒
   while(digitalRead(ToggleSW)==LOW) //繼續未完成動作
    {
      sg90.write(open);
      mg90.write(180);
      limit=1;
    }
  mg90goback(0);
}

void mg90WforOP2(int waiting) //花費waiting毫秒抬頭後動
{
  mg90.attach(MG);
  sg90.attach(SG);
  sganl = close;
  SGMove(open-close, waiting);//花費waiting毫秒抬頭
  LEDblink(10);
  delay(150);
  mg90.write(150);//擺臂快速衝出
  delay(150);
  while(digitalRead(MicroSW)==LOW ) //限位空
   {
  mg90.write(0); //擺臂快速縮回
  sg90.write(close); //關門
   }
  mg90.write(stop); //擺臂暫停(蟄伏)
  delay(1000); //蟄伏1秒
   while(digitalRead(ToggleSW)==LOW) //繼續未完成動作
    {
      sg90.write(open);
      mg90.write(180);
      limit=1;
    }
  mg90goback(0);
}

void SGMove(double anl, double t){ // 將SG的角度在t毫秒內增加anl度
  for(int i =0;i<t/10;i++){
    if((sganl+anl*10/t)>180){ //防呆，避免轉過頭       喔還有打"，"會有快捷鍵是怎樣啦
      sganl += anl*10/t;
      sganl -= 180;
    }else{
      sganl += anl*10/t;  //確認沒過頭後計算每10毫秒要轉幾度
    }
    if(anl*10/t!=0){
      sg90.write(sganl); 
    }
    delay(10);
    }
}

void mg90goback(int backspeed)
 { 
  while ((digitalRead(ToggleSW)==HIGH) && (limit==1)) 
   {
     mg90.write(backspeed);
     if (digitalRead(MicroSW)==HIGH)
       stopservo();
   }
 }

void stopservo()
{  limit=0 ;
   mg90.write(stop);
   sg90.write(close);
   mg90.detach();
  //  sg90.detach(); (servo會回到0度)
}
oid LEDblink(int times)
{
  for(int i=0;i<times;i++)
  {digitalWrite(LED,HIGH);
  delay(50);
  digitalWrite(LED,LOW);
  delay(50);
  }
}

//hummm  好像寫太多廢話了 :D
