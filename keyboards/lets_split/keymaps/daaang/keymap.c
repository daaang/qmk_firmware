/**
 * I currently allow for every standard key except:
 * - Caps Lock              Would be my only lock key, so meh
 * - Scroll Lock            Outdated, rarely useful
 * - Pause/Break            Outdated, never useful
 * - Insert                 I've never used this key
 * - Application (Win menu) This is just right-clicking
 * - SysReq                 Outdated, only useful for OS development
 * - Num Lock / Clear       Silly given layers
 * - Power                  Deprecated
 * - System Power           Hard to imagine a use case
 * - System Sleep           I don't want to accidentally sleep
 * - System Wake            Any key wakes a computer
 * - Next/Prev Track        Different OS's use it differently
 * - Play/Pause/Stop Track  Easier to customize Fx keys anyway
 *
 *     ├── QWERTY
 *     │   ├── Number Pad
 *     │   ├── Symbol Pad
 *     │   ├── Function Pad
 *     │   │   ├── Function Pad 1x
 *     │   │   └── Function Pad 2x
 *     │   ├── Arrow Keys
 *     │   └── Mouse Mode
 *     └── Stenography
 */

#include "lets_split.h"
#include "action_layer.h"
#include "eeconfig.h"
#include "keymap_steno.h"
/* #include "mousekey.h" */

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _MIDDLE 1
#define _NUMPAD 2
#define _NUMNUMPAD 3
#define _SYMPAD 4
#define _ARROWS 5
#define _MOUSE 6
#define _STARCRAFT 7
#define _ASDFGHJKL 8
#define _BRLPHFG 9
#define _FNPAD0x 10
#define _FNPAD1x 11
#define _FNPAD2x 12
#define _SAFE_QWERTY 13
#define _STENO 14

enum custom_keycodes {
  /* Lock the current layer in place. */
  KC_L_LK = SAFE_RANGE,

  /* Send escape most of the time, but send backtick when alt (and only
   * alt) is being held.
   */
  KC_M_ES,

  /* Leave/unlock layer. */
  KC_L_NM,
  KC_L_SM,
  KC_L_AR,
  KC_L_MS,
  KC_L_FN,

  /* Normally, with layer-tap, if I hold a modifier key and release the
   * layer key before the modifier, the modifier is stuck on. These are
   * here to fix that. They're special modifiers that auto-release
   * whenever we enter the base layer.
   */
  KC_LT_S,
  KC_LT_C,
  KC_LT_A,
  KC_LT_G,

  /* These are for a-clicking and p-clicking, so I don't have to do a
   * bunch of layer switching every time. In StarCraft, that is.
   */
  KC_SC_A,
  KC_SC_P,

  /* Enter (not toggle or layer-tap) stenography. */
  KC_L_ST,

  /* Exit stenography. */
  STN_L_EX,

  /* Exit stenography and hit escape (for leaving insert mode in vi). */
  STN_L_ES,

  /* Exit stenography and hit alt (for leaving stenography when trying
   * for alt-tab).
   */
  STN_L_AL
};

/* Fillers to make layering more clear */
#define KC_     KC_TRNS
#define KC_XXXX KC_NO
#define STN_    KC_NO

/* Layer keys */
#define KC_NM_D  LT(_NUMPAD,    KC_D)
#define KC_N_NM  MO(_NUMNUMPAD)
#define KC_SM_F  LT(_SYMPAD,    KC_F)
#define KC_MS_J  LT(_MOUSE,     KC_J)
#define KC_SC_K  LT(_STARCRAFT, KC_K)
#define KC_L_SC  MO(_STARCRAFT)
#define KC_AL_S  LT(_ASDFGHJKL, KC_S)
#define KC_L_AL  MO(_ASDFGHJKL)
#define KC_BR_B  LT(_BRLPHFG,   KC_B)
#define KC_L_BR  MO(_BRLPHFG)
#define KC_AR_M  LT(_ARROWS,    KC_M)
#define KC_F_TB  LT(_FNPAD0x,   KC_TAB)
#define KC_L_F1  LT(_FNPAD1x,   KC_F10)
#define KC_L_F2  LT(_FNPAD2x,   KC_F20)
#define KC_SAFE  TO(_SAFE_QWERTY)
#define KC_TG_S  TG(_SAFE_QWERTY)

