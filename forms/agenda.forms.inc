<?php 

define('FPC', 0); 
define('FCT', 1); 
define('FCA', 2); 
define('FCC', 3); 
define('FCP', 4);


// Form  for created quotes 
function agenda_records_form($form, &$form_state) {
 if (is_numeric(arg(1))) {
     $node = node_load(arg(1));
    if ($node->type == 'disponibilidad') {
         variable_set('nid', $node->nid);
         $wrapper = entity_metadata_wrapper('node', $node);
         variable_set('cupo', $wrapper->field_cupo->value());
    }
  } 
  $form['field_container'] = [
    '#type' => 'container',
    '#weight' => 80,
    '#tree' => TRUE,
    '#prefix' => '<div id="js-ajax-elements-wrapper">',
    '#suffix' => '</div>',
  ];
  $form_state['field_deltas'] = isset($form_state['field_deltas']) ? $form_state['field_deltas'] : range(0, 0);
  $field_count = $form_state['field_deltas'];
  $form['field_container']['add_name'] = [
    '#type' => 'submit',
    '#value' => t('Add'),
    '#submit' => ['agenda_ajax_example_add_more_add_one'],
    '#ajax' => [
      'callback' => 'agenda_ajax_example_add_more_add_one_callback',
      'wrapper' => 'js-ajax-elements-wrapper',
    ],
  ];

  foreach ($field_count as $delta) {
    if ($delta > 0 && $delta <= variable_get('cupo')) {
        $form['field_container'][$delta] = [
          '#type' => 'container',
          '#attributes' => [
            'class' => ['container-inline container'],
          ],
          '#tree' => TRUE,
        ];

        $form['field_container'][$delta]['uid'] = [
          '#type' => 'textfield',
          '#title' => t('Uid'),
          '#size' => 10,
        ];

        $form['field_container'][$delta]['name'] = [
          '#type' => 'textfield',
          '#title' => t('Name'),
          '#size' => 10,
        ];

        $form['field_container'][$delta]['codec'] = [
          '#type' => 'textfield',
          '#title' => t('Codigo'),
          '#size' => 10,
        ];

        $form['field_container'][$delta]['email'] = [
          '#type' => 'textfield',
          '#title' => t('Usuario'),
          '#size' => 10,
        ];

        $form['field_container'][$delta]['motivo'] = [
          '#type' => 'textfield',
          '#title' => t('Motivo de consulta'),
          '#size' => 10,
        ];


        $form['field_container'][$delta]['remove_name'] = [
          '#type' => 'submit',
          '#value' => t('Cancelar Cita'),
          '#prefix' => '<div id="disable-quote"><label>Cancelar citas</label>',
          '#suffix' => '</div>',
          '#submit' => ['agenda_ajax_example_add_more_remove'],
          '#ajax' => [
            'callback' => 'agenda_ajax_example_add_more_remove_callback',
            'wrapper' => 'js-ajax-elements-wrapper',
          ],
          '#attributes' => [
            'class' => ['button-small'],
          ],
          '#name' => 'remove_name_' . $delta,
        ];
      }
  }

    $form['submit'] = [
      '#type' => 'submit',
      '#value' => t('Save'),
      '#ajax' => [
        'callback' => 'agenda_records_form_submit',
        'wrapper' => 'js-ajax-elements-wrapper',
       ],
      '#attributes' => [
        'class' => ['ctools-use-modal'],
      ],        
    ];

    ctools_include('modal');
    ctools_modal_add_js();

    $form['cancelar'] = [
      '#type' => 'submit',
      '#value' => t('Cancel'),
      '#ajax' => [
        'callback' => 'agenda_records_cancel_submit',
        'wrapper' => 'js-ajax-elements-wrapper',
       ], 
    ];

   return $form;
}

function agenda_ajax_example_add_more_remove($form, &$form_state) {
  $delta_remove = $form_state['triggering_element']['#parents'][1];
  $k = array_search($delta_remove, $form_state['field_deltas']);
  unset($form_state['field_deltas'][$k]);

  $form_state['rebuild'] = TRUE;
  drupal_get_messages();
}

function agenda_ajax_example_add_more_remove_callback($form, &$form_state) {
  return $form['field_container'];
}

function agenda_ajax_example_add_more_add_one($form, &$form_state) {
   drupal_add_js(array('agenda' => array('nodo' => variable_get('nid'))), array('type' => 'setting'));
   drupal_add_js(drupal_get_path('module', 'agenda') . '/js/agenda.js');

   $form_state['field_deltas'][] = count($form_state['field_deltas']) > 0 ? max($form_state['field_deltas']) + 1 : 0;
   $form_state['rebuild'] = TRUE;
   drupal_get_messages();
}

