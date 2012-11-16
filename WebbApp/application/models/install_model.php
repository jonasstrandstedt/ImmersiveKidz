<?php
/*
* @brief    Model that creates the table in the database. Runs everytime you visit the site and installs if the images table dont exist.
*
* @details  drop_tables(), drop all tables in the database.
*			create_images_table(), creates the table in the database and inserts example values. Uses images-model.php and create_table_helper.php
*			create_worlds_table(), creates the table in the database and inserts example values. Uses worlds-model.php and create_table_helper.php
*			create_positions_table(), creates the table in the database and inserts example values. Uses positions-model.php and create_table_helper.php
*
* @author   Viktor Fröberg, vikfr292@student.liu.se
* @author 	Belinda Bernfort, belbe886@student.liu.se
* @date     November (9) 14, 2012 
* @version  1.2 Added create_positions_table
*    
*/

class Install_model extends CI_Model 
{
    function __construct()
    {
        // Call the Model constructor
        parent::__construct();

		// drop all tables if ?drop is set in the address bar
		if(isset($_GET['drop'])) {
			$this->drop_tables();
		}

		// check the table
		$this->create_images_table();
		$this->create_worlds_table();
		$this->create_positions_table();

		// Log a debug message
		log_message('debug', "Install_model Class Initialized");
    }

	function drop_tables() {
		$this->load->dbforge();
		$this->dbforge->drop_table('images');
		$this->dbforge->drop_table('worlds');
		$this->dbforge->drop_table('positions');
	}
 	

	function create_images_table()
	{	
		// if the images table does not exist, create it
		if(!$this->db->table_exists('images') || isset($_GET['drop']))
		{
			$this->load->dbforge();
			// the table configurations from /application/helpers/create_tables_helper.php
			$this->dbforge->add_field(get_images_table_fields()); 	// get_images_table_fields() returns an array with the fields
			$this->dbforge->add_key('id',true);						// set the primary key
			$this->dbforge->create_table('images');
			log_message('info', "Created table: images");

			// inserting users
			$this->load->model("Images_model");
			$this->Images_model->add_image("Viktor Fröberg","sköldpadda", "uploads/bild.jpg","uploads/out/bildout.png","uploads/sound.mp3", "2012-11-09", "group1", "bla bla bla");
			$this->Images_model->add_image("Emil Lindström", "sköldpadda", "uploads/bild.jpg","uploads/out/bildout.png","uploads/sound.mp3", "2012-11-09", "group1", "bla bla bla");
			$this->Images_model->add_image("Jonas Strandstedt","sköldpadda", "uploads/bild.jpg","uploads/out/bildout.png","uploads/sound.mp3","2012-11-09", "group2", "bla bla bla");

		}
	}


	function create_worlds_table()
	{	
		// if the images table does not exist, create it
		if(!$this->db->table_exists('worlds') || isset($_GET['drop']))
		{
			$this->load->dbforge();
			// the table configurations from /application/helpers/create_tables_helper.php
			$this->dbforge->add_field(get_worlds_table_fields()); 	// get_images_table_fields() returns an array with the fields
			$this->dbforge->add_key('id',true);						// set the primary key
			$this->dbforge->create_table('worlds');
			log_message('info', "Created table: worlds");

			// inserting worlds
			$this->load->model("Worlds_model");
			$this->Worlds_model->add_world("JonasWorld","../../../JonasWorld/grass.png", "../../../JonasWorld/skybox_xpos.png", "../../../JonasWorld/skybox_xneg.png", "../../../JonasWorld/skybox_ypos.png", "../../../JonasWorld/skybox_yneg.png", "../../../JonasWorld/skybox_zpos.png", "../../../JonasWorld/skybox_zneg.png", "../../../JonasWorld/blomma.png", "../../../JonasWorld/bush.png", "../../../JonasWorld/tree.png");
			}
	}

	function create_positions_table()
	{	
		// if the images table does not exist, create it
		if(!$this->db->table_exists('positions') || isset($_GET['drop']))
		{
			$this->load->dbforge();
			// the table configurations from /application/helpers/create_tables_helper.php
			$this->dbforge->add_field(get_positions_table_fields()); // get_images_table_fields() returns an array with the fields
			$this->dbforge->add_key('id',true);						// set the primary key
			$this->dbforge->create_table('positions');
			log_message('info', "Created table: positions");

			// inserting positions
			$this->load->model("Positions_model");
			$this->Positions_model->add_position("2.0", "0.0", "2.5", "grass");
			}
	}


}