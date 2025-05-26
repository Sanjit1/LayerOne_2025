//#include <Arduino.h>
//  0    1    2    3    4    5    6    7
// PB0, PB1, PB2, PB3, PB4, PD4, PD5, PD6
const uint8_t charliePins[8] = { 9, 10, 11, 12, 13, 6, 7, 8 };

// LED mapping: [ledNumber][0] = highPinIndex, [ledNumber][1] = lowPinIndex
// const uint8_t ledMap[50][2] = {
//   {0, 0}, {0, 0},  // LED1, LED2 DO NOT EXIST
//   {4, 2}, {2, 4},  // LED3, LED4
//   {4, 1}, {1, 4},  // LED5, LED6
//   {4, 0}, {0, 4},  // LED7, LED8
//   {4, 7}, {7, 4},  // LED9, LED10
//   {4, 3}, {3, 4},  // LED11, LED12
//   {6, 3}, {3, 6},  // LED13, LED14
//   {3, 1}, {1, 3},  // LED15, LED16
//   {3, 0}, {0, 3},  // LED17, LED18
//   {3, 7}, {7, 3},  // LED19, LED20
//   {2, 3}, {3, 2},  // LED21, LED22
//   {2, 1}, {1, 2},  // LED23, LED24
//   {2, 0}, {0, 2},  // LED25, LED26
//   {2, 7}, {7, 2},  // LED27, LED28
//   {2, 7}, {7, 2},  // LED29, LED30
//   {1, 0}, {0, 1},  // LED31, LED32
//   {1, 7}, {7, 1},  // LED33, LED34
//   {0, 7}, {7, 0},  // LED35, LED36
//   {1, 6}, {6, 1},  // LED37, LED38
//   {0, 6}, {6, 0},  // LED39, LED40
//   {7, 6}, {6, 7},  // LED41, LED42
//   {6, 4}, {4, 6},  // LED43, LED44
//   {5, 6}, {6, 5},  // LED45, LED46
//   {5, 4}, {4, 5},  // LED47, LED48
//   {5, 3}, {3, 5},  // LED49, LED50
// };

// so these leds are arranged in an 8x6 grid, but the mapping is not straightforward.
// const uint8_t ledGrid[8][6] = {
//   {17, 25, 33, 41, 7, 45},
//   {16, 24, 32, 40, 6, 46},
//   {15, 23, 31, 39, 5, 47},
//   {14, 22, 30, 38, 4, 48},
//   {13, 21, 29, 37, 3, 49},
//   {12, 20, 28, 36, 44, 50},
//   {11, 19, 27, 35, 43, 9},
//   {10, 18, 26, 34, 42, 8}
// };

const uint8_t ledGrid[8][6][2] = {
  { {3, 0}, {2, 0}, {1, 7}, {7, 6}, {4, 0}, {5, 6} },
  { {1, 3}, {1, 2}, {0, 1}, {6, 0}, {1, 4}, {6, 5} },
  { {3, 1}, {2, 1}, {1, 0}, {0, 6}, {4, 1}, {5, 4} },
  { {3, 6}, {3, 2}, {7, 2}, {6, 1}, {2, 4}, {4, 5} },
  { {6, 3}, {2, 3}, {2, 7}, {1, 6}, {4, 2}, {5, 3} },
  { {3, 4}, {7, 3}, {7, 2}, {7, 0}, {4, 6}, {3, 5} },
  { {4, 3}, {3, 7}, {2, 7}, {0, 7}, {6, 4}, {4, 7} },
  { {7, 4}, {0, 3}, {0, 2}, {7, 1}, {6, 7}, {0, 4} },
};


void setup() {
  for (uint8_t i = 0; i < 8; i++) {
    pinMode(charliePins[i], INPUT);
  }
}

void lightGridPosition(uint8_t row, uint8_t col) {
  if (row >= 8 || col >= 6) return;  // bounds check

  uint8_t highIdx = ledGrid[row][col][0];
  uint8_t lowIdx = ledGrid[row][col][1];

  for (uint8_t i = 0; i < 8; i++) {
    pinMode(charliePins[i], INPUT);
  }

  pinMode(charliePins[highIdx], OUTPUT);
  digitalWrite(charliePins[highIdx], HIGH);

  pinMode(charliePins[lowIdx], OUTPUT);
  digitalWrite(charliePins[lowIdx], LOW);
}

void loop() {
// light up each of the grid one by one
  for (uint8_t i = 0; i < 8; i++) {
    for (uint8_t j = 0; j < 6; j++) {
      lightGridPosition(i, j);
      delay(50);  // wait for 500ms before lighting the next position
    }
  }
}
