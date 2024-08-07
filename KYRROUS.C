/*****************************************************************************
 *                                                                           *
 *   KYRANDIA, Fantasy-world of Legends                     Version 7.20     *
 *                                                                           *
 *   KYRROUS.C (KLCROUS.C) - Room-specific command routines                  *
 *                                                                           *
 *   Designed/Programmed by: Scott Brinker & Richard Skurnick   03/18/88     *
 *                                    6.00 Converstion - E. Bush 3/12/92     *
 *                 (v7.1) Worldgroup 3.2 Conversion - R. Hadsall 4/24/2021   *
 *                   (v7.2) Major BBS 10 Conversion - R. Hadsall 4/18/2023   *
 *                                                                           *
 * Copyright (C) 1988-2024 Rick Hadsall.  All Rights Reserved.               *
 *                                                                           *
 * This program is free software: you can redistribute it and/or modify      *
 * it under the terms of the GNU Affero General Public License as published  *
 * by the Free Software Foundation, either version 3 of the License, or      *
 * (at your option) any later version.                                       *
 *                                                                           *
 * This program is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the              *
 * GNU Affero General Public License for more details.                       *
 *                                                                           *
 * You should have received a copy of the GNU Affero General Public License  *
 * along with this program. If not, see <https://www.gnu.org/licenses/>.     *
 *                                                                           *
 * Additional Terms for Contributors:                                        *
 * 1. By contributing to this project, you agree to assign all right, title, *
 *    and interest, including all copyrights, in and to your contributions   *
 *    to Rick Hadsall and Elwynor Technologies.                              *
 * 2. You grant Rick Hadsall and Elwynor Technologies a non-exclusive,       *
 *    royalty-free, worldwide license to use, reproduce, prepare derivative  *
 *    works of, publicly display, publicly perform, sublicense, and          *
 *    distribute your contributions                                          *
 * 3. You represent that you have the legal right to make your contributions *
 *    and that the contributions do not infringe any third-party rights.     *
 * 4. Rick Hadsall and Elwynor Technologies are not obligated to incorporate *
 *    any contributions into the project.                                    *
 * 5. This project is licensed under the AGPL v3, and any derivative works   *
 *    must also be licensed under the AGPL v3.                               *
 * 6. If you create an entirely new project (a fork) based on this work, it  *
 *    must also be licensed under the AGPL v3, you assign all right, title,  *
 *    and interest, including all copyrights, in and to your contributions   *
 *    to Rick Hadsall and Elwynor Technologies, and you must include these   *
 *    additional terms in your project's LICENSE file(s).                    *
 *                                                                           *
 * By contributing to this project, you agree to these terms.                *
 *                                                                           *
 *****************************************************************************/

#include "gcomm.h"
#include "majorbbs.h"
#include "kyrandia.h"
#include "elwkyrm.h"
#include "kyrspls.h"

static GBOOL drkutl(VOID);
static GBOOL chklvl(INT level);
static VOID glvutl(VOID);


struct binwrd *wrdptr;

struct binwrd seewrds[3]={
     {"examine",NULL},
     {"look",NULL},
     {"see",NULL}
};

struct binwrd buywrds[4]={
     {"buy",NULL},
     {"order",NULL},
     {"pay",NULL},
     {"purchase",NULL}
};

struct binwrd trdwrds[3]={
     {"give",NULL},
     {"sell",NULL},
     {"trade",NULL}
};

struct binwrd getwrds[4]={
     {"get",NULL},
     {"grab",NULL},
     {"pick",NULL},
     {"take",NULL}
};

struct binwrd digwrds[4]={
     {"dig",NULL},
     {"hunt",NULL},
     {"look",NULL},
     {"search",NULL}
};

struct binwrd toswrds[3]={
     {"drop",NULL},
     {"throw",NULL},
     {"toss",NULL}
};

struct binwrd putwrds[3]={
     {"lay",NULL},
     {"place",NULL},
     {"put",NULL}
};

struct binwrd drpwrds[5]={
     {"drop",NULL},
     {"insert",NULL},
     {"put",NULL},
     {"stick",NULL},
     {"thrust",NULL}
};

struct binwrd saywrds[3]={
     {"say",NULL},
     {"speak",NULL},
     {"state",NULL}
};

static struct gemlst {
     CHAR *name;
     INT value;
} gemlst[12]={
     {"ruby",22},
     {"emerald",25},
     {"garnet",2},
     {"pearl",6},
     {"aquamarine",9},
     {"moonstone",32},
     {"sapphire",16},
     {"diamond",30},
     {"amethyst",10},
     {"onyx",28},
     {"opal",12},
     {"bloodstone",20}
};

static struct spurch {
     struct spell *spell;
     INT price;
} splinv[16]={
     {&spells[5],80},      /* burnup  */
     {&spells[7],100},     /* cantcmeha */
     {&spells[10],50},     /* clutzopho */
     {&spells[11],40},     /* cuseme  */
     {&spells[16],60},     /* fpandl  */
     {&spells[27],400},    /* hocus   */
     {&spells[33],25},     /* howru   */
     {&spells[39],60},     /* koolit  */
     {&spells[42],30},     /* noouch  */
     {&spells[47],45},     /* pocus   */
     {&spells[54],35},     /* sunglass */
     {&spells[57],75},     /* thedoc   */
     {&spells[58],1000},   /* tiltowait */
     {&spells[61],120},    /* weewillo */
     {&spells[62],100},    /* whereami */
     {&spells[65],50}      /* zapher  */
}, *s2bptr;

