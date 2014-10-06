(function ($) {
"use strict";

  // Focus blur behaviors for textfield elements.
  function inputTips ($inp, text, style, callback) {
    "use strict";

    var $ = jQuery,
        $inp = $inp.jquery ? $inp : $($inp),
        text = text || $inp.prev('label').text(),
        style = style || {};
    $inp.once('inputTips', function () {
      var $this = $(this),
          $label = $this.prev('label').length ? $this.prev('label') : $('<label />');

      if ((navigator.appVersion.indexOf("MSIE") !== -1 && parseInt($.browser.version, 10) <= 9) === false) {
        $this.attr('placeholder', text);
        $label.remove();
        if (callback) {
          callback();
        }
        return;
      }

      $label.insertBefore($this).css(style).text(text);
      $label = $this.prev('label');
      $label.show().click(function (e) {
        e.preventDefault();
        $this.trigger('focus');
      });
      if ($this.val() !== '') {
        $label.hide();
      }
      $this.bind({
        focus: function() {
          $label.hide();
        },
        blur: function() {
          if ($this.val() == '') {
            $label.show();
          }
        }
      });
      if (callback) {
        callback();
      }
    });
  };

  $.fn.extend( {
    limiter: function(limit, elem) {
      $(this).on("keyup focus", function() {
        setCount(this, elem);
      });
      function setCount(src, elem) {
        var chars = src.value.length;
        if (chars > limit) {
          src.value = src.value.substr(0, limit);
          chars = limit;
        }
        elem.html( limit - chars );
      }
      setCount($(this)[0], elem);
    }
  });

  Drupal.behaviors.commonPopup = {
    attach: function (context, settings) {
      var $form_out = $('.node-outsourcing-form'),
          form_id_out = $form_out.attr('id'),
          $form_it = $('.node-integrators-form'),
          form_id_it = $form_it.attr('id'),
          $form_soft = $('.node-software-form'),
          form_id_soft = $form_soft.attr('id'),
          $form_captcha_comment = $('.form_add_comment'),
          $form_contact = $('.common-contact-us-form'),
          form_id_contact = $form_contact.attr('id'),
          $form_adv = $('.common-adv-form'),
          form_id_adv = $form_adv.attr('id');

      $('#popup-overlay').bind('click', function(){
        $(this).siblings().remove();
        $(this).remove();
      });

      $('#top_nav a.common-link').bind('click', function(){
        $('#adv').html('');
        $('#contact-us').html('');
      });

      $('#call-centers .close').bind('click', function(event){
        event.preventDefault();
        $('#call-centers').html('');
      });
      $('#contact-us .close').bind('click', function(event){
        event.preventDefault();
        $('#contact-us').html('');
      });

      $('#adv .close').bind('click', function(event){
        event.preventDefault();
        $('#adv').html('');
      });
  
      $('.call-center-tabs li a').bind('click', function(event){
        $.totalStorage('country', '');
      });

      if ($('.select-countries .form-select').hasClass('error')) {
        $('.select-countries .selectify .header').addClass('error');
      }
      if ($('.field-name-field-call-center-city .form-select').hasClass('error')) {
        $('.field-name-field-call-center-city .selectify .header').addClass('error');
      }
      if ($('.form-item-banner select').hasClass('error')) {
        $('.form-item-banner .selectify .header').addClass('error');
      }


      $('.form-item-captcha-response input[name=captcha_reseponse]').attr("placeholder", Drupal.t("Code picture"));
      $('.jquery-filestyle  input[type=text]').attr("placeholder", Drupal.t("Logo"));
  
      $('select[name="call_center_countries"]').selectify();
      $('select[name="currency"]').selectify();
      $('select[name="field_call_center_country[und]"]').selectify();
      $('select[name="banner_size"]').selectify();
      $('select[name="banner"]').selectify();
      $(":file").jfilestyle({icon: false, buttonText: Drupal.t("Open")});

      $form_out.once(function () {
        if (form_id_out.indexOf('common-outsourcing-form') >= 0) {
          var style_input = {
                'left': '12px',
                'position': 'absolute',
                'top': '4px'
              };

          inputTips($('.form-item-captcha-response input', this), Drupal.t('Code picture'), style_input);
          inputTips($('.form-item-files-image .jquery-filestyle input', this), Drupal.t('Logo'), style_input);

          $('input.at-term-entry').attr('disabled', 'disabled');
          $.totalStorage('country', '');
        }
      });
      $form_it.once(function () {
        if (form_id_it.indexOf('common-integrators-form') >= 0) {
          var style_input = {
                'left': '12px',
                'position': 'absolute',
                'top': '4px'
              };

          inputTips($('.form-item-captcha-response input', this), Drupal.t('Code picture'), style_input);
          inputTips($('.form-item-files-image .jquery-filestyle input', this), Drupal.t('Logo'), style_input);

          $('input.at-term-entry').attr('disabled', 'disabled');
          $.totalStorage('country', '');
        }
      });
      $form_soft.once(function () {
        if (form_id_soft.indexOf('common-software-form') >= 0) {
          var style_input = {
                'left': '12px',
                'position': 'absolute',
                'top': '4px'
              };

          inputTips($('.form-item-captcha-response input', this), Drupal.t('Code picture'), style_input);
          inputTips($('.form-item-files-image .jquery-filestyle input', this), Drupal.t('Logo'), style_input);

          var elem = $("#chars");
          $(".node-software-form textarea").limiter(150, elem);
          $.totalStorage('country', '');
        }
      });

      $form_captcha_comment.once(function () {
          var style_input = {
                'left': '12px',
                'position': 'absolute',
                'top': '4px'
              };

          inputTips($('.form-item-captcha-response input', this), Drupal.t('Code picture'), style_input);
          inputTips($('.form-item-files-image .jquery-filestyle input', this), Drupal.t('Logo'), style_input);
      });

      $form_contact.once(function () {
        if (form_id_contact.indexOf('common-contact-us-form') >= 0) {
          var style_input = {
                'left': '12px',
                'position': 'absolute',
                'top': '4px'
              };

          inputTips($('.form-item-captcha-response input', this), Drupal.t('Code picture'), style_input);
        }
      });

      $form_adv.once(function () {
        if (form_id_adv.indexOf('common-adv-form') >= 0) {
          var style_input = {
                'left': '12px',
                'position': 'absolute',
                'top': '4px'
              };

          inputTips($('.form-item-captcha-response input', this), Drupal.t('Code picture'), style_input);
        }
      });

      $('.comment-button input[type="submit"]').bind('click', function(event){
        if ($.totalStorage('country')) {
          var tmp = $.totalStorage('country');
          $('input[name="country_sity"]').attr('value', JSON.stringify(tmp));
        }
      });

    }
  };

  /**
   * Styling multiple select elements.
   */
  Drupal.behaviors.indexcallMultipleSelect = {
    attach: function (context, settings) {
      $('select[name="call_center_countries"]').once('indexcallMultipleSelect', function () {
        var $that = $(this);
        $that.selectList({
          'addAnimate': false,
          'instance': true,
        });
        $('select[name="call_center_countries"]').attr('multiple', 'multiple');

        $('.selectlist-list').on('click', 'li', function(event) {
          event.preventDefault();
          var key = $(this).attr('data-key');
          $('.form-item-call-center-countries .option').each(function(index, element) {
            if ($(element).attr('data-id') == key) {
              $(this).show();
            }
          });

          $('select[name="call_center_countries"] option').each(function(index, element) {
            if ($(element).attr('value') == key) {
              $(this).remove();
            }
          });

          if ($('input[name="countries"]').attr('value')) {
            var id_c = $('input[name="countries"]').attr('value'),
                out = [],
                tmp = '',
                str = '',
                separator = ',';
            out = id_c.split(',');

            for (var i = 0; i<out.length; i++) {
              if (out[i] != key) {
                str += out[i];
                str += separator;
              }
            }
            str = str.substring(0, str.length - 1);
            $('input[name="countries"]').attr('value', str);
          }

          if ($.totalStorage('country')) {
            stores = $.totalStorage('country');
            if (typeof stores[key] == 'object'  && stores[key].hasOwnProperty('cities')) {
              $.each(stores[key]['cities'], function(index, value) {
                $('.at-term-list div').each(function(i, v) {
                  if (value !== null && $(v).find('.at-term-text').text() === value['name']) {
                    $(v).find('.at-term-action-remove').trigger('click');
                  }
                });
              });
            }
            delete stores[key];
            $.totalStorage('country', stores);
          }
          if ($.isEmptyObject(stores)) {
            $('input.at-term-entry').attr('disabled', 'disabled');
          }

          $(this).remove();
        });

        $('.form-item-call-center-countries .selectify .header div.selected').text('Sity');
        $('.node-integrators-form .form-item-call-center-countries .selectify .header div.selected').text('Sity');
        $('.selectlist-list li').not('.select-multiple').remove();
      });
    }
  };

 /**
  * Adds ActiveTags field if comma is typed, or focus is lost to the field.
  */
  Drupal.behaviors.artisanActiveTagsAddValue = {
    attach: function (context) {
      $('.at-term-entry', context).once('artisanActiveTagsAddValue', function () {
        $(this).bind('blur keydown keyup', function (e) {
          var val = this.value,
              tag = val.split(' '),
              trimmedVal = val.slice(0, 50);
          if (e.type === 'blur' || (e.type === 'keydown' && e.keyCode === 188 && e.shiftKey === false)) {
            $(this).parent().find('input.at-add-btn.activeTagsAdd-processed').trigger('click');
          }
          if (e.type === 'keyup' && e.keyCode === 188 && e.shiftKey === false) {
            $(this).val('');
          }
          if (e.type === 'keyup') {
            if (tag.length >= 3) {
              $(this).trigger('blur');
              $(this).val('');
            }
            if (val.length > 50) {
              $(this).val(trimmedVal);
              $(this).trigger('blur');
              $(this).val('');
            }
          }
        });
      });
    }
  };

  /**
   * Add tags.
   */
  Drupal.behaviors.IndexcallActiveTagsAdd = {
    attach: function (context, settings) {
      $('input.at-add-btn', context)
        .each(function () {
          $(this).click(function (e) {
            var tag = $(this).parent().find('.at-term-entry').val().replace(/["]/g, ''),
                first_tag = [];
              if ($.totalStorage('country') && tag != '') {
                var id = $.totalStorage('country_id');
                stores = $.totalStorage('country');
                stores[id]['cities'].push({'name' : tag});
                $.totalStorage('country', stores);

                $.each(stores, function(index, value) {
                  first_tag.push({'tag' : value['cities'][0]});
                });

                setTimeout(function () {
                  $('.at-term-list .at-term').each(function(index, value) {
                    $.each(first_tag, function(i, v) {
                      if (v['tag']['name'] === $(value).find('.at-term-text').text()) {
                        $(value).css('clear', 'both');
                      }
                    });
                  });
                }, 100);
              }
            return false;
          });
        });
    }
  };

  /**
   * Remove tags.
   */
  Drupal.behaviors.IndexcallActiveTagsRemove = {
    attach: function (context, settings) {
      $('.at-term.at-term-remove span').bind('click', function(event) {
        var tag = $(this).parent().find('.at-term-text').text();
        if ($.totalStorage('country')) {
          stores = $.totalStorage('country');

          $.each(stores, function(index, value) {
            $.each(value['cities'], function(i, v) {
              if (typeof v === 'object' && v.hasOwnProperty('name') && tag == v['name']) {
                stores[index]['cities'].splice(i, 1);
                $.totalStorage('country', stores);

                if (stores[index]['cities'].length == 0) {
                  $('.selectlist-list .selectlist-item').each(function(j, element) {
                    if ($(element).attr('data-key') == index) {
                      $(element).trigger('click');
                    }
                  });
                }
              }
            });
          });

        }
      });
    }
  };

})(jQuery);
