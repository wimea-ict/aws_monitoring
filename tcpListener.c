/*By Kasumba Robert and Kiryamwibo Yenus*/
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <string.h>
#include "nodes.h" //stores the node parameters
#include </usr/include/mysql/mysql.h>
#include </usr/include/mysql/my_global.h>
 #include <unistd.h>
#include <stdlib.h>


#define AF_NET 2
#define TEN_M_KEY "TXT=makg2-10m"
#define TWO_M_KEY "TXT=makg2-2m"
#define GROUND_KEY "TXT=makg2-gnd"
#define SINK_KEY "TXT=makg2-sink"
struct sockaddr_in addr,clientAddr;
struct two_meter_record two_meter_node;
struct ground_node_record ground_node;
struct ten_meter_record ten_meter_node;
struct sink_node_record sink_node;
MYSQL *connection;

char *findKeyValue(char *substr,char *key);
void process2meterString(char buffer[]);
void process10meterString(char buffer[]);
void processSinkNodeString(char buffer[]);
void processGroundNodeString(char buffer[]);
char *getZuluTime(char *normaltime);//format is hh:mm:ss
MYSQL *connect2db();

int main(void){
    pid_t pid = 0;
    pid_t sid = 0;
    pid =fork();
    FILE *fp=NULL;
    if(pid<0){
        printf("Fork failed \n");
        exit(1);
    }
    
    if(pid>0){
         printf("pid of the child process is %d \n",pid);
        exit(0);
    }
    umask(0);
    
    sid =setsid();
    
    if(sid < 0)
    {
        exit(1);
    }
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    fp =fopen("listenerlogs.txt","w+");
    unsigned int clientLen = sizeof(clientAddr);
    int listen_status;
    int socketId = socket(AF_NET,SOCK_STREAM,0);
    int RCVBUFSIZE =256;
    char buffer[RCVBUFSIZE];
    addr.sin_family =AF_NET;
    addr.sin_port = htons(10020);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    float dry_bulb,wet_bulb,dew_point,humidity;
    int bind_status = bind(socketId, (struct sockadrr*) &addr, sizeof(addr));
     MYSQL_RES *res;
     MYSQL_ROW row;
    char space[2]=" ";
    char *report;
    char *reports[25];
    char *record;
    char status_query_template[] = "INSERT INTO nodestatus(V_MCU,V_IN,RSSI,LQI,DRP,date,time,TXT,E64,StationNumber) VALUES('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')";
    char station_Number_template[] ="SELECT StationNumber FROM stations WHERE Latitude = '%s' AND Longitude ='%s'";
    char temp_humid_template[]="INSERT INTO observationslip(Date,StationNumber,TIME,Dry_Bulb, Wet_Bulb,SubmittedBy) VALUES('%s','%s','%s','%f','%f','AWS')";
    char soil_rain_template[]="INSERT INTO observationslip(Date,StationNumber,TIME,SoilTemperature,SoilMoisture,Rainfall,SubmittedBy) VALUES('%s','%s','%s','%s','%s','%s','AWS')";
    char pressure_template[]="INSERT INTO observationslip(Date,StationNumber,TIME,CLP,SubmittedBy) VALUES('%s','%s','%s','%s','AWS')";
    char wind_template[] = "INSERT INTO observationslip(Date,StationNumber,TIME,Wind_Direction,Wind_Speed,SubmittedBy) VALUES('%s','%s','%s','%s','%s','AWS')";
    char station_Number_query[256];//will have the query to get the station Number based on the latitude and longitude
    char station_Number[10];
    char soil_rain_query[256];//holds the query that inserts the soiltemperature,soilmoisture,rainfall;
    char temp_humid_query[256];//will hold the query to insert data from 2m node
    char status_query[256];//holds the query to insert the node status info int nodestatus table
    char pressure_query[256];//holds the query to insert the pressure got from the ground node
    char wind_query[256];//holds a query to insert data about wind status from the 10M node
    int counter =0;
    int max;
    int i_counter=0;
    
    if(bind_status != -1){
        fprintf(fp,"Binded successfully to port %d \n",addr.sin_port);
        connection = connect2db();
        listen_status = listen(socketId, 128);
        if(listen_status != -1){
            fprintf(fp,"Now the server is listening \n");
            int clientSockId = accept(socketId,(struct sockadrr *) &clientAddr,&clientLen);
            
            fprintf(fp,"The client socket id is %d\n",clientSockId);
            int recvMsgSize;
            if(clientSockId != -1){
                while(1){
                    recvMsgSize = recv(clientSockId, buffer, RCVBUFSIZE, 0); 
                    if(recvMsgSize>0){
                       // fprintf(fp,"%s",buffer);
                        counter=0;
                        if(strstr(buffer,TEN_M_KEY)!=NULL){
                            //when it's 10 meter 
                            process10meterString(buffer);
                             fprintf(fp,"\n10m: %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s ",ten_meter_node.date_10m,ten_meter_node.time_10m,ten_meter_node.gw_lat_10m,ten_meter_node.gw_long_10m,ten_meter_node.ps_10m,ten_meter_node.t_10m,
                                ten_meter_node.e64_10m,ten_meter_node.v_mcu_10m,ten_meter_node.v_in_10m,ten_meter_node.v_a1_10m,ten_meter_node.v_a2_10m,ten_meter_node.v_a3_10m,
                                ten_meter_node.ttl_10m,ten_meter_node.rssi_10m,ten_meter_node.lqi_10m,ten_meter_node.drp_10m
                                );
                             sprintf(station_Number_query,station_Number_template,ten_meter_node.gw_lat_10m,ten_meter_node.gw_long_10m);
                            if(mysql_query(connection,station_Number_query)){
                                fprintf(fp, "%s\n", mysql_error(connection));
                            }
                            res = mysql_use_result(connection);
                            i_counter=0;
                            while((row = mysql_fetch_row(res)) != NULL){
                                    if(i_counter==0){
                                       strcpy(station_Number ,row[0]);  
                                    }
                                    i_counter++;
                                }
                             
                            sprintf(status_query,status_query_template,ten_meter_node.v_mcu_10m,ten_meter_node.v_in_10m,ten_meter_node.rssi_10m,ten_meter_node.lqi_10m,ten_meter_node.drp_10m,ten_meter_node.date_10m,ten_meter_node.time_10m,ten_meter_node.txt_10m,ten_meter_node.e64_10m,station_Number);
                            
                            if (mysql_query(connection,status_query)) {
                                fprintf(fp, "%s\n", mysql_error(connection));
                             }
                            sprintf(wind_query,wind_template,ten_meter_node.date_10m,station_Number,getZuluTime(ten_meter_node.time_10m),ten_meter_node.v_a1_10m,ten_meter_node.v_a2_10m);
                            fprintf(fp,"\n%s\n",wind_query);
                            
                        }
                        else if(strstr(buffer,TWO_M_KEY)!=NULL){
                            process2meterString(buffer);
                            fprintf(fp,"\n2m: %s %s %s  %s %s %s %s %s %s %s %s",two_meter_node.date_2m,two_meter_node.time_2m,
                                two_meter_node.gw_lat_2m,two_meter_node.gw_long_2m,two_meter_node.v_mcu_2m,two_meter_node.v_in_2m,
                                 two_meter_node.t_sht2x_2m,two_meter_node.rh_sht2x_2m,two_meter_node.ttl_2m,two_meter_node.rssi_2m,two_meter_node.lqi_2m
                                 );
                            //generating the query string to get the station Number
                            sprintf(station_Number_query,station_Number_template,two_meter_node.gw_lat_2m,two_meter_node.gw_long_2m);
                            
                            if(mysql_query(connection,station_Number_query)){
                                fprintf(fp, "%s\n", mysql_error(connection));
                            }
                            res = mysql_use_result(connection);
                            i_counter=0;
                            //extracting the station Number
                            while((row = mysql_fetch_row(res)) != NULL){
                                    if(i_counter==0){
                                       strcpy(station_Number ,row[0]);  
                                    }
                                    i_counter++;
                                }
                             //generating the query to insert query to insert the node status information
                            sprintf(status_query,status_query_template,two_meter_node.v_mcu_2m,two_meter_node.v_in_2m,two_meter_node.rssi_2m,two_meter_node.lqi_2m,two_meter_node.drp_2m,two_meter_node.date_2m,two_meter_node.time_2m,two_meter_node.txt_2m,two_meter_node.e64_2m,station_Number);
                            //inserting the node status information
                            if (mysql_query(connection,status_query)) {
                                fprintf(fp, "%s\n", mysql_error(connection));
                             }
                            
                            //calculating the dew_point
                            dry_bulb = atof(two_meter_node.t_sht2x_2m);
                            humidity = atof(two_meter_node.rh_sht2x_2m);
                            
                            dew_point = (humidity*dry_bulb)/100;
                            wet_bulb = ((2*dew_point)+dry_bulb)/3;
                            //generating the query to insert humidity and temperature                     
                            sprintf(temp_humid_query,temp_humid_template,two_meter_node.date_2m,station_Number,getZuluTime(two_meter_node.time_2m),dry_bulb,wet_bulb);
                            fprintf(fp,"\n%s\n",temp_humid_query);
                            if (mysql_query(connection,temp_humid_query)) {
                                fprintf(fp, "%s\n", mysql_error(connection));
                             }
                            }
                        else if(strstr(buffer,GROUND_KEY)!=NULL){
                            processGroundNodeString(buffer);
                            fprintf(fp,"\ngnd: %s  %s %s  %s %s %s %s %s %s %s %s %s %s",ground_node.date_gnd,ground_node.time_gnd,
                            ground_node.gw_lat_gnd,ground_node.gw_long_gnd,ground_node.ps_gnd,ground_node.p0_gnd,
                             ground_node.up_gnd,ground_node.p0_lst60_gnd,ground_node.v_a1_gnd,ground_node.v_a2_gnd,
                             ground_node.ttl_gnd,ground_node.rssi_gnd,ground_node.lqi_gnd
                             );//printing the captured data
                            sprintf(station_Number_query,station_Number_template,ground_node.gw_lat_gnd,ground_node.gw_long_gnd);
                            if(mysql_query(connection,station_Number_query)){
                                fprintf(fp, "%s\n", mysql_error(connection));
                            }
                            res = mysql_use_result(connection);
                            i_counter=0;
                            while((row = mysql_fetch_row(res)) != NULL){
                                    if(i_counter==0){
                                       strcpy(station_Number,row[0]);
                                    }
                                    i_counter++;
                                   
                                }                            
                            sprintf(status_query,status_query_template,ground_node.v_mcu_gnd,ground_node.v_in_gnd,ground_node.rssi_gnd,ground_node.lqi_gnd,ground_node.drp_gnd,ground_node.date_gnd,ground_node.time_gnd,ground_node.txt_gnd,ground_node.e64_gnd,station_Number);
                            
                            if (mysql_query(connection,status_query)) {
                                fprintf(fp, "%s\n", mysql_error(connection));
                             }
                            sprintf(soil_rain_query,soil_rain_template,ground_node.date_gnd,station_Number,getZuluTime(ground_node.time_gnd),ground_node.v_a2_gnd,ground_node.v_a1_gnd,ground_node.p0_lst60_gnd);
                            fprintf(fp,"\n%s\n",soil_rain_query);
                            if (mysql_query(connection,temp_humid_query)) {
                                fprintf(fp, "%s\n", mysql_error(connection));
                             }
                            }
                        else if(strstr(buffer,SINK_KEY)!=NULL){
                            processSinkNodeString(buffer);
                            fprintf(fp,"\nsink: %s %s %s  %s %s %s %s %s %s %s %s %s %s %s %s",sink_node.date_sink,sink_node.time_sink,
                            sink_node.gw_lat_sink,sink_node.gw_long_sink,sink_node.ps_sink,sink_node.t_sink,sink_node.up_sink,
                             sink_node.e64_sink,sink_node.v_mcu_sink,sink_node.v_in_sink,sink_node.p_ms5611_sink,
                             sink_node.ttl_sink,sink_node.rssi_sink,sink_node.lqi_sink,sink_node.drp_sink
                             );
                            sprintf(station_Number_query,station_Number_template,sink_node.gw_lat_sink,sink_node.gw_long_sink);
                            if(mysql_query(connection,station_Number_query)){
                                fprintf(fp, "%s\n", mysql_error(connection));
                            }
                            res = mysql_use_result(connection);
                            i_counter=0;
                            while((row = mysql_fetch_row(res)) != NULL){
                                    if(i_counter==0){
                                       strcpy(station_Number ,row[0]);  
                                    }
                                    i_counter++;
                                }
                            sprintf(status_query,status_query_template,sink_node.v_mcu_sink,sink_node.v_in_sink,sink_node.rssi_sink,sink_node.lqi_sink,sink_node.drp_sink,sink_node.date_sink,sink_node.time_sink,sink_node.txt_sink,sink_node.e64_sink,station_Number);
                            
                            if (mysql_query(connection,status_query)) {
                                fprintf(fp, "%s\n", mysql_error(connection));
                             }
                            sprintf(pressure_query,pressure_template,sink_node.date_sink,station_Number,getZuluTime(sink_node.time_sink),sink_node.up_sink);
                             fprintf(fp,"\n%s\n",pressure_query);
                            if (mysql_query(connection,pressure_query)) {
                                fprintf(fp, "%s\n", mysql_error(connection));
                             }
                        }
                            else{
                                
                            }
                    }
                    
                }
            }
        }
        else{
            fprintf(fp,"Failed to listen\n");
        }
    }
    
}

