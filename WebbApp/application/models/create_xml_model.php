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
		$thePlane =  $plane->textureurl;
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
		$camera = xml_add_child($world, "camera");
		$start = xml_add_child($camera, "start");
		xml_add_attribute($start, 'x', $camstart_x);
		xml_add_attribute($start, 'y', $camstart_y);
		xml_add_attribute($start, 'z', $camstart_z);

		$limitx = xml_add_child($camera, "limitx");
		xml_add_attribute($limitx, 'min', $camlim_xmin);
		xml_add_attribute($limitx, 'max', $camlim_xpos);

		$limity = xml_add_child($camera, "limity");
		xml_add_attribute($limity, 'min', $camlim_ymin);
		xml_add_attribute($limity, 'max', $camlim_ypos);

		$limitz = xml_add_child($camera, "limitz");
		xml_add_attribute($limitz, 'min', $camlim_zmin);
		xml_add_attribute($limitz, 'max', $camlim_zpos);

		//plane
		$theplane = xml_add_child($world, "plane");
		$size = xml_add_child($theplane, "texture", $plane->textureurl);

		$size = xml_add_child($theplane, "size");
		xml_add_attribute($size, 'width', $plane->width);
		xml_add_attribute($size, 'height', $plane->height);

		$rot = xml_add_child($theplane, "rot");
		xml_add_attribute($rot, 'x', $plane->rot_x);
		xml_add_attribute($rot, 'y', $plane->rot_y);
		xml_add_attribute($rot, 'z', $plane->rot_z);

		$pos = xml_add_child($theplane, "pos");
		xml_add_attribute($pos, 'x', $plane->pos_x);
		xml_add_attribute($pos, 'y', $plane->pos_y);
		xml_add_attribute($pos, 'z', $plane->pos_z);

		//mask
		foreach ($mask as $m) {
			$themask = xml_add_child($world, "mask", substr($m->textureurl, strrpos($m->textureurl, '/')+1));
			xml_add_attribute($themask, 'name', $m->name);
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
					xml_add_attribute($size, 'x', $bw->pos_x);
					xml_add_attribute($size, 'z', $bw->pos_y);

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
						xml_add_attribute($size, 'x', $b->size_x);
						xml_add_attribute($size, 'y', $b->size_x);
					}
				}
			}
		}

		return xml_print($dom, true);
	}


    function get_xml_file($world, $images, $plane, $model, $map, $mask, $group, $billboard_world, $billboard, $animation, $billboard_animation, $model_world) 
    {
    	$url = "uploads/out/scene.xml";
    	file_put_contents($url, $this->create_xml($world, $images, $plane, $model, $map, $mask, $group, $billboard_world, $billboard, $animation, $billboard_animation, $model_world));
		return $url;

	}
}
