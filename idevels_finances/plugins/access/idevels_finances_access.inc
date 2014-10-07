<?php

/**
 * @file
 * Ctools plugin file.
 */

/**
 * Defines idevels lecture in course access plugin.
 */
$plugin = array(
  'title'             => t('idevels: Check schedule carent user'),
  'description'       => t('Controls access to output button buy course, return TRUE when user have in schedule this course'),
  'callback'          => 'idevels_finances_schedule_access_check',
  'required context'  => new ctools_context_required(t('Node'), 'node'),
  'summary'           => 'idevels_finances_schedule_access_check_value_ctools_summary',
);

/**
 * Check for schedule user.
 */
function idevels_finances_schedule_access_check($conf, $context) {
  global $user;
  $nid = $context->data->nid;

  $sid = db_select('schedule', 's')
    ->fields('s', array('sid'))
    ->condition('s.course', $nid)
    ->condition('s.user', $user->uid)
    ->execute()
    ->fetchAssoc();
  if (empty($sid)) {
    return TRUE;
  }
  else {
    return FALSE;
  }
}

/**
 * Provide a summary description based upon the age.
 */
function idevels_finances_schedule_access_check_value_ctools_summary ($conf, $context) {
  return t('Check schedule carent user');
}

