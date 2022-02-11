<HTML>
<HEAD>
<TITLE>Meet</TITLE> 
<link rel="stylesheet" type="text/css" href="style/s.css">
<meta name="viewport" content="width=device-width,height=device-height,minimum-scale=1,maximum-scale=1"/>
</HEAD>

<BODY BGCOLOR="#FFFFFF" TEXT="#000000">


<?PHP

$item = $_GET["item"];

$data = file("rooms.txt");

@   $parts = explode(";", $data[$item]);			// open item and show it

?>







<h1>Meet Rooms</h1>

 
<table>

<form method="GET" action="index.php" enctype="multipart/form-data">	

<tr>
 <td valign="top"><span class="normal"><b>Room Name</b></span></td>
 <td valign="top"><input class="textfeld" style="width: 350px;" size="50" type="text" name="RoomName" value="<?PHP echo $parts[0]; ?>"></td>
</tr>

<tr>
 <td width="220"  valign="top"><span class="normal"><b>System</b></span></td>
 <td width="350" valign="top"> 
				 <select class="textfeld" style="width: 350px;" id="system" name="System" value="<?PHP echo $parts[1]; ?>">
				  <option value="Jitsi">Jitsi</option>
				</select>
</td>
</tr>

<tr>
 <td valign="top"><span class="normal"><b>Meeting Link</b></span></td>
 <td valign="top"><input class="textfeld" style="width: 350px;" size="50" type="text" name="MeetingLink" value="<?PHP echo $parts[2]; ?>"></td>
</tr>

<tr>
 <td valign="top"><span class="normal"><b>Display Name</b></span></td>
 <td valign="top"><input class="textfeld" style="width: 350px;" size="50" type="text" name="DisplayName" value="<?PHP echo $parts[3]; ?>"></td>
</tr>

<input type="hidden" name="item" value="<?PHP echo $item; ?>">	

<tr>
 <td valign="top"><span class="normal"></td>
 <td valign="top"><button onclick="window.location.href='index.php';">Cancel</button><input  class="textfeld" type="submit" name="Save" value="Save"></td>
</tr>


</table>


</BODY>
</HTML>

