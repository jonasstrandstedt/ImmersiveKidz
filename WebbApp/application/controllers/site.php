<?php
/*
* @brief    The site controller, loads the site and all views.
*
* @details  index(), function that runs the upload() function from the startpage.
*			upload(), function for uploading images to the server and save them in the database.
*			add_info($date = NULL, $group = NULL), loads the content_edit view if date and group is set, else it loads the sub_info view.
*			download_info($date = NULL, $group = NULL), loads the sub_download view if date and group is set, else it loads the content_download view.
*			about(), loads the about view.
*
* @author   Emil Lindström, emili250@student.liu.se
* @author   Viktor Fröberg, vikfr292@student.liu.se
* @author   Gabriella Ivarsson gabiv132
* @date     December 18, 2012
* @version  3.2 (bugfixes)
*    
*/
if ( ! defined('BASEPATH')) exit('No direct script access allowed');
class Site extends CI_Controller 
{	
	/**
	 * @details index(): Sets the start function (startpage)
	 *
	 * @return void
	 */ 
	public function index()
	{
		$this->upload(); // Sets the start to the upload function
	}
	

	/**
	 * @details constructor, loads the form and url-helper
	 *
	 * @return void
	 */ 
	function __construct()
	{
		parent::__construct();
		$this->load->helper(array('form', 'url'));
	}
	 /**
	 * upload(): Uploads images(illustrations) to the server and add them to the database.
	 * Librarys: upload, MY_upload, ProcessImage
	 * Models: Tables_model
	 * Views: site_header, site_nav, content_create, upload_form, site_footer
	 *
	 * @return void
	 */ 
	function upload()
	{	
		$this->load->view("site_header");
		$this->load->view("site_nav");
		$contentCreate = array(
			"group" => "",
			"date" => ""
			);
		$this->load->view("content_create", $contentCreate);

		//If no upload folder exists, create it.
        if(!is_dir("./uploads")){
            mkdir("./uploads", 0777);
        }

		// Config-file for the upload library.
		$config['upload_path'] = './uploads/';
		$config['allowed_types'] = 'gif|jpg|png|jpeg';
		$config['max_size']	= '0';
		$config['max_width']  = '10000';
		$config['max_height']  = '10000';
		
		// loads the upload library with the config-file.
		$this->load->library('upload', $config);
		// Loads the Images_model model, to access the database functions.
		$this->load->model("Tables_model");
		// get an array of all the worlds.
		$info = $this->Tables_model->get_all_worlds();
		// Makes an array of the array, so that the upload_form view gets an array as variabel.
		$data = array(
			"worlds" => $info,
			"error" => ""
			);

		$group = "";
		$date = "";

		if(isset($_POST['submit'])){
			$group = $_POST['group'];
			$date = $_POST['date'];
		}
		
		$ans = $this->Tables_model->get_group_id($date, $group);
		
		// checks if a group exists.
		if(!empty($ans)){ 
			$data = array(
			"worlds" => $info,
			"error" => "Fel: Gruppen \"$group\" finns redan datumet $date, välj ett annat namn."
			);
			$this->load->view('upload_form', $data);
		}else{
		// Runs the do_multi_upload() function, if the function cant be run, load the upload_form view
		if ( !$this->upload->do_multi_upload())
		{
			$error = array('error' => $this->upload->display_errors());
			$this->load->view('upload_form', $data);
		}
		// if the user has submited data from the form.
		else if(isset($_POST['submit']))
		{	
			$group = ($_POST['group']); // Group name
			//echo $group;
			$date = $_POST['date']; // The date for this group
			$world = $_POST['world']; // The chosen world

			// If the user has not added a group-name
			if($group == NULL || $group == ''){
				$data = array(
					"worlds" => $info,
					"error" => "Fel: Du måste ange ett gruppnamn"
			);
			// Load upload_form-view
				$this->load->view('upload_form', $data);
			
			// checks if the user has added a date.
			}else if($date == NULL || $date == ''){
				$data = array(
					"worlds" => $info,
					"error" => "Fel: Du måste ange ett datum"
			);
			// Load upload_form-view
				$this->load->view('upload_form', $data);
			} else{
			// add the group to the database.
 			$this->Tables_model->add_group($group, $date, $world);

			$data = array('upload_data' => $this->upload->get_multi_upload()); // Gets all the url's ect from the upload function.
			$this->load->library('ProcessImage'); // loads  the ProcessImage library.
			$imagesIn = array(); // Array for all the uploaded images.
			for($i = 0; $i < count($data['upload_data']); $i++)// Loop for all images.
			{ 
				array_push($imagesIn, "uploads/".$data['upload_data'][$i]['file_name']); // Add an image to the array.
			}

			$imagesOut = $this->processimage->findDrawing($imagesIn, "uploads"); // Gets an new array with all the processed images. 
			$maxSize = 500;
			for($i = 0; $i < count($imagesIn); $i++) // Loop for all images.
			{	
				$fileurl = $imagesIn[$i]; // Save the url of the original image
				$fileouturl = $imagesOut[$i]; // save the url of the processed image.
				$scalexy = getimagesize($fileouturl)[0] / getimagesize($fileouturl)[1]; 
				$size_x = $maxSize*(5/10);
				$size_y = round($size_x*$scalexy,2);
				$billboard_id_vec = $this->Tables_model->add_billboard($fileouturl, $size_x,$size_y);
				$billboard_id = $billboard_id_vec[0] -> id;
				$group_id = $this->Tables_model->get_group_id($date, $group);
				$this->Tables_model->add_illustration("","", $fileurl,"", $billboard_id, $group_id[0]-> id, ""); // adds the information to the database.
				$this->Tables_model->add_animation_to_billboard("1", $billboard_id);// updates the database for the specific image.
			}
			echo "<script>window.location.href = 'add_information/".$date."/".urlencode($group)."';</script>"; // Javascript, loads the add_information view with the variables $date and $group

		}
	}
}
		$this->load->view("site_footer"); // Finally, add the footer.

	}
	 /**
	 * add_information($date = NULL , $group = NULL): Adds information for all the images to the database.
	 * Librarys:
	 * Models: Tables_model
	 * Views: site_header, site_nav, content_edit, sub_info, site_footer
	 * @param  string	$date		The date
	 * @param  string	$group		The group
	 *	
	 * @return void
	 */ 
	function add_information($date = NULL , $group = NULL)
	{	
		$this->load->view("site_header");
		$this->load->view("site_nav");
		$contentCreate = array(
			"group" =>$group,
			"date" => $date
			);
		$this->load->view("content_create", $contentCreate);
		// Loads the Images_model model, to access the database functions.
		$this->load->model("Tables_model");
		$maxSize = 500;
		if(isset($_POST['delete'])){ //if the user pressed a deletebutton
			
			$group_id = $_POST['group_id']; // Använd istället för name och date.
			$group = $this->Tables_model->get_group($group_id);
			$counter = 0; // count the number of images.

			$idArray = $this->Tables_model->get_all_illustration_id_and_imgurl_from_group($group_id); // an array with all the id's in the group
			foreach ($idArray as $id) 
			{	
				$billboard_id = $this->Tables_model->get_billboard_id_from_illustration($id -> id);
				if($counter == $_POST['delete']) //if the image should be deleted	
				{
					$this->Tables_model->remove_illustration($id->id);
					$this->Tables_model->remove_billboard($billboard_id[0]->billboard_id);
				}
				else //save the filled data
				{
					$artist = $_POST['artist'.$counter]; // gets the specific form for this image. ex: artist0, artist1.
					$imgname = $_POST['imgname'.$counter]; // gets the speficic imgname for this image. ex: imgname0, imgname1
					// Lägg till för type.
					$story = $_POST['story'.$counter];	// gets the specific story for this image. ex: story0, story1
					//$soundurl = $_POST['soundurl'.$counter];
					$soundurl = "";
					$threshold = $_POST['threshold'.$counter];
					$this->Tables_model->update_illustration($id ->id, $artist, $imgname,"", $soundurl, $story,$threshold); // updates the database for the specific image.
					$this->Tables_model->update_billboard_image($billboard_id[0]->billboard_id, '', $threshold);
					$size = $_POST['size'.$counter]; // gets the specific size
					$scalexy = getimagesize($id->imgurl)[0] / getimagesize($id->imgurl)[1]; 
					$size_x = $maxSize*($size/10);
					$size_y = $size_x*$scalexy;
					$this->Tables_model->update_billboard_size($billboard_id[0]->billboard_id, $size_x, $size_y);
					$animation = $_POST['animation'.$counter]; // gets the specific animation
					$this->Tables_model->update_animation_to_billboard($animation, $billboard_id[0]->billboard_id);// updates the database for the specific image.
				}
				$counter ++; 
			}
			$images = $this->Tables_model->get_all_illustrations_billboards_from_group($group_id); // Get all images from a specific group and date.
			$group_id_array = array(
				"group_id" => $group_id);
			$data = array( // Makes an array of the array, so that the sub_info view gets an array as variabel.
			"images" => $images
						);

			if( sizeof($idArray) == 1 ) //if its only 1 image left before delete
			{
				$info = $this->Tables_model->get_all_groups(); // gets an array of all the groups.
				$data = array(	// Makes an array of the array, so that the content_edit view gets an array as variabel.
				"info" => $info);
				$this->load->view("content_edit", $data); // loads the content_edit view, where the user can chose a group to edit.
			}else
			{
				echo "<script>window.location.href = 'add_information/".$group[0] -> date."/".urlencode($group[0] -> name)."';</script>"; // Javascript, loads the add_information view with the variables $date and $group		
			}
		}else if(isset($_POST['rotateplus'])){
			
			$group_id = $_POST['group_id']; // Använd istället för name och date.
			//print_r($group_id);
			$group = $this->Tables_model->get_group($group_id);
			$counter = 0; // count the number of images.
			$idArray = $this->Tables_model->get_all_illustration_id_and_imgurl_from_group($group_id); // an array with all the id's in the group
			foreach ($idArray as $id) 
			{
				if($counter == $_POST['rotateplus'])
				{ 
					$images = $this->Tables_model->get_all_illustrations_billboards_from_group($group_id);
					$imageUrl = $this->Tables_model->get_billboard_image($images[$counter] -> billboard_id);
					//echo $images[$counter]->imgouturl . "<br>";
					$filename = $imageUrl[0]->imgurl;
					$rotang = -90; // Rotation angle
					$source = imagecreatefrompng($filename) or die('Error opening file '.$filename);
					imagealphablending($source, false);
					imagesavealpha($source, true);

					$rotation = imagerotate($source, $rotang, imageColorAllocateAlpha($source, 0, 0, 0, 127));
					imagealphablending($rotation, false);
					imagesavealpha($rotation, true);

					// header('Content-type: image/png');
					imagepng($rotation,$filename);
					imagedestroy($source);
					imagedestroy($rotation);
					
					$artist = $_POST['artist'.$counter]; // gets the specific form for this image. ex: artist0, artist1.
					$imgname = $_POST['imgname'.$counter]; // gets the speficic imgname for this image. ex: imgname0, imgname1
					// Lägg till för type.
					$story = $_POST['story'.$counter];	// gets the specific story for this image. ex: story0, story1
					//$soundurl = $_POST['soundurl'.$counter];
					$threshold = $_POST['threshold'.$counter];
					$soundurl = "";
					$this->Tables_model->update_illustration($id ->id, $artist, $imgname,"", $soundurl, $story,$threshold); // updates the database for the specific image.
					$billboard_id = $this->Tables_model->get_billboard_id_from_illustration($id -> id);
					$this->Tables_model->update_billboard_image($billboard_id[0]->billboard_id, '', $threshold);
					$size = $_POST['size'.$counter]; // gets the specific size
					$scalexy = getimagesize($id->imgurl)[0] / getimagesize($id->imgurl)[1]; 
					$size_x = $maxSize*($size/10);
					$size_y = $size_x*$scalexy;
					$this->Tables_model->update_billboard_size($billboard_id[0]->billboard_id, $size_x, $size_y);
					$animation = $_POST['animation'.$counter]; // gets the specific animation
					$this->Tables_model->update_animation_to_billboard($animation, $billboard_id[0]->billboard_id);// updates the database for the specific image.
				}	
				else //save the filled data
				{
					$artist = $_POST['artist'.$counter]; // gets the specific form for this image. ex: artist0, artist1.
					$imgname = $_POST['imgname'.$counter]; // gets the speficic imgname for this image. ex: imgname0, imgname1
					// Lägg till för type.
					$story = $_POST['story'.$counter];	// gets the specific story for this image. ex: story0, story1
					//$soundurl = $_POST['soundurl'.$counter];
					$threshold = $_POST['threshold'.$counter];
					$soundurl = "";
					$this->Tables_model->update_illustration($id ->id, $artist, $imgname,"", $soundurl, $story, $threshold); // updates the database for the specific image.
					$billboard_id = $this->Tables_model->get_billboard_id_from_illustration($id -> id);
					$this->Tables_model->update_billboard_image($billboard_id[0]->billboard_id, '', $threshold);
					$size = $_POST['size'.$counter]; // gets the specific size
					$scalexy = getimagesize($id->imgurl)[0] / getimagesize($id->imgurl)[1]; 
					$size_x = $maxSize*($size/10);
					$size_y = $size_x*$scalexy;
					$this->Tables_model->update_billboard_size($billboard_id[0]->billboard_id, $size_x, $size_y);
					$animation = $_POST['animation'.$counter]; // gets the specific animation
					$this->Tables_model->update_animation_to_billboard($animation, $billboard_id[0]->billboard_id);// updates the database for the specific image.
				}
				$counter ++; 
			}
			echo "<script>window.location.href = 'add_information/".$group[0] -> date."/".urlencode($group[0] -> name)."';</script>"; // Javascript, loads the add_information view with the variables $date and $group		
			
		}else if(isset($_POST['rotateminus'])){

			$group_id = $_POST['group_id']; // Använd istället för name och date.
			
			$group = $this->Tables_model->get_group($group_id);
			$counter = 0; // count the number of images.
			$idArray = $this->Tables_model->get_all_illustration_id_and_imgurl_from_group($group_id); // an array with all the id's in the group
			foreach ($idArray as $id) 
			{
				if($counter == $_POST['rotateminus'])
				{ 
					$images = $this->Tables_model->get_all_illustrations_billboards_from_group($group_id);
					$imageUrl = $this->Tables_model->get_billboard_image($images[$counter] -> billboard_id);
					//echo $images[$counter]->imgouturl . "<br>";
					$filename = $imageUrl[0]->imgurl;
					$rotang = 90; // Rotation angle
					$source = imagecreatefrompng($filename) or die('Error opening file '.$filename);
					imagealphablending($source, false);
					imagesavealpha($source, true);

					$rotation = imagerotate($source, $rotang, imageColorAllocateAlpha($source, 0, 0, 0, 127));
					imagealphablending($rotation, false);
					imagesavealpha($rotation, true);

					// header('Content-type: image/png');
					imagepng($rotation,$filename);
					imagedestroy($source);
					imagedestroy($rotation);
					
					$artist = $_POST['artist'.$counter]; // gets the specific form for this image. ex: artist0, artist1.
					$imgname = $_POST['imgname'.$counter]; // gets the speficic imgname for this image. ex: imgname0, imgname1
					// Lägg till för type.
					$story = $_POST['story'.$counter];	// gets the specific story for this image. ex: story0, story1
					//$soundurl = $_POST['soundurl'.$counter];
					$threshold = $_POST['threshold'.$counter];
					$soundurl = "";
					$this->Tables_model->update_illustration($id ->id, $artist, $imgname,"", $soundurl, $story,$threshold); // updates the database for the specific image.
					$billboard_id = $this->Tables_model->get_billboard_id_from_illustration($id -> id);
					$this->Tables_model->update_billboard_image($billboard_id[0]->billboard_id, '', $threshold);
					$size = $_POST['size'.$counter]; // gets the specific size
					$scalexy = getimagesize($id->imgurl)[0] / getimagesize($id->imgurl)[1]; 
					$size_x = $maxSize*($size/10);
					$size_y = $size_x*$scalexy;
					$this->Tables_model->update_billboard_size($billboard_id[0]->billboard_id, $size_x, $size_y);
					$animation = $_POST['animation'.$counter]; // gets the specific animation
					$this->Tables_model->update_animation_to_billboard($animation, $billboard_id[0]->billboard_id);// updates the database for the specific image.
				}	
				else //save the filled data
				{
					$artist = $_POST['artist'.$counter]; // gets the specific form for this image. ex: artist0, artist1.
					$imgname = $_POST['imgname'.$counter]; // gets the speficic imgname for this image. ex: imgname0, imgname1
					// Lägg till för type.
					$story = $_POST['story'.$counter];	// gets the specific story for this image. ex: story0, story1
					//$soundurl = $_POST['soundurl'.$counter];
					$threshold = $_POST['threshold'.$counter];
					$soundurl = "";
					$this->Tables_model->update_illustration($id ->id, $artist, $imgname,"", $soundurl, $story,$threshold); // updates the database for the specific image.
					$billboard_id = $this->Tables_model->get_billboard_id_from_illustration($id -> id);
					$this->Tables_model->update_billboard_image($billboard_id[0]->billboard_id, '', $threshold);
					$size = $_POST['size'.$counter]; // gets the specific size
					$scalexy = getimagesize($id->imgurl)[0] / getimagesize($id->imgurl)[1]; 
					$size_x = $maxSize*($size/10);
					$size_y = $size_x*$scalexy;
					$this->Tables_model->update_billboard_size($billboard_id[0]->billboard_id, $size_x, $size_y);
					$animation = $_POST['animation'.$counter]; // gets the specific animation
					$this->Tables_model->update_animation_to_billboard($animation, $billboard_id[0]->billboard_id);// updates the database for the specific image.
				}
				$counter ++; 
			}
			echo "<script>window.location.href = 'add_information/".$group[0] -> date."/".urlencode($group[0] -> name)."';</script>"; // Javascript, loads the add_information view with the variables $date and $group		
			
		
		}else if(!(isset($date) || isset($group)) && !isset($_POST['next']) && !isset($_POST['update'])){ // if the date or group is NULL, and the user has not submited
			$info = $this->Tables_model->get_all_groups(); // gets an array of all the groups.
			$data = array(	// Makes an array of the array, so that the content_edit view gets an array as variabel.
				"info" => $info);
			$this->load->view("content_edit", $data); // loads the content_edit view, where the user can chose a group to edit.

		}
		else if(isset($_POST['update'])){ // else if, update the images.
			// Config-file for the upload library.
			$config['upload_path'] = './uploads/';
			$config['allowed_types'] = 'gif|jpg|png|jpeg';
			$config['max_size']	= '0';
			$config['max_width']  = '10000';
			$config['max_height']  = '10000';

			$counter = 0; // count the number of images.
			$newImages = array();
			$group_id = $_POST['group_id'];
			$idArray = $this->Tables_model->get_all_illustration_id_and_imgurl_from_group($group_id); // an array with all the id's in the group
			$group = $this->Tables_model->get_group($group_id);
			$editId = array();
			$threshId = array();
			$thresholdValues = array();
			$newSound = array();
			//Get new info from form
			foreach ($idArray as $id) {
				if(isset($_FILES['imageurl'.$counter]['name']) && ($_FILES['imageurl'.$counter]['name']) != ''){//Change image
					$replaceimageurl = "uploads/" . $_FILES['imageurl'.$counter]['name'];
					array_push($newImages, 'imageurl'.$counter);
					array_push($editId, $id->id);
				}
				else{
					$replaceimageurl = "";
				}

				//Update threshold
				if($_POST['threshold'.$counter] != '5' && ($_POST['threshold'.$counter]) != ''){//Change image
					//exit($_POST['threshold'.$counter]);
					$threshvalue = $_POST['threshold'.$counter];
					array_push($thresholdValues, $_POST['threshold'.$counter]);
					array_push($threshId, $id->id);
				}
				else{
					$threshvalue = "5";
				}

				//sound
				if(isset($_FILES['soundurl'.$counter]['name']) && ($_FILES['soundurl'.$counter]['name']) != ''){// sound, file input
					$soundurl = "uploads/" . $_FILES['soundurl'.$counter]['name'];
					array_push($newSound, 'soundurl'.$counter);
				}
				else if(isset($_POST['soundurl'.$counter]) && ($_POST['soundurl'.$counter]) != ''){// sound, text input
					$soundurl = "uploads/" . $_POST['soundurl'.$counter];
					array_push($newSound, 'soundurl'.$counter);
				}
				else{
					$soundurl = "";
				}

				$artist = $_POST['artist'.$counter]; // gets the specific form for this image. ex: artist0, artist1.
				$imgname = $_POST['imgname'.$counter]; // gets the speficic imgname for this image. ex: imgname0, imgname1
				// Lägg till för type.
				$story = $_POST['story'.$counter];	// gets the specific story for this image. ex: story0, story1
				//exit(print_r($idArray));
				$this->Tables_model->update_illustration($id ->id, $artist, $imgname,$replaceimageurl, $soundurl, $story, intval($threshvalue));  // updates the database for the specific image.
				
				$billboard_id = $this->Tables_model->get_billboard_id_from_illustration($id -> id);
				$this->Tables_model->update_billboard_image($billboard_id[0]->billboard_id, '', $threshvalue);
				$size = $_POST['size'.$counter]; // gets the specific size
				$scalexy = getimagesize($id->imgurl)[0] / getimagesize($id->imgurl)[1]; 
				$size_x = $maxSize*($size/10);
				$size_y = $size_x*$scalexy;
				$this->Tables_model->update_billboard_size($billboard_id[0]->billboard_id, $size_x, $size_y);
				$animation = $_POST['animation'.$counter]; // gets the specific animation
				$this->Tables_model->update_animation_to_billboard($animation, $billboard_id[0]->billboard_id);// updates the database for the specific image.
				$counter++;
			}

			$configSound['upload_path'] = './uploads/';
			$configSound['allowed_types'] = 'wav|mp3';
			$configSound['max_size']	= '0';
			// loads the upload library with the config-file.
			$this->load->library('upload', $configSound);
			//upload new sound to database
			foreach ($newSound as $inputName) {
				$this->upload->do_multi_upload($inputName);
				$temp = $this->upload->get_multi_upload();
				print_r($this->upload->display_errors());
			}

			$data = array();
			//upload new data to database
			$config['upload_path'] = './uploads/';
			$config['allowed_types'] = 'gif|jpg|png|jpeg';
			$config['max_size']	= '0';
			$config['max_width']  = '10000';
			$config['max_height']  = '10000';

			$this->load->library('upload', $config);
			foreach ($newImages as $inputName) {
				$this->upload->do_multi_upload($inputName);
				$temp = $this->upload->get_multi_upload();
				array_push($data, $temp[0]);
			}
			
			$this->load->library('ProcessImage'); // loads  the ProcessImage library.
			$imagesIn = array(); // Array for all the uploaded images.
			$test = array();
			for($i = 0; $i < count($data); $i++)// Loop for all images.
			{ 
				array_push($imagesIn, "uploads/".$data[$i]['file_name']); // Add an image to the array.
			}

			$threshImagesIn = array();
			foreach ($threshId as $id) {
				$temp = $this->Tables_model->get_url_from_id($id);
				$temp = $temp[0];
				array_push($threshImagesIn, $temp->imgurl); // Add an image to the array.
			}
			
			$imagesOut = $this->processimage->findDrawing($imagesIn, "uploads"); // Gets an new array with all the processed images. 
			
			$threshImagesOut = array();
			$i = 0;
			foreach ($thresholdValues as $value) {
				$out = $this->processimage->findDrawing(array($threshImagesIn[$i]), "uploads", $value);
				$out = $out[0];
				array_push($threshImagesOut, $out); // Gets an new array with all the processed images. 
				$i++;
			}

			for($i = 0; $i < count($imagesIn); $i++) // Loop for all images.
			{	
				$id = $editId[$i];

				$fileurl = $imagesIn[$i]; // Save the url of the original image
				//exit($fileurl . $check[$fileurl]);
				$fileouturl = $imagesOut[$i]; // save the url of the processed image.
				$billboard_id = $this->Tables_model->get_billboard_id_from_illustration($id);
				$this->Tables_model->update_billboard_image($billboard_id[0]-> billboard_id, $fileouturl, '');
			}

			for($i = 0; $i < count($threshImagesIn); $i++) // Loop for all images.
			{	
				$id = $threshId[$i];

				$fileurl = $threshImagesIn[$i]; // Save the url of the original image
				//exit($fileurl . $check[$fileurl]);
				$fileouturl = $threshImagesOut[$i]; // save the url of the processed image.
				$billboard_id = $this->Tables_model->get_billboard_id_from_illustration($id);
				$this->Tables_model->update_billboard_image($billboard_id[0]-> billboard_id, $fileouturl, '');
			}
			echo "<script>window.location.href = 'add_information/".$group[0] -> date."/".urlencode($group[0] -> name)."';</script>"; // Javascript, reload the page

			$this->load->view("site_footer"); // Finally, add the footer.
		}
		else if(!isset($_POST['next'])){ // else if, the user has not submited.
			$group_id = $this->Tables_model->get_group_id($date, urldecode($group));

			$images = $this->Tables_model->get_all_illustrations_billboards_from_group($group_id[0] -> id); // Get all images from a specific group and date.
			$imageID = $this->Tables_model->get_all_illustration_id_from_group($group_id[0] -> id); // Get all images from a specific group and date.
			$animations = $this->Tables_model->get_animation();
			$outImagesArray = array();
			$animation_billboardArray = array();
			foreach($images as $image){
				$billboard_id = $this->Tables_model->get_billboard_id_from_illustration($imageID[0]->id);
				// echo $image->id . "<br>";
				// print_r($billboard_id[0]->billboard_id);
				$animation_billboard = $this->Tables_model->get_animations_from_billboard_animation($billboard_id[0]->billboard_id);
				$billboard_image = $this->Tables_model->get_billboard_image($image -> id);
				array_push($animation_billboardArray, $animation_billboard);
				array_push($outImagesArray, $billboard_image[0] -> imgurl);
			}

			$data = array( // Makes an array of the array, so that the sub_info view gets an array as variabel.
				"images" => $images,
				"group_id" => $group_id,
				"outImages" => $outImagesArray,
				"animations" => $animations,
				"animation_billboard" => $animation_billboardArray
						);

			$this->load->view('sub_info', $data); // Loads the sub_info view, where the user can add information for all the images.
		}
		else{ // isset($_POST['next']) Submit form
			
			$counter = 0; // count the number of images.
			$group_id = $_POST['group_id'];
			$group = $this->Tables_model->get_group($group_id);

			$idArray = $this->Tables_model->get_all_illustration_id_and_imgurl_from_group($group_id); // an array with all the id's in the group
			$newSound = array();
			foreach ($idArray as $id) {
				if(isset($_FILES['soundurl'.$counter]['name']) && ($_FILES['soundurl'.$counter]['name']) != ''){// sound, file input
					$soundurl = "uploads/" . $_FILES['soundurl'.$counter]['name'];
					array_push($newSound, 'soundurl'.$counter);
				}
				else if(isset($_POST['soundurl'.$counter]) && ($_POST['soundurl'.$counter]) != ''){// sound, text input
					$soundurl = "uploads/" . $_POST['soundurl'.$counter];
					array_push($newSound, 'soundurl'.$counter);
				}
				else{
					$soundurl = "";
				}

				$artist = $_POST['artist'.$counter]; // gets the specific form for this image. ex: artist0, artist1.
				$imgname = $_POST['imgname'.$counter]; // gets the speficic imgname for this image. ex: imgname0, imgname1
				// Lägg till för type.
				$story = $_POST['story'.$counter];	// gets the specific story for this image. ex: story0, story1
				//$soundurl = $_FILES['soundurl'.$counter]['name'];
				$this->Tables_model->update_illustration($id ->id, $artist, $imgname, "", $soundurl, $story);// updates the database for the specific image.
				$billboard_id = $this->Tables_model->get_billboard_id_from_illustration($id -> id);
				$size = $_POST['size'.$counter]; // gets the specific size
				$scalexy = getimagesize($id->imgurl)[0] / getimagesize($id->imgurl)[1]; 
				$size_x = $maxSize*($size/10);
				$size_y = $size_x*$scalexy;
				$this->Tables_model->update_billboard_size($billboard_id[0]->billboard_id, $size_x, $size_y);
				$animation = $_POST['animation'.$counter]; // gets the specific animation
				$this->Tables_model->update_animation_to_billboard($animation, $billboard_id[0]->billboard_id);// updates the database for the specific image.
				
				$counter ++; // 
			}
			// loads the upload library with the config-file.
			$configSound['upload_path'] = './uploads/';
			$configSound['allowed_types'] = 'wav|mp3';
			$configSound['max_size']	= '0';
			$this->load->library('upload', $configSound);
			//upload new data to database
			foreach ($newSound as $inputName) {
				$this->upload->do_multi_upload($inputName);
				$temp = $this->upload->get_multi_upload();
			}

			echo "<script>window.location.href = 'add_coordinates/".$group[0] -> date."/". urlencode($group[0] -> name)."';</script>";// Javascript, loads the add_coordinates view with the variable $group_id
			
		}
		$this->load->view("site_footer"); // Finally, add the footer.
		
	}
	 /**
	 * download_info($date = NULL, $group = NULL): downloads a zip of all the information from a specific group.
	 * Librarys:
	 * Models: Tables_model
	 * Views: site_header, site_nav, content_download, sub_download, site_footer
	 * @param  string	$date		The date
	 * @param  string	$group		The group
	 *	
	 */ 

