
#include "button.h"
#include "Display_OLED.h"

#include "euclidean.h"

static const int SERIAL_BAUD_RATE = 9600;

static const size_t BUFLEN = 64;
char msg_buf[BUFLEN];

template <typename... Args>
void serial_log(const char *fmt, Args... args)
{
	snprintf(msg_buf, BUFLEN, fmt, args...);
	Serial.println( msg_buf );
}

//  -----------------------------------------------

//static const int PIN_RANDOM_SEED = 21; // A3
static const int PIN_CV_SFT = 20; // A2
static const int PIN_CV_NUM = 19; // A1
static const int PIN_CV_LEN = 18; // A0
static const int PIN_CV_SELECT = 21; // A3

static const int PIN_ROTARY_SW1 = 10; // pin change interrupt
static const int PIN_ROTARY_SW2 = 6;
static const int PIN_BUTTON = 9; // pin change interrupt
static const int PIN_CLOCK = 7; // attachInterrupt

static const int LED_BEAT = 5;

//bool only_for_develop = true;

//  -----------------------------------------------

Display_OLED display;

//  -----------------------------------------------

class App {
public:
	static constexpr const size_t SEQ_MAX_LEN = 32;

	struct Param {
		size_t len = 8;
		size_t num = 8;
		size_t sft = 0;
	};

	// current parameters
	Param *get_params(size_t i) {
		return &params[i];
	}
	size_t get_len() const {
		return params[pidx].len;
	}
	size_t get_num() const {
		return params[pidx].num;
	}
	size_t get_sft() const {
		return params[pidx].sft;
	}
	size_t get_idx() const {
		return pidx;
	}

	// parameters to be used next/manipulated by UI
	size_t get_next_idx() const {
		return (nidx
			+ (size_t)((float)MAX_PARAM_NUM*(float)cv.select/1024.0)
			) % MAX_PARAM_NUM
		;
	}

	// CV controls length from 0 to 2xlen, with len for 0V.
	size_t get_next_len() const {
		size_t v = (float)nexts[get_next_idx()].len
			*(1.0+(float)((int)cv.len-480)/480.0) // 0 - 480 - 1009
		;

		if (v >= SEQ_MAX_LEN) return SEQ_MAX_LEN;
		else if (v < 0) return 0;
		else return v;
	}

	// returns next parameters modulated by using CV inputs.
	Param get_next_param() const;

	// set the next parameters to the current ones
	void update_param();


	// UI handlers
	void onRotarySW(RotarySwitch::RSW_DIR);
	void onButton(int);

	enum class Mode {
		Length = 0,
		Number,
		Shift,
		List,
		Mode_Max
	};

	Mode get_mode() const {
		return mode;
	}

	static const size_t constexpr MAX_PARAM_NUM = 4;

	void set_cv(int len, int num, int sft, int select);

private:
	Param params[MAX_PARAM_NUM];
	Param nexts[MAX_PARAM_NUM];

	size_t pidx = 0;
	size_t nidx = 0;

	struct CV {
		unsigned int len = 512;
		unsigned int num = 512;
		unsigned int sft = 512;
		unsigned int select = 512;
	};

	CV cv;

	Mode mode = Mode::Length;
};

void App::onRotarySW(RotarySwitch::RSW_DIR dir) {
	// here we use nidx, instead of get_next_idx()
	// to avoid interference between UI and CV.
	auto &next = nexts[nidx];

	if (mode == Mode::Length) {
		auto &target = next.len;
		if (dir == RotarySwitch::CCW) {
			if (target < SEQ_MAX_LEN-1) target += 1;
		} else {
			if (target > 0) target -= 1;
		}

		if (next.num > target) next.num = target;
		if (next.sft > target) next.sft = target;

	} else if (mode == Mode::Number) {
		auto &target = next.num;
		if (dir == RotarySwitch::CCW) {
			if (target < next.len) target += 1;
		} else {
			if (target > 0) target -= 1;
		}
	} else if (mode == Mode::Shift) {
		auto &target = next.sft;
		if (dir == RotarySwitch::CCW) {
			if (target < next.len) target += 1;
		} else {
			if (target > 0) target -= 1;
		}
	} else {
		if (dir == RotarySwitch::CCW) {
			if (nidx < MAX_PARAM_NUM-1) nidx += 1;
		} else {
			if (nidx > 0) nidx -= 1;
		}
	}
}

