jQuery('document').ready(function() {
    jQuery('#lightvideo_img').click(function() {
      jQuery(this).prev().find('a').click();
    });

    // Custom code for playing videos on using fancyBox plugin.
    jQuery('a[data-type="iframe"]').on("click", function(){
      jQuery.fancybox({
        href: this.href,
        type: jQuery(this).data("type")
      });
      return false;
    });

    // Add fancybox plugin popup wrapper for current elements on accomodations and booking tabs.
    jQuery('.accommodation-clk, #newsletter_subscription').fancybox();

  });

(function ($) {
  "use strict";

  Drupal.behaviors.colorboxPos = {
    attach: function() {
      $('.popup').once('colorboxPos', function () {
        $(this).bind('click', function () {
          $('#colorbox').css({
            'margin-top': Math.floor(605 / -2)
          });
        });
      });
    }
  };

  Drupal.behaviors.datePick = {
    attach: function() {
      if ($.fn.datepicker) {
        $('.pickadate').once('datePick', function () {
          $(this).datepicker({
            dateFormat: 'dd-mm-yy',
            autoSize: false
          });
        });
      }
    }
  };

  Drupal.behaviors.animateScrollTop = {
    attach: function() {
      $('.status-message.request').once('animateScrollTop', function () {
        var top = $(this).offset().top;
        $('body').animate({scrollTop: top - 80}, 1700);
      });
      $('#contact-ayb-request-page .form-submit').bind('click', function () {
        $(this).prev('.btn_left').attr('disabled', 'disabled');
        $(this).next('.ajax-progress').next('.btn_right').attr('disabled', 'disabled');
        $(this).next('.btn_right').attr('disabled', 'disabled');
      });
    }
  };

  Drupal.behaviors.disabledSubmit = {
    attach: function() {
      $('#contact-ayb-contact-form-block').find('.form-submit').once('disabledSubmit', function () {
        $(this).bind('click', function () {
          $(this).parents('div.button').attr('disabled', 'disabled');
        });
      });
    }
  };

  var formIds = '#views-exposed-form-faq-faq-page,\
  #views-exposed-form-faq-faq-category-page,\
  #views-exposed-form-faq-page-1,\
  #views-exposed-form-faq-page-2,\
  #views-exposed-form-faq-page-3,\
  #views-exposed-form-faq-page-4';

  Drupal.behaviors.aybFaqFilter = {
    attach: function() {
      $('#ayb-ajax-loader').remove();
      $(formIds).hide();

      var $block = $('#offer-faq-menu');

      $block.once('aybFaqFilter', function () {
        $(this).find('a.active').removeClass('active').addClass('selected');
        $(this).find('a').bind('click', function (e) {
          e.preventDefault();
          if ($(this).hasClass('selected') || $(this).hasClass('active')) {
            return false;
          }
          $('.region-content-inner > .region-content').append('<div id="ayb-ajax-loader"><div class="loader"></div><div class="bg"></div></div>');
          $(formIds).find('select').val($(this).attr('data-tid'));
          $(formIds).find('.form-submit').trigger('click');
          $('.content-header-inner').find('#selected-category h2').html($(formIds).find('select option:selected').text());
          $('.page-header-inner .breadcrumbs-top li.breadcrumb-current').html($(formIds).find('select option:selected').text());
          history.pushState({}, null, $(this).attr('href'));
          document.title = $(formIds).find('select option:selected').text() + ' | ' + Drupal.settings.siteName;
          $block.find('a').removeClass('selected');
          $block.find('a[data-tid=' + $(formIds).find('select').val() + ']').addClass('selected');
        });
      });
    }
  };
})(jQuery);