CHAR_BUFFER(SAYDONE, 80, "...Done.\r");
CHAR_BUFFER(SAYOUCH, 80, "...Ouch!\r");
CHAR_BUFFER(YOURPRAYERHEARD, 80, "...Your prayers are heard.\r");
CHAR_BUFFER(GODDESSBLESSESYOU, 80, "...The Goddess blesses you.\r");


GBOOL
willow(VOID)                       /* willow tree room specific handling   */
{
     CHAR *stg;

     gi_bagthe();
     bagprep();
     if ((wrdptr=binchk(margv[0],seewrds,3)) != NULL) {
          if (margc > 1
            && (sameto(margv[1],"tree") || sameto(margv[1],"willow"))) {
               prfmsg(KID046);
               outprf(usrnum);
               return(FALSE);
          }
          return(TRUE);
     }
     stg=getmsg(WILCMD);
     if (sameas(margv[0],stg)) {
          if (chklvl(2)) {
               glvutl();
               gmpptr->defspls|=SBD053;
               msgutl2(LVL200,GETLVL);
          }
          return(FALSE);
     }
     return(TRUE);
}

GBOOL
getgol(VOID)                       /* exchange gems for gold or items      */
{
     INT i;

     gi_bagthe();
     if ((wrdptr=binchk(margv[0],trdwrds,3)) != NULL) {
          if (margc > 1 && (objptr=fgmpobj(margv[1])) != NULL) {
               for (i=0 ; i < 12 ; i++) {
                    if (sameas(objptr->name,gemlst[i].name)) {
                         tgmpobj(objno);
                         gmpptr->gold+=(USHORT)gemlst[i].value;
                         prfmsg(TRDM00,gemlst[i].value);
                         outprf(usrnum);
                         prfmsg(TRDM01,gmpptr->altnam,dobutl(objptr),
                                       gemlst[i].value);
                         sndoth();
                         return(FALSE);
                    }
               }
               if (sameas(objptr->name,"kyragem")) {
                    tgmpobj(objno);
                    pgmpobj(&gmobjs[28],0);
                    prfmsg(TRDM02);
                    outprf(usrnum);
                    prfmsg(TRDM03,gmpptr->altnam);
                    sndoth();
                    return(FALSE);
               }
               prfmsg(TRDM04);
               outprf(usrnum);
               prfmsg(TRDM03,gmpptr->altnam);
               sndoth();
               return(FALSE);
          }
          prfmsg(TRDM05);
          outprf(usrnum);
          prfmsg(TRDM03,gmpptr->altnam);
          sndoth();
          return(FALSE);
     }
     return(TRUE);
}

GBOOL
buyspl(VOID)                       /* buy a spell and pay for it           */
{
     INT i;

     gi_bagthe();
     bagprep();
     if ((wrdptr=binchk(margv[0],buywrds,4)) != NULL) {
          for (i=0 ; i < 16 ; i++) {
               if (sameto(splinv[i].spell->name,margv[1])) {
                    s2bptr=&splinv[i];
                    if (s2bptr->price > gmpptr->gold) {
                         prfmsg(BUYM00);
                         outprf(usrnum);
                         prfmsg(BUYM01,gmpptr->altnam,himher(gmpptr));
                         sndoth();
                    }
                    else {
                         prfmsg(BUYM02);
                         outprf(usrnum);
                         prfmsg(BUYM03,gmpptr->altnam,hisher(gmpptr),
                                       gmpptr->altnam);
                         sndoth();
                         gmpptr->gold-=(USHORT)s2bptr->price;
                         switch (s2bptr->spell->sbkref) {
                         case OFFENS:
                              gmpptr->offspls|=s2bptr->spell->bitdef;
                              break;
                         case DEFENS:
                              gmpptr->defspls|=s2bptr->spell->bitdef;
                              break;
                         case OTHERS:
                              gmpptr->othspls|=s2bptr->spell->bitdef;
                         }
                    }
                    return(FALSE);
               }
          }
          prfmsg(BUYM04);
          outprf(usrnum);
          prfmsg(BUYM01,gmpptr->altnam,himher(gmpptr));
          sndoth();
          return(FALSE);
     }
     return(TRUE);
}

