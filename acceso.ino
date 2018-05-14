#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN  9    //Pin 9 para el reset del RC522
#define SS_PIN  10   //Pin 10 para el SS (SDA) del RC522
MFRC522 mfrc522(SS_PIN, RST_PIN); ///Creamos el objeto para el RC522

void setup() {
  //Serial.begin(9600); //Iniciamos La comunicacion serial
  SPI.begin();        //Iniciamos el Bus SPI
  mfrc522.PCD_Init(); // Iniciamos el MFRC522
  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);
  //Serial.println("Control de acceso:");
}

byte ActualUID[4]; //almacenará el código del Tag leído
byte Usuario1[4]= {0x1, 0x2, 0x3, 0x4} ; //código del usuario 1
byte Usuario2[4]= {0xF5, 0x3A, 0xCC, 0x65} ; //código del usuario 2 F5 3A CC 65

byte Usuario3[4]= {0xF9, 0xCB, 0x76, 0x0D} ; //CODIGO USUARIO OSCAR F9 CB 76 0D

void loop() {
  // Revisamos si hay nuevas tarjetas  presentes
  if ( mfrc522.PICC_IsNewCardPresent()) 
        {  
      //Seleccionamos una tarjeta
            if ( mfrc522.PICC_ReadCardSerial()) 
            {
                  // Enviamos serialemente su UID
                 // Serial.print(F("Card UID:"));
                  for (byte i = 0; i < mfrc522.uid.size; i++) {
                          //Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                          //Serial.print(mfrc522.uid.uidByte[i], HEX);   
                          ActualUID[i]=mfrc522.uid.uidByte[i];          
                  } 
                  //Serial.print("     ");                 
                  //comparamos los UID para determinar si es uno de nuestros usuarios  
                  if(compareArray(ActualUID,Usuario1)){
                     //Serial.println("Acceso concedido Bienvenido...");
                    digitalWrite(8, LOW);   // turn the LED on (HIGH is the voltage level)
                    delay(3000);                       // wait for a second
                    digitalWrite(8, HIGH);
                  }
                  else if(compareArray(ActualUID,Usuario2)){
                    //Serial.println("Acceso concedido Bienvenido...");
                    digitalWrite(8, LOW);   // turn the LED on (HIGH is the voltage level)
                    delay(3000);                       // wait for a second
                    digitalWrite(8, HIGH);
                  }
                   else if(compareArray(ActualUID,Usuario3)){
                     //Serial.println("Acceso concedido Bienvenido...");
                    digitalWrite(8, LOW);   // turn the LED on (HIGH is the voltage level)
                    delay(3000);                       // wait for a second
                    digitalWrite(8, HIGH);
                   
                   
                    }else
                    //Serial.println("Acceso denegado...");
                  
                  // Terminamos la lectura de la tarjeta tarjeta  actual
                  mfrc522.PICC_HaltA();
          
            }
      
  }
  
}

//Función para comparar dos vectores
 boolean compareArray(byte array1[],byte array2[])
{
  if(array1[0] != array2[0])return(false);
  if(array1[1] != array2[1])return(false);
  if(array1[2] != array2[2])return(false);
  if(array1[3] != array2[3])return(false);
  return(true);
}

