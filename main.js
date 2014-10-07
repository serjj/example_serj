jQuery(document).ready(function($) {
  function fullwidthAboutPic() {
    $("#wrapper").css("height", $(window).height());
    $("body").css("display", 'block');
  }

  $(window).resize(function() {
    fullwidthAboutPic();
  });

  fullwidthAboutPic();
  RequestFromValidate();
  ScrollHash();
  ParalaxScroll();

  /**
   * Tooltips.
   */
  $('.requirements-ssh').hide();
  $('#requirements-toogle').bind('click', function() {
    $('.toogle').toggleClass('open');
    $('.requirements-ssh').slideToggle('slow');
  });

  $('#label-terms').bind('click', function() {
    $(this).toggleClass('checked');
  });

  /**
   * Validate function to request form.
   */
  function RequestFromValidate() {
    jQuery.validator.setDefaults({
      debug: true,
      success: "valid"
    });

    $("#request-form").validate({
      rules: {
        "emergency_rescue_request[name]": {
          required: true,
          minlength: 3
        },
        "emergency_rescue_request[email]": {
          required: true,
          email: true
        },
        "emergency_rescue_request[details]": {
          required: true,
          minlength: 3
        },
        "emergency_rescue_request[requirements]": {
          required: true,
          minlength: 3
        },
      },
      showErrors: function(errorMap, errorList) {
        if (this.numberOfInvalids() > 0) {
          $("#request-form input#request-submit").attr('disabled', true);
          $("#request-form input#request-submit").css({'background-color': '#adadad'});
        }
        else {
          $("#request-form input#request-submit").attr('disabled', false);
          $("#request-form input#request-submit").css({'background-color': '#fb8a2e'});
          $("#request-form input#request-submit").hover(function() {
            $(this).css({'background': '#ffa00a'});
          }, function() {
            $(this).css({'background': '#bd5807'});
          });
        }
        $("#summary").html("Your form contains "
          + this.numberOfInvalids()
          + " errors, see details below.");
        this.defaultShowErrors();
      },
      messages: {
        your_email_address: {
          required: "This field is required.",
          email: "Please enter a valid email address.",
        },
      }
    });
  }

  $('a.terms-use').bind('click', function() {
    $('#request').modal('hide');
  });

  $('.terms-close').bind('click', function() {
    $('#request').modal('show');
  });

  $("#request-form input#request-submit").attr('disabled', false);

  /**
   * Ajax submit to request form.
   */
  $('#request-form').on('submit', function(event) {
    event.preventDefault();
    postForm($(this), function(response) {
      if (response.success) {
        $('#request-body').replaceWith(response.html);
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
   * Change url by scroling.
   */
  function ScrollHash() {
    var currentHash = '#home';
    $(document).bind('scroll', function(e) {
      $('section').not('#container').not('.cbp-so-section').each(function() {
        var top = window.pageYOffset;
        var distance = top - $(this).offset().top;
        var hash = $(this).attr('id');
        if (distance < 50 && distance > -181 && currentHash != hash) {
          if (window.location.hash != '#' + $(this).attr('id')) {
            if(history.pushState) {
              history.pushState(null, null, '#' + $(this).attr('id'));
            }
            else {
              window.location.hash = $(this).attr('id');
            }
          }
        }
      });
    });
  }

  /**
   * Initialization paralax scrolling.
   */
  function ParalaxScroll() {
    var s = skrollr.init();
    new cbpScroller(document.getElementById('cbp-so-scroller'));
  }

  /**
   * Smooth scrolling.
   */
  $('body').on('click.smooth', 'a[href^="#"]', function(e) {
    e.preventDefault();
    var target = this.hash;
    var currentPos = $(document).scrollTop();
    var delta = Math.abs(currentPos - $(target).offset().top);
    var animationTime = Math.round(1000 * (delta / 1500));

    $('html, body').stop().animate({
        'scrollTop' : $(target).offset().top
    }, animationTime, 'swing', function() {
        window.location.hash = target;
      });
  });
});

( function(window) {

'use strict';

function classReg(className) {
  return new RegExp("(^|\\s+)" + className + "(\\s+|$)");
}

var hasClass, addClass, removeClass;

if ('classList' in document.documentElement) {
  hasClass = function(elem, c) {
    return elem.classList.contains(c);
  };
  addClass = function(elem, c) {
    elem.classList.add(c);
  };
  removeClass = function(elem, c) {
    elem.classList.remove(c);
  };
}
else {
  hasClass = function(elem, c) {
    return classReg(c).test(elem.className);
  };
  addClass = function(elem, c) {
    if ( !hasClass(elem, c) ) {
      elem.className = elem.className + ' ' + c;
    }
  };
  removeClass = function(elem, c) {
    elem.className = elem.className.replace(classReg(c), ' ');
  };
}

function toggleClass(elem, c) {
  var fn = hasClass(elem, c) ? removeClass : addClass;
  fn(elem, c);
}

var classie = {
  // full names
  hasClass: hasClass,
  addClass: addClass,
  removeClass: removeClass,
  toggleClass: toggleClass,
  // short names
  has: hasClass,
  add: addClass,
  remove: removeClass,
  toggle: toggleClass
};

if (typeof define === 'function' && define.amd) {
  define(classie);
} else {
  window.classie = classie;
}

})(window);

var cbpAnimatedHeader = (function() {

  var docElem = document.documentElement,
    header = document.querySelector('.menu'),
    didScroll = false,
    changeHeaderOn = 50;

  function init() {
    window.addEventListener('scroll', function(event) {
      if(!didScroll) {
        didScroll = true;
        setTimeout(scrollPage, 30);
      }
    }, false );
  }

  function scrollPage() {
    var sy = scrollY();
    if (sy >= changeHeaderOn) {
      classie.add(header, 'menu-shrink');
    }
    else {
      classie.remove(header, 'menu-shrink');
    }
    didScroll = false;
  }

  function scrollY() {
    return window.pageYOffset || docElem.scrollTop;
  }

  init();

})();
