<?php
require "./include/db.inc";
require "./include/html.inc";
require "./include/userinfo.inc";

// argument becomes a title of a page
$header = getHeader("Vote page");
$header.= beginBody();

$userinfo_key = array();
$userinfo_formcategory = array();
$userinfo_caption = array();
$userinfo_default = array();
getUserInfoKey($userinfo_key, $userinfo_formcategory, $userinfo_caption, $userinfo_default);

$userinfo_value = array();
$userinfo_formcategory_value = array();
$userinfo_caption_value = array();
foreach($userinfo_key as $key => $value) {
	$tmpGet = isset($_GET[$value]) ? htmlspecialchars($_GET[$value]) : null;
	if(strcmp($tmpGet, "") == 0) {
		$tmpGet = $userinfo_default[$key];
	}
	$userinfo_value[$value] = $tmpGet;
	$userinfo_formcategory_value[$value] = $userinfo_formcategory[$key];
	$userinfo_caption_value[$value] = $userinfo_caption[$key];
}

$attribute_key = array();
$attribute_caption = array();
getAttributeKey($attribute_key, $attribute_caption);

$option_key = array();
$option_caption = array();
getOptionKey($option_key, $option_caption);

$form = "";
foreach($userinfo_value as $key => $value) {
	if(strcmp($userinfo_formcategory_value[$key], "text") == 0) {
		$form.= makeTextForm($key, $value, $userinfo_caption_value[$key]);
	} else if(strcmp($userinfo_formcategory_value[$key], "select") == 0) {
		$form.= makeSelectForm($attribute_key, $attribute_caption, $userinfo_value['attribute']);
	} else if(strcmp($userinfo_formcategory_value[$key], "button") == 0) {
		$form.= makeButtonForm($option_key, $option_caption);
	} else if(strcmp($userinfo_formcategory_value[$key], "click") == 0) {
		$form.= makeClickForm();
	}
}
$form.= endBody();

print $header . $form;
?>

