

#define 	PIN_LED_RED		22
#define 	PIN_LED_GREEN	21

#define     LED_OFF   	digitalWrite(PIN_LED_RED, LOW); digitalWrite(PIN_LED_GREEN, LOW)
#define     LED_RED   	digitalWrite(PIN_LED_RED, HIGH); digitalWrite(PIN_LED_GREEN, LOW)
#define     LED_GREEN  	digitalWrite(PIN_LED_RED, LOW); digitalWrite(PIN_LED_GREEN, HIGH)
#define     LED_YELLOW 	digitalWrite(PIN_LED_RED, HIGH); digitalWrite(PIN_LED_GREEN, HIGH)
