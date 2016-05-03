#include <SPI.h>//include the SPI bus library
#include <MFRC522.h>//include the RFID reader library
#include <LiquidCrystal.h>


#define SS_PIN 10  //slave select pin
#define RST_PIN 9  //reset pin
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
MFRC522 mfrc522(SS_PIN, RST_PIN);        // instatiate a MFRC522 reader object.
MFRC522::MIFARE_Key key;//create a MIFARE_Key struct named 'key', which will hold the card information


void setup() {
        Serial.begin(9600);        // Initialize serial communications with the PC
        SPI.begin();               // Init SPI bus
        mfrc522.PCD_Init();        // Init MFRC522 card (in case you wonder what PCD means: proximity coupling device)
        Serial.println("Scan a MIFARE Classic card");
         // set up the LCD's number of columns and rows: 
         lcd.begin(16, 2);
          // Print a message to the LCD.
          lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("A Project By :");
     delay(1000);
     lcd.clear();
     lcd.setCursor(0,0);
      lcd.print("Shashank");
     delay(1000);
     lcd.clear();
      lcd.setCursor(0,0);
     lcd.print("Anagh");
     delay(1000);
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Aquib");
     delay(1000);
       lcd.clear();
      lcd.setCursor(0,0);
     lcd.print("Sharan");
      delay(1000);
     
        
       
        for (byte i = 0; i < 6; i++) {
                key.keyByte[i] = 0xFF;//keyByte is defined in the "MIFARE_Key" 'struct' definition in the .h file of the library
        }

}

int val;
int k=0;
int blockn=1;
int blockv=2;//this is the block number we will read and then write onto. Do not write into 'sector trailer' block, since this can make the block unusable.

byte bal[16];
byte pay[16]={"0400"};
byte blockcontent[16] = {"3000"};//an array with 16 bytes to be written into one of the 64 card blocks is defined

byte readbackblock[18];//This array is used for reading out a block. The MIFARE_Read method requires a buffer that is at least 18 bytes to hold the 16 bytes of a block.

void loop()
{  
   lcd.clear();
      lcd.setCursor(0,0);
     lcd.print("READ CARD 1");     
     for(int k=1;;k++){ 
    // Look for new cards 
  if (  mfrc522.PICC_IsNewCardPresent()) {//if PICC_IsNewCardPresent returns 1, a new card has been found and we continue
    break;//if it did not find a new card is returns a '0' and we return to the start of the loop
  }

  // Select one of the cards
  if (  mfrc522.PICC_ReadCardSerial()) {//if PICC_ReadCardSerial returns 1, the "uid" struct (see MFRC522.h lines 238-45)) contains the ID of the read card.
    break;//if it returns a '0' something went wrong and we return to the start of the loop
  }
     }
 //writeBlock(blockv, blockcontent);//the blockcontent array is written into the card block
       
        readBlock(blockn, readbackblock);//read the block back 
         Serial.println("card selected is:");
          for (int j=0 ; j<16 ; j++)//print the block contents
         {
           Serial.write (readbackblock[j]);//Serial.write() transmits the ASCII numbers as human readable characters to serial monitor
         }
           Serial.println("");
         readBlock(blockv, readbackblock);//read the block back 
          Serial.print("Card Value is: ");
          for (int j=0 ; j<16 ; j++)//print the block contents
         {
           Serial.write (readbackblock[j]);//Serial.write() transmits the ASCII numbers as human readable characters to serial monitor
         }
         Serial.println("");
      
         
         lcd.clear();
         lcd.setCursor(0,0);
         lcd.print("The value :");
         //lcd.setCursor(0,1);
         for (byte l=0 ; l<4; l++)
          {
            val=readbackblock[l];
            lcd.print(val);
           // lcd.print(readbackblock[l], HEX);
          }
          delay(1000);
        


   lcd.clear();
      lcd.setCursor(0,0);
     lcd.print("READ CARD 2");      
    // Look for new cards 
    for(int k=1;;k++){
  if (  mfrc522.PICC_IsNewCardPresent()) {//if PICC_IsNewCardPresent returns 1, a new card has been found and we continue
    break;//if it did not find a new card is returns a '0' and we return to the start of the loop
  }

  // Select one of the cards
  if (  mfrc522.PICC_ReadCardSerial()) {//if PICC_ReadCardSerial returns 1, the "uid" struct (see MFRC522.h lines 238-45)) contains the ID of the read card.
    break;//if it returns a '0' something went wrong and we return to the start of the loop
  }
    }
 //writeBlock(blockv, blockcontent);//the blockcontent array is written into the card block
       
        readBlock(blockn, readbackblock);//read the block back 
         Serial.println("card selected is:");
          for (int j=0 ; j<16 ; j++)//print the block contents
         {
           Serial.write (readbackblock[j]);//Serial.write() transmits the ASCII numbers as human readable characters to serial monitor
         }
           Serial.println("");
         readBlock(blockv, readbackblock);//read the block back 
          Serial.print("Card Value is: ");
          for (int j=0 ; j<16 ; j++)//print the block contents
         {
           Serial.write (readbackblock[j]);//Serial.write() transmits the ASCII numbers as human readable characters to serial monitor
         }
         Serial.println("");
      
         
         lcd.clear();
         lcd.setCursor(0,0);
         lcd.print("The value :");
         //lcd.setCursor(0,1);
         for (byte l=0 ; l<4 ; l++)
          {
            val=readbackblock[l];
            lcd.print(val);
           // lcd.print(readbackblock[l], HEX);
          }
          delay(2000);
          lcd.clear();
          lcd.setCursor(0,0);
         lcd.print("Transaction");
         lcd.setCursor(0,1);
         lcd.print("complete!");
delay(1000);
         
}


