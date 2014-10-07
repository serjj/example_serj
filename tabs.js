(function($) {
  Drupal.behaviors.AybStyler = {
    attach: function() {
      $('input, select').once('AybStyler', function () {
        $(this).styler();
      });
    }
  };

  Drupal.behaviors.aybOffersMap = {
    attach: function() {
      $('ul.quicktabs-tabs.quicktabs-style-allyearsbaltics li').eq(2).once('aybOffersMap', function () {
        var $iframe = $('#quicktabs-tabpage-offer_node_view-2').find('iframe').attr('width', 880);
        if (!$(this).hasClass('active') && !$iframe.hasClass('normalized')) {
          $iframe.detach();
        }
        else {
          $iframe.addClass('normalized');
        }
        $(this).find('a').bind('click', function () {
          if (!$iframe.hasClass('normalized')) {
            $('#quicktabs-tabpage-offer_node_view-2').find('.image-wrapper').append($iframe.addClass('normalized'));
          }
        });
      });
    }
  };

  Drupal.behaviors.destinations = {
    attach: function(context, settings) {
      $(document).ready(function() {

        //jQuery('input, select').styler();
        $("button, .form-actions input").uniform();
        $('.bg-image').imagefit();

        $(".popup").colorbox({
          inline: true,
          top:false,
          height:"605px"
        });
        $('.breadcrumbs-title-white-block-right-corner').height($('.breadcrumbs-title-white-block').height() + 40);
        $('.breadcrumbs-title-white-block').height($('.breadcrumbs-title-white-block').height() + 40);

        /*Dropdown block*/

        $('#destinations-dropdown-block .cities-list-item').mouseenter(function() {
          $('#destinations-dropdown-block .cities-list .cities-list-item').removeClass('active');
          $('#destinations-dropdown-block .city-name').removeClass('active');
          $('#destinations-dropdown-block .city-pin').hide();
          $(this).addClass('active');
          var city = $(this).attr('id');
          if ($(this).parent().hasClass('estonia')) {
            var country = 'estonia'
          }
          if ($(this).parent().hasClass('latvia')) {
            var country = 'latvia'
          }
          if ($(this).parent().hasClass('lithuania')) {
            var country = 'lithuania'
          }
          if ($(this).hasClass('first')) {
            var photoView = country;
          } else {
            var photoView = $(this).attr('id');
          }
          var cityId = '#destinations-dropdown-block .map #' + city + '-city-destinations';
          var cityPinId = '#destinations-dropdown-block .map #' + city + '-pin';
          $('#destinations-dropdown-block .map .country').removeClass('active');
          $('#destinations-dropdown-block #' + country + '-map-destinations').addClass('active');
          $(cityPinId).show();
          $(cityId).addClass('active');
          $('.photo-view').hide();
          $('.' + photoView + '-photo-view').show();
        });

        $('#discover-dropdown-block .countries-list-item a').mouseenter(function() {
          $('#discover-dropdown-block .countries-list-item a').removeClass('active')
          $(this).addClass('active');
          var country = $(this).parent().attr('id');
          $('#discover-dropdown-block .map .country').removeClass('active');
          $('#discover-dropdown-block #' + country + '-map-discover').addClass('active');
          $('#discover-dropdown-block .country-photo').hide();
          $('#discover-dropdown-block .country-photo.' + country + '-photo').show();
        });

        $('.travel-guide-accordion').liHarmonica({
          currentClass: 'cur',
          onlyOne: true,
          speed: 500
        });

        $('.slideshow').mouseover(function() {
          $('.prev-next-container').fadeIn(300);
        });
        $('.slideshow').mouseleave(function() {
          $('.prev-next-container').stop();
          $('.prev-next-container').fadeOut(300);
        });
        //tabs
        $('.tabs-menu a').click(function() {
          var tab_id = $(this).attr('id');
          tabClick(tab_id)
        });

        function tabClick(tab_id) {
          if (tab_id != $('.tabs-menu-item a.active').attr('id')) {
            $('.tabs-content,.tabs-menu-item a').removeClass('active');
            $('#' + tab_id).addClass('active');
            $('#' + tab_id + '-content').addClass('active');
          }
        }

        //tabs hastags support
        if (location.hash != '') {
          var hashtag = location.hash;
          tab_id_hash = hashtag + '-tab';
          if ($(tab_id_hash).length > 0) {
            tab_id = tab_id_hash;
            $('.tabs-content,.tabs-menu-item a').removeClass('active');
            $(tab_id).addClass('active');
            $(tab_id + '-content').addClass('active');
          }
        }

        //payment method select
        $('.select-button').click(function() {
          $('.payment-method').toggleClass('selected');
        });

        $('html').click(function() {
          $('a.active + .drop').hide();
          $('a.active').removeClass('active');
        });

        $('.card-select a').click(function() {
          var dropBlock = $(this).parent().find('.drop');
          event.stopPropagation();
          if (dropBlock.is(':hidden')) {
            dropBlock.show();

            $(this).addClass('active');

            $('.drop').find('li').click(function() {

              var selectResult = $(this).html();

              $(this).parent().parent().find('a').val(selectResult);

              $(this).parent().parent().find('a').removeClass('active').html(selectResult);

              dropBlock.hide();
            });

          } else {
            $(this).removeClass('active');
            dropBlock.hide();
          }
        });

      });
    }
  }
})(jQuery);
