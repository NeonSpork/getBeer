from w1thermsensor import W1ThermSensor


def getTemp():
    tempSensor = W1ThermSensor()
    temp = tempSensor.get_temperature()
    return temp