function agenda_ajax_example_add_more_add_one_callback($form, $form_state) {
  return $form['field_container'];
}


function agenda_records_form_validate($form, &$form_state) {
   
    Global $user;
    $usuario = entity_metadata_wrapper('user', $user->uid);

    // Load Uids Insert for availability 
    foreach ($form_state['values']['field_container'] as $key => $value) {
        if(is_numeric($value['uid'])){
            $uids[] = trim($value['uid']);           
        }
    }

    $node = node_load(variable_get('nid'));
    $wrapper = entity_metadata_wrapper('node',$node);     

    // Check fieldcollections with  Uids Insert
    foreach ($wrapper->field_citas_agenda->value() as $key => $value) {
      $cwrapper = entity_metadata_wrapper('field_collection_item', $value);
      $check_user_isset =  array_search($cwrapper->field_collec_uid->value(), $uids);
      unset($uids[$check_user_isset]);
    }  

    $form_state['storage']['uids'] = [$uids];
}

 
function agenda_records_form_submit($form, &$form_state) {
    foreach ($form_state['values']['field_container'] as $key => $value) {
       $uid = trim($value['uid']); $tid = trim($value['motivo']);
       if (is_numeric($uid)) {
           $data[] = agenda_save_users($uid,variable_get('nid'),$tid);
       }
    }
    ctools_include('ajax'); ctools_include('modal');
    $form_state = array(
      'ajax' => TRUE,
      'title' => t('Gracias'),
    );

    if (in_array(FALSE, $data) == TRUE) {
      $output = ctools_modal_form_wrapper('quote_thx_form', $form_state);
      print ajax_render($output);
      drupal_exit();
    }else{
      $output = ctools_modal_form_wrapper('quote_isset_form', $form_state);
      print ajax_render($output);
      drupal_exit();      
    }
}

function agenda_save_users($uid, $nid, $tid){
      $node = node_load($nid);
      $user = user_load($uid);
      $uwrapper = entity_metadata_wrapper('user', $user);
      $wrapper = entity_metadata_wrapper('node',$node);
      
      $servicio = $wrapper->field_tipo_de_servicio->value();
      

      $data_uids = explode(',',$wrapper->field_profile->value());
      $search = in_array($uwrapper->field_codigo->value(),$data_uids);

      if ($search == FALSE && $servicio->name != 'TOR Obligatorio Disciplinario') {
          $wrapper->field_profile->set($wrapper->field_profile->value(). ',' .$uwrapper->field_codigo->value());
          $collection = entity_create('field_collection_item', array('field_name' => 'field_citas_agenda'));
          $collection->setHostEntity('node', $node);
          $quote = entity_metadata_wrapper('field_collection_item', $collection);
          $quote->field_collec_nombre->set($uwrapper->field_nombre->value());
          $quote->field_collec_apellido->set($uwrapper->field_apellido->value());
          $quote->field_collec_codigo->set($uwrapper->field_codigo->value());
          $quote->field_collec_uid->set($user->uid);
          $quote->field_collec_usuario->set($uwrapper->field_email->value());
          $quote->field_collec_numero_de_documento->set($uwrapper->field_numero_de_documento->value());
          if (!empty($tid)){ $quote->field_collec_motivo->set($tid);} 
          $quote->save();
          $wrapper->save(); 
      }
      if ($search == FALSE && $servicio->name == 'TOR Obligatorio Disciplinario') {
          $id_tor_session = $wrapper->field_relation_tor_disiplinario->value();
          $query = new EntityFieldQuery();
          $query->entityCondition('entity_type', 'node')
            ->entityCondition('bundle', 'disponibilidad')
            ->fieldCondition('field_relation_tor_disiplinario', 'value', $id_tor_session , '=');
          $result = $query->execute();
          foreach ($result['node'] as $key => $value) {
                $node = node_load($value->nid);
                $wrapper = entity_metadata_wrapper('node',$node);
                $wrapper->field_profile->set($wrapper->field_profile->value(). ',' .$uwrapper->field_codigo->value());
                $collection = entity_create('field_collection_item', array('field_name' => 'field_citas_agenda'));
                $collection->setHostEntity('node', $node);
                $quote = entity_metadata_wrapper('field_collection_item', $collection);
                $quote->field_collec_nombre->set($uwrapper->field_nombre->value());
                $quote->field_collec_apellido->set($uwrapper->field_apellido->value());
                $quote->field_collec_codigo->set($uwrapper->field_codigo->value());
                $quote->field_collec_uid->set($user->uid);
                $quote->field_collec_usuario->set($uwrapper->field_email->value());
                $quote->field_collec_numero_de_documento->set($uwrapper->field_numero_de_documento->value());
                if (!empty($tid)){ $quote->field_collec_motivo->set($tid);} 
                $quote->save();
                $wrapper->save();                
          }
      }
      return $search;   
}

