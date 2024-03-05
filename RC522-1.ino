//#include <MFRC522.h>
//#include <MFRC522Extended.h>
//#include <deprecated.h>
//#include <require_cpp11.h>


#include <Timer.h>
#include <SPI.h>
#include <MFRC522.h>                //含入程式庫”MFRC522.h”



#define SS_PIN 10                   //RC522 NSS 連接 Arduino pin 10
#define RST_PIN 9                   //RC522 RST 連接 Arduino pin 9
#define LED_1 2                   
#define LED_2 3
#define LED_3 4
#define LED_4 6
#define LED_5 5
#define LED_6 7
#define LED_7 8


#define Card1 "63 CB 54 18"
#define Card2 "F3 52 91 18" //C1 21 AF 89  //F3 52 91 18
#define Card3 "E3 9A 5B 18" //33 5A 90 0F  //E3 9A 5B 18
#define Card8 "2A 36 4A 17" //73 FC 5A 18  //2A 36 4A 17
#define Card5 "13 19 47 18"
#define Card6 "34 3B 5A 50"
#define Card7 "13 98 4D A9"

                   //蜂鳴器正極 連接 Arduino pin 2
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.


Timer t; //計時器
int count=0; //秒數
bool timer ;
bool cardRead ;
int countdownT=2;
bool Onmode ;
int modecount=60 ;


void setup() 
{
  Serial.begin(9600);  
                // Initiate a serial communication
  SPI.begin();                       // Initiate  SPI bus
  mfrc522.PCD_Init();                // Initiate MFRC522
  
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  pinMode(LED_5, OUTPUT);
  pinMode(LED_6, OUTPUT);
  pinMode(LED_7, OUTPUT);
  
 
  t.every(1000,WriteToSerial);  //啟動器時器
  

  Serial.println("Put your card to reader....");
 

}



void loop() 
{
  
  if(timer)
  {
    
    t.update();
    
  }
  
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
    {
     
      
      return;
    }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
       return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  
  content.toUpperCase();
  delay(500); 
  
      //---------------le1
    if (content.substring(1) == Card1||mfrc522.PICC_ReadCardSerial())                     //在此鍵入讓房門打開的 IC 卡片 ID 碼
    {
      count=0;
      
      Serial.println("Authorized access"); 
      Serial.println("led1");                          
      Serial.println();
      ledlight1();
      timer=true;
      cardRead=true;
      delay(2000); 
      
  
      
      
      
    }


      //---------------le2
    if (content.substring(1) == Card2||mfrc522.PICC_ReadCardSerial())                     //在此鍵入讓房門打開的 IC 卡片 ID 碼
    {
      count=0;
      
      Serial.println("Authorized access"); 
      Serial.println("led2");                          
      Serial.println();
      
      ledlight2();
      timer=true;
      cardRead=true;
      delay(2000); 

      
    } 
  //---------------le3
    if (content.substring(1) == Card3||mfrc522.PICC_ReadCardSerial())                   
    {
      count=0;
      
      Serial.println("Authorized access"); 
      Serial.println("led3");                         
      Serial.println();
      ledlight3();
      timer=true;
      cardRead=true;
      delay(2000); 
      
      
    } 
    //---------------le4
    if(content.substring(1) == Card8||mfrc522.PICC_ReadCardSerial())                     
    {
      count=0;
      
      Serial.println("Authorized access"); 
      Serial.println("led8");                          
      Serial.println();
      ledlight8();
      timer=true;
      cardRead=true;
      delay(2000); 
            
      
    } 
    //---------------le5
    if (content.substring(1) == Card5||mfrc522.PICC_ReadCardSerial())                    
    { 
      count=0;
      
      Serial.println("Authorized access"); 
      Serial.println("led5");                         
      Serial.println();
      ledlight5();
      timer=true;
      cardRead=true;
      delay(2000); 
      
      
    } 

    //------------led6
      if (content.substring(1) == Card6||mfrc522.PICC_ReadCardSerial())                     //在此鍵入讓房門打開的 IC 卡片 ID 碼
    {
      count=0;
      
      Serial.println("Authorized access"); 
      Serial.println("led6");                          
      Serial.println();
      ledlight6();
      timer=true;
      cardRead=true;
      delay(2000); 
      
          
      
    }
    //-------------led7
    if (content.substring(1) == Card7||mfrc522.PICC_ReadCardSerial())                     //在此鍵入讓房門打開的 IC 卡片 ID 碼
    {
      count=0;
      
      Serial.println("Authorized access"); 
      Serial.println("led 7");                          
      Serial.println();
      ledlight7();
      timer=true;
      cardRead=true;
      delay(2000); 
    
      
    }
  }



