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
* @date     November 21, 2012
* @version  2.1 (Added more comments...)
*    
*/
if ( ! defined('BASEPATH')) exit('No direct script access allowed');
class Site extends CI_Controller 
{	
	public function index()
	{
		$this->upload(); // Sets the startpage to the upload view.
	}
	

	
	function __construct()
	{
		parent::__construct();
		$this->load->helper(array('form', 'url'));
	}
	 /**
	 * upload(): Uploads images to the server and add them to the database.
	 * Librarys: upload, MY_upload, ProcessImage
	 * Models: Images_model
	 * Views: site_header, site_nav, content_create, upload_form, site_footer
	 *	
	 */ 
	function upload()
	{	
		$this->load->view("site_header");
		$this->load->view("site_nav");
		$this->load->view("content_create");

		//If no upload folder exists, create it.
        if(!is_dir("./uploads")){
            mkdir("./uploads", 0777);
        }

		// Config-file for the upload library.
		$config['upload_path'] = './uploads/';
		$config['allowed_types'] = 'gif|jpg|png';
		$config['max_size']	= '10000';
		$config['max_width']  = '10000';
		$config['max_height']  = '10000';
		
		// loads the upload library with the config-file.
		$this->load->library('upload', $config);
		// Loads the Images_model model, to access the database functions.
		$this->load->model("Images_model");
		// get an array of all the worlds.
		$info = $this->Images_model->get_all_worlds();
		// Makes an array of the array, so that the upload_form view gets an array as variabel.
		$data = array(
			"worlds" => $info
			);

		// Runs the do_multi_upload() function, if the function cant be run, load the upload_form view
		 if ( ! $this->upload->do_multi_upload())
		{
			$error = array('error' => $this->upload->display_errors());
			$this->load->view('upload_form', $data);
		}
		// if the user has submited data from the form.
		else if(isset($_POST['submit']))
		{	
			$group = $_POST['group']; // Group name
			$date = $_POST['date']; // The date for this group
			$world = $_POST['world']; // The chosen world
 
			$data = array('upload_data' => $this->upload->get_multi_upload()); // Gets all the url's ect from the upload function.
			$this->load->library('ProcessImage'); // loads  the ProcessImage library.
			$imagesIn = array(); // Array for all the uploaded images.
			for($i = 0; $i < count($data['upload_data']); $i++)// Loop for all images.
			{ 
				
				array_push($imagesIn, "uploads/".$data['upload_data'][$i]['file_name']); // Add an image to the array.
			}

			$imagesOut = $this->processimage->findDrawing($imagesIn, "uploads"); // Gets an new array with all the processed images. 

			for($i = 0; $i < count($imagesIn); $i++) // Loop for all images.
			{	
				$fileurl = $imagesIn[$i]; // Save the url of the original image
				$fileouturl = $imagesOut[$i]; // save the url of the processed image.
				$this->Images_model->add_image("","", $fileurl,$fileouturl,"", $date, $group, "", $world); // adds the information to the database.
			}

			echo "<script>window.location.href = 'add_information/".$date."/".$group."';</script>"; // Javascript, loads the add_information view with the variables $date and $group

		}
		$this->load->view("site_footer"); // Finally, add the footer.

	}
	 /**
	 * add_information($date = NULL , $group = NULL): Adds information for all the images to the database.
	 * Librarys:
	 * Models: Images_model
	 * Views: site_header, site_nav, content_edit, sub_info, site_footer
	 * @param  string	$date		The date
	 * @param  string	$group		The group
	 *	
	 */ 
	function add_information($date = NULL , $group = NULL)
	{	
		$this->load->view("site_header");
		$this->load->view("site_nav");
		$this->load->view("content_create");
		// Loads the Images_model model, to access the database functions.
		$this->load->model("Images_model");
		
		if(isset($_POST['delete'])){ //if the user pressed a deletebutton
			$group = $_POST['group'];
			$date = $_POST['date'];
			$counter = 0; // count the number of images.
			$idArray = $this->Images_model->get_all_id_from_group($_POST['group'], $_POST['date']); // an array with all the id's in the group
			foreach ($idArray as $id) 
			{
				if($counter == $_POST['delete']) //if the image should be deleted	
				{
					$this->Images_model->remove_image($id->id);
				}
				else //save the filled data
				{
					$artist = $_POST['artist'.$counter]; // gets the specific form for this image. ex: artist0, artist1.
					$imgname = $_POST['imgname'.$counter]; // gets the speficic imgname for this image. ex: imgname0, imgname1
					// Lägg till för type.
					$story = $_POST['story'.$counter];	// gets the specific story for this image. ex: story0, story1
					//$soundurl = $_POST['soundurl'.$counter];
					$soundurl = "";
					$this->Images_model->update_image($id ->id, $artist, $imgname, $soundurl, $story); // updates the database for the specific image.
				}
				$counter ++; 
			}
			$images = $this->Images_model->get_all_images_from_group($group, $date); // Get all images from a specific group and date.
			$data = array( // Makes an array of the array, so that the sub_info view gets an array as variabel.
			"images" => $images
						);
			if( sizeof($idArray) == 1 ) //if its only 1 image left before delete
			{
				$info = $this->Images_model->get_all_groups(); // gets an array of all the groups.
				$data = array(	// Makes an array of the array, so that the content_edit view gets an array as variabel.
				"info" => $info);
				$this->load->view("content_edit", $data); // loads the content_edit view, where the user can chose a group to edit.
			}else
			{
				echo "<script>window.location.href = 'add_information/".$date."/".$group."';</script>"; // Javascript, loads the add_information view with the variables $date and $group		
			}
				
		}else if(!(isset($date) || isset($group)) && !isset($_POST['update'])){ // if the date or group is NULL, and the user has not submited
			
			$info = $this->Images_model->get_all_groups(); // gets an array of all the groups.
			$data = array(	// Makes an array of the array, so that the content_edit view gets an array as variabel.
				"info" => $info);
			$this->load->view("content_edit", $data); // loads the content_edit view, where the user can chose a group to edit.

		}else if(!isset($_POST['update'])){ // else if, the user has not submited.

			$images = $this->Images_model->get_all_images_from_group($group, $date); // Get all images from a specific group and date.
			$data = array( // Makes an array of the array, so that the sub_info view gets an array as variabel.
				"images" => $images
				);
			$this->load->view('sub_info', $data); // Loads the sub_info view, where the user can add information for all the images.
			
		}else{ // isset($_POST['update'])
				
				$counter = 0; // count the number of images.
				$idArray = $this->Images_model->get_all_id_from_group($_POST['group'], $_POST['date']); // an array with all the id's in the group

				foreach ($idArray as $id) {
				$artist = $_POST['artist'.$counter]; // gets the specific form for this image. ex: artist0, artist1.
				$imgname = $_POST['imgname'.$counter]; // gets the speficic imgname for this image. ex: imgname0, imgname1
				// Lägg till för type.
				$story = $_POST['story'.$counter];	// gets the specific story for this image. ex: story0, story1
				//$soundurl = $_POST['soundurl'.$counter];
				$soundurl = "";
				$this->Images_model->update_image($id ->id, $artist, $imgname, $soundurl, $story); // updates the database for the specific image.
				$counter ++; // 
			}
			$group = $_POST['group'];
			$date = $_POST['date'];

			echo "<script>window.location.href = 'download_info/".$date."/".$group."';</script>";// Javascript, loads the download_info view with the variables $date and $group
		}
		$this->load->view("site_footer"); // Finally, add the footer.
		
	}
	 /**
	 * download_info($date = NULL, $group = NULL): downloads a zip of all the information from a specific group.
	 * Librarys:
	 * Models: Images_model
	 * Views: site_header, site_nav, content_download, sub_download, site_footer
	 * @param  string	$date		The date
	 * @param  string	$group		The group
	 *	
	 */ 

