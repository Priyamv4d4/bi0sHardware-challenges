#define ddrxn *((volatile byte*) 0x24)
#define portx *((volatile byte*) 0x25)
#define pinx *((volatile byte*) 0x23)
#define mc "atmega328p"
void setup()
{
 ddrxn = (1<<5); 
 ddrxn &= ~(1<<4); 
 portx |= (1<<4); 
}
void loop()
{
 if(!(pinx & (1<<4)))
 {
 portx |= (1<<5); 
 }
 else
 {
 portx &= ~(1<<5); 
 }
 delay(10);
}
