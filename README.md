# aws_monitoring
Extracting data received from the AWS nodes and inserting it into the database
The tcpListener listens on port 10020 to the incoming data to the server. It receives the string masks with data from the node and uses the keys defined in nodes.h to extract the values from the strings.
Whenever the string is received, it checks the node it belongs by checking the TXT value in the string. It only considers four nodes (Ground, 2meter, 10meter,Sink) from the Makerere aws.
tcpListener.c uses Global variables (struct) [see nodes.h] to store the values from each node after extracting them.
The values are then inserted into the database based on the corresponding table that has the parameter that the value represents.