void App::onButton(int state) {
	if (state == 1) {
		mode = (Mode)((int)mode + 1);
		if (mode == Mode::Mode_Max) mode = Mode::Length;
	}
}

void App::set_cv(int len, int num, int sft, int select) {
	//serial_log("%d %d %d %d", len, num, sft, select);
	cv.len = len;
	cv.num = num;
	cv.sft = sft;
	cv.select = select;
}

void App::update_param() {
	memcpy(params, nexts, sizeof(params));
	pidx = get_next_idx();
}

/*
                      get_next_param
                      ^
[rotary]->[nexts]--+-----==============--> [param]
[cv]---------------^     (update_param)
*/

// returns next parameters modulated by using CV inputs.
App::Param App::get_next_param() const {
	Param ret;
	auto idx = get_next_idx();
	ret.len = get_next_len();

/*
	serial_log("%d+%d %d+%d %d+%d %d+%d(%d)"
			, (int)nexts[idx].len, (int)(1.0+(float)((int)cv.len-480)/480.0)
			, (int)nexts[idx].num, (int)((float)((int)cv.num-480)/480.0*ret.len)
			, (int)nexts[idx].sft, (int)((float)((int)cv.sft-480)/480.0*ret.len)
			, nidx, (int)((float)MAX_PARAM_NUM*(float)cv.select/1009.0), cv.select
	);
// */

	{
		size_t v = (int)nexts[idx].num
			+ (int)((float)((int)cv.num-480)/480.0*ret.len)
		;

		if (v >= ret.len) ret.num = ret.len;
		else if (v < 0) ret.num = 0;
		else ret.num = v;
	}

	{
		size_t v = (int)nexts[idx].sft
			+ (int)((float)((int)cv.sft-480)/480.0*ret.len)
		;

		if (v >= ret.len) ret.sft = ret.len;
		else if (v < 0) ret.sft = 0;
		else ret.sft = v;
	}

	return ret;
}

App application;
App *app = &application;

//  -----------------------------------------------

volatile int sequence[App::SEQ_MAX_LEN];
volatile size_t seq_idx = 0;

//  -----------------------------------------------

class RSW_cmd : public RotarySwitch
{
public:
	RSW_cmd(int pin_1, int pin_2)
		: RotarySwitch(pin_1, pin_2)
	{}

private:
	virtual void onRotarySW(RSW_DIR dir) override
	{
		if (app) app->onRotarySW(dir);
	}
};

RSW_cmd rsw1(PIN_ROTARY_SW1, PIN_ROTARY_SW2);

//  -----------------------------------------------

class Button_func : public Button
{
public:
	Button_func(int pin)
		: Button(pin)
	{}

private:
	virtual void onButton(int state) override
	{
		if (app) app->onButton(state);
	}
};

Button_func button_1(PIN_BUTTON);

//  -----------------------------------------------

ISR(PCINT0_vect)
{
	button_1.callback();
	rsw1.callback();
}

void onClock()
{
	//serial_log("onClock:");
	int clock = digitalRead(PIN_CLOCK);

/*
	const auto n_len = app->get_next_len();
	const auto n_beat = app->get_next_num();
	const auto n_shift = app->get_next_sft();
	display.show_status("len:%2d num:%2d sft:%2d", n_len, n_beat, n_shift);
*/

	if (/*only_for_develop*/clock == HIGH) {
		// rising edge

		const auto cur_len = app->get_len();
		if (++seq_idx >= cur_len) {
			seq_idx = 0;

			// update parameters with temporal (next_*) ones
			app->update_param();

			// update sequence using new parameters
/*
			const auto n_len = app->get_len();
			const auto n_beat = app->get_num();
			const auto n_shift = app->get_sft();
			euclidean(n_beat, n_shift, (int *)sequence, n_len);
*/
//*
			const auto p = app->get_next_param();
			euclidean(p.num, p.sft, (int *)sequence, p.len);
// */
		}

		// output beat
		if (sequence[seq_idx]) digitalWrite(LED_BEAT, HIGH);
		else digitalWrite(LED_BEAT, LOW);

	} else {
		// falling edge
		digitalWrite(LED_BEAT, LOW);

	}

}

