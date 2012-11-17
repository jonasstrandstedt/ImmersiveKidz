<?php
/*
* @brief    Function that creates the table for the images.
*
* @details  get_images_table_fields(), returns an array containing all the columns that should be in the images table. 
*			function get_worlds_table_fields(), returns an array containing all the columns that should be in the worlds table.
*			function get_positions_table_fields(), returns an array containing all the columns that should be in the positions table.
*			the install model class is using these functions when creating the tables
*
* @author   Viktor Fröberg, vikfr292@student.liu.se
* @author 	Belinda Bernfort, belbe886@studetn.liu.se
* @date     November 15, 2012
* @version  1.2 Added get table fields functions for worlds and positions
*    
*/


function get_images_table_fields()
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
		'imgouturl' => array(
			'type' => 'VARCHAR',
			'constraint' => '400',
			),
		'soundurl' => array(
			'type' => 'VARCHAR',
			'constraint' => '400',
			),
		'date' => array(
			'type' => 'VARCHAR',
			'constraint' => '10',
			),
		'group' => array(
			'type' => 'VARCHAR',
			'constraint' => '30',
			),
		'story' => array(
			'type' => 'TEXT',
			'constraint' => '400'
			)
		);
	return $fields;
}

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
		'floor' => array(
			'type' => 'VARCHAR',
			'constraint' => '40',
			),
		'sky_xpos' => array(
			'type' => 'VARCHAR',
			'constraint' => '40',
			),
		'sky_xneg' => array(
			'type' => 'VARCHAR',
			'constraint' => '40',
			),
		'sky_ypos' => array(
			'type' => 'VARCHAR',
			'constraint' => '40',
			),
		'sky_yneg' => array(
			'type' => 'VARCHAR',
			'constraint' => '10',
			),
		'sky_zpos' => array(
			'type' => 'VARCHAR',
			'constraint' => '30',
			),
		'sky_zneg' => array(
			'type' => 'VARCHAR',
			'constraint' => '30',
			),
		'smallobj' => array(
			'type' => 'VARCHAR',
			'constraint' => '30',
			),
		'mediumobj' => array(
			'type' => 'VARCHAR',
			'constraint' => '30',
			),
		'bigobj' => array(
			'type' => 'VARCHAR',
			'constraint' => '30',
			)
		);
	return $fields;
}

function get_positions_table_fields()
{	
	$fields = array(
		'id' => array(
			'type' => 'INT',
			'constraint' => 5, 
			'unsigned' => TRUE,
			'auto_increment' => TRUE
			),
		'xval' => array(
			'type' => 'DOUBLE',
			),
		'yval' => array(
			'type' => 'DOUBLE',
			),
		'zval' => array(
			'type' => 'DOUBLE',
			),
		'classification' => array(
			'type' => 'VARCHAR',
			'constraint' => '40',
			)
		);
	return $fields;
}