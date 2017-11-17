  /*
* Arduino Wireless Communication Tutorial
*     Example 2 - Receiver Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define In1  2
#define In2 3
#define In3  4
#define In4  5

RF24 radio(7,8); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};

boolean buttonState = 0;
void setup() 
{
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);

  Serial.begin(115200);
  radio.begin();
  radio.openWritingPipe(addresses[0]); // 00002
  radio.openReadingPipe(1, addresses[1]); // 00001
  radio.setPALevel(RF24_PA_MIN);
}
void Forward(int tocdo)
{ 
  analogWrite(In1, tocdo);
  analogWrite(In2, 0);
  analogWrite(In3, tocdo);
  analogWrite(In4, 0);
}
void Backward(int tocdo)
{ 
    analogWrite(In1, 0);
  analogWrite(In2, tocdo);
  analogWrite(In3, 0);
  analogWrite(In4, tocdo);

}

void Right(int tocdo)
{ 
  
  analogWrite(In1, 0);
  analogWrite(In2, 0);
  analogWrite(In3, 255);
  analogWrite(In4, 0);
  
 }

 
void RightBackWard(int tocdo)
{
 analogWrite(In1, tocdo);
  analogWrite(In2, 0);
  analogWrite(In3, 0);
  analogWrite(In4, tocdo);
}
void LeftBackWard(int tocdo)
{
    analogWrite(In1, 0);
    analogWrite(In2, tocdo);
    analogWrite(In3, tocdo);
    analogWrite(In4, 0);
  
}
void loop() 
{
float a;
    
   radio.startListening();
  if ( radio.available()) 
  {
    while (radio.available()) 
       {
      
      for (int i=0;i<3;i++)
      {radio.read(&a, sizeof(a));
       
      delay(100);}
      
       }
    
  
  
  }
 
  Serial.print(" Roll = ");
  Serial.print(a);  
  
  Serial.println("");
      
      int roll=a;
      
      if (roll<-2.5)
     { Forward(255);
       delay(100);
       



     }
 if ((roll>2)&&(roll<5))
     { Backward(255);
       delay(100);
         
     }
 
 }


