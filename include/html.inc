<?php
function getHeader($title) {
	$header =<<<EOT
<!DOCTYPE html>
<html lang="en">
	<head>
		<meta charset="utf-8">
		<meta http-equiv="X-UA-Compatible" content="IE=edge">
		<meta name="viewport" content="width=device-width, initial-scale=1">
		<title>$title</title>

		<!-- Bootstrap -->
		<link rel="stylesheet" type="text/css" href="dist/css/bootstrap-select.css">
		<link href="dist/css/bootstrap.min.css" rel="stylesheet">
		<script type="text/javascript" src="dist/js/jquery-1.10.1.min.js"></script>
		<script type="text/javascript" src="dist/js/bootstrap-select.js"></script>
		<script type="text/javascript" src="dist/js/bootstrap.min.js"></script>
		<script type="text/javascript" src="dist/js/Chart/Chart.js"></script>
	</head>
	<body>
EOT;

	return $header;
}

function beginBody() {
	$html =<<<EOT
		<div class="container">
			<h3>Vote your opinion</h3>
			<form action="insertDB.php" method="get">
EOT;

	return $html;
}

function endBody() {
    $html =<<<EOT
			<script>
				$(document).ready(function () {
					var mySelect = $('#first-disabled2');
					$('#special').on('click', function () {
						mySelect.find('option:opinion').attr('disabled', 'disabled');
						mySelect.selectpicker('refresh');
					});
					var \$basic2 = $('#basic2').selectpicker({
						liveSearch: true,
						maxOptions: 1
					});
				});
			</script>

			<script>
				$(".alignment .btn").click(function() {
					$("#alignment").val($(this).attr('name'));
				});
			</script>

			<script>
				$(".alignment2 .btn").click(function() {
					$("#alignment2").val($(this).attr('name'));
				});
			</script>
		</div>
	</body>
</html>
EOT;

	return $html;
}

function getFooter() {
	$footer = "\t</body>\n</html>";

	return $footer;
}

function makeLink($userinfo_value, $userinfo_default_value) {
	$link = "<p><a href=\"vote.php?";
	foreach($userinfo_value as $key => $value) {
		if(strcmp($userinfo_default_value[$key], "") != 0) {
			$link.= $key . "=" . $userinfo_default_value[$key] . "&";
		} else {
			$link.= $key . "=" . $value . "&";
		}
	}
	$link = preg_replace('/&\z/', '', $link);
	$link.= "\">back to the vote page</a></p>";

	return $link;
}

function makeTruncateLink($graph_size, $mode) {
	$link = "truncate.php?graph_size=" . $graph_size . "&mode=" . $mode;
	$link_html = "<div class=\"container\"><a href=\"" . $link . "\">clear vote results</a></div>";

	return $link_html;
}

function makeTextForm($key, $value, $caption) {
	$text_html = "\n\t\t\t\t" . $caption . ":<input type=\"text\" placeholder=\"" . $key . "\" name=\"" . $key . "\"";
	if(strcmp($value, "") != 0) {
		$text_html.= " value=\"" . $value . "\"";;
	}
	$text_html.= "/><br />";

	return $text_html;
}

function makeSelectForm($attribute_key, $attribute_caption, $attr) {
	$select_html = "\n\t\t\t\t<select class=\"selectpicker\" name=\"attribute\">";
	foreach($attribute_key as $key => $value) {
		if(strcmp($value, $attr) == 0) {
			$select_html.= "\n\t\t\t\t\t<option value=\"" . $value . "\" selected>" . $attribute_caption[$key] . "</option>";
		} else {
			$select_html.= "\n\t\t\t\t\t<option value=\"" . $value . "\">" . $attribute_caption[$key] . "</option>";
		}
	}
	$select_html.= "\n\t\t\t\t</select><br />\n";

	return $select_html;
}

function makeButtonForm($option_key, $option_caption) {
	$button_html =<<<EOT
				<input type="hidden" id="alignment" name="opinion" value="" />
				<div class="btn-group alignment" data-toggle="buttons-radio">
EOT;
	foreach($option_key as $key => $value) {
		$button_html.= "\n\t\t\t\t\t<button type=\"button\" class=\"btn btn-info\" name=\"" . $value . "\">" . $option_caption[$key] . "</button>";
	}
	$button_html.= "\n\t\t\t\t</div><br />\n";

	return $button_html;
}

function makeClickForm() {
	    $click_html =<<<EOT
				<input type="hidden" id="alignment2" name="focus" value="" />
				<div class="btn-group2 alignment2" data-toggle="buttons-radio">
					<button type="button2" class="btn btn-warning" name="focus">Focus on me</button>
				</div><br />
				<button type="submit" class="btn btn-primary">Submit</button>
			</form>

EOT;

	return $click_html;
}

function getBGColor($option_count) {
	$bgcolor = "";
	if($option_count == 1) {
		$bgcolor = "success";
	} else if($option_count == 2) {
		$bgcolor = "info";
	} else if($option_count == 3) {
		$bgcolor = "warning";
	} else if($option_count == 4) {
		$bgcolor = "danger";
	}

	return $bgcolor;
}

