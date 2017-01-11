

/* 
 * Mon Jan  9 22:14:38 CET 2017
 * mayer 
 */ 

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h> // for usleep
#include <time.h>   // for nanosleep

int pin ; 
int count ; 


pulseonpin()
  {
    int i ; 
    printf ( "pulseonpin() %d %d \n", pin, count ) ; 

    pinMode(pin, OUTPUT); 
    for ( i=0; i<count; i++) { 
       digitalWrite(pin, HIGH); // Turn LED ON
       digitalWrite(pin, LOW); // Turn LED OFF
    } ; 
  } ; 

delayonpin()
  {
    struct timespec ts;
    ts.tv_sec = 0 ; 
    ts.tv_nsec = (long)count * 1000 ;
    printf ( "delayonpin() %d %d \n", pin, count ) ; 

    pinMode(pin, OUTPUT); 
    digitalWrite(pin, LOW); // Turn LED OFF
    nanosleep(&ts, NULL);
    digitalWrite(pin, HIGH); // Turn LED ON
  } ; 


int main ( int argc, char **argv )
{
  char option[100] ; 

  printf ("Banana Pi wiringPin program\n") ;

  if (wiringPiSetupGpio() == -1)
    exit (1) ;

  if ( argc > 3 ) 
      { 
        sscanf ( argv[1], "%s", &option ) ; 
        sscanf ( argv[2], "%d", &pin ) ; 
        sscanf ( argv[3], "%d", &count ) ; 
      }
    else 
      {
        printf ("usage: %s -i | -d  pin count \n", argv[0] ) ; 
        exit (1) ; 
      } ; 

  printf ("Using pin: %s %d %d \n", option, pin , count ) ; 
  // exit (0) ; 

  if ( option[1] == 'i' ) pulseonpin() ; 
  if ( option[1] == 'd' ) delayonpin() ; 

}

