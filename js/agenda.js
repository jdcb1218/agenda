(function($) {
Drupal.behaviors.agenda = {
    attach: function (context, settings) {
 		var count = $('.container-inline.container.form-wrapper.form-group').length;
 		$.post(window.location.pathname, function( data ) {
			if ($(context).context) {
				if ($(context).context.id == 'agenda-records-form') {
					$('.form-item-field-container-'+count+'-uid input').val($(".view-id-usuarios_agenda_de_servicios .view-content .uid-user").text());
					$('.form-item-field-container-'+count+'-name input').val($(".view-id-usuarios_agenda_de_servicios .view-content .nombre-user").text());
					$('.form-item-field-container-'+count+'-codec input').val($(".view-id-usuarios_agenda_de_servicios .view-content .codigo-user").text());
					$('.form-item-field-container-'+count+'-email input').val($(".view-id-usuarios_agenda_de_servicios .view-content .email-user").text()); 						
			        $('.form-item-field-container-'+count+'-motivo input').val($('select[name=selector-motivo]').val());  						
				}
		  	}
		});
    }
  };
})(jQuery);