/* I want ZXC and ,./ to act as ctrl/alt/gui when held. */
#define KC_S_A  LSFT_T(KC_A)
#define KC_C_Z  LCTL_T(KC_Z)
#define KC_A_X  LALT_T(KC_X)
#define KC_G_C  LGUI_T(KC_C)
#define KC_G_CM LGUI_T(KC_COMMA)
#define KC_A_PD LALT_T(KC_DOT)
#define KC_C_SL LCTL_T(KC_SLASH)
#define KC_S_CN LSFT_T(KC_SCLN)

#define KC_C_EN LCAG_T(KC_PENT)
#define KC_C_BS MEH_T(KC_BSPC)
#define KC_C_RE ALL_T(KC_ENT)

#define KC_F_RS RESET

/* Used to create a keymap using only STN_ prefixed keys */
#define LAYOUT_stn(                                                   \
  L00, L01, L02, L03, L04, L05, R00, R01, R02, R03, R04, R05,         \
  L10, L11, L12, L13, L14, L15, R10, R11, R12, R13, R14, R15,         \
  L20, L21, L22, L23, L24, L25, R20, R21, R22, R23, R24, R25,         \
  L30, L31, L32, L33, L34, L35, R30, R31, R32, R33, R34, R35          \
  )                                                                   \
  LAYOUT(                                                             \
    STN_##L00, STN_##L01, STN_##L02, STN_##L03, STN_##L04, STN_##L05, \
    STN_##R00, STN_##R01, STN_##R02, STN_##R03, STN_##R04, STN_##R05, \
    STN_##L10, STN_##L11, STN_##L12, STN_##L13, STN_##L14, STN_##L15, \
    STN_##R10, STN_##R11, STN_##R12, STN_##R13, STN_##R14, STN_##R15, \
    STN_##L20, STN_##L21, STN_##L22, STN_##L23, STN_##L24, STN_##L25, \
    STN_##R20, STN_##R21, STN_##R22, STN_##R23, STN_##R24, STN_##R25, \
    STN_##L30, STN_##L31, STN_##L32, STN_##L33, STN_##L34, STN_##L35, \
    STN_##R30, STN_##R31, STN_##R32, STN_##R33, STN_##R34, STN_##R35  \
  )

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* The base layer is qwerty, with these exceptions:
 *
 * 1.  Escape instead of caps lock.
 * 2.  Backspace next to P.
 * 3.  Right thumb has hyphen, space, and underscore.
 * 4.  Left thumb has return, enter, and a second backspace.
 * 5.  Tap left or right shift for left or right parentheses.
 * 6.  Hold A or semicolon for shift.
 * 7.  Hold Z or slash for control.
 * 8.  Hold X or period for alt.
 * 9.  Hold C or comma for GUI.
 * 10. Hold D to use the number pad layer.
 * 11. Hold F to use the symbol pad layer.
 * 12. Hold M to use the arrow keys layer.
 * 13. Hold J to use the mouse layer.
 * 14. Hold tab to use the function layer.
 * 15. Tab-T enters the stenography layer.
 * 16. Left thumb can hold backspace for control-alt-GUI.
 * 17. Left thumb can hold enter for control-alt-shift.
 * 18. Left thumb can hold return for control-alt-shift-GUI.
 *
 * Whenever a key must be held to use a layer, you can tap the key
 * underneath to lock it in. Then, you can let go. To exit the layer,
 * tap its key. For example, D-C enters the number pad, and another tap
 * of D exits back to qwerty. This is useful for one-handed typing.
 *
 * With the exception of the stenography layer, the hand holding the
 * activation key gets nearby command keys -- shift, control, alt, and
 * GUI. In general, pinky/ring gets control, ring/middle gets alt, and
 * middle/index gets GUI and shift. Shift is up for the middle finger
 * and down for the index finger.
 */
