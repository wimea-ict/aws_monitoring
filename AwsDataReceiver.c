/*By Kasumba Robert, Joshua Muhumuza, Eugene Tumwesigye, Steven Byarugaba*/
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <time.h>
#include "config.h" //store the configurations
#include </usr/include/mysql/mysql.h> //for wimea server
#include </usr/include/mysql/my_global.h> // for wimea server
//#include </usr/local/Cellar/mysql-connector-c/6.1.11/include/mysql.h>//for localhost (Kasumba's computer)
//#include </usr/local/Cellar/mysql-connector-c/6.1.11/include/my_global.h>//for localhost (Kasumba's computer)
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include "nodes.h"
#define AF_NET 2
#define RCVBUFSIZE 256
#define TEMPHOLDERSIZE 100
MYSQL *connect2db();
void clientStationHandler(void * clientSockId);
void saveMultipleRecords(char *args);
void saveSingleRecord(char *buffer,MYSQL *connection);
void resetDataHolder(char *array[],int size){
  //clears the array so that it can be used for other purposes
  int i=0;
  for(i=0;i<size;i++){
    array[i]=NULL;
  }
}
void signalHandler(int signal){
     void *array[10];
    size_t size;
    size = backtrace(array, 10);
   printf("\nError: Signal %d; %d frames found:\n", signal, size);
    //print out all the frames to stderr
    backtrace_symbols_fd(array, size, STDERR_FILENO);
    exit(1);
}

void *doWork(void *args) {
  char *buffer = (char *) args;
  int counter =0;
  printf("buffer %s\n",buffer);
}

int number_of_stations;
struct Station *stations[100];

/**
 * The replace function
 *
 * Searches all of the occurrences using recursion
 * and replaces with the given string
 * @param char * o_string The original string
 * @param char * s_string The string to search for
 * @param char * r_string The replace string
 * @return void The o_string passed is modified
 */
void replace(char * o_string, char * s_string, char * r_string) {
      //a buffer variable to do all replace things
      char buffer[2048];
      //to store the pointer returned from strstr
      char * ch;

      //first exit condition
      if(!(ch = strstr(o_string, s_string)))
              return;

      //copy all the content to buffer before the first occurrence of the search string
      strncpy(buffer, o_string, ch-o_string);

      //prepare the buffer for appending by adding a null to the end of it
      buffer[ch-o_string] = 0;

      //append using sprintf function
      sprintf(buffer+(ch - o_string), "%s%s", r_string, ch + strlen(s_string));

      //empty o_string for copying
      o_string[0] = 0;
      strcpy(o_string, buffer);
      //pass recursively to replace other occurrences
      return replace(o_string, s_string, r_string);
 }

