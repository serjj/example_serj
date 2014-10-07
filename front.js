/*
* This file is part of the Sylius package.
*
* (c) Paweł Jędrzejewski
*
* For the full copyright and license information, please view the LICENSE
* file that was distributed with this source code.
*/
(function ( $ ) {
   'use strict';

   $.fn.tabs = function() {
       var selector = this;
       
       this.each(function() {
           var obj = $(this); 
           
           $(obj.attr('href')).hide();
           
           obj.click(function() {
               $(selector).removeClass('selected');
               
               $(this).addClass('selected');
               
               $($(this).attr('href')).fadeIn();
               
               $(selector).not(this).each(function(i, element) {
                   $($(element).attr('href')).hide();
               });
               
               return false;
           });
       });
   
       $(this).show();
       
       $(this).first().click();
   };

   $(document).ready(function() {

       $('.sylius-different-billing-address-trigger').click(function() {
           $('#sylius-billing-address-container').toggleClass('hidden');
       });

       /**
        * Scroll to top.
        */
       $(function () {
           $(window).scroll(function () {
               if ($(this).scrollTop() > 150) {
                   $('#back-top').fadeIn();
               } else {
                   $('#back-top').fadeOut();
               }
           });
       });
       jQuery('.backtotop').bind('click', function() {
           jQuery('html, body').animate({scrollTop: 0}, 'slow');
       });

       /**
        * Language and Currency Dropdowns.
        */
       $('#currency, #language').hover(function() {
           $(this).find('ul').stop(true, true).slideDown('fast');
       },function() {
           $(this).find('ul').stop(true, true).css('display', 'none');
       });

       /**
        * Menu Show Hide Sub Menu.
        */
       $('#menu > ul > li').mouseover(function() {
           var $screensize = $(window).width();
           if ($screensize > 801) {
               $(this).find('.menu-slide').stop(true, true).slideDown('fast');
           }
           $(this).bind('mouseleave', function() {
               $screensize = $(window).width();
               if ($screensize > 801) {
                   $(this).find('.menu-slide').stop(true, true).css('display', 'none');
               }
           });
       });

       $('#menu .categories-hor .column .menu_level_2 li').mouseover(function() {
           var $screensize = $(window).width();
           if ($screensize > 801) {
               $(this).find('> ul').css('display', 'block');
           }
           $(this).bind('mouseleave', function() {
               $screensize = $(window).width();
               if ($screensize > 801) {
                   $(this).find('> ul').css('display', 'none');
               }
           });
       });

       /**
        * Search.
        */
       $('#sylius_search_name').autocomplete({
           minLength: 2,
           source: $('#sylius_search_name').attr('data-url'),
       });

       /**
        * Initialization slider.
        */
       $('#slideshow').nivoSlider();

       $('#menu .categories-hor .column .menu_level_3').siblings('a').addClass('delimiter');

        var $window = $(window),
            flexslider;

        // tiny helper function to add breakpoints
        function getGridSize() {
          return (window.innerWidth < 320) ? 1 :
                 (window.innerWidth < 600) ? 2 :
                 (window.innerWidth < 800) ? 3 :
                 (window.innerWidth < 900) ? 4 : 5;
        }

        $window.load(function() {
            $('#related_pro, #content .latest_category').flexslider({
                animation: "slide",
                animationLoop: false,
                slideshow: false,
                itemWidth: 210,
                minItems: getGridSize(),
                maxItems: getGridSize()
            });

            $('#latest > div').each(function(index, element) {
               var cat = $(element).attr('id');

               $('#tabs-content > div').each(function(i, el) {
                 var tab = $(el).attr('id'),
                      init_class = '#' + tab + ' .flexslider.latest_category_tabs';
                  
                  $(init_class).flexslider({
                     animation: "slide",
                     animationLoop: false,
                     slideshow: false,
                     itemWidth: 210,
                     minItems: getGridSize(),
                     maxItems: getGridSize(),
                     start: function() {
                         $('#' + cat + ' #' + tab).addClass("deactive");
                         $('#' + cat + " .box-content .tab_content:first").show();
                     } 
                  });
               });

               $('#' + cat + ' ul.tabs li:first').addClass("active").show();
               $('#' + cat + ' ul.tabs li').bind('click', function(event) {
                  var activeTab = $(this).find('a').attr('href');

                  $(this).siblings().removeClass('active');
                  $(this).addClass("active");
                  $('#' + cat + ' .box-content .tab_content').hide();
                  $(activeTab).fadeIn();
                  event.preventDefault();
               });

            });

            $('.tabs').tabs();
        });

        /**
         * Jcarusel initialization.
         */
        $('#carousel ul').jcarousel({
            vertical: false,
            visible: 5,
            scroll: 3
        });

        $(function(){
            $("#facebook.fb-left").hover(function(){
                $("#facebook.fb-left").stop(true, false).animate({left: "0" }, 800, 'easeOutQuint' );
            },
            function(){
                $("#facebook.fb-left").stop(true, false).animate({left: "-241px" }, 800, 'easeInQuint' );
            },1000);
        });

        $(function(){
            $("#twitter_footer.twit-left").hover(function(){
                $("#twitter_footer.twit-left").stop(true, false).animate({left: "0" }, 800, 'easeOutQuint' );
            },
            function(){
                $("#twitter_footer.twit-left").stop(true, false).animate({left: "-241px" }, 800, 'easeInQuint' );
            },1000);
        });

        /**
        * Ajax Cart.
        */
        $('#cart-link').bind('click', function(event){
            event.preventDefault();
            $('#cart').addClass('active');
        });
        $('#cart').bind('mouseleave', function(){
            $(this).removeClass('active');
        });

        /**
         * Slideshow to banner.
         */
        var banner = function() {
            $('#banner').cycle({
                before: function(current, next) {
                    $(next).parent().height($(next).outerHeight());
                }
            });
        }
        setTimeout(banner, 2000);

        /**
         * Zooming image.
         */
        $('.colorbox').colorbox({
            overlayClose: true,
            opacity: 0.5,
            rel: "colorbox",
        });

         $('#write-review a').bind('click', function(){
            $('.write-review').addClass('active');
            $('#tabs .first').removeClass('active');
         });

         /**
          * Ajax submit to review form.
          */
         $('#review-form').on('submit', function(event) {
           event.preventDefault();
           var $form = $(this);
           postForm($form, function(response) {
             if (response.success) {
               $form[0].reset();
               $('#success').replaceWith(response.html);
             }
           });
           return false;
         });

         function postForm($form, callback) {
           var values = {};
           $.each($form.serializeArray(), function(i, field) {
             values[field.name] = field.value;
           });

           $.ajax({
             type: $form.attr('method'),
             url: $form.attr('action'),
             data: values,
             success: function(data) {
               callback(data);
             }
           });
         }

         /**
          * Add to wish list.
          */
         $('#wishlist-add').bind('click', function(event) {
            event.preventDefault();
            var url = $(this).attr('data-url'),
                id = $(this).attr('data-id'),
                name = $(this).attr('data-name');
            $.ajax({
               url: url,
               type: 'post',
               data: 'product_id=' + id + '&name=' + name,
               dataType: 'json',
               success: function(json) {
                  if (json['success']) {
                     $('#header').append(json['html']);
                     $('#wishlist-total').html(json['total']);
                     $('html, body').animate({ scrollTop: 0 }, 'slow'); 
                  }
               }
            });
         });

         /**
          * Change display on search page.
          */
         $('#display').on('click', 'a', function(event) {
            event.preventDefault();
            var type = $(this).attr('data-type');
            display(type);
         });

         function display(view) {
            if (view == 'list') {
               $('.product-grid').attr('class', 'product-list');
               $('#display').html('<span class="grid1-icon" data-type="list">List</span><a href="#" class="list-icon" data-type="grid">Grid</a>');
               $.totalStorage('display', 'list');
            } else {
               $('.product-list').attr('class', 'product-grid');
               $('#display').html('<a href="#" class="grid-icon" data-type="list">List</a><span class="list1-icon" data-type="grid">Grid</span>');
               $.totalStorage('display', 'grid');
            }
         }

         var view = $.totalStorage('display');

         if (view) {
            display(view);
         } else {
            display('grid');
         }

   });

})( jQuery );
