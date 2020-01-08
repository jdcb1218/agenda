<?php
/**
 * @file
 * Template to display a summary of the days items as a calendar month entity.
 * 
 * 
 * @see template_preprocess_calendar_month_multiple_entity.
 */
?>

<?php global $user;  

ctools_include('modal');
ctools_modal_add_js();

?>


<?php if (in_array('consejero', $user->roles)): ?>
<div class="view-item view-item-<?php print $view->name ?>">
  <div class="calendar monthview" id="<?php print $curday ?>">
   <?php $nodos = ''; ?>
    <?php foreach ($ids as $id): 
     // $aa = $id.$aa;  dpm($id); 
      $data = explode(".", $id);
      $nodos =  $data[TRUE] . '-' .$nodos;
     ?>
      <?php if ($view->date_info->style_max_items_behavior != 'more'): ?>
        <?php //print theme('calendar_stripe_stripe', $id); ?>
      <?php endif; ?>
      
    <?php endforeach; ?>
    <div class="view-item <?php //print views_css_safe('view-item-'. $view->name) ?>">
      <?php if ($view->date_info->style_max_items_behavior != 'more'):?>
        <div class="multiple-events"> 
          <?php  $nodos = substr($nodos, 0, -1); ?>
          <?php print l(t('+'. $count), '/availabilitys-list/'.$nodos.'/month', 
          array('attributes' => array('class' => 'ctools-use-modal'))); ?>
        </div>    
    </div>
    <?php else: ?>
      <div class="calendar-more"><?php print l(t('more'), $link) ?>»</div>
    <?php endif; ?>
  </div>    
</div>
<?php endif; ?>



<?php if (in_array('estudiante', $user->roles)): ?>
<div class="view-item view-item-<?php print $view->name ?>">
  <div class="calendar monthview" id="<?php print $curday ?>">
   <?php $nodos = ''; ?>
    <?php foreach ($ids as $id): 
     // $aa = $id.$aa;  dpm($id); 
      $data = explode(".", $id);
      $nodos =  $data[TRUE] . '-' .$nodos;
     ?>
      <?php if ($view->date_info->style_max_items_behavior != 'more'): ?>
        <?php //print theme('calendar_stripe_stripe', $id); ?>
      <?php endif; ?>
      
    <?php endforeach; ?>
    <div class="view-item <?php //print views_css_safe('view-item-'. $view->name) ?>">
      <?php if ($view->date_info->style_max_items_behavior != 'more'):?>
        <div class="multiple-events"> 
          <?php  $nodos = substr($nodos, 0, -1); ?>
          <?php print l(t('+'. $count), '/availabilitys-list-students/'.$nodos.'/month', 
          array('attributes' => array('class' => 'ctools-use-modal'))); ?>
        </div>    
    </div>
    <?php else: ?>
      <div class="calendar-more"><?php print l(t('more'), $link) ?>»</div>
    <?php endif; ?>
  </div>    
</div>
<?php endif; ?>