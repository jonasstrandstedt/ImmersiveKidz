<!--
* @brief    Short class description. Max 2 sentences
*
* @details  Verbose description of class details. (Extends the brief description)
*
* @author   examplename1, mailadress1
* @author   examplename2, mailadress2
* @date     June 10, 2020
* @version  1.2.0.1 (alpha)
*    
-->

<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');

class Site extends CI_Controller 
{	
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
		
		/* $data = $this->upload->do_multi_upload();
		if(!$data)
		{
		echo "geh";
		 $error = array('error' => $this->upload->display_errors());
		$this->load->view('upload_form');
		}else 
		{
			$data = array('upload_data' => $data);
			$this->load->view('upload_success', $data);
		} */
	}
	
	public function index()
	{
		$this->create("upload"); // Sets the startpage to the upload view.
	}
		
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