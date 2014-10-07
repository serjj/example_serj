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
  'title'           => t('idevels: output button withdrow courses'),
  'description'     => t('output button withdrow cources.'),
  'single'          => TRUE,
  'content_types'   => array('no_context_content_type'),
  'render callback' => 'idevels_finances_withdraw_course_render',
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
function idevels_finances_withdraw_course_render($subtype, $conf, $args, $contexts) {
  global $user;

  $block = new stdClass();
  $block->content = '';

  $nid = $args[0];
  $node = node_load($nid);

  $resault = db_select('schedule','s')
    ->fields('s',array('sid'))
    ->condition('s.course', $nid)
    ->condition('s.user', $user->uid)
    ->execute()
    ->fetchAll();
  foreach($resault as $s){
    $sid = $s->sid;
  }
  if(isset($sid)){
    $query = db_select('field_data_field_schedule', 'f');
    $query->innerJoin('schedule', 's', 's.sid = f.entity_id');
    $query->condition('s.user', $user->uid);
    $query->condition('s.sid', $sid);
    $query->condition('f.entity_type', 'schedule');
    $query->orderBy('f.field_schedule_url', 'ASC');
    $query->fields('f', array('field_schedule_url'));
    $first_lecture = $query->execute()->fetchField();
    if ($first_lecture > REQUEST_TIME) {
      if (function_exists('idevels_finances_withdraw_from_course_form')) {
        // Return block with form to withdtaw course.
        $block->content = drupal_get_form('idevels_finances_withdraw_from_course_form', $sid, $node);
      }
    }
  }
  return $block;
}

/**
 * Form for withdraw from the course.
 */
function idevels_finances_withdraw_from_course_form ($form, &$form_state, $sid, $node) {
  $form['sid'] = array(
    '#value'  => $sid,
    '#type'   => 'hidden',
  );
  $form['node'] = array(
    '#value'  => $node,
    '#type'   => 'hidden',
  );
  $form['submit'] = array(
    '#value'  => t('Withdraw from the course'),
    '#type'   => 'submit',
  );
  return $form;
}

/**
 * Form for withdraw from the course.
 */
function idevels_finances_withdraw_from_course_form_submit($form, &$form_state) {
  global $user;
  $account   = user_load($user->uid);
  $course    = $form_state['values']['node'];
  $price     = field_get_items('node', $course, 'field_price');
  $schedules = field_get_items('user', $account, 'field_schedule');
  $path      = 'schedule/' . $form_state['values']['sid'];
  // Add count users to course.
  $field_count_lect = field_language('node', $course, 'field_count_users');
  $course->field_count_users[$field_count_lect][0]['value'] = $course->field_count_users[$field_count_lect][0]['value'] - 1;
  node_save($course);

  // Delete from database courses user.
  foreach ($schedules as $k => $v) {
    $path = 'schedule/' . $form_state['values']['sid'];
    if ($path == $v['url']) {
      $lang = field_language('user', $account, 'field_schedule');
      unset($account->field_schedule[$lang][$k]);
    }
  }
  user_save($account);

  // Delete from schedule courses.
  entity_delete('schedule', $form_state['values']['sid']);

  // Return point users.
  $params = array(
    'uid'          => $user->uid,
    'approver_uid' => 1,
    'points'       => $price[0]['amount']/100,
    'operation'    => 'admin',
    'description'  => t('Withdraw from the course @title', array('@title' => $course->title)),
    'reference'    => '',
  );
  userpoints_userpointsapi($params);
}
