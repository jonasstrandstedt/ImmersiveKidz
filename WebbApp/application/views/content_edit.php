<?php 
//$this->output->set_header("Content-type: text/html; charset=utf-8");
echo "<div id='content'><div class='editList'><h2> Välj värld: </h2>";
	 foreach ($info as $groupDate) {
	 			echo "<div class='editObject'><a href='".base_url()."index.php/site/add_information/".$groupDate -> date."/".$groupDate -> group."'>". $groupDate -> group ." (".$groupDate -> date.")</a></div>";
			 }

echo"</div></div>";
?>