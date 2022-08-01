
#ifndef _GSMCONFIG_H_
#define _GSMCONFIG_H_

#define _GSM_USART                      USART2
#define _GSM_KEY_GPIO                   PWRKEY_GSM_GPIO_Port
#define _GSM_KEY_PIN                    PWRKEY_GSM_Pin

#ifdef DEBUG
#define _GSM_DEBUG                      1       //  use printf debug
#else
#define _GSM_DEBUG                      0       //  use printf debug
#endif
#define _GSM_CALL                       0       //  enable call
#define _GSM_MSG                        1       //  enable message
#define _GSM_GPRS                       1       //  enable gprs
#define _GSM_BLUETOOTH                  0       //  enable bluetooth , coming soon

#endif /*_GSMCONFIG_H_ */