GBOOL
temple(VOID)                       /* temple room specific command handling*/
{
     INT gold,offer;
     CHAR *stg;

     gi_bagthe();
     if ((wrdptr=binchk(margv[0],putwrds,3)) != NULL) {
          if ((objptr=fgmpobj(margv[1])) != NULL && chantd == 5) {
               offer=(INT)(objptr-gmobjs);
               tgmpobj(objno);
               switch (offer) {
               case 18:
                    if (chklvl(9)) {
                         glvutl();
                         msgutl2(LVL9M0,LVL9M1);
                    }
                    break;
               case 21:
                    if (chklvl(10)) {
                         glvutl();
                         msgutl2(LV10M0,LVL9M1);
                    }
                    break;
               default:
                    msgutl2(OFFER0,OFFER1);
               }
               return(FALSE);
          }
     }
     if (margc > 1
       && sameas(margv[0],"chant") && sameas(margv[1],"tashanna")) {
          btuxmt(usrnum,SAYDONE);
          prf("***\rThe altar ");
          if (!chantd) {
               prf("begins to glow dimly.\r");
          }
          else {
               prf("glows even brighter!\r");
          }
          sndloc(7);
          chantd++;
          return(FALSE);
     }
     rstrin();
     stg=getmsg(TEMPLE);
     if (margc > 1 && sameas(margv[1],stg)) {
          if (chklvl(3)) {
               glvutl();
               msgutl2(LVL300,GETLVL);
          }
          return(FALSE);
     }
     parsin();
     if (sameas(margv[0],"pray") || sameas(margv[0],"meditate")) {
          prfmsg(TMPRAY);
          outprf(usrnum);
          sndutl("praying to the Goddess Tashanna.");
          return(FALSE);
     }
     if (sameas(margv[0],"marry") || sameas(margv[0],"wed")) {
          if (findgp(margv[1])) {
               if (gmpptr->flags&MARRYD) {
                    prfmsg(MARRY0,gmpptr->spouse);
                    outprf(usrnum);
                    prfmsg(MARRY1,gmpptr->altnam);
                    sndoth();
               }
               else if (gmpptr == ogmptr) {
                    msgutl2(MARRY2,MARRY3);
               }
               else {
                    gmpptr->flags|=MARRYD;
                    strcpy(gmpptr->spouse,ogmptr->plyrid);
                    prfmsg(MARRY4,ogmptr->plyrid);
                    outprf(usrnum);
                    prfmsg(MARRY5,gmpptr->altnam,hisher(gmpptr));
                    outprf(ogmptr->modno);
                    prfmsg(MARRY6,gmpptr->altnam,hisher(gmpptr),ogmptr->altnam);
                    sndbt2();
               }
          }
          else {
               msgutl2(MARRY7,MARRY8);
          }
          return(FALSE);
     }
     if (margc > 2 && sameas(margv[0],"offer")
       && (sameas(margv[2],"gold") || sameas(margv[2],"pieces"))) {
          if ((gold=atoi(margv[1])) > gmpptr->gold || gold <= 0) {
               prfmsg(CHEAPO);
               outprf(usrnum);
               sndutl("looking somewhat cheap.");
          }
          else {
               if (!hasmkey(KYRKEY)) {
                    msgutl2(NPAY02,NPAY03);
                    gmpptr->gold-=(USHORT)gold;
               }
               else if (!givrcrd) {
                    prfmsg(NOGTCR);
                    outprf(usrnum);
                    prfmsg(OGETCR,gmpptr->altnam);
                    sndoth();
                    gmpptr->gold-=(USHORT)gold;
               }
               else {
                    prfmsg(UGETCR,gold);
                    outprf(usrnum);
                    prfmsg(OGETCR,gmpptr->altnam);
                    sndoth();
                    gmpptr->gold-=(USHORT)gold;
                    crdusr(usaptr->userid,l2as((LONG)gold),0,0);
                    shocst("ELW Kyrandia Credited User","GAME CREDITED: %-9s %d Cr.",usaptr->userid,gold);
               }
          }
          return(FALSE);
     }
     return(TRUE);
}

GBOOL
vhealr(VOID)                       /* healer room specific command handling*/
{
     SHORT max;

     gi_bagthe();
     if (margc > 1 && sameas(margv[0],"offer")) {
          if (sameto(margv[1],"rose")) {
               if ((objptr=fgmpobj(margv[1])) != NULL) {
                    tgmpobj(objno);
                    prfmsg(TAKROS);
                    outprf(usrnum);
                    gmpptr->hitpts+=10;
                    if (gmpptr->hitpts > (max=(gmpptr->level*4))) {
                         gmpptr->hitpts=max;
                    }
               }
               else {
                    msgutl2(NOHAVE,NOROSE);
               }
               return(FALSE);
          }
          prfmsg(NOGOOD);
          outprf(usrnum);
          return(FALSE);
     }
     return(TRUE);
}

GBOOL
gquest(VOID)                       /* brook room specific command handling */
{
     INT find;

     gi_bagthe();
     bagprep();
     if ((wrdptr=binchk(margv[0],digwrds,4)) != NULL) {
          if (margc > 1
            && sameas(margv[1],"gold") || sameas(margv[1],"brook") ||
           sameas(margv[1],"water") || sameas(margv[1],"stream")) {
               sndutl("searching the brook for something.");
               if ((find=genrdn(2,102)) < 10 && gmpptr->gold < 101) {
                    prfmsg(FNDGOL,find);
                    outprf(usrnum);
                    gmpptr->gold+=(USHORT)find;
               }
               else {
                    prfmsg(NOFNDG);
                    outprf(usrnum);
               }
               return(FALSE);
          }
     }
     if (drkutl()) {
          return(FALSE);
     }
     if (rosutl()) {
          return(FALSE);
     }
     return(TRUE);
}

GBOOL
terrac(VOID)                       /* terrace room specific command handler*/
{
     if (drkutl()) {
          return(FALSE);
     }
     return(TRUE);
}

GBOOL
waterf(VOID)
{
     if (drkutl()) {
          return(FALSE);
     }
     if (rosutl()) {
          return(FALSE);
     }
     return(TRUE);
}

