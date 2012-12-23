<?php
/*
* @brief    Simple unit test to check data types
*
*
* @author   Christoffer Hermansson chrhe155
* @author   Gabriella Ivarsson gabiv132
* @date     December 6, 2012
* @version  3.0 (new database)
*    
*/
if ( ! defined('BASEPATH')) exit('No direct script access allowed');
class UnitTest extends CI_Controller
{	
	function __construct()
	{
		parent::__construct();
		$this->load->helper(array('form', 'url'));
	}

	public function index()
	{
		$this->load->library('unit_test');
		$this->load->model("Tables_model");
		
		$this->test_get_all_worlds();
		$this->test_get_plane_from_world_id();
		$this->test_get_world_by_name();
		$this->test_get_all_illustration_id_from_group();
		$this->test_get_billboard_url_from_id();
	}

	function test_get_all_worlds()
	{
		$test_name = "Test of get_all_worlds - Should return an array";
		$expected_result = 'is_array';
		$test = $this->Tables_model->get_all_worlds();
		print_r($this->unit->run($test, $expected_result, $test_name));
	}

	function test_get_plane_from_world_id()
	{
		$test_name = "Test of get_plane_from_world_id - Should return an array";
		$expected_result = 'is_array';
		$data = 1;
		$test1 = $this->Tables_model->get_plane_from_world_id($data);
		print_r($this->unit->run($test1, $expected_result, $test_name));
	}

	function test_get_world_by_name()
	{
		$test_name = "Test of get_world_by_name - Should return an array";
		$expected_result = 'is_array';

		$data = 'JonasWorld';
		$test = $this->Tables_model->get_world_by_name($data);

		print_r($this->unit->run($test, $expected_result, $test_name));
	}

	function test_get_all_illustration_id_from_group()
	{
		$test_name = "Test1 of get_all_illustration_id_from_group - Should return an array";
		$expected_result = 'is_array';
		$data = 2;
		$test1 = $this->Tables_model->get_all_illustration_id_from_group($data);
		print_r($this->unit->run($test1, $expected_result, $test_name));
		
		$test_name = "Test2 of get_all_illustrations_id_from_group - The array should contain objects, i.e. images";
		$expected_result = 'is_object'; 
		$test2 = $test1[0]; 
		print_r($this->unit->run($test2, $expected_result, $test_name));
	}

	function test_get_billboard_url_from_id()
	{
		$test_name = "Test1 of get_billboard_url_from_id - Should return an array";
		$expected_result = 'is_array';
		$data = 1;
		$test1 = $this->Tables_model->get_billboard_url_from_id($data);
		print_r($this->unit->run($test1, $expected_result, $test_name));

		$test_name = "Test2 of get_billboard_url_from_id - The array should contain the url:s as strings";
		$expected_result = 'is_string';
		$test1 = $test1[0];
		$test2 = $test1->imgurl;
		print_r($this->unit->run($test2, $expected_result, $test_name));
	}	
}
?>