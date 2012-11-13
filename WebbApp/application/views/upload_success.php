
<h3>Your file was successfully uploaded!</h3>

<ul>
<?php

for($i = 0; $i < count($upload_data); $i++)
//echo print_r($upload_data[$i]);
 ?>
</ul>

<p><?php echo anchor('index.php/site/create/upload', 'Upload Another File!'); ?></p>

