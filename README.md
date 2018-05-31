# aws_monitoring

This AwsDataReceiver is one of the components of the Aws Monitor System. Read about the whole project here
http://kibsys.com/wimeaict-aws-monitoring/
 
This Data Receuver  involves programs/scripts that collect and store the data from the nodes at the automatic weather station..

The parameters in the config.h must be set to the appropriate values. The reports considered by this AwsDataReceiver must be similar to the one below.

2017-08-02 12:10:14 TZ=UTC UT=1501675814 GW_LAT=0.32920 GW_LON=32.57100 &: TXT=makg2-sink E64=fcc23d000001845d PS=0 T=30.56  V_MCU=3.00 UP=0x30492 V_IN=4.82  P_MS5611=879.35  [ADDR=31.193 SEQ=1 TTL=0 RSSI=12 LQI=255 DRP=0.00 DELAY=0]

The keys being referred to are the GW_LAT, GW_LON, TXT, E64, PS, V_MCU etc. The nodes.h file assumes that a report from the 10m from the station uses those keys. In case maybe "LAT" is used to capture Latitude values, then the value of of GW_LAT under the 10m node must be changed from "GW_LAT" to "LAT" so that the latitude value is captured well when the data comes in.

MYSQL-CONNNECTOR must be installed on the computer before the code can be compiled. Refer to the link https://dev.mysql.com/doc/connector-c/en/connector-c-introduction.html for more information.

To install on the Mysql C connector on linux use the command
  $sudo apt-get install libmysqlclient libmysqlclient-dev

Once the nodes.h, config.h have been configured, the tcpListener can be compiled using the command:
gcc -o AwsDataReceiver AwsDataReceiver.c  -I/usr/include/mysql  -lmysqlclient -lz -lpthread 

The command creates an executable AwsDataReceiver which can be executed by running ./AwsDataReceiver on the terminal

Make sure to create a file config.h by copying example.config.h and make the changes for the database access


