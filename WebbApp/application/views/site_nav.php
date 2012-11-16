<body>

<div id="container">	
	<div id="nav">
		<ul>
		<?php echo "<div class='image'><img src='".base_url()."/styles/images/logotyp.png' /></div>"; ?>
		<li><?php echo anchor('index.php/site/create/upload', 'Skapa ny värld');?></li>
		<li><?php echo anchor('index.php/site/edit', 'Ändra befintlig värld');?></li>
		<li><?php echo anchor('index.php/site/about', 'Om');?></li>
		</ul> 	
	</div>