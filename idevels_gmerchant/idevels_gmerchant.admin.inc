<?php

/**
 * @file
 * Admin page callback file for the idevels_gmerchant module.
 */

/**
 * Implements hook_form().
 */

/**
 * Implements hook_form().
 */
function idevels_gmerchant_store_admin_settings_form() {
  $form = array();

  $form['idevels_gmerchant_account_id'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Account ID'),
    '#size'          => 60,
    '#maxlength'     => 255,
    '#required'      => TRUE,
    '#default_value' => variable_get('idevels_gmerchant_account_id', ''),
  );

  $form['idevels_gmerchant_app_name'] = array(
    '#type'          => 'textfield',
    '#title'         => t('App Name'),
    '#size'          => 60,
    '#maxlength'     => 255,
    '#required'      => TRUE,
    '#default_value' => variable_get('idevels_gmerchant_app_name', ''),
  );
  
  $form['idevels_gmerchant_country'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Country'),
    '#size'          => 60,
    '#maxlength'     => 255,
    '#required'      => TRUE,
    '#default_value' => variable_get('idevels_gmerchant_country', ''),
  );
  
  $form['idevels_gmerchant_currency'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Currency'),
    '#size'          => 60,
    '#maxlength'     => 255,
    '#required'      => TRUE,
    '#default_value' => variable_get('idevels_gmerchant_currency', 'USD'),
  );
  
  $form['idevels_gmerchant_account_email'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Account Email'),
    '#size'          => 60,
    '#maxlength'     => 255,
    '#required'      => TRUE,
    '#default_value' => variable_get('idevels_gmerchant_account_email', ''),
  );
  
  $form['idevels_gmerchant_account_password'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Account Password'),
    '#size'          => 60,
    '#maxlength'     => 255,
    '#required'      => TRUE,
    '#default_value' => variable_get('idevels_gmerchant_account_password', ''),
  );

  return system_settings_form($form);
}
