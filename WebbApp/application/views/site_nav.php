<body>

<div id="container">	
	<div id="nav">
		<?php $img = img('styles/images/logotyp.png'); ?>
		<div class="image"><?php echo anchor('".base_url()."', $img); ?></div>
		<ul>
		<li><?php echo anchor('index.php/site/upload', 'Skapa ny värld');?></li>
		<li><?php echo anchor('index.php/site/add_information', 'Ändra befintlig värld');?></li>
		<li><?php echo anchor('index.php/site/about', 'Om');?></li>
		</ul> 	
	</div>                            