GBOOL
gpcone(VOID)
{
     gi_bagthe();
     if ((wrdptr=binchk(margv[0],getwrds,4)) != NULL) {
          if (margc > 1 && sameto(margv[1],"pinecone")) {
               if ((genrdn(0,100)) < 40 && gmpptr->npobjs < MXPOBS) {
                    pgmpobj(&gmobjs[32],0);
                    msgutl2(PINEC0,PINEC1);
               }
               else {
                    msgutl2(PINEC2,PINEC3);
               }
               return(FALSE);
          }
     }
     return(TRUE);
}

GBOOL
stumpr(VOID)
{
     INT obj;

     gi_bagthe();
     if ((wrdptr=binchk(margv[0],drpwrds,5)) != NULL) {
          if ((objptr=fgmpobj(margv[1])) != NULL) {
               obj=(INT)(objptr-gmobjs);
               tgmpobj(objno);
               if (gmpptr->level == 5) {
                    if (gmpptr->stumpi == obj) {
                         gmpptr->stumpi++;
                         if (gmpptr->stumpi == 12) {
                              if (chklvl(6)) {
                                   glvutl();
                                   gmpptr->offspls|=SBD032;
                                   msgutl2(BGEM00,BGEM01);
                              }
                              else {
                                   gmpptr->stumpi=0;
                              }
                         }
                         else {
                              msgutl2(BGEM02,BGEM03);
                         }
                    }
                    else {
                         msgutl2(BGEM04,BGEM03);
                    }
               }
               else {
                    msgutl2(BGEM04,BGEM03);
               }
          }
          else {
               msgutl2(BGEM05,BGEM06);
          }
          return(FALSE);
     }
     return(TRUE);
}

GBOOL
silver(VOID)
{
     INT obj;

     gi_bagthe();
     if (sameas(margv[0],"offer")) {
          if ((objptr=fgmpobj(margv[1])) != NULL) {
               obj=(INT)(objptr-gmobjs);
               tgmpobj(objno);
               if (gmpptr->gemidx < 4
                 && obj == gmpptr->stones[gmpptr->gemidx]) {
                    gmpptr->gemidx++;
                    if (gmpptr->gemidx == 4) {
                         if (chklvl(4)) {
                              glvutl();
                              gmpptr->defspls|=SBD033;
                              msgutl2(SILVM0,SILVM1);
                         }
                         else {
                              gmpptr->gemidx=0;
                         }
                    }
                    else {
                         msgutl2(SILVM2,SILVM3);
                    }
               }
               else {
                    msgutl2(SILVM4,SILVM3);
               }
          }
          else {
               msgutl2(TRDM05,SILVM5);
          }
          return(FALSE);
     }
     if (sameas(margv[0],"pray") || sameas(margv[0],"meditate")) {
          prfmsg(SAPRAY);
          outprf(usrnum);
          sndutl("praying to the Goddess Tashanna.");
          return(FALSE);
     }
     return(TRUE);
}

GBOOL
rubies(VOID)
{
     gi_bagthe();
     if ((wrdptr=binchk(margv[0],getwrds,4)) != NULL) {
          if (margc > 1 && sameas(margv[1],"ruby")) {
               if ((genrdn(0,100)) < 20 && gmpptr->npobjs < MXPOBS) {
                    pgmpobj(&gmobjs[0],0);
                    msgutl2(RUBY00,RUBY01);
               }
               else {
                    msgutl2(RUBY02,RUBY03);
                    ogmptr=gmpptr;
                    hitoth(8);
               }
               return(FALSE);
          }
     }
     return(TRUE);
}

GBOOL
druids(VOID)
{
     INT i;
     static LONG dspells[5]={
          SBD010,SBD018,SBD019,SBD021,SBD030
     };

     gi_bagthe();
     if (margc > 2 && sameas(margv[0],"touch") && sameas(margv[1],"orb") &&
      sameas(margv[3],"sceptre")) {
          if ((objptr=fgmpobj(margv[3])) != NULL) {
               tgmpobj(objno);
               i=genrdn(0,5);
               gmpptr->offspls|=(dspells[i]);
               msgutl2(DRUID0,DRUID1);
          }
          else {
               msgutl2(DRUID2,DRUID1);
          }
          return(FALSE);
     }
     return(TRUE);
}

GBOOL
fthick(VOID)
{
     gi_bagthe();
     bagprep();
     bagwrd("flaming");
     if (margc > 1 && sameas(margv[0],"walk") && sameas(margv[1],"thicket")) {
          btuxmt(usrnum,SAYOUCH);
          sndutl("burning in the flaming thicket!");
          ogmptr=gmpptr;
          hitoth(10);
          return(FALSE);
     }
     return(TRUE);
}

GBOOL
fearno(VOID)
{
     CHAR *stg;

     rstrin();
     stg=getmsg(EGLADE);
     if (sameas(margv[0],stg)) {
          if (chklvl(5)) {
               glvutl();
               msgutl2(FEAR01,FEAR02);
          }
          return(FALSE);
     }
     parsin();
     return(TRUE);
}

