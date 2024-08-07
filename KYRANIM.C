/*****************************************************************************
 *                                                                           *
 *   KYRANDIA, Fantasy-world of Legends                     Version 7.20     *
 *                                                                           *
 *   KYRANIM.C (ANIMATOR.C) - Creature animation routines and timers         *
 *                                                                           *
 *   Designed/Programmed by: Scott Brinker & Richard Skurnick   03/18/88     *
 *                                      6.0 Conversion - E. Bush 3/12/92     *
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
#include "elwkyrm.h"
#include "kyrandia.h"

static struct gmplyr *rndlgp(INT);
static GBOOL zarfood(VOID);
static VOID rmvzar(INT);
static VOID pzinlc(INT,INT);
static VOID dthbyz(VOID);
static VOID dryads(VOID);
static VOID elves(VOID);
static VOID browns(VOID);
static VOID gemakr(VOID);
static VOID zarapp(VOID);

INT dloc=0;                   /* dryad's current location number           */
struct gamloc *dryloc;        /* pointer to dryad's current location       */
INT bpath[40]={               /* path of movement for the brownie          */
     71,144,66,29,82,96,136,31,114,134,
     67,52,103,53,43,150,137,18,0,129,
     168,77,133,92,61,101,73,99,69,111,
     45,132,3,2,55,60,160,48,70,112
};

INT sesame;
INT chantd;
INT rockpr;
INT bpidx=0;                  /* current path index for the brownie        */
INT bloc=0;                   /* brownie's current location number         */
INT zloc=0;                   /* Zar's current location number             */
INT zstat=0;                  /* Zar's current status  (sleep,move,fly)    */
INT zattck=0;                 /* Zar's next form of attack (bite,etc.)     */
INT ngpszl=0;                 /* number of players in Zar's cur. location  */
struct gamloc *zarloc;        /* pointer to Zar's current location         */


VOID
inianm(VOID)
{
     pzinlc(ZARHOM,HLPFAN);
     rtkick(30,animat);
}

static struct gmplyr *
rndlgp(                            /* find a player at specified location  */
INT loc)
{
     INT i;
     struct gmplyr *jnkgp;

     for (jnkgp=gmparr,i=0 ; i < nterms ; jnkgp++,i++) {
          if (jnkgp->gamloc == loc) {
               return(jnkgp);
          }
     }
     return(NULL);
}

VOID
animat(VOID)                       /* rtkick main animation handler        */
{
     static INT var;

     setmbk(kmb);
     chkzar();
     switch (var) {
     case 0:
          dryads();
          break;
     case 1:
          elves();
          break;
     case 2:
     case 3:
          gemakr();
          break;
     case 4:
          zarapp();
          break;
     default:
          browns();
          var=-1;
     }
     if (sesame) {
          prfmsg(WALM05);
          sndloc(185);
          sesame=0;
     }
     if (chantd) {
          chantd=0;
          prf("***\rThe altar stops glowing.\r");
          sndloc(7);
     }
     if (rockpr) {
          rockpr=0;
          prf("***\rThe mists settle down.\r");
          sndloc(27);
     }
     var++;
     rtkick(15,animat);
}

VOID
chkzar(VOID)                       /* manage Zar's activities              */
{
     static INT zarctr=0;

     if (zarctr > 24) {
          rmvzar(ZMSG00);
          pzinlc(ZARHOM,ZMSG01);
          zarctr=0;
     }
     else if (zarctr < 5) {
          zarfood();
     }
     else {
          if (!zarfood()) {
               rmvzar(ZMSG00);
               pzinlc(genrdn(219,300),ZMSG01);
          }
     }
     zarctr++;
}

