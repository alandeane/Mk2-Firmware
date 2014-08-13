/*
 TiLDA Mk2

 RadioTask
 This handles the periodic wake of the radio for all our need communication with the gateway's.
 Incoming request are passed back to the TiLDATask
 Outgoing request from TiLDATask are sent at the next opportunity.

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

#include <Arduino.h>
#include <FreeRTOS_ARM.h>
#include <rtc_clock.h>
#include "EMF2014Config.h"
#include "Task.h"
#include "MessageCheckTask.h"

class RadioTask: public Task {
private:
	enum RadioState : uint8_t {
		RADIO_STATE_DISCOVERY,
		RADIO_STATE_RECEIVE,
		RADIO_STATE_TRANSMIT
	};

public:
	RadioTask(MessageCheckTask& aMessageCheckTask, RTC_clock& aRealTimeClock);

	String getName() const;
protected:
	void task();
private:
	inline void _enterAtMode();
	inline void _leaveAtMode();

	inline uint16_t _bytesToInt(byte b1, byte b2);
	inline uint32_t _bytesToInt(byte b1, byte b2, byte b3, byte b4);
	inline String _intToHex(uint8_t input);

	inline uint8_t _parsePacketBuffer(byte packetBuffer[], uint8_t packetBufferLength);

	inline void _handleReceivePacket(byte packetBuffer[], uint8_t packetBufferLength);
	inline void _handleDiscoveryPacket(byte packetBuffer[], uint8_t packetBufferLength, uint8_t rssi);
	inline void _verifyMessage();
	inline void _checkForStateChange();
	inline void _initialiseDiscoveryState();
	inline void _initialiseReceiveState();
	inline void _clearSerialBuffer();
	inline void _sendOutgoingBuffer();

private:
	MessageCheckTask& mMessageCheckTask;
	RTC_clock& mRealTimeClock;

	byte _messageBuffer[RADIO_MAX_MESSAGE_BUFFER_LENGTH];
	uint16_t _messageBufferPosition;
	uint32_t _remainingMessageLength;
	uint16_t _currentMessageReceiver;
	byte _currentMessageHash[12];
	byte _currentMessageSignature[40];

	uint8_t _bestRssi;
	uint8_t _bestChannel;
	TickType_t _discoveryFinishingTime;
	TickType_t _lastMessageReceived;

	byte _outgoingPacketBuffer[RADIO_PACKET_LENGTH];
	bool _outgoingPacketAvailable;

	RadioState _radioState;
};