[_QWERTY] = LAYOUT_kc(
/* ,-----------------------------. ,-----------------------------. */
    F_TB, Q  , W  , E  , R  , T  ,   Y  , U  , I  , O  , P  ,BSPC,
/* |----+----+----+----+----+----| |----+----+----+----+----+----| */
    M_ES,S_A ,AL_S,NM_D,SM_F, G  ,   H  ,MS_J,SC_K, L  ,S_CN,QUOT,
/* |----+----+----+----+----+----| |----+----+----+----+----+----| */
    LSPO,C_Z ,A_X ,G_C , V  ,BR_B,   N  ,AR_M,G_CM,A_PD,C_SL,RSPC,
/* |----+----+----+----+----+----| |----+----+----+----+----+----| */
    LCTL,LALT,LGUI,L_ST,C_BS,C_RE,  MINS,SPC ,UNDS,RGUI,RALT,RCTL
/* `-----------------------------' `-----------------------------' */
),

/* This layer activates automatically whenever any layer is above it. It
 * automatically deactivates whenever it's on top. Its purpose is to
 * remove the weird stuff from higher layers.
 *
 * Layer activation keys can no longer be tapped to write tab, D, F, J,
 * or M, and the shift keys no longer have the dual function of sending
 * parentheses. Otherwise, the bottom row stays the same, and most other
 * keys are blocked from perpetuating upward.
 */
[_MIDDLE] = LAYOUT_kc(
/* ,-----------------------------. ,-----------------------------. */
    L_FN,XXXX,XXXX,XXXX,XXXX,XXXX,  XXXX,XXXX,XXXX,XXXX,XXXX,    ,
/* |----+----+----+----+----+----| |----+----+----+----+----+----| */
    XXXX,XXXX,L_AL,L_NM,L_SM,XXXX,  XXXX,L_MS,L_SC,XXXX,XXXX,XXXX,
/* |----+----+----+----+----+----| |----+----+----+----+----+----| */
    LSFT,XXXX,XXXX,XXXX,XXXX,L_BR,  XXXX,L_AR,XXXX,XXXX,XXXX,RSFT,
/* |----+----+----+----+----+----| |----+----+----+----+----+----| */
        ,    ,    ,XXXX,    ,    ,      ,    ,    ,    ,    ,
/* `-----------------------------' `-----------------------------' */
),

/* The number pad positions itself so that the middle finger is over the
 * number 5. You can also find plus, minus, slash, asterisk, and equal
 * signs. This layer has the forward delete as well.
 */
[_NUMPAD] = LAYOUT_kc(
/* ,-----------------------------. ,-----------------------------. */
    XXXX,    ,    ,    ,    ,    ,  MINS, 7  , 8  , 9  ,SLSH,    ,
/* |----+----+----+----+----+----| |----+----+----+----+----+----| */
        ,LT_C,LT_A,    ,LT_G,    ,  PLUS, 4  , 5  , 6  ,ASTR,COMM,
/* |----+----+----+----+----+----| |----+----+----+----+----+----| */
        ,    ,    ,L_LK,LT_S,XXXX,  EQL , 1  , 2  , 3  ,DEL ,    ,
/* |----+----+----+----+----+----| |----+----+----+----+----+----| */
        ,    ,    ,    ,N_NM,    ,  ENT , 0  ,DOT ,    ,    ,
/* `-----------------------------' `-----------------------------' */
),

[_NUMNUMPAD] = LAYOUT_kc(
/* ,-----------------------------. ,-----------------------------. */
        ,    ,    ,    ,    ,    ,  PMNS, P7 , P8 , P9 ,PSLS,    ,
/* |----+----+----+----+----+----| |----+----+----+----+----+----| */
        ,    ,    ,    ,    ,    ,  PPLS, P4 , P5 , P6 ,PAST,COMM,
/* |----+----+----+----+----+----| |----+----+----+----+----+----| */
        ,    ,    ,XXXX,    ,    ,  EQL , P1 , P2 , P3 ,DEL ,    ,
/* |----+----+----+----+----+----| |----+----+----+----+----+----| */
        ,    ,    ,    ,N_NM,    ,  PENT, P0 ,PDOT,    ,    ,
/* `-----------------------------' `-----------------------------' */
),

