<?php

/**
 * @file
 * Ctools plugin file.
 */

/**
 * Defines idevels free buy course access plugin.
 */
$plugin = array(
  'title'             => t('idevels: Check price carent course'),
  'description'       => t('Controls access to output button free buy course, return TRUE when course price is zero'),
  'callback'          => 'idevels_finances_price_check',
  'required context'  => new ctools_context_required(t('Node'), 'node'),
  'summary'           => 'idevels_finances_check_price_value_ctools_summary',
);

/**
 * Check for schedule user.
 */
function idevels_finances_price_check ($conf, $context) {

  // Select corse price and check to zero.
  $nid = $context->data->nid;
  $node = node_load($nid);
  $field_price = field_get_items('node', $node, 'field_price');
  $price = $field_price[0]['amount']/100;

  if ($price == 0) {
    return TRUE;
  }
  else {
    return FALSE;
  }
}

/**
 * Provide a summary description based upon the age.
 */
function idevels_finances_check_price_value_ctools_summary ($conf, $context) {
  return t('Check price carent corse');
}

