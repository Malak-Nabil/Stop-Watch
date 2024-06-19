#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define PORTA_PINS 6 //First six pins in PORTA (enable/disable pins)
int units_of_time[] = {0, 0, 0, 0, 0, 0};
/*
units_of_time[0] for seconds(1)
units_of_time[1] for seconds(2)
units_of_time[2] for minutes(1)
units_of_time[3] for minutes(2)
units_of_time[4] for hours(1)
units_of_time[5] for hours(2)
*/
unsigned char seconds = 0;

//Reset time function
void ResetTimer(void) {
    // Stop the timer
    TCCR1B = 0;
    // Reset the count register
    TCNT1 = 0;
    // Restart the timer with the desired settings
    TCCR1B |= (1 << CS11) | (1 << CS10) | (1 << WGM12); // Prescaler 64 and CTC mode
}


// Timer 1 Interrupt Service Routine
ISR(TIMER1_COMPA_vect){
	seconds++;
	units_of_time[0]++;          //increment seconds(1)
	if(seconds==60)              //checks every 60 seconds to increment minutes(1)
	{
		ResetTimer();
		units_of_time[0]=0;      //set seconds(1) with 0
		units_of_time[1]=0;	   	 //set seconds(2) with 0
		units_of_time[2]++;	     //increment minutes(1)

		seconds=0;
	}

}

//configuring Timer1 in compare mode
void Timer1(void)
{

	    // Initialize the Timer counter to zero
		TCNT1 = 0;

	    // Configure Timer Control Register A (TCCR1A) to zeros (no effect on timer operation)
		TCCR1A = 0;

		 // Prescaler 64 and CTC mode
		TCCR1B |= (1 << CS11) | (1 << CS10) | (1 << WGM12);

	    // Enable the Timer/Counter1 Output Compare A Match interrupt
		TIMSK |= (1 << OCIE1A);

	    // Set the Output Compare Register A (OCR1A) to 15624
	    // This value determines the timer's counting range, which is set to 1 second
		OCR1A = 15624;

	    // Enable global interrupts by setting the I-bit in the Status Register (SREG)
		sei();

}

// External INT0 Interrupt Service Routine
ISR(INT0_vect)
{
	ResetTimer();
	for (int i = 0; i < PORTA_PINS; i++)
	{
	        units_of_time[i] = 0;            //reset the enables
	  }

}


//External INT0 enable and configuration function
void INT0_Init(void)
{

	DDRD  &= (~(1<<PD2));     			     // Configure INT0/PD2 as input pin
	PORTD |=(1<<PD2);						 // activate internal pull-up resistor
	GICR |= (1<<INT0);       			     // Enable external interrupt pin INT0
	MCUCR |= (1<<ISC01);                     // Trigger INT0 with the falling edge
	sei();                                   // Enable interrupts by setting I-bit

}

// External INT1 Interrupt Service Routine
ISR(INT1_vect)
{
	 TCCR1B = 0;                             //stop the timer

}

// External INT1 enable and configuration function
void INT1_Init(void)
{

	DDRD  &= (~(1<<PD3));                    // Configure INT1/PD3 as input pin
	GICR |= (1<<INT1);                       // Enable external interrupt pin INT1
	MCUCR |= (1<<ISC11) | (1<<ISC10);        // Trigger INT0 with the rising edge
	sei();			                         // Enable interrupts by setting I-bit

}

// External INT2 Interrupt Service Routine
ISR(INT2_vect)
{
	 // Resume the timer
	TCCR1B |= (1 << CS11) | (1 << CS10) | (1 << WGM12);

	 // Re-enable the timer interrupt
	TIMSK |= (1 << OCIE1A);

}

//External INT2 enable and configuration function
void INT2_Init(void)
{
	DDRB &= (~(1<<PB2));                     // Configure INT2/PB2 as input pin
	PORTB |=(1<<PB2);						 // activate internal pull-up resistor
	GICR |= (1<<INT2);                       // Enable external interrupt pin INT2
	MCUCR &= ~(1<<ISC2);                     // Trigger INT2 with the falling edge
	sei();	                                 // Enable interrupts by setting I-bit

}


/* This function displays the time units (hours, minutes, and seconds) stored in
 * the `units_of_time` array on a 7-segment display. It also updates the time
 * values and handles roll overs when a time unit reaches its maximum value.
 */
void display_digit(void)
{
	for (int i=0;i<PORTA_PINS;i++){

		PORTC=(PORTC & (1<<0xF0)) | (units_of_time[i] & 0x0F);
		PORTA |=(1<<i);      // Enable the corresponding 7-segment digit
		_delay_ms(2);        // Delay to display the digit
		PORTA &=~(1<<i);     // Disable the 7-segment digit after displaying
	}

	 // Check if the first seconds digit has reached 10
	if (units_of_time[0]== 10)
	{
		units_of_time[0] = 0;   // Reset the first seconds digit
		units_of_time[1]++;     // Increment the second seconds digit
	}

	// Check if the first minutes digit has reached 10
	if(units_of_time[2]== 10)
	{
		units_of_time[2] = 0;   // Reset the first minutes digit
		units_of_time[3]++;     // Increment the second minutes digit
	}

	// Check if the second minutes digit has reached 6 (60 minutes)
	if(units_of_time[3]==6)
	{
		units_of_time[3] = 0;   // Reset the second minutes digit
		units_of_time[4]++;     // Increment the first hours digit
	}

	// Check if the first hours digit has reached 10
	if(units_of_time[4]==9)
	{
		units_of_time[4] = 0;  // Reset the first hours digit
		units_of_time[5]++;    // Increment the second hours digit
	}

	// Check if the second hours digit has reached 10 (99 hours)
	if(units_of_time[5]==9)
	{
		 // Reset all digits to 0 for new hours
		for (int i=0;i<PORTA_PINS;i++)
		{

			units_of_time[i]=0;
		}
	}


}

int main(void)
{

	//enabling/disabling six 7 segment
	DDRA |= 0x3F; //Configure first six pins in PORTA as outputs pins
	PORTA &= 0xC0; //Set first six pins in PORTA with value 0 at the beginning(disabled)


	//Decoder pins
	DDRC |= 0x0F; // Configure first four pins of PORTC as output pins
	PORTC &= 0xF0; // initialize the 7-segment with value 0 by clear the first four bits in PORTC


	//Interrupt0 (reset) push button pin
	DDRD &=~ (1<<PD2); // Configure PD2 in PORTD as input pin


	//Interrupt1 (stop) push button pin
	DDRD &=~ (1<<PD3); // Configure PD3 in PORTD as input pin

	//Interrupt2 (resume) push button pin
	DDRB &=~ (1<<PB2); // Configure PB2 in PORTB as input pin



	INT0_Init();     //reset function

	INT1_Init();     //stop function

	INT2_Init();     //resume function

	Timer1();


	while(1)
	{
		display_digit(); //display digits on 7 segment


	}

	return 0;
}
