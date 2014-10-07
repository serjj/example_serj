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
  'title'           => t('idevels: output message free course'),
  'description'     => t('output message free cources.'),
  'single'          => TRUE,
  'content_types'   => array('no_context_content_type'),
  'render callback' => 'idevels_finances_free_course_render',
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
function idevels_finances_free_course_render ($subtype, $conf, $args, $contexts) {
  global $user;

  $block = new stdClass();
  $block->content = t('<strong>Course free</strong>');

  return $block;
}
