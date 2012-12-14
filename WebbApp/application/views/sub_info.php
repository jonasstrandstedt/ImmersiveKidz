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
*/	//echo print_r($images);
	echo "<div id='sub'>". form_open_multipart('index.php/site/add_information/');
	$column = 0;
	echo "<div class='form'><div class='row'>
		<input type='hidden' name='group_id' value='".$group_id[0] -> id."' />";

	foreach ($images as $row)
	{ 
		
		if(htmlentities($row -> soundurl) == ''){
			$typeSound = "file";
			$editFileInput = "";
		}
		else{
			$typeSound = "text";
			$editFileInput = "<input type='file' name='soundurl".$column."'/><br/>";
		}
		$temp = htmlentities($row -> soundurl);
		$soundvalue = substr($temp, strrpos($temp, "/")+1);
	//<img src='".base_url()."styles/images/rotateplus.png' alt=''/>
		echo "<div id='imgform".$column."' class='imgform'>
		<div class='image'><img src='../../../../".$outImages[$column]."' alt='Image' width='90' /> </div>
		<div class='button'>
		<button class='styledDeleteButton' type='submit' name='delete' value='".$column."' >X</button>
		<button class='styledRotateMinus' type='submit' name='rotateminus' value='".$column."' >ROTERA -90&#176;</button>		
		<button class='styledRotatePlus' type='submit' name='rotateplus' value='".$column."' >ROTERA +90&#176;</button>
		<hr size='1px' class='hrbutton1'> <hr size='1px' class='hrbutton2'>
		</div>
		<label>Konstn�r:</label>
		<input type='text' name='artist".$column."' value='".htmlentities($row -> artist)."' />
    	<label>Titel:</label>
		<input type='text' name='imgname".$column."' value='".htmlentities($row -> imgname)."' />
    	<label>Typ:</label>
		<input type='text' name='type".$column."' value='' />
    	<label>Tr�skelv�rde:</label>
		<input type='range' name='threshold".$column."' min='1' max='10' value='".$row -> thresh."' />
    	<label>Historia:</label>
	 	<input type='text' name='story".$column."' value='".htmlentities($row -> story)."' />
    	<label>Ljud:</label>
		<input type='".$typeSound."' name='soundurl".$column."' value='".$soundvalue."' />".$editFileInput."
		<label>Byt ut bild:</label>
		<input type='file' name='imageurl".$column."'/>
		</div>";
 
 		$column++;

 		if($column%3 == 0){
 			echo "</div><div class='row'>";
 		}
	}
echo "</div></div>";
?>
<div id="buttoninfo">
	<input class="styledbutton" type="submit" value="Uppdatera bilder" name="update">
	<input class="styledbutton" type="submit" value="G� vidare" name="next">
</div>
</form>
</div>		