/* The symbol pad has shifted numbers 1-8 in their number pad positions
 * as well as brackets, tilde, backslash, backtick, and pipe.
 */
[_SYMPAD] = LAYOUT_kc(
/* ,-----------------------------. ,-----------------------------. */
    XXXX,    ,    ,LT_S,    ,    ,  GRV ,AMPR,ASTR,TILD,LCBR,RCBR,
/* |----+----+----+----+----+----| |----+----+----+----+----+----| */
        ,LT_C,LT_A,LT_G,    ,    ,  PIPE,DLR ,PERC,CIRC,LBRC,RBRC,
/* |----+----+----+----+----+----| |----+----+----+----+----+----| */
        ,    ,    ,    ,L_LK,XXXX,  DQT ,EXLM, AT ,HASH,BSLS,    ,
/* |----+----+----+----+----+----| |----+----+----+----+----+----| */
        ,    ,    ,    ,    ,    ,      ,    ,    ,    ,    ,
/* `-----------------------------' `-----------------------------' */
),

/* Arrow keys include page up, page down, home, and end.
 */
[_ARROWS] = LAYOUT_kc(
/* ,-----------------------------. ,-----------------------------. */
    XXXX,    ,PGUP, UP ,PGDN,    ,      ,    ,    ,    ,    ,    ,
/* |----+----+----+----+----+----| |----+----+----+----+----+----| */
        ,HOME,LEFT,DOWN,RGHT,END ,      ,XXXX,LT_S,    ,    ,    ,
/* |----+----+----+----+----+----| |----+----+----+----+----+----| */
        ,    ,    ,    ,    ,XXXX,      ,    ,LT_G,LT_A,LT_C,    ,
/* |----+----+----+----+----+----| |----+----+----+----+----+----| */
        ,    ,    ,    ,    ,    ,  XXXX,L_LK,XXXX,    ,    ,
/* `-----------------------------' `-----------------------------' */
),

/* The mouse layer is like the arrow keys, but the arrows move the
 * mouse, and the buttons to either side are for scrolling. Both thumbs
 * curl inward to go from left click to right click and finally to
 * middle/scroll click.
 *
 * Acceleration starts at 2, the fastest. The ring finger and pinky can
 * reach up to slow it to 1 or to 0, respectively. It can be sped up by
 * reaching down with the middle finger.
 *
 * In case they're ever useful, I've left mouse buttons 4 and 5 as well.
 */
[_MOUSE] = LAYOUT_kc(
/* ,-----------------------------. ,-----------------------------. */
    XXXX,    ,WH_U,MS_U,WH_D,    ,      ,    ,LT_S,ACL1,ACL0,    ,
/* |----+----+----+----+----+----| |----+----+----+----+----+----| */
        ,WH_L,MS_L,MS_D,MS_R,WH_R,      ,    ,LT_G,LT_A,LT_C,    ,
/* |----+----+----+----+----+----| |----+----+----+----+----+----| */
        ,    ,    ,    ,BTN4,BTN5,      ,L_LK,ACL2,    ,    ,    ,
/* |----+----+----+----+----+----| |----+----+----+----+----+----| */
        ,    ,    ,BTN3,BTN2,BTN1,  BTN1,BTN2,BTN3,    ,    ,
/* `-----------------------------' `-----------------------------' */
),

/* This is a special mouse mode just for StarCraft. It combines the
 * mouse directions with arrow keys (instead of scroll directions). It's
 * nice for key-scrolling.
 */
[_STARCRAFT] = LAYOUT_kc(
/* ,-----------------------------. ,-----------------------------. */
    XXXX,    , UP ,MS_U,DOWN,    ,      ,    ,    ,    ,    ,    ,
/* |----+----+----+----+----+----| |----+----+----+----+----+----| */
        ,LEFT,MS_L,MS_D,MS_R,RGHT,  ACL2,LT_G,    ,LT_A,LT_C,    ,
/* |----+----+----+----+----+----| |----+----+----+----+----+----| */
        ,    ,    ,    ,    ,XXXX,      ,LT_S,    ,ACL1,ACL0,    ,
/* |----+----+----+----+----+----| |----+----+----+----+----+----| */
        ,    ,    ,SC_A,BTN2,BTN1,  BTN1,BTN2,SC_P,    ,    ,
/* `-----------------------------' `-----------------------------' */
),

