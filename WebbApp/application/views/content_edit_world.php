<?php 
	echo "<div id='content'><div class='editList'><h2> VÄLJ EN VÄRLD ATT EDITERA </h2>";
	foreach ($info as $world)
	{
		echo "<div class='editObject'><a href='".base_url()."index.php/site/add_object_information/".htmlentities($world -> name)."'><span class='world'>".htmlentities($world-> name)."</span></a></div>";
	}
echo "</div></div>" ;
?>