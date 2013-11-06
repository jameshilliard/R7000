<!--
$Copyright Open Broadcom Corporation$

$Id: iptv.asp 332154 2012-05-09 08:41:22Z marc $
-->

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html lang="en">
<head>
<title>Broadcom Home Gateway Reference Design: Media</title>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<link rel="stylesheet" type="text/css" href="style.css" media="screen">
<script language="JavaScript" type="text/javascript" src="overlib.js"></script>
</head>

<body>
<div id="overDiv" style="position:absolute; visibility:hidden; z-index:1000;"></div>

<table border="0" cellpadding="0" cellspacing="0" width="100%" bgcolor="#cc0000">
  <% asp_list(); %>
</table>

<table border="0" cellpadding="0" cellspacing="0" width="100%">
  <tr>
    <td colspan="2" class="edge"><img border="0" src="blur_new.jpg" alt=""></td>
  </tr>
  <tr>
    <td><img border="0" src="logo_new.gif" alt=""></td>
    <td width="100%" valign="top">
	<br>
	<span class="title">Media</span><br>
	<span class="subtitle">This page allows you to configure the
	basic Media related parameters.</span>
    </td>
  </tr>
</table>

<form method="post" action="media.asp">
<input type="hidden" name="page" value="media.asp">

<p>
<table border="0" cellpadding="0" cellspacing="0">
    <tr>
    <th width="310"
        onMouseOver="return overlib('Enable IGMP Proxy in AP mode: 0: disable; 1: enable', LEFT);"
        onMouseOut="return nd();">
        Enable IGMP Proxy: &nbsp;&nbsp;
    </th>
    <td>&nbsp;&nbsp;</td>
    <td><select name="igmp_enable" value="<% nvram_get("igmp_enable"); %>">
		<option value="0" <% nvram_match("igmp_enable", "0", "selected"); %>>Disable</option>
		<option value="1" <% nvram_match("igmp_enable", "1", "selected"); %>>Enable</option>
	</td>
  </tr>
</table>

<!--
#if defined(TRAFFIC_MGMT) || defined(WET_TUNNEL) || defined(TRAFFIC_MGMT_RSSI_POLICY)
-->
<p>
<table border="0" cellpadding="0" cellspacing="0">
  <tr>
    <th width="310"
	onMouseOver="return overlib('Selects which wireless interface to configure.', LEFT);"
	onMouseOut="return nd();">
	Wireless Interface:&nbsp;&nbsp;
    </th>
    <td>&nbsp;&nbsp;</td>
    <td>
	<select name="wl_unit" onChange="submit();">
	  <% wl_list(); %>
	</select>
    </td>
  </tr>
</table>
<!--
#endif
-->

<!--
#ifdef WET_TUNNEL
-->
<% wet_tunnel_display(); %>
<!--
#endif
-->

<!--
#ifdef TRAFFIC_MGMT_RSSI_POLICY
-->
<p>
<table border="0" cellpadding="0" cellspacing="0">
  <tr>
    <th width="310"
	onMouseOver="return overlib('Set to map lowest RSSI STA to low priority(BE) or disable.', LEFT);"
	onMouseOut="return nd();">
	Traffic Management RSSI Policy:&nbsp;&nbsp;
    </th>
    <td>&nbsp;&nbsp;</td>
    <td>
	<select name="wl_trf_mgmt_rssi_policy">
	  <option value="0" <% nvram_match("wl_trf_mgmt_rssi_policy", "0", "selected"); %>>None</option>
	  <option value="1" <% nvram_match("wl_trf_mgmt_rssi_policy", "1", "selected"); %>>Lowest RSSI</option>
	</select>
    </td>
  </tr>
</table>
<!--
#endif
-->

<!--
#ifdef TRAFFIC_MGMT
-->
<p>
<table border="0" cellpadding="0" cellspacing="0">
  <tr>
    <th width="310" valign="top" rowspan="11"
        onMouseOver="return overlib('Adds up to 10 traffic management filters which specifies the TCP/UDP port, MAC and priority.', LEFT);"
        onMouseOut="return nd();">
        <input type="hidden" name="trf_mgmt_port" value="10">
        Traffic Management Settings:&nbsp;&nbsp;
    </th>
    <td>&nbsp;&nbsp;</td>
    <td class="label">Protocol</td>
    <td></td>
    <td class="label">Src Port</td>
    <td></td>
    <td class="label">Dst Port</td>
    <td></td>
    <td class="label">Mac Addr</td>
    <td></td>
    <td class="label">Priority</td>
    <td></td>
    <td class="label">Favored</td>
    <td></td>
    <td class="label">Enabled</td>
  </tr>
  <% trf_mgmt_port(0, 9); %>
</table>
<!--
#endif
-->

<p>
<table border="0" cellpadding="0" cellspacing="0">
    <tr>
      <td width="310"></td>
      <td>&nbsp;&nbsp;</td>
      <td>
	  <input type="submit" name="action" value="Apply">
	  <input type="reset" name="action" value="Cancel">
      </td>
    </tr>
</table>

</form>

<p class="label">&#169;2001-2012 Broadcom Corporation. All rights reserved.</p>

</body>
</html>

