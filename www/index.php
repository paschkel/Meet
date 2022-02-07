<HTML>
<HEAD>
<TITLE>Meet</TITLE> 
<link rel="stylesheet" type="text/css" href="style/s.css">

</HEAD>

<BODY BGCOLOR="#FFFFFF" TEXT="#000000">


<?

$data = file("rooms.txt");
$count = count($data);
$i = $count;
$i--;



?>


<h1>Meet Rooms</h1>

<table>

<tr> 
	<td width="50"  align="left"><b>no</b></td>
	<td width="60"   align="left"><b>Room Name</b></td>
	<td width="120"  align="left"><b>Meeting Link</b></td> 
	<td width="80"  align="left"><b>Display Name</b></td>	
	
</tr> 
  
  
  
  
<?
 for ($i =  $count-1; $i >= 0; $i--)
   {
@   $parts = explode("|", $data[$i]);
	
?>

 
<tr> 
	<td  align="left"><? echo $i; ?></td>
	<td  align="left"><? echo $parts[0]; ?></td>	
	<td  align="left"><? echo $parts[1] . $parts[2]; ?></td>	
	<td  align="left"><? echo $parts[3]; ?></td>
	
</tr>
  
 
<?} ?>

</table>

</BODY>
</HTML>
