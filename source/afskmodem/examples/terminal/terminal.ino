#include  <AudioModem.h> 
#include  <ctype.h> 

AudioModem modem; 

void setup () 
{ 
  Serial.begin(57600); 
  delay(1000); 
  modem.begin (); 
}

// Reverses the order of bits in a byte. 
// I.e. MSB is swapped with LSB, etc. 
unsigned char Bit_Reverse( unsigned char x ) 
{ 
    x = ((x >> 1) & 0x55) | ((x << 1) & 0xaa); 
    x = ((x >> 2) & 0x33) | ((x << 2) & 0xcc); 
    x = ((x >> 4) & 0x0f) | ((x << 4) & 0xf0); 
    return x;    
}

void loop () 
{ 
  while ( modem . available ()) { 
    unsigned char c = modem . read (); 
    c = Bit_Reverse(c);
    if ( isprint ( c )) { 
      Serial . println (( char ) c ); 
    } 
    else { 
      Serial . print ( "(" ); 
      Serial . print ( c , HEX ); 
      Serial . println ( ")" );       
    } 
  } 
  if ( Serial . available ()) { 
    modem . write ( 0xff ); 
    while ( Serial . available ()) { 
      char c =  Serial . read (); 
      modem . write ( c ); 
    } 
  } 
}