[_ASDFGHJKL] = LAYOUT_kc(
/* ,-----------------------------. ,-----------------------------. */
    XXXX,    ,    ,    ,    ,    ,   A  , K  , D  , J  , S  ,    ,
/* |----+----+----+----+----+----| |----+----+----+----+----+----| */
        ,LT_S,    ,XXXX,XXXX,    ,   F  , A  , L  , S  , D  ,    ,
/* |----+----+----+----+----+----| |----+----+----+----+----+----| */
        ,    ,    ,    ,    ,XXXX,   J  , F  , H  , G  , A  ,    ,
/* |----+----+----+----+----+----| |----+----+----+----+----+----| */
        ,    ,    ,    ,    ,    ,      ,    ,    ,    ,    ,
/* `-----------------------------' `-----------------------------' */
),

[_BRLPHFG] = LAYOUT_kc(
/* ,-----------------------------. ,-----------------------------. */
    XXXX,    ,    ,    ,    ,    ,   G  , F  , H  , P  , G  ,    ,
/* |----+----+----+----+----+----| |----+----+----+----+----+----| */
        ,    ,XXXX,XXXX,XXXX,    ,   P  , L  , R  , B  , B  ,    ,
/* |----+----+----+----+----+----| |----+----+----+----+----+----| */
        ,    ,    ,    ,LT_S,    ,   F  , H  , F  , G  , L  ,    ,
/* |----+----+----+----+----+----| |----+----+----+----+----+----| */
        ,    ,    ,    ,    ,    ,      ,    ,    ,    ,    ,
/* `-----------------------------' `-----------------------------' */
),

/* The function pad is like the number pad, but with some extras: the
 * left side has the key for entering stenography in the upper-right;
 * volume buttons are to the left of the function keys; you can reset
 * the firmware with what is usually backspace; and the right thumb can
 * tap print screen, F10, and F20.
 *
 * Hold F10, and F1 through F9 become F11 through F19. Hold F20, and F1
 * through F4 become F21 through F24.
 */
[_FNPAD0x] = LAYOUT_kc(
/* ,-----------------------------. ,-----------------------------. */
        ,LT_C,LT_A,LT_G,    ,SAFE,  VOLU, F7 , F8 , F9 ,    ,F_RS,
/* |----+----+----+----+----+----| |----+----+----+----+----+----| */
    L_LK,    ,    ,LT_S,XXXX,    ,  MUTE, F4 , F5 , F6 ,    ,    ,
/* |----+----+----+----+----+----| |----+----+----+----+----+----| */
        ,    ,    ,    ,    ,    ,  VOLD, F1 , F2 , F3 ,    ,    ,
/* |----+----+----+----+----+----| |----+----+----+----+----+----| */
        ,    ,    ,    ,    ,    ,  PSCR,L_F1,L_F2,    ,    ,
/* `-----------------------------' `-----------------------------' */
),

[_FNPAD1x] = LAYOUT_kc(
/* ,-----------------------------. ,-----------------------------. */
        ,    ,    ,    ,    ,    ,      ,F17 ,F18 ,F19 ,    ,    ,
/* |----+----+----+----+----+----| |----+----+----+----+----+----| */
    XXXX,    ,    ,    ,    ,    ,      ,F14 ,F15 ,F16 ,    ,    ,
/* |----+----+----+----+----+----| |----+----+----+----+----+----| */
        ,    ,    ,    ,    ,    ,      ,F11 ,F12 ,F13 ,    ,    ,
/* |----+----+----+----+----+----| |----+----+----+----+----+----| */
        ,    ,    ,    ,    ,    ,      ,    ,F20 ,    ,    ,
/* `-----------------------------' `-----------------------------' */
),

