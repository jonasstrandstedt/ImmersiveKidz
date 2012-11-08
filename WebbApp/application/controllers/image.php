<?php
class Image extends CI_Controller {

	public function index()
	{
		$this->load->library('ProcessImage');
		$folder = "images";
		$images = $this->processimage->readIms($folder); 
		$this->processimage->findDrawing($images, $folder);  
	}
}
?>