void process2meterString(char buffer[]){
    char space[2]=" ";
    char *report;
    char *reports[25];
    char *record;
    int max;
    int counter=0;
    report = strtok(buffer,space);
      counter=0;
      while(report != NULL){
          reports[counter]=report;
          report = strtok(NULL,space);
          counter++;
      }
      max=counter;
    counter=0;
    while(counter<=max-1){
         report=reports[counter];
         if(counter==0){
              two_meter_node.date_2m=report;
          }else if(counter==1){
              two_meter_node.time_2m =report;
          }else 
          {   
              if(strstr(reports[counter],GW_LAT_2M_KEY) !=NULL){
                  two_meter_node.gw_lat_2m = findKeyValue(reports[counter],GW_LAT_2M_KEY);
              }else if(strstr(reports[counter],GW_LONG_2M_KEY) !=NULL){

                  two_meter_node.gw_long_2m = findKeyValue(reports[counter],GW_LONG_2M_KEY);
              }else if(strstr(reports[counter],V_MCU_2M_KEY) !=NULL){

                two_meter_node.v_mcu_2m = findKeyValue(reports[counter],V_MCU_2M_KEY);
              }else if(strstr(reports[counter],TXT_2M_KEY) !=NULL){

                two_meter_node.txt_2m = findKeyValue(reports[counter],TXT_2M_KEY);
              }
              else if(strstr(reports[counter],V_IN_2M_KEY) !=NULL){
                  two_meter_node.v_in_2m = findKeyValue(reports[counter],V_IN_2M_KEY);  
              }else if(strstr(reports[counter],T_SHT2X_2M_KEY) !=NULL){
                  two_meter_node.t_sht2x_2m = findKeyValue(reports[counter],T_SHT2X_2M_KEY);

              }else if(strstr(reports[counter],RH_SHT2X_2M_KEY) !=NULL){

                  two_meter_node.rh_sht2x_2m = findKeyValue(reports[counter],RH_SHT2X_2M_KEY);
              }else if(strstr(reports[counter],TTL_2M_KEY) !=NULL){

                  two_meter_node.ttl_2m = findKeyValue(reports[counter],TTL_2M_KEY);
              }else if(strstr(reports[counter],RSSI_2M_KEY) !=NULL){

                  two_meter_node.rssi_2m =findKeyValue(reports[counter],RSSI_2M_KEY);
              }else if(strstr(reports[counter],LQI_2M_KEY) !=NULL){

                  two_meter_node.lqi_2m = findKeyValue(reports[counter],LQI_2M_KEY);
              }
              else if(strstr(reports[counter],DRP_2M_KEY) !=NULL){

                  two_meter_node.drp_2m = findKeyValue(reports[counter],DRP_2M_KEY);
              }
              
          } 
//                              	fprintf(fp,"%d =%d \n",max,counter);
           counter++;
          //fprintf(fp,"%d =%d \n",max,counter);
          }
     // fprintf(fp,"%d here",counter);
      
    
}
MYSQL *connect2db(){
   MYSQL *conn;
   MYSQL_RES *res;
   MYSQL_ROW row;

   char *server = "server address";//server address
   char *user = "username";//the username
   char *password = "password"; //the password
   char *database = "database_name";
   conn = mysql_init(NULL);

   /* Connect to database */
   if (!mysql_real_connect(conn, server,
         user, password, database, 0, NULL, 0)) {
     // fprintf(fp, "%s\n", mysql_error(conn));
      return NULL;
   }
   else{
       return conn;
   }
}
void process10meterString(char buffer[]){
    char space[2]=" ";
    char *report;
    char *reports[25];
    char *record;
    int max;
    int counter=0;
     report = strtok(buffer,space);
    counter=0;
    while(report != NULL){
        reports[counter]=report;
        report = strtok(NULL,space);
        counter++;
    }
    max=counter;
    counter=0;
    while(counter<=max-1){
       report=reports[counter];
       if(counter==0){
            ten_meter_node.date_10m=report;
        }else if(counter==1){
            ten_meter_node.time_10m =report;
        }else 
        {   
            if(strstr(reports[counter],GW_LAT_10M_KEY) !=NULL){
                ten_meter_node.gw_lat_10m = findKeyValue(reports[counter],GW_LAT_10M_KEY);
            }else if(strstr(reports[counter],GW_LONG_10M_KEY) !=NULL){

                ten_meter_node.gw_long_10m = findKeyValue(reports[counter],GW_LONG_10M_KEY);
            }else if(strstr(reports[counter],PS_10M_KEY) !=NULL){
              ten_meter_node.ps_10m = findKeyValue(reports[counter],PS_10M_KEY);
            }
            else if(strstr(reports[counter],PS_10M_KEY) !=NULL){
                ten_meter_node.ps_10m = findKeyValue(reports[counter],PS_10M_KEY);  
            }else if(strstr(reports[counter],E64_10M_KEY) !=NULL){
                ten_meter_node.e64_10m = findKeyValue(reports[counter],E64_10M_KEY);

            }else if(strstr(reports[counter],V_MCU_10M_KEY) !=NULL){

                ten_meter_node.v_mcu_10m = findKeyValue(reports[counter],V_MCU_10M_KEY);
            }else if(strstr(reports[counter],T_10M_KEY) !=NULL && strstr(reports[counter],"TZ")==NULL && strstr(reports[counter],"UTC")==NULL){
                ten_meter_node.t_10m = findKeyValue(reports[counter],T_10M_KEY);

            }else if(strstr(reports[counter],V_A1_10M_KEY) !=NULL){
                ten_meter_node.v_a1_10m = findKeyValue(reports[counter],V_A1_10M_KEY);
            }else if(strstr(reports[counter],V_A2_10M_KEY) !=NULL){

                ten_meter_node.v_a2_10m =findKeyValue(reports[counter],V_A2_10M_KEY);
            }else if(strstr(reports[counter],V_IN_10M_KEY) !=NULL){

                ten_meter_node.v_in_10m =findKeyValue(reports[counter],V_IN_10M_KEY);
            }else if(strstr(reports[counter],V_A3_10M_KEY) !=NULL){

                ten_meter_node.v_a3_10m =findKeyValue(reports[counter],V_A3_10M_KEY);
            }
            else if(strstr(reports[counter],TTL_10M_KEY) !=NULL){

                ten_meter_node.ttl_10m = findKeyValue(reports[counter],TTL_10M_KEY);
            }else if(strstr(reports[counter],RSSI_10M_KEY) !=NULL){

                ten_meter_node.rssi_10m =findKeyValue(reports[counter],RSSI_10M_KEY);
            }else if(strstr(reports[counter],LQI_10M_KEY) !=NULL){
                ten_meter_node.lqi_10m = findKeyValue(reports[counter],LQI_10M_KEY);
            }
            else if(strstr(reports[counter],DRP_10M_KEY) !=NULL){
                ten_meter_node.drp_10m = findKeyValue(reports[counter],DRP_10M_KEY);
            }
            
        } 
//                              	fprintf(fp,"%d =%d \n",max,counter);
         counter++;
        //fprintf(fp,"%d =%d \n",max,counter);
        }
   // fprintf(fp,"%d here",counter);
   
    
}
void processSinkNodeString(char buffer[]){
        //when it's sink node
    char space[2]=" ";
    char *report;
    char *reports[25];
    char *record;
    int max;
    int counter=0;
    report = strtok(buffer,space);
    counter=0;
    while(report != NULL){
        reports[counter]=report;
        report = strtok(NULL,space);
        counter++;
    }
    max=counter;

    counter=0;
    while(counter<=max-1){
       report=reports[counter];
       if(counter==0){
            sink_node.date_sink=report;
        }else if(counter==1){
            sink_node.time_sink =report;
        }else 
        {   
            if(strstr(reports[counter],GW_LAT_SINK_KEY) !=NULL){
                sink_node.gw_lat_sink = findKeyValue(reports[counter],GW_LAT_SINK_KEY);
            }else if(strstr(reports[counter],GW_LONG_SINK_KEY) !=NULL){

                sink_node.gw_long_sink = findKeyValue(reports[counter],GW_LONG_SINK_KEY);
            }else if(strstr(reports[counter],PS_SINK_KEY) !=NULL){
              sink_node.ps_sink = findKeyValue(reports[counter],PS_SINK_KEY);
            }
            else if(strstr(reports[counter],PS_SINK_KEY) !=NULL){
                sink_node.ps_sink = findKeyValue(reports[counter],PS_SINK_KEY);  
            }else if(strstr(reports[counter],E64_SINK_KEY) !=NULL){
                sink_node.e64_sink = findKeyValue(reports[counter],E64_SINK_KEY);

            }else if(strstr(reports[counter],V_MCU_SINK_KEY) !=NULL){

                sink_node.v_mcu_sink = findKeyValue(reports[counter],V_MCU_SINK_KEY);
            }else if(strstr(reports[counter],TXT_SINK_KEY) !=NULL){

                sink_node.txt_sink = findKeyValue(reports[counter],TXT_SINK_KEY);
            }else if(strstr(reports[counter],E64_SINK_KEY) !=NULL){

                sink_node.e64_sink = findKeyValue(reports[counter],E64_SINK_KEY);
            }else if(strstr(reports[counter],UP_SINK_KEY) !=NULL){

                sink_node.up_sink = findKeyValue(reports[counter],UP_SINK_KEY);
            }else if(strstr(reports[counter], P_MS5611_SINK_KEY) !=NULL){

                sink_node.p_ms5611_sink = findKeyValue(reports[counter],P_MS5611_SINK_KEY);
            }else if(strstr(reports[counter],T_SINK_KEY) !=NULL && strstr(reports[counter],"TZ")==NULL && strstr(reports[counter],"UTC")==NULL){
                sink_node.t_sink = findKeyValue(reports[counter],T_SINK_KEY);

            }else if(strstr(reports[counter],V_IN_SINK_KEY) !=NULL){
                sink_node.v_in_sink = findKeyValue(reports[counter],V_IN_SINK_KEY);
            }
            else if(strstr(reports[counter],TTL_SINK_KEY) !=NULL){

                sink_node.ttl_sink = findKeyValue(reports[counter],TTL_SINK_KEY);
            }else if(strstr(reports[counter],RSSI_SINK_KEY) !=NULL){

                sink_node.rssi_sink =findKeyValue(reports[counter],RSSI_SINK_KEY);
            }else if(strstr(reports[counter],LQI_SINK_KEY) !=NULL){
                sink_node.lqi_sink = findKeyValue(reports[counter],LQI_SINK_KEY);
            }
            else if(strstr(reports[counter],DRP_SINK_KEY) !=NULL){
                sink_node.drp_sink = findKeyValue(reports[counter],DRP_SINK_KEY);
            }
        } 
//                              	fprintf(fp,"%d =%d \n",max,counter);
         counter++;
        //fprintf(fp,"%d =%d \n",max,counter);
        }
   // fprintf(fp,"%d here",counter);
    
  
}
void processGroundNodeString(char buffer[]){
    //when it's ground node
    char space[2]=" ";
    char *report;
    char *reports[25];
    char *record;
    int max;
    int counter=0;
    report = strtok(buffer,space);
    counter=0;
    while(report != NULL){
        reports[counter]=report;
        report = strtok(NULL,space);
        counter++;
    }
    max=counter;

    counter=0;
  while(counter<=max-1){
       report=reports[counter];
       if(counter==0){
            ground_node.date_gnd=report;
        }else if(counter==1){
            ground_node.time_gnd =report;
        }else 
        {   
            if(strstr(reports[counter],GW_LAT_GND_KEY) !=NULL){
                ground_node.gw_lat_gnd = findKeyValue(reports[counter],GW_LAT_GND_KEY);
            }else if(strstr(reports[counter],GW_LONG_GND_KEY) !=NULL){

                ground_node.gw_long_gnd = findKeyValue(reports[counter],GW_LONG_GND_KEY);
            }else if(strstr(reports[counter],PS_GND_KEY) !=NULL){
              ground_node.ps_gnd = findKeyValue(reports[counter],PS_GND_KEY);
            }
            else if(strstr(reports[counter],P0_GND_KEY) !=NULL){
                ground_node.p0_gnd = findKeyValue(reports[counter],P0_GND_KEY);  
            }else if(strstr(reports[counter],UP_GND_KEY) !=NULL){
                ground_node.up_gnd = findKeyValue(reports[counter],UP_GND_KEY);

            }
            else if(strstr(reports[counter],V_MCU_GND_KEY) !=NULL){

                ground_node.v_mcu_gnd = findKeyValue(reports[counter],V_MCU_GND_KEY);
              }
            else if(strstr(reports[counter],E64_GND_KEY) !=NULL){

                ground_node.e64_gnd = findKeyValue(reports[counter],E64_GND_KEY);
              }
            else if(strstr(reports[counter],TXT_GND_KEY) !=NULL){

                ground_node.txt_gnd = findKeyValue(reports[counter],TXT_GND_KEY);
              }
            else if(strstr(reports[counter],V_IN_GND_KEY) !=NULL){

                ground_node.v_in_gnd = findKeyValue(reports[counter],V_IN_GND_KEY);
              }
            else if(strstr(reports[counter],P0_LST60_GND_KEY) !=NULL){

                ground_node.p0_lst60_gnd = findKeyValue(reports[counter],P0_LST60_GND_KEY);
            }else if(strstr(reports[counter],TXT_GND_KEY) !=NULL){

                ground_node.txt_gnd = findKeyValue(reports[counter],TXT_GND_KEY);             
            }else if(strstr(reports[counter],V_A1_GND_KEY) !=NULL){
                ground_node.v_a1_gnd = findKeyValue(reports[counter],V_A1_GND_KEY);
            }else if(strstr(reports[counter],V_A2_GND_KEY) !=NULL){

                ground_node.v_a2_gnd =findKeyValue(reports[counter],V_A2_GND_KEY);
            }else if(strstr(reports[counter],TTL_GND_KEY) !=NULL){

                ground_node.ttl_gnd = findKeyValue(reports[counter],TTL_GND_KEY);
            }else if(strstr(reports[counter],RSSI_GND_KEY) !=NULL){

                ground_node.rssi_gnd =findKeyValue(reports[counter],RSSI_GND_KEY);
            }else if(strstr(reports[counter],LQI_GND_KEY) !=NULL){
                ground_node.lqi_gnd = findKeyValue(reports[counter],LQI_GND_KEY);
            }
            
        } 
//                              	fprintf(fp,"%d =%d \n",max,counter);
         counter++;
        //fprintf(fp,"%d =%d \n",max,counter);
        }
   // fprintf(fp,"%d here",counter);
    
}
char *findKeyValue(char *substr,char *key){
    //the substring should be of the form key=value
    if(strstr(substr,key)!=NULL){
        const char equal_symbol[2]="=";
        char *token;
        char *saveptr;
        token =strtok(substr,equal_symbol);
        if(*token==*key){
         token=strtok(NULL,equal_symbol);
          return token;
        }else{
            return NULL;
        }
        
    }else{
        return NULL;//the key is not contained in the substr
    }
}
char *getZuluTime(char *normaltime){//format is hh:mm:ss
    char delim[] =":";
    char *token = (char *) malloc(4);
    char holder[4];
    char *zulutime =(char *) malloc(8) ;
    int count =0;
    token =strtok(normaltime,delim);
    while(token!=NULL){
        if(count<2){
           strcat(zulutime,token);
        }
        token =strtok(NULL,delim);
        count++;
    }
    strcat(zulutime,"Z");
    if(token != NULL){
        free(token);
    }
    //free(zulutime);
    return zulutime;  
}