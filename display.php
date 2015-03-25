<?php
require "./include/db.inc";
require "./include/html.inc";
require "./include/userinfo.inc";

$header = getHeader("Display data");
$footer = getFooter();

$graph_size = isset($_GET['graph_size']) ? htmlspecialchars($_GET['graph_size']) : null;
if(strcmp($graph_size, "") == 0) {
	$graph_size = 100;
}
$mode = isset($_GET['mode']) ? htmlspecialchars($_GET['mode']) : null;
if(strcmp($mode, "") == 0) {
	$mode = "all";
}

$userinfo_key = array();
$userinfo_formcategory = array();
$userinfo_caption = array();
$userinfo_default = array();
getUserInfoKey($userinfo_key, $userinfo_formcategory, $userinfo_caption, $userinfo_default);
$userinfo_key_reverse = array();
getUserInfoKeyReverse($userinfo_key, $userinfo_key_reverse);

$attribute_key = array();
$attribute_caption = array();
getAttributeKey($attribute_key, $attribute_caption);
$attribute_key_reverse = array();
getAttributeKeyReverse($attribute_key, $attribute_key_reverse);

$option_key = array();
$option_caption = array();
getOptionKey($option_key, $option_caption);

$data_matrix = array($userinfo_key, $userinfo_key);
$opinion_matrix = array();
$count_opinion = array();
foreach($attribute_key as $key => $value) {
	$count_opinion[$value] = 0;
}

$db_config = array();
getDBConfig($db_config);
$con = mysql_connect($db_config['db_host'] . ":" . $db_config['db_port'], $db_config['db_user'], $db_config['db_passwd']);
if(!$con){ print "error:db connect<br />"; }
$db = mysql_select_db($db_config['db_name'], $con);
if(!$db){ print "error:db select<br />"; }
$res = getData();
if(!$res) {
	$html.= "error:failed to get data<br />";
}

$html = "";
while($row = mysql_fetch_array($res)){
	$tmp_userinfo = array();
	foreach($userinfo_key as $key => $value) {
		$tmp_userinfo[$key] = $row[$value];
	}

	$matrix_key = $tmp_userinfo[$userinfo_key_reverse['attribute']] . ":" . $tmp_userinfo[$userinfo_key_reverse['opinion']];
	$account = getAccount($userinfo_key_reverse, $tmp_userinfo);
	if(strcmp($tmp_userinfo[$userinfo_key_reverse['focus']], "focus") == 0) {
		$account = "<span class=\"text-primary h4\"><strong>" . $account . "</strong></span>";
	} else if(strcmp($mode, "focus_only") == 0) {
		$account = "";
	}
	$opinion_matrix[$matrix_key][] = $account;
	if(!isset($count_opinion[$tmp_userinfo[$userinfo_key_reverse['attribute']]])) {
		$count_opinion[$tmp_userinfo[$userinfo_key_reverse['attribute']]] = 0;
	}
	$count_opinion[$tmp_userinfo[$userinfo_key_reverse['attribute']]]++;
}

$html .=<<<EOT
    <section class="container">
    <!-- Bootstrapのグリッドシステムclass="row"で開始 -->
    <table class="table table-striped table-bordered table-hover table-condensed">
EOT;

$graph_only = 0;
if(strcmp($mode, "graph_only") == 0) {
	$graph_only = 1;
} else {

	$html.=<<<EOT

		<thread>
			<tr class="active">
				<th class="col-xs-3 col-sm-3 col-md-3 col-lg-3"></th>
EOT;
foreach($option_caption as $key => $value) {
	$html.= "\n\t\t\t\t<th class=\"col-xs-3 col-sm-3 col-md-3 col-lg-3 text-center h4\">" . $value . "</th>";
}
$html.=<<<EOT

			</tr>
	    </thread>
	    </tbody>
EOT;
}

$option_count = 0;
foreach($attribute_key as $key => $value) {
	$option_count++;
	$attr_caption = $attribute_caption[$key];
	$html.= makeGraph($option_count, $value, $attr_caption, $graph_size, $option_key, $opinion_matrix, $count_opinion, $graph_only);
}
$html.= "</table></section><br />";
$form = makeGraphForm($graph_size, $mode);
$link = makeTruncateLink($graph_size, $mode);
print $header . $html . $form . $link . $footer;
?>
