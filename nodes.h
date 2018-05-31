#define TEN_M_KEY "10m"
#define TWO_M_KEY "2m"
#define GROUND_KEY "gnd"
#define SINK_KEY "sink"

<<<<<<< HEAD
#define UT_2M_KEY 0
#define GW_LAT_2M_KEY 1
#define GW_LONG_2M_KEY 2
#define V_MCU_2M_KEY 3
#define V_IN_2M_KEY 4
#define T_SHT2X_2M_KEY 5
#define RH_SHT2X_2M_KEY 6
#define TTL_2M_KEY 7
#define RSSI_2M_KEY 8
#define LQI_2M_KEY 9
#define E64_2M_KEY 10
#define DRP_2M_KEY 11
#define TXT_2M_KEY 12
#define DATE_2M_KEY 13
#define TIME_2M_KEY 14
#define SEQ_2M_KEY 15

#define UT_GND_KEY 0
#define GW_LAT_GND_KEY 1
#define GW_LONG_GND_KEY 2
#define PS_GND_KEY 3
#define P0_GND_KEY 4
#define P0_LST60_GND_KEY 5
#define UP_GND_KEY 6
#define V_A1_GND_KEY 7
#define V_A2_GND_KEY 8
#define TTL_GND_KEY 9
#define RSSI_GND_KEY 10
#define LQI_GND_KEY 11
#define E64_GND_KEY 12
#define DRP_GND_KEY 13
#define TXT_GND_KEY 14
#define V_MCU_GND_KEY 15
#define V_IN_GND_KEY 16
#define DATE_GND_KEY 17
#define TIME_GND_KEY 18
#define T1_GND_KEY 19
#define SEQ_GND_KEY 20

#define UT_10M_KEY 0
#define GW_LAT_10M_KEY 1
#define GW_LONG_10M_KEY 2
#define PS_10M_KEY 3
#define T_10M_KEY 4
#define E64_10M_KEY 5
#define V_IN_10M_KEY 6
#define V_MCU_10M_KEY 7
#define V_A1_10M_KEY 8
#define V_A2_10M_KEY 9
#define V_A3_10M_KEY 10
#define TTL_10M_KEY 11
#define RSSI_10M_KEY 12
#define LQI_10M_KEY 13
#define DRP_10M_KEY 14
#define TXT_10M_KEY 15
#define DATE_10M_KEY 17
#define TIME_10M_KEY 16
#define P0_LST60_10M_KEY 18
#define SEQ_10M_KEY 19
#define V_AD1_10M_KEY 20
#define V_AD2_10M_KEY 21



#define UT_SINK_KEY 0
#define GW_LAT_SINK_KEY 1
#define GW_LONG_SINK_KEY 2
#define PS_SINK_KEY 3
#define T_SINK_KEY 4
#define E64_SINK_KEY 5
#define V_IN_SINK_KEY 6
#define V_MCU_SINK_KEY 7
#define UP_SINK_KEY 8
#define P_MS5611_SINK_KEY 9
#define TTL_SINK_KEY 10
#define RSSI_SINK_KEY 11
#define LQI_SINK_KEY 12
#define DRP_SINK_KEY 13
#define TXT_SINK_KEY 14
#define DATE_SINK_KEY 15
#define TIME_SINK_KEY 16
#define SEQ_SINK_KEY 17

struct TwoMeterConfig{
    char date_2m[5];
    char time_2m[10];
    char ut_2m[10];
    char gw_lat_2m[10];
    char gw_long_2m[10];
    char v_mcu_2m[10];
    char v_in_2m[10];
    char ttl_2m[10];
    char rssi_2m[10];
    char lqi_2m[10];
    char drp_2m[10];
    char e64_2m[10];
    char txt_2m[10];
    char seq_2m[10];
    char t_sht2x_2m[10];
    char rh_sht2x_2m[10];
    char txt_2m_value[30];
};
struct GroundConfig{
    char date_gnd[10];
    char time_gnd[10];
    char ut_gnd[10];
    char gw_lat_gnd[10];
    char gw_long_gnd[10];
    char ps_gnd[10];
    char p0_gnd[10];
    char v_mcu_gnd[10];
    char v_in_gnd[10];
    char p0_lst60_gnd[15];
    char up_gnd[10];
    char v_a1_gnd[10];
    char v_a2_gnd[10];
    char ttl_gnd[10];
    char rssi_gnd[10];
    char lqi_gnd[10];
    char drp_gnd[10];
    char e64_gnd[10];
    char txt_gnd[10];
    char t1_gnd[10];
    char seq_gnd[10];
    char txt_gnd_value[30];
};
struct TenMeterConfig{
    char date_10m[5];
    char time_10m[10];
    char ut_10m[10];
    char gw_lat_10m[10];
    char gw_long_10m[10];
    char e64_10m[10];
    char ps_10m[10];
    char t_10m[10];
    char v_mcu_10m[10];
    char v_in_10m[10];
    char v_a1_10m[10];
    char v_a2_10m[10];
    char v_a3_10m[10];
    char p0_lst60_10m[10];
    char ttl_10m[10];
    char rssi_10m[10];
    char lqi_10m[10];
    char drp_10m[10];
    char txt_10m[10];
    char seq_10m[10];
    char txt_10m_value[30];
    char v_ad1_10m[10];
    char v_ad2_10m[10];
};
struct SinkConfig{
  char date_sink[5];
  char time_sink[10];
  char ut_sink[10];
  char gw_lat_sink[10];
  char gw_long_sink[10];
  char e64_sink[10];
  char t_sink[10];
  char ps_sink[10];
  char up_sink[10];
  char v_mcu_sink[10];
  char v_in_sink[10];
  char p_ms5611_sink[15];
  char ttl_sink[10];
  char rssi_sink[10];
  char lqi_sink[10];
  char drp_sink[10];
  char txt_sink[10];
  char seq_sink[10];
  char txt_sink_value[30];
};
struct Station {
  char latitude[15];
  char longitude[15];
  char id[5];
  struct TwoMeterConfig *config_2m;
  struct SinkConfig *config_sink;
  struct TenMeterConfig *config_10m;
  struct GroundConfig *config_gnd;
};
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
   // printf("");
    strcat(zulutime,"Z");

    if(token != NULL){
        free(token);
    }
    //free(zulutime);
    return zulutime;
}