GBOOL
swrock(VOID)
{
     gi_bagthe();
     bagprep();
     if (sameas(margv[0],"pray")) {
          btuxmt(usrnum, YOURPRAYERHEARD);
          prf("***\rThe mists around the rock begin to swirl magically!\r");
          sndloc(27);
          rockpr++;
     }
     if ((wrdptr=binchk(margv[0],drpwrds,5)) != NULL) {
          if (margc > 2
            && sameto(margv[1],"sword") && sameto(margv[2],"rock") && rockpr) {
               if ((objptr=fgmpobj(margv[1])) != NULL) {
                    tgmpobj(objno);
                    pgmpobj(&gmobjs[21],0);
                    msgutl2(ROCK00,ROCK01);
               }
               else {
                    msgutl2(ROCK02,ROCK01);
               }
               return(FALSE);
          }
     }
     return(TRUE);
}

GBOOL
ashtre(VOID)
{
     gi_bagthe();
     bagprep();
     if (sameas(margv[0],"cry") || sameas(margv[0],"weep")) {
          if (margc > 1
            && (sameto(margv[1],"trees") || sameto(margv[1],"ashes"))) {
               msgutl2(ASHM00,ASHM01);
               if (gmlptr->nlobjs < MXLOBS) {
                    pgmlobj(&gmobjs[43]);
               }
               else {
                    prfmsg(ASHM02);
                    sndloc(gmpptr->gamloc);
               }
               return(FALSE);
          }
     }
     return(TRUE);
}

GBOOL
spring(VOID)
{
     if (drkutl()) {
          return(FALSE);
     }
     if (rosutl()) {
          return(FALSE);
     }
     return(TRUE);
}

GBOOL
rosutl(VOID)
{
     if ((wrdptr=binchk(margv[0],getwrds,4)) != NULL) {
          if (margc > 1 && sameas(margv[1],"rose")) {
               if (gmpptr->npobjs >= MXPOBS) {
                    msgutl2(GROSE3,GROSE4);
               }
               else {
                    pgmpobj(&gmobjs[40],0);
                    msgutl2(GROSE1,GROSE2);
               }
               return(TRUE);
          }
     }
     return(FALSE);
}

GBOOL
magicf(VOID)
{
     INT var,sloc;
     static INT scroll,shard;
     CHAR *stg;

     rstrin();
     stg=getmsg(FOUNTI);
     if (sameas(margv[0],stg)) {
          btuxmt(usrnum, GODDESSBLESSESYOU);
          gmpptr->flags|=BLESSD;
          return(FALSE);
     }
     parsin();
     gi_bagthe();
     if ((wrdptr=binchk(margv[0],toswrds,3)) != NULL) {
          if ((objptr=fgmpobj(margv[1])) != NULL) {
               if (margc > 3 && sameas(margv[3],"fountain")) {
                    tgmpobj(objno);
                    var=(INT)(objptr-gmobjs);
                    switch (var) {
                    case 32:
                         if (gmpptr->flags&BLESSD) {
                              scroll++;
                         }
                         if (scroll == 3) {
                              scroll=0;
                              sloc=genrdn(0,168);
                              if (gmlocs[sloc].nlobjs < MXLOBS) {
                                   putlobj(&gmlocs[sloc],&gmobjs[35]);
                              }
                              msgutl2(MAGF00,MAGF01);
                         }
                         else {
                              msgutl2(MAGF04,MAGF07);
                         }
                         break;
                    case 43:
                         shard++;
                         if (shard == 6) {
                              shard=0;
                              pgmpobj(&gmobjs[16],0);
                              msgutl2(MAGF05,MAGF03);
                         }
                         else {
                              msgutl2(MAGF06,MAGF03);
                         }
                         break;
                    default:
                         msgutl2(MAGF02,MAGF03);
                    }
                    return(FALSE);
               }
          }
     }
     if (drkutl()) {
          return(FALSE);
     }
     return(TRUE);
}

GBOOL
hnsrou(VOID)
{
     if (margc && sameas(margv[0],"offer")) {
          if (margc > 3 && sameas(margv[1],"heart")
            && sameas(margv[3],"soul")) {
               if (sameas(margv[5],"tashanna")) {
                    if (chklvl(7)) {
                         glvutl();
                         gmpptr->othspls|=SBD062;
                         msgutl2(HNSYOU,HNSOTH);
                    }
                    return(FALSE);
               }
          }
     }
     return(TRUE);
}

GBOOL
tashas(VOID)
{
     gi_bagthe();
     if (margc > 1 && sameas(margv[0],"imagine") && sameas(margv[1],"dagger")) {
          if (gmpptr->npobjs < MXPOBS) {
               pgmpobj(&gmobjs[33],0);
               msgutl2(DAGM00,DAGM01);
          }
          else {
               msgutl2(DAGM02,DAGM01);
          }
          return(FALSE);
     }
     bagprep();
     if ((wrdptr=binchk(margv[0],seewrds,3)) != NULL
       && sameas(margv[1],"statue")) {
          msgutl2(DAGM03,DAGM04);
          return(FALSE);
     }
     return(TRUE);
}

GBOOL
refpoo(VOID)
{
     gi_bagthe();
     bagprep();
     if ((wrdptr=binchk(margv[0],toswrds,3)) != NULL && margc > 2
       && sameas(margv[2],"pool")) {
          if (sameas(margv[1],"dagger") && (objptr=fgmpobj(margv[1])) != NULL) {
               tgmpobj(objno);
               pgmpobj(&gmobjs[34],0);
               msgutl2(REFM00,REFM01);
          }
          else {
               msgutl2(REFM02,REFM01);
          }
          return(FALSE);
     }
     if ((wrdptr=binchk(margv[0],seewrds,3)) != NULL && margc > 1
       && sameas(margv[1],"pool")) {
          msgutl2(REFM03,REFM04);
          return(FALSE);
     }
     return(TRUE);
}

