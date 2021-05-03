#include <Servo.h>
#include <LedControl.h>

//--------------------- 8X8 MATRIX ---------------------------

#define LEDON 28

//--------------------- 8X8 MATRIX ---------------------------
LedControl lc = LedControl(41, 45, 43, 1); // Pins: DIN,CLK, CS, # display connessi

byte Happy[] = {
  B00000000,
  B00100110,
  B01000110,
  B01000000,
  B01000000,
  B01000110,
  B00100110,
  B00000000
};

byte HappyClosedEyes[] = {
  B00000000,
  B00100100,
  B01000100,
  B01000000,
  B01000000,
  B01000100,
  B00100100,
  B00000000
};

/*//------------------ BRACCIO MECCANICO 1 DESTRA ----------------------
Servo Spalla;
Servo Braccio;
Servo Mano;

void MuoviSpallaDestra(int valore);
void MuoviBraccioDestra(int valore);
void MuoviManoDestra(int valore);

int spalla1 = 80;
int braccio1 = 80;
int mano1 = 80;*/

//------------------ BRACCIO MECCANICO 2 SINISTRA ----------------------
Servo Spalla2;
Servo Braccio2;
Servo Mano2;

void MuoviSpallaSinistra(int valore);
void MuoviBraccioSinistra(int valore);
void MuoviManoSinistra(int valore);

int spalla2 = 80;
int braccio2 = 80;
int mano2 = 80;

//------------------------ DISTANZIOMETRO ------------------------------
Servo ServoDist; // 23

const int TrigPin = A13;
const int EchoPin = A14;

long Duration;
int Distance;

bool Dist = LOW;

//------------------------ LED MONITOR ------------------------------
int digit1 = 9; //PWM Display pin D1
int digit2 = 10; //PWM Display pin D2
int digit3 = 11; //PWM Display pin D3
int digit4 = 12; //PWM Display pin D4

int segA = 8; //Display pin 11
int segB = 2; //Display pin 7
int segC = 3; //Display pin 4
int segD = 4; //Display pin 2
int segE = 5; //Display pin 1
int segF = 7; //Display pin 10
int segG = 6; //Display pin 5

//------------------------ TESTA ------------------------------

Servo ServoBase; //26
Servo ServoTesta; //24

const int Sopra = A9;
const int SxGiu = A7;
const int DxGiu = A8;

int valoreTesta = 50;
int valoreBase = 80;

bool Testa = HIGH;
bool BassoDx = HIGH;
bool BassoSx = HIGH;

bool Segui = LOW;
bool SeguiDisable = LOW;

//---------------------- Potenziometro -----------------------------

  const int Potentiometer = A15;
  int VarX = 0;
  
  int CountPress = 0;

  int MovBase[2];
  int MovBraccio[2];

  bool Press = false;

//------------ PULSANTI A-B-RECORD-PLAY ---------------

  const int ButtonHead = A0;
  const int ButtonA = A1;
  const int ButtonB = A2;
  const int ButtonRecord = A3;
  const int ButtonPlay = A4;
  const int ButtonOK = A5;
  const int ButtonDist = A6;
  const int ButtonMisu = A10;

  int StateButtonHead = 0;
  int StateButtonA = 0;
  int StateButtonB = 0;
  int StateButtonRecord = 0;
  int StateButtonPlay = 0;
  int StateButtonOK = 0;
  int StateButtonDist = 0;
  int StateButtonMisu = 0;
  
  bool Record = false;
  bool PressButton = LOW;

  int CountMisu = 0;

