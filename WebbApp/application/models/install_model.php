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
* @date     November (9) 14, 2012 (December 4, 2012)
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
		$this->create_illustrations_table();
		$this->create_worlds_table();
		$this->create_models_table();
		$this->create_billboards_table();
		$this->create_groups_table();
		$this->create_planes_table();
		$this->create_maps_table();
		$this->create_masks_table();
		$this->create_animations_table();
		$this->create_billboard_world_table();
		$this->create_model_world_table();
		$this->create_billboard_animation_table();
		$this->create_plane_world_table();
		//$this->create_map_world_table();

		// Log a debug message
		log_message('debug', "Install_model Class Initialized");
    }

	function drop_tables() {
		$this->load->dbforge();
		$this->dbforge->drop_table('illustrations');
		$this->dbforge->drop_table('worlds');
		$this->dbforge->drop_table('models');
		$this->dbforge->drop_table('billboards');
		$this->dbforge->drop_table('groups');
		$this->dbforge->drop_table('planes');
		$this->dbforge->drop_table('maps');
		$this->dbforge->drop_table('masks');
		$this->dbforge->drop_table('animations');
		$this->dbforge->drop_table('worlds');
		$this->dbforge->drop_table('billboard_world');
		$this->dbforge->drop_table('model_world');
		$this->dbforge->drop_table('billboard_animation');
		$this->dbforge->drop_table('plane_world');
		//$this->dbforge->drop_table('map_world');
		
	}
 	

	function create_illustrations_table()
	{	
		// if the images table does not exist, create it
		if(!$this->db->table_exists('illustrations') || isset($_GET['drop']))
		{
			$this->load->dbforge();
			// the table configurations from /application/helpers/create_tables_helper.php
			$this->dbforge->add_field(get_images_table_fields()); 	// get_images_table_fields() returns an array with the fields
			$this->dbforge->add_key('id',true);						// set the primary key
			$this->dbforge->create_table('illustrations');
			log_message('info', "Created table: illustrations");
		}
	}


	function create_worlds_table()
	{	
		// if the images table does not exist, create it
		if(!$this->db->table_exists('worlds') || isset($_GET['drop']))
		{
			$this->load->dbforge();
			// the table configurations from /application/helpers/create_tables_helper.php
			$this->dbforge->add_field(get_worlds_table_fields()); 	// get_worlds_table_fields() returns an array with the fields
			$this->dbforge->add_key('id',true);						// set the primary key
			$this->dbforge->create_table('worlds');
			log_message('info', "Created table: worlds");

			// inserting worlds

			$this->load->model("Tables_model");
			$this->Tables_model->add_world("JonasWorld",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL, "-100","-100","-100","100", "100","200", "1");
			}
	}


	function create_models_table()
	{	
		// if the images table does not exist, create it
		if(!$this->db->table_exists('models') || isset($_GET['drop']))
		{
			$this->load->dbforge();
			// the table configurations from /application/helpers/create_tables_helper.php
			$this->dbforge->add_field(get_models_table_fields()); // get_models_table_fields() returns an array with the fields
			$this->dbforge->add_key('id',true);						// set the primary key
			$this->dbforge->create_table('models');
			log_message('info', "Created table: models");
		}
	}

	function create_billboards_table()
	{	
		// if the images table does not exist, create it
		if(!$this->db->table_exists('billboards') || isset($_GET['drop']))
		{
			$this->load->dbforge();
			// the table configurations from /application/helpers/create_tables_helper.php
			$this->dbforge->add_field(get_billboards_table_fields()); // get_billboards_table_fields() returns an array with the fields
			$this->dbforge->add_key('id',true);						// set the primary key
			$this->dbforge->create_table('billboards');
			log_message('info', "Created table: billboards");

		}
	}

	function create_groups_table()
	{	
		// if the images table does not exist, create it
		if(!$this->db->table_exists('groups') || isset($_GET['drop']))
		{
			$this->load->dbforge();
			// the table configurations from /application/helpers/create_tables_helper.php
			$this->dbforge->add_field(get_groups_table_fields()); // get_groups_table_fields() returns an array with the fields
			$this->dbforge->add_key('id',true);						// set the primary key
			$this->dbforge->create_table('groups');
			log_message('info', "Created table: groups");
		}
	}


	function create_planes_table()
	{	
		// if the images table does not exist, create it
		if(!$this->db->table_exists('planes') || isset($_GET['drop']))
		{
			$this->load->dbforge();
			// the table configurations from /application/helpers/create_tables_helper.php
			$this->dbforge->add_field(get_planes_table_fields()); // get_planes_table_fields() returns an array with the fields
			$this->dbforge->add_key('id',true);						// set the primary key
			$this->dbforge->create_table('planes');
			log_message('info', "Created table: planes");
			$this->load->model("Tables_model");
			$this->Tables_model->add_plane("512", "512", "plane/grass.png", "0", "0", "0", "-256", "0", "-256");
		}
	}

	function create_maps_table()
	{	
		// if the images table does not exist, create it
		if(!$this->db->table_exists('maps') || isset($_GET['drop']))
		{
			$this->load->dbforge();
			// the table configurations from /application/helpers/create_tables_helper.php
			$this->dbforge->add_field(get_maps_table_fields()); // get_maps_table_fields() returns an array with the fields
			$this->dbforge->add_key('id',true);						// set the primary key
			$this->dbforge->create_table('maps');
			log_message('info', "Created table: maps");
			$this->load->model("Tables_model");
			$this->Tables_model->add_map("Grass", "1"); 
		}
	}


	function create_masks_table()
	{	
		// if the images table does not exist, create it
		if(!$this->db->table_exists('masks') || isset($_GET['drop']))
		{
			$this->load->dbforge();
			// the table configurations from /application/helpers/create_tables_helper.php
			$this->dbforge->add_field(get_masks_table_fields()); // get_masks_table_fields() returns an array with the fields
			$this->dbforge->add_key('id',true);						// set the primary key
			$this->dbforge->create_table('masks');
			log_message('info', "Created table: masks");
			$this->load->model("Tables_model");
			$this->Tables_model->add_mask("plane/grass_mask.png","Grass", 1);
		}
	}

	function create_animations_table()
	{	
		// if the images table does not exist, create it
		if(!$this->db->table_exists('animations') || isset($_GET['drop']))
		{
			$this->load->dbforge();
			// the table configurations from /application/helpers/create_tables_helper.php
			$this->dbforge->add_field(get_animations_table_fields()); // get_animations_table_fields() returns an array with the fields
			$this->dbforge->add_key('id',true);						// set the primary key
			$this->dbforge->create_table('animations');
			log_message('info', "Created table: animations");
			$this->load->model("Tables_model");
			$this->Tables_model->add_animation("Ingen"); 
			$this->Tables_model->add_animation("Dansa"); 
			$this->Tables_model->add_animation("Hoppa"); 
		}
	}

	function create_billboard_world_table()
	{	
		// if the images table does not exist, create it
		if(!$this->db->table_exists('billboard_world') || isset($_GET['drop']))
		{
			$this->load->dbforge();
			// the table configurations from /application/helpers/create_tables_helper.php
			$this->dbforge->add_field(get_billboard_world_table_fields()); //get_billboard_world_table_fields() returns an array with the fields
			$this->dbforge->add_key('world_id',true);
			$this->dbforge->add_key('billboard_id',true);						// set the primary key
			$this->dbforge->create_table('billboard_world');
			log_message('info', "Created table: billboard_world");
		}
	}

	function create_model_world_table()
	{	
		// if the images table does not exist, create it
		if(!$this->db->table_exists('model_world') || isset($_GET['drop']))
		{
			$this->load->dbforge();
			// the table configurations from /application/helpers/create_tables_helper.php
			$this->dbforge->add_field(get_model_world_table_fields()); //get_model_world_table_fields() returns an array with the fields
			$this->dbforge->add_key('world_id',true);
			$this->dbforge->add_key('model_id',true);						// set the primary key
			$this->dbforge->create_table('model_world');
			log_message('info', "Created table: model_world");
		}
	}

	function create_billboard_animation_table()
	{	
		// if the images table does not exist, create it
		if(!$this->db->table_exists('billboard_animation') || isset($_GET['drop']))
		{
			$this->load->dbforge();
			// the table configurations from /application/helpers/create_tables_helper.php
			$this->dbforge->add_field(get_billboard_animation_table_fields()); //get_billboard_animation_table_fields() returns an array with the fields
			$this->dbforge->add_key('animation_id',true);
			$this->dbforge->add_key('billboard_id',true);						// set the primary key
			$this->dbforge->create_table('billboard_animation');
			log_message('info', "Created table: billboard_animation");
		}
	}

	function create_plane_world_table()
	{	
		// if the images table does not exist, create it
		if(!$this->db->table_exists('plane_world') || isset($_GET['drop']))
		{
			$this->load->dbforge();
			// the table configurations from /application/helpers/create_tables_helper.php
			$this->dbforge->add_field(get_plane_world_table_fields()); //get_plane_world_table_fields() returns an array with the fields
			$this->dbforge->add_key('plane_id',true);
			$this->dbforge->add_key('world_id',true);						// set the primary key
			$this->dbforge->create_table('plane_world');
			log_message('info', "Created table: plane_world");
		}
	}

	function create_map_world_table()
	{	
		// if the images table does not exist, create it
		if(!$this->db->table_exists('map_world') || isset($_GET['drop']))
		{
			$this->load->dbforge();
			// the table configurations from /application/helpers/create_tables_helper.php
			$this->dbforge->add_field(get_map_world_table_fields()); //get_plane_world_table_fields() returns an array with the fields
			$this->dbforge->add_key('map_id',true);
			$this->dbforge->add_key('world_id',true);						// set the primary key
			$this->dbforge->create_table('map_world');
			log_message('info', "Created table: map_world");
		}
	}


}