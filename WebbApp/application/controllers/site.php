<?php
/*
* @brief    The site controller, loads the site and all views.
*
* @details  do_multi_upload(), function for uploading images to the server and save them in the database.
*			index(), loads the startpage(upload)
*			create($submenu), loads a specific view.
*			function edit(), loads the edif view.
*			about(), loads the about view.
*
* @author   Emil Lindström, emili250@student.liu.se
* @author   Viktor Fröberg, vikfr292@student.liu.se
* @date     November 16, 2012
* @version  2.0 (Cleaned up site.php.)
*    
*/
if ( ! defined('BASEPATH')) exit('No direct script access allowed');
class Site extends CI_Controller 
{	
	public function index()
	{
		$this->upload(); // Sets the startpage to the upload view.
	}
	

	
	//Ladda upp bilder
	function __construct()
	{
		parent::__construct();
		$this->load->helper(array('form', 'url'));
	}

	function upload()
	{	
		$this->load->view("site_header");
		$this->load->view("site_nav");
		$this->load->view("content_create");

		$config['upload_path'] = './uploads/';
		$config['allowed_types'] = 'gif|jpg|png';
		$config['max_size']	= '10000';
		$config['max_width']  = '10000';
		$config['max_height']  = '10000';
		
		$this->load->library('upload', $config);
		$this->load->model("Images_model");

		$info = $this->Images_model->get_all_worlds();
		
		$data = array(
			"worlds" => $info
			);

		 if ( ! $this->upload->do_multi_upload())
		{
			$error = array('error' => $this->upload->display_errors());
			$this->load->view('upload_form', $data);
		}
		else if(isset($_POST['submit']))
		{	
			$group = $_POST['group'];
			$date = $_POST['date'];
			$world = $_POST['world'];

			$data = array('upload_data' => $this->upload->get_multi_upload());
			$this->load->model("Images_model"); // model för images tablen 
			$this->load->library('ProcessImage'); // bibliotek för bildbehandling.
			$imagesIn = array(); // Array över de uppladdade bilderna.
			for($i = 0; $i < count($data['upload_data']); $i++)// Loopa igenom alla bilder för att skapa en array över filnamen.
			{ 
				
				array_push($imagesIn, "uploads/".$data['upload_data'][$i]['file_name']);
			}

			$imagesOut = $this->processimage->findDrawing($imagesIn, "uploads"); // $imagesOut blir en array över de behandlade bilderna.

			for($i = 0; $i < count($imagesIn); $i++)
			{	
				$fileurl = $imagesIn[$i];
				$fileouturl = $imagesOut[$i];
				$this->Images_model->add_image("","", $fileurl,$fileouturl,"", $date, $group, "", $world);
			}
			//$_SESSION['group'] = $group;
			//$_SESSION['date'] = $date;
			echo "<script>window.location.href = 'add_information/".$date."/".$group."';</script>";
			//$this->add_information($date, $group);
			//$this->create("info");
			
			//$this->load->view("sub_info", $info);

		}
		$this->load->view("site_footer");

	}
	//SLUT ladda upp bilder

	function add_information($date = NULL , $group = NULL)
	{	
		$this->load->view("site_header");
		$this->load->view("site_nav");
		$this->load->view("content_create");

		$this->load->model("Images_model");

		if(!(isset($date) || isset($group)) && !isset($_POST['update'])){


			$info = $this->Images_model->get_all_groups();
			$data = array(
				"info" => $info);
			$this->load->view("content_edit", $data);
			// foreach ($info as $groupDate) {


			// }


		}else if(!isset($_POST['update'])){

			$images = $this->Images_model->get_all_images_from_group($group, $date);
			$data = array(
				"images" => $images
				);
			$this->load->view('sub_info', $data);

		}else{ // isset($_POST['update'])
				$counter = 0;
				$idArray = $this->Images_model->get_all_id_from_group($_POST['group'], $_POST['date']);

				foreach ($idArray as $id) {
				$artist = $_POST['artist'.$counter];
				$imgname = $_POST['imgname'.$counter];
				// Lägg till för type.
				$story = $_POST['story'.$counter];
				//$soundurl = $_POST['soundurl'.$counter];
				$soundurl = "";
				$this->Images_model->update_image($id ->id, $artist, $imgname, $soundurl, $story);
				$counter ++;
			}
			//$_SESSION['group'] = $_POST['group'];
			//$_SESSION['date'] = $_POST['date'];
			$group = $_POST['group'];
			$date = $_POST['date'];

			echo "<script>window.location.href = 'download_info/".$date."/".$group."';</script>";
			//$this->download_info($date, $group);
		}
		$this->load->view("site_footer");
		
	}

	function download_info($date = NULL, $group = NULL){
		$this->load->view("site_header");
		$this->load->view("site_nav");
		$this->load->view("content_create");
		$this->load->model("Images_model");
		if(!(isset($date) || isset($group)) && !isset($_POST['download'])){
			$info = $this->Images_model->get_all_groups();
			
			$data = array(
				"info" => $info);
			$this->load->view("content_download", $data);
		}
		elseif(!isset($_POST['download'])){
		
		$data = array(
				"group" => $group,
				"date" => $date
				);

		$this->load->view("sub_download", $data);
		}else{
			
			$filename = $group."_".$date.".Zip"; // Name of the zip-file to create.
			$images = $this->Images_model->get_all_images_from_group($group, $date);
			$this->zip->clear_data();
			foreach ($images as $row){
				$path = $row -> imgouturl;
				$this->zip->read_file($path, TRUE);

			}

			$this->zip->download($filename);
		}
		$this->load->view("site_footer");
		
	}
	
	function about()
	{
		$this->load->view("site_header");
		$this->load->view("site_nav");
		$this->load->view("content_about");
		$this->load->view("site_footer");
	}
}