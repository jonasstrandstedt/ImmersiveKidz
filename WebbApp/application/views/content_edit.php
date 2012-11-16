<?php 
echo "<div id='content'>";
	 foreach ($info as $groupDate) {
	 			echo "<a href='".base_url()."index.php/site/add_information/".$groupDate -> date."/".$groupDate -> group."'>". $groupDate -> group ."</a></ br>";

			 }

echo"</div>";
?>