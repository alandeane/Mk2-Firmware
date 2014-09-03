/*
 TiLDA Mk2

 SettingsStore

 This class stores information like badgeId, preferences and whatever
 else we can think of. This goes into the flash memory.

 See: https://github.com/sebnil/DueFlashStorage/blob/master/flash_efc.cpp#L845

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

#ifndef _SETTINGS_STORE_H_
#define _SETTINGS_STORE_H_

#include <Arduino.h>
#include <FreeRTOS_ARM.h>
#include "EMF2014Config.h"

class SettingsStoreObserver {
public:
};

class SettingsStore {
public:
    SettingsStore();
    ~SettingsStore();

    bool getUniqueId(uint32_t* unique_id) const;

    char* getUserNameLine1();
    char* getUserNameLine2();
    void setUserNameLine1(char *newname1);
    void setUserNameLine2(char *newname2);

    void addObserver(SettingsStoreObserver* aObserver);
    void removeObserver(SettingsStoreObserver* aObserver);

private:
    SettingsStore(const SettingsStore&);

    void notifyObservers(uint16_t aBadgeId);

private:
    char name1[11];
    char name2[11];

    SettingsStoreObserver** mObservers;
    SemaphoreHandle_t mObserversMutex;
};

#endif // _SETTINGS_STORE_H_