MYSQL *connect2db(){
   MYSQL *conn;
   MYSQL_RES *res;
   MYSQL_ROW row;

   char *server = SERVER;
   char *user = DATABASE_USERNAME;
   char *password = DATABASE_USER_PASSWORD;
   char *database = DATABASE_NAME;
   conn = mysql_init(NULL);
   /* Connect to database */
   if (!mysql_real_connect(conn, server,
         user, password, database, 0, NULL, 0)) {
     // printf( "%s\n", mysql_error(conn));
      return NULL;
   }
   else{
       return conn;
   }
}

void loadConfigurations(struct Station *stations[],MYSQL *connection, int number_of_stations){
    
  char * config_2m_query_template="SELECT node_id, station_id, date_2m, time_2m, ut_2m, gw_lat_2m, gw_long_2m,v_mcu_2m,v_in_2m, ttl_2m, rssi_2m, lqi_2m, drp_2m, e64_2m, txt_2m, t_sht2x_2m,rh_sh2x_2m, txt_2m_value,seq_2m FROM  twoMeterNode WHERE station_id =%s";
  char * config_10m_query_template="SELECT node_id, station_id, date_10m, time_10m, ut_10m, gw_lat_10m, gw_long_10m, e64_10m, ps_10m, v_mcu_10m, v_in_10m, v_a1_10m, v_a2_10m, v_a3_10m, ttl_10m, rssi_10m, lqi_10m, drp_10m, txt_10m,txt_10m_value,p0_lst60_10m,seq_10m,v_ad1_10m, v_ad2_10m FROM  tenMeterNode WHERE station_id =%s";
  char *config_gnd_query_template="SELECT node_id, station_id, date_gnd, time_gnd, ut_gnd, gw_lat_gnd, gw_long_gnd, ps_gnd, p0_gnd, v_mcu_gnd, v_in_gnd, p0_lst60_gnd, up_gnd, v_a1_gnd, v_a2_gnd, ttl_gnd, rssi_gnd, lqi_gnd, drp_gnd, e64_gnd, txt_gnd, txt_gnd_value, t1_gnd,seq_gnd FROM  groundNode WHERE station_id =%s";
  char *config_sink_query_template="SELECT node_id, station_id, date_sink, time_sink, ut_sink, gw_lat_sink, gw_long_sink, e64_sink, t_sink, ps_sink, up_sink, v_mcu_sink, v_in_sink, p_ms5611_sink, ttl_sink, rssi_sink, lqi_sink, drp_sink, txt_sink, txt_sink_value,seq_sink FROM  sinkNode WHERE station_id =%s";

  char config_2m_query[400];
  char config_10m_query[400];
  char config_gnd_query[400];
  char config_sink_query[400];
  MYSQL_RES  *node_res;
  MYSQL_ROW  node_row;
      int counter;
      counter=0;
      //extracting the station Number
      int station_has_config=0;//to be used to eliminate stations without configurations
        printf("PASSED HERE -1");
      for(counter=0; counter<number_of_stations; counter++){
        station_has_config =0;
        sprintf(config_2m_query,config_2m_query_template,stations[counter]->id);
        if(mysql_query(connection,config_2m_query)){
        }
        else{
            node_res = mysql_use_result(connection);

                while ((node_row = mysql_fetch_row(node_res)) != NULL ) {
                    station_has_config+=1;
                    struct TwoMeterConfig *y =(struct TwoMeterConfig *)malloc(sizeof(struct TwoMeterConfig)) ;
                    strcpy(y->date_2m,node_row[2]);
                    strcpy(y->time_2m,node_row[3]);
                    strcpy(y->ut_2m,node_row[4]);
                    strcpy(y->gw_lat_2m,node_row[5]);
                    strcpy(y->gw_long_2m,node_row[6]);
                    strcpy(y->v_mcu_2m,node_row[7]);
                    strcpy(y->v_in_2m,node_row[8]);
                    strcpy(y->ttl_2m,node_row[9]);
                    strcpy(y->rssi_2m,node_row[10]);
                    strcpy(y->lqi_2m,node_row[11]);
                    strcpy(y->drp_2m,node_row[12]);
                    strcpy(y->e64_2m,node_row[13]);
                    strcpy(y->txt_2m,node_row[14]);
                    strcpy(y->t_sht2x_2m,node_row[15]);
                    strcpy(y->rh_sht2x_2m,node_row[16]);
                    strcpy(y->txt_2m_value,node_row[17]);
                    strcpy(y->seq_2m,node_row[18]);
                    stations[counter]->config_2m =y;
                }
                //printf("%s has count as %d at 2m\n",stations[counter]->id,station_has_config);
        }
          
        //load configurations for 10m nodes
        sprintf(config_10m_query,config_10m_query_template,stations[counter]->id);
        if(mysql_query(connection,config_10m_query)){
          printf( "%s\n", mysql_error(connection));
        }
        else{
            node_res = mysql_use_result(connection);

                printf("%d/%d is %s \n",counter,number_of_stations,stations[counter]->id);
                while ((node_row = mysql_fetch_row(node_res)) != NULL ) {
                    station_has_config+=1;
                    struct TenMeterConfig *z =(struct TenMeterConfig *)malloc(sizeof(struct TenMeterConfig)) ;
                    strcpy(z->date_10m,node_row[2]);
                    strcpy(z->time_10m,node_row[3]);
                    strcpy(z->ut_10m,node_row[4]);
                    strcpy(z->gw_lat_10m,node_row[5]);
                    strcpy(z->gw_long_10m,node_row[6]);
                    strcpy(z->e64_10m,node_row[7]);
                    strcpy(z->ps_10m,node_row[8]);
                    strcpy(z->v_mcu_10m,node_row[9]);
                    strcpy(z->v_in_10m,node_row[10]);
                    strcpy(z->v_a1_10m,node_row[11]);
                    strcpy(z->v_a2_10m,node_row[12]);
                    strcpy(z->v_a3_10m,node_row[13]);
                    strcpy(z->ttl_10m,node_row[14]);
                    strcpy(z->rssi_10m,node_row[15]);
                    strcpy(z->lqi_10m,node_row[16]);
                    strcpy(z->drp_10m,node_row[17]);
                    strcpy(z->txt_10m,node_row[18]);
                    strcpy(z->txt_10m_value,node_row[19]);
                    strcpy(z->p0_lst60_10m,node_row[20]);
                    strcpy(z->seq_10m,node_row[21]);
                    strcpy(z->v_ad1_10m,node_row[22]);
                    strcpy(z->v_ad2_10m,node_row[23]);
                    stations[counter]->config_10m =z;
                }

                //printf("%s has count as %d at 10m\n",stations[counter]->id,station_has_config);

          }
           printf("\nPASSED HERE 4");
          //load configurations for the ground nodes

          sprintf(config_gnd_query,config_gnd_query_template,stations[counter]->id);
          //printf("%d/%d is %s AND  \n",counter,number_of_stations,stations[counter]->id);


          int res =mysql_query(connection,config_gnd_query);
          if(res){
            printf("ERROR %s\n", mysql_error(connection));
          }
          else{

              node_res = mysql_use_result(connection);
               //printf("%d/%d is  %s __Y \n",counter,number_of_stations,stations[counter]->id);
              while ((node_row = mysql_fetch_row(node_res)) != NULL ) {

                  struct GroundConfig *g =(struct GroundConfig *)malloc(sizeof(struct GroundConfig)) ;
                  strcpy(g->date_gnd,node_row[2]);
                  strcpy(g->time_gnd,node_row[3]);
                  strcpy(g->ut_gnd,node_row[4]);
                  strcpy(g->gw_lat_gnd,node_row[5]);
                  strcpy(g->gw_long_gnd,node_row[6]);
                  strcpy(g->ps_gnd,node_row[7]);
                  strcpy(g->p0_gnd,node_row[8]);
                  strcpy(g->v_mcu_gnd,node_row[9]);
                  strcpy(g->v_in_gnd,node_row[10]);
                  strcpy(g->p0_lst60_gnd ,node_row[11]);
                  strcpy(g->up_gnd,node_row[12]);
                  strcpy(g->v_a1_gnd,node_row[13]);
                  strcpy(g->v_a2_gnd,node_row[14]);
                  strcpy(g->ttl_gnd,node_row[15]);
                  strcpy(g->rssi_gnd,node_row[16]);
                  strcpy(g->lqi_gnd,node_row[17]);
                  strcpy(g->drp_gnd,node_row[18]);
                  strcpy(g->e64_gnd,node_row[19]);
                  strcpy(g->txt_gnd,node_row[20]);
                  strcpy(g->txt_gnd_value,node_row[21]);
                  strcpy(g->t1_gnd,node_row[22]);
                  strcpy(g->seq_gnd,node_row[23]);
                  stations[counter]->config_gnd =g;
                  station_has_config+=1;

              }

          }

          //printf("%s has count as %d at GND\n",stations[counter]->id,station_has_config);
          //load configurations for the sink nodes
          sprintf(config_sink_query,config_sink_query_template,stations[counter]->id);
          if(mysql_query(connection,config_sink_query)){
            printf( "%s\n", mysql_error(connection));
          }
          else{
              node_res = mysql_use_result(connection);

                   while ((node_row = mysql_fetch_row(node_res)) != NULL ) {
                       station_has_config+=1;
                       struct SinkConfig *s =(struct SinkConfig *)malloc(sizeof(struct SinkConfig)) ;
                       strcpy(s->date_sink,node_row[2]);
                       strcpy(s->time_sink,node_row[3]);
                       strcpy(s->ut_sink,node_row[4]);
                       strcpy(s->gw_lat_sink,node_row[5]);
                       strcpy(s->gw_long_sink,node_row[6]);
                       strcpy(s->e64_sink,node_row[7]);
                       strcpy(s->t_sink,node_row[8]);
                       strcpy(s->ps_sink,node_row[9]);
                       strcpy(s->up_sink,node_row[10]);
                       strcpy(s->v_mcu_sink,node_row[11]);
                       strcpy(s->v_in_sink,node_row[12]);
                       strcpy(s->p_ms5611_sink ,node_row[13]);
                       strcpy(s->ttl_sink,node_row[14]);
                       strcpy(s->rssi_sink,node_row[15]);
                       strcpy(s->lqi_sink,node_row[16]);
                       strcpy(s->drp_sink,node_row[17]);
                       strcpy(s->txt_sink,node_row[18]);
                       strcpy(s->txt_sink_value,node_row[19]);
                       strcpy(s->seq_sink,node_row[20]);
                       stations[counter]->config_sink =s;
                   }
                  //printf("%s has count as %d at SINK\n",stations[counter]->id,station_has_config);
          }
          
        // printf("ID is %s and Count is %d\n",stations[counter]->id,station_has_config);
          if (station_has_config<4) {
            printf("%d is not configured\n",counter);
            free(stations[counter]);
            stations[counter] =NULL;
            station_has_config=0;

          }
      }
      //the following logic removes any non complete(invalid stations)
      int valid_stations =0;
      struct Station *temp_stations[number_of_stations];
      for(counter=0; counter<number_of_stations; counter++){
        if (stations[counter] !=NULL ) {
          temp_stations[valid_stations++]=stations[counter];
        }
      }

      for(counter=0; counter<valid_stations; counter++){
        stations[counter]=temp_stations[counter];
      }
      number_of_stations = valid_stations;
    printf("LEFT HERE\n");
}
char *findKeyValue(char *substr,char *key){
    //the substring should be of the form key=value
    if(strstr(substr,key)!=NULL){
        const char equal_symbol[2]="=";
        char *token;
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
void process2mRecord(char *buffer, char *two_m_report[], struct TwoMeterConfig *config_2m){
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
        two_m_report[DATE_2M_KEY]=report;
    }else if(counter==1){
        two_m_report[TIME_2M_KEY] =report;
    }else if(strstr(reports[counter],"UT") !=NULL){
        //ignore this value UT. It returns true for a search of "T=" which may lead to missing the temperature
    }else if(strstr(reports[counter],"TTL") !=NULL){
        //ignore this value TTL. It returns true for a search of "T=" which may lead to missing the temperature
    }else if(strstr(reports[counter],"TZ") !=NULL){
        //ignore this value TZ. It returns true for a search of "T=" which may lead to missing the temperature
    }
    else
    {
        if(strstr(reports[counter],config_2m->t_sht2x_2m) !=NULL){
            two_m_report[T_SHT2X_2M_KEY] = findKeyValue(reports[counter],config_2m->t_sht2x_2m);
            printf("\n%s and  %s GIVES %s\n",reports[counter],config_2m->t_sht2x_2m,two_m_report[T_SHT2X_2M_KEY]);
        }else  if(strstr(reports[counter],config_2m->gw_lat_2m) !=NULL){
            two_m_report[GW_LAT_2M_KEY] = findKeyValue(reports[counter],config_2m->gw_lat_2m);
        }else if(strstr(reports[counter],config_2m->gw_long_2m) !=NULL){
            two_m_report[GW_LONG_2M_KEY] = findKeyValue(reports[counter],config_2m->gw_long_2m);
        }else if(strstr(reports[counter],config_2m->v_mcu_2m) !=NULL){
          two_m_report[V_MCU_2M_KEY] = findKeyValue(reports[counter],config_2m->v_mcu_2m);
        }else if(strstr(reports[counter],config_2m->txt_2m) !=NULL){
          two_m_report[TXT_2M_KEY] = findKeyValue(reports[counter],config_2m->txt_2m);
        }else if(strstr(reports[counter],config_2m->v_in_2m) !=NULL){
            two_m_report[V_IN_2M_KEY] = findKeyValue(reports[counter],config_2m->v_in_2m);
        }else if(strstr(reports[counter],config_2m->rh_sht2x_2m) !=NULL){
            two_m_report[RH_SHT2X_2M_KEY] = findKeyValue(reports[counter],config_2m->rh_sht2x_2m);
        }else if(strstr(reports[counter],config_2m->ttl_2m) !=NULL){
            two_m_report[TTL_2M_KEY] = findKeyValue(reports[counter],config_2m->ttl_2m);
        }else if(strstr(reports[counter],config_2m->rssi_2m) !=NULL){
            two_m_report[RSSI_2M_KEY]=findKeyValue(reports[counter],config_2m->rssi_2m);
        }else if(strstr(reports[counter],config_2m->lqi_2m) !=NULL){
            two_m_report[LQI_2M_KEY] = findKeyValue(reports[counter],config_2m->lqi_2m);
        }
        else if(strstr(reports[counter],config_2m->drp_2m) !=NULL){
            two_m_report[DRP_2M_KEY] = findKeyValue(reports[counter],config_2m->drp_2m);
        }
        else if(strstr(reports[counter],config_2m->seq_2m) !=NULL){
            two_m_report[SEQ_2M_KEY] = findKeyValue(reports[counter],config_2m->seq_2m);
        }
        }
  //                              	printf("%d =%d \n",max,counter);
     counter++;
    //printf("%d =%d \n",max,counter);
    }
  // printf("%d here",counter);

}

