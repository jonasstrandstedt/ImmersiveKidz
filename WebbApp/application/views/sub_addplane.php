<?php
/*
* @brief    Upload image to use as plane or choose an existing one.
*
* @details  
*
* @author   Emil Lindström, emili250@student.liu.se
* @date     December 7, 2012
* @version  1.0
*/
?>
<div id="sub">
	<div class='uploadform'>
		<?php echo form_open_multipart('index.php/site/add_plane');
			echo "<input type='hidden' name='world_id' value='".$world_id."' />";
		?>	
		<div id="uploadPlane">
			<label for="uploadPlane">
				Välj ett plan
			</label>
			<input class="uploadMap" type="file" name="uploadPlane" size="20" />
		</div>
		<div id="uploadMask">
			<label for="uploadMask">
				Välj en mask
			</label>
			<input class="uploadMap" type="file" name="uploadMask" size="20" />
		<div id="plane">
				<label for="plane">
					Eller välj ett plan som redan finns
				</label>
				<select name="plane">
					<?php
					foreach ($planes as $plane)
					{ 
						echo "<option value='".$plane-> id."'>".$plane-> textureurl."</option>";
					}
					?>
				</select>
		</div>

			<div id="button">
				<input class="styledbutton" type="submit" name="submitplane" value="Lägg till planet" />
			</div>
		</form>
	</div>
</div>