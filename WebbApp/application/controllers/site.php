<?php session_start(); ?>
<!--
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
* @date     November 14, 2012
* @version  1.34 (processed images are now added to the database on upload.)
*    
-->

<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');
class Site extends CI_Controller 
{	
	public function index()
	{
		$this->create("upload"); // Sets the startpage to the upload view.
	}
	

	
	//Ladda upp bilder
	function __construct()
	{
		parent::__construct();
		$this->load->helper(array('form', 'url'));
	}

	function do_multi_upload()
	{
		$config['upload_path'] = './uploads/';
		$config['allowed_types'] = 'gif|jpg|png';
		$config['max_size']	= '10000';
		$config['max_width']  = '10000';
		$config['max_height']  = '10000';

		$this->load->library('upload', $config);
		
		 if ( ! $this->upload->do_multi_upload())
		{
			$error = array('error' => $this->upload->display_errors());
			$this->load->view('upload_form');
		}
		else if(isset($_POST['submit']))
		{	
			$group = $_POST['group'];
			$date = $_POST['date'];
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
				$this->Images_model->add_image("","", $fileurl,$fileouturl,"", $date, $group, "");
			}
			$_SESSION['group'] = $group;
			$_SESSION['date'] = $date;
			echo "<script>window.location.href = '../create/info';</script>";
			//$this->create("info");
			
			//$this->load->view("sub_info", $info);

		} 
	}
	//SLUT ladda upp bilder

	function add_information($date, $group)
	{
		$this->load->model("Images_model");
		
		echo $date . " " . $group;

		if(!(isset($date) || isset($group)) && !isset($_POST['update'])){
			// Välj en grupp och ett datum att editera.
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
			$_SESSION['group'] = $_POST['group'];
			$_SESSION['date'] = $_POST['date'];
			echo "<script>window.location.href = '../create/download';</script>";
		}
		
	}

	function download_info(){
		$this->load->view("sub_download");
		echo $_SESSION['group'];
		
	}

	
	public function create($submenu)
	{		echo"<h2>".$submenu."</h2>";
			$this->load->view("site_header");
			$this->load->view("site_nav");
			$this->load->view("content_create");
			if($submenu=="upload") $this->do_multi_upload();
			if($submenu=="download") $this->download_info(); 
			//if($submenu=="info") $this->load->view("sub_info");
			if($submenu=="info")
			{ 	
				if(isset($_SESSION['date']) && isset($_SESSION['group'])){
					$date = $_SESSION['date'];
					$group = $_SESSION['group'];
					$this->add_information($date,$group);
				}else{
					$this->add_information(NULL,NULL);
				}
			}
			$this->load->view("site_footer");
		}
	public function edit()
	{
		$this->load->view("site_header");
		$this->load->view("site_nav");
		$this->load->view("content_edit");
		$this->load->view("site_footer");
	}
	
	public function about()
	{
		$this->load->view("site_header");
		$this->load->view("site_nav");
		$this->load->view("content_about");
		$this->load->view("site_footer");
	}
}