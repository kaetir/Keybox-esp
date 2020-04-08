(function() {
  function sectionHeight() {
    $('section').each(function() {
      $(this).css({minHeight : $(window).height() });
    });
  }

  $(document).ready(function() {
    sectionHeight();
  });

  $(window).resize(function() {
    sectionHeight();
  });
})(jQuery)