VOID
zaritm(VOID)                       /* handle using a dragonstaff           */
{
     sndutl("rubbing %s dragonstaff!");
     if (zloc == gmpptr->gamloc) {
          prfmsg(ZMSG12);
          prfmsg(ZMSG14);
          outprf(usrnum);
          tgmpobj(objno);
          zarfood();
     }
     else {
          tgmpobj(objno);
          prfmsg(ZMSG13);
          outprf(usrnum);
          rmvzar(ZMSG10);
          pzinlc(gmpptr->gamloc,ZMSG11);
          prfmsg(ZMSG14);
          outprf(usrnum);
          if ((genrdn(0,2)) == 1) {
               zarfood();
          }
     }
}

static GBOOL
zarfood(VOID)                      /* attack users in Zar's room           */
{
     if (ngpslc(zloc)) {
          dthbyz();
          return(TRUE);
     }
     return(FALSE);
}

static VOID
rmvzar(                            /* remove Zar from a room               */
INT msgno)
{
     if ((objptr=fndlobj(zarloc,"dragon")) == NULL) {
          catastro("KYRANDIA ERROR: ZAR ON LOOSE");
     }
     taklobj(zarloc,objno);
     prfmsg(msgno);
     sndloc(zloc);
}

static VOID
pzinlc(                            /* pur Zar in a room                    */
INT loc,
INT msgno)
{
     INT retdry=0;

     if ((objptr=fndlobj(&gmlocs[loc],"dryad")) == NULL) {
     }
     else {
          retdry=1;
     }
     zloc=loc;
     zarloc=&gmlocs[loc];
     zarloc->nlobjs=0;
     putlobj(zarloc,&gmobjs[52]);
     switch (loc) {
     case 0:
          putlobj(zarloc,&gmobjs[46]);
          break;
     case 7:
          putlobj(zarloc,&gmobjs[47]);
          break;
     case 9:
          putlobj(zarloc,&gmobjs[48]);
          break;
     case 42:
          putlobj(zarloc,&gmobjs[49]);
          break;
     case 101:
          putlobj(zarloc,&gmobjs[50]);
          break;
     case 186:
          putlobj(zarloc,&gmobjs[51]);
          break;
     case 295:
          putlobj(zarloc,&gmobjs[53]);
          break;
     }
     if (retdry) {
          putlobj(zarloc,&gmobjs[45]);
     }
     prfmsg(msgno);
     sndloc(loc);
}

static VOID
dthbyz(VOID)                       /* attack each user in a different way  */
{
     INT i;

     prfmsg(ZMSG02);
     sndloc(zloc);
     for (gmpptr=gmparr,i=0 ; i < nterms ; gmpptr++,i++) {
          if (zattck == 4) {
               zattck=BITE;
          }
          if (gmpptr->gamloc == zloc && gmpptr->level < 25) {
               prfmsg(ZMSG07,gmpptr->altnam);
               sndoth();
               switch (zattck) {
               case BITE:
                    prfmsg(ZMSG03);
                    outprf(gmpptr->modno);
                    ogmptr=gmpptr;
                    hitoth(16);
                    break;
               case BREATH:
                    prfmsg(ZMSG04);
                    outprf(gmpptr->modno);
                    if (gmpptr->charms[FIRPRO]) {
                         ogmptr=gmpptr;
                         hitoth(28);
                    }
                    else {
                         ogmptr=gmpptr;
                         hitoth(48);
                    }
                    break;
               case CLAW:
                    prfmsg(ZMSG05);
                    outprf(gmpptr->modno);
                    ogmptr=gmpptr;
                    hitoth(12);
                    break;
               case LIGHTN:
                    prfmsg(ZMSG06);
                    outprf(gmpptr->modno);
                    if (gmpptr->charms[LIGPRO]) {
                         ogmptr=gmpptr;
                         hitoth(16);
                    }
                    else {
                         ogmptr=gmpptr;
                         hitoth(32);
                    }
               }
          }
          zattck++;
     }
}

