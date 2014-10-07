<?php

/**
 * @file
 * Theme related functions for processing our output style plugins.
 *
 * Views bug: http://drupal.org/node/593336
 */

/**
 * Theme a feed link.
 *
 * This theme function uses the theme pattern system to allow it to be
 * overidden in a more specific manner. The options for overiding this include
 * providing per display id; per type; per display id and per type.
 *
 * e.g.
 * For the view "export_test" with the display "page_1" and the type "csv" you
 * would have the following options.
 *   views_data_export_feed_icon__export_test__page_1__csv
 *   views_data_export_feed_icon__export_test__page_1
 *   views_data_export_feed_icon__export_test__csv
 *   views_data_export_feed_icon__page_1__csv
 *   views_data_export_feed_icon__page_1
 *   views_data_export_feed_icon__csv
 *   views_data_export_feed_icon
 *
 * @ingroup themeable
 */
function theme_idevels_gmerchant_feed_icon($variables) {
  extract($variables, EXTR_SKIP);
  $url_options = array('html' => true);
  if ($query) {
    $url_options['query'] = $query;
  }
  $image = theme('image', array('path' => $image_path, 'alt' => $text, 'title' => $text));
  return l($image, $url, $url_options);
}


function template_preprocess_idevels_gmerchant(&$vars) {
  $vars['header'] = $vars['rows']['header'];
  $vars['body'] = $vars['rows']['body'];
  $vars['footer'] = $vars['rows']['footer'];

  $view     = $vars['view'];
  $fields   = &$view->field;
}

/**
 * Preprocess xml output template.
 */
function template_preprocess_idevels_gmerchant_xml_header(&$vars) {
  $vars['root_node'] = 'channel';
  $vars['feed_title'] = $vars['options']['feed_title'];
  $vars['feed_link'] = $vars['options']['feed_link'];
  $vars['feed_description'] = $vars['options']['feed_description'];
}

/**
 * Preprocess xml output template.
 */
function template_preprocess_idevels_gmerchant_xml_footer(&$vars) {
  $vars['root_node'] = 'channel';
}

/**
 * Preprocess xml output template.
 */
function template_preprocess_idevels_gmerchant_xml_body(&$vars) {
  _idevels_gmerchant_header_shared_preprocess($vars);
  // We support not outputting fields when they are empty, so indicate so.
  $vars['hide_empty_support'] = TRUE;
  _idevels_gmerchant_body_shared_preprocess($vars);

  $vars['item_node'] = 'item';

  foreach ($vars['themed_rows'] as $num => $row) {
    foreach ($row as $field => $content) {
      // Get the original image and convert uri to absolute.
      if ($field == 'field_image') {
        $images = explode(', ', $content);
        $original_image = array_shift($images);
        $content = file_create_url($original_image);
        if (!empty($images)) {
          array_walk($images, 'idevels_gmerchant_absolute_uri');
          $vars['themed_rows'][$num]['additional_image_link'] = $images;
        }
      }
      // Prevent double encoding of the ampersand. Look for the entities produced by check_plain().
      $content = preg_replace('/&(?!(amp|quot|#039|lt|gt);)/', '&amp;', $content);
      // Convert < and > to HTML entities.
      $content = str_replace(
        array('<', '>'),
        array('&lt;', '&gt;'),
        $content);
      $vars['themed_rows'][$num][$field] = $content;
    }
    $vars['themed_rows'][$num]['identifier_exists'] = 'FALSE';
    $vars['themed_rows'][$num]['condition'] = 'new';
  }

  foreach ($vars['header'] as $field => $header) {
    // If there is no field label, use 'no name'.
      if ($field == 'field_image') {
        $vars['xml_tag']['additional_image_link'] = 'g:additional_image_link';
      }
    if (empty($header)) {
      $header = 'no name';
    }
    if ($vars['options']['transform']) {
      switch ($vars['options']['transform_type']) {
        case 'dash':
          $vars['xml_tag'][$field] = str_replace(' ', '-', $header);
          break;
        case 'underline':
          $vars['xml_tag'][$field] = str_replace(' ', '_', $header);
          break;
        case 'camel':
          $vars['xml_tag'][$field] = str_replace(' ', '', ucwords(strtolower($header)));
          // Convert the very first character of the string to lowercase.
          $vars['xml_tag'][$field][0] = strtolower($vars['xml_tag'][$field][0]);
          break;
        case 'pascal':
          $vars['xml_tag'][$field] = str_replace(' ', '', ucwords(strtolower($header)));
          break;
      }
    }
    // We should always try to output valid XML.
    $vars['xml_tag'][$field] = _views_data_export_xml_tag_clean($vars['xml_tag'][$field]);
  }
  $vars['xml_tag']['identifier_exists'] = 'g:identifier_exists';
  $vars['xml_tag']['condition'] = 'g:condition';
}

/**
 * Shared helper function for export preprocess functions.
 */
function _idevels_gmerchant_header_shared_preprocess(&$vars) {
  $view     = $vars['view'];
  $fields   = &$view->field;

  $vars['header'] = array();
  foreach ($fields as $key => $field) {
    if (empty($field->options['exclude'])) {
      $vars['header'][$key] = check_plain($field->label());
    }
  }

}

/**
 * Shared helper function for export preprocess functions.
 */
function _idevels_gmerchant_body_shared_preprocess(&$vars) {
  $view     = $vars['view'];
  $fields   = &$view->field;
  $hide_empty_support = !empty($vars['hide_empty_support']);

  $rows = $vars['rows'];

  $vars['themed_rows'] = array();
  $keys = array_keys($fields);
  foreach ($rows as $num => $row) {
    $vars['themed_rows'][$num] = array();

    foreach ($keys as $id) {
      if (empty($fields[$id]->options['exclude'])) {
        $content = $view->style_plugin->rendered_fields[$num][$id];

        if ($hide_empty_support && !empty($fields[$id]->options['hide_empty'])) {
          if ($fields[$id]->is_value_empty($content, $fields[$id]->options['empty_zero'])) {
            continue;
          }
        }

        $vars['themed_rows'][$num][$id] = $content;
      }
    }
  }
}

/**
 * Function for generate absolute uri.
 */
function idevels_gmerchant_absolute_uri(&$item) {
  $item = file_create_url($item);
}
