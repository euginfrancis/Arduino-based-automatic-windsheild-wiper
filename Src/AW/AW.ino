#include<LiquidCrystal.h>

#define LCD_RS 9
#define LCD_EN 8
#define LCD_D4 13
#define LCD_D5 12
#define LCD_D6 11
#define LCD_D7 10
#define SEN_MAX 150
#define MOTOR1 2 
#define MOTOR2 3

LiquidCrystal lcd(LCD_RS,LCD_EN,LCD_D4,
                      LCD_D5,LCD_D6,LCD_D7);

void setup()
{
  lcd.begin(16,2);
  lcd.print("Wiper Speed :");                                           
}
void loop()
{
 uint16_t sensor = analog();
    
 if(sensor > SEN_MAX) sensor = SEN_MAX;
    
 uint8_t motor_speed = sensor*10 / SEN_MAX ;
   
 lcd.setCursor(13,0);
 lcd.print(motor_speed);
    
 motor(motor_speed);
    
 delay(10);
}
uint16_t analog()
{
  int sen = 0;
  
  for(uint8_t i =0; i<10;i++)
    sen += analogRead(0);
  
  return (sen/10);
    
}
void motor(uint8_t spd)
{
  static uint8_t motor_state;
  
  if(spd)
  {
    motor_state ^= 1;
  
    if(motor_state)
    {
      digitalWrite(MOTOR1,HIGH);
      digitalWrite(MOTOR2,LOW);
     _delay_ms(1000);
    }else
      {
        digitalWrite(MOTOR1,LOW);
        digitalWrite(MOTOR2,HIGH);
        _delay_ms(1200);
      }
    
    
    digitalWrite(MOTOR1,LOW);
    digitalWrite(MOTOR2,LOW);
        
    for(uint8_t i =0; i<(10-spd) ; i++)
      _delay_ms(1000);
   }
}