static VOID
dryads(VOID)                       /* have the dryads do something         */
{
     INT drnd;

     if ((objptr=fndlobj(&gmlocs[dloc],"dryad")) == NULL) {
          catastro("KYRANDIA ERROR: DRYAD ON LOOSE");
     }
     drnd=genrdn(12,168);
     if (drnd != dloc) {
          prfmsg(DMSG00);
          sndloc(dloc);
          dryloc=&gmlocs[dloc];
          taklobj(dryloc,objno);
          dloc=drnd;
          dryloc=&gmlocs[dloc];
          if (dryloc->nlobjs == MXLOBS) {
               prfmsg(DMSG01,dryloc->lcobjs[MXLOBS-1]->name,dryloc->objlds);
               taklobj(dryloc,MXLOBS-1);
          }
          putlobj(dryloc,&gmobjs[45]);
          prfmsg(DMSG02);
          sndloc(dloc);
     }
}

static VOID
elves(VOID)                        /* have the elves do something          */
{
     INT gold;
     INT eloc;
     static INT erand;
     static INT ehidx;
     static INT hints[10]={
          EHINT0,EHINT1,EHINT2,EHINT3,EHINT4,
          EHINT5,EHINT6,EHINT7,EHINT8,EHINT9
     };

     eloc=genrdn(12,168);
     if ((gmpptr=rndlgp(eloc)) != NULL) {
          prfmsg(EMSG00);
          sndloc(eloc);
          if (erand) {
               gold=genrdn(2,11);
               gmpptr->gold+=(SHORT)gold;
               prfmsg(EMSG01,gold);
               outprf(gmpptr->modno);
               prfmsg(EMSG02,gmpptr->altnam,gold);
               sndoth();
               erand=0;
          }
          else {
               if (ehidx > 9) {
                    ehidx=0;
               }
               prfmsg(hints[ehidx]);
               outprf(gmpptr->modno);
               prfmsg(EMSG03,gmpptr->altnam);
               sndoth();
               ehidx++;
               erand=1;
          }
          prfmsg(EMSG04);
          sndloc(eloc);
     }
}

static VOID
browns(VOID)                       /* have the brownies do something       */
{
     if (bpidx > 39) {
          bpidx=0;
     }
     bloc=bpath[bpidx];
     if ((gmpptr=rndlgp(bloc)) != NULL) {
          prfmsg(BMSG00);
          sndloc(bloc);
          if (gmpptr->gold > 0) {
               prfmsg(BMSG01);
               outprf(gmpptr->modno);
               prfmsg(BMSG02,gmpptr->altnam,himher(gmpptr));
               sndoth();
               gmpptr->gold=0;
          }
          else if (gmpptr->npobjs > 0) {
               prfmsg(BMSG03);
               outprf(gmpptr->modno);
               prfmsg(BMSG04,gmpptr->altnam);
               sndoth();
               gmpptr->npobjs=0;
          }
          else {
               prfmsg(BMSG05);
               outprf(gmpptr->modno);
               prfmsg(BMSG06,gmpptr->altnam);
               sndoth();
          }
          prfmsg(BMSG07);
          sndloc(bloc);
     }
     bpidx++;
}

static VOID
gemakr(VOID)                       /* place a gem in a random location     */
{
     INT floc;
     INT gemno;
     static INT gemctr;

     floc=genrdn(44,168);     /* forest locations */
     oglptr=&gmlocs[floc];
     if (oglptr->nlobjs < 4) {
          if (gemctr == 10) {
               gemno=genrdn(0,12);
               gemctr=0;
          }
          else {
               gemctr++;
               gemno=2;
          }
          putlobj(oglptr,&gmobjs[gemno]);
          prfmsg(GEMAPP,gmobjs[gemno].name);
          sndloc(floc);
     }
}

static VOID
zarapp(VOID)                       /* send a zar sighted warning message   */
{
     INT i;

     i=genrdn(0,168);
     prfmsg(ZARABO);
     sndloc(i);
}
