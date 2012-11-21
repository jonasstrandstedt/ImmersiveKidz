<?php 
/*
* @brief   	The page where you view and edit pictures and related information
*
* @details  
*
* @author   Viktor Fr�berg, vikfr292@student.liu.se
* @author 	Belinda Bernfort, belbe886@student.liu.se
* @date     November 14, 2012 
* @version  1.0
*    
*/

$counter = 0;

	echo "<div id='sub'>". form_open_multipart('index.php/site/add_information/');
	$column = 0;
	$idArray = array();
	echo "<div class='form'><div class='row'>
		<input type='hidden' name='date' value='".$images[0] -> date."' />
		<input type='hidden' name='group' value='".$images[0] -> group."' />";
	foreach ($images as $row)
	{ 

	echo "<div class='imgform'>
	<div class='image'><img src='../../../../".$row -> imgouturl."' alt='Bildj�vel' width='90' /> </div>
		<label>Konstn�r:</label>
		<input type='text' name='artist".$column."' value='".$row -> artist."' />
    	<label>Titel:</label>
		<input type='text' name='imgname".$column."' value='".$row -> imgname."' />
    	<label>Typ:</label>
		<input type='text' name='type".$column."' value='' />
    	<label>Tr�skelv�rde:</label>
		<input type='range' name='threshold".$column."' min='1' max='10' value='5' />
    	<label>Historia:</label>
	 	<input type='text' name='story".$column."' value='".$row -> story."' />
    	<label>Ljud:</label>
		<input type='file' name='soundurl".$column."' />
		</div>";
 			
 		$column++;

 		if($column%3 == 0){
 			echo "</div><div class='row'>";
 		}
	}
echo "</div></div>";
?>
<div id="buttoninfo"><input class="styledbutton" type="submit" value="G� vidare" name="update"></div>
</form>
</div>		