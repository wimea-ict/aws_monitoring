<?php
        /**
         * This program retrieves the data from the last 6 minutes in the nodestatus
         * If a node has no record in the last six minutes, it's reported as failed.
         * It checks the V_IN, V_MCU values to see if junk data was not stored
         * It also checks 
         */
        $GLOBALS["MIN_V_IN_VALUE"] =2.80;
        $GLOBALS["MIN_DRY_BULB_VALUE"]=20.00;
        $GLOBALS["MIN_WET_BULB_VALUE"]=16.00;
        $GLOBALS["MAX_DRY_BULB_VALUE"]=39.00;
        $GLOBALS["MAX_WET_BULB_VALUE"]=25.00;
        $GLOBALS["MIN_RAINFALL_VALUE"]=0.0;
        $GLOBALS["MAX_RAINFALL_VALUE"]=20.0;
        $GLOBALS["MIN_SOILMOISTURE_VALUE"] =23.0;
        $GLOBALS["MAX_SOILMOISTURE_VALUE"] =30.0;
        $GLOBALS["MIN_SOILTEMPERATURE_VALUE"] =30.0;
        $GLOBALS["MAX_SOILTEMPERATURE_VALUE"] =40.0;
        $GLOBALS["MIN_PRESSURE_VALUE"] =10.0;
        $GLOBALS["MAX_PRESSURE_VALUE"] =900.0;
        $GLOBALS["MAX_WIND_SPEED_VALUE"]=10.0;
        $GLOBALS["MIN_WIND_SPEED_VALUE"]=0.0;
        $GLOBALS["MAX_INSOLATION_VALUE"]=10.0;
        $GLOBALS["MIN_INSOLATION_VALUE"]=10.0;
        $GLOBALS["MAX_WIND_SPEED_VALUE"]=120.0;
        $GLOBALS["MIN_WIND_SPEED_VALUE"]=0.0;
        //this will contain the station number of the station being monitored
        $STATION_NUMBER="536738"; //Station Number for the Makerere Automatic Weather station
        
        
        $time_range =6*60;//six minutes ago
        //txt identifiers for the node
        $GLOBALS["TEN_M_KEY"]="makg2-10m";
        $GLOBALS["TWO_M_KEY"] ="makg2-2m";
        $GLOBALS["GROUND_NODE_KEY"] ="makg2-gnd";
        $GLOBALS["SINK_NODE_KEY"]="makg2-sink";
        
        date_default_timezone_set("UTC"); //all the times here are in UTC
        
	$con = new mysqli("localhost", "username", "password", "mobilewimeadb") or die("failed to connect");
        $date_today = gmdate("Y-m-d",time());//the current date in UTC
        $time_6_mins_ago =gmdate("H:i:s",time()-$time_range);//the time in UTC
	$sql ="SELECT * FROM nodestatus WHERE nodestatus.date like '$date_today' AND nodestatus.time >='$time_6_mins_ago' AND StationNumber='$STATION_NUMBER' ORDER BY nodestatus.time DESC";
      //  echo "$sql"."<br />";
	$result = $con->query($sql);
        $ten_meter_on =false;
        $two_meter_on =false;
        $ground_node_on =false;
        $sink_node_on =false;
        $float_number_pattern ="/[0-9]\.[0-9]+/";//matches float values of the format 0.00 to 9.99
        $node_availability =array($GLOBALS["SINK_NODE_KEY"]=>false,$GLOBALS["GROUND_NODE_KEY"]=>false,$GLOBALS["TWO_M_KEY"]=>false,$GLOBALS["TEN_M_KEY"]=>false);
        $v_in_value =array($GLOBALS["SINK_NODE_KEY"]=>NULL,$GLOBALS["GROUND_NODE_KEY"]=>NULL,$GLOBALS["TWO_M_KEY"]=>NULL,$GLOBALS["TEN_M_KEY"]=>NULL);
        $v_mcu_value =array($GLOBALS["SINK_NODE_KEY"]=>NULL,$GLOBALS["GROUND_NODE_KEY"]=>NULL,$GLOBALS["TWO_M_KEY"]=>NULL,$GLOBALS["TEN_M_KEY"]=>NULL);
        $e64_value=array($GLOBALS["SINK_NODE_KEY"]=>NULL,$GLOBALS["GROUND_NODE_KEY"]=>NULL,$GLOBALS["TWO_M_KEY"]=>NULL,$GLOBALS["TEN_M_KEY"]=>NULL);
        //$GLOBALS["error_reports"] array will store the error reports for each node
        
        $GLOBALS["error_reports"] = array($GLOBALS["SINK_NODE_KEY"]=> array(),$GLOBALS["GROUND_NODE_KEY"]=> array(),$GLOBALS["TWO_M_KEY"]=> array(),$GLOBALS["TEN_M_KEY"]=> array());
	while($row = $result->fetch_assoc()){
		if($row["TXT"]==$GLOBALS["TEN_M_KEY"]){
                    $node_availability[$GLOBALS["TEN_M_KEY"]]=true;
                   
                    //extract the most recent V_IN, V_MCU, and E64 values
                    if($v_in_value[$GLOBALS["TEN_M_KEY"]]==NULL){
                      $v_in_value[$GLOBALS["TEN_M_KEY"]]=$row["V_IN"];
                    } 
                    
                    if($e64_value[$GLOBALS["TEN_M_KEY"]]==NULL){
                      $e64_value[$GLOBALS["TEN_M_KEY"]]=$row["E64"];
                    }
                    
                    if($v_in_value[$GLOBALS["TEN_M_KEY"]]==NULL){
                      $v_in_value[$GLOBALS["TEN_M_KEY"]]=$row["V_IN"];
                    }
                    
                    if($v_mcu_value[$GLOBALS["TEN_M_KEY"]]==NULL){
                      $v_mcu_value[$GLOBALS["TEN_M_KEY"]]=$row["V_MCU"];
                    }
                }
                else if($row["TXT"]==$GLOBALS["TWO_M_KEY"]){
                    $node_availability[$GLOBALS["TWO_M_KEY"]]=true;
                    if($v_in_value[$GLOBALS["TWO_M_KEY"]]==NULL){
                      $v_in_value[$GLOBALS["TWO_M_KEY"]]=$row["V_IN"];
                    }
                    if($e64_value[$GLOBALS["TEN_M_KEY"]]==NULL){
                      $e64_value[$GLOBALS["TEN_M_KEY"]]=$row["E64"];
                    }
                    
                     if($v_mcu_value[$GLOBALS["TWO_M_KEY"]]==NULL){
                      $v_mcu_value[$GLOBALS["TWO_M_KEY"]]=$row["V_MCU"];
                    }
                }
                else if($row["TXT"]==$GLOBALS["GROUND_NODE_KEY"]){
                    $node_availability[$GLOBALS["GROUND_NODE_KEY"]]=true;
                    if($v_in_value[$GLOBALS["GROUND_NODE_KEY"]]==NULL){
                      $v_in_value[$GLOBALS["GROUND_NODE_KEY"]]=$row["V_IN"];
                    }
                    if($e64_value[$GLOBALS["GROUND_NODE_KEY"]]==NULL){
                      $e64_value[$GLOBALS["GROUND_NODE_KEY"]]=$row["E64"];
                    }
                    if($v_mcu_value[$GLOBALS["GROUND_NODE_KEY"]]==NULL){
                      $v_mcu_value[$GLOBALS["GROUND_NODE_KEY"]]=$row["V_MCU"];
                    }
                }
                else if($row["TXT"]==$GLOBALS["SINK_NODE_KEY"]){
                    $node_availability[$GLOBALS["SINK_NODE_KEY"]]=true;
                    //record V_IN value
                    if($v_in_value[$GLOBALS["SINK_NODE_KEY"]]==NULL){
                      $v_in_value[$GLOBALS["SINK_NODE_KEY"]]=$row["V_IN"];
                    }
                    //record E64 value
                    if($e64_value[$GLOBALS["SINK_NODE_KEY"]]==NULL){
                      $e64_value[$GLOBALS["SINK_NODE_KEY"]]=$row["E64"];
                    }
                    
                    if($v_mcu_value[$GLOBALS["SINK_NODE_KEY"]]==NULL){
                      $v_mcu_value[$GLOBALS["SINK_NODE_KEY"]]=$row["V_MCU"];
                    }
                }      
	}
       //checking the status of the nodes
        checkNodeAvailability($node_availability);
        checkVINvalues($v_in_value,$node_availability);
        checkE64Values($e64_value,$node_availability);
        checkMCUValues($v_mcu_value,$node_availability);
       
        
        
        //checkking the data from the nodes 
        /**
         * These functions to check data from the nodes use the following Global variables declared up
            * $GLOBALS["error_reports"]
            * $date_today
            * $con
            * $float_number_pattern
         * 
         */
        
        checkTemperatureValues($con,$date_today);
        checkSoilTemperatureValues($con,$date_today);
        checkSoilMoistureValues($con,$date_today);
        checkPressureValues($con,$date_today);
        checkwindDirection($con,$date_today);
        checkWindSpeed($con,$date_today);
        checkRainfallValues($con,$date_today);
        echo "Sink_Node: ";
        print_r($GLOBALS["error_reports"][$GLOBALS["SINK_NODE_KEY"]]);
        echo "<br /> 10m: ";
        print_r($GLOBALS["error_reports"][$GLOBALS["TEN_M_KEY"]]);
        echo "<br /> 2m: ";
        print_r($GLOBALS["error_reports"][$GLOBALS["TWO_M_KEY"]]);
        echo "<br /> gnd: ";
        print_r($GLOBALS["error_reports"][$GLOBALS["GROUND_NODE_KEY"]]);
        echo "<br />";
        function sendMessage($message){
            //echo $message;
            mail("robein@ymail.com","Attention: makg2 aws", $message);
        }
        
        function checkWindSpeed($con,$date_today){
              $sql_to_get_wind_speed ="SELECT Wind_Speed, TIME FROM observationslip WHERE observationslip.Date LIKE".
                " '$date_today' AND SubmittedBy LIKE 'AWS' AND Wind_Speed IS NOT NULL ORDER BY id DESC LIMIT 1";
        $wind_speed_results=$con->query($sql_to_get_wind_speed);
        //echo $sql_to_get_pressure;
        if($wind_speed_results->num_rows==0){
            $GLOBALS["error_reports"][$GLOBALS["TEN_M_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["TEN_M_KEY"]])]="The Wind_Speed value was not recorded on ".$date_today;
        }
         while ($row=$wind_speed_results->fetch_assoc()){
            if(is_numeric($row["Wind_Speed"])){
                //check whether it's within range
                if($row["Wind_Speed"]<$GLOBALS["MIN_WIND_SPEED_VALUE"]){
                    $GLOBALS["error_reports"][$GLOBALS["TEN_M_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["TEN_M_KEY"]])]="The Pressure Wind_Speed value =".$row["Wind_Speed"]."  recorded on ".$date_today."at ".$row["TIME"]." is too low";
                }
                else if($row["Wind_Speed"]>$GLOBALS["MAX_WIND_SPEED_VALUE"]){
                    $GLOBALS["error_reports"][$GLOBALS["TEN_M_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["TEN_M_KEY"]])]="The Pressure Wind_Speed value =".$row["Wind_Speed"]."  recorded on ".$date_today."at ".$row["TIME"]." is too High";
                }
            }else if($row["Wind_Speed"]==""){
                $GLOBALS["error_reports"][$GLOBALS["TEN_M_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["TEN_M_KEY"]])]="The Wind_Speed value was not captured on ".$date_today."at ".$row["TIME"];
            }
            else {
                $GLOBALS["error_reports"][$GLOBALS["TEN_M_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["TEN_M_KEY"]])]="Wrong(Junk) Wind_Speed value =".$row["Wind_Speed"]."  was recorded on ".$date_today."at ".$row["TIME"];
            }
         }
         
        }
        function checkwindDirection($con,$date_today){
            $sql_to_get_wind_direction ="SELECT Wind_Direction, TIME FROM observationslip WHERE observationslip.Date LIKE".
                " '$date_today' AND SubmittedBy LIKE 'AWS' AND Wind_Direction IS NOT NULL ORDER BY id DESC LIMIT 1";
        $wind_direction_results=$con->query($sql_to_get_wind_direction);
        //echo $sql_to_get_pressure;
        if($wind_direction_results->num_rows==0){
            $GLOBALS["error_reports"][$GLOBALS["TEN_M_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["TEN_M_KEY"]])]="The Wind_Direction value was not recorded on ".$date_today;
        }
         while ($row=$wind_direction_results->fetch_assoc()){
            if(is_numeric($row["Wind_Direction"])){
                //check whether it's within range
                if($row["Wind_Direction"]<$GLOBALS["MIN_WIND_SPEED_VALUE"]){
                    $GLOBALS["error_reports"][$GLOBALS["TEN_M_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["TEN_M_KEY"]])]="The Wind_Direction value =".$row["Wind_Direction"]."  recorded on ".$date_today."at ".$row["TIME"]." is too low";
                }
                else if($row["Wind_Direction"]>$GLOBALS["MAX_WIND_SPEED_VALUE"]){
                    $GLOBALS["error_reports"][$GLOBALS["TEN_M_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["TEN_M_KEY"]])]="The Wind_Direction value =".$row["Wind_Direction"]."  recorded on ".$date_today."at ".$row["TIME"]." is too High";
                }
                else {
                    //do not report anything as the value is fine. 
                }
            }else if($row["Wind_Direction"]==""){
                $GLOBALS["error_reports"][$GLOBALS["TEN_M_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["TEN_M_KEY"]])]="The Wind_Direction value was not captured on ".$date_today."at ".$row["TIME"];
            }
            else {
                $GLOBALS["error_reports"][$GLOBALS["TEN_M_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["TEN_M_KEY"]])]="Wrong(Junk) Wind_Direction value =".$row["Wind_Direction"]."  was recorded on ".$date_today."at ".$row["TIME"];
            }
         }
         return $GLOBALS["error_reports"];
        }
        function checkPressureValues($con,$date_today){
            $sql_to_get_pressure ="SELECT CLP, TIME FROM observationslip WHERE observationslip.Date LIKE".
                " '$date_today' AND SubmittedBy LIKE 'AWS' AND CLP IS NOT NULL ORDER BY id DESC LIMIT 1";
        $pressure_results=$con->query($sql_to_get_pressure);
       // echo $sql_to_get_pressure;
        if($pressure_results->num_rows==0){
            $GLOBALS["error_reports"][$GLOBALS["SINK_NODE_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["SINK_NODE_KEY"]])]="The Pressure(CLP) value was not recorded on ".$date_today;
        }
         while ($row=$pressure_results->fetch_assoc()){
            if(is_numeric($row["CLP"])){
                //check whether it's within range
                if($row["CLP"]<$$GLOBALS["MIN_PRESSURE_VALUE"]){
                    $GLOBALS["error_reports"][$GLOBALS["SINK_NODE_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["SINK_NODE_KEY"]])]="The Pressure (CLP) value =".$row["CLP"]."  recorded on ".$date_today."at ".$row["TIME"]." is too low";
                }
                else if($row["CLP"]>$$GLOBALS["MAX_PRESSURE_VALUE"]){
                    $GLOBALS["error_reports"][$GLOBALS["SINK_NODE_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["SINK_NODE_KEY"]])]="The Pressure (CLP) value =".$row["CLP"]."  recorded on ".$date_today."at ".$row["TIME"]." is too High";
                }
                else {
                    //do not report anything as the value is fine. 
                }
            }else if($row["CLP"]==""){
                $GLOBALS["error_reports"][$GLOBALS["SINK_NODE_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["SINK_NODE_KEY"]])]="The Pressure (CLP) value was not captured on ".$date_today."at ".$row["TIME"];
            }
            else {
                $GLOBALS["error_reports"][$GLOBALS["SINK_NODE_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["SINK_NODE_KEY"]])]="Wrong(Junk) Pressure (CLP) value =".$row["CLP"]."  was recorded on ".$date_today."at ".$row["TIME"];
            }
         }
         
        }
        function checkRainfallValues($con,$date_today){
            $sql_to_get_rainfall ="SELECT Rainfall,TIME FROM observationslip WHERE observationslip.Date LIKE".
                " '$date_today' AND SubmittedBy LIKE 'AWS' AND Rainfall IS NOT NULL ORDER BY id DESC LIMIT 1";
        // echo $sql_to_get_rainfall."<br />";
        $rainfall_results=$con->query($sql_to_get_rainfall);
        if($rainfall_results->num_rows==0){
            $GLOBALS["error_reports"][$GLOBALS["GROUND_NODE_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["GROUND_NODE_KEY"]])]="The rainfall has not been recorded on ".$date_today;
        }
        $row ="";
        while($row=$rainfall_results->fetch_assoc()){
            if(is_numeric($row["Rainfall"])){
                //check whether it's within range
                if($row["Rainfall"]<$GLOBALS["MIN_RAINFALL_VALUE"]){
                    $GLOBALS["error_reports"][$GLOBALS["GROUND_NODE_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["GROUND_NODE_KEY"]])]="The Rainfall value =".$row["Rainfall"]."  recorded on ".$date_today."at ".$row["TIME"]." is too low";
                }
                else if($row["Rainfall"]>$GLOBALS["MAX_RAINFALL_VALUE"]){
                    $GLOBALS["error_reports"][$GLOBALS["GROUND_NODE_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["GROUND_NODE_KEY"]])]="The Rainfall value =".$row["Rainfall"]."  recorded on ".$date_today."at ".$row["TIME"]." is too High";
                }
                else {
                    //do not report anything as the value is fine. 
                }
            }else if($row["Rainfall"]==""){
               $GLOBALS["error_reports"][$GLOBALS["GROUND_NODE_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["GROUND_NODE_KEY"]])]="Rainfall was not capture on ".$date_today." at ".$row["TIME"];
            }
            else {
                $GLOBALS["error_reports"][$GLOBALS["GROUND_NODE_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["GROUND_NODE_KEY"]])]="Wrong(Junk) Rainfall value =".$row["Rainfall"]."  was recorded on ".$date_today."at ".$row["TIME"];
            } 
            
            
        }
        }
        function checkSoilMoistureValues($con,$date_today){
            $sql_to_get_soil_mositure ="SELECT SoilMoisture,TIME FROM observationslip WHERE observationslip.Date LIKE".
                " '$date_today' AND SubmittedBy LIKE 'AWS' AND SoilMoisture IS NOT NULL ORDER BY id DESC LIMIT 1";
       // echo $sql_to_get_soil_mositure."<br />";
        $soil_moist_results=$con->query($sql_to_get_soil_mositure);
       
        if($soil_moist_results->num_rows==0){
            $GLOBALS["error_reports"][$GLOBALS["GROUND_NODE_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["GROUND_NODE_KEY"]])]="The Soil Moisture has not been recorded on ".$date_today;
        }
        $row ="";
        while($row=$soil_moist_results->fetch_assoc()){
             if(is_numeric($row["SoilMoisture"])){
                //check whether it's within range
                if($row["SoilMoisture"]<$GLOBALS["MIN_SOILMOISTURE_VALUE"]){
                    $GLOBALS["error_reports"][$GLOBALS["GROUND_NODE_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["GROUND_NODE_KEY"]])]="The Soil Moisture value =".$row["SoilMoisture"]."  recorded on ".$date_today."at ".$row["TIME"]." is too low";
                }
                else if($row["SoilMoisture"]>$GLOBALS["MAX_SOILMOISTURE_VALUE"]){
                    $GLOBALS["error_reports"][$GLOBALS["GROUND_NODE_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["GROUND_NODE_KEY"]])]="The Soil Moisture value =".$row["SoilMoisture"]."  recorded on ".$date_today."at ".$row["TIME"]." is too High";
                }
                else {
                    //do not report anything as the value is fine. 
                }
            }else if($row["SoilMoisture"]==""){
               $GLOBALS["error_reports"][$GLOBALS["GROUND_NODE_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["GROUND_NODE_KEY"]])]="The Soil Moisture was not recorded on ".$date_today."at ".$row["TIME"];
            }
            else {
                $GLOBALS["error_reports"][$GLOBALS["GROUND_NODE_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["GROUND_NODE_KEY"]])]="Wrong(Junk)  Soil Moisture value =".$row["SoilMoisture"]."  was recorded on ".$date_today."at ".$row["TIME"];
            }  
        }
        return $GLOBALS["error_reports"];
        }
        function checkSoilTemperatureValues($con,$date_today){
            $sql_to_get_soil_temperature ="SELECT SoilTemperature,TIME FROM observationslip WHERE observationslip.Date LIKE".
                " '$date_today' AND SubmittedBy LIKE 'AWS' AND SoilTemperature IS NOT NULL ORDER BY id DESC LIMIT 1";
        $soil_temp_results=$con->query($sql_to_get_soil_temperature);
        //echo $sql_to_get_soil_temperature;
       // echo $soil_temp_results->num_rows;
        if($soil_temp_results->num_rows==0){
            $GLOBALS["error_reports"][$GLOBALS["GROUND_NODE_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["GROUND_NODE_KEY"]])]="The Soil Temperature has not been recorded on ".$date_today;
        }
        while ($row=$soil_temp_results->fetch_assoc()){
            
            if(is_numeric($row["SoilTemperature"])){
                //check whether it's within range
                if($row["SoilTemperature"]<$$GLOBALS["MIN_SOILTEMPERATURE_VALUE"]){
                    $GLOBALS["error_reports"][$GLOBALS["GROUND_NODE_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["GROUND_NODE_KEY"]])]="The Soil Temperature value =".$row["SoilTemperature"]."  recorded on ".$date_today."at ".$row["TIME"]." is too low";
                }
                else if($row["SoilTemperature"]>$$GLOBALS["MAX_SOILTEMPERATURE_VALUE"]){
                    $GLOBALS["error_reports"][$GLOBALS["GROUND_NODE_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["GROUND_NODE_KEY"]])]="The Soil Temperature value =".$row["SoilTemperature"]."  recorded on ".$date_today."at ".$row["TIME"]." is too High";
                }
                else {
                    //do not report anything as the value is fine. 
                    
                }
            }else if($row["SoilTemperature"]==""){
               $GLOBALS["error_reports"][$GLOBALS["GROUND_NODE_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["GROUND_NODE_KEY"]])]="The Soil Temperature was not recorded on ".$date_today."at ".$row["TIME"];
            }
            else {
                $GLOBALS["error_reports"][$GLOBALS["GROUND_NODE_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["GROUND_NODE_KEY"]])]="Wrong(Junk) Soil Temperature value =".$row["SoilTemperature"]."  was recorded on ".$date_today."at ".$row["TIME"];
            }
            
        }
        return $GLOBALS["error_reports"];
        }
        function checkTemperatureValues($con,$date_today){
        $sql_to_get_temp ="SELECT Dry_Bulb, Wet_Bulb, TIME FROM observationslip WHERE observationslip.Date LIKE '$date_today' AND SubmittedBy LIKE 'AWS' AND Dry_Bulb != 'NULL' ORDER BY id DESC LIMIT 1";
        $temp_result =$con->query($sql_to_get_temp);
        if($temp_result->num_rows==0){
            $GLOBALS["error_reports"][$GLOBALS["TWO_M_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["TWO_M_KEY"]])]="The Temperature hasn't been recorded today".$date_today;
        }
        
        while ($record = $temp_result->fetch_assoc()){
            if(is_numeric($record["Dry_Bulb"])){
                if ($record["Dry_Bulb"]<$GLOBALS["MIN_DRY_BULB_VALUE"]){
                    $GLOBALS["error_reports"][$GLOBALS["TWO_M_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["TWO_M_KEY"]])]="The Temperature (Dry Bulb) recorded at ".$record["TIME"]." on ".$date_today."is too low".$record["Dry_Bulb"];
                }
                else if($record["Dry_Bulb"]>$GLOBALS["MAX_DRY_BULB_VALUE"]){
                    $GLOBALS["error_reports"][$GLOBALS["TWO_M_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["TWO_M_KEY"]])]="The Temperature (Dry Bulb) recorded at ".$record["TIME"]." on ".$date_today."is too high:".$record["Dry_Bulb"];
                }
                else{
                    //echo "TEMPERATURE IS FINE <br />";
                }
            }
            else{
                $GLOBALS["error_reports"][$GLOBALS["TWO_M_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["TWO_M_KEY"]])]="The Temperature (Dry Bulb) recorded at ".$record["TIME"]." on ".$date_today."is not a number:".$record["Dry_Bulb"];
            }
            
            if(is_numeric($record["Wet_Bulb"])){
                if ($record["Wet_Bulb"]<$GLOBALS["MIN_WET_BULB_VALUE"]){
                    $GLOBALS["error_reports"][$GLOBALS["TWO_M_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["TWO_M_KEY"]])]="The Temperature (Dry Bulb) recorded at ".$record["TIME"]." on ".$date_today."is too low".$record["Wet_Bulb"];
                }
                else if($record["Wet_Bulb"]>$GLOBALS["MAX_WET_BULB_VALUE"]){
                    $GLOBALS["error_reports"][$GLOBALS["TWO_M_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["TWO_M_KEY"]])]="The Temperature (Dry Bulb) recorded at ".$record["TIME"]." on ".$date_today."is too high:".$record["Wet_Bulb"];
                }
                else{
                   // echo "WET TEMPERATURE IS FINE <br />";
                }
            }
            else{
                $GLOBALS["error_reports"][$GLOBALS["TWO_M_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["TWO_M_KEY"]])]="The Temperature (Dry Bulb) recorded at ".$record["TIME"]." on ".$date_today."is not a number:".$record["Wet_Bulb"];
            }
            
        }
       // echo $sql_to_get_temp;
        
        }
        function checkMCUValues($v_mcu_value,$node_availability){
            //test V_MCU values
            $float_number_pattern ="/[0-9]\.[0-9]+/";
        foreach($v_mcu_value as $node=>$value){
            if(preg_match($float_number_pattern,$value)){
                       //V_MCU value is fine
            }
            else if($value==NULL && !$node_availability[$node]){
                //do not report this since the node is down
            }
            else if($value=="(null)"){
                   $GLOBALS["error_reports"][$node][count($GLOBALS["error_reports"][$node])]="The V_MCU value was not reported. $value was recorded";
            }
            else if($value=="") {
                $GLOBALS["error_reports"][$node][count($GLOBALS["error_reports"][$node])]="The V_MCU value was not reported";
            }
            else{
               $GLOBALS["error_reports"][$node][count($GLOBALS["error_reports"][$node])]="Poor V_MCU value $value from the $node"; 
            }
        }
        }
        function checkE64Values($e64_value,$node_availability){
            //test e64 values
        foreach ($e64_value as $node=>$value){
            //check if the e64 value is actually made up of 16 lowercase letters and numbers
            if(preg_match("/^[a-z0-9]{16}$/",$value)){
                //echo "$node e64 value is fine <br />";
            }
            else if($value==NULL && !$node_availability[$node]){
                //ignore this scenario since the entire node is down
            }
            else if($value==""){
                $GLOBALS["error_reports"][$node][count($GLOBALS["error_reports"][$node])]="E64 not captured for $node";
            }
            else if($value=="(null)"){
                $GLOBALS["error_reports"][$node][count($GLOBALS["error_reports"][$node])]="E64 not captured for $node";
            }
            else{
                $GLOBALS["error_reports"][$node][count($GLOBALS["error_reports"][$node])]="bad E64 value $value captured for $node";
            }
        }
        }
        function checkVINvalues($v_in_value,$node_availability){
            //test V_IN VALUES
            $float_number_pattern ="/[0-9]\.[0-9]+/";
        foreach($v_in_value as $node=>$value){
            
             if(preg_match($float_number_pattern,$value)){
                       if($value<$GLOBALS["MIN_V_IN_VALUE"] && $value != NULL){
                           $GLOBALS["error_reports"][$node][count($GLOBALS["error_reports"][$node])]="V_IN value for ".$node." is very low";
                       }
                        else {
                                //the voltage value is fine
                        }
            }else if($value==NULL && !$node_availability[$node]){
                //do not report this since the node is down
            }
            else if($value=="(null)"){
                    $GLOBALS["error_reports"][$node][count($GLOBALS["error_reports"][$node])]="The reported V_IN value from $node is $value";
            }
            else if($value=="") {
                $GLOBALS["error_reports"][$node][count($GLOBALS["error_reports"][$node])]="The V_IN value was not reported";
            }
            else{
               $GLOBALS["error_reports"][$node][count($GLOBALS["error_reports"][$node])]="Poor V_IN value $value from the $node"; 
            }
        }
        }
        function checkNodeAvailability($node_availability){
             //check the node availability
        foreach($node_availability as $node=>$status){
            if(!$status){
                $GLOBALS["error_reports"][$node][count($GLOBALS["error_reports"][$node])]="Attention required: $node is down. ";
                sendMessage("Attention required: $node is down. ");
            }
        }
        }
       $con->close();
?>
