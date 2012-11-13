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
* @date     November 9, 2012
* @version  1.3 (images are now added to the database)
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
		else 
		{	
			//print_r($this->upload->get_multi_upload());
			//print_r($this->upload->data());
			//print_r($this->upload->get_multi_upload());
			$group = $_POST['group'];
			$date = $_POST['date'];
			$data = array('upload_data' => $this->upload->get_multi_upload());
			$this->load->model("Images_model");
			//echo print_r($data);
			for($i = 0; $i < count($data['upload_data']); $i++)
			{	
				$fileurl = "uploads/".$data['upload_data'][$i]['file_name'];
				//echo $data['upload_data'][$i]['file_name'];

				$this->Images_model->add_image("", $fileurl, $date, $group);
				echo "<img src='../../../".$fileurl."'' height='42' width='42'/>"; // TEST
			}
			

			$this->load->view('upload_success', $data);
		} 
	}
	//SLUT ladda upp bilder

	
	public function create($submenu)
	{		
		$this->load->view("site_header");
		$this->load->view("site_nav");	
		$this->load->view("content_create");
		if($submenu=="upload") $this->do_multi_upload();
		if($submenu=="info") $this->load->view("sub_info");
		if($submenu=="download") $this->load->view("sub_download");
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