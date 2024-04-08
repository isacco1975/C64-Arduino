/*
 **********************************************************************
 * Name:    Telegraph.ino                                             *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  *
 * Created: 05.04.2024 10:01:49                                       *
 * Author:  Isaac Garcia Peveri                                       *
 *          isacco1975gp@gmail.com                                    *
 *          compatible with BASIC V2 (c64) and AmigaBasic             *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  *
 **********************************************************************
*/

#pragma region "Working-Storage"
const int PUSH_BUTTON = 7;
const int BUZZER_PIN = 3;
byte buttonValue;
#pragma endregion

void setup()
{  
   Serial.begin(1200);
   pinMode(BUZZER_PIN, OUTPUT);
   pinMode(PUSH_BUTTON, INPUT);
}

///
/// Reading Loop
///
void loop()
{
   int startTime = 0;
   int startTime2 = 0;
   int endTime = 0;
   int endTime2 = 0;
   int diffTime = 0;
   int diffTime2 = 0;
   bool isStartSignal = false;
   
   buttonValue = digitalRead(PUSH_BUTTON); 
   startTime2 = millis();
   
   if (buttonValue == 0)
   {
       startTime = millis(); 
   }
   
   while (buttonValue == 0)
   {
      tone(BUZZER_PIN, 600);
      //digitalWrite(LED_PIN, HIGH);  
      endTime = 0;    
      buttonValue = digitalRead(PUSH_BUTTON); 

      if (buttonValue != 0) 
      {
         endTime = millis();  
         diffTime = endTime - startTime; 
         exit;
      }
   }

   if (diffTime > 0 && diffTime >= 110)
   {
      isStartSignal = true;
      Serial.println("-");
   } 
   else
   {
     if (diffTime > 0 && diffTime < 110)
     {
        isStartSignal = true;
        Serial.println(".");
     } 
   }     

   endTime2 = millis();  
   diffTime2 = endTime2 - startTime; 

   if (isStartSignal && diffTime2 > 250)
   {
      Serial.println("#");
      isStartSignal = false;
   } 

   noTone(BUZZER_PIN);
 
   delay(20);
}