void processSinkRecord(char *buffer, char *sink_report[], struct SinkConfig *config_sink){
  char space[2]=" ";
  char *report;
  char *reports[25];
  char *record;
  int max;
  int counter=0;
  report = strtok(buffer,space);
  counter=0;
  //break the buffer(report) into key=value pairs
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
        sink_report[DATE_SINK_KEY]=report;
    }else if(counter==1){
        sink_report[TIME_SINK_KEY] =report;
    }else
    {
        if(strstr(reports[counter],config_sink->gw_lat_sink) !=NULL){
            sink_report[GW_LAT_SINK_KEY] = findKeyValue(reports[counter],config_sink->gw_lat_sink);
        }else if(strstr(reports[counter],config_sink->gw_long_sink) !=NULL){
            sink_report[GW_LONG_SINK_KEY] = findKeyValue(reports[counter],config_sink->gw_long_sink);
        }else if(strstr(reports[counter],config_sink->v_mcu_sink) !=NULL){
          sink_report[V_MCU_SINK_KEY] = findKeyValue(reports[counter],config_sink->v_mcu_sink);
        }else if(strstr(reports[counter],config_sink->txt_sink) !=NULL){
          sink_report[TXT_SINK_KEY] = findKeyValue(reports[counter],config_sink->txt_sink);
        }else if(strstr(reports[counter],config_sink->v_in_sink) !=NULL){
            sink_report[V_IN_SINK_KEY] = findKeyValue(reports[counter],config_sink->v_in_sink);
        }else if(strstr(reports[counter],config_sink->p_ms5611_sink) !=NULL){
            sink_report[P_MS5611_SINK_KEY] = findKeyValue(reports[counter],config_sink->p_ms5611_sink);
        }else if(strstr(reports[counter],config_sink->up_sink) !=NULL){
            sink_report[UP_SINK_KEY] = findKeyValue(reports[counter],config_sink->up_sink);
        }else if(strstr(reports[counter],config_sink->ps_sink) !=NULL){
            sink_report[PS_SINK_KEY] = findKeyValue(reports[counter],config_sink->ps_sink);
        }else if(strstr(reports[counter],config_sink->t_sink) !=NULL){
            sink_report[T_SINK_KEY] = findKeyValue(reports[counter],config_sink->t_sink);
        }else if(strstr(reports[counter],config_sink->e64_sink) !=NULL){
            sink_report[E64_SINK_KEY] = findKeyValue(reports[counter],config_sink->e64_sink);
        }else if(strstr(reports[counter],config_sink->ttl_sink) !=NULL){
            sink_report[TTL_SINK_KEY] = findKeyValue(reports[counter],config_sink->ttl_sink);
        }else if(strstr(reports[counter],config_sink->rssi_sink) !=NULL){
            sink_report[RSSI_SINK_KEY]=findKeyValue(reports[counter],config_sink->rssi_sink);
        }else if(strstr(reports[counter],config_sink->lqi_sink) !=NULL){
            sink_report[LQI_SINK_KEY] = findKeyValue(reports[counter],config_sink->lqi_sink);
        }else if(strstr(reports[counter],config_sink->drp_sink) !=NULL){
            sink_report[DRP_SINK_KEY] = findKeyValue(reports[counter],config_sink->drp_sink);
        }
        else if(strstr(reports[counter],config_sink->seq_sink) !=NULL){
            sink_report[SEQ_SINK_KEY] = findKeyValue(reports[counter],config_sink->seq_sink);
        }
    }
     counter++;

    }

}