void setup() {

    Serial.begin(9600);

  //----------- INIZIALIZZAZIONE BOTTONI ----------------
   
    pinMode(ButtonA, INPUT);
    pinMode(ButtonB, INPUT);
    pinMode(ButtonRecord, INPUT);
    pinMode(ButtonPlay, INPUT);
    pinMode(ButtonOK, INPUT);

  //----------- POTENZIOMETRO ----------------
   
    pinMode(Potentiometer, INPUT);
    
  //--------------- 8x8 pt. 1 --------------------------
    lc.shutdown(0, true);
    lc.shutdown(0, false);
    lc.setIntensity(0, 5);
    lc.clearDisplay(0);
  
    LedOn(HappyClosedEyes);

  /*//---------- Braccio destra --------------------
    Spalla.attach(28);
    Braccio.attach(30);
    Mano.attach(32);

    MuoviSpallaDestra(145);
    MuoviBraccioDestra(90);
    MuoviManoDestra(180);

    Serial.print("Braccio Destro startato \n");
    delay(3000);*/
    
    //---------- DISTANZIOMETRO --------------------
    
    ServoDist.attach(52);
    ServoDist.write(0);

    pinMode(TrigPin,OUTPUT);
    pinMode(EchoPin,INPUT);

    //---------- LED MONITOR --------------------
    
    pinMode(segA, OUTPUT);
    pinMode(segB, OUTPUT);
    pinMode(segC, OUTPUT);
    pinMode(segD, OUTPUT);
    pinMode(segE, OUTPUT);
    pinMode(segF, OUTPUT);
    pinMode(segG, OUTPUT);
  
    pinMode(digit1, OUTPUT);
    pinMode(digit2, OUTPUT);
    pinMode(digit3, OUTPUT);
    pinMode(digit4, OUTPUT);

    
    //--------------- Testa ------------------------
    ServoBase.attach(26);
    ServoTesta.attach(24);

    pinMode(Sopra,INPUT);
    pinMode(DxGiu,INPUT);
    pinMode(SxGiu,INPUT);

    ServoTesta.write(valoreTesta);
    ServoBase.write(valoreBase);

    Serial.print("Testa startata \n");
    delay(3000);
    
    //---------- Braccio Sinistra --------------------
    
    Spalla2.attach(34);
    Braccio2.attach(36);
    Mano2.attach(38);

    MuoviSpallaSinistra(0);
    MuoviBraccioSinistra(170);
    MuoviManoSinistra(0);

    Serial.print("Braccio Sinistro startato \n");
    LedOn(Happy);
    delay(1000);

}