function agenda_qoute_form($form, &$form_state){

  $form['back'] = array(
      '#type'=> 'item',
      '#prefix' => '<div class="coment-mobil">',
      '#markup' => '<input type="button" value="Back" onclick="goBack()"><span>Citas</span>',
      '#suffix' => '</div>',
  );

  $form['options_qoute'] = [
      '#type'          => 'select',
      '#default_value' => variable_get('options_qoute'),
      '#options'       => [
        FPC => t('Filtrar por'),
        FCT => t('Todas las citas'), 
        FCA => t('Citas abiertas'),  
        FCC => t('Citas cerradas'),
        FCP => t('Citas pendientes'), 
      ],

      '#attributes'    => [
        'onChange' => 'this.form.submit();',
      ],
    ];

    $form['complete_projects_submit'] = [
      '#type'       => 'submit',
      '#value'      => t('Apply'),
      // The submit itself is necessary, but now it can be hidden:
      '#attributes' => [
        'style' => ['display: none;'],
      ],
    ];
  return $form;
}

function agenda_qoute_form_submit($form, &$form_state){
  variable_set('options_qoute', $form_state['values']['options_qoute']);
}

/**
 * Implements hook_form() for delete node(obj) bundle (availability).
 */

function agenda_form($form, &$form_state) {
  $form = array();
 
  $form['from'] = array(
   '#type'=> 'item',
   '#markup' => t('Seguro que desea eliminar la disponibilidad'),
 );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Aceptar'),
  );
  return $form;
}

/**
 * Implements hook_form_submit() delete node bundle (availability).
 */

function agenda_form_submit($form, &$form_state) {
  $form = array();
  ctools_include('modal');
  ctools_include('ajax');
  $node = node_load($form_state["nid"]);
  $wrapper = entity_metadata_wrapper('node', $node);
  $service = $wrapper->field_tipo_de_servicio->value();
      
  if ($node->type == 'disponibilidad' && $service->name == 'TOR Obligatorio Disciplinario') {
      $id_tor_session = $wrapper->field_relation_tor_disiplinario->value();
      $query = new EntityFieldQuery();
      $query->entityCondition('entity_type', 'node')
        ->entityCondition('bundle', 'disponibilidad')
        ->fieldCondition('field_relation_tor_disiplinario', 'value', $id_tor_session , '=');
      $result = $query->execute();
      foreach ($result['node'] as $key => $value) {
        node_delete($value->nid);
      }
  }
  node_delete($form_state["nid"]);
  $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
  $form_state['ajax_commands'][] = ctools_ajax_command_reload();
  return $form;
}

function agenda_records_cancel_submit($form, &$form_state) {
  ctools_include('ajax');
  ctools_add_js('ajax-responder');
  // Path to redirect to
  $commands[] = ctools_ajax_command_redirect('crear/'.variable_get('nid').'/citas');
  print ajax_render($commands);
  return drupal_exit();
}



function quotes_delete_form($form, &$form_state){
  $form = array();
 
  $form['from'] = array(
   '#type'=> 'item',
   '#markup' => t('Seguro que deseas cancelar la cita'),
 );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Aceptar'),
  );
  return $form;  
}

