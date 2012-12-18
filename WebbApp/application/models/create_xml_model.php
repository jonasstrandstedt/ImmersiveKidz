<?php
/*
* @brief    Functions to generate resulting xml file.
*
* @details  
			function xml_dom() Creates a DOMDocument
*			create_xml($world, $images) Creates the xml structure
			get_xml_file($world, $images) Writes the generated structure to an xml file
*
* @author   Gabriella Ivarsson gabiv132
* @date     December 4, 2012
* @version  
*    
*/


class Create_xml_model extends CI_Model 
{

    function __construct()
    {
        // Call the Model constructor
        parent::__construct();
    }


    function xml_dom()
	{
		return new DOMDocument('1.0');
	}

    function create_xml($world, $images, $plane, $model, $map, $mask, $group, $billboard_world, $billboard, $animation, $billboard_animation, $model_world) 
    {
    	/***Variables world****/
    	//Camera

		$camlim_xpos =  $world->camlim_xpos;
		$camlim_ypos =  $world->camlim_ypos;
		$camlim_zpos =  $world->camlim_zpos;

		$camlim_xmin =  $world->camlim_xmin;
		$camlim_ymin =  $world->camlim_ymin;
		$camlim_zmin =  $world->camlim_zmin;

		$camstart_x =  $world->camstart_x;
		$camstart_y =  $world->camstart_y;
		$camstart_z =  $world->camstart_z;

		$camdir_x =  $world->camdir_x;
		$camdir_y =  $world->camdir_y;
		$camdir_z =  $world->camdir_z;

		//Plane
		//$thePlane =  $plane->textureurl;
		$theMinX_rand =  $world->randmin_x;
		$theMinY_rand =  $world->randmin_y;
		$theMinZ_rand =  $world->randmin_z;
		$theMaxX_rand =  $world->randmax_x;
		$theMaxY_rand =  $world->randmax_y;
		$theMaxZ_rand =  $world->randmax_z;

		$this->load->helper('xml');

		/********XML*********/
    	/***World****/
		$dom = $this->xml_dom();
		$scene = xml_add_child($dom, "scene");
		$world = xml_add_child($scene, "world");
		//camera
		//if(($camlim_xpos != NULL || $camlim_xpos != '') && ($camlim_ypos != NULL || $camlim_ypos != '') && ($camlim_xpos != NULL || $camlim_xpos != '')&& ($camlim_zpos != NULL || $camlim_zpos != '') && ($camlim_xmin != NULL || $camlim_xmin != '')&& ($camlim_ymin != NULL || $camlim_ymin != '')&& ($camlim_zmin != NULL || $camlim_zmin != '') && ($camstart_x != NULL || $camstart_x != '') && ($camstart_y != NULL || $camstart_y != '') && ($camstart_z != NULL || $camstart_z != '') && ($camdir_x != NULL || $camdir_x != '') && ($camdir_y != NULL || $camdir_y != '') && ($camdir_z != NULL || $camdir_z != '') && ($camdir_x != NULL || $camdir_x != '')){
		//if(($camlim_xpos != NULL) || ($camlim_ypos != NULL) || ($camlim_xpos != NULL)|| ($camlim_zpos != NULL) || ($camlim_xmin != NULL)|| ($camlim_ymin != NULL)|| ($camlim_zmin != NULL) || ($camstart_x != NULL) || ($camstart_y != NULL) || ($camstart_z != NULL) || ($camdir_x != NULL) || ($camdir_y != NULL) || ($camdir_z != NULL) || ($camdir_x != NULL)){
		if(($camstart_x != NULL && $camstart_y != NULL && $camstart_z != NULL) || ($camlim_xmin != NULL && $camlim_xpos != NULL) || ($camlim_ymin != NULL && $camlim_ypos != NULL) || ($camlim_ymin != NULL && $camlim_ypos != NULL)){
		$camera = xml_add_child($world, "camera");

		if($camstart_x != NULL && $camstart_y != NULL && $camstart_z != NULL){
			$start = xml_add_child($camera, "start");

			xml_add_attribute($start, 'x', $camstart_x);	
			xml_add_attribute($start, 'y', $camstart_y);
			xml_add_attribute($start, 'z', $camstart_z);
			
		}

		if($camlim_xmin != NULL && $camlim_xpos != NULL){
			$limitx = xml_add_child($camera, "limitx");
			xml_add_attribute($limitx, 'min', $camlim_xmin);
			xml_add_attribute($limitx, 'max', $camlim_xpos);
		}
		if($camlim_ymin != NULL && $camlim_ypos != NULL){
			$limity = xml_add_child($camera, "limity");
			xml_add_attribute($limity, 'min', $camlim_ymin);
			xml_add_attribute($limity, 'max', $camlim_ypos);
		}

		if($camlim_ymin != NULL && $camlim_ypos != NULL){
			$limitz = xml_add_child($camera, "limitz");
			xml_add_attribute($limitz, 'min', $camlim_zmin);
			xml_add_attribute($limitz, 'max', $camlim_zpos);
		}

		if($camdir_x != NULL && $camdir_y != NULL && $camdir_z != NULL){
			$direction = xml_add_child($camera, "direction");

			xml_add_attribute($direction, 'x', $camdir_x);	
			xml_add_attribute($direction, 'y', $camdir_y);
			xml_add_attribute($direction, 'z', $camdir_z);
			
		}

		}
		//map
		$theplane = xml_add_child($world, "plane");
		$size = xml_add_child($theplane, "texture", $map->textureurl);

		$size = xml_add_child($theplane, "size");
		xml_add_attribute($size, 'width', $map->width);
		xml_add_attribute($size, 'height', $map->height);

		$rot = xml_add_child($theplane, "rot");
		xml_add_attribute($rot, 'x', $map->rot_x);
		xml_add_attribute($rot, 'y', $map->rot_y);
		xml_add_attribute($rot, 'z', $map->rot_z);

		$pos = xml_add_child($theplane, "pos");
		xml_add_attribute($pos, 'x', $map->pos_x);
		xml_add_attribute($pos, 'y', $map->pos_y);
		xml_add_attribute($pos, 'z', $map->pos_z);

		//mask
		foreach ($mask as $m) {
			//$themask = xml_add_child($world, "mask", substr($m->textureurl, strrpos($m->textureurl, '/')+1));
			$themask = xml_add_child($world, "mask", $m->textureurl);
			xml_add_attribute($themask, 'name', $m->name);
		}

		//Planes
		if(!empty($plane)){
		foreach ($plane as $p) {
				
				$theplane = xml_add_child($scene, "plane");
				$size = xml_add_child($theplane, "texture", $p->textureurl);

				$size = xml_add_child($theplane, "size");
				xml_add_attribute($size, 'width', $p->width);
				xml_add_attribute($size, 'height', $p->height);

				$rot = xml_add_child($theplane, "rot");
				xml_add_attribute($rot, 'x', $p->rot_x);
				xml_add_attribute($rot, 'y', $p->rot_y);
				xml_add_attribute($rot, 'z', $p->rot_z);

				$pos = xml_add_child($theplane, "pos");
				xml_add_attribute($pos, 'x', $p->pos_x);
				xml_add_attribute($pos, 'y', $p->pos_y);
				xml_add_attribute($pos, 'z', $p->pos_z);
			}

		}


		$bill_ani = array();
		$count = 0;
		foreach ($billboard_animation as $ba) {
			$bill_ani[$count]['a_id'] = $ba->animation_id;
			$bill_ani[$count]['b_id'] = $ba->billboard_id;
			$bill_ani[$count]['seed'] = $ba->seed;
			$count++;
		}

		/***Models****/
		foreach ($model as $m) {
			foreach ($model_world as $mw) {
				if($m->id == $mw->world_id){
					$themodel = xml_add_child($scene, "model");
					$size = xml_add_child($themodel, "filename", $m->obj_fileurl);
					$texture = xml_add_child($themodel, 'texture', substr($m->textureurl, strrpos($m->textureurl, '/')+1));

					foreach ($animation as $a) {
						if ($m->animation_id == $a->id){
							$animation = xml_add_child($themodel, "animation");
							xml_add_attribute($animation, 'name', $a->name);
						}
					}

					$mult = xml_add_child($themodel, "mult");
					xml_add_attribute($mult, 'count', $mw->mult_count);
					xml_add_attribute($mult, 'seed', $mw->mult_seed);
				}
			}
		}


		$world_billboards = array();
		/***Billboards****/
		/*The billboards that are present in billboard_world*/
		foreach ($billboard as $b) {
			foreach ($billboard_world as $bw) {
				if($bw->billboard_id == $b->id){
					array_push($world_billboards, $b->id);
					$thebillboard = xml_add_child($scene, "billboard");
					$texture = xml_add_child($thebillboard, "texture", substr($b->imgurl, strrpos($b->imgurl, '/')+1));
					$size = xml_add_child($thebillboard, "size");
					xml_add_attribute($size, 'width', $bw->pos_x);
					xml_add_attribute($size, 'height', $bw->pos_y);

					$mult = xml_add_child($thebillboard, "mult");
					xml_add_attribute($mult, 'count', $bw->mult_count);
					xml_add_attribute($mult, 'seed', $bw->mult_seed);

					foreach ($bill_ani as $ba) {
						if (isset($ba['b_id']) && $ba['b_id'] == $b->id){
							foreach ($animation as $a) {
								if ($ba['a_id'] == $a->id){
									$theanimation = xml_add_child($thebillboard, "animation");
									xml_add_attribute($theanimation, 'seed', $ba['seed']);
									xml_add_attribute($theanimation, 'name', $a->name);
								}
							}
						}
					}

					foreach ($mask as $m) {
						if($m->id == $bw->mask_id){
							$themask = xml_add_child($thebillboard, "mask");
							xml_add_attribute($themask, 'name', $m->name);
							break;
						}
					}
				}
			}
		}

		/***Illustrations, i.e. images draws by children****/
		foreach ($images as $image) {
			/***Size****/
			foreach ($billboard as $b) {
				if($b->id == $image->billboard_id){
					if(!in_array($b->id, $world_billboards)){ //if billboard is a world billboard, do not use as illustrations
						$illustration = xml_add_child($scene, "illustration");
			
						/***Artist name****/
						$name_artist = xml_add_child($illustration, "name_artist", $image->artist);

						/***Drawing name****/
						$name_drawing = xml_add_child($illustration, "name_drawing", $image->imgname);

						/***Description****/
						$description = xml_add_child($illustration, "description", $image->story);
						
						/***Sound****/
						$sound = xml_add_child($illustration, "sound", substr($image->soundurl, strrpos($image->soundurl, '/')+1));

						/***Postition****/
						$pos = xml_add_child($illustration, "pos");
						xml_add_attribute($pos, 'x', $image->pos_x);
						xml_add_attribute($pos, 'y', $image->pos_y);
						xml_add_attribute($pos, 'z', $image->pos_z);

						/***Image (texture)****/
						$texture = xml_add_child($illustration, "texture", substr($b->imgurl, strrpos($b->imgurl, '/')+1));

						foreach ($bill_ani as $ba) {
							if (isset($ba['b_id']) && $ba['b_id'] == $b->id){

								foreach ($animation as $a) {
									if ($ba['a_id'] == $a->id){
										$theanimation = xml_add_child($illustration, "animation");
										xml_add_attribute($theanimation, 'seed', $ba['seed']);
										xml_add_attribute($theanimation, 'name', $a->name);
									}
								}
							}
						}

						$size = xml_add_child($illustration, "size");
						xml_add_attribute($size, 'width', $b->size_x);
						xml_add_attribute($size, 'height', $b->size_x);
					}
				}
			}
		}

		return xml_print($dom, true);
	}


    function get_xml_file($world, $images, $plane, $model, $map, $mask, $group, $billboard_world, $billboard, $animation, $billboard_animation, $model_world) 
    {
    	$url = "uploads/scene.xml";
    	file_put_contents($url, $this->create_xml($world, $images, $plane, $model, $map, $mask, $group, $billboard_world, $billboard, $animation, $billboard_animation, $model_world));
		return $url;

	}
}
