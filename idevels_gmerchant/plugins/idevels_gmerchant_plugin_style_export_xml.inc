<?php
/**
 * @file
 * Plugin include file for export style plugin.
 */

/**
 * Generalized style plugin for export plugins.
 *
 * @ingroup views_style_plugins
 */
class idevels_gmerchant_plugin_style_export_xml extends views_data_export_plugin_style_export {

  /**
   * Set options fields and default values.
   *
   * @return
   * An array of options information.
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['transform'] = array(
      'default' => TRUE,
      'translatable' => FALSE,
    );
    $options['transform_type'] = array(
      'default' => 'dash',
      'translatable' => FALSE,
    );
    $options['feed_title'] = array(
      'default' => $this->definition['export feed title'],
      'translatable' => TRUE,
    );
    $options['feed_link'] = array(
      'default' => $this->definition['export feed link'],
      'translatable' => TRUE,
    );
    $options['feed_description'] = array(
      'default' => $this->definition['export feed description'],
      'translatable' => TRUE,
    );

    return $options;
  }

  /**
   * Options form mini callback.
   *
   * @param $form
   * Form array to add additional fields to.
   * @param $form_state
   * State of the form.
   * @return
   * None.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['transform'] = array(
      '#type' => 'checkbox',
      '#title' => t('Transform spaces'),
      '#default_value' => $this->options['transform'],
      '#description' => t('Transform spaces to valid XML in field labels (spaces create invalid XML markup). Note that invalid XML tag characters will always be converted.'),
    );
    $form['transform_type'] = array(
      '#type' => 'select',
      '#title' => t('Transform type'),
      '#default_value' => $this->options['transform_type'],
      '#options' => array(
        'dash' => t('Dash'),
        'underline' => t('Underline'),
        'camel' => t('camelCase'),
        'pascal' => t('PascalCase'),
      ),
      '#process' => array('ctools_dependent_process'),
      '#dependency' => array(
        'edit-style-options-transform' => array(TRUE),
      ),
    );
    $form['feed_title'] = array(
      '#type' => 'textfield',
      '#title' => t('Your feed title'),
      '#default_value' => $this->options['feed_title'],
      '#required' => TRUE,
    );
    $form['feed_link'] = array(
      '#type' => 'textfield',
      '#title' => t('Your feed link'),
      '#default_value' => $this->options['feed_link'],
      '#required' => TRUE,
    );
    $form['feed_description'] = array(
      '#type' => 'textarea',
      '#title' => t('Your feed description'),
      '#default_value' => $this->options['feed_description'],
      '#required' => TRUE,
    );
  }
}
