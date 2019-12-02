
#define BUZZER 12 //the pin of the active buzzer

void setup()
{
 pinMode(BUZZER,OUTPUT);//initialize the buzzer pin as an output
}
void loop()
{
 unsigned char i;
   //output an frequency
   for(i=0;i<80;i++) {
    digitalWrite(BUZZER,HIGH);
    delay(1);//wait for 1ms
    digitalWrite(BUZZER,LOW);
    delay(1);//wait for 1ms
   }
    //output another frequency
   for(i=0;i<100;i++) {
     digitalWrite(BUZZER,HIGH);
     delay(2);//wait for 2ms
     digitalWrite(BUZZER,LOW);
     delay(2);//wait for 2ms
   }
} 
