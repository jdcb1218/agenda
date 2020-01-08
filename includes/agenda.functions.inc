<?php 

/**
 * Implementation of function save_availability_without_repeating
 * for save availability sin epeating
 */

function save_availability_without_repeating($node) { 
     $node->title = $node->name . " - " . date('m-d-Y',$node->created);
     $wrapper = entity_metadata_wrapper('node', $node);
     $date = $wrapper->field_fecha->value();
     $time = date_format(date_create($date['value']), 'g:i A') . ' - ' . date_format(date_create($date['value2']), 'g:i A'); 
     $service = $wrapper->field_tipo_de_servicio->value()->name;
     $wrapper->field_operaciones->set($time . ' ' . $service); 	
}

function save_availability_monthly_repeating($node){
	$lugar = $node->field_lugar['und'][false]['value'];
	$cupos = $node->field_cupo['und'][false]['value'];
	$repeticion = $node->field_repeticion['und'][false]['tid'];
	Global $user;

	for($x = 0; $x <= 2; $x++){
		$node = entity_create('node', array('type' => 'disponibilidad'));
		$node->uid = $user->uid;
		$emw_node = entity_metadata_wrapper('node', $node);
		$emw_node->title = 'Test node';
		$emw_node->field_lugar = $lugar;
		$emw_node->field_cupo = $cupos;
		$emw_node->field_repeticion = 12;
		$emw_node->save();
	}
}

