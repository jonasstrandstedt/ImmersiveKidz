<?php
/*
* @brief    Function that that returns all fields for the different tables the database should have. Used in install_model.php
*
* @details  get_illustrations_table_fields(), returns an array containing all the columns that should be in the illustrations table. 
*			get_worlds_table_fields(), returns an array containing all the columns that should be in the worlds table.
*			get_models_table_fields(), returns an array containing all the columns that should be in the models table.
*			get_billboards_table_fields(), returns an array containing all the columns that should be in the billboards table.
*			get_groups_table_fields(), returns an array containing all the columns that should be in the groups table.
*			get_planes_table_fields(), returns an array containing all the columns that should be in the planes table.
*			get_masks_table_fields(), returns an array containing all the columns that should be in the masks table.
*			get_animations_table_fields(), returns an array containing all the columns that should be in the animations table.
*			get_maps_table_fields(), returns an array containing all the columns that should be in the maps table.
*			the install model class is using these functions when creating the tables
*
* @author   Viktor Fröberg, vikfr292@student.liu.se
* @author 	Belinda Bernfort, belbe886@studetn.liu.se
* @date     December 6, 2012
* @version  1.4 Added get table fields functions for all tables
*    
*/


 /**
 * Function returning all the columns the illustrations-table should contain
 *
 * @return array 	
 */ 
function get_illustrations_table_fields()
{	
	$fields = array(
		'id' => array(
			'type' => 'INT',
			'constraint' => 5, 
			'unsigned' => TRUE,
			'auto_increment' => TRUE
			),
		'artist' => array(
			'type' => 'VARCHAR',
			'constraint' => '40',
			),
		'imgname' => array(
			'type' => 'VARCHAR',
			'constraint' => '40',
			),
		'imgurl' => array(
			'type' => 'VARCHAR',
			'constraint' => '400',
			),
		'soundurl' => array(
			'type' => 'VARCHAR',
			'constraint' => '400',
			),
		'group_id' => array(
			'type' => 'INT',
			'constraint' => 5, 
			'unsigned' => TRUE
			),
		'story' => array(
			'type' => 'TEXT',
			'constraint' => '400'
			),
		'billboard_id' => array(
			'type' => 'INT',
			'constraint' => 5, 
			'unsigned' => TRUE
			),
		'pos_x' => array(
			'type' => 'FLOAT',
			'constraint' => 4,1,
			'null' => TRUE
			),
		'pos_y' => array(
			'type' => 'FLOAT',
			'constraint' => 4,1,
			'null' => TRUE
			),
		'pos_z' => array(
			'type' => 'FLOAT',
			'constraint' => 4,1,
			'null' => TRUE
			),
		'thresh' => array(
			'type' => 'INT',
			'constraint' => 15,
			'default' => 5
			)

		);
	return $fields;
}
 /**
 * Function returning all the columns the worlds-table should contain
 *
 * @return array 	
 */ 
function get_worlds_table_fields() 
{	
	$fields = array(
		'id' => array(
			'type' => 'INT',
			'constraint' => 5, 
			'unsigned' => TRUE,
			'auto_increment' => TRUE
			),
		'name' => array(
			'type' => 'VARCHAR',
			'constraint' => '40',
			),
		'camlim_xpos' => array(
			'type' => 'FLOAT',
			'constraint' => 4,1,
			'null' => TRUE
			),
		'camlim_xmin' => array(
			'type' => 'FLOAT',
			'constraint' => 4,1,
			'null' => TRUE
			),
		'camlim_ypos' => array(
			'type' => 'FLOAT',
			'constraint' => 4,1,
			'null' => TRUE
			),
		'camlim_ymin' => array(
			'type' => 'FLOAT',
			'constraint' => 4,1,
			'null' => TRUE
			),
		'camlim_zpos' => array(
			'type' => 'FLOAT',
			'constraint' => 4,1,
			'null' => TRUE
			),
		'camlim_zmin' => array(
			'type' => 'FLOAT',
			'constraint' => 4,1,
			'null' => TRUE
			),
		'camstart_x' => array(
			'type' => 'FLOAT',
			'constraint' => 4,1,
			'null' => TRUE
			),
		'camstart_y' => array(
			'type' => 'FLOAT',
			'constraint' => 4,1,
			'null' => TRUE
			),
		'camstart_z' => array(
			'type' => 'FLOAT',
			'constraint' => 4,1,
			'null' => TRUE
			),
		'camdir_x' => array(
			'type' => 'FLOAT',
			'constraint' => 4,1,
			'null' => TRUE
			),
		'camdir_y' => array(
			'type' => 'FLOAT',
			'constraint' => 4,1,
			'null' => TRUE
			),
		'camdir_z' => array(
			'type' => 'FLOAT',
			'constraint' => 4,1,
			'null' => TRUE
			),
		'randmin_x' => array(
			'type' => 'FLOAT',
			'constraint' => 4,1,
			'null' => TRUE
			),
		'randmin_y' => array(
			'type' => 'FLOAT',
			'constraint' => 4,1,
			'null' => TRUE
			),
		'randmin_z' => array(
			'type' => 'FLOAT',
			'constraint' => 4,1,
			'null' => TRUE
			),
		'randmax_x' => array(
			'type' => 'FLOAT',
			'constraint' => 4,1,
			'null' => TRUE
			),
		'randmax_y' => array(
			'type' => 'FLOAT',
			'constraint' => 4,1,
			'null' => TRUE
			),
		'randmax_z' => array(
			'type' => 'FLOAT',
			'constraint' => 4,1,
			'null' => TRUE
			),
		'map_id' => array(
			'type' => 'INT',
			'constraint' => 5, 
			'unsigned' => TRUE,
			)
		);
	return $fields;
}
 /**
 * Function returning all the columns the models-table should contain
 *
 * @return array 	
 */ 