void loop() {

    StateButtonHead = digitalRead(ButtonHead);
    //delay(10);
    StateButtonA = digitalRead(ButtonA);
    //delay(10);
    StateButtonB = digitalRead(ButtonB);
    //delay(10);
    StateButtonRecord = digitalRead(ButtonRecord);
    //delay(10);
    StateButtonPlay = digitalRead(ButtonPlay);
    //delay(10);
    StateButtonDist = digitalRead(ButtonDist);
    //delay(10);
    StateButtonMisu = digitalRead(ButtonMisu);
    //delay(10);
    StateButtonOK = digitalRead(ButtonOK);
    //delay(10);
    
    if (StateButtonA == HIGH && PressButton == LOW && Dist == LOW) 
    { 
      DisableHead();
      LedOn();
      
      Serial.print("\n");
      Serial.print("A");
      
      MuoviSpallaSinistra(1);
      MuoviBraccioSinistra(72);
      MuoviManoSinistra(50);
      delay(1500);
      MuoviManoSinistra(0);

      MuoviBraccioSinistra(170);
      MuoviSpallaSinistra(0);   
      MuoviManoSinistra(0);
      
      PressButton = HIGH;
    }
    else if (StateButtonB == HIGH && PressButton == LOW && Dist == LOW) 
    { 
      DisableHead();
      LedOn();
      
      Serial.print("\n");
      Serial.print("B");
        
      MuoviSpallaSinistra(38);
      MuoviBraccioSinistra(62);
      MuoviManoSinistra(50);
      delay(1500);
      MuoviManoSinistra(0);

      MuoviBraccioSinistra(170);
      MuoviSpallaSinistra(0);   
      MuoviManoSinistra(0);  
      
      PressButton = HIGH;
    }
    else if (StateButtonHead == HIGH && PressButton == LOW && Dist == LOW) 
    { 
      LedOn();
       
      if (Segui == HIGH)
      {
         Segui = LOW;
      
         valoreTesta = 50;
         valoreBase = 80;
            
         ServoTesta.write(valoreTesta);
         ServoBase.write(valoreBase);
         
         Serial.print("\n");  
         Serial.print("Testa OFF");
      }
      else
      {
         Segui = HIGH;

         Serial.print("\n");  
         Serial.print("Testa ON");
      }
       
      PressButton = HIGH;
    }
    else if (StateButtonRecord == HIGH && PressButton == LOW &&  Record == false && Dist == LOW) 
    { 
      DisableHead();
      LedOn();
      
      if (Record == false)
      {
        Record = true;
        CountPress = 0;

        Serial.print("\n");  
        Serial.print("Record ON");
      }
      else
      {
        Record = false;
        CountPress = 0;
        Serial.print("\n");  
        Serial.print("Record OFF");
      }
      
      PressButton = HIGH;
    }
    else if (StateButtonPlay == HIGH && PressButton == LOW && Dist == LOW) 
    { 
      DisableHead();
      LedOn();
      
      Serial.print("\n");
      Serial.print("Play");
             
      MuoviManoSinistra(50);
      MuoviSpallaSinistra(MovBase[0]);
      MuoviBraccioSinistra(MovBraccio[0]);
      delay(1500);
      MuoviManoSinistra(0);

      MuoviBraccioSinistra(170);
      
      MuoviSpallaSinistra(MovBase[1]);
      MuoviBraccioSinistra(MovBraccio[1]);
      MuoviManoSinistra(50);

      MuoviBraccioSinistra(170);
      MuoviSpallaSinistra(0);   
      MuoviManoSinistra(0);
      
      PressButton = HIGH;
    }
    else if (StateButtonOK == HIGH && PressButton == LOW && Dist == LOW) 
    {
      DisableHead();
      LedOn();
      
      Serial.print("\n");
      Serial.print("OK");
       
      CountPress++;
      PressButton = HIGH;
    }
    else if (StateButtonDist == HIGH && PressButton == LOW) 
    { 
      DisableHead();
      LedOn();
      
      if (Dist == LOW)
      {
        Serial.print("Distanziometro: ON");
        Serial.print("\n");
        
        ServoDist.write(80);
        Dist = HIGH;
      }
      else
      {
        Serial.print("Distanziometro: OFF");
        Serial.print("\n");
        
        ServoDist.write(0);
        Dist = LOW;
      }
          
      PressButton = HIGH;
    }
    else if (StateButtonMisu == HIGH && PressButton == LOW && Dist == HIGH) 
    { 
      DisableHead();
      LedOn();
      CountMisu++;

      if(CountMisu == 3)
      {
        CountMisu = 0;
      }
      
      PressButton = HIGH;
    }
    else if ( StateButtonMisu == LOW && StateButtonHead == LOW && StateButtonDist == LOW && StateButtonOK == LOW && StateButtonB == LOW && StateButtonB == LOW && StateButtonRecord == LOW && StateButtonPlay == LOW && PressButton == HIGH)
    {
      PressButton = LOW;
    }     

  //-------------------- FUNZIONE TESTA -----------------------
    if (Segui == HIGH && Dist == LOW)
    {
      Testa = digitalRead(Sopra);
      delay(5);
      BassoDx = digitalRead(DxGiu);
      delay(5);
      BassoSx = digitalRead(SxGiu);
  
      if (BassoSx == LOW && Testa == LOW && BassoDx == LOW) //Fermo
      {
        valoreTesta += 0;
        valoreBase += 0;
        ServoTesta.write(valoreTesta);
        ServoBase.write(valoreBase);        
      }
      else if (BassoSx == LOW && Testa == LOW && BassoDx == HIGH) //Sinistra
      {
        valoreBase -= 1;
        ServoBase.write(valoreBase);
      }
      else if (BassoDx == LOW && Testa == LOW && BassoSx == HIGH) //Destra
      {
        valoreBase += 1;
        ServoBase.write(valoreBase);
      }
      else if (BassoDx == LOW && BassoSx == LOW && Testa == HIGH) //Giu
      {
        valoreTesta += 1;
        ServoTesta.write(valoreTesta);
      }
      else if (Testa == LOW) // Sopra
      {
        valoreTesta -= 1;
        ServoTesta.write(valoreTesta);
      }
      else if (BassoDx == LOW) //basso destra
      {
        valoreTesta += 1;
        valoreBase += 1;
        ServoTesta.write(valoreTesta);
        ServoBase.write(valoreBase);
      }
      else if (BassoSx == LOW) //basso a sinistra
      {
        valoreTesta += 1;
        valoreBase -= 1;
        ServoTesta.write(valoreTesta);
        ServoBase.write(valoreBase);
      }
  
      if (valoreTesta > 180 && valoreTesta < 0)
      {
        if (valoreTesta > 180)
        {
          valoreTesta = 180;
        }
        else
        {
          valoreTesta = 0;
        }
      }
  
      if (valoreBase > 180 && valoreBase < 0)
      {
        if (valoreBase > 180)
        {
          valoreBase = 180;
        }
        else
        {
          valoreBase = 0;
        }
      }
    }

  //------------------------ POTENZIOMETRO ----------------
   else if(Record == true && Dist == LOW )
   {
      VarX = analogRead(Potentiometer);
      VarX = map(VarX, 0, 1023, 0, 180);
      Serial.print("\n");
        
      if(CountPress == 0)
      {
          MovBase[0] = VarX;
          MuoviSpallaSinistra(VarX);
          Serial.print("Spalla 1: ");
      }
      else if(CountPress == 1)
      {
          MovBraccio[0] = VarX;
          MuoviBraccioSinistra(VarX);
          Serial.print("Braccio 1: ");
      }
      else if(CountPress == 2)
      {
         MuoviBraccioSinistra(180);
         MovBase[1] = VarX;
         delay (10);
         MuoviSpallaSinistra(VarX);
         Serial.print("Spalla 2: ");
      }
      else if(CountPress == 3)
      {
         MovBraccio[1] = VarX;
         delay (10);
         MuoviBraccioSinistra(VarX);
         Serial.print("Braccio 2: ");
      }
      else if(CountPress == 4)
      {
         CountPress = 0;
         Record = false;
         
         Serial.print("Fine");
         Serial.print("\n");

         Serial.print("Base 1:");
         Serial.print(MovBase[0]);
         
         Serial.print("   Braccio 1:");
         Serial.print(MovBraccio[0]);

         Serial.print("   Base 2:");
         Serial.print(MovBase[1]);

         Serial.print("   Braccio 2:");
         Serial.print(MovBraccio[1]);

         MuoviSpallaSinistra(0);
         MuoviBraccioSinistra(170);
         MuoviManoSinistra(0);
         
      }

      Serial.print("   VarX=");    
      Serial.print(VarX);

      Serial.print("   CountPress=");
      Serial.print(CountPress);
          
      delay(10);
   }
   else if(Dist == HIGH)
   {
      digitalWrite(TrigPin, LOW);
      delayMicroseconds(2);
    
      digitalWrite(TrigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(TrigPin, LOW);
    
      Duration = pulseIn(EchoPin, HIGH);
      Distance = Duration*0.034/2;

      if(CountMisu == 1)
      Distance = Distance*10; //mm
      
      if(CountMisu == 2)
      Distance = Distance*0.393701; //pollici / inch
    
      displayNumber(Distance);
      Serial.print("Distanza: ");
      Serial.println(Distance);

      Serial.print("CountMisu: ");
      Serial.println(CountMisu);
      
   }
}

void LedOn(byte led[])
{
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(0, i, led[i]);
    delay(1);
  }
}

