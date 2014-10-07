<?php

/**
 * @file
 * Search box for exposed filters.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title'           => t('idevels: output button free buy courses'),
  'description'     => t('output button free buy cources.'),
  'single'          => TRUE,
  'content_types'   => array('no_context_content_type'),
  'render callback' => 'idevels_finances_free_buy_course_render',
  'category' => array(t('idevels'),-9),
);


/**
 * Run-time rendering of the body of the block.
 *
 * @param String $subtype
 *   Panel Pane subtype name.
 * @param Array $conf
 *   Configuration as done at admin time.
 * @param Array $args
 *   Array of arguments.
 * @param String $contexts
 *   Context - in this case we don't have any.
 *
 * @return Object
 *   An object with at least title and content members.
 */
function idevels_finances_free_buy_course_render ($subtype, $conf, $args, $contexts) {
  global $user;

  $block = new stdClass();
  $block->content = '';

  $nid = $args[0];
  $node = node_load($nid);
  $uid = $user->uid;

  // Return block with form to withdtaw course.
  $block->content = drupal_get_form('idevels_finances_free_buy_course_form', $uid, $nid);
  return $block;
}

/**
 * Form for withdraw from the course.
 */
function idevels_finances_free_buy_course_form ($form, &$form_state, $uid, $nid) {
  $form['uid'] = array(
    '#value'  => $uid,
    '#type'   => 'hidden',
  );
  $form['nid'] = array(
    '#value'  => $nid,
    '#type'   => 'hidden',
  );
  $form['submit'] = array(
    '#value'  => t('Add course to schedule'),
    '#type'   => 'submit',
  );
  return $form;
}

/**
 * Form for withdraw from the course.
 */
function idevels_finances_free_buy_course_form_submit ($form, &$form_state) {
  $nid = $form_state['values']['nid'];
  $uid = $form_state['values']['uid'];

  // Call function was plays lecture in schedule to free course.
  idevels_finances_place_course ($nid, $uid);
}
