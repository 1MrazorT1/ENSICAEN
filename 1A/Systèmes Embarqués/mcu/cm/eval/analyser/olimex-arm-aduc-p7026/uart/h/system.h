// system.h

#define LED1_ON     GP4DAT &= ~0x00010000
#define LED1_OFF    GP4DAT |= 0x00010000

#define LED2_ON     GP4DAT &= ~0x00020000
#define LED2_OFF    GP4DAT |= 0x00020000

// Init Frequency
void InitFreq(void);

// Init Leds
void InitLeds(void);

