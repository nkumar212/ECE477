<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="6.4">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="MinotaurParts">
<packages>
<package name="TQFP64_10X10MC">
<smd name="1" x="-5.6134" y="3.7592" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="2" x="-5.6134" y="3.2512" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="3" x="-5.6134" y="2.7432" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="4" x="-5.6134" y="2.2606" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="5" x="-5.6134" y="1.7526" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="6" x="-5.6134" y="1.2446" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="7" x="-5.6134" y="0.762" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="8" x="-5.6134" y="0.254" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="9" x="-5.6134" y="-0.254" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="10" x="-5.6134" y="-0.762" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="11" x="-5.6134" y="-1.2446" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="12" x="-5.6134" y="-1.7526" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="13" x="-5.6134" y="-2.2606" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="14" x="-5.6134" y="-2.7432" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="15" x="-5.6134" y="-3.2512" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="16" x="-5.6134" y="-3.7592" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="17" x="-3.7592" y="-5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="18" x="-3.2512" y="-5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="19" x="-2.7432" y="-5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="20" x="-2.2606" y="-5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="21" x="-1.7526" y="-5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="22" x="-1.2446" y="-5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="23" x="-0.762" y="-5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="24" x="-0.254" y="-5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="25" x="0.254" y="-5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="26" x="0.762" y="-5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="27" x="1.2446" y="-5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="28" x="1.7526" y="-5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="29" x="2.2606" y="-5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="30" x="2.7432" y="-5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="31" x="3.2512" y="-5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="32" x="3.7592" y="-5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="33" x="5.6134" y="-3.7592" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="34" x="5.6134" y="-3.2512" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="35" x="5.6134" y="-2.7432" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="36" x="5.6134" y="-2.2606" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="37" x="5.6134" y="-1.7526" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="38" x="5.6134" y="-1.2446" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="39" x="5.6134" y="-0.762" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="40" x="5.6134" y="-0.254" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="41" x="5.6134" y="0.254" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="42" x="5.6134" y="0.762" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="43" x="5.6134" y="1.2446" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="44" x="5.6134" y="1.7526" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="45" x="5.6134" y="2.2606" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="46" x="5.6134" y="2.7432" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="47" x="5.6134" y="3.2512" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="48" x="5.6134" y="3.7592" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="49" x="3.7592" y="5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="50" x="3.2512" y="5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="51" x="2.7432" y="5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="52" x="2.2606" y="5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="53" x="1.7526" y="5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="54" x="1.2446" y="5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="55" x="0.762" y="5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="56" x="0.254" y="5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="57" x="-0.254" y="5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="58" x="-0.762" y="5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="59" x="-1.2446" y="5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="60" x="-1.7526" y="5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="61" x="-2.2606" y="5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="62" x="-2.7432" y="5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="63" x="-3.2512" y="5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="64" x="-3.7592" y="5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<wire x1="-4.6228" y1="4.1148" x2="-4.1148" y2="4.6228" width="0.1524" layer="51"/>
<wire x1="-5.0038" y1="-5.0038" x2="-4.2164" y2="-5.0038" width="0.1524" layer="51"/>
<wire x1="5.0038" y1="-5.0038" x2="5.0038" y2="-4.2164" width="0.1524" layer="51"/>
<wire x1="5.0038" y1="5.0038" x2="4.2164" y2="5.0038" width="0.1524" layer="51"/>
<wire x1="-5.0038" y1="5.0038" x2="-5.0038" y2="4.2164" width="0.1524" layer="51"/>
<wire x1="-5.0038" y1="-4.2164" x2="-5.0038" y2="-5.0038" width="0.1524" layer="51"/>
<wire x1="4.2164" y1="-5.0038" x2="5.0038" y2="-5.0038" width="0.1524" layer="51"/>
<wire x1="5.0038" y1="4.2164" x2="5.0038" y2="5.0038" width="0.1524" layer="51"/>
<wire x1="-4.2164" y1="5.0038" x2="-5.0038" y2="5.0038" width="0.1524" layer="51"/>
<text x="-7.5692" y="3.7338" size="1.27" layer="51" ratio="6" rot="SR0">*</text>
<text x="-3.2766" y="-0.635" size="1.27" layer="51" ratio="6" rot="SR0">RefDes</text>
<text x="-1.7272" y="-0.635" size="1.27" layer="51" ratio="6" rot="SR0">DEV</text>
<text x="-1.143" y="-0.635" size="1.27" layer="51" ratio="6" rot="SR0">PN</text>
<text x="-1.7272" y="-0.635" size="1.27" layer="51" ratio="6" rot="SR0">DEV</text>
<text x="-1.7272" y="-0.635" size="1.27" layer="51" ratio="6" rot="SR0">VAL</text>
<text x="-1.7272" y="-0.635" size="1.27" layer="51" ratio="6" rot="SR0">TOL</text>
<wire x1="3.6068" y1="5.0038" x2="3.8862" y2="5.0038" width="0" layer="21"/>
<wire x1="3.8862" y1="5.0038" x2="3.8862" y2="5.9944" width="0" layer="21"/>
<wire x1="3.8862" y1="5.9944" x2="3.6068" y2="5.9944" width="0" layer="21"/>
<wire x1="3.6068" y1="5.9944" x2="3.6068" y2="5.0038" width="0" layer="21"/>
<wire x1="3.0988" y1="5.0038" x2="3.3782" y2="5.0038" width="0" layer="21"/>
<wire x1="3.3782" y1="5.0038" x2="3.3782" y2="5.9944" width="0" layer="21"/>
<wire x1="3.3782" y1="5.9944" x2="3.0988" y2="5.9944" width="0" layer="21"/>
<wire x1="3.0988" y1="5.9944" x2="3.0988" y2="5.0038" width="0" layer="21"/>
<wire x1="2.6162" y1="5.0038" x2="2.8956" y2="5.0038" width="0" layer="21"/>
<wire x1="2.8956" y1="5.0038" x2="2.8956" y2="5.9944" width="0" layer="21"/>
<wire x1="2.8956" y1="5.9944" x2="2.6162" y2="5.9944" width="0" layer="21"/>
<wire x1="2.6162" y1="5.9944" x2="2.6162" y2="5.0038" width="0" layer="21"/>
<wire x1="2.1082" y1="5.0038" x2="2.3876" y2="5.0038" width="0" layer="21"/>
<wire x1="2.3876" y1="5.0038" x2="2.3876" y2="5.9944" width="0" layer="21"/>
<wire x1="2.3876" y1="5.9944" x2="2.1082" y2="5.9944" width="0" layer="21"/>
<wire x1="2.1082" y1="5.9944" x2="2.1082" y2="5.0038" width="0" layer="21"/>
<wire x1="1.6002" y1="5.0038" x2="1.8796" y2="5.0038" width="0" layer="21"/>
<wire x1="1.8796" y1="5.0038" x2="1.8796" y2="5.9944" width="0" layer="21"/>
<wire x1="1.8796" y1="5.9944" x2="1.6002" y2="5.9944" width="0" layer="21"/>
<wire x1="1.6002" y1="5.9944" x2="1.6002" y2="5.0038" width="0" layer="21"/>
<wire x1="1.1176" y1="5.0038" x2="1.397" y2="5.0038" width="0" layer="21"/>
<wire x1="1.397" y1="5.0038" x2="1.397" y2="5.9944" width="0" layer="21"/>
<wire x1="1.397" y1="5.9944" x2="1.1176" y2="5.9944" width="0" layer="21"/>
<wire x1="1.1176" y1="5.9944" x2="1.1176" y2="5.0038" width="0" layer="21"/>
<wire x1="0.6096" y1="5.0038" x2="0.889" y2="5.0038" width="0" layer="21"/>
<wire x1="0.889" y1="5.0038" x2="0.889" y2="5.9944" width="0" layer="21"/>
<wire x1="0.889" y1="5.9944" x2="0.6096" y2="5.9944" width="0" layer="21"/>
<wire x1="0.6096" y1="5.9944" x2="0.6096" y2="5.0038" width="0" layer="21"/>
<wire x1="0.1016" y1="5.0038" x2="0.381" y2="5.0038" width="0" layer="21"/>
<wire x1="0.381" y1="5.0038" x2="0.381" y2="5.9944" width="0" layer="21"/>
<wire x1="0.381" y1="5.9944" x2="0.1016" y2="5.9944" width="0" layer="21"/>
<wire x1="0.1016" y1="5.9944" x2="0.1016" y2="5.0038" width="0" layer="21"/>
<wire x1="-0.381" y1="5.0038" x2="-0.1016" y2="5.0038" width="0" layer="21"/>
<wire x1="-0.1016" y1="5.0038" x2="-0.1016" y2="5.9944" width="0" layer="21"/>
<wire x1="-0.1016" y1="5.9944" x2="-0.381" y2="5.9944" width="0" layer="21"/>
<wire x1="-0.381" y1="5.9944" x2="-0.381" y2="5.0038" width="0" layer="21"/>
<wire x1="-0.889" y1="5.0038" x2="-0.6096" y2="5.0038" width="0" layer="21"/>
<wire x1="-0.6096" y1="5.0038" x2="-0.6096" y2="5.9944" width="0" layer="21"/>
<wire x1="-0.6096" y1="5.9944" x2="-0.889" y2="5.9944" width="0" layer="21"/>
<wire x1="-0.889" y1="5.9944" x2="-0.889" y2="5.0038" width="0" layer="21"/>
<wire x1="-1.397" y1="5.0038" x2="-1.1176" y2="5.0038" width="0" layer="21"/>
<wire x1="-1.1176" y1="5.0038" x2="-1.1176" y2="5.9944" width="0" layer="21"/>
<wire x1="-1.1176" y1="5.9944" x2="-1.397" y2="5.9944" width="0" layer="21"/>
<wire x1="-1.397" y1="5.9944" x2="-1.397" y2="5.0038" width="0" layer="21"/>
<wire x1="-1.8796" y1="5.0038" x2="-1.6002" y2="5.0038" width="0" layer="21"/>
<wire x1="-1.6002" y1="5.0038" x2="-1.6002" y2="5.9944" width="0" layer="21"/>
<wire x1="-1.6002" y1="5.9944" x2="-1.8796" y2="5.9944" width="0" layer="21"/>
<wire x1="-1.8796" y1="5.9944" x2="-1.8796" y2="5.0038" width="0" layer="21"/>
<wire x1="-2.3876" y1="5.0038" x2="-2.1082" y2="5.0038" width="0" layer="21"/>
<wire x1="-2.1082" y1="5.0038" x2="-2.1082" y2="5.9944" width="0" layer="21"/>
<wire x1="-2.1082" y1="5.9944" x2="-2.3876" y2="5.9944" width="0" layer="21"/>
<wire x1="-2.3876" y1="5.9944" x2="-2.3876" y2="5.0038" width="0" layer="21"/>
<wire x1="-2.8956" y1="5.0038" x2="-2.6162" y2="5.0038" width="0" layer="21"/>
<wire x1="-2.6162" y1="5.0038" x2="-2.6162" y2="5.9944" width="0" layer="21"/>
<wire x1="-2.6162" y1="5.9944" x2="-2.8956" y2="5.9944" width="0" layer="21"/>
<wire x1="-2.8956" y1="5.9944" x2="-2.8956" y2="5.0038" width="0" layer="21"/>
<wire x1="-3.3782" y1="5.0038" x2="-3.0988" y2="5.0038" width="0" layer="21"/>
<wire x1="-3.0988" y1="5.0038" x2="-3.0988" y2="5.9944" width="0" layer="21"/>
<wire x1="-3.0988" y1="5.9944" x2="-3.3782" y2="5.9944" width="0" layer="21"/>
<wire x1="-3.3782" y1="5.9944" x2="-3.3782" y2="5.0038" width="0" layer="21"/>
<wire x1="-3.8862" y1="5.0038" x2="-3.7338" y2="5.0038" width="0" layer="21"/>
<wire x1="-3.7338" y1="5.0038" x2="-3.6068" y2="5.0038" width="0" layer="21"/>
<wire x1="-3.6068" y1="5.0038" x2="-3.6068" y2="5.9944" width="0" layer="21"/>
<wire x1="-3.6068" y1="5.9944" x2="-3.8862" y2="5.9944" width="0" layer="21"/>
<wire x1="-3.8862" y1="5.9944" x2="-3.8862" y2="5.0038" width="0" layer="21"/>
<wire x1="-5.0038" y1="3.6068" x2="-5.0038" y2="3.7338" width="0" layer="21"/>
<wire x1="-5.0038" y1="3.7338" x2="-5.0038" y2="3.8862" width="0" layer="21"/>
<wire x1="-5.0038" y1="3.8862" x2="-5.9944" y2="3.8862" width="0" layer="21"/>
<wire x1="-5.9944" y1="3.8862" x2="-5.9944" y2="3.6068" width="0" layer="21"/>
<wire x1="-5.9944" y1="3.6068" x2="-5.0038" y2="3.6068" width="0" layer="21"/>
<wire x1="-5.0038" y1="3.0988" x2="-5.0038" y2="3.3782" width="0" layer="21"/>
<wire x1="-5.0038" y1="3.3782" x2="-5.9944" y2="3.3782" width="0" layer="21"/>
<wire x1="-5.9944" y1="3.3782" x2="-5.9944" y2="3.0988" width="0" layer="21"/>
<wire x1="-5.9944" y1="3.0988" x2="-5.0038" y2="3.0988" width="0" layer="21"/>
<wire x1="-5.0038" y1="2.6162" x2="-5.0038" y2="2.8956" width="0" layer="21"/>
<wire x1="-5.0038" y1="2.8956" x2="-5.9944" y2="2.8956" width="0" layer="21"/>
<wire x1="-5.9944" y1="2.8956" x2="-5.9944" y2="2.6162" width="0" layer="21"/>
<wire x1="-5.9944" y1="2.6162" x2="-5.0038" y2="2.6162" width="0" layer="21"/>
<wire x1="-5.0038" y1="2.1082" x2="-5.0038" y2="2.3876" width="0" layer="21"/>
<wire x1="-5.0038" y1="2.3876" x2="-5.9944" y2="2.3876" width="0" layer="21"/>
<wire x1="-5.9944" y1="2.3876" x2="-5.9944" y2="2.1082" width="0" layer="21"/>
<wire x1="-5.9944" y1="2.1082" x2="-5.0038" y2="2.1082" width="0" layer="21"/>
<wire x1="-5.0038" y1="1.6002" x2="-5.0038" y2="1.8796" width="0" layer="21"/>
<wire x1="-5.0038" y1="1.8796" x2="-5.9944" y2="1.8796" width="0" layer="21"/>
<wire x1="-5.9944" y1="1.8796" x2="-5.9944" y2="1.6002" width="0" layer="21"/>
<wire x1="-5.9944" y1="1.6002" x2="-5.0038" y2="1.6002" width="0" layer="21"/>
<wire x1="-5.0038" y1="1.1176" x2="-5.0038" y2="1.397" width="0" layer="21"/>
<wire x1="-5.0038" y1="1.397" x2="-5.9944" y2="1.397" width="0" layer="21"/>
<wire x1="-5.9944" y1="1.397" x2="-5.9944" y2="1.1176" width="0" layer="21"/>
<wire x1="-5.9944" y1="1.1176" x2="-5.0038" y2="1.1176" width="0" layer="21"/>
<wire x1="-5.0038" y1="0.6096" x2="-5.0038" y2="0.889" width="0" layer="21"/>
<wire x1="-5.0038" y1="0.889" x2="-5.9944" y2="0.889" width="0" layer="21"/>
<wire x1="-5.9944" y1="0.889" x2="-5.9944" y2="0.6096" width="0" layer="21"/>
<wire x1="-5.9944" y1="0.6096" x2="-5.0038" y2="0.6096" width="0" layer="21"/>
<wire x1="-5.0038" y1="0.1016" x2="-5.0038" y2="0.381" width="0" layer="21"/>
<wire x1="-5.0038" y1="0.381" x2="-5.9944" y2="0.381" width="0" layer="21"/>
<wire x1="-5.9944" y1="0.381" x2="-5.9944" y2="0.1016" width="0" layer="21"/>
<wire x1="-5.9944" y1="0.1016" x2="-5.0038" y2="0.1016" width="0" layer="21"/>
<wire x1="-5.0038" y1="-0.381" x2="-5.0038" y2="-0.1016" width="0" layer="21"/>
<wire x1="-5.0038" y1="-0.1016" x2="-5.9944" y2="-0.1016" width="0" layer="21"/>
<wire x1="-5.9944" y1="-0.1016" x2="-5.9944" y2="-0.381" width="0" layer="21"/>
<wire x1="-5.9944" y1="-0.381" x2="-5.0038" y2="-0.381" width="0" layer="21"/>
<wire x1="-5.0038" y1="-0.889" x2="-5.0038" y2="-0.6096" width="0" layer="21"/>
<wire x1="-5.0038" y1="-0.6096" x2="-5.9944" y2="-0.6096" width="0" layer="21"/>
<wire x1="-5.9944" y1="-0.6096" x2="-5.9944" y2="-0.889" width="0" layer="21"/>
<wire x1="-5.9944" y1="-0.889" x2="-5.0038" y2="-0.889" width="0" layer="21"/>
<wire x1="-5.0038" y1="-1.397" x2="-5.0038" y2="-1.1176" width="0" layer="21"/>
<wire x1="-5.0038" y1="-1.1176" x2="-5.9944" y2="-1.1176" width="0" layer="21"/>
<wire x1="-5.9944" y1="-1.1176" x2="-5.9944" y2="-1.397" width="0" layer="21"/>
<wire x1="-5.9944" y1="-1.397" x2="-5.0038" y2="-1.397" width="0" layer="21"/>
<wire x1="-5.0038" y1="-1.8796" x2="-5.0038" y2="-1.6002" width="0" layer="21"/>
<wire x1="-5.0038" y1="-1.6002" x2="-5.9944" y2="-1.6002" width="0" layer="21"/>
<wire x1="-5.9944" y1="-1.6002" x2="-5.9944" y2="-1.8796" width="0" layer="21"/>
<wire x1="-5.9944" y1="-1.8796" x2="-5.0038" y2="-1.8796" width="0" layer="21"/>
<wire x1="-5.0038" y1="-2.3876" x2="-5.0038" y2="-2.1082" width="0" layer="21"/>
<wire x1="-5.0038" y1="-2.1082" x2="-5.9944" y2="-2.1082" width="0" layer="21"/>
<wire x1="-5.9944" y1="-2.1082" x2="-5.9944" y2="-2.3876" width="0" layer="21"/>
<wire x1="-5.9944" y1="-2.3876" x2="-5.0038" y2="-2.3876" width="0" layer="21"/>
<wire x1="-5.0038" y1="-2.8956" x2="-5.0038" y2="-2.6162" width="0" layer="21"/>
<wire x1="-5.0038" y1="-2.6162" x2="-5.9944" y2="-2.6162" width="0" layer="21"/>
<wire x1="-5.9944" y1="-2.6162" x2="-5.9944" y2="-2.8956" width="0" layer="21"/>
<wire x1="-5.9944" y1="-2.8956" x2="-5.0038" y2="-2.8956" width="0" layer="21"/>
<wire x1="-5.0038" y1="-3.3782" x2="-5.0038" y2="-3.0988" width="0" layer="21"/>
<wire x1="-5.0038" y1="-3.0988" x2="-5.9944" y2="-3.0988" width="0" layer="21"/>
<wire x1="-5.9944" y1="-3.0988" x2="-5.9944" y2="-3.3782" width="0" layer="21"/>
<wire x1="-5.9944" y1="-3.3782" x2="-5.0038" y2="-3.3782" width="0" layer="21"/>
<wire x1="-5.0038" y1="-3.8862" x2="-5.0038" y2="-3.6068" width="0" layer="21"/>
<wire x1="-5.0038" y1="-3.6068" x2="-5.9944" y2="-3.6068" width="0" layer="21"/>
<wire x1="-5.9944" y1="-3.6068" x2="-5.9944" y2="-3.8862" width="0" layer="21"/>
<wire x1="-5.9944" y1="-3.8862" x2="-5.0038" y2="-3.8862" width="0" layer="21"/>
<wire x1="-3.6068" y1="-5.0038" x2="-3.8862" y2="-5.0038" width="0" layer="21"/>
<wire x1="-3.8862" y1="-5.0038" x2="-3.8862" y2="-5.9944" width="0" layer="21"/>
<wire x1="-3.8862" y1="-5.9944" x2="-3.6068" y2="-5.9944" width="0" layer="21"/>
<wire x1="-3.6068" y1="-5.9944" x2="-3.6068" y2="-5.0038" width="0" layer="21"/>
<wire x1="-3.0988" y1="-5.0038" x2="-3.3782" y2="-5.0038" width="0" layer="21"/>
<wire x1="-3.3782" y1="-5.0038" x2="-3.3782" y2="-5.9944" width="0" layer="21"/>
<wire x1="-3.3782" y1="-5.9944" x2="-3.0988" y2="-5.9944" width="0" layer="21"/>
<wire x1="-3.0988" y1="-5.9944" x2="-3.0988" y2="-5.0038" width="0" layer="21"/>
<wire x1="-2.6162" y1="-5.0038" x2="-2.8956" y2="-5.0038" width="0" layer="21"/>
<wire x1="-2.8956" y1="-5.0038" x2="-2.8956" y2="-5.9944" width="0" layer="21"/>
<wire x1="-2.8956" y1="-5.9944" x2="-2.6162" y2="-5.9944" width="0" layer="21"/>
<wire x1="-2.6162" y1="-5.9944" x2="-2.6162" y2="-5.0038" width="0" layer="21"/>
<wire x1="-2.1082" y1="-5.0038" x2="-2.3876" y2="-5.0038" width="0" layer="21"/>
<wire x1="-2.3876" y1="-5.0038" x2="-2.3876" y2="-5.9944" width="0" layer="21"/>
<wire x1="-2.3876" y1="-5.9944" x2="-2.1082" y2="-5.9944" width="0" layer="21"/>
<wire x1="-2.1082" y1="-5.9944" x2="-2.1082" y2="-5.0038" width="0" layer="21"/>
<wire x1="-1.6002" y1="-5.0038" x2="-1.8796" y2="-5.0038" width="0" layer="21"/>
<wire x1="-1.8796" y1="-5.0038" x2="-1.8796" y2="-5.9944" width="0" layer="21"/>
<wire x1="-1.8796" y1="-5.9944" x2="-1.6002" y2="-5.9944" width="0" layer="21"/>
<wire x1="-1.6002" y1="-5.9944" x2="-1.6002" y2="-5.0038" width="0" layer="21"/>
<wire x1="-1.1176" y1="-5.0038" x2="-1.397" y2="-5.0038" width="0" layer="21"/>
<wire x1="-1.397" y1="-5.0038" x2="-1.397" y2="-5.9944" width="0" layer="21"/>
<wire x1="-1.397" y1="-5.9944" x2="-1.1176" y2="-5.9944" width="0" layer="21"/>
<wire x1="-1.1176" y1="-5.9944" x2="-1.1176" y2="-5.0038" width="0" layer="21"/>
<wire x1="-0.6096" y1="-5.0038" x2="-0.889" y2="-5.0038" width="0" layer="21"/>
<wire x1="-0.889" y1="-5.0038" x2="-0.889" y2="-5.9944" width="0" layer="21"/>
<wire x1="-0.889" y1="-5.9944" x2="-0.6096" y2="-5.9944" width="0" layer="21"/>
<wire x1="-0.6096" y1="-5.9944" x2="-0.6096" y2="-5.0038" width="0" layer="21"/>
<wire x1="-0.1016" y1="-5.0038" x2="-0.381" y2="-5.0038" width="0" layer="21"/>
<wire x1="-0.381" y1="-5.0038" x2="-0.381" y2="-5.9944" width="0" layer="21"/>
<wire x1="-0.381" y1="-5.9944" x2="-0.1016" y2="-5.9944" width="0" layer="21"/>
<wire x1="-0.1016" y1="-5.9944" x2="-0.1016" y2="-5.0038" width="0" layer="21"/>
<wire x1="0.381" y1="-5.0038" x2="0.1016" y2="-5.0038" width="0" layer="21"/>
<wire x1="0.1016" y1="-5.0038" x2="0.1016" y2="-5.9944" width="0" layer="21"/>
<wire x1="0.1016" y1="-5.9944" x2="0.381" y2="-5.9944" width="0" layer="21"/>
<wire x1="0.381" y1="-5.9944" x2="0.381" y2="-5.0038" width="0" layer="21"/>
<wire x1="0.889" y1="-5.0038" x2="0.6096" y2="-5.0038" width="0" layer="21"/>
<wire x1="0.6096" y1="-5.0038" x2="0.6096" y2="-5.9944" width="0" layer="21"/>
<wire x1="0.6096" y1="-5.9944" x2="0.889" y2="-5.9944" width="0" layer="21"/>
<wire x1="0.889" y1="-5.9944" x2="0.889" y2="-5.0038" width="0" layer="21"/>
<wire x1="1.397" y1="-5.0038" x2="1.1176" y2="-5.0038" width="0" layer="21"/>
<wire x1="1.1176" y1="-5.0038" x2="1.1176" y2="-5.9944" width="0" layer="21"/>
<wire x1="1.1176" y1="-5.9944" x2="1.397" y2="-5.9944" width="0" layer="21"/>
<wire x1="1.397" y1="-5.9944" x2="1.397" y2="-5.0038" width="0" layer="21"/>
<wire x1="1.8796" y1="-5.0038" x2="1.6002" y2="-5.0038" width="0" layer="21"/>
<wire x1="1.6002" y1="-5.0038" x2="1.6002" y2="-5.9944" width="0" layer="21"/>
<wire x1="1.6002" y1="-5.9944" x2="1.8796" y2="-5.9944" width="0" layer="21"/>
<wire x1="1.8796" y1="-5.9944" x2="1.8796" y2="-5.0038" width="0" layer="21"/>
<wire x1="2.3876" y1="-5.0038" x2="2.1082" y2="-5.0038" width="0" layer="21"/>
<wire x1="2.1082" y1="-5.0038" x2="2.1082" y2="-5.9944" width="0" layer="21"/>
<wire x1="2.1082" y1="-5.9944" x2="2.3876" y2="-5.9944" width="0" layer="21"/>
<wire x1="2.3876" y1="-5.9944" x2="2.3876" y2="-5.0038" width="0" layer="21"/>
<wire x1="2.8956" y1="-5.0038" x2="2.6162" y2="-5.0038" width="0" layer="21"/>
<wire x1="2.6162" y1="-5.0038" x2="2.6162" y2="-5.9944" width="0" layer="21"/>
<wire x1="2.6162" y1="-5.9944" x2="2.8956" y2="-5.9944" width="0" layer="21"/>
<wire x1="2.8956" y1="-5.9944" x2="2.8956" y2="-5.0038" width="0" layer="21"/>
<wire x1="3.3782" y1="-5.0038" x2="3.0988" y2="-5.0038" width="0" layer="21"/>
<wire x1="3.0988" y1="-5.0038" x2="3.0988" y2="-5.9944" width="0" layer="21"/>
<wire x1="3.0988" y1="-5.9944" x2="3.3782" y2="-5.9944" width="0" layer="21"/>
<wire x1="3.3782" y1="-5.9944" x2="3.3782" y2="-5.0038" width="0" layer="21"/>
<wire x1="3.8862" y1="-5.0038" x2="3.6068" y2="-5.0038" width="0" layer="21"/>
<wire x1="3.6068" y1="-5.0038" x2="3.6068" y2="-5.9944" width="0" layer="21"/>
<wire x1="3.6068" y1="-5.9944" x2="3.8862" y2="-5.9944" width="0" layer="21"/>
<wire x1="3.8862" y1="-5.9944" x2="3.8862" y2="-5.0038" width="0" layer="21"/>
<wire x1="5.0038" y1="-3.6068" x2="5.0038" y2="-3.8862" width="0" layer="21"/>
<wire x1="5.0038" y1="-3.8862" x2="5.9944" y2="-3.8862" width="0" layer="21"/>
<wire x1="5.9944" y1="-3.8862" x2="5.9944" y2="-3.6068" width="0" layer="21"/>
<wire x1="5.9944" y1="-3.6068" x2="5.0038" y2="-3.6068" width="0" layer="21"/>
<wire x1="5.0038" y1="-3.0988" x2="5.0038" y2="-3.3782" width="0" layer="21"/>
<wire x1="5.0038" y1="-3.3782" x2="5.9944" y2="-3.3782" width="0" layer="21"/>
<wire x1="5.9944" y1="-3.3782" x2="5.9944" y2="-3.0988" width="0" layer="21"/>
<wire x1="5.9944" y1="-3.0988" x2="5.0038" y2="-3.0988" width="0" layer="21"/>
<wire x1="5.0038" y1="-2.6162" x2="5.0038" y2="-2.8956" width="0" layer="21"/>
<wire x1="5.0038" y1="-2.8956" x2="5.9944" y2="-2.8956" width="0" layer="21"/>
<wire x1="5.9944" y1="-2.8956" x2="5.9944" y2="-2.6162" width="0" layer="21"/>
<wire x1="5.9944" y1="-2.6162" x2="5.0038" y2="-2.6162" width="0" layer="21"/>
<wire x1="5.0038" y1="-2.1082" x2="5.0038" y2="-2.3876" width="0" layer="21"/>
<wire x1="5.0038" y1="-2.3876" x2="5.9944" y2="-2.3876" width="0" layer="21"/>
<wire x1="5.9944" y1="-2.3876" x2="5.9944" y2="-2.1082" width="0" layer="21"/>
<wire x1="5.9944" y1="-2.1082" x2="5.0038" y2="-2.1082" width="0" layer="21"/>
<wire x1="5.0038" y1="-1.6002" x2="5.0038" y2="-1.8796" width="0" layer="21"/>
<wire x1="5.0038" y1="-1.8796" x2="5.9944" y2="-1.8796" width="0" layer="21"/>
<wire x1="5.9944" y1="-1.8796" x2="5.9944" y2="-1.6002" width="0" layer="21"/>
<wire x1="5.9944" y1="-1.6002" x2="5.0038" y2="-1.6002" width="0" layer="21"/>
<wire x1="5.0038" y1="-1.1176" x2="5.0038" y2="-1.397" width="0" layer="21"/>
<wire x1="5.0038" y1="-1.397" x2="5.9944" y2="-1.397" width="0" layer="21"/>
<wire x1="5.9944" y1="-1.397" x2="5.9944" y2="-1.1176" width="0" layer="21"/>
<wire x1="5.9944" y1="-1.1176" x2="5.0038" y2="-1.1176" width="0" layer="21"/>
<wire x1="5.0038" y1="-0.6096" x2="5.0038" y2="-0.889" width="0" layer="21"/>
<wire x1="5.0038" y1="-0.889" x2="5.9944" y2="-0.889" width="0" layer="21"/>
<wire x1="5.9944" y1="-0.889" x2="5.9944" y2="-0.6096" width="0" layer="21"/>
<wire x1="5.9944" y1="-0.6096" x2="5.0038" y2="-0.6096" width="0" layer="21"/>
<wire x1="5.0038" y1="-0.1016" x2="5.0038" y2="-0.381" width="0" layer="21"/>
<wire x1="5.0038" y1="-0.381" x2="5.9944" y2="-0.381" width="0" layer="21"/>
<wire x1="5.9944" y1="-0.381" x2="5.9944" y2="-0.1016" width="0" layer="21"/>
<wire x1="5.9944" y1="-0.1016" x2="5.0038" y2="-0.1016" width="0" layer="21"/>
<wire x1="5.0038" y1="0.381" x2="5.0038" y2="0.1016" width="0" layer="21"/>
<wire x1="5.0038" y1="0.1016" x2="5.9944" y2="0.1016" width="0" layer="21"/>
<wire x1="5.9944" y1="0.1016" x2="5.9944" y2="0.381" width="0" layer="21"/>
<wire x1="5.9944" y1="0.381" x2="5.0038" y2="0.381" width="0" layer="21"/>
<wire x1="5.0038" y1="0.889" x2="5.0038" y2="0.6096" width="0" layer="21"/>
<wire x1="5.0038" y1="0.6096" x2="5.9944" y2="0.6096" width="0" layer="21"/>
<wire x1="5.9944" y1="0.6096" x2="5.9944" y2="0.889" width="0" layer="21"/>
<wire x1="5.9944" y1="0.889" x2="5.0038" y2="0.889" width="0" layer="21"/>
<wire x1="5.0038" y1="1.397" x2="5.0038" y2="1.1176" width="0" layer="21"/>
<wire x1="5.0038" y1="1.1176" x2="5.9944" y2="1.1176" width="0" layer="21"/>
<wire x1="5.9944" y1="1.1176" x2="5.9944" y2="1.397" width="0" layer="21"/>
<wire x1="5.9944" y1="1.397" x2="5.0038" y2="1.397" width="0" layer="21"/>
<wire x1="5.0038" y1="1.8796" x2="5.0038" y2="1.6002" width="0" layer="21"/>
<wire x1="5.0038" y1="1.6002" x2="5.9944" y2="1.6002" width="0" layer="21"/>
<wire x1="5.9944" y1="1.6002" x2="5.9944" y2="1.8796" width="0" layer="21"/>
<wire x1="5.9944" y1="1.8796" x2="5.0038" y2="1.8796" width="0" layer="21"/>
<wire x1="5.0038" y1="2.3876" x2="5.0038" y2="2.1082" width="0" layer="21"/>
<wire x1="5.0038" y1="2.1082" x2="5.9944" y2="2.1082" width="0" layer="21"/>
<wire x1="5.9944" y1="2.1082" x2="5.9944" y2="2.3876" width="0" layer="21"/>
<wire x1="5.9944" y1="2.3876" x2="5.0038" y2="2.3876" width="0" layer="21"/>
<wire x1="5.0038" y1="2.8956" x2="5.0038" y2="2.6162" width="0" layer="21"/>
<wire x1="5.0038" y1="2.6162" x2="5.9944" y2="2.6162" width="0" layer="21"/>
<wire x1="5.9944" y1="2.6162" x2="5.9944" y2="2.8956" width="0" layer="21"/>
<wire x1="5.9944" y1="2.8956" x2="5.0038" y2="2.8956" width="0" layer="21"/>
<wire x1="5.0038" y1="3.3782" x2="5.0038" y2="3.0988" width="0" layer="21"/>
<wire x1="5.0038" y1="3.0988" x2="5.9944" y2="3.0988" width="0" layer="21"/>
<wire x1="5.9944" y1="3.0988" x2="5.9944" y2="3.3782" width="0" layer="21"/>
<wire x1="5.9944" y1="3.3782" x2="5.0038" y2="3.3782" width="0" layer="21"/>
<wire x1="5.0038" y1="3.8862" x2="5.0038" y2="3.6068" width="0" layer="21"/>
<wire x1="5.0038" y1="3.6068" x2="5.9944" y2="3.6068" width="0" layer="21"/>
<wire x1="5.9944" y1="3.6068" x2="5.9944" y2="3.8862" width="0" layer="21"/>
<wire x1="5.9944" y1="3.8862" x2="5.0038" y2="3.8862" width="0" layer="21"/>
<wire x1="-5.0038" y1="3.7338" x2="-3.7338" y2="5.0038" width="0" layer="21"/>
<wire x1="-5.0038" y1="-5.0038" x2="5.0038" y2="-5.0038" width="0" layer="21"/>
<wire x1="5.0038" y1="-5.0038" x2="5.0038" y2="5.0038" width="0" layer="21"/>
<wire x1="5.0038" y1="5.0038" x2="-5.0038" y2="5.0038" width="0" layer="21"/>
<wire x1="-5.0038" y1="5.0038" x2="-5.0038" y2="-5.0038" width="0" layer="21"/>
<text x="-7.5692" y="3.7338" size="1.27" layer="21" ratio="6" rot="SR0">*</text>
<text x="-3.8354" y="-0.635" size="1.27" layer="21" ratio="6" rot="SR0">RefDes2</text>
</package>
<package name="L298">
<smd name="GND3" x="-5.715" y="5.5" dx="1.1" dy="0.5" layer="1" rot="R90"/>
<smd name="SB" x="-4.445" y="5.5" dx="1.1" dy="0.5" layer="1" rot="R90"/>
<smd name="IN3" x="3.175" y="5.5" dx="1.1" dy="0.5" layer="1" rot="R90"/>
<smd name="N.C." x="-3.175" y="5.5" dx="1.1" dy="0.5" layer="1" rot="R90"/>
<smd name="ENB" x="1.905" y="5.5" dx="1.1" dy="0.5" layer="1" rot="R90"/>
<smd name="IN4" x="0.635" y="5.5" dx="1.1" dy="0.5" layer="1" rot="R90"/>
<smd name="VSS" x="4.445" y="5.5" dx="1.1" dy="0.5" layer="1" rot="R90"/>
<smd name="OUT4" x="-1.905" y="5.5" dx="1.1" dy="0.5" layer="1" rot="R90"/>
<smd name="OUT3" x="-0.635" y="5.5" dx="1.1" dy="0.5" layer="1" rot="R90"/>
<smd name="GND2" x="5.715" y="5.5" dx="1.1" dy="0.5" layer="1" rot="R90"/>
<smd name="GND" x="-5.715" y="-5.5" dx="1.1" dy="0.5" layer="1" rot="R90"/>
<smd name="OUT1" x="-1.905" y="-5.5" dx="1.1" dy="0.5" layer="1" rot="R90"/>
<smd name="SA" x="-4.445" y="-5.5" dx="1.1" dy="0.5" layer="1" rot="R90"/>
<smd name="NC" x="-3.175" y="-5.5" dx="1.1" dy="0.5" layer="1" rot="R90"/>
<smd name="OUT2" x="-0.635" y="-5.5" dx="1.1" dy="0.5" layer="1" rot="R90"/>
<smd name="VS" x="0.635" y="-5.5" dx="1.1" dy="0.5" layer="1" rot="R90"/>
<smd name="IN1" x="1.905" y="-5.5" dx="1.1" dy="0.5" layer="1" rot="R90"/>
<smd name="IN2" x="4.445" y="-5.5" dx="1.1" dy="0.5" layer="1" rot="R90"/>
<smd name="GND1" x="5.715" y="-5.5" dx="1.1" dy="0.5" layer="1" rot="R90"/>
<smd name="ENA" x="3.175" y="-5.5" dx="1.1" dy="0.5" layer="1" rot="R90"/>
<wire x1="-6" y1="-5.5" x2="-6.3" y2="-5.5" width="0.127" layer="21"/>
<wire x1="-6.3" y1="-5.5" x2="-7.4" y2="-4.4" width="0.127" layer="21"/>
<wire x1="-7.4" y1="-4.4" x2="-7.4" y2="-1.4" width="0.127" layer="21"/>
<wire x1="-7.4" y1="-1.4" x2="-6.5" y2="-1.4" width="0.127" layer="21"/>
<wire x1="-6.5" y1="-1.4" x2="-6.5" y2="1.4" width="0.127" layer="21"/>
<wire x1="-6.5" y1="1.4" x2="-7.4" y2="1.4" width="0.127" layer="21"/>
<wire x1="-7.4" y1="1.4" x2="-7.4" y2="5.5" width="0.127" layer="21"/>
<wire x1="-7.4" y1="5.5" x2="-6" y2="5.5" width="0.127" layer="21"/>
<wire x1="-5.4" y1="5.5" x2="-4.7" y2="5.5" width="0.127" layer="21"/>
<wire x1="-4.2" y1="5.5" x2="-3.4" y2="5.5" width="0.127" layer="21"/>
<wire x1="-2.9" y1="5.5" x2="-2.2" y2="5.5" width="0.127" layer="21"/>
<wire x1="-1.6" y1="5.5" x2="-0.9" y2="5.5" width="0.127" layer="21"/>
<wire x1="-0.4" y1="5.5" x2="0.4" y2="5.5" width="0.127" layer="21"/>
<wire x1="0.9" y1="5.5" x2="1.6" y2="5.5" width="0.127" layer="21"/>
<wire x1="2.2" y1="5.5" x2="2.9" y2="5.5" width="0.127" layer="21"/>
<wire x1="3.4" y1="5.5" x2="4.2" y2="5.5" width="0.127" layer="21"/>
<wire x1="4.7" y1="5.5" x2="5.5" y2="5.5" width="0.127" layer="21"/>
<wire x1="6" y1="5.5" x2="7.4" y2="5.5" width="0.127" layer="21"/>
<wire x1="7.4" y1="5.5" x2="7.4" y2="1.4" width="0.127" layer="21"/>
<wire x1="7.4" y1="1.4" x2="6.5" y2="1.4" width="0.127" layer="21"/>
<wire x1="6.5" y1="1.4" x2="6.5" y2="-1.4" width="0.127" layer="21"/>
<wire x1="6.5" y1="-1.4" x2="7.4" y2="-1.4" width="0.127" layer="21"/>
<wire x1="7.4" y1="-1.4" x2="7.4" y2="-5.5" width="0.127" layer="21"/>
<wire x1="7.4" y1="-5.5" x2="6" y2="-5.5" width="0.127" layer="21"/>
<wire x1="4.7" y1="-5.5" x2="5.5" y2="-5.5" width="0.127" layer="21"/>
<wire x1="4.2" y1="-5.5" x2="3.4" y2="-5.5" width="0.127" layer="21"/>
<wire x1="2.9" y1="-5.5" x2="2.1" y2="-5.5" width="0.127" layer="21"/>
<wire x1="1.6" y1="-5.5" x2="0.9" y2="-5.5" width="0.127" layer="21"/>
<wire x1="0.4" y1="-5.5" x2="-0.4" y2="-5.5" width="0.127" layer="21"/>
<wire x1="-0.9" y1="-5.5" x2="-1.7" y2="-5.5" width="0.127" layer="21"/>
<wire x1="-2.2" y1="-5.5" x2="-2.9" y2="-5.5" width="0.127" layer="21"/>
<wire x1="-3.4" y1="-5.5" x2="-4.2" y2="-5.5" width="0.127" layer="21"/>
<wire x1="-4.7" y1="-5.5" x2="-5.5" y2="-5.5" width="0.127" layer="21"/>
<text x="-13.9" y="-2.9" size="1.27" layer="25" rot="R90">&gt;NAME</text>
<text x="-11.5" y="-3" size="1.27" layer="27" rot="R90">&gt;VALUE</text>
</package>
<package name="SSOP-14">
<smd name="1" x="-1.95" y="-2.8" dx="0.3" dy="1.55" layer="1"/>
<smd name="2" x="-1.3" y="-2.8" dx="0.3" dy="1.55" layer="1"/>
<smd name="3" x="-0.65" y="-2.8" dx="0.3" dy="1.55" layer="1"/>
<smd name="4" x="0" y="-2.8" dx="0.3" dy="1.55" layer="1"/>
<smd name="5" x="0.65" y="-2.8" dx="0.3" dy="1.55" layer="1"/>
<smd name="6" x="1.3" y="-2.8" dx="0.3" dy="1.55" layer="1"/>
<smd name="7" x="1.95" y="-2.8" dx="0.3" dy="1.55" layer="1"/>
<smd name="14" x="-1.95" y="2.8" dx="0.3" dy="1.55" layer="1"/>
<smd name="13" x="-1.3" y="2.8" dx="0.3" dy="1.55" layer="1"/>
<smd name="12" x="-0.65" y="2.8" dx="0.3" dy="1.55" layer="1"/>
<smd name="11" x="0" y="2.8" dx="0.3" dy="1.55" layer="1"/>
<smd name="10" x="0.65" y="2.8" dx="0.3" dy="1.55" layer="1"/>
<smd name="9" x="1.3" y="2.8" dx="0.3" dy="1.55" layer="1"/>
<smd name="8" x="1.95" y="2.8" dx="0.3" dy="1.55" layer="1"/>
<wire x1="2.5" y1="2.2" x2="2.1" y2="2.2" width="0.127" layer="21"/>
<wire x1="1.7" y1="2.2" x2="1.5" y2="2.2" width="0.127" layer="21"/>
<wire x1="1.1" y1="2.2" x2="0.8" y2="2.2" width="0.127" layer="21"/>
<wire x1="0.5" y1="2.2" x2="0.2" y2="2.2" width="0.127" layer="21"/>
<wire x1="-0.2" y1="2.2" x2="-0.4" y2="2.2" width="0.127" layer="21"/>
<wire x1="-0.8" y1="2.2" x2="-1.1" y2="2.2" width="0.127" layer="21"/>
<wire x1="-1.5" y1="2.2" x2="-1.8" y2="2.2" width="0.127" layer="21"/>
<wire x1="-2.1" y1="2.2" x2="-2.6" y2="2.2" width="0.127" layer="21"/>
<wire x1="2.5" y1="-2.3" x2="2.1" y2="-2.3" width="0.127" layer="21"/>
<wire x1="1.8" y1="-2.3" x2="1.5" y2="-2.3" width="0.127" layer="21"/>
<wire x1="1.1" y1="-2.3" x2="0.8" y2="-2.3" width="0.127" layer="21"/>
<wire x1="0.5" y1="-2.3" x2="0.2" y2="-2.3" width="0.127" layer="21"/>
<wire x1="-0.2" y1="-2.3" x2="-0.5" y2="-2.3" width="0.127" layer="21"/>
<wire x1="-0.8" y1="-2.3" x2="-1.1" y2="-2.3" width="0.127" layer="21"/>
<wire x1="-1.5" y1="-2.3" x2="-1.8" y2="-2.3" width="0.127" layer="21"/>
<wire x1="-2.1" y1="-2.3" x2="-2.6" y2="-2.3" width="0.127" layer="21"/>
<wire x1="-2.6" y1="2.2" x2="-2.6" y2="-2.3" width="0.127" layer="21"/>
<wire x1="2.5" y1="2.2" x2="2.5" y2="-2.3" width="0.127" layer="21"/>
<circle x="-2" y="-1.5" radius="0.22360625" width="0.127" layer="21"/>
<text x="-2.9" y="-3.1" size="1.27" layer="21" rot="R90">&gt;NAME</text>
<text x="4" y="-3.3" size="1.27" layer="21" rot="R90">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="PIC24FJ128GA006-">
<pin name="PMD5/RE5" x="0" y="0" direction="pas"/>
<pin name="PMD6/RE6" x="0" y="-2.54" direction="pas"/>
<pin name="PMD7/RE7" x="0" y="-5.08" direction="pas"/>
<pin name="PMA5/SCK2/CN8/RG6" x="0" y="-7.62" direction="pas"/>
<pin name="PMA4/SDI2/CN9/RG7" x="0" y="-10.16" direction="pas"/>
<pin name="PMA3/SDO2/CN10/RG8" x="0" y="-12.7" direction="pas"/>
<pin name="*MCLR" x="0" y="-15.24" direction="pas"/>
<pin name="PMA2/*SS2/CN11/RG9" x="0" y="-17.78" direction="pas"/>
<pin name="VSS_2" x="0" y="-20.32" direction="pas"/>
<pin name="VDD_2" x="0" y="-22.86" direction="pas"/>
<pin name="C1IN+/AN5/CN7/RB5" x="0" y="-25.4" direction="pas"/>
<pin name="C1IN-/AN4/CN6/RB4" x="0" y="-27.94" direction="pas"/>
<pin name="C2IN+/AN3/CN5/RB3" x="0" y="-30.48" direction="pas"/>
<pin name="C2IN-/AN2/*SS1/CN4/RB2" x="0" y="-33.02" direction="pas"/>
<pin name="PGC1/EMUC1/VREF-/AN1/CN3/RB1" x="0" y="-35.56" direction="pas"/>
<pin name="PGD1/EMUD1/PMA6/VREF+/AN0/CN2/RB0" x="0" y="-38.1" direction="pas"/>
<pin name="PGC2/EMUC2/AN6/OCFA/RB6" x="0" y="-40.64" direction="pas"/>
<pin name="PGD2/EMUD2/AN7/RB7" x="0" y="-43.18" direction="pas"/>
<pin name="AVDD" x="0" y="-45.72" direction="pas"/>
<pin name="AVSS" x="0" y="-48.26" direction="pas"/>
<pin name="*U2CTS/C1OUT/AN8/RB8" x="0" y="-50.8" direction="pas"/>
<pin name="PMA7/C2OUT/AN9/RB9" x="0" y="-53.34" direction="pas"/>
<pin name="TMS/PMA13/CVREF/AN10/RB10" x="0" y="-55.88" direction="pas"/>
<pin name="TDO/PMA12/AN11/RB11" x="0" y="-58.42" direction="pas"/>
<pin name="VSS_3" x="0" y="-60.96" direction="pas"/>
<pin name="VDD_3" x="0" y="-63.5" direction="pas"/>
<pin name="TCK/PMA11/AN12/RB12" x="0" y="-66.04" direction="pas"/>
<pin name="TDI/PMA10/AN13/RB13" x="0" y="-68.58" direction="pas"/>
<pin name="PMA1/*U2RTS/BCLK2/AN14/RB14" x="0" y="-71.12" direction="pas"/>
<pin name="PMA0/AN15/OCFB/CN12/RB15" x="0" y="-73.66" direction="pas"/>
<pin name="PMA9/U2RX/SDA2/CN17/RF4" x="0" y="-76.2" direction="pas"/>
<pin name="PMA8/U2TX/SCL2/CN18/RF5" x="0" y="-78.74" direction="pas"/>
<pin name="U1TX/SDO1/RF3" x="154.94" y="-78.74" direction="pas" rot="R180"/>
<pin name="U1RX/SDI1/RF2" x="154.94" y="-76.2" direction="pas" rot="R180"/>
<pin name="*U1RTS/BCLK1/SCK1/INT0/RF6" x="154.94" y="-73.66" direction="pas" rot="R180"/>
<pin name="SDA1/RG3" x="154.94" y="-71.12" direction="pas" rot="R180"/>
<pin name="SCL1/RG2" x="154.94" y="-68.58" direction="pas" rot="R180"/>
<pin name="VDD" x="154.94" y="-66.04" direction="pas" rot="R180"/>
<pin name="OSC1/CLKI/RC12" x="154.94" y="-63.5" direction="pas" rot="R180"/>
<pin name="OSC2/CLKO/RC15" x="154.94" y="-60.96" direction="pas" rot="R180"/>
<pin name="VSS" x="154.94" y="-58.42" direction="pas" rot="R180"/>
<pin name="IC1/RTCC/INT1/RD8" x="154.94" y="-55.88" direction="pas" rot="R180"/>
<pin name="IC2/*U1CTS/INT2/RD9" x="154.94" y="-53.34" direction="pas" rot="R180"/>
<pin name="IC3/PMCS2/INT3/RD10" x="154.94" y="-50.8" direction="pas" rot="R180"/>
<pin name="IC4/PMCS1/INT4/RD11" x="154.94" y="-48.26" direction="pas" rot="R180"/>
<pin name="OC1/RD0" x="154.94" y="-45.72" direction="pas" rot="R180"/>
<pin name="SOSCI/CN1/RC13" x="154.94" y="-43.18" direction="pas" rot="R180"/>
<pin name="SOSCO/T1CK/CN0/RC14" x="154.94" y="-40.64" direction="pas" rot="R180"/>
<pin name="OC2/RD1" x="154.94" y="-38.1" direction="pas" rot="R180"/>
<pin name="OC3/RD2" x="154.94" y="-35.56" direction="pas" rot="R180"/>
<pin name="PMBE/OC4/RD3" x="154.94" y="-33.02" direction="pas" rot="R180"/>
<pin name="PMWR/OC5/IC5/CN13/RD4" x="154.94" y="-30.48" direction="pas" rot="R180"/>
<pin name="PMRD/CN14/RD5" x="154.94" y="-27.94" direction="pas" rot="R180"/>
<pin name="CN15/RD6" x="154.94" y="-25.4" direction="pas" rot="R180"/>
<pin name="CN16/RD7" x="154.94" y="-22.86" direction="pas" rot="R180"/>
<pin name="VCAP/VDDCORE" x="154.94" y="-20.32" direction="pas" rot="R180"/>
<pin name="ENVREG" x="154.94" y="-17.78" direction="pas" rot="R180"/>
<pin name="RF0" x="154.94" y="-15.24" direction="pas" rot="R180"/>
<pin name="RF1" x="154.94" y="-12.7" direction="pas" rot="R180"/>
<pin name="PMD0/RE0" x="154.94" y="-10.16" direction="pas" rot="R180"/>
<pin name="PMD1/RE1" x="154.94" y="-7.62" direction="pas" rot="R180"/>
<pin name="PMD2/RE2" x="154.94" y="-5.08" direction="pas" rot="R180"/>
<pin name="PMD3/RE3" x="154.94" y="-2.54" direction="pas" rot="R180"/>
<pin name="PMD4/RE4" x="154.94" y="0" direction="pas" rot="R180"/>
<wire x1="7.62" y1="5.08" x2="7.62" y2="-83.82" width="0.127" layer="94"/>
<wire x1="7.62" y1="-83.82" x2="147.32" y2="-83.82" width="0.127" layer="94"/>
<wire x1="147.32" y1="-83.82" x2="147.32" y2="5.08" width="0.127" layer="94"/>
<wire x1="147.32" y1="5.08" x2="7.62" y2="5.08" width="0.127" layer="94"/>
<text x="72.1106" y="9.1186" size="2.0828" layer="95" ratio="6" rot="SR0">REFDES</text>
<text x="73.6854" y="6.5786" size="2.0828" layer="96" ratio="6" rot="SR0">TYPE</text>
</symbol>
<symbol name="L298">
<pin name="GND" x="-15.24" y="22.86" length="middle"/>
<pin name="SA" x="-15.24" y="17.78" length="middle"/>
<pin name="NC" x="-15.24" y="12.7" length="middle"/>
<pin name="OUT1" x="-15.24" y="7.62" length="middle"/>
<pin name="OUT2" x="-15.24" y="2.54" length="middle"/>
<pin name="VS" x="-15.24" y="-2.54" length="middle"/>
<pin name="IN1" x="-15.24" y="-7.62" length="middle"/>
<pin name="ENA" x="-15.24" y="-12.7" length="middle"/>
<pin name="IN2" x="-15.24" y="-17.78" length="middle"/>
<pin name="GND1" x="-15.24" y="-22.86" length="middle"/>
<pin name="GND2" x="15.24" y="-22.86" length="middle" rot="R180"/>
<pin name="VSS" x="15.24" y="-17.78" length="middle" rot="R180"/>
<pin name="IN3" x="15.24" y="-12.7" length="middle" rot="R180"/>
<pin name="ENB" x="15.24" y="-7.62" length="middle" rot="R180"/>
<pin name="IN4" x="15.24" y="-2.54" length="middle" rot="R180"/>
<pin name="OUT3" x="15.24" y="2.54" length="middle" rot="R180"/>
<pin name="OUT4" x="15.24" y="7.62" length="middle" rot="R180"/>
<pin name="N.C." x="15.24" y="12.7" length="middle" rot="R180"/>
<pin name="SB" x="15.24" y="17.78" length="middle" rot="R180"/>
<pin name="GND3" x="15.24" y="22.86" length="middle" rot="R180"/>
<wire x1="-10.16" y1="25.4" x2="-10.16" y2="-25.4" width="0.254" layer="94"/>
<wire x1="-10.16" y1="-25.4" x2="10.16" y2="-25.4" width="0.254" layer="94"/>
<wire x1="10.16" y1="-25.4" x2="10.16" y2="25.4" width="0.254" layer="94"/>
<wire x1="10.16" y1="25.4" x2="-10.16" y2="25.4" width="0.254" layer="94"/>
<text x="-2.54" y="30.48" size="1.27" layer="95">&gt;NAME</text>
<text x="-2.54" y="27.94" size="1.27" layer="96">&gt;VALUE</text>
</symbol>
<symbol name="TXS0104E">
<wire x1="10.16" y1="12.7" x2="-10.16" y2="12.7" width="0.254" layer="94"/>
<wire x1="-10.16" y1="12.7" x2="-10.16" y2="-7.62" width="0.254" layer="94"/>
<wire x1="-10.16" y1="-7.62" x2="10.16" y2="-7.62" width="0.254" layer="94"/>
<wire x1="10.16" y1="-7.62" x2="10.16" y2="12.7" width="0.254" layer="94"/>
<pin name="VCCA" x="-15.24" y="10.16" length="middle"/>
<pin name="A1" x="-15.24" y="7.62" length="middle"/>
<pin name="A2" x="-15.24" y="5.08" length="middle"/>
<pin name="A3" x="-15.24" y="2.54" length="middle"/>
<pin name="A4" x="-15.24" y="0" length="middle"/>
<pin name="GND" x="-15.24" y="-5.08" length="middle"/>
<pin name="VCCB" x="15.24" y="10.16" length="middle" rot="R180"/>
<pin name="B1" x="15.24" y="7.62" length="middle" rot="R180"/>
<pin name="B2" x="15.24" y="5.08" length="middle" rot="R180"/>
<pin name="B3" x="15.24" y="2.54" length="middle" rot="R180"/>
<pin name="B4" x="15.24" y="0" length="middle" rot="R180"/>
<pin name="OE" x="15.24" y="-5.08" length="middle" rot="R180"/>
<text x="-7.62" y="12.7" size="1.27" layer="95">&gt;NAME</text>
<text x="-7.62" y="-10.16" size="1.27" layer="96">&gt;VALUE</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="PIC24FJ128GA006-">
<gates>
<gate name="A" symbol="PIC24FJ128GA006-" x="0" y="0"/>
</gates>
<devices>
<device name="" package="TQFP64_10X10MC">
<connects>
<connect gate="A" pin="*MCLR" pad="7"/>
<connect gate="A" pin="*U1RTS/BCLK1/SCK1/INT0/RF6" pad="35"/>
<connect gate="A" pin="*U2CTS/C1OUT/AN8/RB8" pad="21"/>
<connect gate="A" pin="AVDD" pad="19"/>
<connect gate="A" pin="AVSS" pad="20"/>
<connect gate="A" pin="C1IN+/AN5/CN7/RB5" pad="11"/>
<connect gate="A" pin="C1IN-/AN4/CN6/RB4" pad="12"/>
<connect gate="A" pin="C2IN+/AN3/CN5/RB3" pad="13"/>
<connect gate="A" pin="C2IN-/AN2/*SS1/CN4/RB2" pad="14"/>
<connect gate="A" pin="CN15/RD6" pad="54"/>
<connect gate="A" pin="CN16/RD7" pad="55"/>
<connect gate="A" pin="ENVREG" pad="57"/>
<connect gate="A" pin="IC1/RTCC/INT1/RD8" pad="42"/>
<connect gate="A" pin="IC2/*U1CTS/INT2/RD9" pad="43"/>
<connect gate="A" pin="IC3/PMCS2/INT3/RD10" pad="44"/>
<connect gate="A" pin="IC4/PMCS1/INT4/RD11" pad="45"/>
<connect gate="A" pin="OC1/RD0" pad="46"/>
<connect gate="A" pin="OC2/RD1" pad="49"/>
<connect gate="A" pin="OC3/RD2" pad="50"/>
<connect gate="A" pin="OSC1/CLKI/RC12" pad="39"/>
<connect gate="A" pin="OSC2/CLKO/RC15" pad="40"/>
<connect gate="A" pin="PGC1/EMUC1/VREF-/AN1/CN3/RB1" pad="15"/>
<connect gate="A" pin="PGC2/EMUC2/AN6/OCFA/RB6" pad="17"/>
<connect gate="A" pin="PGD1/EMUD1/PMA6/VREF+/AN0/CN2/RB0" pad="16"/>
<connect gate="A" pin="PGD2/EMUD2/AN7/RB7" pad="18"/>
<connect gate="A" pin="PMA0/AN15/OCFB/CN12/RB15" pad="30"/>
<connect gate="A" pin="PMA1/*U2RTS/BCLK2/AN14/RB14" pad="29"/>
<connect gate="A" pin="PMA2/*SS2/CN11/RG9" pad="8"/>
<connect gate="A" pin="PMA3/SDO2/CN10/RG8" pad="6"/>
<connect gate="A" pin="PMA4/SDI2/CN9/RG7" pad="5"/>
<connect gate="A" pin="PMA5/SCK2/CN8/RG6" pad="4"/>
<connect gate="A" pin="PMA7/C2OUT/AN9/RB9" pad="22"/>
<connect gate="A" pin="PMA8/U2TX/SCL2/CN18/RF5" pad="32"/>
<connect gate="A" pin="PMA9/U2RX/SDA2/CN17/RF4" pad="31"/>
<connect gate="A" pin="PMBE/OC4/RD3" pad="51"/>
<connect gate="A" pin="PMD0/RE0" pad="60"/>
<connect gate="A" pin="PMD1/RE1" pad="61"/>
<connect gate="A" pin="PMD2/RE2" pad="62"/>
<connect gate="A" pin="PMD3/RE3" pad="63"/>
<connect gate="A" pin="PMD4/RE4" pad="64"/>
<connect gate="A" pin="PMD5/RE5" pad="1"/>
<connect gate="A" pin="PMD6/RE6" pad="2"/>
<connect gate="A" pin="PMD7/RE7" pad="3"/>
<connect gate="A" pin="PMRD/CN14/RD5" pad="53"/>
<connect gate="A" pin="PMWR/OC5/IC5/CN13/RD4" pad="52"/>
<connect gate="A" pin="RF0" pad="58"/>
<connect gate="A" pin="RF1" pad="59"/>
<connect gate="A" pin="SCL1/RG2" pad="37"/>
<connect gate="A" pin="SDA1/RG3" pad="36"/>
<connect gate="A" pin="SOSCI/CN1/RC13" pad="47"/>
<connect gate="A" pin="SOSCO/T1CK/CN0/RC14" pad="48"/>
<connect gate="A" pin="TCK/PMA11/AN12/RB12" pad="27"/>
<connect gate="A" pin="TDI/PMA10/AN13/RB13" pad="28"/>
<connect gate="A" pin="TDO/PMA12/AN11/RB11" pad="24"/>
<connect gate="A" pin="TMS/PMA13/CVREF/AN10/RB10" pad="23"/>
<connect gate="A" pin="U1RX/SDI1/RF2" pad="34"/>
<connect gate="A" pin="U1TX/SDO1/RF3" pad="33"/>
<connect gate="A" pin="VCAP/VDDCORE" pad="56"/>
<connect gate="A" pin="VDD" pad="38"/>
<connect gate="A" pin="VDD_2" pad="10"/>
<connect gate="A" pin="VDD_3" pad="26"/>
<connect gate="A" pin="VSS" pad="41"/>
<connect gate="A" pin="VSS_2" pad="9"/>
<connect gate="A" pin="VSS_3" pad="25"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="L298">
<description>H bridge motor driver</description>
<gates>
<gate name="G$1" symbol="L298" x="-5.08" y="2.54"/>
</gates>
<devices>
<device name="" package="L298">
<connects>
<connect gate="G$1" pin="ENA" pad="ENA"/>
<connect gate="G$1" pin="ENB" pad="ENB"/>
<connect gate="G$1" pin="GND" pad="GND"/>
<connect gate="G$1" pin="GND1" pad="GND1"/>
<connect gate="G$1" pin="GND2" pad="GND2"/>
<connect gate="G$1" pin="GND3" pad="GND3"/>
<connect gate="G$1" pin="IN1" pad="IN1"/>
<connect gate="G$1" pin="IN2" pad="IN2"/>
<connect gate="G$1" pin="IN3" pad="IN3"/>
<connect gate="G$1" pin="IN4" pad="IN4"/>
<connect gate="G$1" pin="N.C." pad="N.C."/>
<connect gate="G$1" pin="NC" pad="NC"/>
<connect gate="G$1" pin="OUT1" pad="OUT1"/>
<connect gate="G$1" pin="OUT2" pad="OUT2"/>
<connect gate="G$1" pin="OUT3" pad="OUT3"/>
<connect gate="G$1" pin="OUT4" pad="OUT4"/>
<connect gate="G$1" pin="SA" pad="SA"/>
<connect gate="G$1" pin="SB" pad="SB"/>
<connect gate="G$1" pin="VS" pad="VS"/>
<connect gate="G$1" pin="VSS" pad="VSS"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="TXS0104E">
<gates>
<gate name="G$1" symbol="TXS0104E" x="0" y="-2.54"/>
</gates>
<devices>
<device name="" package="SSOP-14">
<connects>
<connect gate="G$1" pin="A1" pad="2"/>
<connect gate="G$1" pin="A2" pad="3"/>
<connect gate="G$1" pin="A3" pad="4"/>
<connect gate="G$1" pin="A4" pad="5"/>
<connect gate="G$1" pin="B1" pad="13"/>
<connect gate="G$1" pin="B2" pad="12"/>
<connect gate="G$1" pin="B3" pad="11"/>
<connect gate="G$1" pin="B4" pad="10"/>
<connect gate="G$1" pin="GND" pad="7"/>
<connect gate="G$1" pin="OE" pad="8"/>
<connect gate="G$1" pin="VCCA" pad="1"/>
<connect gate="G$1" pin="VCCB" pad="14"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="con-molex">
<description>&lt;b&gt;Molex Connectors&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="22-23-2031">
<description>.100" (2.54mm) Center Header - 3 Pin</description>
<wire x1="-3.81" y1="3.175" x2="3.81" y2="3.175" width="0.254" layer="21"/>
<wire x1="3.81" y1="3.175" x2="3.81" y2="1.27" width="0.254" layer="21"/>
<wire x1="3.81" y1="1.27" x2="3.81" y2="-3.175" width="0.254" layer="21"/>
<wire x1="3.81" y1="-3.175" x2="-3.81" y2="-3.175" width="0.254" layer="21"/>
<wire x1="-3.81" y1="-3.175" x2="-3.81" y2="1.27" width="0.254" layer="21"/>
<wire x1="-3.81" y1="1.27" x2="-3.81" y2="3.175" width="0.254" layer="21"/>
<wire x1="-3.81" y1="1.27" x2="3.81" y2="1.27" width="0.254" layer="21"/>
<pad name="1" x="-2.54" y="0" drill="1" shape="long" rot="R90"/>
<pad name="2" x="0" y="0" drill="1" shape="long" rot="R90"/>
<pad name="3" x="2.54" y="0" drill="1" shape="long" rot="R90"/>
<text x="-3.81" y="3.81" size="1.016" layer="25" ratio="10">&gt;NAME</text>
<text x="-3.81" y="-5.08" size="1.016" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="22-23-2041">
<description>.100" (2.54mm) Center Header - 4 Pin</description>
<wire x1="-5.08" y1="3.175" x2="5.08" y2="3.175" width="0.254" layer="21"/>
<wire x1="5.08" y1="3.175" x2="5.08" y2="1.27" width="0.254" layer="21"/>
<wire x1="5.08" y1="1.27" x2="5.08" y2="-3.175" width="0.254" layer="21"/>
<wire x1="5.08" y1="-3.175" x2="-5.08" y2="-3.175" width="0.254" layer="21"/>
<wire x1="-5.08" y1="-3.175" x2="-5.08" y2="1.27" width="0.254" layer="21"/>
<wire x1="-5.08" y1="1.27" x2="-5.08" y2="3.175" width="0.254" layer="21"/>
<wire x1="-5.08" y1="1.27" x2="5.08" y2="1.27" width="0.254" layer="21"/>
<pad name="1" x="-3.81" y="0" drill="1" shape="long" rot="R90"/>
<pad name="2" x="-1.27" y="0" drill="1" shape="long" rot="R90"/>
<pad name="3" x="1.27" y="0" drill="1" shape="long" rot="R90"/>
<pad name="4" x="3.81" y="0" drill="1" shape="long" rot="R90"/>
<text x="-5.08" y="3.81" size="1.016" layer="25" ratio="10">&gt;NAME</text>
<text x="-5.08" y="-5.08" size="1.016" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="22-23-2021">
<description>.100" (2.54mm) Center Headers - 2 Pin</description>
<wire x1="-2.54" y1="3.175" x2="2.54" y2="3.175" width="0.254" layer="21"/>
<wire x1="2.54" y1="3.175" x2="2.54" y2="1.27" width="0.254" layer="21"/>
<wire x1="2.54" y1="1.27" x2="2.54" y2="-3.175" width="0.254" layer="21"/>
<wire x1="2.54" y1="-3.175" x2="-2.54" y2="-3.175" width="0.254" layer="21"/>
<wire x1="-2.54" y1="-3.175" x2="-2.54" y2="1.27" width="0.254" layer="21"/>
<wire x1="-2.54" y1="1.27" x2="-2.54" y2="3.175" width="0.254" layer="21"/>
<wire x1="-2.54" y1="1.27" x2="2.54" y2="1.27" width="0.254" layer="21"/>
<pad name="1" x="-1.27" y="0" drill="1" shape="long" rot="R90"/>
<pad name="2" x="1.27" y="0" drill="1" shape="long" rot="R90"/>
<text x="-2.54" y="3.81" size="1.016" layer="25" ratio="10">&gt;NAME</text>
<text x="-2.54" y="-5.08" size="1.016" layer="27" ratio="10">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="MV">
<wire x1="1.27" y1="0" x2="0" y2="0" width="0.6096" layer="94"/>
<text x="2.54" y="-0.762" size="1.524" layer="95">&gt;NAME</text>
<text x="-0.762" y="1.397" size="1.778" layer="96">&gt;VALUE</text>
<pin name="S" x="-2.54" y="0" visible="off" length="short" direction="pas"/>
</symbol>
<symbol name="M">
<wire x1="1.27" y1="0" x2="0" y2="0" width="0.6096" layer="94"/>
<text x="2.54" y="-0.762" size="1.524" layer="95">&gt;NAME</text>
<pin name="S" x="-2.54" y="0" visible="off" length="short" direction="pas"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="22-23-2031" prefix="X">
<description>.100" (2.54mm) Center Header - 3 Pin</description>
<gates>
<gate name="-1" symbol="MV" x="0" y="2.54" addlevel="always" swaplevel="1"/>
<gate name="-2" symbol="M" x="0" y="0" addlevel="always" swaplevel="1"/>
<gate name="-3" symbol="M" x="0" y="-2.54" addlevel="always" swaplevel="1"/>
</gates>
<devices>
<device name="" package="22-23-2031">
<connects>
<connect gate="-1" pin="S" pad="1"/>
<connect gate="-2" pin="S" pad="2"/>
<connect gate="-3" pin="S" pad="3"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="MOLEX" constant="no"/>
<attribute name="MPN" value="22-23-2031" constant="no"/>
<attribute name="OC_FARNELL" value="1462950" constant="no"/>
<attribute name="OC_NEWARK" value="30C0862" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="22-23-2041" prefix="X">
<description>.100" (2.54mm) Center Header - 4 Pin</description>
<gates>
<gate name="-1" symbol="MV" x="0" y="2.54" addlevel="always" swaplevel="1"/>
<gate name="-2" symbol="M" x="0" y="0" addlevel="always" swaplevel="1"/>
<gate name="-3" symbol="M" x="0" y="-2.54" addlevel="always" swaplevel="1"/>
<gate name="-4" symbol="M" x="0" y="-5.08" addlevel="always" swaplevel="1"/>
</gates>
<devices>
<device name="" package="22-23-2041">
<connects>
<connect gate="-1" pin="S" pad="1"/>
<connect gate="-2" pin="S" pad="2"/>
<connect gate="-3" pin="S" pad="3"/>
<connect gate="-4" pin="S" pad="4"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="MOLEX" constant="no"/>
<attribute name="MPN" value="22-23-2041" constant="no"/>
<attribute name="OC_FARNELL" value="1462920" constant="no"/>
<attribute name="OC_NEWARK" value="38C0355" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="22-23-2021" prefix="X">
<description>.100" (2.54mm) Center Header - 2 Pin</description>
<gates>
<gate name="-1" symbol="MV" x="0" y="0" addlevel="always" swaplevel="1"/>
<gate name="-2" symbol="M" x="0" y="-2.54" addlevel="always" swaplevel="1"/>
</gates>
<devices>
<device name="" package="22-23-2021">
<connects>
<connect gate="-1" pin="S" pad="1"/>
<connect gate="-2" pin="S" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="MOLEX" constant="no"/>
<attribute name="MPN" value="22-23-2021" constant="no"/>
<attribute name="OC_FARNELL" value="1462926" constant="no"/>
<attribute name="OC_NEWARK" value="25C3832" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="U$1" library="MinotaurParts" deviceset="PIC24FJ128GA006-" device=""/>
<part name="SENSOR1" library="con-molex" deviceset="22-23-2031" device=""/>
<part name="SENSOR2" library="con-molex" deviceset="22-23-2031" device=""/>
<part name="SENSOR3" library="con-molex" deviceset="22-23-2031" device=""/>
<part name="SENSOR4" library="con-molex" deviceset="22-23-2031" device=""/>
<part name="SENSOR5" library="con-molex" deviceset="22-23-2031" device=""/>
<part name="RS232" library="con-molex" deviceset="22-23-2041" device=""/>
<part name="U$2" library="MinotaurParts" deviceset="L298" device=""/>
<part name="U$3" library="MinotaurParts" deviceset="TXS0104E" device=""/>
<part name="ENCODER" library="con-molex" deviceset="22-23-2021" device=""/>
<part name="FUELGUAGE" library="con-molex" deviceset="22-23-2021" device=""/>
<part name="X9" library="con-molex" deviceset="22-23-2041" device=""/>
<part name="X10" library="con-molex" deviceset="22-23-2041" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="U$1" gate="A" x="-78.74" y="48.26"/>
<instance part="SENSOR1" gate="-1" x="-73.66" y="-96.52"/>
<instance part="SENSOR1" gate="-2" x="-73.66" y="-99.06"/>
<instance part="SENSOR1" gate="-3" x="-73.66" y="-101.6"/>
<instance part="SENSOR2" gate="-1" x="-53.34" y="-96.52"/>
<instance part="SENSOR2" gate="-2" x="-53.34" y="-99.06"/>
<instance part="SENSOR2" gate="-3" x="-53.34" y="-101.6"/>
<instance part="SENSOR3" gate="-1" x="-33.02" y="-96.52"/>
<instance part="SENSOR3" gate="-2" x="-33.02" y="-99.06"/>
<instance part="SENSOR3" gate="-3" x="-33.02" y="-101.6"/>
<instance part="SENSOR4" gate="-1" x="-12.7" y="-96.52"/>
<instance part="SENSOR4" gate="-2" x="-12.7" y="-99.06"/>
<instance part="SENSOR4" gate="-3" x="-12.7" y="-101.6"/>
<instance part="SENSOR5" gate="-1" x="7.62" y="-96.52"/>
<instance part="SENSOR5" gate="-2" x="7.62" y="-99.06"/>
<instance part="SENSOR5" gate="-3" x="7.62" y="-101.6"/>
<instance part="RS232" gate="-1" x="73.66" y="-91.44"/>
<instance part="RS232" gate="-2" x="73.66" y="-93.98"/>
<instance part="RS232" gate="-3" x="73.66" y="-96.52"/>
<instance part="RS232" gate="-4" x="73.66" y="-99.06"/>
<instance part="U$2" gate="G$1" x="157.48" y="15.24"/>
<instance part="U$3" gate="G$1" x="157.48" y="-66.04"/>
<instance part="ENCODER" gate="-1" x="205.74" y="-58.42"/>
<instance part="ENCODER" gate="-2" x="205.74" y="-60.96"/>
<instance part="FUELGUAGE" gate="-1" x="205.74" y="-40.64"/>
<instance part="FUELGUAGE" gate="-2" x="205.74" y="-43.18"/>
<instance part="X9" gate="-1" x="215.9" y="78.74"/>
<instance part="X9" gate="-2" x="215.9" y="76.2"/>
<instance part="X9" gate="-3" x="215.9" y="73.66"/>
<instance part="X9" gate="-4" x="215.9" y="71.12"/>
<instance part="X10" gate="-1" x="215.9" y="101.6"/>
<instance part="X10" gate="-2" x="215.9" y="99.06"/>
<instance part="X10" gate="-3" x="215.9" y="96.52"/>
<instance part="X10" gate="-4" x="215.9" y="93.98"/>
</instances>
<busses>
</busses>
<nets>
<net name="N$1" class="0">
<segment>
<pinref part="U$1" gate="A" pin="C1IN+/AN5/CN7/RB5"/>
<wire x1="-78.74" y1="22.86" x2="-106.68" y2="22.86" width="0.2032" layer="91"/>
<wire x1="-106.68" y1="22.86" x2="-106.68" y2="-96.52" width="0.2032" layer="91"/>
<pinref part="SENSOR1" gate="-1" pin="S"/>
<wire x1="-106.68" y1="-96.52" x2="-76.2" y2="-96.52" width="0.2032" layer="91"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<pinref part="SENSOR2" gate="-1" pin="S"/>
<wire x1="-55.88" y1="-96.52" x2="-55.88" y2="-88.9" width="0.2032" layer="91"/>
<wire x1="-55.88" y1="-88.9" x2="-104.14" y2="-88.9" width="0.2032" layer="91"/>
<wire x1="-104.14" y1="-88.9" x2="-104.14" y2="20.32" width="0.2032" layer="91"/>
<pinref part="U$1" gate="A" pin="C1IN-/AN4/CN6/RB4"/>
<wire x1="-104.14" y1="20.32" x2="-78.74" y2="20.32" width="0.2032" layer="91"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<pinref part="U$1" gate="A" pin="C2IN+/AN3/CN5/RB3"/>
<wire x1="-78.74" y1="17.78" x2="-101.6" y2="17.78" width="0.2032" layer="91"/>
<wire x1="-101.6" y1="17.78" x2="-101.6" y2="-83.82" width="0.2032" layer="91"/>
<wire x1="-101.6" y1="-83.82" x2="-38.1" y2="-83.82" width="0.2032" layer="91"/>
<wire x1="-38.1" y1="-83.82" x2="-38.1" y2="-96.52" width="0.2032" layer="91"/>
<pinref part="SENSOR3" gate="-1" pin="S"/>
<wire x1="-38.1" y1="-96.52" x2="-35.56" y2="-96.52" width="0.2032" layer="91"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<pinref part="SENSOR4" gate="-1" pin="S"/>
<wire x1="-15.24" y1="-96.52" x2="-15.24" y2="-78.74" width="0.2032" layer="91"/>
<wire x1="-15.24" y1="-78.74" x2="-99.06" y2="-78.74" width="0.2032" layer="91"/>
<wire x1="-99.06" y1="-78.74" x2="-99.06" y2="15.24" width="0.2032" layer="91"/>
<pinref part="U$1" gate="A" pin="C2IN-/AN2/*SS1/CN4/RB2"/>
<wire x1="-99.06" y1="15.24" x2="-78.74" y2="15.24" width="0.2032" layer="91"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<wire x1="-76.2" y1="-2.54" x2="-96.52" y2="-2.54" width="0.2032" layer="91"/>
<wire x1="-96.52" y1="-2.54" x2="-96.52" y2="-76.2" width="0.2032" layer="91"/>
<wire x1="-96.52" y1="-76.2" x2="2.54" y2="-76.2" width="0.2032" layer="91"/>
<wire x1="2.54" y1="-76.2" x2="2.54" y2="-96.52" width="0.2032" layer="91"/>
<pinref part="SENSOR5" gate="-1" pin="S"/>
<wire x1="2.54" y1="-96.52" x2="5.08" y2="-96.52" width="0.2032" layer="91"/>
</segment>
</net>
<net name="N$6" class="0">
<segment>
<pinref part="RS232" gate="-1" pin="S"/>
<wire x1="71.12" y1="-91.44" x2="68.58" y2="-91.44" width="0.2032" layer="91"/>
<wire x1="68.58" y1="-91.44" x2="68.58" y2="-45.72" width="0.2032" layer="91"/>
<wire x1="68.58" y1="-45.72" x2="88.9" y2="-45.72" width="0.2032" layer="91"/>
<wire x1="88.9" y1="-45.72" x2="88.9" y2="-5.08" width="0.2032" layer="91"/>
<wire x1="88.9" y1="-5.08" x2="73.66" y2="-5.08" width="0.2032" layer="91"/>
</segment>
</net>
<net name="N$7" class="0">
<segment>
<pinref part="RS232" gate="-2" pin="S"/>
<wire x1="71.12" y1="-93.98" x2="66.04" y2="-93.98" width="0.2032" layer="91"/>
<wire x1="66.04" y1="-93.98" x2="66.04" y2="-43.18" width="0.2032" layer="91"/>
<wire x1="66.04" y1="-43.18" x2="86.36" y2="-43.18" width="0.2032" layer="91"/>
<wire x1="86.36" y1="-43.18" x2="86.36" y2="-25.4" width="0.2032" layer="91"/>
<pinref part="U$1" gate="A" pin="*U1RTS/BCLK1/SCK1/INT0/RF6"/>
<wire x1="86.36" y1="-25.4" x2="76.2" y2="-25.4" width="0.2032" layer="91"/>
</segment>
</net>
<net name="N$8" class="0">
<segment>
<pinref part="U$1" gate="A" pin="U1RX/SDI1/RF2"/>
<wire x1="76.2" y1="-27.94" x2="83.82" y2="-27.94" width="0.2032" layer="91"/>
<wire x1="83.82" y1="-27.94" x2="83.82" y2="-40.64" width="0.2032" layer="91"/>
<wire x1="83.82" y1="-40.64" x2="63.5" y2="-40.64" width="0.2032" layer="91"/>
<wire x1="63.5" y1="-40.64" x2="63.5" y2="-96.52" width="0.2032" layer="91"/>
<pinref part="RS232" gate="-3" pin="S"/>
<wire x1="63.5" y1="-96.52" x2="71.12" y2="-96.52" width="0.2032" layer="91"/>
</segment>
</net>
<net name="N$9" class="0">
<segment>
<pinref part="RS232" gate="-4" pin="S"/>
<wire x1="71.12" y1="-99.06" x2="60.96" y2="-99.06" width="0.2032" layer="91"/>
<wire x1="60.96" y1="-99.06" x2="60.96" y2="-38.1" width="0.2032" layer="91"/>
<wire x1="60.96" y1="-38.1" x2="81.28" y2="-38.1" width="0.2032" layer="91"/>
<wire x1="81.28" y1="-38.1" x2="81.28" y2="-30.48" width="0.2032" layer="91"/>
<wire x1="81.28" y1="-30.48" x2="73.66" y2="-30.48" width="0.2032" layer="91"/>
</segment>
</net>
<net name="N$10" class="0">
<segment>
<wire x1="73.66" y1="10.16" x2="124.46" y2="10.16" width="0.2032" layer="91"/>
<wire x1="124.46" y1="10.16" x2="124.46" y2="2.54" width="0.2032" layer="91"/>
<wire x1="124.46" y1="2.54" x2="144.78" y2="2.54" width="0.2032" layer="91"/>
</segment>
</net>
<net name="N$11" class="0">
<segment>
<wire x1="73.66" y1="12.7" x2="129.54" y2="12.7" width="0.2032" layer="91"/>
<wire x1="129.54" y1="12.7" x2="129.54" y2="50.8" width="0.2032" layer="91"/>
<wire x1="129.54" y1="50.8" x2="182.88" y2="50.8" width="0.2032" layer="91"/>
<wire x1="182.88" y1="50.8" x2="182.88" y2="7.62" width="0.2032" layer="91"/>
<wire x1="182.88" y1="7.62" x2="170.18" y2="7.62" width="0.2032" layer="91"/>
</segment>
</net>
<net name="N$12" class="0">
<segment>
<pinref part="U$1" gate="A" pin="SCL1/RG2"/>
<wire x1="76.2" y1="-20.32" x2="132.08" y2="-20.32" width="0.2032" layer="91"/>
<wire x1="132.08" y1="-20.32" x2="132.08" y2="-58.42" width="0.2032" layer="91"/>
<wire x1="132.08" y1="-58.42" x2="144.78" y2="-58.42" width="0.2032" layer="91"/>
</segment>
</net>
<net name="N$13" class="0">
<segment>
<wire x1="73.66" y1="-22.86" x2="129.54" y2="-22.86" width="0.2032" layer="91"/>
<wire x1="129.54" y1="-22.86" x2="129.54" y2="-60.96" width="0.2032" layer="91"/>
<wire x1="129.54" y1="-60.96" x2="144.78" y2="-60.96" width="0.2032" layer="91"/>
</segment>
</net>
<net name="N$14" class="0">
<segment>
<wire x1="144.78" y1="7.62" x2="127" y2="7.62" width="0.2032" layer="91"/>
<wire x1="127" y1="7.62" x2="127" y2="35.56" width="0.2032" layer="91"/>
<wire x1="127" y1="35.56" x2="86.36" y2="35.56" width="0.2032" layer="91"/>
<wire x1="86.36" y1="35.56" x2="86.36" y2="38.1" width="0.2032" layer="91"/>
<pinref part="U$1" gate="A" pin="PMD0/RE0"/>
<wire x1="86.36" y1="38.1" x2="76.2" y2="38.1" width="0.2032" layer="91"/>
</segment>
</net>
<net name="N$15" class="0">
<segment>
<pinref part="U$1" gate="A" pin="PMD1/RE1"/>
<wire x1="76.2" y1="40.64" x2="134.62" y2="40.64" width="0.2032" layer="91"/>
<wire x1="134.62" y1="40.64" x2="134.62" y2="-2.54" width="0.2032" layer="91"/>
<wire x1="134.62" y1="-2.54" x2="144.78" y2="-2.54" width="0.2032" layer="91"/>
</segment>
</net>
<net name="N$16" class="0">
<segment>
<wire x1="170.18" y1="2.54" x2="180.34" y2="2.54" width="0.2032" layer="91"/>
<wire x1="180.34" y1="2.54" x2="180.34" y2="53.34" width="0.2032" layer="91"/>
<wire x1="180.34" y1="53.34" x2="88.9" y2="53.34" width="0.2032" layer="91"/>
<wire x1="88.9" y1="53.34" x2="88.9" y2="43.18" width="0.2032" layer="91"/>
<wire x1="88.9" y1="43.18" x2="73.66" y2="43.18" width="0.2032" layer="91"/>
</segment>
</net>
<net name="N$17" class="0">
<segment>
<wire x1="73.66" y1="45.72" x2="86.36" y2="45.72" width="0.2032" layer="91"/>
<wire x1="86.36" y1="45.72" x2="86.36" y2="55.88" width="0.2032" layer="91"/>
<wire x1="86.36" y1="55.88" x2="177.8" y2="55.88" width="0.2032" layer="91"/>
<wire x1="177.8" y1="55.88" x2="177.8" y2="12.7" width="0.2032" layer="91"/>
<pinref part="U$2" gate="G$1" pin="IN4"/>
<wire x1="177.8" y1="12.7" x2="172.72" y2="12.7" width="0.2032" layer="91"/>
</segment>
</net>
<net name="N$18" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="OUT1"/>
<wire x1="142.24" y1="22.86" x2="139.7" y2="22.86" width="0.2032" layer="91"/>
<wire x1="139.7" y1="22.86" x2="139.7" y2="99.06" width="0.2032" layer="91"/>
<wire x1="139.7" y1="99.06" x2="213.36" y2="99.06" width="0.2032" layer="91"/>
<pinref part="X10" gate="-2" pin="S"/>
</segment>
</net>
<net name="N$19" class="0">
<segment>
<wire x1="144.78" y1="17.78" x2="137.16" y2="17.78" width="0.2032" layer="91"/>
<wire x1="137.16" y1="17.78" x2="137.16" y2="101.6" width="0.2032" layer="91"/>
<wire x1="137.16" y1="101.6" x2="213.36" y2="101.6" width="0.2032" layer="91"/>
<pinref part="X10" gate="-1" pin="S"/>
</segment>
</net>
<net name="N$20" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="OUT4"/>
<wire x1="172.72" y1="22.86" x2="190.5" y2="22.86" width="0.2032" layer="91"/>
<wire x1="190.5" y1="22.86" x2="190.5" y2="78.74" width="0.2032" layer="91"/>
<wire x1="190.5" y1="78.74" x2="198.12" y2="78.74" width="0.2032" layer="91"/>
<pinref part="X9" gate="-1" pin="S"/>
<wire x1="198.12" y1="78.74" x2="200.66" y2="78.74" width="0.2032" layer="91"/>
<wire x1="200.66" y1="78.74" x2="213.36" y2="78.74" width="0.2032" layer="91"/>
</segment>
</net>
<net name="N$21" class="0">
<segment>
<wire x1="170.18" y1="17.78" x2="195.58" y2="17.78" width="0.2032" layer="91"/>
<wire x1="195.58" y1="17.78" x2="195.58" y2="76.2" width="0.2032" layer="91"/>
<wire x1="195.58" y1="76.2" x2="198.12" y2="76.2" width="0.2032" layer="91"/>
<pinref part="X9" gate="-2" pin="S"/>
<wire x1="198.12" y1="76.2" x2="200.66" y2="76.2" width="0.2032" layer="91"/>
<wire x1="213.36" y1="76.2" x2="200.66" y2="76.2" width="0.2032" layer="91"/>
</segment>
</net>
<net name="N$22" class="0">
<segment>
<wire x1="-76.2" y1="-25.4" x2="-91.44" y2="-25.4" width="0.2032" layer="91"/>
<wire x1="-91.44" y1="-25.4" x2="-91.44" y2="-55.88" width="0.2032" layer="91"/>
<wire x1="-91.44" y1="-55.88" x2="114.3" y2="-55.88" width="0.2032" layer="91"/>
<wire x1="114.3" y1="-55.88" x2="114.3" y2="-83.82" width="0.2032" layer="91"/>
<wire x1="114.3" y1="-83.82" x2="175.26" y2="-83.82" width="0.2032" layer="91"/>
<wire x1="175.26" y1="-83.82" x2="175.26" y2="-71.12" width="0.2032" layer="91"/>
<pinref part="U$3" gate="G$1" pin="OE"/>
<wire x1="175.26" y1="-71.12" x2="172.72" y2="-71.12" width="0.2032" layer="91"/>
</segment>
</net>
<net name="N$23" class="0">
<segment>
<wire x1="170.18" y1="-58.42" x2="198.12" y2="-58.42" width="0.2032" layer="91"/>
<pinref part="ENCODER" gate="-1" pin="S"/>
<wire x1="198.12" y1="-58.42" x2="203.2" y2="-58.42" width="0.2032" layer="91"/>
<wire x1="198.12" y1="-58.42" x2="198.12" y2="-40.64" width="0.2032" layer="91"/>
<pinref part="FUELGUAGE" gate="-1" pin="S"/>
<wire x1="198.12" y1="-40.64" x2="203.2" y2="-40.64" width="0.2032" layer="91"/>
<junction x="198.12" y="-58.42"/>
</segment>
</net>
<net name="N$24" class="0">
<segment>
<wire x1="170.18" y1="-60.96" x2="200.66" y2="-60.96" width="0.2032" layer="91"/>
<pinref part="ENCODER" gate="-2" pin="S"/>
<wire x1="200.66" y1="-60.96" x2="203.2" y2="-60.96" width="0.2032" layer="91"/>
<wire x1="200.66" y1="-60.96" x2="200.66" y2="-43.18" width="0.2032" layer="91"/>
<pinref part="FUELGUAGE" gate="-2" pin="S"/>
<wire x1="200.66" y1="-43.18" x2="203.2" y2="-43.18" width="0.2032" layer="91"/>
<junction x="200.66" y="-60.96"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
