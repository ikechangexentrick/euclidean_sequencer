#include "euclidean.h"
#include "button.h"
#include "7-segment.h"

#define SerialBaudRate (9600)

#undef NODEMCU
#define PRO_MICRO

//----------------------------------
		#ifdef PRO_MICRO

#define ICACHE_RAM_ATTR 

#define CLOCK_PIN (3) // 20

#define BUTTON_NEXT_PIN (8)
#define BUTTON_PREV_PIN (7)
#define BUTTON_SHIFT_PIN (9)

#define ROTARY_SW_1 (2) // 19
#define ROTARY_SW_2 (18)

#define LED_BEAT (21)

#define LATCH595_PIN (4)
#define DATA595_PIN (5)
#define CLOCK595_PIN (6)

		#endif // PRO_MICRO

//----------------------------------
		#ifdef NODEMCU

#define CLOCK_PIN (15)

#define BUTTON_NEXT_PIN (2)
#define BUTTON_PREV_PIN (12)
#define BUTTON_SHIFT_PIN ()

#define ROTARY_SW_1 (4) // for NodeMCU, GPIO3 is shared with RX, and won't be flashed if use it.
#define ROTARY_SW_2 (16)

#define LED_BEAT (13)

#define LATCH595_PIN (0)
/* for NodeMCU, GPIO9 (SD2) seems not to be used as an OUTPUT port..
   when "pinMode( 9, OUTPUT )", board seems go crazy..
*/
#define DATA595_PIN (14)
#define CLOCK595_PIN (5)

		#endif // NODEMCU
//----------------------------------


#define N_LENGTH (16)

volatile int cnt_beat;
volatile int n_beat;

#define LEN_HISTORY (8)
volatile int history[LEN_HISTORY];
volatile int idx_history;

SevenSegmentDisplay SLED(DATA595_PIN, CLOCK595_PIN, LATCH595_PIN);

volatile bool shift_pressed;
volatile int n_shift;

class Button_next : public Button
{
public:
	Button_next(int pin)
		: Button(pin)
	{}

private:
	virtual void onButton(int state) override
	{
		if (state == 1) {
			idx_history += 1;
			if (idx_history >= LEN_HISTORY) idx_history = LEN_HISTORY-1;
			n_beat = history[idx_history];

			SLED.on(n_beat);

			char buf[50];
  		snprintf(buf, 50, "Button_next::onButton: idx=%d, n_beat=%d", idx_history, n_beat);
  		Serial.println(buf);
		}
	}
};

class Button_prev : public Button
{
public:
	Button_prev(int pin)
		: Button(pin)
	{}

private:
	virtual void onButton(int state) override
	{
		if (state == 1) {
			idx_history -= 1;
			if (idx_history <= 0) idx_history = 0;
			n_beat = history[idx_history];

			SLED.on(n_beat);

			char buf[50];
  		snprintf(buf, 50, "Button_prev::onButton: idx=%d, n_beat=%d", idx_history, n_beat);
  		Serial.println(buf);
		}
	}
};

class Button_shift : public Button
{
public:
	Button_shift(int pin)
		: Button(pin)
	{}

private:
	virtual void onButton(int state) override
	{
		if (state == 1) {
			shift_pressed = false;

			char buf[64];
  		snprintf(buf, 64, "Button_shift::onButton: idx=%d, n_beat=%d, n_shift=%d", idx_history, n_beat, n_shift);
  		Serial.println(buf);
		} else {
			shift_pressed = true;
		}
	}
};

