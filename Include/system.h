#ifndef SYSTEM_H_
#define SYSTEM_H_






















//------------------------------------------------------------------------------
// Prototypes
//------------------------------------------------------------------------------
void system_init(void);
void SystemClock_Config(void);
void _Error_Handler(char *file, int line);
void assert_failed(uint8_t* file, uint32_t line);

#endif /* SYSTEM_H_ */
