#include "euclidean.h"

#define SerialBaudRate (9600)

#define BUTTON_INTERVAL_THRESHOLD (20)
#define ROTARY_SW_INTERVAL_THRESHOLD (20)

#define CLOCK_PIN (15)

#define BUTTON_PIN (2)
#define BUTTON_CLEAR (12)

#define ROTARY_SW_1 (4) // for NodeMCU, GPIO3 is shared with RX, and won't be flashed if use it.
#define ROTARY_SW_2 (16)

#define LED_BEAT (13)

#define N_LENGTH (16)

int cnt_beat;
int n_beat;


class Button
{
public:
	Button(int pin)
		:	pin(pin), state_prev(true)
	{
		t_prev = millis();
	}

	virtual ~Button() = default;

	virtual void onButton(int state)
	{
		char buf[32];
  	snprintf(buf, 32, "Button::onButton(%d): %d", pin, state);
  	Serial.println(buf);
	}

	void callback()
	{
		unsigned long cur = millis();
		if (cur - t_prev < BUTTON_INTERVAL_THRESHOLD) return;

		bool state = digitalRead(pin);
		if (state != state_prev) {
			state_prev = state;
			t_prev = cur;
			onButton(state);
		}
	}

private:
	const int pin;
	volatile unsigned long t_prev;
	volatile bool state_prev;
};

class RotarySwitch
{
public:
	enum RSW_DIR {
		CW, CCW
	};

	RotarySwitch(int pin_1, int pin_2)
		: pin_1(pin_1), pin_2(pin_2)
		, prev_state_1(0), prev_state_2(0)
	{}

	virtual void onRotarySW(RSW_DIR dir)
	{
		if (dir == CCW) {
			if (n_beat == 0) return;	
			n_beat -= 1;
		} else { // CW
			if (n_beat == 16) return;	
			n_beat += 1;
		}

		char buf[45];
		snprintf(buf, 45, "RotarySwitch::onRotarySW: %d n_beat=%d", dir, n_beat);
		Serial.println( buf );
	}

	void callback()
	{
		bool state_1 = digitalRead(pin_1);
		bool state_2 = digitalRead(pin_2);

		if (prev_state_1 != state_1) {
			prev_state_1 = state_1;
			prev_state_2 = state_2;

			if (state_1 == 0) {
				if (state_1 == state_2) onRotarySW(CCW);
				else onRotarySW(CW);
			}
		}
	}

private:
	const int pin_1, pin_2;
	volatile int prev_state_1;
	volatile int prev_state_2;
};


#define LEN_HISTORY (8)
int history[LEN_HISTORY];
int idx_history;

class Button_next : public Button
{
public:
	Button_next(int pin)
		: Button(pin)
	{}

	virtual void onButton(int state) override
	{
		if (state == 1) {
			idx_history += 1;
			if (idx_history >= LEN_HISTORY) idx_history = LEN_HISTORY-1;
			n_beat = history[idx_history];

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

	virtual void onButton(int state) override
	{
		if (state == 1) {
			idx_history -= 1;
			if (idx_history <= 0) idx_history = 0;
			n_beat = history[idx_history];

			char buf[50];
  		snprintf(buf, 50, "Button_prev::onButton: idx=%d, n_beat=%d", idx_history, n_beat);
  		Serial.println(buf);
		}
	}
};

Button_next button_1(BUTTON_PIN);
ICACHE_RAM_ATTR void onButton1Changed()
{
	button_1.callback();
}

Button_prev button_2(BUTTON_CLEAR);
ICACHE_RAM_ATTR void onButton2Changed()
{
	button_2.callback();
}

RotarySwitch rsw1(ROTARY_SW_1, ROTARY_SW_2);
ICACHE_RAM_ATTR void onRotarySW1Changed()
{
	rsw1.callback();
}

void setup() {
  Serial.begin(SerialBaudRate);

  pinMode(LED_BEAT, OUTPUT);

  pinMode(CLOCK_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(CLOCK_PIN), onClock, CHANGE);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), onButton1Changed, CHANGE);

  pinMode(BUTTON_CLEAR, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_CLEAR), onButton2Changed, CHANGE);

  pinMode(ROTARY_SW_1, INPUT);
  pinMode(ROTARY_SW_2, INPUT);
  attachInterrupt(digitalPinToInterrupt(ROTARY_SW_1), onRotarySW1Changed, CHANGE);

	cnt_beat = 0;
	n_beat = 8;

	idx_history = 0;
	memset(history, 0, LEN_HISTORY);
	history[0] = n_beat;
}

int rhythm[N_LENGTH];

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
			euclidean(n_beat, rhythm);
			cnt_beat = 0;

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
	}
}


void loop() {
/*
	unsigned int cur = millis();
	int v0 = analogRead(0);
	int delayValue = 
		//(0.5e3 - 0.2e3)/(1023 - 0) * v0 + 30
		0.17e3 - 0.08e3/1024 * v0
	;
*/

/*
	Serial.print( "val: ");
	Serial.print( v0 );
	Serial.print( " freq: ");
	float freq = 1e3/((float)cur-(float)t_prev)/4;
	Serial.print( freq, 1 );
	Serial.print( " bpm: ");
	Serial.print( freq*60, 1 );
	t_prev = cur;
// */
}