void processGroundRecord(char *buffer, char *ground_report[], struct GroundConfig *config_ground){
  char space[2]=" ";
  char *report;
  char *reports[25];
  char *record;
  int max;
  int counter=0;
  report = strtok(buffer,space);
  counter=0;
  //break the buffer(report) into key=value pairs
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
        ground_report[DATE_GND_KEY]=report;
    }else if(counter==1){
        ground_report[TIME_GND_KEY] =report;
    }else
    {
        if(strstr(reports[counter],config_ground->gw_lat_gnd) !=NULL){
            ground_report[GW_LAT_GND_KEY] = findKeyValue(reports[counter],config_ground->gw_lat_gnd);
        }else if(strstr(reports[counter],config_ground->v_a1_gnd) !=NULL){
            ground_report[V_A1_GND_KEY] = findKeyValue(reports[counter],config_ground->v_a1_gnd);
        }else if(strstr(reports[counter],config_ground->v_a2_gnd) !=NULL){
            ground_report[V_A2_GND_KEY] = findKeyValue(reports[counter],config_ground->v_a2_gnd);
        }else if(strstr(reports[counter],config_ground->gw_long_gnd) !=NULL){
            ground_report[GW_LONG_GND_KEY] = findKeyValue(reports[counter],config_ground->gw_long_gnd);
        }else if(strstr(reports[counter],config_ground->v_mcu_gnd) !=NULL){
          ground_report[V_MCU_GND_KEY] = findKeyValue(reports[counter],config_ground->v_mcu_gnd);
        }else if(strstr(reports[counter],config_ground->txt_gnd) !=NULL){
          ground_report[TXT_GND_KEY] = findKeyValue(reports[counter],config_ground->txt_gnd);
        }else if(strstr(reports[counter],config_ground->v_in_gnd) !=NULL){
            ground_report[V_IN_GND_KEY] = findKeyValue(reports[counter],config_ground->v_in_gnd);
        }else if(strstr(reports[counter],config_ground->p0_lst60_gnd) !=NULL){
            ground_report[P0_LST60_GND_KEY] = findKeyValue(reports[counter],config_ground->p0_lst60_gnd);
        }else if(strstr(reports[counter],config_ground->up_gnd) !=NULL){
            ground_report[UP_GND_KEY] = findKeyValue(reports[counter],config_ground->up_gnd);
        }else if(strstr(reports[counter],config_ground->p0_gnd) !=NULL){
            ground_report[P0_GND_KEY] = findKeyValue(reports[counter],config_ground->p0_gnd);
        }else if(strstr(reports[counter],config_ground->ps_gnd) !=NULL){
            ground_report[PS_GND_KEY] = findKeyValue(reports[counter],config_ground->ps_gnd);
        }else if(strstr(reports[counter],config_ground->e64_gnd) !=NULL){
            ground_report[E64_GND_KEY] = findKeyValue(reports[counter],config_ground->e64_gnd);
        }else if(strstr(reports[counter],config_ground->ttl_gnd) !=NULL){
            ground_report[TTL_GND_KEY] = findKeyValue(reports[counter],config_ground->ttl_gnd);
        }else if(strstr(reports[counter],config_ground->rssi_gnd) !=NULL){
            ground_report[RSSI_GND_KEY]=findKeyValue(reports[counter],config_ground->rssi_gnd);
        }else if(strstr(reports[counter],config_ground->lqi_gnd) !=NULL){
            ground_report[LQI_GND_KEY] = findKeyValue(reports[counter],config_ground->lqi_gnd);
        }else if(strstr(reports[counter],config_ground->drp_gnd) !=NULL){
            ground_report[DRP_GND_KEY] = findKeyValue(reports[counter],config_ground->drp_gnd);
        }
        else if(strstr(reports[counter],config_ground->t1_gnd) !=NULL){
            ground_report[T1_GND_KEY] = findKeyValue(reports[counter],config_ground->t1_gnd);
        }
        else if(strstr(reports[counter],config_ground->seq_gnd) !=NULL){
            ground_report[SEQ_GND_KEY] = findKeyValue(reports[counter],config_ground->seq_gnd);
        }
    }
     counter++;

    }

}

