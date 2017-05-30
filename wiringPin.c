

/* 
 * Mon Jan  9 22:14:38 CET 2017 - initial 
 * mayer 
   Mon Feb 13 21:07:31 CET 2017 - add 8% more pulses  
   Tue May 30 21:42:56 CEST 2017 - calculate seconds too 
 */ 

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h> // for usleep
#include <time.h>   // for nanosleep

#define VERSION "1.2" 

int pin ; 	// is the BCM numbering and NOT the physical 
int count ; 	// number of pulses to insert or delay in usec 


// insert count pulses in the given pin 
pulseonpin()
  {
    int i ; 
    int newcount  ;  /* about 8 % more than we really should do   
    	 	obviously some pulses are lost */ 
    newcount = (int)(1.08 * (float)count) ; 
    printf ( "pulseonpin() %d %d \n", pin, newcount ) ; 

    pinMode(pin, OUTPUT); 
    for ( i=0; i<newcount; i++) { 
       digitalWrite(pin, HIGH); // Turn LED ON
       digitalWrite(pin, LOW); // Turn LED OFF
    } ; 
  } ; 

// delay for count micro-seconds 
delayonpin()
  {
    struct timespec ts;
    long count1000 ; 

    // we need about 100 till 200 usec for down and up 
    // therefore do nothing for values below 100
    if ( count <= 100 ) 
      {
        printf ( "delayonpin() delay %d <= 100 - exit \n", count ) ; 
        exit (1) ; 
      } ; 
    // and subtract 100 usec for values above 
    count -= 100 ; 
    count1000 = (long)count * 1000 ; 
    ts.tv_sec = count / (long)1000000 ; 
    ts.tv_nsec = count1000 % (long)1000000000 ;
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

  // printf ( "argc : %d \n" , argc ) ; 
  if ( argc == 4 ) 
      { 
        sscanf ( argv[1], "%s", &option ) ; 
        sscanf ( argv[2], "%d", &pin ) ; 
        sscanf ( argv[3], "%d", &count ) ; 
      }
    else 
      {
        // printf ( "argc : %d \n" , argc ) ; 
        if ( argc == 2 ) 
          { 
            sscanf ( argv[1], "%s", &option ) ; 
            if ( option[1] == 'v' ) printf ( " %s - version %s\n", argv[0], VERSION ) ; 
            exit (1) ; 
	  }
          else 
          {
            printf ("usage: %s -i | -d  pin count \n", argv[0] ) ; 
            printf ("          -v    ( show version )  \n" ) ; 
            exit (1) ; 
	  } ; 
      } ; 

  printf ("Using pin: %s %d %d \n", option, pin , count ) ; 
  // exit (0) ; 

  if ( option[1] == 'i' ) pulseonpin() ; 
  if ( option[1] == 'd' ) delayonpin() ; 

}

