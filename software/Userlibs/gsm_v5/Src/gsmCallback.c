
#include "gsm.h"
#include "cmsis_os.h"

#if (_GSM_CALL == 1 || _GSM_MSG == 1 || _GSM_GPRS == 1)
//###############################################################################################################
void gsm_callback_simcardReady(void)
{
  gsm_printf("CALLBACK SIMCARD READY\r\n");
}
//###############################################################################################################
void gsm_callback_simcardPinRequest(void)
{
  gsm_printf("CALLBACK SIMCARD PIN\r\n");
}
//###############################################################################################################
void gsm_callback_simcardPukRequest(void)
{
  gsm_printf("CALLBACK SIMCARD PUK\r\n");
}
//###############################################################################################################
void gsm_callback_simcardNotInserted(void)
{
  gsm_printf("CALLBACK SIMCARD NOT DETECT\r\n");
}
//###############################################################################################################
void gsm_callback_networkRegister(void)
{
  gsm_printf("CALLBACK NETWORK REGISTER\r\n");
}
//###############################################################################################################
void gsm_callback_networkUnregister(void)
{
  gsm_printf("CALLBACK NETWORK UNREGISTER\r\n");
}
//###############################################################################################################
#if (_GSM_CALL == 1)
void gsm_callback_newCall(const char *number)
{
  gsm_printf("CALLBACK NEW CALL FROM: %s\r\n", number);
  //gsm_call_answer();
}
//###############################################################################################################
void gsm_callback_endCall(void)
{
  gsm_printf("CALLBACK END CALL\r\n");
}
//###############################################################################################################
void gsm_callback_dtmf(char *string, uint8_t len)
{
  gsm_printf("CALLBACK DTMF %s, LEN:%d\r\n", string, len);
}
#endif
//###############################################################################################################
#if (_GSM_MSG == 1)
void gsm_callback_newMsg(char *number, gsm_time_t time, char *msg)
{
	extern osMessageQueueId_t sender_num_queueHandle;
	extern osThreadId_t send_sms_semHandle;
	char buff[16] = {'\0'};
	strcpy(buff, number);

	gsm_printf("CALLBACK NEW MESSAGE FROM %s, LEN:%d\r\n", number, strlen(msg));
	gsm_printf("%s\r\n", msg);

//	if (gsm_number_validation(number)) {
//		if (strcmp(msg, "GET GPS") == 0) {
			osMessageQueuePut(sender_num_queueHandle, number, 0, osWaitForever);
			osSemaphoreRelease(send_sms_semHandle);
//		}
//	}
}
#endif
//###############################################################################################################
#if (_GSM_GPRS == 1)
void gsm_callback_gprsConnected(void)
{
  gsm_printf("CALLBACK GPRS CONNECTED, IP: %s\r\n", gsm.gprs.ip);
}
//###############################################################################################################
void gsm_callback_gprsDisconnected(void)
{
  gsm_printf("CALLBACK GPRS DISCONNECTED\r\n");
}
//###############################################################################################################
void gsm_callback_mqttMessage(char *topic, char *message)
{
  gsm_printf("CALLBACK GPRS MQTT TOPIC: %s   ----   MESSAGE: %s\r\n", topic, message);
}
//###############################################################################################################
void gsm_callback_mqttDisconnect(void)
{
  gsm_printf("CALLBACK GPRS MQTT DISCONNECT\r\n");
}
//###############################################################################################################
#endif
#endif