void process10mRecord(char *buffer, char *ten_m_report[], struct TenMeterConfig *config_10m){
  char space[2]=" ";
  char *report;
  char *reports[25];
  char *record;
  int max;
  int counter=0;
  report = strtok(buffer,space);
  counter=0;
  //break the buffer(report) into key=value pairs
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
        ten_m_report[DATE_10M_KEY]=report;
    }else if(counter==1){
        ten_m_report[TIME_10M_KEY] =report;
    }else
    {
        //printf("Value: %s ",reports[counter]);
        if(strstr(reports[counter],config_10m->gw_lat_10m) !=NULL){
            ten_m_report[GW_LAT_10M_KEY] = findKeyValue(reports[counter],config_10m->gw_lat_10m);
        }else if(strstr(reports[counter],config_10m->v_a1_10m) !=NULL){
            ten_m_report[V_A1_10M_KEY] = findKeyValue(reports[counter],config_10m->v_a1_10m);
        }else if(strstr(reports[counter],config_10m->v_a2_10m) !=NULL){
            ten_m_report[V_A2_10M_KEY] = findKeyValue(reports[counter],config_10m->v_a2_10m);
        }else if(strstr(reports[counter],config_10m->v_a3_10m) !=NULL){
            ten_m_report[V_A3_10M_KEY] = findKeyValue(reports[counter],config_10m->v_a3_10m);
        }else if(strstr(reports[counter],config_10m->v_ad1_10m) !=NULL){
            ten_m_report[V_AD1_10M_KEY] = findKeyValue(reports[counter],config_10m->v_ad1_10m);
        }else if(strstr(reports[counter],config_10m->v_ad2_10m) !=NULL){
            ten_m_report[V_AD2_10M_KEY] = findKeyValue(reports[counter],config_10m->v_ad2_10m);
        }else if(strstr(reports[counter],config_10m->v_a3_10m) !=NULL){
            ten_m_report[V_A3_10M_KEY] = findKeyValue(reports[counter],config_10m->v_a3_10m);
        }else if(strstr(reports[counter],config_10m->gw_long_10m) !=NULL){
            ten_m_report[GW_LONG_10M_KEY] = findKeyValue(reports[counter],config_10m->gw_long_10m);
        }else if(strstr(reports[counter],config_10m->v_mcu_10m) !=NULL){
          ten_m_report[V_MCU_10M_KEY] = findKeyValue(reports[counter],config_10m->v_mcu_10m);
        }else if(strstr(reports[counter],config_10m->txt_10m) !=NULL){
          ten_m_report[TXT_10M_KEY] = findKeyValue(reports[counter],config_10m->txt_10m);
        }else if(strstr(reports[counter],config_10m->v_in_10m) !=NULL){
            ten_m_report[V_IN_10M_KEY] = findKeyValue(reports[counter],config_10m->v_in_10m);
        }else if(strstr(reports[counter],config_10m->ps_10m) !=NULL){
            ten_m_report[PS_10M_KEY] = findKeyValue(reports[counter],config_10m->ps_10m);
        }else if(strstr(reports[counter],config_10m->p0_lst60_10m) !=NULL){
            ten_m_report[P0_LST60_10M_KEY] = findKeyValue(reports[counter],config_10m->p0_lst60_10m);
        }else if(strstr(reports[counter],config_10m->e64_10m) !=NULL){
            ten_m_report[E64_10M_KEY] = findKeyValue(reports[counter],config_10m->e64_10m);
        }else if(strstr(reports[counter],config_10m->ttl_10m) !=NULL){
            ten_m_report[TTL_10M_KEY] = findKeyValue(reports[counter],config_10m->ttl_10m);
        }else if(strstr(reports[counter],config_10m->rssi_10m) !=NULL){
            ten_m_report[RSSI_10M_KEY]=findKeyValue(reports[counter],config_10m->rssi_10m);
        }else if(strstr(reports[counter],config_10m->lqi_10m) !=NULL){
            ten_m_report[LQI_10M_KEY] = findKeyValue(reports[counter],config_10m->lqi_10m);
        }else if(strstr(reports[counter],config_10m->drp_10m) !=NULL){
            ten_m_report[DRP_10M_KEY] = findKeyValue(reports[counter],config_10m->drp_10m);
        }else if(strstr(reports[counter],config_10m->seq_10m) !=NULL){
            ten_m_report[SEQ_10M_KEY] = findKeyValue(reports[counter],config_10m->seq_10m);
           
            
        }
        //printf("Yield %s and %s \n",reports[counter],ten_m_report[SEQ_10M_KEY]);
       // printf("SEQ: %s and \n",config_10m->seq_10m);

        //printf("P0_LST60 is %s from %s\n", config_10m->p0_lst60_10m,reports[counter]);
    }
     counter++;

    }

}
=======
/*#define TEN_M_KEY "TXT=makg2-10m"
#define TWO_M_KEY "TXT=makg2-2m"
#define GROUND_KEY "TXT=makg2-gnd"
#define SINK_KEY "TXT=makg2-sink"*/

