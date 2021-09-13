#pragma once
typedef enum msgType	//type of messages used as enum
{
	joinRequest=0x01,	//used in pairing mode for join request
	joinAccept,			//used in pairing mode for join accept
	joinConfirm,		//used in pairing mode for join confirmation
	configReq,			//used in configuration mode for requesting configuration message
	configMsg,			//used in configuration mode for sending configuration message
	configAck,			//used in configuration mode for acknowledging configuration successfull
	sensorData,			//used in monitoring mode for sending sensor data and battery level
	ack,				//used for acknowledging a message received
	motorStatus,		//used for acknowleging status of motor
	alarm,				//used to send warning messages/error messages
	initController		//used to notify level monitor that the controller is recently initiated
}msgType; 

typedef enum devType {
	monitor = 0x01,
	controller,
	relayUnit
}devType;

typedef enum response {
	failure = 0x00,
	success
}response;

typedef enum motorState {
	on = 0x00,
	off,
	dryRun
}motorState;
/*
* Message type: Join Request
* devType: Device type
*/
typedef struct joinRequest {
	unsigned char devType;
}joinRequest;

/*
* Message type: Join Accept
* devID: Device ID, 
* secretKey: AES Secret Key
*/
typedef struct joinAccept {
	unsigned char devID[4];
	unsigned char secretKey[16];
	}joinAccept;

/*
* Message type: Join Confirm
* joinAck: Acknowledgement for joining confirmation
*/
typedef struct joinConfirm {
	unsigned char response;
}joinConfirm;

/*
* Message type: config Request
* devType: Device type
*/
typedef struct configReq {
	unsigned char devType;
}configReq;

/*
* Message type: Configuration Message
* lowThreshold: Height of lower threshold value
* highThreshold: Height of higher threshold value
* sendFrequency: Number of messages to be send in an hour
* backoffTries: Number of tries untill going back to normal mode
*/
typedef struct configmsg {
	float lowThreshold;
	float highThreshold;
	int sendFrequency;
	int backoffTries;
}configmsg;

/*
* Message type: config Acknowledgement
* configAck: Acknowledgement for configuration success
*/
typedef struct configAck {
	unsigned char response;
}configAck;

/*
* Message type: sensorData
* level: height of water level from the sensor
* batteryInfo: Battery voltage information
*/
typedef struct sensorData {
	float level;
	float batteryInfo;
}sensorData;

/*
* Message type: acknowledgment
* response : Acknowledgment response
*/
typedef struct ack {
	unsigned char response;
}ack;

/*
* Message type: Motor /Pump Status
* status: Working status of the motor
*/
typedef struct motorStatus {
	unsigned char motorState;
}motorStatus;

/*
* Message type: alarm
* dryRun: Warning to alarm a dry run state
* lowBattery: Warning to alarm a lowBattery state
* sensorErr: Warning to alarm a sensor error state
*/
typedef struct alarm {
	unsigned char dryRun;
	unsigned char lowBattery;
	unsigned char sensorErr;
}alarm;

/*
* Message type: Controller initialization / Restart 
* controllerRestart: Flag of controller restarted recently
*/
typedef struct initController {
	unsigned char controllerRestart;
}initController;