<?php
require "./include/db.inc";
require "./include/html.inc";
require "./include/userinfo.inc";

// argument becomes a title of a page
$header = getHeader("Insert data");
$footer = getFooter();

$db_config = array();
getDBConfig($db_config);
$con = mysql_connect($db_config['db_host'] . ":" . $db_config['db_port'], $db_config['db_user'], $db_config['db_passwd']);
if(!$con){ print "error:db connect<br />"; }
$db = mysql_select_db($db_config['db_name'], $con);
if(!$db){ print "error:db select<br />"; }

$userinfo_key = array();
$userinfo_formcategory = array();
$userinfo_caption = array();
$userinfo_default = array();
getUserInfoKey($userinfo_key, $userinfo_formcategory, $userinfo_caption, $userinfo_default);

$userinfo_value = array();
$userinfo_caption_value = array();
$userinfo_default_value = array();
foreach($userinfo_key as $key => $value) {
	$tmpGet = $_GET[$value];
	if(strcmp($tmpGet, "") == 0) {
		$tmpGet = $userinfo_default[$key];
	}
	$userinfo_value[$value] = $tmpGet;
	$userinfo_caption_value[$value] = $userinfo_caption[$key];
	$userinfo_default_value[$value] = $userinfo_default[$key];
}

$check = false;
$html = "";
foreach($userinfo_value as $key => $value) {
	if(strcmp($value, "") == 0) {
		$html.= "please input/choose " . $userinfo_caption_value[$key] . "<br />";
		$check = true;
	}
}
if($check == true) {
	$html.= "vote again<br />";
} else {
	$res = insertData($userinfo_value);
	if(!$res) {
		$html.= "error:failed to insertDB<br />";
	} else {
		$html.= "voted!";
	}
}
$link = makeLink($userinfo_value, $userinfo_default_value);
print $header . $html . $link . $footer;
?>