#define UT_2M_KEY "UT"
#define GW_LAT_2M_KEY "GW_LAT"
#define GW_LONG_2M_KEY "GW_LON"
#define V_MCU_2M_KEY "V_MCU"
#define V_IN_2M_KEY "V_IN"
#define T_SHT2X_2M_KEY "T_SHT2X"
#define RH_SHT2X_2M_KEY "RH_SHT2X"
#define TTL_2M_KEY "TTL"
#define RSSI_2M_KEY "RSSI"
#define LQI_2M_KEY "LQI"
#define E64_2M_KEY "E64"
#define DRP_2M_KEY "DRP"
#define TXT_2M_KEY "TXT"

#define UT_GND_KEY "UT"
#define GW_LAT_GND_KEY "GW_LAT"
#define GW_LONG_GND_KEY "GW_LON"
#define PS_GND_KEY "PS"
#define P0_GND_KEY "P0"
#define P0_LST60_GND_KEY "P0_LST60"
#define UP_GND_KEY "UP"
#define V_A1_GND_KEY "V_A1"
#define V_A2_GND_KEY "V_A2"
#define TTL_GND_KEY "TTL"
#define RSSI_GND_KEY "RSSI"
#define LQI_GND_KEY "LQI"
#define E64_GND_KEY "E64"
#define DRP_GND_KEY "DRP"
#define TXT_GND_KEY "TXT"
#define V_MCU_GND_KEY "V_MCU"
#define V_IN_GND_KEY "V_IN"

