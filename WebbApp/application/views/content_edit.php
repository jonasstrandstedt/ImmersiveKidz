<?php 
//$this->output->set_header("Content-type: text/html; charset=utf-8");
echo "<div id='content'><div class='editList'><h2> VÄLJ EN VÄRLD ATT EDITERA </h2>";
	 foreach ($info as $group) {
	 			echo "<div class='editObject'><a href='".base_url()."index.php/site/add_information/".$group -> date."/".$group -> name."'><span class='date'>". $group -> date."</span><span class='group'>".$group-> name."</span></a></div>";
			 }

echo"</div></div>";
?>