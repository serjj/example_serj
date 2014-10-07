<?php

/**
 * @file
 * Ctools plugin file.
 */

/**
 * Defines idevels isset in commerce cart product access plugin.
 */
$plugin = array(
  'title' => t('idevels: Check price for zero'),
  'description' => t('Controls access to output price course, return FALSE when price product ecvil zero'),
  'callback' => 'idevels_finances_check_price',
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'summary' => 'idevels_finances_check_price_check_field_age_value_ctools_summary',
);

/**
 * Check price corces.
 */
function idevels_finances_check_price($conf, $context) {
  $lang = field_language('node', $context->data, 'field_price');
  $price = $context->data->field_price[$lang][0]['amount']/100;
  if ($price == 0) {
    return FALSE;
  }
  elseif ($price != 0) {
    return TRUE;
  }
}

/**
 * Provide a summary description based upon the age.
 */
function idevels_finances_check_price_check_field_age_value_ctools_summary ($conf, $context) {
  return t('Check price course');
}
