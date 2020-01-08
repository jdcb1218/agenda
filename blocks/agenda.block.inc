<?php

/**
 * Implements hook_block_info().
 */

function agenda_block_info() {
  $blocks['modals'] = array(
    'info' => t('Request Modals'),
    'cache' => DRUPAL_NO_CACHE
  );

  $blocks['citas_ajax'] = array(
    'info' => t('Add citas ajax'),
    'cache' => DRUPAL_NO_CACHE
  );

  $blocks['my_qoute'] = array(
    'info' => t('My Qoute'),
    'cache' => DRUPAL_NO_CACHE
  );

  $blocks['list_consejeros'] = array(
    'info' => t('List Consejeros'),
    'cache' => DRUPAL_NO_CACHE
  );


 return $blocks;
}

/**
 * Implements hook_block_configure().
 */

function agenda_block_configure($delta = '') {
  $form = array();
  if ($delta == 'modals') {
	    $form['popup'] = array(
	      '#type' => 'textfield',
	      '#title' => t('Please write  form_id entity render'),
	      '#default_value' => variable_get('popup'),
	    );
      $form['link'] = array(
        '#type' => 'textfield',
        '#title' => t('Please write the name button'),
        '#default_value' => variable_get('link'),
      );

      $form['coute_free'] = array(
        '#type' => 'textfield',
        '#title' => t('Please write the name button second'),
        '#default_value' => variable_get('coute_free'),
        '#attributes' => array('class' => array('col-lg-12 col-sm-6')),
      );

      $form['coute_full'] = array(
        '#type' => 'textfield',
        '#title' => t('Please write the name button three'),
        '#default_value' => variable_get('coute_full'),
        '#attributes' => array('class' => array('col-lg-12 col-sm-6')),
      );

      $form['today'] = array(
        '#type' => 'textfield',
        '#title' => t('Please write the name button four'),
        '#default_value' => variable_get('today'),
        '#attributes' => array('class' => array('col-lg-12 col-sm-6')),
      );

      $form['content_type'] = array(
        '#type' => 'textfield',
        '#title' => t('Please write the machine_name Content Type'),
        '#default_value' => variable_get('content_type'),
        '#attributes' => array('class' => array('col-lg-12')),
      );            
  }
  return $form;
}

/**
 * Implementation of hook_block_save().
 */

function agenda_block_save($delta = '', $edit = array()) {
   switch ($delta) {
   	case 'modals':
   		variable_set('popup', $edit['popup']);
      variable_set('link',  $edit['link']);
      
      variable_set('coute_free',  $edit['coute_free']);
      variable_set('coute_full',  $edit['coute_full']);
      variable_set('today',  $edit['today']);

      variable_set('content_type',  $edit['content_type']);
   		break;
   }
}

/**
 * Implements hook_block_view().
 */

function agenda_block_view($delta = '') {
  $block = array();

  switch ($delta) {
    case 'modals':
      $block['content'] = modals_render();
      break;
 
     case 'citas_ajax':
       $block['content'] = drupal_get_form('agenda_records_form');
      break;

     case 'my_qoute':
       $block['content'] = drupal_get_form('agenda_qoute_form');
      break;

     case 'list_consejeros':
       $block['content'] = drupal_get_form('agenda_list_consejeros_form');
      break;      
  }
  return $block;
}


function modals_render(){
   $block = array();

   ctools_include('modal');
   ctools_modal_add_js(); 
   
  $block['content']['popud'][] = array(
      '#prefix' => '<div id="magical-modal-link">' . l(variable_get('link'), 'request/nojs', 
                       array('attributes' => array('class' => 'ctools-use-modal'))),
      '#suffix' => '</div>',
   );


  $block['content']['coute_free'][] = array(
      '#prefix' => '<div class="col-lg-12 col-md-12 col-sm-6 col-xs-6 cupo-disponible"> <div class="caja-1"></div>' . t(variable_get('coute_free')),
      '#suffix' => '</div>',
   );

  $block['content']['coute_full'][] = array(
      '#prefix' => '<div class="col-lg-12 col-md-12 col-sm-6 col-xs-6 cupo-lleno"><div class="caja-2"></div>' . t(variable_get('coute_full')),
      '#suffix' => '</div>',
   );

  $block['content']['today'][] = array(
      '#prefix' => '<div class="col-lg-12 col-md-12 col-xs-12 hoy"> <div class="caja-3"></div>' . t(variable_get('today')),
      '#suffix' => '</div>',
   ); 

  return $block;
 }


