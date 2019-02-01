
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(7, 8);  

LiquidCrystal_I2C lcd(0x27, 16, 2);

//  Numeros celulares registrados en el sistema.
String   Number_One    = "77886521";   // Número master o Cliente master

String  Comment_Room_1 = "";
String  keys = "";
String  Cell_Number = "";
int     Find_Chars = 0;
char    incoming_char;
char    Digits;
char  Character1;
char  Character2;
char  Character3;
char  Character4;
char  Character5;
char  Character6;
char  Character7;


// Declaración de pines digitales
#define   Alarm  2
#define   Door_1 A0
#define   Door_2 A1
#define   Win_1  A2
#define   Win_2  A3

// Declaración de puerto analogico 0 para un sensor fotoresistivo.

boolean Presence = false;
boolean State_Room_1 = false;

int   State_Door_1;
int   State_Door_2;
int   State_Win_1;
int   State_Win_2;

int   Count_Room_1 = 0;
