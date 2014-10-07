<?php

/**
 * @file
 * Search box for exposed filters.
 */

define('TEORITICAL_LECTURE', 38);
define('PRACTICAL_LECTURE', 37);

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title'           => t('idevels: output lecture courses'),
  'description'     => t('Output lecture cources.'),
  'single'          => TRUE,
  'content_types'   => array('no_context_content_type'),
  'render callback' => 'idevels_finances_lecture_course_render',
  'edit form' => 'idevels_finances_block_edit_form',
  'category' => array(t('idevels'),-8),
);


/**
 * Generates example block edit form.
 */
function idevels_finances_block_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  // We don't want to use standart pane title functionallity.
  $form['override_title']['#access'] = FALSE;
  $form['override_title_text']['#access'] = FALSE;
  $form['override_title_markup']['#access'] = FALSE;
  $form['title_nid'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter content title'),
    '#autocomplete_path' => 'ctools_example/autocomplete',
    '#default_value' =>  $conf['title_nid'] ? $conf['title_nid'] : '',
  );
  $form['show_body'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show body'),
    '#default_value' =>  $conf['show_body'] ? TRUE : FALSE,
  );
  $form['display_title'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display title'),
    '#default_value' =>  $conf['display_title'] ? TRUE : FALSE,
  );
  $form['title_as_link'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display title as link'),
    '#default_value' =>  $conf['title_as_link'] ? TRUE : FALSE,
    '#states' => array(
      'visible' => array(
        ':input[name="display_title"]' => array('checked' => TRUE),
      ),
    ),
  );

  return $form;
}

/**
 * Submit handler for example block edit form.
 */
function idevels_finances_block_edit_form_submit($form, &$form_state) {
  foreach (array('title_nid', 'display_title', 'title_as_link', 'show_body') as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
}

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
function idevels_finances_lecture_course_render($subtype, $conf, $args, $contexts) {
  global $user;

  $block = new stdClass();
  $block->content = '';
  // Load node course.
  $nid = $args[0];
  $node = node_load($nid);


  $user_full = user_load($user->uid);
  $resolv = field_get_items('user', $user_full, 'field_resolved');
  foreach ($resolv as $k => $v) {
    $nids[] = $v['nid'];
  }
  // Select carent schedule user and output lecture was user have access.
  $schedul = db_select('schedule', 's')
    ->fields('s', array('sid'))
    ->condition('s.course', $nid)
    ->condition('s.user', $user->uid)
    ->execute()
    ->fetchAssoc();
  $node->content['field_lectures'] = array();
  $lecture_nid = field_get_items('node', $node, 'field_lectures');
  if (!isset($schedul['sid']) || empty($schedul['sid'])) {
    $schedul['sid'] = 0;
  }

  $squeue = field_get_items('node', $node, 'field_nodequeue_course_name');
  if (!empty($squeue[0]['value'])) {
    $queues = nodequeue_load_queue_by_name($squeue[0]['value']);
    if (!empty($queues)) {
      foreach ($lecture_nid as $k => $v) {
        $position = nodequeue_get_subqueue_position($queues->qid, $v['nid']);
        $lecture_nid[$position]['nid'] = $v['nid'];
      }
      unset($lecture_nid[0]);
      ksort($lecture_nid);
    }
  }
  // Select lecture user.
  foreach ($lecture_nid as $l) {

    $time = db_select('field_data_field_schedule', 'field_data_field_schedule')
      ->fields('field_data_field_schedule', array('field_schedule_url'))
      ->condition('field_schedule_title', $l['nid'])
      ->condition('entity_type', 'schedule')
      ->condition('entity_id', $schedul['sid'])
      ->condition('field_schedule_url', mktime (23, 0, 0, date("n"), date("j"), date("Y")), '<=')
      ->execute()
      ->fetchField();
    // Load node lecture cours.
    $node_lecture = node_load($l['nid']);
    // Get lecture type.
    $lecture_type_lang = field_language('node', $node_lecture, 'field_type');
    $lecture_type = $node_lecture->field_type[$lecture_type_lang][0]['tid'];
    $lecture_media = '';
    if (!empty($node_lecture->field_audio) || !empty($node_lecture->field_file) || !empty($node_lecture->field_video)) {
      $lecture_media = 'media_lecture';
    }
    // Checking type lecture and add class.
    if ($lecture_type == TEORITICAL_LECTURE) {
      $type_lecture = 'lecture_teoritical';
    }
    elseif ($lecture_type == PRACTICAL_LECTURE) {
      $type_lecture = 'lecture_practical';
    }
    if (node_access('view', $node_lecture) || $time) {
      $lecture_prefix = "<div class='field-items-lecture $type_lecture yes_access $lecture_media'>";
      $output .= $lecture_prefix . l($node_lecture->title, 'node/' . $l['nid'], array('attributes' => array('class' => 'link_lecture'))) . '</div>';
    }
    else {
      $lecture_prefix = "<div class='field-items-lecture $type_lecture not_acces $lecture_media'>";
      $output .= $lecture_prefix . $node_lecture->title . '</div>';
    }
  }
  $output .= '</div>';
  $block->title = $conf['title_nid'];
  $block->content = render($output);
  // Returns an object block, which will be displayed in the panel.
  return $block;
}
