<?php
class Image extends CI_Controller {

	public function index()
	{
		$this->load->library('ProcessImage');
		$this->processimage->test();  
	}
}
?>