function agenda_save_node_tor_submit(&$form, &$form_state){
  	
  $form = array();
  ctools_include('modal');
  ctools_include('ajax');
  // Vars Globales 
  $z = 0;
  $cupo   = $form_state['values']['field_cupo']['und'][$z]['value'];
  $repeat = $form_state['values']['field_repeticion']['und'][$z]['tid']; 
  $tid_service = $form_state['values']['field_tipo_de_servicio']['und'][$z]['tid'];

    // Vars TOR SESSION 1
  $start_tor_one = $form_state['values']['field_tor_disciplinario_uno']['und'][$z]['field_fecha']['und'][$z]['value']; 
  $end_tor_one = $form_state['values']['field_tor_disciplinario_uno']['und'][$z]['field_fecha']['und'][$z]['value2'];
  $place_tor_one = $form_state['values']['field_tor_disciplinario_uno']['und'][$z]['field_lugar']['und'][$z]['value'];
  $hr_tor_one_st = $form_state['values']['field_tor_disciplinario_uno']['und'][$z]['field_horario_inicio']['und'][$z]['tid'];
  $hr_tor_one_fn = $form_state['values']['field_tor_disciplinario_uno']['und'][$z]['field_horario_fin']['und'][$z]['tid'];
    

    // Vars TOR SESSION 2
  $start_tor_two = $form_state['values']['field_tor_disciplinario_dos']['und'][$z]['field_fecha']['und'][$z]['value'];
  $end_tor_two = $form_state['values']['field_tor_disciplinario_dos']['und'][$z]['field_fecha']['und'][$z]['value2'];
  $place_tor_two = $form_state['values']['field_tor_disciplinario_dos']['und'][$z]['field_lugar']['und'][$z]['value'];
  $hr_tor_two_st = $form_state['values']['field_tor_disciplinario_dos']['und'][$z]['field_horario_inicio']['und'][$z]['tid'];
  $hr_tor_two_fn = $form_state['values']['field_tor_disciplinario_dos']['und'][$z]['field_horario_fin']['und'][$z]['tid'];

    //relation_tor_disiplinario 
    // CREATE Disponibilidad TOR SESSION 1. 
    $node = entity_create('node', array('type' => $form_state['values']['type']));
    $node->uid = $form_state['values']['uid'];
    $node->language = $form_state['values']['language'];
    $entity = entity_metadata_wrapper('node', $node);
    $entity->title->set('Taller TOR SESSION 1');
    $entity->field_fecha->set(array('value'  => $start_tor_one, 'value2' => $end_tor_one));
    $entity->field_lugar->set($place_tor_one);
    $entity->field_relation_tor_disiplinario->set($form_state['values']['created']);
    $entity->field_cupo->set($cupo);
    $entity->field_horario_inicio->set($hr_tor_one_st);
    $entity->field_horario_fin->set($hr_tor_one_fn);
    $entity->field_tipo_de_servicio->set($tid_service);
    $entity->field_repeticion->set($repeat);
    // Create Field Collections TOR DISIPLINARIO 1
    $collection = entity_create('field_collection_item', array('field_name' => 'field_tor_disciplinario_uno'));
    $collection->setHostEntity('node', $node);
    $tor_session_one = entity_metadata_wrapper('field_collection_item', $collection);
    $tor_session_one->field_lugar->set($place_tor_one);
    $tor_session_one->field_horario_inicio->set($hr_tor_one_st);
    $tor_session_one->field_horario_fin->set($hr_tor_one_fn);
    $tor_session_one->field_fecha->set(array('value'  => $start_tor_one,'value2' => $end_tor_one));
    $tor_session_one->save();
    // Create Field Collections TOR DISIPLINARIO 2
    $collection = entity_create('field_collection_item', array('field_name' => 'field_tor_disciplinario_dos'));
    $collection->setHostEntity('node', $node);
    $tor_session_dos = entity_metadata_wrapper('field_collection_item', $collection);
    $tor_session_dos->field_lugar->set($place_tor_two);
    $tor_session_dos->field_horario_inicio->set($hr_tor_two_st);
    $tor_session_dos->field_horario_fin->set($hr_tor_two_fn);
    $tor_session_dos->field_fecha->set(array('value'  => $start_tor_two,'value2' => $end_tor_two));
    $tor_session_dos->save();
    $entity->save();

    // CREATE Disponibilidad TOR SESSION 2. 
    $node = entity_create('node', array('type' => $form_state['values']['type']));
    $node->uid = $form_state['values']['uid'];
    $node->language = $form_state['values']['language'];
    $entity = entity_metadata_wrapper('node', $node);
    $entity->title->set('Taller TOR SESSION 2');
    $entity->field_fecha->set(array('value'  => $start_tor_two, 'value2' => $end_tor_two));
    $entity->field_lugar->set($place_tor_two);
    $entity->field_relation_tor_disiplinario->set($form_state['values']['created']);
    $entity->field_cupo->set($cupo);
    $entity->field_horario_inicio->set($hr_tor_two_st);
    $entity->field_horario_fin->set($hr_tor_two_fn);
    $entity->field_tipo_de_servicio->set($tid_service);
    $entity->field_repeticion->set($repeat);
    // Create Field Collections TOR DISIPLINARIO 1
    $collection = entity_create('field_collection_item', array('field_name' => 'field_tor_disciplinario_uno'));
    $collection->setHostEntity('node', $node);
    $tor_session_one = entity_metadata_wrapper('field_collection_item', $collection);
    $tor_session_one->field_lugar->set($place_tor_one);
    $tor_session_one->field_horario_inicio->set($hr_tor_one_st);
    $tor_session_one->field_horario_fin->set($hr_tor_one_fn);
    $tor_session_one->field_fecha->set(array('value'  => $start_tor_one,'value2' => $end_tor_one));
    $tor_session_one->save();
    // Create Field Collections TOR DISIPLINARIO 2
    $collection = entity_create('field_collection_item', array('field_name' => 'field_tor_disciplinario_dos'));
    $collection->setHostEntity('node', $node);
    $tor_session_dos = entity_metadata_wrapper('field_collection_item', $collection);
    $tor_session_dos->field_lugar->set($place_tor_two);
    $tor_session_dos->field_horario_inicio->set($hr_tor_two_st);
    $tor_session_dos->field_horario_fin->set($hr_tor_two_fn);
    $tor_session_dos->field_fecha->set(array('value'  => $start_tor_two,'value2' => $end_tor_two));
    $tor_session_dos->save();
    $entity->save();
}