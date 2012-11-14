<!--
* @brief    Function that creates the table for the images.
*
* @details  get_images_table_fields(), returns an array containing all the columns that should be in the images table. 
*			the install model class is using these functions when creating the tables
*
* @author   Viktor Fröberg, vikfr292@student.liu.se
* @date     November 9, 2012
* @version  1.0
*    
-->

<?php

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
			'constraint' => '40',
			),
		'imgouturl' => array(
			'type' => 'VARCHAR',
			'constraint' => '40',
			),
		'soundurl' => array(
			'type' => 'VARCHAR',
			'constraint' => '40',
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
			'constraint' => '300'
			)
		);
	return $fields;
}