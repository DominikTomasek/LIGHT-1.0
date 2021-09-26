#include <LIGHT_1_0.h>

void setup()
{
  LedErr_Init();
  if(Bluetooth_Init()<0)
  {
    LedErr_Zap();
  }
  Vypinac_Init();
  Mikrofon_Init();
  Rele_Init();
  // Bluetooth_Rename();
}

void loop()
{ 
  // rozsviceni pres bl. modul 
  if (Bluetooth_Available()>0)
  {
    if(Bluetooth_Read() == 'A')
    {
      Rele_VypZap(Auto);
    }
  }
  
  // rozsviceni pres tlacitko 
  if (Vypinac_JeSepnut()>0)
  {
    Rele_VypZap(Auto);
    delay(1000);
  }
  
  // rozsviceni pres mikrofon 
  Mikrofon_VypZap();
  if (Mikrofon_JeZvuk()>0 && mikrofonStav)
  {
    Rele_VypZap(Auto);
    delay(1000);
  }
}



// DEBUG MIKROFON
// void setup()
// {
//   Rele_Init();
//   Mikrofon_Init();
// }
// void loop()
// {
//   if (Mikrofon_JeZvuk()>0)
//   {
//     Rele_VypZap(Auto);
//     delay(500);
//   }
// }


// DEBUG RELE
// void setup()
// {
//   LedErr_Init();
//   if(Bluetooth_Init()<0)
//     LedErr_Zap();
//   Vypinac_Init();
//   Rele_Init();
// }
// void loop()
// {
//   if(Vypinac_JeSepnut()>0)
//     {
//       Rele_VypZap(!relestav);
//       delay(1000);
//     }
//   if(Bluetooth_Available()>0)
//   {
//     if(Bluetooth_Read() == 'A')
//     {
//       Rele_VypZap(!relestav);
//       delay(1000);
//     }
//   }
// }


// DEBUG BLUETOOTH
// void setup() {
//   SerialW.begin(115200);
//   Serial.begin(Bluetooth_Baud);
//   delay(1000);
//   SerialW.println("Start...");
//   delay(100);
//   pinMode(LED_BUILTIN, OUTPUT);
//   if(Bluetooth_Init()>0)
//     digitalWrite(LED_BUILTIN, HIGH);
//   delay(1000);
// }
// void loop() {
//   if(Bluetooth_Available()>0)
//     SerialW.println(Bluetooth_Read());
//   delay(500);
// }