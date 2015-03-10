/* Interrupt on a button
 * By: Jeffrey Hundstad <we0a@arrl.net> 2015-03-09
 * Documentation on AttachInterrupt:
 *  http://arduino.cc/en/Reference/AttachInterrupt 
 *
 * Circuit:
 *   Internal builtin LED on LED_BUILTIN (usually pin-13)
 *   Momentary pushbutton between pin-2 and ground.  Pin-2 will be
 *     software selected to the internal pullup resistor to 5V.
 *
 * Description:
 *   This will demonstrate the use of interrupts and interrupt
 *   Service Routines (ISR).
 *
 *   1. The button will toggle the LED state.
 *   2. The state will only change when the button is pressed
 *      for at least PRESS_DELAY milliseconds, no sooner.
 *   3. It won't miss presses even if the LED is being updated
 *      in the loop() much slower than the number of presses.
 *
 * Try these:
 *   1. Change PRESS_DELAY to 2 seconds. What happens when you press
 *      the button more frequently than every 2 seconds?
 *   2. Uncomment the delay(5000), and change PRESS_DELAY back to
 *      100 milliseconds.   What happens if you press the button
 *      twice every 5 seconds?  How about three times?  Explain
 *      the results.
 *   3. Re-comment the delay(5000).  Slowly press and release
 *      the button.  Now change the interrupt mode to RISING.
 *      Again slowly press and release the button.
 *      What has changed?  Try setting it to CHANGE.  Now, what
 *      has changed?
 */

/* PIN definitions */
const byte led_pin = LED_BUILTIN;  // built in LED
const byte but_pin = 2;            // Button on pin-2, internal pullup

/* Volatile variables modified in the ISR */
volatile boolean led_state = LOW;
volatile unsigned int last_but_ptime = 0;

void setup()
{
  pinMode(led_pin, OUTPUT);
  pinMode(but_pin, INPUT_PULLUP);

  /*
   * attachInterrupt(interrupt, ISR, mode)
   *  interrupt = [0 == pin 2, 1 == pin 3]
   *  MODE = [LOW, CHANGE, RISING, FALLING]
   */
  attachInterrupt(0, blink, FALLING);
}

/* Show the led_state on the internal LED, it is changed in the ISR */
void loop()
{
  digitalWrite(led_pin, led_state);
  // delay(5000); /* 5 seconds */
}


/* Intended to be attached as an ISR */
/* Change the led_state but on as fast as PRESS_DELAY */
const unsigned int PRESS_DELAY = 100; /* milliseconds */
void blink()
{
  unsigned int but_ptime = millis();
  if ( (but_ptime - last_but_ptime) > PRESS_DELAY) {
    last_but_ptime = but_ptime;
    led_state = !led_state;
  }
}

