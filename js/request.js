(function ($) {
	Drupal.behaviors.request = {
	    attach: function (context, settings) {
			contentBreakpoint();

			var docWidth = jQuery(document).width();
			jQuery("button#cbox2").click(function(event) {
				if (docWidth <= 992 ) {
					if (jQuery("body").hasClass('page-calendario-consejero')) {
						console.log("verdadero");
						closeBurgerConsejero();
					}else {
						console.log("falso");
						closeBurgerEstudiante();
					}
				}
			});

			$(".page-node-edit #disponibilidad-node-form #edit-field-tipo-de-servicio" ).remove();
			$(".page-node-edit #disponibilidad-node-form #edit-field-citas-agenda-und-0-field-collec-motivo" ).remove();

			/*
			*	Funcion cambiar los breakpoints bootstrap region container;
			*/
			function contentBreakpoint(){
				//contenerdor de consejero home (filtro dia )// change dimencion table
				$('body.sidebar-first.page-calendario-consejero aside').removeClass("col-sm-3").addClass("col-lg-3 col-md-3 col-sm-12 col-xs-12");
				$('body.sidebar-first.page-calendario-consejero .row > section.col-sm-9').removeClass("col-sm-9").addClass("col-lg-9 col-md-9 col-sm-12 col-xs-12");
				//contenerdor de estudiante home
				$('body.page-calendario-estudiante aside').removeClass("col-sm-3").addClass("col-lg-3 col-md-3 col-sm-12 col-xs-12");
				$('body.page-calendario-estudiante .row > section.col-sm-9').removeClass("col-sm-9").addClass("col-lg-9 col-md-9 col-sm-12 col-xs-12");
				// add class user student menu my data
				$(".page-user-edit #user-profile-form .form-wrapper.form-group").addClass("col-lg-4 col-xs-6 col-sm-6");
			}

			/*
			*	Crear Citas cambiar orden
			*/
			$('body.page-crear-citas section#block-agenda-citas-ajax form#agenda-records-form div div#js-ajax-elements-wrapper').prependTo('body.page-crear-citas section#block-agenda-citas-ajax form#agenda-records-form');

			/*
			*	Button en mobil para expandir y ocultar el menu, fecha, calendario, button crear disponibilidad, color status.
			*/
			function closeBurgerConsejero() {
				$("button#cbox2").toggleClass("close");
				$(".Calendario_Contenedor .view-header .clearfix.date-nav-wrapper, .Calendario_Contenedor .view-content, .crear_disponibilidad").toggle();
			}

			/*
			*	Button en mobil para expandir y ocultar el menu, fecha, calendario, Select consejeros, color status.
			*/
			function closeBurgerEstudiante() {
				$("button#cbox2").toggleClass("close");
				$(".Calendario_Contenedor-estudiantes .view-header .clearfix.date-nav-wrapper, .Calendario_Contenedor-estudiantes .view-estudiante-calendar .view-content .month-view, #block-agenda-list-consejeros, .info-citas-estudiantes").toggle();
			}

			$('.field-name-field-horario-inicio select').change(function(){
				 var result = dateFormat($(this).context.id);
				 $('.form-item-field-fecha-und-0-value-time input').val(result);
			});


			$('.field-name-field-horario-fin select').change(function(){
				var result = dateFormat($(this).context.id);
				$('.form-item-field-fecha-und-0-value2-time input').val(result);
			});


			// TOR Disiplinario Session Uno Fecha Inicio
			$('.field-name-field-tor-disciplinario-uno .field-name-field-horario-inicio select').change(function(){
				 var result = dateFormat($(this).context.id);
				 $('.form-item-field-tor-disciplinario-uno-und-0-field-fecha-und-0-value-time input').val(result);
			});

			// TOR Disiplinario Session Uno Fecha End
			$('.field-name-field-tor-disciplinario-uno .field-name-field-horario-fin select').change(function(){
				 var result = dateFormat($(this).context.id);
				 $('.form-item-field-tor-disciplinario-uno-und-0-field-fecha-und-0-value2-time input').val(result);
			});


			// TOR Disiplinario Session Dos Fecha Inicio
			$('.field-name-field-tor-disciplinario-dos .field-name-field-horario-inicio select').change(function(){
				 var result = dateFormat($(this).context.id);
				 $('.form-item-field-tor-disciplinario-dos-und-0-field-fecha-und-0-value-time input').val(result);
			});
			// TOR Disiplinario Session Dos Fecha End
			$('.field-name-field-tor-disciplinario-dos .field-name-field-horario-fin select').change(function(){
				 var result = dateFormat($(this).context.id);
				 $('.form-item-field-tor-disciplinario-dos-und-0-field-fecha-und-0-value2-time input').val(result);
			});

			function dateFormat(id){
				var selector = document.getElementById(id);
				var selected = selector.options[selector.selectedIndex].text;
				selected = selected.replace(" ", "");
				selected = selected.replace(".", "");
				selected = selected.replace(".", "");
				return selected;
			}

			var hoy = $(".month-view .mini .today").text().trim();
			// Add PlaceHolder Fields Login.
			$('#user-login #edit-name').attr('placeholder', 'Usuario');
	    	$('#user-login #edit-pass').attr('placeholder', 'Clave');
	        $( "#edit-submit-usuarios-agenda-de-servicios" ).click(function() {
		       $("#block-agenda-citas-ajax").css("display", "initial");
	    	});

			$.post(document.location.href + "/request/ajax", function( data ) {
				$('#disponibilidad-node-form .save_tor_submit').hide();
				$("#modalContent .modal-content #modal-content").each( function(item) {
					var clase = $(this).first();
					var id = clase.context.firstElementChild.id;
					var clasename = clase.context.firstElementChild.className;
					$(".ctools-modal-dialog.modal-dialog").addClass(clasename +' '+id);
				});
				$('#edit-field-tipo-de-servicio-und').change(function(){
					if ($(this).val() == 7) {
				    	$('.group-basic-info .field-name-field-fecha').hide();
				    	$('.group-basic-info .field-name-field-lugar').hide();
				    	$('.group-basic-info .field-name-field-horario-inicio').hide();
				    	$('.group-basic-info .field-name-field-horario-fin').hide();
				    	$('#disponibilidad-node-form .save_tor_submit').show();
				    	$('#disponibilidad-node-form #edit-submit').hide();
				    }else{
				    	$('.group-basic-info .field-name-field-fecha').show();
				    	$('.group-basic-info .field-name-field-lugar').show();
				    	$('.group-basic-info .field-name-field-horario-inicio').show();
				    	$('.group-basic-info .field-name-field-horario-fin').show();
				    	$('#disponibilidad-node-form .save_tor_submit').hide();
				    	$('#disponibilidad-node-form #edit-submit').show();
				    }
				});
			});
			var url = new URL(window.location.href);
			var arg = window.location.pathname.split('/');
			// Redirect dropdown rol consejero
			$( ".view-consejero-calendar .wrapper" ).click(function() {
				var mes = $(".dropdown .active").text();
			      switch($('.view-header .dropdown .selected').text()) {
				    case 'Enero':
				    	if (mes == 'Enero') {
				    		setTimeout(function(){ window.location.href = Drupal.settings.agenda.dominio+"/calendario-consejero/diario/2018-01-01";
				    		}, 1000);
					    }
					break;
				    case 'Febrero':
					    if (mes == 'Febrero') {
					    	window.location.href = Drupal.settings.agenda.dominio+"/calendario-consejero/diario/2018-02-01";
					    }
				    break;
				    case 'Marzo':
					    if (mes == 'Marzo') {
					    	 window.location.href = Drupal.settings.agenda.dominio+"/calendario-consejero/diario/2018-03-01";
					    }
				    break;
				    case 'Abril':
					    if (mes == 'Abril') {
					    	window.location.href = Drupal.settings.agenda.dominio+"/calendario-consejero/diario/2018-04-01";
					    }
				    break;
				    case 'Mayo':
				    	if (mes == 'Mayo') {
				    		window.location.href = Drupal.settings.agenda.dominio+"/calendario-consejero/diario/2018-05-01";
				    	}

				    break;
				    case 'Junio':
				    	if (mes == 'Junio') {
				    		window.location.href = Drupal.settings.agenda.dominio+"/calendario-consejero/diario/2018-06-01";
				    	}
				   break;
				    case 'Julio':
				    	if (mes == 'Julio') {
				    		window.location.href = Drupal.settings.agenda.dominio+"/calendario-consejero/diario/2018-07-01";
				    	}

				    break;
				    case 'Agosto':
				    	if (mes == 'Agosto') {
				    		window.location.href = Drupal.settings.agenda.dominio+"/calendario-consejero/diario/2018-08-01";
				    	}

				    break;
				    case 'Septiembre':
				    	if (mes == 'Septiembre') {
				    		window.location.href = Drupal.settings.agenda.dominio+"/calendario-consejero/diario/2018-09-01";
				    	}

				    break;
				    case 'Octubre':
				    	if (mes == 'Octubre') {
				    		window.location.href = Drupal.settings.agenda.dominio+"/calendario-consejero/diario/2018-10-01";
				    	}

				    break;
				    case 'Noviembre':
				    	if (mes == 'Noviembre') {
				    		window.location.href = Drupal.settings.agenda.dominio+"/calendario-consejero/diario/2018-11-01";
				    	}

				    break;
				    case 'Diciembre':
				    	if (mes == 'Diciembre') {
				    		window.location.href = Drupal.settings.agenda.dominio+"/calendario-consejero/diario/2018-12-01";
				    	}
				    break;
				}
			});

			var currenpath = window.location.href.split(Drupal.settings.agenda.dominio);
			var arg = currenpath[1].split('/');
			var tid = arg[5];


			// Redirect dropdown rol estudiante
			$( ".view-estudiante-calendar .wrapper" ).click(function() {
				var mes = $(".dropdown .active").text();
				var uid = document.location.href.substring(document.location.href.lastIndexOf('/') + 1);
				var date = new Date(); var year = date.getFullYear();

			      switch($('.view-header .dropdown .selected').text()) {
				    case 'Enero':
				    	if (mes == 'Enero' && url.searchParams.get("mini") != null) {
				    		setTimeout(function(){ window.location.href = Drupal.settings.agenda.dominio+'/es/es/calendario-estudiante/'+year+'-02-01/diario/' + tid + '/' + uid;
				    		}, 2000);
					    }
					break;
				    case 'Febrero':
					    if (mes == 'Febrero') {
					    	 window.location.href = Drupal.settings.agenda.dominio+'/es/calendario-estudiante/'+year+'-02-01/diario/'+ tid + '/' + uid;
					    }
				    break;
				    case 'Marzo':
					    if (mes == 'Marzo') {
					    	 window.location.href = Drupal.settings.agenda.dominio+'/es/calendario-estudiante/'+year+'-03-01/diario/'+ tid + '/' + uid;
					    }
				    break;
				    case 'Abril':
					    if (mes == 'Abril') {
					    	 window.location.href = Drupal.settings.agenda.dominio+'/es/calendario-estudiante/'+year+'-04-01/diario/'+ tid + '/' + uid;
					    }
				    break;
				    case 'Mayo':
				    	if (mes == 'Mayo') {
				    	    window.location.href = Drupal.settings.agenda.dominio+'/es/calendario-estudiante/'+year+'-05-01/diario/'+ tid + '/' + uid;
				    	}
				    break;
				    case 'Junio':
				    	if (mes == 'Junio') {
				    		 window.location.href = Drupal.settings.agenda.dominio+'/es/calendario-estudiante/'+year+'-06-01/diario/'+ tid + '/' + uid;
				    	}
				   break;
				    case 'Julio':
				    	if (mes == 'Julio') {
				    		window.location.href = Drupal.settings.agenda.dominio+'/es/calendario-estudiante/'+year+'-07-01/diario/'+ tid + '/' + uid;
				    	}
				    break;
				    case 'Agosto':
				    	if (mes == 'Agosto') {
				    		 window.location.href = Drupal.settings.agenda.dominio+'/es/calendario-estudiante/'+year+'-08-01/diario/'+ tid + '/' + uid;
				    	}
				    break;
				    case 'Septiembre':
				    	if (mes == 'Septiembre') {
				    		 window.location.href = Drupal.settings.agenda.dominio+'/es/calendario-estudiante/'+year+'-09-01/diario/'+ tid + '/' + uid;
				    	}
				    break;
				    case 'Octubre':
				    	if (mes == 'Octubre') {
				    		window.location.href = Drupal.settings.agenda.dominio+'/es/calendario-estudiante/'+year+'-10-01/diario/'+ tid + '/' +uid;
				    	}
				    break;
				    case 'Noviembre':
				    	if (mes == 'Noviembre') {
				    		 window.location.href = Drupal.settings.agenda.dominio+'/es/calendario-estudiante/'+year+'-11-01/diario/'+ tid + '/' +uid;
				    	}
				    break;
				    case 'Diciembre':
				    	if (mes == 'Diciembre') {
				    		 window.location.href = Drupal.settings.agenda.dominio+'/es/calendario-estudiante/'+year+'-12-01/diario/'+ tid + '/' +uid;
				    	}
				    break;
				}
		});
	   // Loader Animation.
		$(window).load(function(){
		    $('.loader').fadeOut(500);
		});
		// Add User and Rold to Date(Today).
		if ($(".cotainer-name-user ").length == false) {
		 	 $('<h2 class="cotainer-name-user"> '+$('.view-user-login .views-field-name .field-content').text()+'</h2>').appendTo('#block-system-main .view .clearfix.date-nav-wrapper');
		}

			// Add Year to Month Calendar (Consejero) && Estudiante
			$( ".date-nav-wrapper h3 a" ).attr( "src", function() {
				var params = $(this).context.href.split("-");
				var arg = params[1].split("/");

				if ($( ".page-calendario-consejero .clearfix.date-nav-wrapper h3 a" ).text().split(' ').length <2) {
					$('.page-calendario-consejero .clearfix.date-nav-wrapper h3 a').text($( ".page-calendario-consejero .clearfix.date-nav-wrapper h3 a" ).text() + ' '+ arg[2]);
				}


				if(params[3]){
					var arg_es = params[3].split("/");
					if (($(".page-calendario-estudiante .clearfix.date-nav-wrapper h3 a" ).text().split(' ').length <2) && (arg_es[2])) {
						$('.page-calendario-estudiante .clearfix.date-nav-wrapper h3 a').text($( ".page-calendario-estudiante .clearfix.date-nav-wrapper h3 a" ).text() + ' '+ arg_es[2]);
					}else{
						var date_moth = $('.page-calendario-estudiante .clearfix.date-nav-wrapper h3 a').text();
						var arg_moth =  date_moth.split(" ");
						if (arg_moth.length == true) {
							var arg_es = params[2].split("/");
							$('.page-calendario-estudiante .clearfix.date-nav-wrapper h3 a').text($( ".page-calendario-estudiante .clearfix.date-nav-wrapper h3 a" ).text() + ' '+ arg_es[2]);
						}
					}
				}
			});

			// Add default month in select dropdrown Select Month.
			$(document).ready(function(){
			var result = $(".view-header .date-nav-wrapper h3 a").text().split(' ');
			if (result[0]) {
				$('.view-header .dropdown .selected').text(result[0]);
			}
			});


			// Add link to days for block calendar (Consejero)
     	$('.page-calendario-consejero .mini tr').each(function(){
     		$(this).find('td').each(function(){
     			var res = $(this).context.id.split("-");
     			$(this).context.innerHTML = '<div class="month mini-day-on"> <a href="'+Drupal.settings.agenda.dominio+'/calendario-consejero/diario/'+res[1]+'-'+res[2]+'-'+res[3]+'">'+$(this).context.innerText.replace('&nbsp;', '')+'</a></div>';
					 $(this).find('a').html($(this).find('a').html().replace('&nbsp;', ''));
				})
		 })
			// Add link to days for block calendar (Estudiante)
     	$('.page-calendario-estudiante .mini tr').each(function(){
     		$(this).find('td').each(function(){
     		  var res = $(this).context.id.split("-");
     		  var tid = document.location.href.substring(document.location.href.lastIndexOf('/') + 1);
     		  $(this).context.innerHTML = '<div class="month mini-day-on"> <a href="'+Drupal.settings.agenda.dominio+'/calendario-estudiante/'+res[1]+'-'+res[2]+'-'+res[3]+'/diario/'+tid+'">'+$(this).context.innerText.replace('&nbsp;', '')+'</a></div>';
					 $(this).find('a').html($(this).find('a').html().replace('&nbsp;', ''));
				})
		 });

     	// Validate field // Creation Availability

		$('.node-disponibilidad-form  .form-item-field-cupo-und-0-value input').on('input', function () {
		    this.value = this.value.replace(/[^0-9]/g,'');
		});
	}
  };
}(jQuery));

function goBack() {
  return window.history.back();
}