	function download_info($date = NULL, $group = NULL){
		$this->load->view("site_header");
		$this->load->view("site_nav");
		$contentCreate = array(
			"group" =>$group,
			"date" => $date
			);
		$this->load->view("content_create", $contentCreate);
		$this->load->model("Tables_model");
		$this->load->model("Create_xml_model");

		if(!(isset($date) || isset($group)) && !isset($_POST['download'])){ // if the date or group is NULL, and the user has not submited
			$info = $this->Tables_model->get_all_groups();	// gets an array of all the groups.
			
			$data = array( // Makes an array of the array, so that the content_download view gets an array as variabel.
				"info" => $info);
			$this->load->view("content_download", $data); // loads the content_download view, where the user can chose a group to download.
		}
		elseif(!isset($_POST['download'])){ // else if, the user has not submited.
		
		$data = array( // Makes an array of the array, so that the sub_download view gets an array as variabel.
				"group" => $group,
				"date" => $date
				);

		$this->load->view("sub_download", $data); // loads the sub_download view, where the user can download a zip.
		}else{// isset($_POST['download'])
			$group_id = $this->Tables_model->get_group_id($date, urldecode($group));
			$world_id_array = $this->Tables_model->get_group_world($group_id[0] -> id);
			$filename = $group."_".$date.".zip"; // Name of the zip-file to create.
			$images = $this->Tables_model->get_all_illustrations_from_group($group_id[0] -> id); // Get all images from a specific group and date.
			$billboardimages = $this->Tables_model->get_billboards_from_billboard_world($world_id_array[0] -> world_id); 
			$this->zip->clear_data(); // clear all data in the zip, just in case ;)
			foreach ($billboardimages as $bimage) {
				$pathimg = $bimage->imgurl; // save the path to the image on the server.
				$newImgpath = "uploads" . substr($pathimg, strrpos($pathimg, "/"));//find name without folder
				copy($pathimg, $newImgpath);//copy sound to folder
				$this->zip->read_file($newImgpath);
			}

			//add all mask textures to zip
			$maskurl = $this->Tables_model->get_mask_from_group_id($group_id[0] -> id); 
			foreach ($maskurl as $mask) {
				$this->zip->read_file($mask->textureurl, TRUE);
			}

			//add model textures to zip
			$modelurl = $this->Tables_model->get_model_from_group_id($group_id[0] -> id);
			foreach ($modelurl as $model) { 
				$this->zip->read_file($model->textureurl, TRUE);
				$this->zip->read_file($model->obj_fileurl, TRUE);
			}

			//add plane texture to zip
			$planeurl = $this->Tables_model->get_plane_from_group_id($group_id[0] -> id); 
			foreach ($planeurl as $plane) { 
				$this->zip->read_file($plane->textureurl, TRUE);
			}

			

			//add illustrations, billboards and sound to zip
			foreach ($images as $row){ // For all images
				$billboard_id = $this->Tables_model->get_billboard_id_from_illustration($row -> id);
				$imgouturl = $this->Tables_model->get_billboard_image($billboard_id[0] -> billboard_id); 
				$soundurl = $this->Tables_model->get_illustration_sound($billboard_id[0] -> billboard_id); 
				$pathimg = $imgouturl[0] -> imgurl; // save the path to the image on the server.
				$newImgpath = "uploads" . substr($pathimg, strrpos($pathimg, "/"));//find name without folder
				if($soundurl[0] -> soundurl != ''){ //if there is a sound
					$pathsound = $soundurl[0] -> soundurl; // save the path to the image on the server.
					$newSoundpath = "uploads" . substr($pathsound, strrpos($pathsound, "/"));//find name without folder
					copy($pathsound, $newSoundpath);//copy sound to  folder
					$this->zip->read_file($newSoundpath);
				}
				copy($pathimg, $newImgpath);//copy sound to folder
				$this->zip->read_file($newImgpath); // add the image to the zipfile. TRUE makes sure that the map structure remains.
				
			}

			$world = $this->Tables_model->get_world($world_id_array[0] -> world_id);
			$plane = $this->Tables_model->get_plane_from_world_id($world[0]->id);
			$model = $this->Tables_model->get_model_from_world_id($world[0]->id);
			$map = $this->Tables_model->get_map_from_world_id($world[0]->id);
			$mask = $this->Tables_model->get_masks_from_map_id($map[0]->id);
			$group = $this->Tables_model->get_group_from_world_id($world[0]->id);
			$billboard_world = $this->Tables_model->get_billboard_from_billboard_world($world[0]->id);
			
			$billboard = $this->Tables_model->get_billboard_from_illustrations($group[0] -> id);
			$animation = $this->Tables_model->get_animation();
			$billboard_animation = $this->Tables_model->get_billboard_animation();
			$model_world = $this->Tables_model->get_model_world($world[0]->id);

			//Create xml file using the world and images
			$xml_url = $this->Create_xml_model->get_xml_file($world[0], $images, $plane, $model, $map[0], $mask, $group, $billboard_world, $billboard, $animation, $billboard_animation, $model_world);


			$this->zip->read_file($xml_url);
			$this->zip->download($filename); // Makes the user download the zip-file
		}
		$this->load->view("site_footer"); // Finally, add the footer.
		
	}
	
