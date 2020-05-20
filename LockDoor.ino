//Kütüphane
#include <LiquidCrystal.h>
#include <Keypad.h>

//Değişkenler
int errorNumbers = 0;
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
//Değişmeyen sabit değerler
const byte ROWS = 4;
const byte COLS = 4;

char hexakeys[ROWS][COLS] = {
  {'7', '8', '9','/'},
  {'4', '5', '6','x'},
  {'1', '2', '3','-'},
  {'C', '0', '=','+'}
};

byte rowPins[ROWS] = {7, 6, 5,4}; // satır pinleri bağlanması
byte colPins[COLS] = {3, 2, 1,0}; //sütün pinleri bağlanması

Keypad customKeypad = Keypad( makeKeymap(hexakeys), rowPins, colPins, ROWS, COLS); // Keypad Değer Alıyoruz
#define Password_Lenght 7 // Give enough room for six chars + NULL char

char Data[Password_Lenght]; // 6 is the number of chars it can hold + the null char = 7
char Master[Password_Lenght] = "123456"; //Şifre
byte data_count = 0;
char customKey;
void setup()
{
  lcd.begin(16, 2);
  StringWrite("Laboratuvar Girmek  Icin Sifre Girin ");
  delay(1000);
}
void loop() {
  digitalWrite(13,LOW);
  customKey = customKeypad.getKey();
  if(customKey)
  {
    if(data_count==0)
       { 
        lcd.clear();
        lcd.setCursor(0,0);
        StringWrite("Sifre Girin:");
        lcd.setCursor(0,1);
       }
    Data[data_count] = customKey; // char'ı veri dizisine depola
    lcd.setCursor(data_count, 1); // her yeni karakteri göstermek için imleci hareket ettirin
    lcd.print(Data[data_count]); // adı geçen imleçte char yazdır
    data_count++; // yeni karakter saklamak için veri dizisini 1 arttırır, girilen karakter sayısını da takip eder
      
      if (data_count == Password_Lenght - 1) // dizi dizini beklenen karakter sayısına eşitse, verileri ana verilerle karşılaştırın
      {
        if ((!strcmp(Data, Master))) // Eğer Şifre eşit ise Ekrana kapı açıldı yazılır.
        {
          
          pinMode(A0,OUTPUT);
          lcd.clear();
          lcd.setCursor(0,0);
          StringWrite("Kilidi Actiniz");
          lcd.setCursor(0,1);
          StringWrite("Giris Yapiniz");
          delay(1000);
          lcd.clear();
          lcd.setCursor(0,0);
          digitalWrite(A0,HIGH);
          StringWrite("3 Saniye Sonra Kapi Kapanacak");
          delay(3000);
          lcd.clear();
          lcd.print("Sifre Girin");
          digitalWrite(A0,LOW);
        }
    else
    {
      lcd.clear();
      StringWrite("Yanlis Sifre");
      delay(1000);
      lcd.clear();
      lcd.setCursor(0,0);
      StringWrite("Sifre Girin:");
    }
    clearData();
    } 
  }
}
void clearData()
{
  while (data_count != 0)
  { 
    Data[data_count--] = 0;
  }
  return;
}
void StringWrite(char text[]) // Var olan text değerini ekrana tek tek yazdırır.
{
  int textLength;
  textLength = strlen(text);
  for(byte i = 0 ; i<textLength ; i++)
  {
    lcd.write(text[i]);
    delay(25);
  }
}
