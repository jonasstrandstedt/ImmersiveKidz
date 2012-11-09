<?php
/**
* The following function are defining the table
*
* @uses the install model class is using these functions when creating the tables
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
		'name' => array(
			'type' => 'VARCHAR',
			'constraint' => '40',
			),
		'imgurl' => array(
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
		);
	return $fields;
}