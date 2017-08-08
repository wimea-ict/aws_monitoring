# aws_monitoring
The aws monitoring process involves programs/scripts that collect and insert the data(per minute) from the nodes at the automatic weather station as well as scripts that check the database to identify any issues with data or the station.

The programs(tcpListener.c, nodes.h, config.h) implemented in C are responsible for receiving the data from the nodes and inserting it into the database.[See their individual descriptions].


Extracting data received from the AWS nodes and inserting it into the database
The tcpListener listens on port or any specified to the incoming data to the server. It receives the string masks with data from the node and uses the keys defined in nodes.h to extract the values from the strings.
Whenever the string is received, it checks the node it belongs by checking the TXT value in the string. It only considers four nodes (Ground, 2meter, 10meter,Sink) from the Makerere aws.
tcpListener.c uses Global variables (struct) [see nodes.h] to store the values from each node after extracting them.
The values are then inserted into the database based on the corresponding table that has the parameter that the value represents.
