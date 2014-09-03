/*
 TiLDA Mk2

 EMF2014Config
 This files contains all the initial configuration details for the badge firmware and any compli time defines that might be used by any of the task


 The MIT License (MIT)

 Copyright (c) 2014 Electromagnetic Field LTD

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#pragma once

// This defines how many subscription each button can handle
#define MAX_BUTTON_SUBSCRIPTIONS 10
// maximum amount of apps the AppManager can handle
#define MAX_APPS 10
// pin used for seeding the random number generator
#define RANDOM_SEED_PIN 5

// duration that center has to be pressed to go back to the homescreen
#define CENTER_BUTTON_PRESS_DURATION_FOR_HOME_SCREEN 500
// time before the backlight goes out
#define BACKLIGHT_TIMEOUT 15 * 1000
// time before the current app gets killed and the badge goes back to the homescreen
#define APP_KILL_TIMEOUT 90 * 1000
// backlight light level speed in ms
#define BACKLIGHT_BRIGHTNESS_UPDATE_TIME 50

// EMF Camp 2014 will be in Britain during British Summer Time
#define TIMEZONE_OFFSET 3600

#define BOOT_SCREEN_TIME 2000

enum Button {
    NONE         = 0,
    LIGHT        = 1,
    A            = 2,
    B            = 4,
    UP           = 8,
    DOWN         = 16,
    LEFT         = 32,
    RIGHT        = 64,
    CENTER       = 128
};

enum Orientation_t{
    ORIENTATION_HELD,
    ORIENTATION_RIGHT,  // joystick to the right of the screen
    ORIENTATION_HUNG,
    ORIENTATION_LEFT    // joystick to the left of the screen,
};
