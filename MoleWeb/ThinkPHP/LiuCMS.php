<?php
function getWeek($date){
	$weekArray = array("天","一","二","三","四","五","六");
    $theWeek = "星期".$weekArray[date("w",$date)]; 
	return $theWeek;
}
function getProImg($attachment){
	$att_path = __ROOT__."/Attachments/Products/";
	if(!$attachment) return $att_path = $att_path."noimg_thumb.jpg";
	$attachment = explode('.',$attachment);
    $att_file = $att_path.$attachment[0]."_thumb.".$attachment[1];
	return $att_file;
    if(!file_exists($att_file)){
		return $att_path = $att_path."noimg_thumb.jpg";
    }else {
        return $att_path = $att_file;
    }
}
function msgType($types = 0){
	$msgTypeArray = array("留言","建议","投诉","合作");
    $theType = $msgTypeArray[$types]; 
	return $theType;
}
?>