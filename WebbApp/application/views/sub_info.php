<!--<form name="form" method="post">
<input type="submit" name="button1" value="Button 1" /> 
<input type="submit" name="button2" value="Button 2" /> 
<input type="submit" name="button3" value="Button 3" /> 
<input type="submit" name="button4" value="Button 4" />

</form> -->
<?php 
if(isset($_POST['delete1'])){

echo("You clicked button one!");

}//if isset
/*
* @brief   	The page where you view and edit pictures and related information
*
* @details  
*
* @author   Viktor Fröberg, vikfr292@student.liu.se
* @author 	Belinda Bernfort, belbe886@student.liu.se
* @date     November 14, 2012 
* @version  1.0
*    
*/

	echo "<div id='sub'>". form_open_multipart('index.php/site/add_information/');
	$column = 0;
	$idArray = array();
	echo "<div class='form'><div class='row'>
		<input type='hidden' name='date' value='".$images[0] -> date."' />
		<input type='hidden' name='group' value='".$images[0] -> group."' />";
	foreach ($images as $row)
	{ 
		echo "<div id='imgform".$column."' class='imgform'>
		
		


		<div class='image'><img src='../../../../".$row -> imgouturl."' alt='Bildjävel' width='90' /> </div>
		<label>Konstnär:</label>
		<input type='text' name='artist".$column."' value='".$row -> artist."' />
    	<label>Titel:</label>
		<input type='text' name='imgname".$column."' value='".$row -> imgname."' />
    	<label>Typ:</label>
		<input type='text' name='type".$column."' value='' />
    	<label>Tröskelvärde:</label>
		<input type='range' name='threshold".$column."' min='1' max='10' value='5' />
    	<label>Historia:</label>
	 	<input type='text' name='story".$column."' value='".$row -> story."' />
    	<label>Ljud:</label>
		<input type='file' name='soundurl".$column."' />
		<button type='submit' name='delete' value='".$column."' >Ta bort bild</button>
		</div>";
 
 		$column++;

 		if($column%3 == 0){
 			echo "</div><div class='row'>";
 		}
	}
echo "</div></div>";
?>
<div id="buttoninfo"><input class="styledbutton" type="submit" value="Gå vidare" name="update"></div>
</form>
</div>		