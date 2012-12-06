<?php /* @brief    Site navigation
*
* @details  -
*
* @author   Emil Lindström, emili250@student.liu.se
* @author   Svante Berg, svabe170@student.liu.se
* @date     ?
* @version  
*/
?>

<body>

<div id="container">	
	<div id="nav">
		<?php $img = img('styles/images/logotyp.png'); ?>
		<div class="image"><?php echo anchor('".base_url()."', $img); ?></div><div class="logo"><a href="<?=base_url();?>"><b>Norrköpings</b> Visualiseringscenter</a></div>
		
		<ul>
			<li><?php echo anchor('index.php/site/upload', 'Skapa ny värld');?></li>
			<li><?php echo anchor('index.php/site/add_information', 'Ändra befintlig värld');?></li>
			<li><?php echo anchor('index.php/site/instructions', 'Manual');?></li>
			<li><?php echo anchor('index.php/site/about', 'Om');?></li>
		</ul> 	
	</div>                            