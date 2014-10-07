<?php

/**
 * @file
 * Ctools plugin file.
 */

/**
 * Defines idevels isset in commerce cart product access plugin.
 */
$plugin = array(
  'title' => t('idevels: Check isset in cart carent product'),
  'description' => t('Controls access to output button buy course and subscribe to groups, return FALSE when user add product to cart'),
  'callback' => 'idevels_finances_cart_add_check',
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'summary' => 'idevels_finances_cart_add_check_field_age_value_ctools_summary',
);

/**
 * Check for added product to cart.
 */
function idevels_finances_cart_add_check($conf, $context) {
  global $user;
  $nid = $context->data->nid;
  $cart_data = commerce_cart_order_load($user->uid);
  $cart_isset = '';
  if ($cart_data) {
    $line_i = field_get_items('commerce_order', $cart_data, 'commerce_line_items');
    if (!empty($line_i)) {
      foreach ($line_i as $k => $l) {
        // Select line items id form order.
        $lid = $l['line_item_id'];
        $lini_obj = commerce_line_item_load($lid);

        // Select product id from line item object this order.
        $pr = field_get_items('commerce_line_item', $lini_obj, 'commerce_product');
        $pr_id = $pr[0]['product_id'];
        $prod = commerce_product_load($pr_id);
        // If the course is in the basket display a message.
        if ($nid == $prod->sku) {
          $cart_isset = 1;
          drupal_set_message(t('Course in busket already'));
          break;
        }
        else {
          $cart_isset = 0;
        }
      }
    }
  }
  if ($cart_isset == 0) {
    return FALSE;
  }
  elseif ($cart_isset == 1) {
    return TRUE;
  }
}

/**
 * Provide a summary description based upon the age.
 */
function idevels_finances_cart_add_check_field_age_value_ctools_summary ($conf, $context) {
  return t('Check isset in cart carent product');
}