	 /**
	 * add_world_and_objects(): add a new world with billboards.
	 * Librarys: upload, MY_upload, ProcessImage
	 * Models: Tables_model
	 * Views: site_header, site_nav, content_create_world, sub_addworldandobjects, site_footer
	 *	
	 * @return void
	 */ 
	function add_world_and_objects()
	{
		$this->load->view("site_header");
		$this->load->view("site_nav");
		
		$data = array(
			"error" => "");

		$contentCreate = array(
			"world_name" => "");

		$this->load->view("content_create_world", $contentCreate);
		
		// Config-file for the upload library.
		$config['upload_path'] = './uploads/';
		$config['allowed_types'] = 'gif|jpg|png|jpeg';
		$config['max_size']	= '0';
		$config['max_width']  = '10000';
		$config['max_height']  = '10000';
		
		// loads the upload library with the config-file.
		$this->load->library('upload', $config);
		
		// Loads the Images_model model, to access the database functions.
		$this->load->model("Tables_model");
		

		$world_name = "";
		if(isset($_POST['submitworld'])){
			$world_name = $_POST['world'];
		}
		$ans = $this->Tables_model->get_world_by_name($world_name);
		
		// Runs the do_multi_upload() function, if the function cant be run, load the upload_form view
		if(!empty($ans)){
			$data = array(
			"error" => "Fel: $world_name finns redan, välj ett annat namn."
			);
			$this->load->view('sub_addworldandobjects', $data);
		}else{


		if(isset($_POST['submitworld']) && $_FILES['uploadObject']['error'][0] == 4) //if user didnt upload objects when submited world
		{
			if($world_name == NULL || $world_name == ''){
				$data = array(
					"error" => "Fel: Du måste ange ett namn på världen."
				);
			$this->load->view('sub_addworldandobjects', $data);
			}else{
				$this->Tables_model->add_world($world_name , NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, "", "", "", "", "", "", "");
				echo "<script>window.location.href = 'add_plane/".urlencode($world_name)."';</script>"; // Javascript, loads the add_plane view with the variable $world_name
			}
		}
		else if ( ! $this->upload->do_multi_upload("uploadObject")) //if upload didnt work
		{	
			$error = array('error' => $this->upload->display_errors());
			$data = array(
				"error" =>"");
			$this->load->view('sub_addworldandobjects', $data);
		}
		else if(isset($_POST['submitworld'])) // if the user has submited the world
		{	
			$world_name= $_POST['world'];
			if($world_name == NULL || $world_name == ''){
				$data = array(
					"error" => "Fel: Du måste ange ett namn på världen."
				);
				$this->load->view('sub_addworldandobjects', $data);
			}else{
			
 			$this->Tables_model->add_world($world_name , NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, "", "", "", "", "", "", "");
			$world = $this->Tables_model->get_world_by_name($world_name);
			$world_id = $world[0]->id;			
			
			$data = array('upload_data' => $this->upload->get_multi_upload("uploadObject")); // Gets all the url's ect from the upload function.
			$this->load->library('ProcessImage'); // loads  the ProcessImage library.
			$imagesIn = array(); // Array for all the uploaded images.
			for($i = 0; $i < count($data['upload_data']); $i++)// Loop for all images.
			{ 
				array_push($imagesIn, "uploads/".$data['upload_data'][$i]['file_name']); // Add an image to the array.
			}

			$imagesOut = $this->processimage->findDrawing($imagesIn, "uploads"); // Gets an new array with all the processed images. 
			$maxSize = 500;
			for($i = 0; $i < count($imagesIn); $i++) // Loop for all images.
			{	
				$fileurl = $imagesIn[$i]; // Save the url of the original image
				$fileouturl = $imagesOut[$i]; // save the url of the processed image.
				$scalexy = getimagesize($fileouturl)[0] / getimagesize($fileouturl)[1]; 
				$size_x = $maxSize*(5/10);
				$size_y = round($size_x*$scalexy,2);
				$billboard_id_vec = $this->Tables_model->add_billboard($fileouturl, $size_x,$size_y);
				$billboard_id = $billboard_id_vec[0] -> id;
				$this->Tables_model->add_billboard_to_world($world_id, $billboard_id, "", "", "", "", "1", "", "normal");
				$this->Tables_model->add_animation_to_billboard("1", $billboard_id);// updates the database for the specific image.
			}
			echo "<script>window.location.href = 'add_object_information/".urlencode($world_name)."';</script>"; // Javascript, loads the add_object_information view with the variables $world_name
		}
	}
}
		$this->load->view("site_footer"); // Finally, add the footer.		
	}
	
	
	/**
	 * add_object_information(): edit the worlds billboards information
	 * Librarys: upload, MY_upload, ProcessImage
	 * Models: Tables_model
	 * Views: site_header, site_nav, content_create_world, sub_edit_world, site_footer
	 *	
	 * @param $world_name = NULL
	 * @return void
	 */ 
	function add_object_information($world_name = NULL)
	{
		$this->load->view("site_header");
		$this->load->view("site_nav");
		$contentCreate = array(
			"world_name" => $world_name);
		$this->load->view("content_create_world", $contentCreate);
		
		// Loads the Images_model model, to access the database functions.
		$this->load->model("Tables_model");		
		$maxSize = 500;
		if(isset($_POST['delete'])){ //if the user pressed a deletebutton
			
			$world_id = $_POST['world_id']; // Använd istället för name och date.
			$world = $this->Tables_model->get_world($world_id);
			$counter = 0; // count the number of images.

			$billboards = $this->Tables_model->get_billboards_from_billboard_world($world_id); // Get all billboards from a specific world.
			foreach ($billboards as $billboard) 
			{
				if($counter == $_POST['delete']) //if the image should be deleted	
				{
					 $this->Tables_model->remove_billboard_from_world($world_id,$billboard->billboard_id);
					$this->Tables_model->remove_billboard($billboard->billboard_id);
				}
				else //save the filled data
				{
					$quantity = $_POST['quantity'.$counter]; // gets the specific quantity for this billboard
					$type = $_POST['type'.$counter]; // gets the specific type for this billboard
					$size = $_POST['size'.$counter]; // gets the specific size
					$scalexy = getimagesize($billboard->imgurl)[0] / getimagesize($billboard->imgurl)[1]; 
					$size_x = $maxSize*($size/10);
					$size_y = $size_x*$scalexy;
					$animation = $_POST['animation'.$counter]; // gets the specific animation

					$threshold = $_POST['threshold'.$counter];
					$this->Tables_model->update_billboard_image($billboard->billboard_id, '', $threshold);


					$this->Tables_model->update_billboard_world($world_id, $billboard->billboard_id, $quantity, $type, $size_x, $size_y);// updates the database for the specific image.
					$this->Tables_model->update_animation_to_billboard($animation, $billboard->billboard_id);// updates the database for the specific image.
				}
				$counter ++; 
			}

			if( sizeof($billboards) == 1 ) //if its only 1 image left before delete
			{
				$info = $this->Tables_model->get_all_worlds(); // gets an array of all the groups.
				$data = array(	// Makes an array of the array, so that the content_edit view gets an array as variabel.
				"info" => $info);
				$this->load->view("content_edit_world", $data); // loads the content_edit view, where the user can chose a group to edit.
			}else
			{
				echo "<script>window.location.href = 'add_object_information/".urlencode($world[0] -> name)."';</script>"; // Javascript, loads the add_information view with the variables $date and $group		
			}
		}else if(isset($_POST['rotateplus'])){

			$world_id = $_POST['world_id']; 
			$world = $this->Tables_model->get_world($world_id);
			$counter = 0; // count the number of images.
			$billboards = $this->Tables_model->get_billboards_from_billboard_world($world_id); // Get all billboards from a specific world.
			foreach ($billboards as $billboard) 
			{
				if($counter == $_POST['rotateplus'])
				{ 
					$imageUrl = $this->Tables_model->get_billboard_image($billboards[$counter] -> billboard_id);
					$filename = $imageUrl[0]->imgurl;
					$rotang = -90; // Rotation angle
					$source = imagecreatefrompng($filename) or die('Error opening file '.$filename);
					imagealphablending($source, false);
					imagesavealpha($source, true);

					$rotation = imagerotate($source, $rotang, imageColorAllocateAlpha($source, 0, 0, 0, 127));
					imagealphablending($rotation, false);
					imagesavealpha($rotation, true);

					// header('Content-type: image/png');
					imagepng($rotation,$filename);
					imagedestroy($source);
					imagedestroy($rotation);
					
					$quantity = $_POST['quantity'.$counter]; // gets the specific quantity for this billboard
					$type = $_POST['type'.$counter]; // gets the specific type for this billboard
					$size = $_POST['size'.$counter]; // gets the specific size
					$scalexy = getimagesize($billboard->imgurl)[0] / getimagesize($billboard->imgurl)[1]; 
					$size_x = $maxSize*($size/10);
					$size_y = $size_x*$scalexy;
					$animation = $_POST['animation'.$counter]; // gets the specific animation

					$threshold = $_POST['threshold'.$counter];
					$this->Tables_model->update_billboard_image($billboard->billboard_id, '', $threshold);

					$this->Tables_model->update_billboard_world($world_id, $billboard->billboard_id, $quantity, $type, $size_x, $size_y);// updates the database for the specific image.
					$this->Tables_model->update_animation_to_billboard($animation, $billboard->billboard_id);// updates the database for the specific image.
				}	
				else //save the filled data
				{
					$quantity = $_POST['quantity'.$counter]; // gets the specific quantity for this billboard
					$type = $_POST['type'.$counter]; // gets the specific type for this billboard
					$size = $_POST['size'.$counter]; // gets the specific size
					$scalexy = getimagesize($billboard->imgurl)[0] / getimagesize($billboard->imgurl)[1]; 
					$size_x = $maxSize*($size/10);
					$size_y = $size_x*$scalexy;
					$animation = $_POST['animation'.$counter]; // gets the specific animation

					$threshold = $_POST['threshold'.$counter];
					$this->Tables_model->update_billboard_image($billboard->billboard_id, '', $threshold);

					$this->Tables_model->update_billboard_world($world_id, $billboard->billboard_id, $quantity, $type, $size_x, $size_y);// updates the database for the specific image.
					$this->Tables_model->update_animation_to_billboard($animation, $billboard->billboard_id);// updates the database for the specific image.
				}
				$counter ++; 
			}
			echo "<script>window.location.href = 'add_object_information/".urlencode($world[0] -> name)."';</script>"; // Javascript, loads the add_information view with the variables $date and $group		
			
		}else if(isset($_POST['rotateminus'])){

			$world_id = $_POST['world_id']; 
			$world = $this->Tables_model->get_world($world_id);
			$counter = 0; // count the number of images.
			$billboards = $this->Tables_model->get_billboards_from_billboard_world($world_id); // Get all billboards from a specific world.
			foreach ($billboards as $billboard) 
			{
				if($counter == $_POST['rotateminus'])
				{ 
					$imageUrl = $this->Tables_model->get_billboard_image($billboards[$counter] -> billboard_id);
					$filename = $imageUrl[0]->imgurl;
					$rotang = 90; // Rotation angle
					$source = imagecreatefrompng($filename) or die('Error opening file '.$filename);
					imagealphablending($source, false);
					imagesavealpha($source, true);

					$rotation = imagerotate($source, $rotang, imageColorAllocateAlpha($source, 0, 0, 0, 127));
					imagealphablending($rotation, false);
					imagesavealpha($rotation, true);

					// header('Content-type: image/png');
					imagepng($rotation,$filename);
					imagedestroy($source);
					imagedestroy($rotation);
					
					$quantity = $_POST['quantity'.$counter]; // gets the specific quantity for this billboard
					$type = $_POST['type'.$counter]; // gets the specific type for this billboard
					$size = $_POST['size'.$counter]; // gets the specific size
					$scalexy = getimagesize($billboard->imgurl)[0] / getimagesize($billboard->imgurl)[1]; 
					$size_x = $maxSize*($size/10);
					$size_y = $size_x*$scalexy;
					$animation = $_POST['animation'.$counter]; // gets the specific animation

					$threshold = $_POST['threshold'.$counter];
					$this->Tables_model->update_billboard_image($billboard->billboard_id, '', $threshold);

					$this->Tables_model->update_billboard_world($world_id, $billboard->billboard_id, $quantity, $type, $size_x, $size_y);// updates the database for the specific image.
					$this->Tables_model->update_animation_to_billboard($animation, $billboard->billboard_id);// updates the database for the specific image.
				}	
				else //save the filled data
				{
					$quantity = $_POST['quantity'.$counter]; // gets the specific quantity for this billboard
					$type = $_POST['type'.$counter]; // gets the specific type for this billboard
					$size = $_POST['size'.$counter]; // gets the specific size
					$scalexy = getimagesize($billboard->imgurl)[0] / getimagesize($billboard->imgurl)[1]; 
					$size_x = $maxSize*($size/10);
					$size_y = $size_x*$scalexy;
					$animation = $_POST['animation'.$counter]; // gets the specific animation

					$threshold = $_POST['threshold'.$counter];
					$this->Tables_model->update_billboard_image($billboard->billboard_id, '', $threshold);

					$this->Tables_model->update_billboard_world($world_id, $billboard->billboard_id, $quantity, $type, $size_x, $size_y);// updates the database for the specific image.
					$this->Tables_model->update_animation_to_billboard($animation, $billboard->billboard_id);// updates the database for the specific image.
				}
				$counter ++; 
			}
			echo "<script>window.location.href = 'add_object_information/".urlencode($world[0] -> name)."';</script>"; // Javascript, loads the add_information view with the variables $date and $group		
				
		}else if(!isset($world_name) && !isset($_POST['next']) && !isset($_POST['update'])) //if world name is not set and user didnt click the next or update button
		{
			$info = $this->Tables_model->get_all_worlds(); // gets an array of all the groups.
			$data = array(	// Makes an array of the array, so that the content_edit view gets an array as variabel.
			"info" => $info);
			$this->load->view("content_edit_world", $data); // loads the content_edit view, where the user can chose a group to edit.
		
		}
		else if(isset($_POST['update'])){ // else if, update the images.
			$world_id = $_POST['world_id']; 
			$world = $this->Tables_model->get_world($world_id);
			// Config-file for the upload library.
			$config['upload_path'] = './uploads/';
			$config['allowed_types'] = 'gif|jpg|png|jpeg';
			$config['max_size']	= '0';
			$config['max_width']  = '10000';
			$config['max_height']  = '10000';
			$counter = 0; // count the number of images.
			$newImages = array();
			$billboards = $this->Tables_model->get_billboards_from_billboard_world($world_id); // an array with all the id's in the group
			$editId = array();
			$threshId = array();
			$thresholdValues = array();
			$newSound = array();
			//Get new info from form
			$maxSize = 500;
			foreach ($billboards as $billboard) {
				//Update threshold
				if($_POST['threshold'.$counter] != '5' && ($_POST['threshold'.$counter]) != ''){//Change image
					//exit($_POST['threshold'.$counter]);
					$threshvalue = $_POST['threshold'.$counter];
					array_push($thresholdValues, $threshvalue);
					array_push($threshId, $billboard->billboard_id);
				}
				else{
					$threshvalue = "5";
				}
				//save filled values
				$this->Tables_model->update_billboard_image($billboard->billboard_id, "", intval($threshvalue));
				$quantity = $_POST['quantity'.$counter]; // gets the specific quantity for this billboard
				$type = $_POST['type'.$counter]; // gets the specific type for this billboard
				$size = $_POST['size'.$counter]; // gets the specific size
				$scalexy = getimagesize($billboard->imgurl)[0] / getimagesize($billboard->imgurl)[1]; 
				$size_x = $maxSize*($size/10);
				$size_y = $size_x*$scalexy;
				$animation = $_POST['animation'.$counter]; // gets the specific animation
				$this->Tables_model->update_billboard_world($world_id, $billboard->billboard_id, $quantity, $type, $size_x, $size_y);// updates the database for the specific image.
				$this->Tables_model->update_animation_to_billboard($animation, $billboard->billboard_id);// updates the database for the specific image.

				$counter++;
			}
			// loads the upload library with the config-file.
			$this->load->library('upload', $config);

			$data = array();
			
			$this->load->library('ProcessImage'); // loads  the ProcessImage library.

			$threshImagesIn = array();
			foreach ($threshId as $id) {
				$temp = $this->Tables_model->get_billboard_url_from_id($id);
				$temp = $temp[0];
				
				//recreate url for in image
				$inimg = $temp->imgurl;
				$inimg = substr($inimg, strrpos($inimg, "/")+1);
				$inimg = str_replace("out", "", $inimg);
				$length = strlen($inimg)-(strlen($inimg)-strrpos($inimg, "."));
				$inimg = substr($inimg, 0, $length);
				$inimg = "uploads/" . $inimg; //will give url like "uploads/flower"
				//find correct file ending
				if(file_exists($inimg.".jpg")){
					$inimg = $inimg.".jpg";
				}
				else if(file_exists($inimg.".jpeg")){
					$inimg = $inimg.".jpeg";
				}
				else if(file_exists($inimg.".png")){
					$inimg = $inimg.".png";
				}
				else if(file_exists($inimg.".gif")){
					$inimg = $inimg.".gif";
				}

				array_push($threshImagesIn, $inimg); // Add an image to the array.
			}
			$threshImagesOut = array();
			$i = 0;
			foreach ($thresholdValues as $value) {
				$out = $this->processimage->findDrawing(array($threshImagesIn[$i]), "uploads", $value);
				$out = $out[0];
				array_push($threshImagesOut, $out); // Gets an new array with all the processed images. 
				$i++;
			}
			for($i = 0; $i < count($threshImagesIn); $i++) // Loop for all images.
			{	
				$billboard_id = $threshId[$i];
				$fileurl = $threshImagesIn[$i]; // Save the url of the original image
				//exit($fileurl . $check[$fileurl]);
				$fileouturl = $threshImagesOut[$i]; // save the url of the processed image.
				$this->Tables_model->update_billboard_image($billboard_id, $fileouturl);
			}

			echo "<script>window.location.href = 'add_object_information/".urlencode($world[0] -> name)."';</script>"; // Javascript, reload the page


			$this->load->view("site_footer"); // Finally, add the footer.
		}
		else if(!isset($_POST['next'])) // if, the user has not submited.
		{ 		
			$world = $this->Tables_model->get_world_by_name(urldecode($world_name));
			$world_id = $world[0]->id;
			$billboards = $this->Tables_model->get_billboards_from_billboard_world($world_id); // Get all billboards from a specific world.
			$animations = $this->Tables_model->get_animation();
			$outImagesArray = array();
			$animation_billboardArray = array();
			foreach($billboards as $billboard)
			{
				$billboard_id = $billboard->billboard_id;
				$animation_billboard = $this->Tables_model->get_animations_from_billboard_animation($billboard_id);
				$billboard_image = $billboard->imgurl; 
				array_push($animation_billboardArray, $animation_billboard);
				array_push($outImagesArray, $billboard_image);
			}

			$data = array( // Makes an array of the array, so that the sub_info view gets an array as variabel.
				"billboards" => $billboards,
				"world_id" => $world_id,
				"outImages" => $outImagesArray,
				"animations" => $animations,
				"animation_billboard" => $animation_billboardArray
						);
			$this->load->view('sub_addobjectinformation', $data); // Loads the sub_addobjectinformation view, where the user can add information for all the images.
		}else{ // isset($_POST['next']) Submit form
			$counter = 0; // count the number of images.
			$world_id = $_POST['world_id'];	
			$world = $this->Tables_model->get_world($world_id);
			$world_name = $world[0]->name;
		
			$idArray = $this->Tables_model->get_billboards_from_billboard_world($world_id); // an array with all the id's in the group
			foreach ($idArray as $id) 
			{
				$quantity = $_POST['quantity'.$counter]; // gets the quantity from form.
				$type = $_POST['type'.$counter]; // gets the specific type
				$size = $_POST['size'.$counter]; // gets the specific size_x
				$scalexy = getimagesize($id->imgurl)[0] / getimagesize($id->imgurl)[1]; 
				$size_x = $maxSize*($size/10);
				$size_y = $size_x*$scalexy;
				$animation = $_POST['animation'.$counter]; // gets the specific animation
				$this->Tables_model->update_billboard_world($world_id, $id->billboard_id, $quantity, $type, $size_x, $size_y);// updates the database for the specific image.
				$this->Tables_model->update_animation_to_billboard($animation, $id->billboard_id);// updates the database for the specific image.
				$counter ++; 
			}
			echo "<script>window.location.href = 'add_plane/".urlencode($world_name)."';</script>"; // Javascript, loads the add_plane view with the variable $world_name
		}
		$this->load->view("site_footer"); // Finally, add the footer.
	}
	/**
	 * add_plane(): add a plane-map and mask to the world
	 * Librarys: upload, MY_upload, ProcessImage
	 * Models: Tables_model
	 * Views: site_header, site_nav, content_create_world, content_plane, site_footer
	 *	
	 * @param $world_name = NULL
	 * @return void
	 */ 
	function add_plane($world_name = NULL)
	{
		$this->load->view("site_header");
		$this->load->view("site_nav");
		$contentCreate = array(
			"world_name" => $world_name);

		$this->load->view("content_create_world", $contentCreate);
		
		$config['upload_path'] = './plane/';
		$config['allowed_types'] = 'gif|jpg|png';
		$config['max_size']	= '10000';
		$config['max_width']  = '2000';
		$config['max_height']  = '2000';
		
				
		// Loads the Images_model model, to access the database functions.
		$this->load->model("Tables_model");		
		// Loads the upload library with the config-file.
		$this->load->library('upload', $config);
		
		if(!isset($world_name) && !isset($_POST['submitplane'])) //list worlds
		{
			$info = $this->Tables_model->get_all_worlds(); // gets an array of all the groups.
			$data = array(	// Makes an array of the array, so that the content_edit view gets an array as variabel.
			"info" => $info);
			$this->load->view("content_plane", $data); // loads the content_edit view, where the user can chose a group to edit.
		
		}else if(!isset($_POST['submitplane'])) //if user didnt submited plane
		{	
			$world_name = urldecode($world_name);
			// echo $world_name;
			$world = $this->Tables_model->get_world_by_name($world_name);
			// print_r($world);
			// get an array of all the planes
			$info = $this->Tables_model->get_all_planes_from_maps();
			// Makes an array of the array, so that the sub_addplane view gets an array as variabel.
			$data = array(
			"planes" => $info,
			"world_id" => $world[0] -> id
			);
			$this->load->view("sub_addplane", $data);
			
		}else if(isset($_POST['submitplane']) && isset($_POST['plane']) && $_FILES['uploadPlane']['error'] == 4 && $_FILES['uploadMask']['error'] == 4 ) //if user submited and didnt upload file
		{	
			$plane_id = $_POST['plane'];
			$world_id = $_POST['world_id'];
			$map_id = $this->Tables_model->get_map_id_from_plane($plane_id);
			$this->Tables_model->update_map_id_world($map_id[0]->id,$world_id);
			echo "<script>window.location.href = '".base_url()."';</script>";
		}
		else if(isset($_POST['submitplane'])) //if user submited and uploaded file
		{
			if ( ! $this->upload->do_upload("uploadPlane")) //if upload didnt work
			{
				$error = array('error' => $this->upload->display_errors());
				print_r($error);
			}
			else //if upload did work
			{
				$data = array('upload_data' => $this->upload->data());
				$textureurl = "plane/".$data['upload_data']['file_name']; // url to texture
				$width = getimagesize($textureurl)[0];
				$height = getimagesize($textureurl)[1];
				$plane_id_vec = $this->Tables_model->add_plane($width ,$height, $textureurl, "", "", "", "", "", ""); //returns plane id
				$plane_id = $plane_id_vec[0] -> id;
				$world_id = $_POST['world_id'];
				
				//$this->Tables_model->add_plane_to_world($plane_id,$world_id);
				$map_id = $this->Tables_model->add_map("",$plane_id);
				$this->Tables_model->update_map_id_world($map_id[0]->id,$world_id);

				if ( ! $this->upload->do_upload("uploadMask")) //if upload didnt work
				{
					$error = array('error' => $this->upload->display_errors());
					print_r($error);
				}else //if upload did work
				{
					$dataMask = array('upload_data' => $this->upload->data());
					$maskurl = "plane/".$dataMask['upload_data']['file_name']; // url to texture
					$this->Tables_model->add_mask($maskurl, "", $map_id[0]->id);
				}
			}
			echo "<script>window.location.href = '".base_url()."';</script>";
		}
		$this->load->view("site_footer"); // Finally, add the footer.
	}
	

	

	
	/**
	 * instructions(): loads the instrunctons view.
	 * Models: 
	 * Views: site_header, site_nav, content_instructions, site_footer
	 *	
	 * @return void
	 */ 
	function instructions()
	{	
		$this->load->view("site_header");
		$this->load->view("site_nav");
		$this->load->view("content_instructions");
		$this->load->view("site_footer");
	}
	
	
	/**
	 * about(): information about the webapp
	 * Librarys:
	 * Models: 
	 * Views: site_header, site_nav, content_about, sub_download, site_footer
	 *	
	 * @return void
	 */ 
	function about()
	{
		$this->load->view("site_header");
		$this->load->view("site_nav");
		$this->load->view("content_about");
		$this->load->view("site_footer");
	}


