# aws_monitoring
The aws monitoring process involves programs/scripts that collect and insert the data(per minute) from the nodes at the automatic weather station as well as scripts that check the database to identify any issues with data or the station.

The programs(tcpListener.c, nodes.h, config.h) implemented in C are responsible for receiving the data from the nodes and inserting it into the database.[See their individual descriptions].

The php programs(awsmonitor.php and reportAwsIssues.php) are responsible for identifying and reporting issues with data in the nodestatus and observationslip. 


