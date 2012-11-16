<?php 
echo "<div id='content'><div class='editList'>";
	 foreach ($info as $groupDate) {
	 			echo "<div class='editObject'><a href='".base_url()."index.php/site/add_information/".$groupDate -> date."/".$groupDate -> group."'>". $groupDate -> group ."</a></div>";

			 }

echo"</div></div>";
?>