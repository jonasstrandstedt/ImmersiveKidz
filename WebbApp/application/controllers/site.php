<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');

class Site extends CI_Controller 
{	
	function __construct()
	{
		parent::__construct();
		$this->load->helper(array('form', 'url'));
	}

	function do_upload()
	{
		$config['upload_path'] = './uploads/';
		$config['allowed_types'] = 'gif|jpg|png';
		$config['max_size']	= '10000';
		$config['max_width']  = '1024';
		$config['max_height']  = '768';

		$this->load->library('upload', $config);
		
		if ( ! $this->upload->do_multi_upload())
		{
			$error = array('error' => $this->upload->display_errors());

			$this->load->view('upload_form');
		}
		else 
		{
			$data = array('upload_data' => $this->upload->data());

			$this->load->view('upload_success', $data);
		}
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
		if($submenu=="upload") $this->do_upload();
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