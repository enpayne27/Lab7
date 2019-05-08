/*
 * SerialWifiBridge.h
 *
 *  Created on: Apr 18, 2018
 *      Author: ece631
 */

#ifndef SERIALWIFIBRIDGE_H_
#define SERIALWIFIBRIDGE_H_

#include <string.h>

typedef enum BridgeResponses{
	StartUp = 1<<0, 					// StartUp -- 0
	WifiStatus = 1<<1,				// WifiStatus -- 1
	MQTTSetup = 1<<2,					// MQTTSetup -- 2
	MQTTPub = 1<<3,						// MQTTPub -- 3
	MQTTSubs = 1<<4,					// MQTTSubs -- 4
	SubscribedMessage = 1<<5	// SubscribedMessage -- 5
}BRIDGERESPONSES_t;

typedef struct ResponseItem{
	char Name[40];
	BRIDGERESPONSES_t ID;
}RESPONSEITEM_t;

#define TotalResponses 6
RESPONSEITEM_t ResponseItems[TotalResponses] = {
	{"StartUp",StartUp},
	{"WifiStatus",WifiStatus},
	{"MQTTSetup",MQTTSetup},
	{"MQTTPub",MQTTPub},
	{"MQTTSubs",MQTTSubs},
	{"SubscribedMessage",SubscribedMessage}
};

//Returns corresponding ID for response string received
unsigned int BridgeResponseID(char* ResponseStr){
	unsigned int Mask =0;
	for (int i=0;i<TotalResponses;i++){
		Mask |=(strcmp(ResponseStr,ResponseItems[i].Name)==0?ResponseItems[i].ID:0);
	}
	return Mask;
}
//Returns corresponding string name for response ID received
void getBridgeResponseName(BRIDGERESPONSES_t ID,char* Name){
	Name[0] = 0x0;
	for (int i=0;i<TotalResponses;i++){
		if (ID == ResponseItems[i].ID){
			strcpy(Name,ResponseItems[i].Name);
			return;
		}
	}
}
#endif /* SERIALWIFIBRIDGE_H_ */
