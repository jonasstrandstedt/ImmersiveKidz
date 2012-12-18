<div id="content">	
	
	<?php 
	$sokvag = '';
	if(($date != NULL || $date != '') && ($group != NULL || $group != '') ){
		$sokvag = "/".$date."/".$group;
	}

	?>
		<ul>
		<li><?php echo anchor('index.php/site/upload'.$sokvag, 'Ladda upp bilder');?></li>
		<li><?php echo ">";?></li>
		<li><?php echo anchor('index.php/site/add_information'.$sokvag, 'Fyll i info');?></li>
		<li><?php echo ">";?></li>
		<li><?php echo anchor('index.php/site/add_coordinates'.$sokvag, 'Placera ut bilder');?></li>
		<li><?php echo ">";?></li>
		<li><?php echo anchor('index.php/site/download_info'.$sokvag, 'Ladda ner');?></li>
		
		</ul>
		<hr size="1px" class="hr1"> <hr size="1px" class="hr2">
	</div>
	