int main(int argc, char const *argv[]) {
    MYSQL *connection = connect2db();
    char *stations_query ="SELECT station_id, Latitude ,Longitude  FROM stations WHERE stationCategory ='aws'";
    MYSQL_RES *stations_res;
    MYSQL_ROW station_row;
    int counter=0;
    if(mysql_query(connection,stations_query)){
       printf( "%s\n", mysql_error(connection));
    }
    stations_res = mysql_store_result(connection);
    number_of_stations=mysql_num_rows(stations_res);

    while((station_row = mysql_fetch_row(stations_res)) != NULL){
            struct Station *x =(struct Station *)malloc(sizeof(struct Station));
            //memset(x.id, '\0', sizeof(x.id));
            if(x != NULL){
           //printf("%s, %s, %s : %d\n",station_row[0],station_row[1],station_row[2], counter);
            strcpy(x->id ,station_row[0]);
            strcpy(x->latitude,station_row[1]);
            strcpy(x->longitude ,station_row[2]);
            stations[counter]=x;
            counter +=1;
          }
         }
    loadConfigurations(stations,connection,number_of_stations);
     /*pid_t pid = 0;
     pid_t sid = 0;
     pid =fork();
     FILE *fp=NULL;
     if(pid<0){
         printf("Fork failed \n");
         exit(1);
     }

     if(pid>0){
          printf("pid of the child process is %d \n",pid);
          //kill the parent process to leave the child as a daemon
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
      */
    signal(SIGABRT,signalHandler);

     struct sockaddr_in addr,clientAddr;
     unsigned int clientLen = sizeof(clientAddr);
     int listen_status;
     int socketId = socket(AF_NET,SOCK_STREAM,0);
     addr.sin_family =AF_NET;
     addr.sin_port = htons(TCP_LISTENER_PORT_NUMBER);
     addr.sin_addr.s_addr = htonl(INADDR_ANY);
     printf("LISTENER IS STARTED...\n");
     int bind_status = bind(socketId, (struct sockadrr*) &addr, sizeof(addr));
      int clientSockId;
      int new_sock;
     if(bind_status != -1){
         //connection = connect2db();

         listen_status = listen(socketId, 128);

         if(listen_status != -1){

             while(1){

                 while( (clientSockId = accept(socketId,(struct sockadrr *) &clientAddr,&clientLen)) )
                 {
                     puts("Connection has been made ...");
                     pthread_t new_thread;
                     // Copy the value of the accepted socket, in order to pass to the thread
                     //new_sock = malloc(4);
                     new_sock = clientSockId;

                     if(pthread_create( &new_thread, NULL,  clientStationHandler, (void *)&new_sock) < 0)
                     {
                         perror("could not create thread");
                         return 1;
                     }
                    //pthread_join(new_thread, NULL);
                       //  handler(clientSockId);
                 }
             }
         }
         else{
             printf("Failed to listen\n");
         }
     }
     else{
         printf("FAILED : The bind status is %d",bind_status);
     }



  return 0;
}


void clientStationHandler(void *clientSockId){
  char buffer[RCVBUFSIZE];
  int socketId = *((int *)clientSockId);
  int recvMsgSize;
  int counter =0;
  time_t curr_time, last_time;
  last_time =NULL;
  char temp_holder [RCVBUFSIZE*TEMPHOLDERSIZE]="";
  if(socketId != -1){
      while(1){
          recvMsgSize = recv(socketId, buffer, RCVBUFSIZE, 0);
          if(recvMsgSize>0){
                curr_time = time (NULL);//gets the time in seconds since 1970
                strcat(temp_holder, buffer);
                strcat(temp_holder, "~");
                pthread_t processor_thread;
                counter++;
                 printf("%s \n",temp_holder);
                if(counter==TEMPHOLDERSIZE){
                  //this section deals with data that may be coming in very slowly
                  char report[RCVBUFSIZE*TEMPHOLDERSIZE];
                  strcpy(report,temp_holder);
                  pthread_create(&processor_thread, NULL, saveMultipleRecords, (void *)report);
                  strcpy(temp_holder,"");
                  counter =0;
                  printf("Buffer Reset Fast\n");
                }
                else if((curr_time-last_time)>=10 && last_time != NULL){
                  //this section deals with data that may be coming in very slowly
                  char report[RCVBUFSIZE*(counter+2)];
                  strncpy(report,temp_holder,(RCVBUFSIZE*(counter+2)));
                  report[RCVBUFSIZE*(counter+2)]='\0';
                   
                  if(counter==1){
                        printf("CRUSHED DUE TO THIS\n");
                    saveSingleRecord(report,NULL);
                       strcpy(temp_holder,"");
                  }
                  else{
                    pthread_create(&processor_thread, NULL, saveMultipleRecords, (void *)report);
                       strcpy(temp_holder,"");
                  }
                  counter =0;
                  printf("Buffer Reset Slow\n");
                }
                last_time = curr_time;
              }
          }
          }
          else{
            printf("Client for %d has gone off",clientSockId);
          }
      }