GBOOL
panthe(VOID)
{
     if ((wrdptr=binchk(margv[0],saywrds,3)) != NULL) {
          if (margc == 13 &&
            sameas(margv[1],"legends") &&
            sameas(margv[4],"time") &&
            sameas(margv[8],"true") &&
            sameas(margv[11],"never") &&
            sameas(margv[12],"die")) {
               if (gmpptr->npobjs < MXPOBS) {
                    pgmpobj(&gmobjs[14],0);
                    msgutl2(PANM00,PANM01);
                }
               else {
                    msgutl2(PANM02,PANM01);
               }
               return(FALSE);
          }
     }
     gi_bagthe();
     bagprep();
     if ((wrdptr=binchk(margv[0],seewrds,3)) != NULL) {
          if (sameto(margv[1],"symbols") || sameto(margv[1],"pillars")) {
               msgutl2(PANM03,PANM04);
               return(FALSE);
          }
     }
     return(TRUE);
}

GBOOL
portal(VOID)
{
     INT i;

     gi_bagthe();
     if (margc > 1 && sameas(margv[0],"enter") && sameto(margv[1],"portal")) {
          i=genrdn(1,10);
          prfmsg(PORTAL);
          prfmsg(PORTAL+i);
          prfmsg(ENDPOR);
          outprf(usrnum);
          prfmsg(OEPORT,gmpptr->altnam,kheshe(gmpptr));
          sndoth();
          return(FALSE);
     }
     return(TRUE);
}

GBOOL
waller(VOID)
{
     gi_bagthe();
     bagprep();
     if (margc > 2 && (wrdptr=binchk(margv[0],drpwrds,5)) != NULL
       && sameas(margv[2],"crevice")) {
          if (sameas(margv[1],"key") && (objptr=fgmpobj(margv[1])) != NULL
            && sesame) {
               tgmpobj(objno);
               prfmsg(WALM00);
               remvgp(gmpptr,"vanished in a golden flash of light");
               entrgp(186,gmpptr,"appeared in a golden flash of light");
          }
          else {
               msgutl2(WALM01,WALM02);
          }
          return(FALSE);
     }
     if (sameas(margv[0],"chant") || sameas(margv[1],"opensesame")) {
          sesame=1;
          msgutl2(WALM03,WALM04);
          return(FALSE);
     }
     return(TRUE);
}

GBOOL
slotma(VOID)
{
     INT objidx;

     gi_bagthe();
     bagprep();
     if (margc > 2 && (wrdptr=binchk(margv[0],drpwrds,5)) != NULL
       && sameas(margv[2],"slot")) {
          if (sameas(margv[1],"garnet") && (objptr=fgmpobj(margv[1])) != NULL) {
               tgmpobj(objno);
               if ((genrdn(1,11)) < 3) {
                    objidx=genrdn(0,12);
                    pgmpobj(&gmobjs[objidx],0);
                    msgutl2(SLOT00,SLOT01);
                    prfmsg(SLOT02,dobutl(&gmobjs[objidx]));
                    outprf(usrnum);
               }
               else {
                    msgutl2(SLOT03,SLOT04);
               }
               return(FALSE);
          }
     }
     return(TRUE);
}

GBOOL
mistyr(VOID)
{
     gi_bagthe();
     if (sameas(margv[0],"touch") || sameas(margv[0],"get")) {
          if (sameas(margv[1],"orb")) {
               prfmsg(MISM00);
               outprf(usrnum);
               remvgp(gmpptr,"vanished in a bright blue flash");
               entrgp(34,gmpptr,"appeared in a bright blue flash");
               return(FALSE);
          }
     }
     if (sameas(margv[0],"think") || sameas(margv[0],"concentrate")
       || sameas(margv[0],"meditate")) {
          if (sameas(margv[1],"orb") || sameas(margv[2],"orb")) {
               if (gmpptr->npobjs < MXPOBS) {
                    pgmpobj(&gmobjs[18],0);
                    msgutl2(MISM01,MISM02);
               }
               else {
                    msgutl2(MISM03,MISM02);
               }
               return(FALSE);
          }
     }
     bagprep();
     if (margc > 2 && (wrdptr=binchk(margv[0],drpwrds,5)) != NULL
       && sameas(margv[2],"orb")) {
          if (sameas(margv[1],"dagger") && (objptr=fgmpobj(margv[1])) != NULL) {
               if (chklvl(8)) {
                    tgmpobj(objno);
                    glvutl();
                    msgutl2(MISM04,MISM05);
               }
               return(FALSE);
          }
     }
     return(TRUE);
}

GBOOL
sanman(VOID)
{
     gi_bagthe();
     bagprep();
     if ((wrdptr=binchk(margv[0],digwrds,4)) != NULL) {
          if (sameas(margv[1],"sand")) {
               if ((genrdn(0,100)) < 10) {
                    gmpptr->gold++;
                    msgutl2(SANM00,SANM01);
               }
               else {
                    msgutl2(SANM02,SANM01);
               }
               return(FALSE);
          }
     }
     return(TRUE);
}

