<?php


/**
 * Implements hook_form().
 */
function agenda_form_config($form, &$form_state) {

  $form['front_page'] = array(
    '#type' =>'checkbox', 
    '#title' => t('Enable $path user/login how front page'),
    '#default_value' => variable_get('config_agenda_front_page'),
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/*
 *Implements Hook Submit
 */
function agenda_form_config_submit($form, &$form_state) {
  variable_set('config_agenda_front_page', $form_state['values']['front_page']);
}