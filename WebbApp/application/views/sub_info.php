<div id="sub">		
		<div id="sub">		

<h1>Här är alla fina bilder, jippi</h1>
		<p> majs</p>

<?php 
$im1 = '../../uploads/hej1.png';
$im2 = '../../uploads/hej2.jpg';
$im3 = '../../uploads/hej3.jpg';
$im4 = '../../uploads/hu1.gif';
$im5 = '../../uploads/hu2.jpg';
$im6 = '../../uploads/hu3.jpg';
$im7 = '../../uploads/bla1.jpg';
$im8 = '../../uploads/bla2.jpg';

$images = array($im1, $im2, $im3, $im4, $im5, $im6, $im7, $im8);

$counter = 0;
?>

<form method="post" action="http://www....">
<table>
	
 	<tr>
  		<?php
  		$column = 0;
		$columns = 3;

  		foreach ($images as $im)
  		{ 

    		if ($column and !($column % $columns)) {
        		echo '</tr><tr>';
    		}
    		echo "<td>
				<table>
					<tr>
						<td>
							<img src='$im' alt='Bildjävel' width='90' > 
						</td>
				  	<tr>
				    	<td>Konstnär:
				    	</td>
				    	<td>
				      		<input type='text' name='artist'>
				    	</td>
					</tr>
					<tr>
				        <td>Titel:
				      	</td>
				    	<td>
				    		<input type='text' name='title'>
				    	</td>
				    </tr>
					<tr>
					    <td>Typ:
				      	</td>
				    	<td>	
				    		<input type='text' name='type'>
				    	</td>
				    </tr>
					<tr>
					    <td>Tröskelvärde:
				      	</td>
				    	<td>
				    		<input type='range' name='threshold' min='1' max='10' value='5'>
				    	</td>
				    </tr>
					<tr>
					    <td>Historia:
				     	</td>
				    	<td>
				    	 	<input type='text' name='history'>
				    	</td>
				    </tr>
					<tr>
					    <td>Ljud:
				      	</td>
				    	<td>
				    		<input type='file' name='sound'>
				    	</td>
				  </tr>
				</table>
			</td>";
   	 		$column++;
		}
		for ($x = $column; $x < $columns; $x++) { echo '<td>&nbsp;</td>'; }
	?>

	</tr>
</table>

<p><input type="submit" value="Submit" name="B1"></p>
</form>
		

<?php echo anchor('index.php/site/create/download', 'Gå vidare');?>


</div>
	
	
</div>
	
	