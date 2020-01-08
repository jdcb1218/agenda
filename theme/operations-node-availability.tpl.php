<div class="operation-node">
	<?php ctools_include('modal'); ctools_include('ajax'); ?>

	<div class="create meeting">
	<?php  print(l(t('Crear cita'), 'crear/'.arg(1).'/citas')); ?>
	</div>

	<div class="edit availability">
	<?php 
	print(l(t('Editar disponibilidad'), 'availability-edit/'.arg(1).'/nojs', 
	      array('attributes' => array('class' => 'ctools-use-modal'))));
	?>
	</div>

	<div class="delete availability">
	<?php 
	print(l(t('Eliminar disponibilidad'), 'availability-delete/'.arg(1).'/nojs', 
	      array('attributes' => array('class' => 'ctools-use-modal'))));
	?>
	</div>
</div>