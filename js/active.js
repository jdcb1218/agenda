(function ($) {
  Drupal.behaviors.active = {
    attach: function (context, settings) {
     // Rol Consejero //
	     // Active views calendar 
	     $(".page-calendario-consejero-diario .menu.nav li:nth-child(1)").addClass("active-trail active");
	     $(".page-calendario-consejero-semanal .menu.nav li:nth-child(1)").addClass("active-trail active");
	     $(".page-calendario-consejero-mes .menu.nav li:nth-child(1)").addClass("active-trail active");
	     // Active historial cita 
	     $(".page-node-edit.node-type-disponibilidad .menu.nav li:nth-child(2)").addClass("active-trail active");
	     // Add cita 
	     $(".page-crear-citas .menu.nav li:nth-child(1)").addClass("active-trail active");

      //Rol estudiante
       // Interna de servicios.
		 if ( $("#block-views-servicios-block-1").length > 0 ) {
			$(".page-calendario-estudiante .menu.nav li:nth-child(1)").addClass("active-trail active");	
		 }
       // Mis datos	
		 $(".page-user-edit .menu.nav li:nth-child(2)").addClass("active-trail active");
		 $(".node-disponibilidad-form .field-name-field-lugar input").attr("placeholder", "Lugar");
		 $(".node-disponibilidad-form .field-name-field-cupo input").attr("placeholder", "Cupo");
    }
  };
}(jQuery));