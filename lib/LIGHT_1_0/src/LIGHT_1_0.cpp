#include "LIGHT_1_0.h"


void LedErr_Init()
{
    pinMode(LedErr, OUTPUT);
    digitalWrite(LedErr, LOW);
}

// kdyz bude chyba tak se rozsviti tato ledka 
void LedErr_Zap()
{
    digitalWrite(LedErr, HIGH);
}

int Bluetooth_Init()
{
    Serial.begin(Bluetooth_Baud); // nastav rychlost na bl. baud 
    Serial.print("AT"); // posli prikaz at prikaz por zjisteni zda bl. modul komunikuje 
    char data[2];  // ulozeni charu co bl posle 
    uint8_t i = 0; //cyklus pro i 
    while (Serial.available() > 0) // cyklus, pokud neco prijde na seriovou linku tak se provede vnitrek
    {
        if(i<2)
        {
            data[i] = Serial.read();
            if (data[i] != 'O' || data[i] != 'K') {
                Serial.flush();
                return -1;
            }
            i++;
        }
    }
    return 1;
}

// seriová komunikace pro abl.modul a arduino
int Bluetooth_Available()
{
    return Serial.available();
}

// vraci char = 1 byte ,cte seriovou linku 
char Bluetooth_Read()
{
    return Serial.read();
}

// metoda pro prejmenovani bl.modulu 
void Bluetooth_Rename(void)
{
    Serial.print("AT+NAME");
    Serial.print(Bluetooth_Jmeno);
    Serial.flush(); // vymaze kompletne celou seriovou linku
}

void Vypinac_Init()
{
    pinMode(Vypinac1, OUTPUT);
    pinMode(Vypinac2, INPUT_PULLUP);
    digitalWrite(Vypinac1, LOW);
}

// hodnota posledniho stisku tlacitka 
unsigned long vypinacLastDebounce = 0;

// metoda pro hlidani zda je talcitko sepnuto
int Vypinac_JeSepnut()
{
    // pokud aktualni hodnota casu(millis) - hodnota posledniho stisku tlacitka bude vetsi nez vypinac_delay(80) tak se provede vnitrek
    if((millis() - vypinacLastDebounce) > Vypinac_Delay)
    {   
        // ulozi se aktualni hodnota casu 
        vypinacLastDebounce = millis();

        /*
            if (digitalRead(vypinac2) != HIGH)
                return 1
            else
                return -1
        */
        return digitalRead(Vypinac2) != HIGH ? 1 : -1; // ? = if , : = else
    }
    return -1;
}

void Mikrofon_Init()
{
    pinMode(MikrofonD, INPUT);
}

int Mikrofon_JeZvuk()
{
    // funguje to stejne jako utoho tlacitka 
    return digitalRead(MikrofonD) == HIGH ? 1 : -1;
}

bool mikrofonStav = Mikrofon_Default;
// metoda pro vypinani a zapinani mikrofonu 
void Mikrofon_VypZap()
{
    if(Bluetooth_Available()>0)
    {
        // kdyz arduino precte po seriove lince znak B tak zapne nebo vypne mikrofon podle posledniho stavu (xor)
        if(Bluetooth_Read() == 'B')
            mikrofonStav = !mikrofonStav;
    }
}

void Rele_Init()
{
    pinMode(Rele2, OUTPUT);
    digitalWrite(Rele2, LOW);
}

bool releStav = false;
// metoda pro spinani rele
void Rele_VypZap(bool data)
{
    if(data == true)
    {
        releStav = true;
        digitalWrite(Rele2, HIGH);
    }
    else
    {
        releStav = false;
        digitalWrite(Rele2,LOW);
    }
}