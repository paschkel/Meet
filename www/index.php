<HTML>
<HEAD>
<TITLE>Meet</TITLE> 
<link rel="stylesheet" type="text/css" href="style/s.css">
<meta name="viewport" content="width=device-width,height=device-height,minimum-scale=1,maximum-scale=1"/>
</HEAD>

<BODY BGCOLOR="#FFFFFF" TEXT="#000000">


<?PHP
$Save = $_GET["Save"];
$RoomName = $_GET["RoomName"];
$DisplayName = $_GET["DisplayName"];
$System = $_GET["System"];
$MeetingLink = $_GET["MeetingLink"];
$item = $_GET["item"];
$mode = $_GET["mode"];

if($Save=="Save" && $item=="NEW")
	{
	$Output = "$RoomName;$System;$MeetingLink;$DisplayName\n";
	
	$file = fopen("rooms.txt", "a");							// write data to file
	fputs($file, $Output); 
	fclose($file);	
	}



if($Save=="Save" && $item!="NEW")
	 {
	 $filename = "rooms.txt";
	 $Output = "$RoomName;$System;$MeetingLink;$DisplayName\n";
		
	 $dat = file($filename);
	 $row_count = count($dat);

	 $file_handle = fopen($filename, 'w+');

	 for ($row = 0; $row < $row_count; $row++)
	   {
	   if ($row != $item)
			fputs($file_handle, $dat[$row]);
		else
			fputs($file_handle, $Output); 
	   }
	 
	 fclose($file_handle);
	 }



// - Datensatz löschen -----------------------------------

if($mode=="delete")
 {
 $filename = "rooms.txt";

 $dat = file($filename);
 $row_count = count($dat);

 $file_handle = fopen($filename, 'w+');

 for ($row = 0; $row < $row_count; $row++)
   {
   if ($row != $item)
     {
     fwrite($file_handle, $dat[$row]);
     }
   }
 
 fclose($file_handle);
 }


?>

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
	<td width="120" align="left"><b>Room Name</b></td>	
	<td width="120" align="left"><b>System</b></td>
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
	<td  align="left"><?PHP echo $parts[2]; ?></td>	
	<td  align="left"><?PHP echo $parts[3]; ?></td>
	<td  align="left">
	    <button  onclick="window.location.href='edit.php?item=<?PHP echo $i;?>';">Edit</button>
	    <button  onclick="window.location.href='index.php?mode=delete&item=<?PHP echo $i;?>';">Delete</button>
	</td>	
</tr>
<?PHP } ?>  
 <tr> 
	<td  align="left"></td>
	<td  align="left"></td>		
	<td  align="left"></td>	
	<td  align="left"></td>	
	<td  align="left"></td>
	<td  align="left">
	    <button  onclick="window.location.href='edit.php?item=NEW';">New</button>
	</td>	
</tr>


</table>

</BODY>
</HTML>
