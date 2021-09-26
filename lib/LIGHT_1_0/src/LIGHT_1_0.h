/*  LIGHT 1.0
 *  version: 1.2.0
 *  author: Tomášek Dominik
 *  
 *  (c)2021
 */


//  zde jsi definuji všechny vstupní a vystupní platformy,proměné atd 
// hlavička celeho programu.

// indetifikace knihovny 
#ifndef LIGHT_1_0_H 
//pojmenovani knihovny 
#define LIGHT_1_0_H 
// zahrnuje arduino 
#include <Arduino.h>

#define LedErr 13 // ledka co je tu pro pripad nejakeho erroru

#define Bluetooth_Jmeno "LIGHT-1.0" // jmeno pro bl. modul 
#define Bluetooth_Baud 115200       // rychlost komunikace bl. modulu a arduina 

#define Vypinac1 11 // vystup pro signal na tlacitko 
#define Vypinac2 12 // vstup pro signal tlacitka 
// vypinac1 vysle signal a jakmile se sepne tlacitko tak vypinac2 aktivuje rele
#define Vypinac_Delay 80 //debounce - osetreni zakmitu 

extern bool mikrofonStav; // stav mikrofonu 

#define MikrofonD A0 // digitalni vstup mikrofonu 
#define Mikrofon_Default true // slouzi k zapinani a vypinai mikrofonu a potom se ulozi do mikrofon stav 
 
extern bool releStav;

#define Rele2 9 // vystup pro relemodul 
#define Zapni true 
#define Vypni false
#define Auto !releStav // logicka funkce xor- rozepina as pina podle aktualniho stavu 


// definice metod 
// inicializace je  neco jako vytvoreni hromady setapu pro jednotlive piny na arduinu , zde je pouzita pro prehlednost

void LedErr_Init(void); // incializace pro ledku erroru 
void LedErr_Zap(void);  // zapnuti ledky , kdyz se ledka rozsviti neco je spatne 

int Bluetooth_Init(void); // inicializace bl.modulu 
int Bluetooth_Available(void); // metoda por zjistovani zda prislo neco na seriovou linku 
char Bluetooth_Read(void); // cteni dat z bl modulu 
void Bluetooth_Rename(void); // metoda pro prejmenovani modulu ale nepouzivam to 

void Vypinac_Init(void); // inicializace vypinace 
int Vypinac_JeSepnut(void); // metoda pro zjisteni stavu tlacitka 

void Mikrofon_Init(void);   // inicializace mikrofonu 
int Mikrofon_JeZvuk(void); // metoda pro zjisteni stavu mikrofonu pro digitalni vstup 
void Mikrofon_VypZap(void); // metoda pro zapinani avypinani mikrofonu pres mobil a bl.modulu 

void Rele_Init(void); // inicializace rele 
void Rele_VypZap(bool data); // slouzi k zapinani avypinani rele a do bool data se zadava (zapni,vypni a auto)

#endif