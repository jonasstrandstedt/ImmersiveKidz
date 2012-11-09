<?php
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

		// Log a debug message
		log_message('debug', "Install_model Class Initialized");
    }

	function drop_tables() {
		$this->load->dbforge();
		$this->dbforge->drop_table('images');
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
			$this->Images_model->add_image("Viktor Fröberg", "uploads/bild1.jpg", "2012-11-09", "group1");
			$this->Images_model->add_image("Emil Lindström", "uploads/bild2.jpg", "2012-11-09", "group1");
			$this->Images_model->add_image("Jonas Strandstedt", "uploads/bild3.jpg", "2012-11-09", "group2");

		}
	}

	}