class RSW_cmd : public RotarySwitch
{
public:
	RSW_cmd(int pin_1, int pin_2)
		: RotarySwitch(pin_1, pin_2)
	{}

private:
	virtual void onRotarySW(RSW_DIR dir) override
	{
#ifdef PRO_MICRO
		if (dir == CW) {
#else // PRO_MICRO
		if (dir == CCW) {
#endif // PRO_MICRO
			if (shift_pressed) {
				if (n_shift == 0) return;	
				n_shift -= 1;
			} else {
				if (n_beat == 0) return;	
				n_beat -= 1;
			}
		} else { // CW for NodeMCU, CCW for Pro Micro
			if (shift_pressed) {
				if (n_shift == 15) return;	
				n_shift += 1;
			} else {
				if (n_beat == 16) return;	
				n_beat += 1;
			}
		}

		if (shift_pressed) {
			SLED.on(n_shift);
		} else {
			SLED.on(n_beat);
		}

		char buf[45];
		snprintf(buf, 45, "RotarySwitch::onRotarySW: %d n_beat=%d", dir, n_beat);
		Serial.println( buf );
	}
};


Button_prev button_2(BUTTON_PREV_PIN);
ICACHE_RAM_ATTR void onButton2Changed()
{
	button_2.callback();
}

RSW_cmd rsw1(ROTARY_SW_1, ROTARY_SW_2);
ICACHE_RAM_ATTR void onRotarySW1Changed()
{
	rsw1.callback();
}

Button_next button_1(BUTTON_NEXT_PIN);
Button_shift button_3(BUTTON_SHIFT_PIN);
#ifdef PRO_MICRO
ISR(PCINT0_vect)
{
	button_1.callback();
	button_3.callback();
}
#else // PRO_MICRO
ICACHE_RAM_ATTR void onButton1Changed()
{
	button_1.callback();
}
ICACHE_RAM_ATTR void onButton3Changed()
{
	button_3.callback();
}
#endif // PRO_MICRO

void setup() {
  Serial.begin(SerialBaudRate);

  pinMode(LED_BEAT, OUTPUT);

  pinMode(CLOCK_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(CLOCK_PIN), onClock, CHANGE);

  pinMode(BUTTON_PREV_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PREV_PIN), onButton2Changed, CHANGE);

  pinMode(BUTTON_NEXT_PIN, INPUT_PULLUP);
  pinMode(BUTTON_SHIFT_PIN, INPUT_PULLUP);
#ifdef PRO_MICRO
  pinMode(15, INPUT_PULLUP); // PB1
  pinMode(16, INPUT_PULLUP); // PB2
  pinMode(14, INPUT_PULLUP); // PB3
  pinMode(BUTTON_NEXT_PIN, INPUT_PULLUP); // PB4
  pinMode(BUTTON_SHIFT_PIN, INPUT_PULLUP); // PB5
  pinMode(10, INPUT_PULLUP); // PB5

	PCICR = 0;
	PCMSK0 = 
		1 << 4 // 8
		| 1 << 5 // 9
	;
	PCICR = 
		1 // PCIE0
	;

#else // PRO_MICRO
  attachInterrupt(digitalPinToInterrupt(BUTTON_NEXT_PIN), onButton1Changed, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BUTTON_SHIFT_PIN), onButton3Changed, CHANGE);
#endif // PRO_MICRO

  pinMode(ROTARY_SW_1, INPUT);
  pinMode(ROTARY_SW_2, INPUT);
  attachInterrupt(digitalPinToInterrupt(ROTARY_SW_1), onRotarySW1Changed, CHANGE);

	pinMode(CLOCK595_PIN, OUTPUT);
	pinMode(DATA595_PIN, OUTPUT);
	pinMode(LATCH595_PIN, OUTPUT);

	cnt_beat = 0;
	n_beat = 8;

	idx_history = 0;
	memset((void *)history, 0, LEN_HISTORY);
	history[0] = n_beat;

	n_shift = 0;
	shift_pressed = false;

	SLED.on(n_beat);
}

volatile int rhythm[N_LENGTH];

ICACHE_RAM_ATTR void onClock()
{
	if (digitalRead(CLOCK_PIN) == HIGH) {
		// rising edge

		if (cnt_beat >= N_LENGTH) {
			//* update pattern
			char buf[40];
			snprintf(buf, 40, "onClock: update: n_beat=%d n_shift=%d", n_beat, n_shift);
			Serial.println( buf );
			// */
			euclidean(n_beat, n_shift, (int *)rhythm);
			cnt_beat = 0;

			SLED.on(n_beat, true);

			// register to history if changed
			if (n_beat != history[idx_history]) {
				idx_history += 1;
				if (idx_history >= LEN_HISTORY) idx_history = LEN_HISTORY-1;
				history[idx_history] = n_beat;

				char buf[32];
				snprintf(buf, 32, "onClock: update: history[%d]=%d", idx_history, n_beat);
				Serial.println( buf );
			}
		}

		// output beat
		if (rhythm[cnt_beat]) digitalWrite(LED_BEAT, HIGH);
		else digitalWrite(LED_BEAT, LOW);
		cnt_beat += 1;

	} else {
		// falling edge
		digitalWrite(LED_BEAT, LOW);
		SLED.on(n_beat);
	}
}


void loop() {
		#ifdef PRO_MICRO
/*
	if (digitalRead(BUTTON_NEXT_PIN) == HIGH) onButton1Changed();
	else if (digitalRead(BUTTON_SHIFT_PIN) == HIGH) onButton3Changed();
*/
		#endif // PRO_MICRO

	if (shift_pressed) {
		SLED.on(n_shift);
	} else {
		SLED.on(n_beat);
	}
}