/*void MuoviSpallaDestra(int valore)
{
  Segui = LOW;
  if (spalla1 != valore)
  {

    if (spalla1 < valore)
    {
      for (spalla1; spalla1 <= valore; spalla1++)
      {
        Spalla.write(spalla1);
        delay(10);
      }
    }
    else
    {
      for (spalla1; spalla1 >= valore; spalla1--)
      {
        Spalla.write(spalla1);
        delay(10);
      }
    }
    spalla1 = valore;
  }
  Segui = HIGH;
}

void MuoviBraccioDestra(int valore)
{
  Segui = LOW;
  if (braccio1 != valore)
  {
    if (braccio1 < valore)
    {
      for (braccio1; braccio1 <= valore; braccio1++)
      {
        Braccio.write(braccio1);
        delay(10);
      }
    }
    else
    {
      for (braccio1; braccio1 >= valore; braccio1--)
      {
        Braccio.write(braccio1);
        delay(10);
      }
    }
    braccio1 = valore;
  }
  Segui = HIGH;
}

void MuoviManoDestra(int valore)
{
  Segui = LOW;
  if (mano1 != valore)
  {
    if (mano1 < valore)
    {
      for (mano1; mano1 <= valore; mano1++)
      {
        Mano.write(mano1);
        delay(10);
      }
    }
    else
    {
      for (mano1; mano1 >= valore; mano1--)
      {
        Mano.write(mano1);
        delay(10);
      }
    }
    mano1 = valore;
  }
  Segui = HIGH;
}*/

