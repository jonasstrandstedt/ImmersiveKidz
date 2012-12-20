<?php 
/* @brief    Site navigation
*
* @author   Emil Lindström, emili250@student.liu.se
* @author   Svante Berg, svabe170@student.liu.se
* @date     15 November 2012
*/
?>
<body>
	<div id="container">	
		<div id="nav">
			<?php $img = img('styles/images/logotyp.png'); ?>
			<div class="image"><?php echo anchor('".base_url()."', $img); ?></div><div class="logo"><a href="<?=base_url();?>"><b>Norrköpings</b> Visualiseringscenter</a></div>
			<ul>
				<li><?php echo anchor('index.php/site/upload', 'Skapa ny grupp');?></li>
				<li><?php echo anchor('index.php/site/add_information', 'Redigera grupp');?></li>
				<li>|</li>
				<li><?php echo anchor('index.php/site/add_world_and_objects', 'Skapa ny värld');?></li>
				<li><?php echo anchor('index.php/site/add_object_information', 'Redigera värld');?></li>
				<li>|</li>
				<li><?php echo anchor('index.php/site/instructions', 'Manual');?></li>
				<li><?php echo anchor('index.php/site/about', 'Om');?></li>
			</ul> 	
		</div>                            