function get_models_table_fields()
{	
	$fields = array(
		'id' => array(
			'type' => 'INT',
			'constraint' => 5, 
			'unsigned' => TRUE,
			'auto_increment' => TRUE
			),
		'obj_fileurl' => array(
			'type' => 'VARCHAR',
			'constraint' => '400'
			),
		'textureurl' => array(
			'type' => 'VARCHAR',
			'constraint' => '400'
			),
		'animation_id' => array(
			'type' => 'INT',
			'constraint' => 5, 
			'unsigned' => TRUE
			)
		);
	return $fields;
}
 /**
 * Function returning all the columns the billboards-table should contain
 *
 * @return array 	
 */ 
function get_billboards_table_fields()
{	
	$fields = array(
		'id' => array(
			'type' => 'INT',
			'constraint' => 5, 
			'unsigned' => TRUE,
			'auto_increment' => TRUE
			),
		'imgurl' => array(
			'type' => 'VARCHAR',
			'constraint' => '400'
			),
		'size_x' => array(
			'type' => 'FLOAT',
			'constraint' => 4,1,
			'unsigned' => TRUE
			),
		'size_y' => array(
			'type' => 'FLOAT',
			'constraint' => 4,1,
			'unsigned' => TRUE
			),
		'thresh' => array(
			'type' => 'INT',
			'constraint' => 15,
			'default' => 5
			)
		);
	return $fields;
}

 /**
 * Function returning all the columns the groups-table should contain
 *
 * @return array 	
 */ 
function get_groups_table_fields()
{	
	$fields = array(
		'id' => array(
			'type' => 'INT',
			'constraint' => 5, 
			'unsigned' => TRUE,
			'auto_increment' => TRUE
			),
		'name' => array(
			'type' => 'VARCHAR',
			'constraint' => '40'
			),
		'date' => array(
			'type' => 'VARCHAR',
			'constraint' => '10',
			),
		'world_id' => array(
			'type' => 'INT',
			'constraint' => 5, 
			'unsigned' => TRUE
			)
		);
	return $fields;
}

 /**
 * Function returning all the columns the planes-table should contain
 *
 * @return array 	
 */ 
function get_planes_table_fields()
{	
	$fields = array(
		'id' => array(
			'type' => 'INT',
			'constraint' => 5, 
			'unsigned' => TRUE,
			'auto_increment' => TRUE
			),
		'width' => array(
			'type' => 'FLOAT',
			'constraint' => 4,1
			),
		'height' => array(
			'type' => 'FLOAT',
			'constraint' => 4,1
			),
		'textureurl' => array(
			'type' => 'VARCHAR',
			'constraint' => '400'
			),
		'rot_x' => array(
			'type' => 'FLOAT',
			'constraint' => 4,1
			),
		'rot_y' => array(
			'type' => 'FLOAT',
			'constraint' => 4,1
			),
		'rot_z' => array(
			'type' => 'FLOAT',
			'constraint' => 4,1
			),
		'pos_x' => array(
			'type' => 'FLOAT',
			'constraint' => 4,1
			),
		'pos_y' => array(
			'type' => 'FLOAT',
			'constraint' => 4,1
			),
		'pos_z' => array(
			'type' => 'FLOAT',
			'constraint' => 4,1
			)
		);
	return $fields;
}

 /**
 * Function returning all the columns the masks-table should contain
 *
 * @return array 	
 */ 
function get_masks_table_fields()
{	
	$fields = array(
		'id' => array(
			'type' => 'INT',
			'constraint' => 5, 
			'unsigned' => TRUE,
			'auto_increment' => TRUE
			),
		'textureurl' => array(
			'type' => 'VARCHAR',
			'constraint' => '400'
			),
		'name' => array(
			'type' => 'VARCHAR',
			'constraint' => '40'
			),
		'map_id' => array(
			'type' => 'INT',
			'constraint' => 5, 
			'unsigned' => TRUE
			)
		);
	return $fields;
}

 /**
 * Function returning all the columns the animations-table should contain
 *
 * @return array 	
 */ 