	function download_info($date = NULL, $group = NULL){
		$this->load->view("site_header");
		$this->load->view("site_nav");
		$this->load->view("content_create");
		$this->load->model("Images_model");
		$this->load->model("Worlds_model");
		$this->load->model("Create_xml_model");

		if(!(isset($date) || isset($group)) && !isset($_POST['download'])){ // if the date or group is NULL, and the user has not submited
			$info = $this->Images_model->get_all_groups();	// gets an array of all the groups.
			
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

			$filename = $group."_".$date.".Zip"; // Name of the zip-file to create.
			$images = $this->Images_model->get_all_images_from_group($group, $date); // Get all images from a specific group and date.
			$this->zip->clear_data(); // clear all data in the zip, just in case ;)
			foreach ($images as $row){ // For all images
				$path = $row -> imgouturl; // save the path to the image on the server.
				$this->zip->read_file($path, TRUE); // add the image to the zipfile. TRUE makes sure that the map structure remains.
				$world_id = $path = $row -> world;
			}

			$world = $this->Worlds_model->get_world($world_id);
			//Create xml file using the world and images
			$xml_url = $this->Create_xml_model->get_xml_file($world[0], $images);

			$this->zip->read_file($xml_url, TRUE);
			$this->zip->download($filename); // Makes the user download the zip-file
		}
		$this->load->view("site_footer"); // Finally, add the footer.
		
	}
	/**
	 * about(): information about the webapp
	 * Librarys:
	 * Models: 
	 * Views: site_header, site_nav, content_about, sub_download, site_footer
	 *	
	 */ 
	function about()
	{
		$this->load->view("site_header");
		$this->load->view("site_nav");
		$this->load->view("content_about");
		$this->load->view("site_footer");
	}

	function instructions()
	{
		$this->load->view("site_header");
		$this->load->view("site_nav");
		$this->load->view("content_instructions");
		$this->load->view("site_footer");
	}
	/**
	*
	* coord(): function to acess the sub_coord view, will be removed later.
	*
	*/
	function coord($id)
	{	

		$this->load->model("Worlds_model");

		$info = $this->Worlds_model->get_world($id);
		$data  = array('data' => $info);
		$this->load->view("site_header");
		$this->load->view("site_nav");
		$this->load->view("sub_coord", $data);
		$this->load->view("site_footer");
	}
}