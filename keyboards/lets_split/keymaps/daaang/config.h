/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

/* I'm using I2C, and I want to be able to plug in either usb port. */
#define USE_I2C
#define EE_HANDS

/* By default, a key must be held for at least 200 milliseconds for it
 * to count as being "held" if it has different behavior when tapped.
 *
 * For example, say the Z key is ctrl when held. The below case will
 * cause `KC_LCTL down, KC_A down, KC_A up, KC_LCTL up` to be sent:
 *
 *     00:00:00.000 Z down
 *     00:00:00.150 A down
 *     00:00:00.250 A up
 *     00:00:00.300 Z up
 *
 * Which is likely the desired behavior. However, the below case will
 * cause `KC_Z down, KC_A down, KC_A up, KC_Z up` to be sent:
 *
 *     00:00:00.000 Z down
 *     00:00:00.050 A down
 *     00:00:00.100 A up
 *     00:00:00.150 Z up
 *
 * Make this number smaller if that's causing problems.
 */
#define TAPPING_TERM 200

/* If I roll over ZX quickly without this setting, it will send ctrl-x.
 * Setting this will make it send zx, as long as it happened under the
 * term.
 */
#define IGNORE_MOD_TAP_INTERRUPT

/* These are currently set to their defaults, but I may want to change
 * them as I get a feel for mouse movement. Even if not, I'll get used
 * to them as they are, so I'll want them the same if the defaults ever
 * change.
 */
#define MOUSEKEY_INTERVAL 20
#define MOUSEKEY_DELAY 0
#define MOUSEKEY_TIME_TO_MAX 25
#define MOUSEKEY_MAX_SPEED 7
#define MOUSEKEY_WHEEL_MAX 10
#define MOUSEKEY_WHEEL_MAX_SPEED 7
#define MOUSEKEY_WHEEL_TIME_TO_MAX 255

#endif
