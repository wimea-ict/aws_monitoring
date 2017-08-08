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
        $GLOBALS["TEN_M_KEY"]="10m";
        $GLOBALS["TWO_M_KEY"] ="2m";
        $GLOBALS["GROUND_NODE_KEY"] ="gnd";
        $GLOBALS["SINK_NODE_KEY"]="sink";
        
        date_default_timezone_set("UTC"); //all the times here are in UTC
        
	$con = new mysqli("localhost", "jmuhumuza", "joshua", "mobilewimeadb") or die("failed to connect");
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
		if(strpos($row["TXT"],$GLOBALS["TEN_M_KEY"])!=false){
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
                else if(strpos($row["TXT"],$GLOBALS["TWO_M_KEY"])!=false){
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
                else if(strpos($row["TXT"],$GLOBALS["GROUND_NODE_KEY"])!=false){
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
                else if(strpos($row["TXT"],$GLOBALS["SINK_NODE_KEY"]) !=false){
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
        checkNodeAvailability($node_availability,$con,$date_today);
        checkVINvalues($v_in_value,$node_availability,$con);
        //checkE64Values($e64_value,$node_availability);
        //checkMCUValues($v_mcu_value,$node_availability);
       
        
        
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
      saveErrorReports($con,$STATION_NUMBER);
        function sendMessage($message){
            //echo $message;
            mail("robein@ymail.com","Attention: makg2 aws", $message);
        }
        
        function saveErrorReports($con,$stationNumber){
            $associatedStation=$stationNumber;
            $errorMessage ="";
            $priority ="Low"; 
            $associatedNode ="";
            $date_time_now =gmdate("Y-m-d H:i:s",time());
            foreach($GLOBALS["error_reports"] as $node=>$report){
                foreach ($report as $key=>$error){
                    if(strpos($error,"Attention") != false){
                        $priority ="High";
                    }
                    else{
                        $priority ="Low"; 
                    }
                    $associatedNode =$node;
                        $errorMessage=$error;
                        $sql ="INSERT INTO node_error_reports(associatedStation,errorMessage,priority,associatedNode,date_recorded) VALUES(' $associatedStation',"
                    . "'$errorMessage','$priority','$associatedNode','$date_time_now')";
                        $con->query($sql);
  
                        
                }
            }
        }
        
        function checkWindSpeed($con,$date_today){
              $sql_to_get_wind_speed ="SELECT Wind_Speed, TIME FROM observationslip WHERE observationslip.Date LIKE".
                " '$date_today' AND SubmittedBy LIKE 'AWS' AND Wind_Speed IS NOT NULL ORDER BY id DESC LIMIT 1";
        $wind_speed_results=$con->query($sql_to_get_wind_speed);
        //echo $sql_to_get_pressure;
        
        if($wind_speed_results->num_rows==0){
           $error="The Wind_Speed value was not recorded on ".$date_today;
            $error_key="The Wind_Speed value was not recorded on ".$date_today;
        }
         while ($row=$wind_speed_results->fetch_assoc()){
            if(is_numeric($row["Wind_Speed"])){
                //check whether it's within range
                if($row["Wind_Speed"]<$GLOBALS["MIN_WIND_SPEED_VALUE"]){
                    $error="Very low Wind_Speed value ".$row["Wind_Speed"]."was recorded on ".$date_today."at ".$row["TIME"];
                    $error_key="Very low Wind_Speed value";
                }
                else if($row["Wind_Speed"]>$GLOBALS["MAX_WIND_SPEED_VALUE"]){
                     $error="Very High Wind_Speed value".$row["Wind_Speed"]."  recorded on ".$date_today."at ".$row["TIME"];
                     $error_key="Very High Wind_Speed value";
                }
            }else if($row["Wind_Speed"]==""){
             //   $error="The Wind_Speed value was not captured on ".$date_today."at ".$row["TIME"];
               // $error_key="The Wind_Speed value was not captured on ".$date_today;
            }
            else {
                $error="Wrong(Junk) Wind_Speed value ".$row["Wind_Speed"]."  was recorded on ".$date_today."at ".$row["TIME"];
                $error_key="Wrong(Junk) Wind_Speed value ".$row["Wind_Speed"];
            }
         }
         
         if(!checkIfErrorRecorded($con,$error_key)){
              $GLOBALS["error_reports"][$GLOBALS["TEN_M_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["TEN_M_KEY"]])]=$error;
         }
         
        }
        function checkwindDirection($con,$date_today){
            $sql_to_get_wind_direction ="SELECT Wind_Direction, TIME FROM observationslip WHERE observationslip.Date LIKE".
                " '$date_today' AND SubmittedBy LIKE 'AWS' AND Wind_Direction IS NOT NULL ORDER BY id DESC LIMIT 1";
        $wind_direction_results=$con->query($sql_to_get_wind_direction);
        //echo $sql_to_get_pressure;
        if($wind_direction_results->num_rows==0){
            $error="The Wind_Direction value was not recorded at all on ".$date_today;
            $error_key="The Wind_Direction value was not recorded at all on ".$date_today;
        }
         while ($row=$wind_direction_results->fetch_assoc()){
            if(is_numeric($row["Wind_Direction"])){
                //check whether it's within range
                if($row["Wind_Direction"]<$GLOBALS["MIN_WIND_SPEED_VALUE"]){
                    $error="Very Low Wind_Direction value ".$row["Wind_Direction"]."was recorded on ".$date_today."at ".$row["TIME"];
                    $error_key="Very Low Wind_Direction value";
                }
                else if($row["Wind_Direction"]>$GLOBALS["MAX_WIND_SPEED_VALUE"]){
                    $error="Very High Wind_Direction value ".$row["Wind_Direction"]."was recorded on ".$date_today."at ".$row["TIME"];
                    $error_key="Very High Wind_Direction value";
                }
                else {
                    //do not report anything as the value is fine. 
                }
            }else if($row["Wind_Direction"]==""){
               // $error="The Wind_Direction value was not captured on ".$date_today;
               // $error_key="The Wind_Direction value was not captured on ".$date_today;;
                
            }
            else {
                $error="Wrong(Junk) Wind_Direction value ".$row["Wind_Direction"]."  was recorded on ".$date_today."at ".$row["TIME"];
                $error_key="Wrong(Junk) Wind_Direction value";
            }
         }
         if(!checkIfErrorRecorded($con,$error_key)){
              $GLOBALS["error_reports"][$GLOBALS["TEN_M_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["TEN_M_KEY"]])]=$error;
         }
        }
        function checkPressureValues($con,$date_today){
            $sql_to_get_pressure ="SELECT CLP, TIME FROM observationslip WHERE observationslip.Date LIKE".
                " '$date_today' AND SubmittedBy LIKE 'AWS' AND CLP IS NOT NULL ORDER BY id DESC LIMIT 1";
        $pressure_results=$con->query($sql_to_get_pressure);
       // echo $sql_to_get_pressure;
        if($pressure_results->num_rows==0){
            $error="The Pressure(CLP) value was not recorded at all  on ".$date_today;
            $error_key="The Pressure(CLP) value was not recorded at all  on ".$date_today;;
        }
         while ($row=$pressure_results->fetch_assoc()){
            if(is_numeric($row["CLP"])){
                //check whether it's within range
                if($row["CLP"]<$GLOBALS["MIN_PRESSURE_VALUE"]){
                    $error="Very Low Pressure (CLP) value ".$row["CLP"]."  recorded on ".$date_today."at ".$row["TIME"];
                     $error_key="Very Low Pressure (CLP) value";
                }
                else if($row["CLP"]>$GLOBALS["MAX_PRESSURE_VALUE"]){
                    $error="Very High Pressure (CLP) value ".$row["CLP"]." was recorded on ".$date_today."at ".$row["TIME"];
                    $error_key="Very High Pressure (CLP) value";
                }
                else {
                    //do not report anything as the value is fine. 
                }
            }else if($row["CLP"]==""){
              //  $error="The Pressure (CLP) value was not captured on ".$date_today."at ".$row["TIME"];
                //$error_key="The Pressure (CLP) value was not captured on ".$date_today;
            }
            else {
                $error="Wrong(Junk) Pressure (CLP) value ".$row["CLP"]."  was recorded on ".$date_today."at ".$row["TIME"];
                $error_key="Wrong(Junk) Pressure (CLP) value";
            }
         }
         if(!checkIfErrorRecorded($con,$error_key)){
              $GLOBALS["error_reports"][$GLOBALS["SINK_NODE_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["SINK_NODE_KEY"]])]=$error;
         }
        }
        function checkRainfallValues($con,$date_today){
            $sql_to_get_rainfall ="SELECT Rainfall,TIME FROM observationslip WHERE observationslip.Date LIKE".
                " '$date_today' AND SubmittedBy LIKE 'AWS' AND Rainfall IS NOT NULL ORDER BY id DESC LIMIT 1";
        // echo $sql_to_get_rainfall."<br />";
        $rainfall_results=$con->query($sql_to_get_rainfall);
        if($rainfall_results->num_rows==0){
            $error="The rainfall has not been recorded on ".$date_today;
            $error_key=$error;
        }
        $row ="";
        while($row=$rainfall_results->fetch_assoc()){
            if(is_numeric($row["Rainfall"])){
                //check whether it's within range
                if($row["Rainfall"]<$GLOBALS["MIN_RAINFALL_VALUE"]){
                    $error="Very Low Rainfall value ".$row["Rainfall"]."  recorded on ".$date_today."at ".$row["TIME"]." is too low";
                    $error_key="Very Low Rainfall value";
                }
                else if($row["Rainfall"]>$GLOBALS["MAX_RAINFALL_VALUE"]){
                    $error="Very High Rainfall value ".$row["Rainfall"]."  recorded on ".$date_today."at ".$row["TIME"]." is too High";
                    $error_key="Very High Rainfall value";
                }
            }else if($row["Rainfall"]==""){
              // $error="Rainfall was not captured on ".$date_today." at ".$row["TIME"];
               //$error_key="Rainfall was not captured on ".$date_today;
            }
            else {
                $error="Wrong(Junk) Rainfall value =".$row["Rainfall"]."  was recorded on ".$date_today."at ".$row["TIME"];
                $error_key="Wrong(Junk) Rainfall value";
            }   
        }
        if(!checkIfErrorRecorded($con,$error_key)){
              $GLOBALS["error_reports"][$GLOBALS["GROUND_NODE_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["GROUND_NODE_KEY"]])]=$error;
         }
        }
        function checkSoilMoistureValues($con,$date_today){
            $sql_to_get_soil_mositure ="SELECT SoilMoisture,TIME FROM observationslip WHERE observationslip.Date LIKE".
                " '$date_today' AND SubmittedBy LIKE 'AWS' AND SoilMoisture IS NOT NULL ORDER BY id DESC LIMIT 1";
       // echo $sql_to_get_soil_mositure."<br />";
        $soil_moist_results=$con->query($sql_to_get_soil_mositure);
       
        if($soil_moist_results->num_rows==0){
            $error="The Soil Moisture has not been recorded on ".$date_today;
            $error_key =$error;
        }
        $row ="";
        while($row=$soil_moist_results->fetch_assoc()){
             if(is_numeric($row["SoilMoisture"])){
                //check whether it's within range
                if($row["SoilMoisture"]<$GLOBALS["MIN_SOILMOISTURE_VALUE"]){
                   $error ="Very Low Soil Moisture value ".$row["SoilMoisture"]."  recorded on ".$date_today."at ".$row["TIME"];
                   $error_key="Very Low Soil Moisture value";
                }
                else if($row["SoilMoisture"]>$GLOBALS["MAX_SOILMOISTURE_VALUE"]){
                    $error="Very Soil Moisture value =".$row["SoilMoisture"]."was recorded on ".$date_today."at ".$row["TIME"]."";
                    $error_key="Very Low Soil Moisture value";
                }
                else {
                    //do not report anything as the value is fine. 
                }
            }else if($row["SoilMoisture"]==""){
             //  $error="The Soil Moisture was not recorded on ".$date_today."at ".$row["TIME"];
             //  $error_key = "The Soil Moisture was not recorded on ".$date_today;
            }
            else {
                $error="Wrong(Junk)  Soil Moisture value =".$row["SoilMoisture"]."  was recorded on ".$date_today."at ".$row["TIME"];
                $error_key ="Wrong(Junk)  Soil Moisture value";
            }  
        }
        if(!checkIfErrorRecorded($con,$error_key)){
              $GLOBALS["error_reports"][$GLOBALS["GROUND_NODE_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["GROUND_NODE_KEY"]])]=$error;
         }
        }
        function checkSoilTemperatureValues($con,$date_today){
            $sql_to_get_soil_temperature ="SELECT SoilTemperature,TIME FROM observationslip WHERE observationslip.Date LIKE".
                " '$date_today' AND SubmittedBy LIKE 'AWS' AND SoilTemperature IS NOT NULL ORDER BY id DESC LIMIT 1";
        $soil_temp_results=$con->query($sql_to_get_soil_temperature);
        if($soil_temp_results->num_rows==0){
            $error="The Soil Temperature has not been recorded on ".$date_today;
            $error_key =$error;
        }
        while ($row=$soil_temp_results->fetch_assoc()){    
            if(is_numeric($row["SoilTemperature"])){
                //check whether it's within range
                if($row["SoilTemperature"]<$GLOBALS["MIN_SOILTEMPERATURE_VALUE"]){
                    $error="Very Low Soil Temperature value ".$row["SoilTemperature"]."was recorded on ".$date_today."at ".$row["TIME"];
                    $error_key="Very Low Soil Temperature value";
                }
                else if($row["SoilTemperature"]>$GLOBALS["MAX_SOILTEMPERATURE_VALUE"]){
                    $error="Very High Soil Temperature value ".$row["SoilTemperature"]."  recorded on ".$date_today."at ".$row["TIME"];
                    $error_key="Very High Soil Temperature value";
                }
            }else if($row["SoilTemperature"]==""){
              // $error="The Soil Temperature was not recorded on ".$date_today."at ".$row["TIME"];
               //$error_key="The Soil Temperature was not recorded on ".$date_today;
            }
            else {
                $error="Wrong(Junk) Soil Temperature value =".$row["SoilTemperature"]."  was recorded on ".$date_today."at ".$row["TIME"];
                $error_key="Wrong(Junk) Soil Temperature value";
            }
            
        }
        if(!checkIfErrorRecorded($con,$error_key)){
              $GLOBALS["error_reports"][$GLOBALS["GROUND_NODE_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["GROUND_NODE_KEY"]])]=$error;
         }
        }
        function checkTemperatureValues($con,$date_today){
        $sql_to_get_temp ="SELECT Dry_Bulb, Wet_Bulb, TIME FROM observationslip WHERE observationslip.Date LIKE '$date_today' AND SubmittedBy LIKE 'AWS' AND Dry_Bulb != 'NULL' ORDER BY id DESC LIMIT 1";
        $temp_result =$con->query($sql_to_get_temp);
        if($temp_result->num_rows==0){
            $error="The Temperature hasn't been recorded today".$date_today;
            $error_key=$error;
        }
        while ($record = $temp_result->fetch_assoc()){
            if(is_numeric($record["Dry_Bulb"])){
                if ($record["Dry_Bulb"]<$GLOBALS["MIN_DRY_BULB_VALUE"]){
                    $error="Very Low emperature (Dry Bulb) value".$record["Dry_Bulb"]." recorded at ".$record["TIME"]." on ".$date_today;
                    $error_key="Very Low emperature (Dry Bulb) value";    
                }
                else if($record["Dry_Bulb"]>$GLOBALS["MAX_DRY_BULB_VALUE"]){
                    $error="Very high Temperature (Dry Bulb) value ".$record["Dry_Bulb"]." was recorded at ".$record["TIME"]." on ".$date_today;
                    $error_key="Very high Temperature (Dry Bulb) value";
                }
            }
            else{
                $error="The Temperature (Dry Bulb) recorded at ".$record["TIME"]." on ".$date_today."is not a number:".$record["Dry_Bulb"];
                $error_key="The Temperature (Dry Bulb) recorded";
            }
            if(is_numeric($record["Wet_Bulb"])){
                if ($record["Wet_Bulb"]<$GLOBALS["MIN_WET_BULB_VALUE"]){
                   $error2="The Temperature (Wet Bulb) recorded at ".$record["TIME"]." on ".$date_today."is too low".$record["Wet_Bulb"];
                   $error2_key="The Temperature (Wet Bulb) recorded";
                }
                else if($record["Wet_Bulb"]>$GLOBALS["MAX_WET_BULB_VALUE"]){
                    $error2="The Temperature (wet Bulb) recorded at ".$record["TIME"]." on ".$date_today."is too high:".$record["Wet_Bulb"];
                    $error2_key="The Temperature (wet Bulb) recorded";
                }
                else{
                   // echo "WET TEMPERATURE IS FINE <br />";
                }
            }
            else{
                $error2="Junk Temperature (Wet Bulb) recorded at ".$record["TIME"]." on ".$date_today."is not a number:".$record["Wet_Bulb"];
                $error2_key="Junk Temperature (Wet Bulb) recorded";
            }
            
        }
       if(!checkIfErrorRecorded($con,$error_key)){
              $GLOBALS["error_reports"][$GLOBALS["TWO_M_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["TWO_M_KEY"]])]=$error;
       }
         
         if(!checkIfErrorRecorded($con,$error2_key)){
              $GLOBALS["error_reports"][$GLOBALS["TWO_M_KEY"]][count($GLOBALS["error_reports"][$GLOBALS["TWO_M_KEY"]])]=$error2;
         }
    }
        function checkMCUValues($v_mcu_value,$node_availability,$con){
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
                   $error="The V_MCU value was not reported. $value was recorded";
                   $error_key="The V_MCU value was not reported";
            }
            else if($value=="") {
                $error="The V_MCU value was not reported";
                $error_key=$error;
            }
            else{
               $error="Poor V_MCU value $value from the $node"; 
               $error_key="Poor V_MCU value";
            }
            if(!checkIfErrorRecorded($con,$error_key)){
              $GLOBALS["error_reports"][$node][count($GLOBALS["error_reports"][$node])]=$error;
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
        function checkVINvalues($v_in_value,$node_availability,$con){
            //test V_IN VALUES
            $float_number_pattern ="/[0-9]\.[0-9]+/";
        foreach($v_in_value as $node=>$value){
            
             if(preg_match($float_number_pattern,$value)){
                       if($value<$GLOBALS["MIN_V_IN_VALUE"] && $value != NULL){
                           $error="Very Low V_IN value for ".$node;
                           $error_key="Very Low V_IN value";
                       }
                        else {
                                //the voltage value is fine
                        }
            }else if($value==NULL && !$node_availability[$node]){
                //do not report this since the node is down
            }
            else if($value=="(null)"){
                    $error="wrong V_IN value from $node is $value";
                    $error_key="wrong V_IN value from";
            }
            else if($value=="") {
                $error="The V_IN value was not reported";
                $error_key =$error;
            }
            else{
               $error="Poor V_IN value $value from the $node"; 
               $error_key ="Poor V_IN value";
            }
            if(!checkIfErrorRecorded($con,$error_key)){
              $GLOBALS["error_reports"][$node][count($GLOBALS["error_reports"][$node])]=$error;
            }
        }
        }
        function checkNodeAvailability($node_availability,$con,$date_today){
             //check the node availability
        foreach($node_availability as $node=>$status){
            if(!$status){
                if($node==$GLOBALS["SINK_NODE_KEY"]){
                    $error="Special Attention required: THE STATION IS DOWN : ".$date_today;
                    $error_key=$error;
                }
                else{
                    $error="Special Attention required: $node is down. ".$date_today;
                    $error_key=$error;
                }
            }
            if(!checkIfErrorRecorded($con,$error_key)){
                $GLOBALS["error_reports"][$node][count($GLOBALS["error_reports"][$node])]=$error; 
                $message="<h4 style='color:red;'> ".$error."</h4>";
                sendMail($message,"CRITICAL PROBLEM WITH MAKG2 STATION");
            }
        }
        }
        function sendMail($error_message,$subject){
         $message ="<html>";
         $message .= "<body>";
         $message .=$error_message;
         $message .="</body>";
         $message .="</html>";
        echo $message;
        $headers = "MIME-Version: 1.0" . "\r\n";
        $headers .= "Content-type:text/html;charset=UTF-8" . "\r\n";
        // More headers
        $headers .= 'From: <awsmonitor@wimea.mak.ac.ug>' . "\r\n";
        $headers .= 'Cc: kccfcumo@gmail.com' . "\r\n";
        if(mail("robein@ymail.com",$subject,$message,$headers)){
            echo "<br /> Email sent";
        }
        
     }
        function checkIfErrorRecorded($con,$error_key){
           
            if($error_key==""){
                return true;//don't record
            }
            $sql ="SELECT * FROM node_error_reports WHERE errorMessage LIKE '%$error_key%' AND notification_sent='0'";
            $result =$con->query($sql);
            
            if($result->num_rows==0){
                
                return false;
            }
            else {
                
                           return true;
            }
        }
       $con->close();
?>
