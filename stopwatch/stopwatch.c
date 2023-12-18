
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Define global variables
 uint8_t stopwatch_sec = 0; // seconds counter
 uint8_t stopwatch_min = 0; // minutes counter
 uint8_t stopwatch_hour = 0; // hours counter
 uint8_t stopwatch_paused = 0; // flag to indicate stopwatch is paused

// Function to initialize Timer1 in CTC mode
void Timer1_CTC_Init() {

    TCNT1 = 0;		/* Set timer1 initial count to zero */

  	OCR1A = 1000;    /* Set the Compare value to 1000  */

  	TIMSK |= (1<<OCIE1A); /* Enable Timer1 Compare A Interrupt */

  	/* Configure timer control register TCCR1A
  	 * 1. Disconnect OC1A and OC1B  COM1A1=0 COM1A0=0 COM1B0=0 COM1B1=0
  	 * 2. FOC1A=1 FOC1B=0
  	 * 3. CTC Mode WGM10=0 WGM11=0 (Mode Number 4)
  	 */
  	TCCR1A = (1<<FOC1A);

  	/* Configure timer control register TCCR1B
  	 * 1. CTC Mode WGM12=1 WGM13=0 (Mode Number 4)
  	 * 2. Prescaler = F_CPU/1024 CS10=1 CS11=0 CS12=1
  	 */
  	TCCR1B = (1<<WGM12) | (1<<CS10)| (1<<CS12);
}
void enable_display(uint8_t display_index) {
  // Disable all displays first
  PORTA &= ~(0x3F); // Set PA0-PA5 low

  // Enable the desired display
  switch (display_index) {
    case 0:
      PORTA |= (1 << PA0); // Set PA0 high
      break;
    case 1:
      PORTA |= (1 << PA1); // Set PA1 high
      break;
    case 2:
      PORTA |= (1 << PA2); // Set PA2 high
      break;
    case 3:
      PORTA |= (1 << PA3); // Set PA3 high
      break;
    case 4:
      PORTA |= (1 << PA4); // Set PA4 high
      break;
    case 5:
      PORTA |= (1 << PA5); // Set PA5 high
      break;
    default:
      break;
  }
}
void display_digit(uint8_t n){
	PORTC = (PORTC & 0xF0) | (n & 0x0F);


}

// Function to display stopwatch time on 6 7-segment displays
void    display_stopwatch_time() {
  // Extract digits for display
  uint8_t sec2 = stopwatch_sec / 10;
  uint8_t sec1 = stopwatch_sec % 10;
  uint8_t min2 = stopwatch_min / 10;
  uint8_t min1 = stopwatch_min % 10;
  uint8_t hour2 = stopwatch_hour / 10;
  uint8_t hour1 = stopwatch_hour % 10;


  // enable and Display hours
  enable_display(0);
  display_digit(hour2); // Display tens digit of hours
  _delay_us(100);
  enable_display(1);
  display_digit(hour1); // Display units digit of hours
  _delay_us(100);

  // enable and Display minutes
  enable_display(2);
  display_digit(min2); // Display tens digit of minutes
  _delay_us(100);
  enable_display(3);
  display_digit(min1); // Display units digit of minutes
  _delay_us(100);

  // enable and Display seconds
  enable_display(4);
  display_digit(sec2); // Display tens digit of seconds
  _delay_us(100);
  enable_display(5);
  display_digit(sec1); // Display units digit of seconds
  _delay_us(100);
}


// Interrupt service routine for Timer1 compare match
ISR(TIMER1_COMPA_vect) {
	 if (!stopwatch_paused) {
   stopwatch_sec++;    // Increment seconds

    if (stopwatch_sec >= 60) {
      stopwatch_sec = 0; // Reset seconds
      stopwatch_min++;   // Increment minutes

      if (stopwatch_min >= 60) {
        stopwatch_min = 0; // Reset minutes
        stopwatch_hour++;  // Increment hours

        if (stopwatch_hour >= 24) {
          stopwatch_hour = 0; // Reset hours
        }
        }
      }
    }

    display_stopwatch_time(); // Update the stopwatch display
  }


// Interrupt service routine for external interrupt INT1
ISR(INT1_vect) {
  stopwatch_paused = 1; // Set stopwatch paused flag

}

// Interrupt service routine for external interrupt INT2
ISR(INT2_vect) {
  stopwatch_paused = 0; // Clear stopwatch paused flag

}
ISR(INT0_vect) {
	  stopwatch_sec = 0;     // Reset seconds counter
	  stopwatch_min = 0;     // Reset minutes counter
	  stopwatch_hour = 0;    // Reset hours counter
	  stopwatch_paused = 0;  // Clear paused flag
	  display_stopwatch_time(); // Update the stopwatch display
}

// Function to initialize external interrupt INT1
void INT2_Init(void)
{
	DDRB   &= (~(1<<PB2));   // Configure INT2/PB2 as input pin
	MCUCSR &= ~(1<<ISC2);     // Trigger INT2 with the falling edge
	GICR   |= (1<<INT2);	 // Enable external interrupt pin INT2

}
void INT1_Init(void)
{
	DDRD  &= (~(1<<PD3));  // Configure INT1/PD3 as input pin
	// Trigger INT1 with the raising edge
	MCUCR |= (1<<ISC10) | (1<<ISC11);
	GICR  |= (1<<INT1);    // Enable external interrupt pin INT1

}
void INT0_Init(void)
{
	DDRD  &= (~(1<<PD2));               // Configure INT0/PD2 as input pin
	// Trigger INT0 with the FALLING edge
	MCUCR |= (1<<ISC01);
	MCUCR &= ~(1<<ISC00);
	GICR  |= (1<<INT0);                 // Enable external interrupt pin INT0

}


int main(void){


  DDRA |= 0x3F; //OutPut Pins A0 --> A5
  DDRC |= 0x0F ; //OutPut Pins C0 --> C3
	/*Initialization Values*/

  PORTC &= 0xF0; //7-segment displays 0 as initial value
  PORTA |=0x3F;
	  // Enable internal pull-up resistor for INT0 and INT2
  PORTD |= (1 << PD2) ;
  PORTB |= (1 << PB2);
  // Initialize Timer1
  Timer1_CTC_Init();

  // Initialize external interrupts INT1, INT1 and INT2
  INT0_Init();
  INT1_Init();
  INT2_Init();
  SREG |= (1<<7); /* Enable global interrupts in MC */



  // Main loop
  while (1) {
	  display_stopwatch_time();
  }

  }
































































































































































































































































































































































































































































































































































































































































































































































































































