[_FNPAD2x] = LAYOUT_kc(
/* ,-----------------------------. ,-----------------------------. */
        ,    ,    ,    ,    ,    ,      ,XXXX,XXXX,XXXX,    ,    ,
/* |----+----+----+----+----+----| |----+----+----+----+----+----| */
    XXXX,    ,    ,    ,    ,    ,      ,F24 ,XXXX,XXXX,    ,    ,
/* |----+----+----+----+----+----| |----+----+----+----+----+----| */
        ,    ,    ,    ,    ,    ,      ,F21 ,F22 ,F23 ,    ,    ,
/* |----+----+----+----+----+----| |----+----+----+----+----+----| */
        ,    ,    ,    ,    ,    ,      ,F20 ,    ,    ,    ,
/* `-----------------------------' `-----------------------------' */
),

[_SAFE_QWERTY] = LAYOUT_kc(
/* ,-----------------------------. ,-----------------------------. */
     TAB, Q  , W  , E  , R  , T  ,   Y  , U  , I  , O  , P  ,    ,
/* |----+----+----+----+----+----| |----+----+----+----+----+----| */
    TG_S, A  , S  , D  , F  , G  ,   H  , J  , K  , L  ,SCLN,QUOT,
/* |----+----+----+----+----+----| |----+----+----+----+----+----| */
    LSFT, Z  , X  , C  , V  , B  ,   N  , M  ,COMM,DOT ,SLSH,RSFT,
/* |----+----+----+----+----+----| |----+----+----+----+----+----| */
        ,    ,    ,XXXX,    ,    ,      ,    ,    ,    ,    ,
/* `-----------------------------' `-----------------------------' */
),

/* The stenography layer has the usual 23 keys, plus an exit key at the
 * lower left corner. Also, just above the exit key is a key that exits
 * and taps escape, for switching from vim insert stenography to vim
 * command qwerty with a single keystroke.
 */
[_STENO] = LAYOUT_stn(
/* ,-----------------------------. ,-----------------------------. */
     N1 , N2 , N3 , N4 , N5 , N6 ,   N7 , N8 , N9 , NA , NB , NC ,
/* `-----------------------------| |-----------------------------| */
        , S1 , TL , PL , HL ,ST1 ,  ST3 , FR , PR , LR , TR , DR ,
/*      |    |----+----+----|           |----+----+----+----+----| */
    L_ES, S2 , KL , WL , RL ,ST2 ,  ST4 , RR , BR , GR , SR , ZR ,
/*      `--------------+----+----| |----+----+-------------------' */
    L_EX,L_AL,    ,    , A  , O  ,   E  , U  ,    ,    ,    ,
/*                     `---------' `---------'                     */
)
};

void matrix_init_user() {
  /* Let's just go ahead and use the full gemini protocol, why not. */
  steno_set_mode(STENO_MODE_GEMINI);
}

/* Private state vars */
bool daaang_global_layer_is_locked = false;
uint8_t daaang_global_layer_tap_mods = 0;
bool daaang_global_sent_grave = false;

/* This runs every time the layer mask changes. */
uint32_t layer_state_set_user (uint32_t state) {
  uint8_t top_layer = biton32(state);

  if (top_layer > _MIDDLE)
    /* Enable the middle layer any time it won't be on top. */
    state |= (1 << _MIDDLE);

  switch (top_layer) {
    case _QWERTY:
      /* As we enter the base layer, check for any lingering modifiers
       * and send key-up events.
       */
      if (daaang_global_layer_tap_mods & (1 << 0))
        unregister_code(KC_LSFT);

      if (daaang_global_layer_tap_mods & (1 << 1))
        unregister_code(KC_LCTL);

      if (daaang_global_layer_tap_mods & (1 << 2))
        unregister_code(KC_LALT);

      if (daaang_global_layer_tap_mods & (1 << 3))
        unregister_code(KC_LGUI);

      /* Reset the state for layer-tap modifiers. */
      daaang_global_layer_tap_mods = 0;
      break;

    case _MIDDLE:
      /* Disable the middle layer any time it winds up on top. */
      return layer_state_set_user(state & (~(1 << _MIDDLE)));

    case _MOUSE:
      /* On entering the mouse layer, set acceleration to max by tapping
       * KC_ACL2.
       */
      register_code(KC_ACL2);
      unregister_code(KC_ACL2);
      break;

    case _STENO:
      /* Entering stenography mode should disable most other layers.
       * Allowed layers are: base (workman), middle, and stenography.
       */
      state &= (1 << _QWERTY) | (1 << _MIDDLE) | (1 << _STENO);
      break;
  }

  return state;
}

