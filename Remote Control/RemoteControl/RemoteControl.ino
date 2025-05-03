// From the desk of Lucas

#include <IRremote.h>  // Library IRemote required to read the infrared Control

// Var PINS 
int led_1 = 7; // LED green 
int led_2 = 6; // LED blue
int led_3 = 5; // LED white
int led_4 = 4; // LED red
int led_5 = 3; // start LED green
int RECV_PIN = 8; // Input Sensor

IRrecv irrecv(RECV_PIN); // criando a instância
decode_results results;
int delay_ms = 250;
int speed_1 = 50;
int speed_2 = 100;
int speed_3 = 150;
int speed_4 = 200;

// Vars to indicate the states of LEDS 
bool LED1 = false; 
bool LED2 = false;
bool LED3 = false; 
bool LED4 = false; 
bool LED5 = false;

// var configs
bool arrow_left = false;
bool arrow_right = false;
bool arrow_front = false;
bool arrow_back = false;

// Function begin 
void initOutPuts(){
    digitalWrite(led_1, HIGH);
    digitalWrite(led_2, HIGH);
    digitalWrite(led_3, HIGH);
    digitalWrite(led_4, HIGH);
    digitalWrite(led_5, LOW);
  }
  
// function to make the leds Blinks
void activeRelaysDelays(int speed_led){
     digitalWrite(led_4, HIGH); 
     delay(speed_led);
     digitalWrite(led_4, LOW);

     digitalWrite(led_3, HIGH); 
     delay(speed_led);
     digitalWrite(led_3, LOW);

     digitalWrite(led_2, HIGH); 
     delay(speed_led);
     digitalWrite(led_2, LOW);

     digitalWrite(led_1, HIGH); 
     delay(speed_led);
     digitalWrite(led_1, LOW); 
  }

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  pinMode(led_3, OUTPUT);
  pinMode(led_4, OUTPUT);
  pinMode(led_5, OUTPUT);
  initOutPuts();
}

// the loop function runs over and over again forever
void loop() {

  // Begin of code 
  results.value = 0;
  if (irrecv.decode(&results))             
  {
    Serial.println(results.value, HEX);     
    irrecv.resume();                        
    delay(10);                             
  }

  // Detecta o botao de ligar o geral 
  if(results.value == 0xFF02FD){
    LED5 = !LED5;
    digitalWrite(led_5, LED5);
    }
    
 // Reset wall pin 
  if(LED5 == false){
    initOutPuts();
    arrow_left = false;
    arrow_right = false; 
    arrow_front = false;
    arrow_back = false;
    }

  // Begin the program 
  if(LED5 == true){

  // set de var to opost value arrow_left
   if(results.value == 0xFF22DD){
      arrow_left = !arrow_left;
      arrow_right = false; 
      arrow_front = false;
      arrow_back = false;
    } 
    
   // set de var to opost value seta_diretia
   if(results.value == 0xFFC23D){
      arrow_right = !arrow_right;
      arrow_left = false;
      arrow_front = false;
      arrow_back = false;
    }
    
   // set de var to opost value arrow_front
   if(results.value == 0xFF629D){
      arrow_front = !arrow_front;
      arrow_back = false;
      arrow_right = false;
      arrow_left = false;
    }
    
   // set de var to opost value arrow_back
   if(results.value == 0xFFA857){
      arrow_back = !arrow_back;
      arrow_front = false;
      arrow_right = false;
      arrow_left = false;
    }

   if( ( arrow_left == false ) and ( arrow_right == false ) and ( arrow_front == false ) and ( arrow_back == false ) ){
    // case the wall button arre desatvate      
        if (results.value == 0xFF30CF)               
        {
          LED4 = !LED4;                                  
          digitalWrite(led_4, LED4); 
          delay(delay_ms);                                                     
        }
      
        if (results.value == 0xFFB04F)                 
        {
          LED3 = !LED3;                                 
          digitalWrite(led_3, LED3); 
          delay(delay_ms);                                                   
        }
      
        if (results.value == 0xFF9867)                 
        {
          LED2 = !LED2;                                  
          digitalWrite(led_2, LED2);   
          delay(delay_ms);                                                   
        }
      
        if (results.value == 0xFF6897)                  
        {
          LED1 = !LED1;                                
          digitalWrite(led_1, LED1);
          delay(delay_ms);                                                        
        }
    }

    // begin the piscas pisca
     if( ( arrow_left == true ) and ( arrow_right == false ) and ( arrow_front == false ) and ( arrow_back == false ) )
     {                                         
         activeRelaysDelays(speed_1);       
     }

    // begin the piscas pisca
     if( ( arrow_left == false ) and ( arrow_right == true ) and ( arrow_front == false ) and ( arrow_back == false ) )
     {                                         
         activeRelaysDelays(speed_2);   
     }

     // begin the piscas pisca
     if( ( arrow_left == false ) and ( arrow_right == false ) and ( arrow_front == true ) and ( arrow_back == false ) )
     {                                         
         activeRelaysDelays(speed_3);   
     }

    // begin the piscas piscas
     if( ( arrow_left == false ) and ( arrow_right == false ) and ( arrow_front == false ) and ( arrow_back == true ) )
     {                                         
         activeRelaysDelays(speed_4);   
     }

            
  } 
}