	/**
	*
	* add_coordinates(): add coordinates to the illustrations
	* Librarys:
	* Models: Tables_model
	* Views: site_header, site_nav, content_about, sub_coord, site_footer
	* @return void
	*/
	function add_coordinates($date = NULL, $group = NULL)
	{	
		$this->load->view("site_header");
		$this->load->view("site_nav");
		$contentCreate = array(
			"group" =>$group,
			"date" => $date
			);
		$this->load->view("content_create", $contentCreate);
		$group = urldecode($group);
		$this->load->model("Tables_model");
		if(isset($_POST['submitcoord'])){
			$group_id = $_POST['group_id'];
			$group = $this->Tables_model->get_group($group_id);
			$illustrations = $this->Tables_model->get_all_illustration_id_from_group($group_id);
			for($i = 0; $i < sizeof($illustrations); $i++){
				$x_coord = $_POST['image'.$i.'_x'];
				$z_coord = $_POST['image'.$i.'_z'];

				$this->Tables_model->update_illustration_coordinates($illustrations[$i] -> id, $x_coord,"", $z_coord);

			}
			echo "<script>window.location.href = 'download_info/".$group[0] -> date."/". urlencode($group[0] -> name)."';</script>";// Javascript, loads the download_info view with the variables $date and $group

		}
		else if($date != NULL & $group != NULL ){
			$group_id = $this->Tables_model->get_group_id($date, $group);
			$group = $this->Tables_model->get_group($group_id[0]-> id);
			$illustrations = $this->Tables_model->get_all_illustrations_from_group($group_id[0]-> id);
			$world_id = $this->Tables_model->get_group_world($group_id[0]-> id);
			$world = $this->Tables_model->get_world($world_id[0] -> world_id);
			$map = $this->Tables_model->get_map($world[0]-> map_id);
			$plane = $this->Tables_model->get_plane($map[0] -> plane_id);
			$billboards = array();
			foreach ($illustrations as $image) {
				$billboard = $this->Tables_model->get_billboard_image($image -> billboard_id);
				array_push($billboards,$billboard[0]);
			}
			$data  = array(
				'world' => $world[0],
				'map' => $map[0],
				'plane' => $plane[0],
				'group' => $group[0],
				'illustrations' => $illustrations,
				'billboards' => $billboards
					);

			
			$this->load->view("sub_coord", $data);
		}
		else{ // Let the user choose group.
			$info = $this->Tables_model->get_all_groups();	// gets an array of all the groups.
			
			$data = array( // Makes an array of the array, so that the content_download view gets an array as variabel.
				"info" => $info);
			$this->load->view("content_coord", $data);
		}

		$this->load->view("site_footer");
	}
}