#define UT_10M_KEY "UT"
#define GW_LAT_10M_KEY "GW_LAT"
#define GW_LONG_10M_KEY "GW_LON"
#define PS_10M_KEY "PS"
#define T_10M_KEY "T"
#define E64_10M_KEY "E64"
#define V_IN_10M_KEY "V_IN"
#define V_MCU_10M_KEY "V_MCU"
#define V_A1_10M_KEY "V_A1"
#define V_A2_10M_KEY "V_A2"
#define  V_A3_10M_KEY "V_A3"
#define TTL_10M_KEY "TTL"
#define RSSI_10M_KEY "RSSI"
#define LQI_10M_KEY "LQI"
#define DRP_10M_KEY "DRP"
#define TXT_10M_KEY "TXT"

#define UT_SINK_KEY "UT"
#define GW_LAT_SINK_KEY "GW_LAT"
#define GW_LONG_SINK_KEY "GW_LON"
#define PS_SINK_KEY "PS"
#define T_SINK_KEY "T"
#define E64_SINK_KEY "E64"
#define V_IN_SINK_KEY "V_IN"
#define V_MCU_SINK_KEY "V_MCU"
#define UP_SINK_KEY "UP"
#define P_MS5611_SINK_KEY "P_MS5611"
#define TTL_SINK_KEY "TTL"
#define RSSI_SINK_KEY "RSSI"
#define LQI_SINK_KEY "LQI"
#define DRP_SINK_KEY "DRP"
#define TXT_SINK_KEY "TXT"