function quotes_delete_form_submit($form, &$form_state){
      $cwrapper = entity_metadata_wrapper('field_collection_item', $form_state['fcid']);
      $query = new EntityFieldQuery();
      $query->entityCondition('entity_type', 'node')
        ->entityCondition('bundle', 'disponibilidad')
        ->fieldCondition('field_citas_agenda', 'value',  $form_state['fcid'], '='); 
      $result = $query->execute();

      $quote = reset($result['node']); $node = node_load($quote->nid);
      $wrapper = entity_metadata_wrapper('node', $node);
      $servicio = $wrapper->field_tipo_de_servicio->value();

     if ($servicio->name == 'TOR Obligatorio Disciplinario') {
          $id_tor_session = $wrapper->field_relation_tor_disiplinario->value();
          $query = new EntityFieldQuery();
          $query->entityCondition('entity_type', 'node')
            ->entityCondition('bundle', 'disponibilidad')
            ->fieldCondition('field_relation_tor_disiplinario', 'value', $id_tor_session , '=');
          $result = $query->execute();
          foreach ($result['node'] as $key => $nodo) {
              $node = node_load($nodo->nid);
              $wrapper = entity_metadata_wrapper('node', $node);
              foreach ($node->field_citas_agenda['und'] as $key => $value) {
                $wrapper_quotes = entity_metadata_wrapper('field_collection_item', $value['value']);
                if ($wrapper_quotes->field_collec_codigo->value() == $cwrapper->field_collec_codigo->value()) {
                    $remove_string = str_replace($wrapper_quotes->field_collec_codigo->value(), '', $wrapper->field_profile->value());
                      $wrapper->field_profile->set($remove_string);
                      $wrapper->save();
                      entity_delete('field_collection_item', array($value['value']));
                }
              }
          }
     }else{
        $remove_string = str_replace($cwrapper->field_collec_codigo->value(), '', $wrapper->field_profile->value());
        $wrapper->field_profile->set($remove_string);
        $wrapper->save();
        entity_delete('field_collection_item', array($form_state['fcid']));
    } 
        $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
        $form_state['ajax_commands'][] = ctools_ajax_command_reload(); 
        return $form; 
  }

function quotes_list_form($form, &$form_state){
    foreach (explode("-",$form_state['storage']) as $key => $value) {
      if (is_numeric($value)) {
          $node = node_load($value);
          $wrapper = entity_metadata_wrapper('node',$node);
            if (isset($wrapper->field_tipo_de_servicio->value()->tid)) {
                  $hora = explode(" ",$wrapper->field_fecha->value()['value']);
                  $hora_end = explode(" ",$wrapper->field_fecha->value()['value2']);
                  $join_hora = date("g:i a",strtotime($hora[1])).' '.date("g:i a",strtotime($hora_end[1]));
                  $servicio = taxonomy_term_load($wrapper->field_tipo_de_servicio->value()->tid);
                  $servicios .= '<li>'.$join_hora.' | '.$servicio->name.'</li>';
            }        
      }
    }
    $form['back'] = array(
        '#type'=> 'item',
        '#prefix' => '<ul>',
        '#markup' =>  $servicios,
        '#suffix' => '</ul>',
    );
  return $form;
}


function agenda_list_consejeros_form($form, &$form_state){

    $role = user_role_load_by_name('consejero');
    $uids = db_select('users_roles', 'ur')
        ->fields('ur', array('uid'))
        ->condition('ur.rid', $role->rid, '=')
        ->execute()
        ->fetchCol();
    $users = user_load_multiple($uids);
    
    foreach ($users as $value) {
       $usuarios['data']['all'] = t('Selecciona el consejero');
       $usuarios['data'][$value->uid] = $value->name;
    }

  $args = arg(); $uid = array_pop($args);
 
   $form['select_list_consejero'] = array(
      '#type'          => 'select',
      '#default_value' => ($uid == 'all') ? $uid : variable_get('select_list_consejero'),
      '#options'        => $usuarios['data'],
      '#attributes'    => array(
        'onChange' => 'this.form.submit();',
      ),
    );

    $form['select_list_consejero_submit'] = array(
      '#type'       => 'submit',
      '#value'      => t('Apply'),
      '#attributes' =>  array(
        'style' => array('display: none;'),
      ),
    );

    return $form;
}

function agenda_list_consejeros_form_submit($form, &$form_state){
    variable_set('select_list_consejero',$form_state['values']['select_list_consejero']);
    $args = arg(); $url = array_pop($args);
    drupal_goto(implode('/',$args) . '/' . $form_state['values']['select_list_consejero']);
}