//  -----------------------------------------------

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);

	pinMode(LED_BEAT, OUTPUT);

	//randomSeed(analogRead(PIN_RANDOM_SEED));

	pinMode(PIN_CV_LEN, INPUT);
	pinMode(PIN_CV_NUM, INPUT);
	pinMode(PIN_CV_SFT, INPUT);
	pinMode(PIN_CV_SELECT, INPUT);

	pinMode(PIN_ROTARY_SW1, INPUT);
	pinMode(PIN_ROTARY_SW2, INPUT);

	pinMode(PIN_CLOCK, INPUT);
	attachInterrupt(digitalPinToInterrupt(PIN_CLOCK), onClock, CHANGE);

	pinMode(PIN_BUTTON, INPUT_PULLUP);

	PCICR = 0;
	PCMSK0 = 
		1 << 5 // 9
		| 1 << 6 // 10
	;
	PCICR = 
		1 // PCIE0
	;

	SPI.begin();

	display.init();
}

void show_graph(const int *arr, size_t len, size_t current)
{
	static constexpr const size_t MERGIN = 2; // pixel
	static constexpr const auto top = 0+Display_OLED::TEXT_HEIGHT*2 + MERGIN;
	static constexpr const auto bottom = 0+Display_OLED::TEXT_HEIGHT*3 - 1;

	static constexpr const auto left = MERGIN;
	static constexpr const auto right = Display_OLED::OLED_WIDTH-MERGIN;

	const size_t dx = (right-left)/len;
	for (size_t i = 0; i < len; ++i) {
		display.draw_hbar(left+dx*i, bottom-arr[i]*(bottom-top)-2, dx-1);
		if (i == current) display.draw_hbar(left+dx*i, bottom, dx);
	}
}

using AppMode = App::Mode;
void show_mode(AppMode mode) {
	size_t scale_w = 1; // in character number
	size_t offset_w = 0; // in pixel
	size_t scale_h = 1; // in character number
	size_t offset_h = 0; // in pixel
	if (mode == App::Mode::Length) {
		scale_w = 7*0+4;
		scale_h = 1;
		offset_h = 1;
	} else if (mode == App::Mode::Number) {
		scale_w = 7*1+4;
		scale_h = 1;
		offset_h = 1;
	} else if (mode == App::Mode::Shift) {
		scale_w = 7*2+4;
		scale_h = 1;
		offset_h = 1;
	} else {
		scale_w = 0;
		scale_h = 4+app->get_next_idx();
		offset_h = -1;
	}

	display.draw_hbar(0+Display_OLED::TEXT_WIDTH*scale_w+offset_w, 0+Display_OLED::TEXT_HEIGHT*scale_h+offset_h, Display_OLED::TEXT_WIDTH*2);
}
/*
len:xx num:xx sft:xx
    ^-spos
*/

void show_pattern()
{
	int c = 0;
	for (size_t i = 0; i < App::MAX_PARAM_NUM; ++i) {
		char buf[16];
		auto p = app->get_params(c);
		snprintf(buf, 16, "%c%d: %2d/%2d/%2d", i == app->get_next_idx() ? '>' : ' ', ++c, p->len, p->num, p->sft);
		display.print_column(Display_OLED::TEXT_HEIGHT*(i+3), buf);
	}
}

uint64_t t_prev = 0;
uint64_t t_prev_disp = 0;

void loop() {
	auto t_cur = millis();

/*
	auto a0 = analogRead(PIN_CV_LEN);
	char buf[8];
	snprintf(buf, 8, "%4d", a0);
	serial_log("a0= %4d", a0);
*/

	if (t_cur-t_prev_disp > 20) {
		app->set_cv(
			analogRead(PIN_CV_LEN),
			analogRead(PIN_CV_NUM),
			analogRead(PIN_CV_SFT),
			analogRead(PIN_CV_SELECT)
		);

		const auto p = app->get_next_param();
		display.show_status("len:%2d num:%2d sft:%2d", p.len, p.num, p.sft);

		// graphics functions cannot be called in interruption callbacks.
		display.display(
			[&](){
				display.show_menu();
				show_mode(app->get_mode());
				show_graph(sequence, app->get_len(), seq_idx);
				//display.draw_hline(Display_OLED::TEXT_HEIGHT*3+Display_OLED::TEXT_HEIGHT/2);
				show_pattern();
			}
		);
		t_prev_disp = t_cur;
	}

/*
	if (t_cur-t_prev > 125) {
		only_for_develop = !only_for_develop;
		onClock();
		t_prev = t_cur;
	}
// */
}
