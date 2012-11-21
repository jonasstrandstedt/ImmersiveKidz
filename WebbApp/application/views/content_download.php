<?php 
echo "<div id='content'><div class='editList'><h2> VÄLJ VÄRLD </h2>";
	 foreach ($info as $groupDate) {
	 			echo "<div class='editObject'><a href='".base_url()."index.php/site/download_info/".$groupDate -> date."/".$groupDate -> group."'><span class='date'>". $groupDate -> date."</span><span class='group'>".$groupDate -> group."</span></a></div>";

			 }

echo"</div></div>";
?>