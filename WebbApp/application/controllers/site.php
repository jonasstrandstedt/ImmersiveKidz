<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');

class Site extends CI_Controller 
{
	public function index()
	{
		$this->skapa();
	}
		
	public function skapa()
	{
		$this->load->view("site_header");
		$this->load->view("site_nav");
		$this->load->view("content_skapa");
		$this->load->view("site_footer");
	}
	
	public function andra()
	{
		$this->load->view("site_header");
		$this->load->view("site_nav");
		$this->load->view("content_andra");
		$this->load->view("site_footer");
	}
	
	public function om()
	{
		$this->load->view("site_header");
		$this->load->view("site_nav");
		$this->load->view("content_om");
		$this->load->view("site_footer");
	}
}