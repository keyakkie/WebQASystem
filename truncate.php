<?php
require "./include/db.inc";
require "./include/html.inc";
require "./include/userinfo.inc";

// argument becomes a title of a page
$header = getHeader("Truncate data");
$footer = getFooter();

$db_config = array();
getDBConfig($db_config);
$con = mysql_connect($db_config['db_host'] . ":" . $db_config['db_port'], $db_config['db_user'], $db_config['db_passwd']);
if(!$con){ print "error:db connect<br />"; }
$db = mysql_select_db($db_config['db_name'], $con);
if(!$db){ print "error:db select<br />"; }
$res = truncateData();

$graph_size = $_GET['graph_size'];
$mode = $_GET['mode'];

$html = "";
if(!$res) {
	$html .= "error:failed to insertDB<br />";
} else {
	$html .= "successfully truncated<br />";
	$html .= "<a href=\"display.php?graph_size=" . $graph_size . "&mode=" . $mode . "\">go to the display page</a>";
}
print $header . $html . $footer;
?>