function getGraphColor($graph_count) {
	$color = "";
	if($graph_count == 1) {
		$color = "#E5004F";
	} else if($graph_count == 2) {
		$color = "#0068B7";
	} else if($graph_count == 3) {
		$color = "#8FC31F";
	} else {
		$color = "#FFFFFF";
	}

	return $color;
}

function makeGraph($option_count, $attr, $attr_caption, $graph_size, $option_key, $opinion_matrix, $count_opinion, $graph_only) {
	$graph_count = 0;
	$bgcolor = getBGColor($option_count);
	$color = "";
	$graph_html = "";
	if($graph_only == 0) {
		$graph_html.= "<tr class=\"" . $bgcolor . "\">";
	}
	$graph_html.= "<td class=\"";
	if($graph_only == 1) {
		$graph_html.= "$bgcolor ";
	}
	$graph_html.=<<<EOT
col-xs-3 col-sm-3 col-md-3 col-lg-3 h4 text-center"><div>$attr_caption</div>
		<canvas id="pieArea$option_count" height="$graph_size" width="$graph_size"></canvas>
		<div id="pieLegend$option_count"></div>
		<script>
			var datasets = [
EOT;
	foreach($option_key as $key => $value) {
		$graph_count++;
		$color = getGraphColor($graph_count);
		$matrix_key = $attr . ":" . $value;
		$rate = 0;
		if(isset($opinion_matrix[$matrix_key])) {
			$graph_html.= "\n\t\t\t\t{\n\t\t\t\t\tvalue:" . round(((double) count($opinion_matrix[$matrix_key]) / $count_opinion[$attr] * 100), 1) . ","
				. "\n\t\t\t\t\tcolor : \"" . $color . "\",\n\t\t\t\t\tlineColor: \"" . $color . "\",\n\t\t\t\t\tlabel: \"Yes\"\n\t\t\t\t},";
		} else {
			$graph_html.= "\n\t\t\t\t{\n\t\t\t\t\tvalue:0,"
				. "\n\t\t\t\t\tcolor : \"" . $color . "\",\n\t\t\t\t\tlineColor: \"" . $color . "\",\n\t\t\t\t\tlabel: \"Yes\"\n\t\t\t\t},";
		}
	}
	$graph_html = preg_replace('/,\z/', '', $graph_html);
	$graph_html.=<<<EOT

			];
			var options$option_count = {
				legendTemplate : "<ul class=\"<%=name.toLowerCase()%>-legend\"><% for (var i=0; i<datasets.length; i++){%><li><span style=\"background-color:<%=datasets[i].lineColor%>\">&nbsp;&nbsp;&nbsp;</span><%if(datasets[i].label){%><%=datasets[i].label%><%}%></li><%}%></ul>"
			};
			var myPie = new Chart(document.getElementById("pieArea$option_count").getContext("2d")).Pie(datasets, options$option_count);
			document.getElementById("pieLegend$option_count").innerHTML = myPie.generateLegend();
		</script>
EOT;
	if($graph_only == 0) {
		foreach($option_key as $key => $value) {
			$matrix_key = $attr . ":" . $value;
			if(isset($opinion_matrix[$matrix_key])) {
				$graph_html.= "</td><td class=\"col-xs-3 col-sm-3 col-md-3 col-lg-3\"><div class=\"h5 text-center\"><strong>"
					. round(((double) count($opinion_matrix[$matrix_key]) / $count_opinion[$attr] * 100), 1) . "%</strong></div>";
			} else {
				$graph_html.= "</td><td class=\"col-xs-3 col-sm-3 col-md-3 col-lg-3\"><div class=\"h5 text-center\"><strong>0%</strong></div>";
			}
			$str = "";
			if(isset($opinion_matrix[$matrix_key])) {
				foreach($opinion_matrix[$matrix_key] as $key => $value) {
					if(strcmp($value, "") != 0) {
						$str .= ", " . $value;
					}
				}
			}
			$graph_html.= preg_replace("/^, /m", "", $str);
		}
	}
	if($graph_only == 0 || ($option_count % 2) == 0) {
		$graph_html.= "</td></tr>";
	} else {
		$graph_html.= "</td>";
	}

	return $graph_html;
}

function makeGraphForm($graph_size, $mode) {
	$form_html =<<<EOT
	<div class="container">
		<form action="display.php" method="get">
			<input type="text" placeholder="graph size" name="graph_size" value="$graph_size"/>
			<input type="hidden" id="alignment" name="mode" value="" />
			<div class="btn-group alignment" data-toggle="buttons-radio">
				<button type="button" class="btn btn-info" name="all">All</button>
				<button type="button" class="btn btn-info" name="focus_only">Focus</button>
				<button type="button" class="btn btn-info" name="graph_only">Graph</button>
			</div>
			<button type="submit" class="btn btn-primary">Change</button>
		</form>
	</div>
	<script>
		$(document).ready(function(){
			var mode = '$mode';
			$("#alignment").val(mode);
		});

		$(".alignment .btn").click(function() {
			$("#alignment").val($(this).attr('name'));
		});
	</script>
EOT;

	return $form_html;
}
?>

