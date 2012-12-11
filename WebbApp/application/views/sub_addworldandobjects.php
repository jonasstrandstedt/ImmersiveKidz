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
	<div class='uploadform'>
		<?php echo form_open_multipart('index.php/site/add_world_and_objects');?>
			<input class="upload" type="file" name="userfile[]" size="20" multiple=""/>
			<div id="world">
				<label for="world">
					Namnge din  värld
				</label>
				<input type="text" name="world" size="20"/>
			</div>

			<div id="button">
				<p>Max filstorlek 2MB.</p>
				<input class="styledbutton" type="submit" name="submitworld" value="Ladda upp bilderna" />
			</div>
		</form>
	</div>
</div>