void WriteToSerial()
  {
    
    Serial.println(count);
    count++;
    if(!Onmode)
      {
        if(count>countdownT)
            {
            //Serial.println("offmode"); 
            offlight();
            
            
            }

      }
      if(count>30)
      {
        Serial.println("onmode"); 
        onlight();
        timer=false;
        count=0;
        Onmode=false;

      }
    


  ReadCard();
  if(cardRead)
    {
      Onmode=false;
    }else
    {
      
    }

}


void ReadCard()
  {
  
  }




void offlight()
    {
      
        digitalWrite(LED_1, LOW);
        digitalWrite(LED_2, LOW);
        digitalWrite(LED_3, LOW);
        digitalWrite(LED_4, LOW);
        digitalWrite(LED_5, LOW);
        digitalWrite(LED_6, LOW);
        digitalWrite(LED_7, LOW);
        
        cardRead=false;
        Serial.println("offlight");
        
          
    }
void onlight()
    {
      
        ledlight1();
        cardRead=false;
    
        
      
    }    
void ledlight1()
  {
      digitalWrite(LED_1, HIGH);
      digitalWrite(LED_2, HIGH);
      digitalWrite(LED_3, HIGH);
      digitalWrite(LED_4, HIGH);
      digitalWrite(LED_5, HIGH);
      digitalWrite(LED_6, HIGH);
      digitalWrite(LED_7, HIGH);
      Serial.println("1light");
      //delay(500);
  }
void ledlight2()
    {
        digitalWrite(LED_1, LOW);
        digitalWrite(LED_2, HIGH);
        digitalWrite(LED_3, HIGH);
        digitalWrite(LED_4, HIGH);
        digitalWrite(LED_5, HIGH);
        digitalWrite(LED_6, HIGH);
        digitalWrite(LED_7, HIGH);
        Serial.println("2light");
        //delay(500);
    }
void ledlight3()
  {
      digitalWrite(LED_1, HIGH);
      digitalWrite(LED_2, LOW);
      digitalWrite(LED_3, LOW);
      digitalWrite(LED_4, HIGH);
      digitalWrite(LED_5, LOW);
      digitalWrite(LED_6, LOW);
      digitalWrite(LED_7, HIGH);
      Serial.println("3light");
      //delay(500);
  }
void ledlight8()
    {
        digitalWrite(LED_1, LOW);
        digitalWrite(LED_2, HIGH);
        digitalWrite(LED_3, HIGH);
        digitalWrite(LED_4, LOW);
        digitalWrite(LED_5, HIGH);
        digitalWrite(LED_6, HIGH);
        digitalWrite(LED_7, LOW);
        Serial.println("8light");
        //delay(500);
    }
void ledlight5()
  {
      digitalWrite(LED_1, LOW);
      digitalWrite(LED_2, HIGH);
      digitalWrite(LED_3, HIGH);
      digitalWrite(LED_4, LOW);
      digitalWrite(LED_5, LOW);
      digitalWrite(LED_6, LOW);
      digitalWrite(LED_7, HIGH);
      Serial.println("5light");
      
  }
void ledlight6()
  {
      digitalWrite(LED_1, LOW);
      digitalWrite(LED_2, LOW);
      digitalWrite(LED_3, LOW);
      digitalWrite(LED_4, LOW);
      digitalWrite(LED_5, HIGH);
      digitalWrite(LED_6, LOW);
      digitalWrite(LED_7, LOW);
      Serial.println("6light");
      //(500);
  }
void ledlight7()
  {
      digitalWrite(LED_1, LOW);
      digitalWrite(LED_2, LOW);
      digitalWrite(LED_3, LOW);
      digitalWrite(LED_4, LOW);
      digitalWrite(LED_5, LOW);
      digitalWrite(LED_6, HIGH);
      digitalWrite(LED_7, LOW);
      Serial.println("7light");
      //delay(500);
  }