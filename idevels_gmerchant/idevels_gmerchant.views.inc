<?php
/**
 * @file
 * Views include file with views hooks.
 */

/**
 * Implementation of hook_views_plugins().
 */
function idevels_gmerchant_views_plugins() {
  $path = drupal_get_path('module', 'idevels_gmerchant');

  $style_defaults = array(
    'path' => $path . '/plugins',
    'parent' => 'idevels_gmerchant',
    'theme' => 'idevels_gmerchant',
    'theme path' => $path . '/theme',
    'theme file' => 'idevels_gmerchant.theme.inc',
    'uses row plugin' => FALSE,
    'uses fields' => TRUE,
    'uses options' => TRUE,
    'type' => 'data_export',
  );

  return array(
    'style' => array(
      'idevels_gmerchant_xml' => array(
        'title' => t('Gmerchant XML file'),
        'help' => t('Display the view as a txt file.'),
        'handler' => 'idevels_gmerchant_plugin_style_export_xml',
        'export headers' => array('Content-Type' => 'text/xml'),
        'export feed type' => 'xml',
        'export feed text' => 'XML',
        'export feed title' => 'title',
        'export feed link' => 'link',
        'export feed description' => 'description',
        'export feed file' => '%view.xml',
        'export feed icon' => drupal_get_path('module', 'views_data_export') . '/images/xml.png',
        'additional themes' => array(
          'idevels_gmerchant_xml_header' => 'style',
          'idevels_gmerchant_xml_body' => 'style',
          'idevels_gmerchant_xml_footer' => 'style',
        ),
        'additional themes base' => 'idevels_gmerchant_xml',
      ) + $style_defaults,
    ),
  );
}

/**
 * Implements hook_views_data().
 */
function idevels_gmerchant_views_data() {
  $data['idevels_gmerchant']['table']['group'] = t('Gmerchant export');
  
  $data['idevels_gmerchant']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'entity_id',
    ),
  );
  
  $data['idevels_gmerchant']['entity_id'] = array(
    'title' => t('Gmerchant content'),
    'help' => t('Gmerchantcontent that references a node.'),
    'relationship' => array(
      'base' => 'node',
      'field' => 'entity_id',
      'handler' => 'views_handler_relationship',
      'label' => t('gmerchant'),
    ),
  );

  $data['idevels_gmerchant']['product_type'] = array(
    'title' => t('Gmerchant product type'), 
    'help' => t('Type product in gmerchant'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'idevels_gwh_handler_filter_select_list',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['idevels_gmerchant']['product_description'] = array(
    'title' => t('Gmerchant product description'), 
    'help' => t('Description product in gmerchant'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'idevels_gwh_handler_filter_select_list',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  

  return $data;
}
