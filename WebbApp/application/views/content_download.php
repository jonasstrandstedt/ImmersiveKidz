<?php 
echo "<div id='content'><div class='editList'><h2> VÄLJ EN VÄRLD ATT LADDA NER </h2>";
	 foreach ($info as $group) {
	 			echo "<div class='editObject'><a href='".base_url()."index.php/site/download_info/".$group -> date."/".$group -> name."'><span class='date'>". $group -> date."</span><span class='group'>".$group -> name."</span></a></div>";

			 }

echo"</div></div>";
?>