/* This runs every time a physical key is pressed or released. */
bool process_record_user (uint16_t keycode, keyrecord_t *record) {
  static uint8_t mods_pressed;

  switch (keycode) {
    case KC_L_LK:
      daaang_global_layer_is_locked = true;
      return false;

    case KC_M_ES:
      if (record->event.pressed) {
        mods_pressed = get_mods();
        daaang_global_sent_grave = mods_pressed &&
            (mods_pressed == (mods_pressed & (MOD_LALT | MOD_RALT)));

        if (daaang_global_sent_grave)
          register_code(KC_GRV);
        else
          register_code(KC_ESC);

      } else {
        if (daaang_global_sent_grave)
          unregister_code(KC_GRV);
        else
          unregister_code(KC_ESC);
      }

      return false;

#define LAYER_CASE(LAYER_KEY, LAYER)            \
    case LAYER_KEY:                             \
      if (record->event.pressed)                \
        /* Unlock on key-down. */               \
        daaang_global_layer_is_locked = false;  \
                                                \
      else if (!daaang_global_layer_is_locked)  \
        /* Disable on key-up if unlocked. */    \
        layer_off(LAYER);                       \
                                                \
      return false

      LAYER_CASE(KC_L_NM, _NUMPAD);
      LAYER_CASE(KC_L_SM, _SYMPAD);
      LAYER_CASE(KC_L_AR, _ARROWS);
      LAYER_CASE(KC_L_MS, _MOUSE);
      LAYER_CASE(KC_L_FN, _FNPAD0x);
#undef LAYER_CASE

#define LAYER_TAP_MOD(LAYER_KEY, MOD_KEY, FLAGNO)            \
    case LAYER_KEY:                                          \
      /* Register the modifier, and also store its state. */ \
      if (record->event.pressed) {                           \
        register_code(MOD_KEY);                              \
        daaang_global_layer_tap_mods |= (1 << FLAGNO);       \
                                                             \
      } else {                                               \
        unregister_code(MOD_KEY);                            \
        daaang_global_layer_tap_mods &= (~(1 << FLAGNO));    \
      }                                                      \
                                                             \
      return false

      LAYER_TAP_MOD(KC_LT_S, KC_LSFT, 0);
      LAYER_TAP_MOD(KC_LT_C, KC_LCTL, 1);
      LAYER_TAP_MOD(KC_LT_A, KC_LALT, 2);
      LAYER_TAP_MOD(KC_LT_G, KC_LGUI, 3);
#undef LAYER_TAP_MOD

    case KC_SC_A:
      if (record->event.pressed) {
        register_code(KC_A);
        unregister_code(KC_A);
        /* mousekey_on(KC_BTN1); */
      } else {
        /* mousekey_off(KC_BTN1); */
      }

      return false;

    case KC_SC_P:
      if (record->event.pressed) {
        register_code(KC_P);
        unregister_code(KC_P);
        /* mousekey_on(KC_BTN1); */
      } else {
        /* mousekey_off(KC_BTN1); */
      }

      return false;

    case KC_L_ST:
      if (!record->event.pressed)
        layer_on(_STENO);
      return false;

    case STN_L_EX:
      if (!record->event.pressed)
        layer_off(_STENO);
      return false;

    case STN_L_ES:
      /* Holding STN_L_ES is nearly the same as holding KC_ESC. */
      if (record->event.pressed) {
        register_code(KC_ESC);
      } else {
        unregister_code(KC_ESC);

        /* But letting go also exits stenography mode. */
        layer_off(_STENO);
      }

      return false;

    case STN_L_AL:
      if (record->event.pressed) {
        layer_off(_STENO);
        register_code(KC_LALT);
      } else {
        unregister_code(KC_LALT);
      }

      return false;
  }

  return true;
}
