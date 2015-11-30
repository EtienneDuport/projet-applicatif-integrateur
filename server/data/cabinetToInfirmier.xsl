<?xml version="1.0" encoding="UTF-8"?>

<!--
    Document   : infirmiere.xsl
    Created on : 14 octobre 2015, 09:55
    Author     : adjibodr
    Description:
        Purpose of transformation follows.
-->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
    xmlns:cab="http://www.ujf-grenoble.fr/l3miage/medical"
    xmlns:act="http://www.ujf-grenoble.fr/l3miage/actes">
    
    <xsl:output method="html"/>

    <!-- TODO customize transformation rules 
         syntax recommendation http://www.w3.org/TR/xslt 
    -->
    <xsl:param name="id" select="001"/>
    <xsl:variable name="actes" select="document('actes.xml', /)/act:ngap"/>
    <xsl:variable name="laDate">2015-10-14</xsl:variable>
    <xsl:variable name="nbPatients" select="count(//cab:visite[@intervenant=$id and @date=$laDate])"/>
    <xsl:template match="/">
        <html>
            <head>
                <title>Programme du jour</title>
                <link rel="stylesheet" href="../public_html/infirmiere.css"/>
                <script type="text/javascript"><![CDATA[
                   
                    function openFacture(prenom, nom, actes) {
                        var width  = 500;
                        var height = 300;
                        if(window.innerWidth) {
                            var left = (window.innerWidth-width)/2;
                            var top = (window.innerHeight-height)/2;
                        }
                        else {
                            var left = (document.body.clientWidth-width)/2;
                            var top = (document.body.clientHeight-height)/2;
                        }
                        var factureWindow = window.open('','facture','menubar=yes, scrollbars=yes, top='+top+', left='+left+', width='+width+', height='+height+'');
                        factureText = "Facture pour : " + prenom + " " + nom + " \n" + actes;
                        factureWindow.document.write(factureText);
                     }
                    function init(){
                        var today = new Date();
                        var options = {weekday: "long", year: "numeric", month: "long", day: "numeric"};
                        document.getElementById('time').innerHTML=today.toLocaleString("fr-FR", options);
                    }
               ]]>
                </script>
                
            </head>
            <body onload="init()">
                <h1>Cabinet Médical Tartampion</h1><img id="illustration" src="http://a142.idata.over-blog.com/2/25/98/74/01-janvier/visa-medical-pour-la-france-copie-1.jpg"/><hr/>
                Bonjour <b><xsl:value-of select="cab:cabinet/cab:infirmiers/cab:infirmier[@id=$id]/cab:prénom/text()"/></b>,   
                Aujourd'hui <strong>
         <span id="time"></span>
                </strong>    , vous avez <b><xsl:value-of select="$nbPatients"/> patient<xsl:if test="$nbPatients>1">s</xsl:if></b>.<br/>
            <br/>
                 <h3><u>Liste des patients</u></h3><br/>
                <table>
                    <xsl:apply-templates select="//cab:patient/cab:visite[@intervenant=$id and @date=$laDate]/.."/>
                </table>
                
                
            </body>
        </html>
    </xsl:template>
    
    <xsl:template match="cab:patient">
        
        <tr>
            <td>
                <h4>
                    <xsl:value-of select="cab:nom/text()"/>&#160;
                    <xsl:value-of select="cab:prénom/text()"/>
                </h4>
                <i>
                    <xsl:if test="cab:adresse/cab:étage/text()!=''">Etage <xsl:value-of select="cab:adresse/cab:étage/text()"/>
                    <br/></xsl:if>
                    <xsl:value-of select="cab:adresse/cab:numéro/text()"/>&#160;<xsl:value-of select="cab:adresse/cab:rue/text()"/>
                    <br/>
                    <xsl:value-of select="cab:adresse/cab:codePostal/text()"/>&#160;<xsl:value-of select="cab:adresse/cab:ville/text()"/>
                    <br/>
                </i>
            </td>
            <td>
                <h4>Soins :</h4> <ul>
                    <xsl:apply-templates select="cab:visite/cab:acte"/>
                </ul>
            </td>
            <td>
                
                <xsl:variable name="listeActes">
                    <xsl:call-template name="Actes" />
                </xsl:variable>
                
                <xsl:element name="button">
                    <xsl:attribute name="onclick">
                        openFacture('<xsl:value-of select="cab:prénom"/>','<xsl:value-of select="cab:nom"/>','<xsl:value-of select="$listeActes"/>')
                    </xsl:attribute>
                    <xsl:text>Facture</xsl:text>
                </xsl:element>
            </td>
        </tr>
    </xsl:template>
    
    <xsl:template match="cab:acte" name="Actes">
        <xsl:variable name="idActe" select="@id"/>
        <li><xsl:value-of select="$actes/act:actes/act:acte[@id=$idActe]/text()"/></li>
    </xsl:template>

</xsl:stylesheet>
