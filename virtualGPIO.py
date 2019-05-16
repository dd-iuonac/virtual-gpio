import time

import serial

PORT = "COM3"
BAUD_RATE = 9600
STD_TIMEOUT = 0.8

# DIGITAL PINS VALUE
HIGH = 2
LOW = 1

# ANALOG PINS
A0 = 14
A1 = 15
A2 = 16
A3 = 17
A4 = 18
A5 = 19
A6 = 20
A7 = 21

# PIN MODE
OUT = 2
IN = 1

Serial = serial.Serial(PORT, BAUD_RATE, timeout=STD_TIMEOUT,  dsrdtr=False)


def _serial_write(message: str):
    data = message.encode("utf-8")
    print("Sending: ", data)
    Serial.write(data)


def _serial_read(count=1):
    data = Serial.read(count)
    print("Received: ", data)
    return data


def setup(pin: int, mode: int):
    _serial_write("1/" + str(pin) + "/" + str(mode) + "/")
    time.sleep(STD_TIMEOUT)


def digital_read(pin: int):
    _serial_write("3/2/" + str(pin) + "/")
    time.sleep(STD_TIMEOUT)
    return _serial_read()


def analog_read(pin: int):
    _serial_write("3/1/" + str(pin) + "/")
    time.sleep(STD_TIMEOUT)
    return _serial_read(count=8)


def digital_write(pin: int, value: int):
    _serial_write("2/2/" + str(pin) + "/" + str(value) + "/")
    time.sleep(STD_TIMEOUT)


def analog_write(pin: int, value: int):
    _serial_write("2/1/" + str(pin) + "/" + str(value) + "/")
    time.sleep(STD_TIMEOUT)