void MuoviSpallaSinistra(int valore)
{
  if(Segui == HIGH)
  {
    Segui = LOW;
    SeguiDisable = HIGH;
  }
  
  if (spalla2 != valore)
  {
    if (spalla2 < valore)
    {
      for (spalla2; spalla2 <= valore; spalla2++)
      {
        Spalla2.write(spalla2);
        delay(10);
      }
    }
    else
    {
      for (spalla2; spalla2 >= valore; spalla2--)
      {
        Spalla2.write(spalla2);
        delay(10);
      }
    }
    spalla2 = valore;
  }

  if(SeguiDisable == HIGH)
  {
    Segui = HIGH;
    SeguiDisable = LOW;
  }
  
}

void MuoviBraccioSinistra(int valore)
{
  if(Segui == HIGH)
  {
    Segui = LOW;
    SeguiDisable = HIGH;
  }
  
  if (braccio2 != valore)
  {
    if (braccio2 < valore)
    {
      for (braccio2; braccio2 <= valore; braccio2++)
      {
        Braccio2.write(braccio2);
        delay(10);
      }
    }
    else
    {
      for (braccio2; braccio2 >= valore; braccio2--)
      {
        Braccio2.write(braccio2);
        delay(10);
      }
    }
    braccio2 = valore;
  }
  
  if(SeguiDisable == HIGH)
  {
    Segui = HIGH;
    SeguiDisable = LOW;
  }
}

void MuoviManoSinistra(int valore)
{
  if(Segui == HIGH)
  {
    Segui = LOW;
    SeguiDisable = HIGH;
  }
  
  if (mano2 != valore)
  {
    if (mano2 < valore)
    {
      for (mano2; mano2 <= valore; mano2++)
      {
        Mano2.write(mano2);
        delay(10);
      }
    }
    else
    {
      for (mano2; mano2 >= valore; mano2--)
      {
        Mano2.write(mano2);
        delay(10);
      }
    }
    mano2 = valore;
  }
  
  if(SeguiDisable == HIGH)
  {
    Segui = HIGH;
    SeguiDisable = LOW;
  }
  
}

void lightNumber(int numberToDisplay) {

#define SEGMENT_ON  LOW
#define SEGMENT_OFF HIGH

  switch (numberToDisplay){

  case 0:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_OFF);
    break;

  case 1:
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_OFF);
    break;

  case 2:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 3:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 4:
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 5:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 6:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 7:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_OFF);
    break;

  case 8:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 9:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 10:
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_OFF);
    break;
  }
}

void displayNumber(int toDisplay) {
#define DISPLAY_BRIGHTNESS  500

#define DIGIT_ON  HIGH
#define DIGIT_OFF  LOW

  long beginTime = millis();

  for(int digit = 4 ; digit > 0 ; digit--) {

    switch(digit) {
    case 1:
      digitalWrite(digit1, DIGIT_ON);
      break;
    case 2:
      digitalWrite(digit2, DIGIT_ON);
      break;
    case 3:
      digitalWrite(digit3, DIGIT_ON);
      break;
    case 4:
      digitalWrite(digit4, DIGIT_ON);
      break;
    }

    lightNumber(toDisplay % 10);
    toDisplay /= 10;

    delayMicroseconds(DISPLAY_BRIGHTNESS); 

    lightNumber(10); 

    digitalWrite(digit1, DIGIT_OFF);
    digitalWrite(digit2, DIGIT_OFF);
    digitalWrite(digit3, DIGIT_OFF);
    digitalWrite(digit4, DIGIT_OFF);
  }

  while( (millis() - beginTime) < 10) ; 

}

void DisableHead()
{
  if (Segui = HIGH)
  {
     Segui = LOW;

     valoreTesta = 50;
     valoreBase = 80;
      
     ServoTesta.write(valoreTesta);
     ServoBase.write(valoreBase);
  }
}

void LedOn()
{
  analogWrite(LEDON, 255);
  delay(500);
  analogWrite(LEDON, 0);
}

