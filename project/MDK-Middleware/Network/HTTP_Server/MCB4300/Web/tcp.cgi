t <html><head><title>TCP Socket Status</title>
t <meta http-equiv="refresh" content="5"></head>
i pg_header.inc
t <h2 align=center><br>Tcp Socket online Status</h2>
t <center>
t <table border=0 width=99%><font size="3">
t <tr bgcolor=#aaccff>
t  <th width=10%>Socket</th>
t  <th width=16%>State</th>
t  <th width=10%>Port</th>
t  <th width=10%>Timer</th>
t  <th width=44% bgcolor=#aacc00>Remote Address</th>
t  <th width=10% bgcolor=#aacc0>Port</th>
t </tr>
c c
t </font></table>
t <form action=tcp.cgi method=post name=form1>
t  <table width=660>
t  <tr><td align="center">
t  <input type=button value="Refresh" onclick="location='/tcp.cgi'">
t  </td></tr></table>
t  </center>
t </form>
i pg_footer.inc
. End of script must be closed with period.

