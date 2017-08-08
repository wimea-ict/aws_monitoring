<?php

    $TIME_BEFORE_SECOND_REPORT =60*60; //time in seconds
    
    date_default_timezone_set("UTC"); //all the times here are in UTC
   // $con = new mysqli("localhost", "root", "bless1708ro", "mobilewimeadb") or die("failed to connect");
    $con = new mysqli("localhost", "jmuhumuza", "joshua", "mobilewimeadb") or die("failed to connect");
    $date_one_hr_ago =gmdate("Y-m-d H:i:s",time()-$TIME_BEFORE_SECOND_REPORT);
    $critical_subject=NULL;
    $sink_issue_found=false; $twom_issue_found=false; $tenm_issue_found=false; $gnd_issue_found=false;
    $sql_gnd_high_priority_issues ="SELECT * FROM `node_error_reports` WHERE associatedNode  LIKE '%gnd%' AND priority LIKE 'High' AND notification_sent=0";
    $gnd_issues_result = $con->query($sql_gnd_high_priority_issues);
     $gnd_errors ="<div>Issues with the Ground node <ul>";
    if($gnd_issues_result->num_rows==0){
        //do nothing
    }
    else{
        $report = $gnd_issues_result->fetch_assoc();
        $gnd_errors .="<li style='color:red;'>".$report["errorMessage"]."</li>";
         $critical_subject =$report["errorMessage"];
         $gnd_issue_found =true;
    }
    $sql_gnd_low_priority_issues="SELECT * FROM `node_error_reports` WHERE associatedNode  LIKE '%gnd%' AND priority LIKE 'Low' AND notification_sent=0 AND date_recorded>='$date_one_hr_ago'";
    $gnd_issues_low_result = $con->query($sql_gnd_low_priority_issues);
    if($gnd_issues_low_result->num_rows>0){
         $gnd_issue_found =true;
    }
    while($row = $gnd_issues_low_result->fetch_assoc()){
        $gnd_errors .="<li>".$row["errorMessage"]."</li>";
    }
     $gnd_errors .="</ul></div>";

    
    
     
    $sql_10m_high_priority_issues ="SELECT * FROM `node_error_reports` WHERE associatedNode  LIKE '%10m%' AND priority LIKE 'High' AND notification_sent=0";
    $tenm_issues_result = $con->query($sql_10m_high_priority_issues);
     $tenm_errors ="<di>Issues with the 10 meter node <ul>";
    if($tenm_issues_result->num_rows==0){
        //do nothing
    }
    else{
        $report = $tenm_issues_result->fetch_assoc();
        $tenm_errors .="<li style='color:red;'>".$report["errorMessage"]."</li>";
        $critical_subject =$report["errorMessage"];
        $tenm_issue_found =true;
    }
    $sql_10m_low_priority_issues="SELECT * FROM `node_error_reports` WHERE associatedNode  LIKE '%10m%' AND priority LIKE 'Low' AND notification_sent=0 AND date_recorded>='$date_one_hr_ago'";
    $tenm_issues_low_result = $con->query($sql_10m_low_priority_issues);
    if($tenm_issues_low_result->num_rows>0){
         $tenm_issue_found =true;
    }
    while($row = $tenm_issues_low_result->fetch_assoc()){
        $tenm_errors .="<li>".$row["errorMessage"]."</li>";
    }
     $tenm_errors .="</ul></div>";

     
     
     $sql_2m_high_priority_issues ="SELECT * FROM `node_error_reports` WHERE associatedNode  LIKE '%2m%' AND priority LIKE 'High' AND notification_sent=0";
    $twom_issues_result = $con->query($sql_2m_high_priority_issues);
     $twom_errors ="<div>Issues with the 2 meter node <ul>";
    if($twom_issues_result->num_rows==0){
        //do nothing
    }
    else{
        $report = $twom_issues_result->fetch_assoc();
        $twom_errors .="<li style='color:red;'>".$report["errorMessage"]."</li>";
        $critical_subject =$report["errorMessage"];
        $twom_issue_found =true;
    }
    $sql_2m_low_priority_issues="SELECT * FROM `node_error_reports` WHERE associatedNode  LIKE '%2m%' AND priority LIKE 'Low' AND notification_sent=0 AND date_recorded>='$date_one_hr_ago'";
    $twom_issues_low_result = $con->query($sql_2m_low_priority_issues);
    if($twom_issues_low_result->num_rows>0){
         $twom_issue_found =true;
    }
    while($row = $twom_issues_low_result->fetch_assoc()){
        $twom_errors .="<li>".$row["errorMessage"]."</li>";
    }
     $twom_errors .="</ul></div>";

     
     $sql_sink_high_priority_issues ="SELECT * FROM `node_error_reports` WHERE associatedNode  LIKE '%sink%' AND priority LIKE 'High' AND notification_sent=0";
    $sink_issues_result = $con->query($sql_sink_high_priority_issues);
     $sink_errors ="<div>Issues with the Sink node <ul>";
    if($sink_issues_result->num_rows==0){
        //do nothing
    }
    else{
        $report = $sink_issues_result->fetch_assoc();
        $sink_errors .="<li style='color:red;'>".$report["errorMessage"]."</li>";
        $critical_subject =$report["errorMessage"];
        $sink_issue_found =true;
    }
    $sql_sink_low_priority_issues="SELECT * FROM `node_error_reports` WHERE associatedNode  LIKE '%sink%' AND priority LIKE 'Low' AND notification_sent=0 AND date_recorded>='$date_one_hr_ago'";
    $sink_issues_low_result = $con->query($sql_sink_low_priority_issues);
    if($sink_issues_low_result->num_rows>0){
         $sink_issue_found =true;
    }
    while($row = $sink_issues_low_result->fetch_assoc()){
        $sink_errors .="<li>".$row["errorMessage"]."</li>";
    }
     $sink_errors .="</ul></div>";

     $erros=4;
     if(!$sink_issue_found){
         $sink_errors="";
         $erros-=1;
     }
     if(!$tenm_issue_found){
         $tenm_errors ="";
          $erros-=1;
     }
     if(!$twom_issue_found){
         $twom_errors="";
          $erros-=1;
     }
     if(!$gnd_issue_found){
         $gnd_errors ="";
          $erros-=1;
     } 
     if($erros>0){
          sendMail($sink_errors,$gnd_errors,$twom_errors,$tenm_errors,$subject);
     }
     
     $sql ="UPDATE `node_error_reports` SET notification_sent=1 WHERE date_recorded<'".gmdate("Y-m-d H:i:s",time())."'";
     //echo $sql;
     $con->query($sql);
     function sendMail($sink_errors,$gnd_errors,$twom_errors,$tenm_errors,$subject){
         $message ="<html>";
         $message .= "<body>";
         $message .=$sink_errors;
         $message .=$gnd_errors;
         $message .=$twom_errors;
         $message .=$tenm_errors;
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
     
?>