function get_animations_table_fields()
{	
	$fields = array(
		'id' => array(
			'type' => 'INT',
			'constraint' => 5, 
			'unsigned' => TRUE,
			'auto_increment' => TRUE
			),
		'name' => array(
			'type' => 'VARCHAR',
			'constraint' => '40'
			)
		);
	return $fields;
}

 /**
 * Function returning all the columns the maps-table should contain
 *
 * @return array 	
 */ 
function get_maps_table_fields()
{	
	$fields = array(
		'id' => array(
			'type' => 'INT',
			'constraint' => 5, 
			'unsigned' => TRUE,
			'auto_increment' => TRUE
			),
		'name' => array(
			'type' => 'VARCHAR',
			'constraint' => '40'
			),
		'plane_id' => array(
			'type' => 'INT',
			'constraint' => 5, 
			'unsigned' => TRUE
			)
		);
	return $fields;
}

 /**
 * Function returning all the columns the billboard_world-table should contain
 *
 * @return array 	
 */ 
function get_billboard_world_table_fields()
{	
	$fields = array(
		'world_id' => array(
			'type' => 'INT',
			'constraint' => 5, 
			'unsigned' => TRUE
			),
		'billboard_id' => array(
			'type' => 'INT',
			'constraint' => 5, 
			'unsigned' => TRUE
			),
		'mask_id' => array(
			'type' => 'INT',
			'constraint' => 5, 
			'unsigned' => TRUE
			),
		'pos_x' => array(
			'type' => 'FLOAT',
			'constraint' => 4,1 
			),
		'pos_y' => array(
			'type' => 'FLOAT',
			'constraint' => 4,1 
			),
		'pos_z' => array(
			'type' => 'FLOAT',
			'constraint' => 4,1 
			),
		'mult_count' => array(  
			'type' => 'INT',
			'constraint' => 7 
			),
		'mult_seed' => array(
			'type' => 'INT',
			'constraint' => 7 
			),
		'type' => array(
			'type' => 'VARCHAR',
			'constraint' => '40' 
			)
		);
	return $fields;
}

 /**
 * Function returning all the columns the model_world-table should contain
 *
 * @return array 	
 */ 
function get_model_world_table_fields()
{	
	$fields = array(
		'world_id' => array(
			'type' => 'INT',
			'constraint' => 5, 
			'unsigned' => TRUE
			),
		'model_id' => array(
			'type' => 'INT',
			'constraint' => 5, 
			'unsigned' => TRUE
			),
		'pos_x' => array(
			'type' => 'FLOAT',
			'constraint' => 4,1 
			),
		'pos_y' => array(
			'type' => 'FLOAT',
			'constraint' => 4,1 
			),
		'pos_z' => array(
			'type' => 'FLOAT',
			'constraint' => 4,1 
			),
		'rot_x' => array(
			'type' => 'FLOAT',
			'constraint' => 4,1 
			),
		'rot_y' => array(
			'type' => 'FLOAT',
			'constraint' => 4,1 
			),
		'rot_z' => array(
			'type' => 'FLOAT',
			'constraint' => 4,1 
			),
		'mult_count' => array(  
			'type' => 'INT',
			'constraint' => 7 
			),
		'mult_seed' => array(
			'type' => 'INT',
			'constraint' => 7 
			)
		);
	return $fields;
}

 /**
 * Function returning all the columns the billboard_animation-table should contain
 *
 * @return array 	
 */ 
function get_billboard_animation_table_fields()
{	
	$fields = array(
		'animation_id' => array(
			'type' => 'INT',
			'constraint' => 5, 
			'unsigned' => TRUE
			),
		'billboard_id' => array(
			'type' => 'INT',
			'constraint' => 5, 
			'unsigned' => TRUE
			),
		'seed' => array(           
			'type' => 'INT',
			'constraint' => 7 
			)
		);
	return $fields;
}

 /**
 * Function returning all the columns the plane_world-table should contain
 *
 * @return array 	
 */ 
function get_plane_world_table_fields()
{	
	$fields = array(
		'plane_id' => array(
			'type' => 'INT',
			'constraint' => 5, 
			'unsigned' => TRUE
			),
		'world_id' => array(
			'type' => 'INT',
			'constraint' => 5, 
			'unsigned' => TRUE
			),
		'mult_count' => array(  
			'type' => 'INT',
			'constraint' => 7 
			),
		'mult_seed' => array(
			'type' => 'INT',
			'constraint' => 7 
			),
		'animation_id' => array(
			'type' => 'INT',
			'constraint' => 5, 
			'unsigned' => TRUE
			)
		);
	return $fields;
}