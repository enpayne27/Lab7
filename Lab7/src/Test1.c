/*
 ============================================================================
 Name        : Test1.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "SerialWifiBridge.h"

/*
 ============================================================================
 Name        : Test1.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "ECE631JSON.h"

int main(void) {

	/*
	 Example of pack_json
	*/
	{
	char JSONStr[500];
	//{"Action":"WifiSetup","Wifi":{"SSID":"KSU Guest","Password":"","UpdateInterval":7}}
	pack_json("{s:s,s:{s:s,s:s,s:n}}", JSONStr, "Action","WifiSetup","Wifi","SSID","ece631Lab","Password","1234567890","UpdateInterval",Interval);
	printf("JSON String: %s\n\r",JSONStr);
	}
	{
	//{"Action":"MQTTPub","MQTT":{"Topic":"Topic String","Message":"Needs to Be JSON String"}}
	//Needs to JSON String == {"Temperature":3400,"Unit":"F"}
	char JSONStr[500];
	char JSONStr1[500];
	int Temp = 1<<31;
	pack_json("{s:n,s:s,s:b}", JSONStr1, "Temperature",Temp,"Unit","F","IsHeatOn","true");
	pack_json("{s,s:{s:s,s:s}}", JSONStr, "Action","MQTTPub","Topic","room.living","Message",JSONStr1);
	printf("JSON String: %s\n\r",JSONStr);
	}
	return EXIT_SUCCESS;
}
/*
 Output from above C code
----------------------------------------------------------------------------------------------------------------
JSON String: {"Action":"WifiSetup","Wifi":{"SSID":"ece631Lab","Password":"1234567890","UpdateInterval":7}}

JSON String: {"Action","MQTTPub":{"Topic":"room.living","Message":"{\"Temperature\":-2147483648,\"Unit\":\"F\",\"IsHeatOn\":true}"}}
----------------------------------------------------------------------------------------------------------------
 */


int main(void) {
	printf("Here are the Serial Wifi Bridge Responses and IDs\n");
	printf("Response -- ID\n");
	for(int i=0;i<TotalResponses;i++){
		printf("%s -- %d\n",ResponseItems[i].Name,ResponseItems[i].ID);
	}
	/*
	StartUp -- 1
	WifiStatus -- 2
	MQTTSetup -- 4
	MQTTPub -- 8
	MQTTSubs -- 16
	SubscribedMessage -- 32
	*/
	// Response Type Example
	//char Test[] = "StartUp";
	unsigned int Mask = BridgeResponseID(Test);
	switch(Mask){
	case StartUp:{
		break;
	}
	case WifiStatus:{
		break;
	}
	case MQTTSetup:{
		break;
	}
	case MQTTPub:{
		break;
	}
	case MQTTSubs:{
		break;
	}
	case SubscribedMessage:{
		break;
	}
	default:{
		printf("Bad ID\n");
		break;
	}
	}
	return EXIT_SUCCESS;
}