GBOOL
tulips(VOID)
{
     gi_bagthe();
     if ((wrdptr=binchk(margv[0],getwrds,4)) != NULL
       && sameas(margv[1],"tulip")) {
          if (gmpptr->npobjs < MXPOBS) {
               pgmpobj(&gmobjs[44],0);
               msgutl2(TULM00,TULM01);
          }
          else {
               msgutl2(TULM02,TULM01);
          }
          return(FALSE);
     }
     return(TRUE);
}

GBOOL
crystt(VOID)
{
     gi_bagthe();
     bagprep();
     bagwrd("crystal");
     if (sameas(margv[0],"aim") && sameas(margv[2],"tree")) {
          if (sameas(margv[1],"wand") && (objptr=fgmpobj(margv[1])) != NULL) {
               if (chklvl(11)) {
                    glvutl();
                    msgutl2(CTREM0,CTREM1);
               }
               return(FALSE);
          }
     }
     return(TRUE);
}

GBOOL
rainbo(VOID)
{
     gi_bagthe();
     if (sameas(margv[0],"break")) {
          if (sameto(margv[1],"wand") && (objptr=fgmpobj("wand")) != NULL) {
               tgmpobj(objno);
               if (gmpptr->flags&GOTKYG) {
                    msgutl2(RABOM0,RABOM1);
               }
               else {
                    msgutl2(RABOM2,RABOM3);
                    pgmpobj(&gmobjs[29],0);
                    gmpptr->flags|=GOTKYG;
               }
               return(FALSE);
          }
     }
     return(TRUE);
}

GBOOL
sunshi(VOID)
{
     gi_bagthe();
     bagprep();
     if (sameas(margv[0],"cast")) {
          if (sameas(margv[1],"zapher")) {
               if (sameas(margv[2],"tulip")
                 && (objptr=fgmpobj("tulip")) != NULL) {
                    tgmpobj(objno);
                    pgmpobj(&gmobjs[26],0);
                    msgutl2(SUNM00,SUNM01);
                    return(FALSE);
               }
          }
          if (sameas(margv[1],"zennyra")) {
               msgutl2(SUNM02,SUNM01);
               return(FALSE);
          }
     }
     if (sameas(margv[0],"offer")) {
          if (sameas(margv[1],"kyragem")
            && (objptr=fgmpobj(margv[1])) != NULL) {
               if (chklvl(12)) {
                    glvutl();
                    msgutl2(SUNM03,SUNM04);
               }
               return(FALSE);
          }
     }
     return(TRUE);
}

GBOOL
demong(VOID)
{
     gi_bagthe();
     bagprep();
     if ((wrdptr=binchk(margv[0],drpwrds,5)) != NULL) {
          if (sameas(margv[1],"soulstone")
            && (objptr=fgmpobj("soulstone")) != NULL) {
               if (sameas(margv[2],"niche")) {
                    prfmsg(SOUKEY);
                    outprf(usrnum);
                    remvgp(gmpptr,"vanished through the demon gate");
                    entrgp(219,gmpptr,"appeared in a column of blue flame");
                    return(FALSE);
               }
          }
     }
     return(TRUE);
}

GBOOL
bodyma(VOID)
{
     gi_bagthe();
     bagwrd("across");
     if (margc > 1 && (sameas(margv[0],"jump") || sameas(margv[0],"leap"))) {
          if (sameas(margv[1],"chasm")) {
               if (gmpptr->charms[OBJPRO]) {
                    if (chklvl(13)) {
                         msgutl2(BODM01,BODM02);
                         if (gmpptr->npobjs == MXPOBS) {
                              tgmpobj(0);
                              prfmsg(BODM03);
                              outprf(usrnum);
                         }
                         pgmpobj(&gmobjs[23],0);
                         glvutl();
                    }
               }
               else {
                    msgutl2(BODM04,BODM05);
                    ogmptr=gmpptr;
                    hitoth(100);
               }
               return(FALSE);
          }
     }
     return(TRUE);
}

GBOOL
mindma(VOID)
{
     if (sameas(margv[0],"answer") && sameas(margv[1],"time")) {
          if (chklvl(14)) {
               msgutl2(MINM01,MINM02);
               if (gmpptr->npobjs == MXPOBS) {
                    tgmpobj(0);
                    prfmsg(MINM03);
                    outprf(usrnum);
               }
               pgmpobj(&gmobjs[17],0);
               glvutl();
          }
          return(FALSE);
     }
     return(TRUE);
}

GBOOL
heartm(VOID)
{
     bagprep();
     if (margc == 3 && sameas(margv[0],"offer") && sameas(margv[1],"heart")) {
          if (sameas(margv[2],gmpptr->spouse)) {
               if (chklvl(15)) {
                    msgutl2(HEAR01,HEAR02);
                    if (gmpptr->npobjs == MXPOBS) {
                         tgmpobj(0);
                         prfmsg(HEAR03);
                         outprf(usrnum);
                    }
                    pgmpobj(&gmobjs[15],0);
                    glvutl();
               }
               return(FALSE);
          }
     }
     return(TRUE);
}

