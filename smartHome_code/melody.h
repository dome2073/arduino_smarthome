/*"melody.h"
   스마트홈에 들어가는 경고음, 멜로디를 설정하는 헤더파일입니다.
*/

#include "setting.h"

#define C 262 // 도 
#define D 294 // 레 
#define E 330 // 미 
//#define F 349 // 파 
#define G 392 // 솔 
#define A 440 // 라 
#define B 494 // 시 

int notes[] = {523, 1046, 2093};
int notes_1[25] = { G, G, A, A, G, G, E, G, G, E, E, D, G, G, A, A, G, G, E, G, E, D, E, C };
int tempo = 200;

void ascMelody() {                   //상승음
  for (int i = 0; i < 3; i++) {
    tone(piezoPin, notes[i], tempo);
    delay(200);
  }
}

void dscMelody() {                   //하강음
  for (int i = 3; i >= 0; i--) {
    tone(piezoPin, notes[i], tempo);
    delay(200);
  }
}

//학교종이 땡땡땡//
void melody() {
  for (int i = 0; i < 12; i++) {
    tone (piezoPin, notes_1[i], tempo);
    delay (300);
  }
  delay(100);
  for (int i = 12; i < 25; i++) {
    tone (piezoPin, notes_1[i], tempo);
    delay(300);
  }
}
