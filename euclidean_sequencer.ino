#include "euclidean.h"
#include "button.h"
#include "7-segment.h"

#define SerialBaudRate (9600)

#define CLOCK_PIN (15)

#define BUTTON_NEXT_PIN (2)
#define BUTTON_PREV_PIN (12)

#define ROTARY_SW_1 (4) // for NodeMCU, GPIO3 is shared with RX, and won't be flashed if use it.
#define ROTARY_SW_2 (16)

#define LED_BEAT (13)

#define N_LENGTH (16)

#define LATCH595_PIN (0)
/* for NodeMCU, GPIO9 (SD2) seems not to be used as an OUTPUT port..
   when "pinMode( 9, OUTPUT )", board seems go crazy..
*/
#define DATA595_PIN (14)
#define CLOCK595_PIN (5)

volatile int cnt_beat;
volatile int n_beat;

#define LEN_HISTORY (8)
volatile int history[LEN_HISTORY];
volatile int idx_history;

SevenSegmentDisplay SLED(DATA595_PIN, CLOCK595_PIN, LATCH595_PIN);

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

class RSW_cmd : public RotarySwitch
{
public:
	RSW_cmd(int pin_1, int pin_2)
		: RotarySwitch(pin_1, pin_2)
	{}

private:
	virtual void onRotarySW(RSW_DIR dir) override
	{
		if (dir == CCW) {
			if (n_beat == 0) return;	
			n_beat -= 1;
		} else { // CW
			if (n_beat == 16) return;	
			n_beat += 1;
		}

		SLED.on(n_beat);

		char buf[45];
		snprintf(buf, 45, "RotarySwitch::onRotarySW: %d n_beat=%d", dir, n_beat);
		Serial.println( buf );
	}
};


Button_next button_1(BUTTON_NEXT_PIN);
ICACHE_RAM_ATTR void onButton1Changed()
{
	button_1.callback();
}

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

void setup() {
  Serial.begin(SerialBaudRate);

  pinMode(LED_BEAT, OUTPUT);

  pinMode(CLOCK_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(CLOCK_PIN), onClock, CHANGE);

  pinMode(BUTTON_NEXT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_NEXT_PIN), onButton1Changed, CHANGE);

  pinMode(BUTTON_PREV_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PREV_PIN), onButton2Changed, CHANGE);

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

	SLED.on(n_beat);
}

volatile int rhythm[N_LENGTH];

ICACHE_RAM_ATTR void onClock()
{
	if (digitalRead(CLOCK_PIN) == HIGH) {
		// rising edge

		if (cnt_beat >= N_LENGTH) {
			//* update pattern
			char buf[32];
			snprintf(buf, 32, "onClock: update: n_beat=%d", n_beat);
			Serial.println( buf );
			// */
			euclidean(n_beat, (int *)rhythm);
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
}
