#define TEN_M_KEY "10m"
#define TWO_M_KEY "2m"
#define GROUND_KEY "gnd"
#define SINK_KEY "sink"

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
