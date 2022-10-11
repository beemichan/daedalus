exec O.$EPICS_HOST_ARCH/streamApp $0
dbLoadDatabase "O.Common/streamApp.dbd"
streamApp_registerRecordDeviceDriver


epicsEnvSet "STREAM_PROTOCOL_PATH","."

drvAsynSerialPortConfigure("AirSCPI.ino","/dev/ttyUSB0")
asynSetOption("AirSCPI",0,"baud","9600")
asynSetOption("AirSCPI",0,"bits","8")
asynSetOption("AirSCPI",0,"parity","none")
asynSetOption("AirSCPI",0,"stop","1")
asynSetOption("AirSCPI",0,"clocal","Y")
asynSetOption("AirSCPI",0,"crtscts","N")

#drvAsynIPPortConfigure "LO","localhost:40000"
#vxi11Configure "LO","192.168.1.236",0,0.0,"gpin0"

epicsThreadSleep(5) # empirically necessary to pause here, to avoid communication timeout on first SCPI commands to Arduinos. -SKF April 5 2022

dbLoadRecords "air.db"

#log debug output to file
#streamSetLogfile StreamDebug.log

iocInit

#var streamDebug 1
