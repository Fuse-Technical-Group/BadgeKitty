
#pragma once
#include "pins.h"
#define LED_COUNT 2
#include <tinyNeoPixel.h>

tinyNeoPixel eyes = tinyNeoPixel(LED_COUNT, EYES, NEO_GRB);
