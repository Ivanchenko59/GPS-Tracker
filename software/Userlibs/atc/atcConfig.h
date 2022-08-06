
#ifndef _ATCCONFIG_H_
#define _ATCCONFIG_H_

#ifdef DEBUG
#define	_ATC_DEBUG            1       //  use printf debug
#else
#define	_ATC_DEBUG            0       //  use printf debug
#endif
#define	_ATC_RTOS             2       //  0: no rtos    1: cmsis_os v1    2: cmsis_os v2
#define	_ATC_RXSIZE           1024    //  at-command rx buffer size
#define	_ATC_SEARCH_CMD_MAX   5       //  maximum of answer in at-command
#define	_ATC_SEARCH_MAX       10      //  maximum	of always search in buffer
#define	_ATC_RXTIMEOUT_MS     50      //  rx timeout to get new packet

#endif /* _ATCCONFIG_H_ */