function agenda_add_quotes_students_form($form, &$form_state){
  $output = arg(1); $nodos = explode("-", $output);

  ctools_include('ajax'); ctools_include('modal'); 

  foreach ($nodos as $key => $value) {
    $node = node_load($value);
    $user = user_load($node->uid);
    $wrapper = entity_metadata_wrapper('node', $node);
    $hora_start = $wrapper->field_horario_inicio->value();
    $hora_end = $wrapper->field_horario_fin ->value();
    $time = $hora_start->name .' a '. $hora_end->name;

    $form['info_consejeros_enabled'] = array(
      '#type' => 'item',
      '#markup' => t('Consejeros Disponibles'),
    );

    $form['strorage'][$key][$value] = array(
      '#type' => 'checkbox',
      '#title' => t($user->name .' | ' .$time),
    );
   }
 
   $query = new EntityFieldQuery();
   $query->entityCondition('entity_type','taxonomy_term')
          ->entityCondition('bundle','motivos_consulta_estudiante')
          ->propertyCondition('name', $wrapper->field_tipo_de_servicio->value()->name);
   $results = $query->execute();
   $parent = reset($results['taxonomy_term']);


    $result = db_select('taxonomy_term_hierarchy', 'n')
                      ->fields('n',array('tid','parent'))
                      ->condition('parent', $parent->tid)
                      ->execute();
    $data = array(); 
    while($row=$result->fetchAssoc()) {
          $term = taxonomy_term_load($row['tid']);
          $data['services_students'][$term->tid] = $term->name;
    }

   $form['selected_reason_student'] = array(
       '#type' => 'select',
       '#options' => $data['services_students'],
       '#required' => TRUE,
   );
  
  $form['infor_quotes'] = array(
    '#type' => 'markup',
    '#prefix' => '<div class="info-quote-student-modal">',
    '#markup' => t('Si separa una cita y no puede asistir debe cancelar'),
    '#suffix' => '</div>',
  );

  $form['#attributes'] = array('class' => array('availability-quotes-students'));

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Crear cita',
  );

  return $form;
}

function agenda_add_quotes_students_form_validate($form, &$form_state){
    Global $user;
    $usuario = entity_metadata_wrapper('user', $user->uid);
    foreach ($form_state['input'] as $key => $value) {
      if(is_numeric($key) && is_numeric($value)){
            ctools_include('ajax'); ctools_include('modal'); 
            $node = node_load($key);
            $wrapper = entity_metadata_wrapper('node',$node);
            foreach ($wrapper->field_citas_agenda->value() as $key => $value) {
              $cwrapper = entity_metadata_wrapper('field_collection_item', $value);
              if ($cwrapper->field_collec_uid->value() == $user->uid) {
                return quotes_isset();
              }
            }
      }
    }   
}

function agenda_add_quotes_students_form_submit($form, &$form_state){
    Global $user;
    $usuario = entity_metadata_wrapper('user', $user->uid);
    foreach ($form_state['input'] as $key => $value) {
      if(is_numeric($key) && is_numeric($value)){
        ctools_include('ajax'); ctools_include('modal'); 
        $node = node_load($key);
        $wrapper = entity_metadata_wrapper('node',$node);
          if (count($wrapper->field_citas_agenda->value()) < $wrapper->field_cupo->value()) {
            $wrapper->field_profile->set($wrapper->field_profile->value(). ',' .$usuario->field_codigo->value());
            $collection = entity_create('field_collection_item', array('field_name' => 'field_citas_agenda'));
            $collection->setHostEntity('node', $node);
            $quote = entity_metadata_wrapper('field_collection_item', $collection);
            $quote->field_collec_nombre->set($usuario->field_nombre->value());
            $quote->field_collec_apellido->set($usuario->field_apellido->value());
            $quote->field_collec_codigo->set($usuario->field_codigo->value());
            $quote->field_collec_uid->set($user->uid);
            $quote->field_collec_usuario->set($usuario->field_nombre->value());
            $quote->field_collec_numero_de_documento->set($usuario->field_numero_de_documento->value());
            $quote->field_collec_motivo->set($form_state['values']['selected_reason_student']);
            $quote->save();
            $wrapper->save();
            return quotes_created();          
          }else{
            return availabilitys_full(); 
          }
      }
  }
} 


function quote_thx_form(){
  $form['thx_quote'] = array(
    '#prefix' => '<div class="quote-thx">',
    '#markup' => t('Tu cita(s) se ha registrado'),
    '#suffix' => '</div>', 
  );
  return $form;
} 

function quote_isset_form(){
  $form['thx_quote'] = array(
    '#prefix' => '<div class="quote-thx">',
    '#markup' => t('Ya existe una cita asociada a esta disponibilidad'),
    '#suffix' => '</div>', 
  );
  return $form;
} 

function availabilitys_full_form(){
  $form['availabilitys_full'] = array(
    '#prefix' => '<div class="availabilitys-full">',
    '#markup' => t('Esta disponibilidad ya se encuentra llena'),
    '#suffix' => '</div>', 
  );
  return $form;
}

function created_availabilitys_form($form, &$form_state){
      
    $form['enlace'] = array(
      '#prefix' => '<div class="availabilitys-full">',
      '#markup' => l('X', 'calendario-consejero/diario'),
      '#suffix' => '</div>', 
    );

    $form['availabilitys_full'] = array(
      '#prefix' => '<div class="availabilitys-full">',
      '#markup' => t('Tu disponibilidad'),
      '#suffix' => '</div>', 
    );
    
  return $form;
}