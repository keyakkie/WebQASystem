<?php
function getDBConfig(&$db_config) {
	$db_config['db_host'] = "";
	$db_config['db_port'] = "3306";
	$db_config['db_user'] = "";
	$db_config['db_passwd'] = "";
	$db_config['db_name'] = "";
}

function insertData($userinfo_value) {
	$sql = "INSERT INTO vote VALUES (";
	foreach($userinfo_value as $key => $value) {
		$sql.= "'" . $value . "',";
	}
	$sql = preg_replace('/,\z/', '', $sql);
	$sql.= ");";

	$res = mysql_query($sql);

	return $res;
}

function getData() {
	$sql = "SELECT * FROM vote;";
	$res = mysql_query($sql);

	return $res;
}

function truncateData() {
	$sql = "TRUNCATE TABLE vote;";
	$res = mysql_query($sql);

	return $res;
}
?>