struct two_meter_record{
    char *date_2m;
    char *time_2m; 
    char *ut_2m;
    char *gw_lat_2m; 
    char *gw_long_2m;
    char * v_mcu_2m;
    char * v_in_2m;
    char * ttl_2m;
    char * rssi_2m;
    char * lqi_2m;
    char * drp_2m;
    char * e64_2m;
    char * txt_2m;
    char *t_sht2x_2m;
    char *rh_sht2x_2m;
};

struct ground_node_record{
    char *date_gnd;
    char *time_gnd; 
    char *ut_gnd;
    char *gw_lat_gnd; 
    char *gw_long_gnd;
    char * ps_gnd;
    char * p0_gnd;
    char * v_mcu_gnd;
    char * v_in_gnd;
    char * p0_lst60_gnd;
    char * up_gnd;
    char * v_a1_gnd;
    char * v_a2_gnd;
    char * ttl_gnd;
    char * rssi_gnd;
    char * lqi_gnd;
    char * drp_gnd;
    char * e64_gnd;
    char * txt_gnd;
};
struct ten_meter_record{
    char *date_10m;
    char *time_10m; 
    char *ut_10m;
    char *gw_lat_10m; 
    char *gw_long_10m;
    char * e64_10m;
    char * ps_10m;
    char * t_10m;
    char * v_mcu_10m;
    char * v_in_10m;
    char * v_a1_10m;
    char * v_a2_10m;
    char * v_a3_10m;
    char * ttl_10m;
    char * rssi_10m;
    char * lqi_10m;
    char * drp_10m;
    char * txt_10m;
};
struct sink_node_record{
    char *date_sink;
    char *time_sink; 
    char *ut_sink;
    char *gw_lat_sink; 
    char *gw_long_sink;
    char * e64_sink;
    char * t_sink;
    char * ps_sink;
    char * up_sink;
    char * v_mcu_sink;
    char * v_in_sink;
    char * p_ms5611_sink;
    char * ttl_sink;
    char * rssi_sink;
    char * lqi_sink;
    char * drp_sink;
    char * txt_sink;
    
};
>>>>>>> 962d80f129cf9e9953929417296ee7faa5376833
