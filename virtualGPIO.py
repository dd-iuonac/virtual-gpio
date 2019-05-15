import time

import serial

PORT = "COM3"
BAUD_RATE = 9600
STD_TIMEOUT = 0.8


HIGH = 2
LOW = 1

A0 = 14   # the analog pins
A1 = 15
A2 = 16
A3 = 17
A4 = 18
A5 = 19
A6 = 20
A7 = 21

OUT = 2
IN = 1

Serial = serial.Serial(PORT, BAUD_RATE, timeout=STD_TIMEOUT, dsrdtr=False)


def _serial_write(message: str):
    Serial.write(message.encode("utf-8"))


def _serial_read(count=1):
    return Serial.read(count)


def setup(pin: int, mode: int):
    _serial_write("1/" + str(pin) + "/" + str(mode) + "/")


def digital_read(pin: int):
    _serial_write("3/2/" + str(pin) + "/")
    time.sleep(STD_TIMEOUT)
    return _serial_read()


def analog_read(pin: int):
    _serial_write("3/1/" + str(pin) + "/")
    time.sleep(STD_TIMEOUT)
    return _serial_read()


def digital_write(pin: int, value: int):
    _serial_write("2/2/" + str(pin) + "/" + str(value) + "/")


def analog_write(pin: int, value: int):
    _serial_write("2/1/" + str(pin) + "/" + str(value) + "/")

