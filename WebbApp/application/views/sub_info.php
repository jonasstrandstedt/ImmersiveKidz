<?php 
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
*/	//echo print_r($images);
	echo "<div id='sub'>". form_open_multipart('index.php/site/add_information/');
	$column = 0;
	echo "<div class='form'><div class='row'>
		<input type='hidden' name='group_id' value='".$group_id[0] -> id."' />";
	$maxSize = 500;
	foreach ($images as $row)
	{ 
		$size = 10*($row->size_x/$maxSize);
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
		<label>Konstnär:</label>
		<input type='text' name='artist".$column."' value='".htmlentities($row -> artist)."' />
    	<label>Titel:</label>
		<input type='text' name='imgname".$column."' value='".htmlentities($row -> imgname)."' />
    	<label>Typ:</label>
		<input type='text' name='type".$column."' value='' />
    	<label>Tröskelvärde:</label>
		<input type='range' name='threshold".$column."' min='1' max='10' value='".$row -> thresh."' />
		<label>Storlek:</label>
		<select type='text' name='size".$column."' value='".htmlentities($size)."' >   
		<optgroup label='Vald'></optgroup>
		<option value='".htmlentities($size)."'> ".htmlentities($size)." </option>
		<optgroup label='----------'></optgroup>
		<option value='1'>1 </option>
		<option value='2'> 2 </option>
		<option value='3'> 3 </option>
		<option value='4'> 4 </option>
		<option value='5'> 5 </option>
		<option value='6'> 6 </option>
		<option value='7'> 7 </option>
		<option value='8'> 8 </option>
		<option value='9'> 9 </option>
		<option value='10'> 10 </option>
		</select>
		<label>Animation:</label>
		<select type='text' name='animation".$column."'> 
		<optgroup label='Vald'></optgroup>
		<option value='".$animation_billboard[$column][0]->animation_id."'>".$animation_billboard[$column][0]->name."</option>
		<optgroup label='----------'></optgroup>

		";		
		foreach($animations as $animation)
		{
			echo  "
			<option value='".$animation->id."'> ".$animation->name." </option> ";
		}
		echo "</select>
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
	<input class="styledbutton" type="submit" value="Gå vidare" name="next">
</div>
</form>
</div>		