<?php
/*
* @brief    Model that creates the table in the database. Runs everytime you visit the site and installs if the tables dont exist.
*
* @details  drop_tables(), drop all tables in the database.
*			create_illustrations_table(), creates the illustrations-table in the database.
*			create_worlds_table(), creates the worlds-table in the database.
*			create_models_table(), creates the models-table in the database.
*			create_billboards_table(), creates the billboards-table in the database.
*			create_groups_table(), creates the groups-table in the database.
*			create_plane_table(), creates the plane-table in the database.
*			create_maps_table(), creates the maps-table in the database.
*			create_masks_table(), creates the mask-table in the database.
*			create_animations_table(), creates the animations-table in the database.
*			create_billboards_world_table(), creates the billboard_world relations-table in the database.
*			create_model_world_table(), creates the model_world relations-table in the database.
*			create_billboards_animation_table(), creates the billboard_animation relations-table in the database.
*			create_plane_world_table(), creates the plane_world relations-table in the database.
*
* @author   Viktor Fröberg, vikfr292@student.liu.se
* @author 	Belinda Bernfort, belbe886@student.liu.se
* @date     December 18, 2012
* @version  1.3
*    
*/

class Install_model extends CI_Model 
{	

	/**
	 * Constructor, checks if the tables exist or if the user wants to drop all tables (the drop-function will be removed when development is done)
	 *
	 * @return void	
	 */ 
    function __construct()
    {
        // Call the Model constructor
        parent::__construct();

		// Drop all tables if ?drop is set in the address bar (will be removed when development is done)
		if(isset($_GET['drop'])) {
			$this->drop_tables();
		}

		// Run all functions, if drop is set, all tables will be droped. If the tables dont exist, they will be installed.
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

		// Log a debug message
		log_message('debug', "Install_model Class Initialized");
    }
    /**
	 * Drop function that dropes all tables (the drop-function will be removed when development is done)
	 *
	 * @return void	
	 */ 
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
		
	}
 	
	/**
	 * Function that creates the illustrations-table if it does not exist (or if it just have been droped).
	 *
	 * @return void	
	 */ 
	function create_illustrations_table()
	{	
		// if the illustrations-table does not exist, create it
		if(!$this->db->table_exists('illustrations') || isset($_GET['drop']))
		{
			$this->load->dbforge();
			// the table configurations from /application/helpers/create_tables_helper.php
			$this->dbforge->add_field(get_illustrations_table_fields()); 	// get_illustrations_table_fields() returns an array with the fields
			$this->dbforge->add_key('id',true);						// set the primary key
			$this->dbforge->create_table('illustrations');
			log_message('info', "Created table: illustrations");
		}
	}

	/**
	 * Function that creates the world-table if it does not exist (or if it just have been droped).
	 *
	 * @return void	
	 */ 
	function create_worlds_table()
	{	
		// if the worlds-table does not exist, create it
		if(!$this->db->table_exists('worlds') || isset($_GET['drop']))
		{
			$this->load->dbforge();
			// the table configurations from /application/helpers/create_tables_helper.php
			$this->dbforge->add_field(get_worlds_table_fields()); 	// get_worlds_table_fields() returns an array with the fields
			$this->dbforge->add_key('id',true);						// set the primary key
			$this->dbforge->create_table('worlds');
			log_message('info', "Created table: worlds");

			// insert world
			$this->load->model("Tables_model");
			$this->Tables_model->add_world("JonasWorld",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL, "-100","-100","-100","100", "100","200", "1");
			}
	}

	/**
	 * Function that creates the models-table if it does not exist (or if it just have been droped).
	 *
	 * @return void	
	 */ 
	function create_models_table()
	{	
		// if the models-table does not exist, create it
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

	/**
	 * Function that creates the billboards-table if it does not exist (or if it just have been droped).
	 *
	 * @return void	
	 */ 
	function create_billboards_table()
	{	
		// if the billboards-table does not exist, create it
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

	/**
	 * Function that creates the groups-table if it does not exist (or if it just have been droped).
	 *
	 * @return void	
	 */ 
	function create_groups_table()
	{	
		// if the groups-table does not exist, create it
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

	/**
	 * Function that creates the planes-table if it does not exist (or if it just have been droped).
	 *
	 * @return void	
	 */ 
	function create_planes_table()
	{	
		// if the planes-table does not exist, create it
		if(!$this->db->table_exists('planes') || isset($_GET['drop']))
		{
			$this->load->dbforge();
			// the table configurations from /application/helpers/create_tables_helper.php
			$this->dbforge->add_field(get_planes_table_fields()); // get_planes_table_fields() returns an array with the fields
			$this->dbforge->add_key('id',true);						// set the primary key
			$this->dbforge->create_table('planes');
			log_message('info', "Created table: planes");

			// Insert plane
			$this->load->model("Tables_model");
			$this->Tables_model->add_plane("512", "512", "plane/grass.png", "0", "0", "0", "-256", "0", "-256");
		}
	}

	/**
	 * Function that creates the maps-table if it does not exist (or if it just have been droped).
	 *
	 * @return void	
	 */ 
	function create_maps_table()
	{	
		// if the maps-table does not exist, create it
		if(!$this->db->table_exists('maps') || isset($_GET['drop']))
		{
			$this->load->dbforge();
			// the table configurations from /application/helpers/create_tables_helper.php
			$this->dbforge->add_field(get_maps_table_fields()); // get_maps_table_fields() returns an array with the fields
			$this->dbforge->add_key('id',true);						// set the primary key
			$this->dbforge->create_table('maps');
			log_message('info', "Created table: maps");

			// Insert map
			$this->load->model("Tables_model");
			$this->Tables_model->add_map("Grass", "1"); 
		}
	}

	/**
	 * Function that creates the masks-table if it does not exist (or if it just have been droped).
	 *
	 * @return void	
	 */ 
	function create_masks_table()
	{	
		// if the masks-table does not exist, create it
		if(!$this->db->table_exists('masks') || isset($_GET['drop']))
		{
			$this->load->dbforge();
			// the table configurations from /application/helpers/create_tables_helper.php
			$this->dbforge->add_field(get_masks_table_fields()); // get_masks_table_fields() returns an array with the fields
			$this->dbforge->add_key('id',true);						// set the primary key
			$this->dbforge->create_table('masks');
			log_message('info', "Created table: masks");

			// Insert mask
			$this->load->model("Tables_model");
			$this->Tables_model->add_mask("plane/grass_mask.png","Grass", 1);
		}
	}

	/**
	 * Function that creates the animations-table if it does not exist (or if it just have been droped).
	 *
	 * @return void	
	 */ 
	function create_animations_table()
	{	
		// if the animations-table does not exist, create it
		if(!$this->db->table_exists('animations') || isset($_GET['drop']))
		{
			$this->load->dbforge();
			// the table configurations from /application/helpers/create_tables_helper.php
			$this->dbforge->add_field(get_animations_table_fields()); // get_animations_table_fields() returns an array with the fields
			$this->dbforge->add_key('id',true);						// set the primary key
			$this->dbforge->create_table('animations');
			log_message('info', "Created table: animations");

			// Insert animations
			$this->load->model("Tables_model");
			$this->Tables_model->add_animation("Ingen"); 
			$this->Tables_model->add_animation("Dansa"); 
			$this->Tables_model->add_animation("Hoppa"); 
		}
	}

	/**
	 * Function that creates the billboard_world relations-table if it does not exist (or if it just have been droped).
	 *
	 * @return void	
	 */ 
	function create_billboard_world_table()
	{	
		// if the billboard_world relations-table does not exist, create it
		if(!$this->db->table_exists('billboard_world') || isset($_GET['drop']))
		{
			$this->load->dbforge();
			// the table configurations from /application/helpers/create_tables_helper.php
			$this->dbforge->add_field(get_billboard_world_table_fields()); //get_billboard_world_table_fields() returns an array with the fields
			$this->dbforge->add_key('world_id',true);
			$this->dbforge->add_key('billboard_id',true);						// set the primary key(world_id & billboard_id)
			$this->dbforge->create_table('billboard_world');
			log_message('info', "Created table: billboard_world");
		}
	}
	/**
	 * Function that creates the model_world relations-table if it does not exist (or if it just have been droped).
	 *
	 * @return void	
	 */ 
	function create_model_world_table()
	{	
		// if the model_world relations-table does not exist, create it
		if(!$this->db->table_exists('model_world') || isset($_GET['drop']))
		{
			$this->load->dbforge();
			// the table configurations from /application/helpers/create_tables_helper.php
			$this->dbforge->add_field(get_model_world_table_fields()); //get_model_world_table_fields() returns an array with the fields
			$this->dbforge->add_key('world_id',true);
			$this->dbforge->add_key('model_id',true);						// set the primary key(world_id & model_id)
			$this->dbforge->create_table('model_world');
			log_message('info', "Created table: model_world");
		}
	}

	/**
	 * Function that creates the billboard_animation relations-table if it does not exist (or if it just have been droped).
	 *
	 * @return void	
	 */ 
	function create_billboard_animation_table()
	{	
		// if the billboard_animation relations-table does not exist, create it
		if(!$this->db->table_exists('billboard_animation') || isset($_GET['drop']))
		{
			$this->load->dbforge();
			// the table configurations from /application/helpers/create_tables_helper.php
			$this->dbforge->add_field(get_billboard_animation_table_fields()); //get_billboard_animation_table_fields() returns an array with the fields
			$this->dbforge->add_key('animation_id',true);
			$this->dbforge->add_key('billboard_id',true);						// set the primary key(animations_id & billboard_id)
			$this->dbforge->create_table('billboard_animation');
			log_message('info', "Created table: billboard_animation");
		}
	}

	/**
	 * Function that creates the plane_world relations-table if it does not exist (or if it just have been droped).
	 *
	 * @return void	
	 */ 
	function create_plane_world_table()
	{	
		// if the plane_world relations-table does not exist, create it
		if(!$this->db->table_exists('plane_world') || isset($_GET['drop']))
		{
			$this->load->dbforge();
			// the table configurations from /application/helpers/create_tables_helper.php
			$this->dbforge->add_field(get_plane_world_table_fields()); //get_plane_world_table_fields() returns an array with the fields
			$this->dbforge->add_key('plane_id',true);
			$this->dbforge->add_key('world_id',true);						// set the primary key (plane_id & world_id)
			$this->dbforge->create_table('plane_world');
			log_message('info', "Created table: plane_world");
		}
	}

}