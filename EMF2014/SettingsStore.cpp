/*
 TiLDA Mk2

 SettingsStore

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

#include "SettingsStore.h"
#include <DueFlashStorage.h>
#include <debug.h>
#include "Utils.h"

#define MAX_OBSERVERS 10

SettingsStore::SettingsStore()
{
    mObservers = new SettingsStoreObserver*[MAX_OBSERVERS];
    for (int i = 0 ; i < MAX_OBSERVERS ; ++i) {
        mObservers[i] = NULL;
    }

    for (int i = 0; i < 11; ++i) {
        name1[i] = 0;
        name2[i] = 0;
    }

    mObserversMutex = xSemaphoreCreateMutex();
}

SettingsStore::~SettingsStore() {
    delete[] mObservers;
}

void SettingsStore::addObserver(SettingsStoreObserver* aObserver) {
    if (xSemaphoreTake(mObserversMutex, portMAX_DELAY) == pdTRUE) {
        for (int i = 0 ; i < MAX_OBSERVERS ; ++i) {
            if (mObservers[i] == NULL) {
                mObservers[i] = aObserver;
                break;
            }
        }

        xSemaphoreGive(mObserversMutex);
    }
}

void SettingsStore::removeObserver(SettingsStoreObserver* aObserver) {
    if (xSemaphoreTake(mObserversMutex, portMAX_DELAY) == pdTRUE) {
        for (int i = 0 ; i < MAX_OBSERVERS ; ++i) {
            if (mObservers[i] = aObserver) {
                mObservers[i] = NULL;
            }
        }

        xSemaphoreGive(mObserversMutex);
    }
}

// What does this function do? And what needs doing for non-badgeid
// notifications?
void SettingsStore::notifyObservers(uint16_t aBadgeId) {
/*    if (xSemaphoreTake(mObserversMutex, portMAX_DELAY) == pdTRUE) {
        for (int i = 0 ; i < MAX_OBSERVERS ; ++i) {
            if (mObservers[i] != NULL) {
                mObservers[i]->badgeIdChanged(aBadgeId);
            }
        }

        xSemaphoreGive(mObserversMutex);
    }*/
}

char* SettingsStore::getUserNameLine1() {
    return name1;
}

char* SettingsStore::getUserNameLine2() {
    return name2;
}

void SettingsStore::setUserNameLine1(char *newname1) {
    for(int i=0; i<10; i++)
        name1[i] = newname1[i];
}

void SettingsStore::setUserNameLine2(char *newname2) {
    for(int i=0; i<10; i++)
        name2[i] = newname2[i];
}

bool SettingsStore::getUniqueId(uint32_t* unique_id) const {
    return flash_init(FLASH_ACCESS_MODE_128, 4) == FLASH_RC_OK &&
           flash_read_unique_id(unique_id, 4) == FLASH_RC_OK;
}
