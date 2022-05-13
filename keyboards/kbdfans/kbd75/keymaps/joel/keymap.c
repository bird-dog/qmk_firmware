#include QMK_KEYBOARD_H

#define _QWERTY 0
#define _MEDIA 1
#define _NUM 2
#define _ADJUST 3

enum custom_keycodes {
  MYLOCK = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MYLOCK:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI(SS_TAP(X_L)));
      } else {
        layer_on(_MEDIA);
        set_oneshot_layer(_MEDIA, ONESHOT_START);
        clear_oneshot_layer_state(ONESHOT_PRESSED);
      }
      break;
  }
  return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
    KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  KC_INS,   KC_DEL,
    KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_DEL,   KC_BSPC,  KC_HOME,
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_END,
    KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,                      KC_ENT,   KC_PGUP,
    KC_LSFT,  MO(1),    KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,            KC_UP,    KC_PGDN,
    KC_LCTL,  KC_LGUI,  KC_LALT,                      KC_SPC,   KC_SPC,   KC_SPC,                       LT(_MEDIA, KC_MUTE),    LT(_ADJUST, KC_VOLD),  LT(_NUM, KC_VOLU),  KC_LEFT,  KC_DOWN,  KC_RGHT
  ),

  [_MEDIA] = LAYOUT(
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RESET,    KC_VOLU,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            KC_MUTE,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,  KC_VOLD,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            KC_MSTP,  _______,
    _______,  _______,  _______,                      _______,  _______,  _______,                      _______,  _______,  _______,  KC_MPRV,  KC_MPLY,  KC_MNXT
  ),

  [_NUM] = LAYOUT(
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_PSLS,  KC_PAST,  RESET,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_P7,  KC_P8,  KC_P9,  KC_PMNS,  _______,            _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_P4,  KC_P5,  KC_P6,                      KC_PPLS,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_P1,  KC_P2,  KC_P3,  KC_PENT,            _______,  _______,
    _______,  _______,  _______,                      KC_P0,  KC_P0,  KC_P0,                      _______,  _______,  KC_PDOT,  _______,  _______,  _______
  ),

  [_ADJUST] = LAYOUT(
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  RGB_TOG,  RGB_MOD,  RGB_HUI,  RGB_HUD,  RGB_SAI,  RGB_SAD,  RGB_VAI,  RGB_VAD,  _______,  _______,  _______,  _______,  _______,  RESET,    _______,
    _______,  KC_BTN1,  KC_MS_U,  KC_BTN2,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
    _______,  KC_MS_L,  KC_MS_D,  KC_MS_R,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,
    _______,  _______,  _______,  _______,  BL_DEC,   BL_TOGG,  BL_INC,   BL_STEP,  _______,  _______,  _______,  _______,  _______,            _______,  _______,
    _______,  _______,  _______,                      _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,  _______
  ),
};

// RGB Modes
// 1 = Static
// 2-5 = Breathing
// 6-8 = Rainbow
// 9-14 = Swirl
// 15-20 = Snake
// 21-24 = Nightrider
// 25 = Christmas
// 26-30 = Static Gradient
const uint8_t RGBLED_RAINBOW_SWIRL_INTERVALS[] PROGMEM = {100, 50, 10}; // Set the last one to 10ms for some speedy swirls

uint8_t prev = _QWERTY;
uint32_t check;
uint32_t desired = 1;

void matrix_init_user() {
	rgblight_mode(desired);
}

uint32_t layer_state_set_user(uint32_t state) {
  uint8_t layer = biton32(state);
  if (prev!=_ADJUST) {
	  switch (layer) {
      case _QWERTY:
        rgblight_mode(desired);
        break;

      case _MEDIA: // If we're in swirl mode, then speed up the swirls, otherwise breathe
        check = rgblight_get_mode();
        if (check > 8 && check < 15) {
          rgblight_mode(14);
        } else {
          rgblight_mode(2);
        }
        break;

      case _NUM: // Same as above but reverse direction, otherwise nightrider
        check = rgblight_get_mode();
        if (check > 8 && check < 15) {
          rgblight_mode(13);
        } else {
          rgblight_mode(23);
        }
        break;

      case _ADJUST:
        break;
      }
  } else {
	  desired = rgblight_get_mode();
  }
  prev = layer;
  return state;
}