<?php
function getUserInfoKey(&$userinfo_key, &$userinfo_formcategory, &$userinfo_caption, &$userinfo_default) {
	array_push($userinfo_key, "fname", "gname", "affiliation", "attribute", "opinion", "focus");
	array_push($userinfo_formcategory, "text", "text", "text", "select", "button", "click");
	array_push($userinfo_caption, "姓", "名", "所属", "区分", "意見", "強調");
	array_push($userinfo_default, "", "", "", "", "", "non-focus");
}

function getUserInfoKeyReverse(&$userinfo_key, &$userinfo_key_reverse) {
	foreach($userinfo_key as $key => $value) {
		$userinfo_key_reverse[$value] = $key;
	}
}

function getAttributeKey(&$attribute_key, &$attribute_caption) {
	array_push($attribute_key, "academia", "company", "doctor", "master");
	array_push($attribute_caption, "大学教員", "企業研究者", "博士課程学生", "修士・学部学生");
}

function getAttributeKeyReverse(&$attribute_key, &$attribute_key_reverse) {
	foreach($attribute_key as $key => $value) {
		$attribute_key_reverse[$value] = $key;
	}
}

function getOptionKey(&$option_key, &$option_caption) {
	array_push($option_key, "yes", "neutral", "no");
	array_push($option_caption, "賛成", "中立", "反対");
}

function getAccount($userinfo_key_reverse, $tmp_userinfo) {
	$account = $tmp_userinfo[$userinfo_key_reverse['fname']] . " " . $tmp_userinfo[$userinfo_key_reverse['gname']] . "(" . $tmp_userinfo[$userinfo_key_reverse['affiliation']] . ")";
	return $account;
}
?>

