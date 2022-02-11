<HTML>
<HEAD>
<TITLE>Meet</TITLE> 
<link rel="stylesheet" type="text/css" href="style/s.css">
<meta name="viewport" content="width=device-width,height=device-height,minimum-scale=1,maximum-scale=1"/>
</HEAD>

<BODY BGCOLOR="#FFFFFF" TEXT="#000000">


<?PHP

$data = file("rooms.txt");
$count = count($data);
$i = $count;
$i--;



?>


<h1>Meet Rooms</h1>

<table>

<tr> 
	<td width="50" 	align="left"><b>No</b></td>
	<td width="120" align="left"><b>System</b></td>	
	<td width="120" align="left"><b>Room Name</b></td>
	<td width="240" align="left"><b>Meeting Link</b></td> 
	<td width="120" align="left"><b>Display Name</b></td>	
	<td width="120" align="left"><b></b></td>		
</tr> 
  
  
  
  
<?PHP
 for ($i = 1; $i < $count; $i++)
   {
@   $parts = explode(";", $data[$i]);
	
?>

 
<tr> 
	<td  align="left"><?PHP echo $i; ?></td>
	<td  align="left"><?PHP echo $parts[0]; ?></td>		
	<td  align="left"><?PHP echo $parts[1]; ?></td>	
	<td  align="left"><?PHP echo $parts[2] . $parts[3]; ?></td>	
	<td  align="left"><?PHP echo $parts[4]; ?></td>
	<td  align="left"></td>	
</tr>
  
 
<?PHP } ?>

</table>

</BODY>
</HTML>