GBOOL
soulma(VOID)
{
     if (sameas(margv[0],"ignore") && sameas(margv[1],"time")) {
          if (chklvl(16)) {
               msgutl2(SOUL01,SOUL02);
               if (gmpptr->npobjs == MXPOBS) {
                    tgmpobj(0);
                    prfmsg(SOUL03);
                    outprf(usrnum);
               }
               pgmpobj(&gmobjs[39],0);
               glvutl();
          }
          return(FALSE);
     }
     return(TRUE);
}

GBOOL
devote(VOID)
{
     if (sameas(margv[0],"devote")) {
          if (chklvl(17)) {
               if (fouris()) {
                    msgutl2(DEVM01,DEVM02);
                    glvutl();
               }
               else {
                    msgutl2(DEVM03,DEVM04);
               }
          }
          return(FALSE);
     }
     return(TRUE);
}

GBOOL
truthy(VOID)
{
     gi_bagthe();
     if (sameas(margv[0],"seek") && sameas(margv[1],"truth")) {
          if (chklvl(18)) {
               if (genrdn(0,100) < 50) {
                    prfmsg(TRUM01);
                    outprf(usrnum);
                    ogmptr=gmpptr;
                    hitoth(100);
               }
               else {
                    msgutl2(TRUM02,TRUM03);
                    glvutl();
               }
          }
          return(FALSE);
     }
     return(TRUE);
}

GBOOL
fouris(VOID)
{
     if ((objptr=fgmpobj("broach")) == NULL) {
          return(FALSE);
     }
     if ((objptr=fgmpobj("pendant")) == NULL) {
          return(FALSE);
     }
     if ((objptr=fgmpobj("locket")) == NULL) {
          return(FALSE);
     }
     if ((objptr=fgmpobj("ring")) == NULL) {
          return(FALSE);
     }
     fgmpobj("broach");
     tgmpobj(objno);
     fgmpobj("pendant");
     tgmpobj(objno);
     fgmpobj("locket");
     tgmpobj(objno);
     fgmpobj("ring");
     tgmpobj(objno);
     return(TRUE);
}

GBOOL
singer(VOID)
{
     if (sameas(margv[0],"sing")
       || sameas(margv[0],"hum") || sameas(margv[0],"whistle")) {
          if (chklvl(19)) {
               msgutl2(LEVL19,LVL9M1);
               glvutl();
          }
          return(FALSE);
     }
     return(TRUE);
}

GBOOL
forgtr(VOID)
{
     if (sameas(margv[0],"forget")) {
          if (chklvl(20)) {
               msgutl2(LEVL20,LVL9M1);
               glvutl();
          }
          return(FALSE);
     }
     return(TRUE);
}

GBOOL
oflove(VOID)
{
     if (sameas(margv[0],"offer") &&
       (sameas(margv[1],"love") || sameas(margv[2],"love"))) {
          if (chklvl(22)) {
               msgutl2(LEVL22,LVL9M1);
               glvutl();
          }
          return(FALSE);
     }
     return(TRUE);
}

GBOOL
believ(VOID)
{
     if (sameas(margv[0],"believe") && sameas(margv[1],"in")
       && sameas(margv[2],"magic")) {
          if (chklvl(21)) {
               msgutl2(LEVL21,LVL9M1);
               glvutl();
          }
          return(FALSE);
     }
     return(TRUE);
}

GBOOL
philos(VOID)
{
     if (sameas(margv[0],"wonder") || sameas(margv[0],"consider")) {
          if (chklvl(23)) {
               msgutl2(LEVL23,LVL9M1);
               glvutl();
          }
          return(FALSE);
     }
     return(TRUE);
}

GBOOL
fanbel(VOID)
{
     CHAR *stg;

     rstrin();
     stg=getmsg(BELINF);
     if (sameas(margv[0],stg)) {
          if (chklvl(24)) {
               msgutl2(LEVL24,LVL9M1);
               glvutl();
          }
          return(FALSE);
     }
     parsin();
     return(TRUE);
}

GBOOL
wingam(VOID)
{
     CHAR *stg;
     if (sameas(margv[0],"answer") && zloc == 302) {
          rstrin();
          stg=getmsg(RIDDLE);
          if (sameas(stg,margv[1])) {
               if (chklvl(25)) {
                    shocst("ELW Kyrandia Winner!","%s COMPLETED KYRANDIA!",usaptr->userid);
                    msgutl2(YOUWIN,SHEWON);
                    glvutl();
               }
               return(FALSE);
          }
     }
     return(TRUE);
}

static GBOOL
drkutl(VOID)
{
     gi_bagthe();
     if (margc && sameas(margv[0],"drink") && sameas(margv[1],"water")) {
          msgutl2(DRINK0,DRINK1);
          return(TRUE);
     }
     return(FALSE);
}

static GBOOL
chklvl(
INT level)
{
     if (gmpptr->level == (level-1)) {
          if (!hasmkey(KYRKEY)) {
               msgutl2(NPAY00,NPAY01);
               return(FALSE);
          }
          return(TRUE);
     }
     if (gmpptr->level >= level) {
          msgutl2(LVLM00,LVLM01);
     }
     else {
          msgutl2(LVLM02,LVLM03);
     }
     return(FALSE);
}

static VOID
glvutl(VOID)
{
     gmpptr->level++;
     gmpptr->nmpdes++;
     gmpptr->hitpts+=4;
     gmpptr->spts+=2;
}
