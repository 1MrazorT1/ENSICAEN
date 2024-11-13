// uart.h

// init uart interface
void InitUart(void);
// Send char via uart
void WriteChar(unsigned char ch);
// Receive char from uart
unsigned char ReadChar(void);
// Send text via uart
void WriteText(unsigned char *txt);
// Receive char from uart non stop
unsigned char ReadChar_nonstop(void);