void saveMultipleRecords(char *args){
  char *reports_combined = (char *) args; //pick the combined report passed
  char separator[2]="~";
  char *report;
  char *reports_extracted[TEMPHOLDERSIZE];
  int buffer_counter=0;
  report = strtok(reports_combined,separator);
  //separate the combined reports into single reports
  while(report != NULL){
      printf("Report: %s\n",report);
    reports_extracted[buffer_counter]=report;
    report = strtok(NULL,separator);
    buffer_counter++;
  }

  int number_of_reports=buffer_counter;
   MYSQL *connection = connect2db();

   buffer_counter =0;
   char buffer[RCVBUFSIZE];
    printf("Before loop, x = %d\n",number_of_stations);
   while(buffer_counter<TEMPHOLDERSIZE){

      if(reports_extracted[buffer_counter]==NULL){
        break; //there is no report
      }
      strcpy(buffer,reports_extracted[buffer_counter]);
      printf("THIS %s\n",buffer);
      saveSingleRecord(buffer,connection);
      printf("\nSaved Successfully\n");
       buffer_counter++;
}
    printf("After the loop, x = %d",number_of_stations);

   mysql_close(connection);
   return NULL;
}

void saveSingleRecord(char *buffer,MYSQL *connection){
  printf("Entered here \n");
  char *two_meter_report[20]={};
  char *ten_meter_report[20]={};
  char *sink_node_report[20]={};
  char *ground_node_report[20]={};
  char status_query_template[] = "INSERT INTO nodestatus(V_MCU,V_IN,RSSI,LQI,DRP,date,time,TXT,E64,SEQ,StationNumber) VALUES('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')";
  char station_Number_template[] ="SELECT StationNumber FROM stations WHERE Latitude = '%s' AND Longitude ='%s'";
  char temp_humid_template[]="INSERT INTO observationslip(Date,Station,TIME,Dry_Bulb, Wet_Bulb,SubmittedBy) VALUES('%s','%s','%s','%f','%f','AWS')";
  char soil_rain_template[]="INSERT INTO observationslip(Date,Station,TIME,SoilTemperature,SoilMoisture,Rainfall,SubmittedBy) VALUES('%s','%s','%s','%s','%s','%s','AWS')";
  char pressure_template[]="INSERT INTO observationslip(Date,Station,TIME,CLP,SubmittedBy) VALUES('%s','%s','%s','%s','AWS')";
  char wind_direction_template[] = "INSERT INTO observationslip(Date,Station,TIME,Wind_Direction,SubmittedBy) VALUES('%s','%s','%s','%.2f','AWS')";
  char wind_speed_template[] = "INSERT INTO observationslip(Date,Station,TIME,Wind_Speed,SubmittedBy) VALUES('%s','%s','%s','%.2f','AWS')";
  char soil_rain_query[256];//holds the query that inserts the soiltemperature,soilmoisture,rainfall;
  char temp_humid_query[256];//will hold the query to insert data from 2m node
  char status_query[256]={};//holds the query to insert the node status info int nodestatus table
  char pressure_query[256];//holds the query to insert the pressure got from the ground node
  char wind_query[256];//holds a query to insert data about wind status from the 10M node
  int counter=0;
  //caters for Gen 3 data which sends RTC_T=date,time
  if(strstr(buffer,"RTC_T=")!=NULL){
    replace(buffer, "RTC_T=" ,"");
    replace(buffer, "," ," ");
  }
  int made_conn =0;
  if (connection ==NULL){
    connection = connect2db();
    made_conn =1;
  }
  //caters for Gen 3 data which starts with ID=XXXXXXXXXXXXXXXXX
  if(strstr(buffer,"ID=")!=NULL){
    char temp_buffer[RCVBUFSIZE];
    int len = strlen(buffer)-20;
    strncpy(temp_buffer,buffer+20,len);
    temp_buffer[len]='\0';
    strcpy(buffer,temp_buffer);
  }
    printf("The Crush is in the loop\n");
    //printf("START: %s : END\n",buffer);
  for(counter=0; counter<number_of_stations; counter++){
     if(stations[counter] != NULL){
         
         printf("BUFFER: %s +====%s aah %s\n",buffer,strstr(buffer,"fios-10m"),stations[counter]->config_10m->txt_10m_value);
        
     //check if the string is of type 2m from the current station
         if(strstr(buffer,stations[counter]->config_2m->txt_2m_value)!=NULL){

             process2mRecord(buffer,two_meter_report,stations[counter]->config_2m);

             //generating the query to insert query to insert the node status information
             sprintf(status_query,status_query_template,two_meter_report[V_MCU_2M_KEY],
             two_meter_report[V_IN_2M_KEY],two_meter_report[RSSI_2M_KEY],
             two_meter_report[LQI_2M_KEY],two_meter_report[DRP_2M_KEY],
             two_meter_report[DATE_2M_KEY],two_meter_report[TIME_2M_KEY],
             two_meter_report[TXT_2M_KEY],
             two_meter_report[E64_2M_KEY],two_meter_report[SEQ_2M_KEY],stations[counter]->id);
             //inserting the node status information

             if (mysql_query(connection,status_query)) {
             //  printf( "%s\n", mysql_error(connection));
             }
             //calculating the dew_point

             float dry_bulb = atof(two_meter_report[T_SHT2X_2M_KEY]);
             float humidity = atof(two_meter_report[RH_SHT2X_2M_KEY]);
             float dew_point = (humidity*dry_bulb)/100;
             float wet_bulb = ((2*dew_point)+dry_bulb)/3;
             
             //generating the query to insert humidity and temperature
             sprintf(temp_humid_query,temp_humid_template,two_meter_report[DATE_2M_KEY],stations[counter]->id,getZuluTime(two_meter_report[TIME_2M_KEY]),dry_bulb,wet_bulb);
             //storing temperature into the observationslip slip
             if (mysql_query(connection,temp_humid_query)) {
              // printf( "%s\n", mysql_error(connection));
             }
             resetDataHolder(two_meter_report,20);
             printf("EH \n %s",temp_humid_query);
             printf("\nThe string is two meter type\n");
             break;
         }
         else if(strstr(buffer,stations[counter]->config_10m->txt_10m_value)!=NULL){
             
              //printf("%s",buffer);
             process10mRecord(buffer, ten_meter_report, stations[counter]->config_10m);
             sprintf(status_query,status_query_template,ten_meter_report[V_MCU_10M_KEY],
              ten_meter_report[V_IN_10M_KEY],ten_meter_report[RSSI_10M_KEY],ten_meter_report[LQI_10M_KEY],
             ten_meter_report[DRP_10M_KEY],ten_meter_report[DATE_10M_KEY],ten_meter_report[TIME_10M_KEY],
              ten_meter_report[TXT_10M_KEY],ten_meter_report[E64_10M_KEY],ten_meter_report[SEQ_10M_KEY],stations[counter]->id);
             printf("REPORT: %s \n",status_query);
             if (mysql_query(connection,status_query)) {
                //printf( "%s\n", mysql_error(connection));
             }
              if(!(ten_meter_report[V_A1_10M_KEY] == NULL || ten_meter_report[V_A2_10M_KEY]== NULL)){
              float va1 =atof(ten_meter_report[V_A1_10M_KEY]);
              float va2 =atof(ten_meter_report[V_A2_10M_KEY]);

              float direction_in_degrees = (va1/va2 -0.05)*400;
             // printf("%f degrees\n", direction_in_degrees);
             sprintf(wind_query,wind_direction_template,ten_meter_report[DATE_10M_KEY],
              stations[counter]->id,getZuluTime(ten_meter_report[TIME_10M_KEY])
             ,direction_in_degrees);
             //printf("\n%s\n",wind_query);
             if (mysql_query(connection,wind_query)) {
                //printf( "%s\n", mysql_error(connection));
             }

             }else if(ten_meter_report[P0_LST60_10M_KEY] != NULL){
                  float p0_lst60_10m = atof(ten_meter_report[P0_LST60_10M_KEY]);
                  float speed = ((2.5*p0_lst60_10m)/3600);
                  sprintf(wind_query,wind_speed_template,ten_meter_report[DATE_10M_KEY],
                          stations[counter]->id,getZuluTime(ten_meter_report[TIME_10M_KEY])
                          ,speed);
                 // printf("\n%s\n",wind_query);
                  if (mysql_query(connection,wind_query)) {
                      //printf( "%s\n", mysql_error(connection));
                  }
              }
               else {
                printf("ten_meter_report[P0_LST60_10M_KEY] = %s",ten_meter_report[P0_LST60_10M_KEY]);
               }

               resetDataHolder(ten_meter_report,20);
             printf("\nThe string is 10m meter type\n");
               break;
         }
         else if(strstr(buffer,stations[counter]->config_gnd->txt_gnd_value)!=NULL){
              printf("%s",buffer);
             processGroundRecord(buffer, ground_node_report, stations[counter]->config_gnd);
             

             sprintf(status_query,status_query_template,
              ground_node_report[V_MCU_GND_KEY],
              ground_node_report[V_IN_GND_KEY]
              ,ground_node_report[RSSI_GND_KEY],
              ground_node_report[LQI_GND_KEY],
              ground_node_report[DRP_GND_KEY],ground_node_report[DATE_GND_KEY],
              ground_node_report[TIME_GND_KEY],ground_node_report[TXT_GND_KEY],
              ground_node_report[E64_GND_KEY],ground_node_report[SEQ_GND_KEY],stations[counter]->id);
             if (mysql_query(connection,status_query)) {
               // printf( "%s\n", mysql_error(connection));
             }

              printf("%s and %s SOIL",ground_node_report[T1_GND_KEY],ground_node_report[V_A1_GND_KEY]);
              sprintf(soil_rain_query,soil_rain_template,ground_node_report[DATE_GND_KEY],stations[counter]->id,
              getZuluTime(ground_node_report[TIME_GND_KEY]),ground_node_report[T1_GND_KEY],
              ground_node_report[V_A1_GND_KEY],ground_node_report[P0_LST60_GND_KEY]);
             printf("\n%s\n",soil_rain_query);
              if (mysql_query(connection,soil_rain_query)) {
                 // printf( "%s\n", mysql_error(connection));
               }

             resetDataHolder(ground_node_report,20);
             printf("\nThe string is ground node type\n");
             break;
         }
         else if(strstr(buffer,stations[counter]->config_sink->txt_sink_value)!=NULL){
            
             processSinkRecord(buffer, sink_node_report,stations[counter]->config_sink);
             sprintf(status_query,status_query_template,sink_node_report[V_MCU_SINK_KEY],
              sink_node_report[V_IN_SINK_KEY],sink_node_report[RSSI_SINK_KEY],
              sink_node_report[LQI_SINK_KEY],sink_node_report[DRP_SINK_KEY],
              sink_node_report[DATE_SINK_KEY],sink_node_report[TIME_SINK_KEY],
              sink_node_report[TXT_SINK_KEY],sink_node_report[E64_SINK_KEY],sink_node_report[SEQ_SINK_KEY],stations[counter]->id);
             if (mysql_query(connection,status_query)) {
               // printf( "%s\n", mysql_error(connection));
             }
             sprintf(pressure_query,pressure_template,sink_node_report[DATE_SINK_KEY],
              stations[counter]->id,getZuluTime(sink_node_report[TIME_SINK_KEY]),
              sink_node_report[P_MS5611_SINK_KEY]);
             // printf("\n%s\n",pressure_query);
             if (mysql_query(connection,pressure_query)) {
               // printf( "%s\n", mysql_error(connection));
             }
             resetDataHolder(sink_node_report,20);
            printf("\nThe string is Sink node type\n");
             break;
         }
         else{
              printf("10M KEY: %s\n", stations[counter]->config_10m->txt_10m_value);
         }
         
         printf("10M KEY: %s and %s\n", stations[counter]->config_10m->txt_10m_value);

     }
     else{
       //ignore null station record
     }
 }
    printf("\nNo crush inside this loop");
   if(made_conn==1){
     mysql_close(connection);//close the connection if it was made by this function
   }
}
