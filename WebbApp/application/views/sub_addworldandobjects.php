<?php
/*
* @brief    Creates a new world and upload objects to use
*
* @details  
*
* @author   Emil Lindström, emili250@student.liu.se
* @date     December 7, 2012
* @version  1.0
*/
?>
<div id="sub">
	<?php if($error != ""){
		echo "<h3 id='error'> ".htmlentities($error)." </h3></br>";
	}?>
	<div class='uploadform'>
	<div class="textinfo"><p>Skapa din värld här. Ladda upp dina objekt som ska användas i världen, exempelvis blommor eller träd. Om du inte vill ha några objekt så skriver du bara in namnet på världen.</p></div>
		<?php echo form_open_multipart('index.php/site/add_world_and_objects');?>
			<input class="upload" type="file" name="uploadObject[]" size="20" multiple=""/>
			<div id="world">
				<label for="world">
					Världnamn
				</label>
				<input type="text" name="world" size="20"/>
			</div>

			<div id="button">
				<p class='max'>Max filstorlek 2MB.</p>
				<input class="styledbutton" type="submit" name="submitworld" value="Ladda upp bilderna" />
			</div>
		</form>
	</div>
</div>