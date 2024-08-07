/*****************************************************************************
 *                                                                           *
 *   KYRANDIA, Fantasy-world of Legends                     Version 7.20     *
 *                                                                           *
 *   KYRSYSP.C (KSYSOP.C) - Sysop Editor for KYRANDIA User File              *
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
#include "kyrspls.h"
#undef LEVEL6
#include "elwkyrs.h"
#undef LEVEL6
#include "elwkyrm.h"

static VOID kyrawho(VOID);
static VOID kyramnu(VOID);
static VOID kyrdsp(VOID);
static VOID kyrchg(VOID);
static VOID instchg(CHAR *,CHAR *,LONG);
static VOID gi_kyrspl(VOID);
static CHAR kyryn(INT);
static VOID chgspl(INT);
static VOID kyrsav(VOID);
static VOID beusr(INT);
static VOID injax(VOID);
static VOID kpmt(INT);

INT kinuse,kyrasub,grp;

static CHAR uid[UIDSIZ];

VOID
kyraedit(VOID)                     /* Main Entry for Kyrandia Editor       */
{
     INT i;
     INT j;

     setmbk(ksmb);
     switch (kyrasub) {
     case 0:
          kyrply=(struct gmplyr *)alcmem(sizeof(struct gmplyr));
          kpmt(KYREDT);
          btumil(usrnum,UIDSIZ-1);
          usrptr->substt=90;
          kinuse=1;
          return;
     case KYREDT:
          kyrawho();
          break;
     case KYRMNU:
          kyramnu();
          break;
     case CHGWCH:
          kyrchg();
          break;
     case EDT001:
          if (!margc) {
               kyrdsp();
          }
          else if ((i=atoi(margv[0])) < 1 || i > 5) {
               prfmsg(BADCHO);
               prfmsg(EDT001);
          }
          else {
               switch (i) {
               case 1:
                    instchg(kyrply->plyrid,kyrply->plyrid,0);
                    break;
               case 2:
                    instchg("Some Unseen Force","Unseen Force",INVISF);
                    break;
               case 3:
                    instchg("Some pegasus","pegasus",PEGASU);
                    break;
               case 4:
                    instchg("Some psuedo dragon","psuedo dragon",PDRAGN);
                    break;
               case 5:
                    instchg("Some willowisp","willowisp",WILLOW);
                    break;
               }
          }
          break;
     case EDT002:
          if (!margc) {
               kyrdsp();
          }
          else if ((i=atoi(margv[0])) < 1 || i > 25) {
               prfmsg(BADCHO);
               prfmsg(EDT002);
          }
          else {
               kyrply->level=(SHORT)i;
               if (kyrply->flags&FEMALE) {
                    kyrply->nmpdes=FDES00+(SHORT)i-1;
               }
               else {
                    kyrply->nmpdes=MDES00+(SHORT)i-1;
               }
               kyrply->hitpts=4*kyrply->level;
               kyrply->spts=2*kyrply->level;
               if (i < 9) {
                    kyrply->flags&=~GOTKYG;
               }
               kyrdsp();
          }
          break;
     case EDT003:
          if (!margc) {
               kyrdsp();
          }
          else if ((i=atoi(margv[0])) < 0 || i > 304) {
               prfmsg(BADCHO);
               prfmsg(EDT003);
          }
          else {
               kyrply->pgploc=(SHORT)i;
               kyrdsp();
          }
          break;
     case EDT004:
          if (!margc) {
               kyrdsp();
          }
          else if ((i=(SHORT)atoi(margv[0])) < 1 || i > 32766) {
               prfmsg(BADCHO);
               prfmsg(EDT004);
          }
          else {
               kyrply->gold=(USHORT)i;
               kyrdsp();
          }
          break;
     case EDT005:
          if (!margc) {
               kyrdsp();
          }
          else if ((i=atoi(margv[0])) < 1 || i > 50) {
               prfmsg(BADCHO);
               prfmsg(EDT005);
          }
          else {
               kyrply->spts=(i > (kyrply->level*2) ? kyrply->level*2 : (SHORT)i);
               kyrdsp();
          }
          break;
     case EDT006:
          if (!margc) {
               kyrdsp();
          }
          else if ((i=atoi(margv[0])) < 1 || i > 99) {
               prfmsg(BADCHO);
               prfmsg(EDT006);
          }
          else {
               kyrply->hitpts=(i > (kyrply->level*4) ? kyrply->level*4 : (SHORT)i);
               kyrdsp();
          }
          break;
     case EDT007:
          if (!margc) {
               kyrdsp();
          }
          else if (toupper(*margv[0]) == 'X') {
               kyrply->spouse[0]='\0';
               kyrply->flags&=~MARRYD;
               kyrdsp();
          }
          else {
               makhdl(input);
               setmem(kyrply->spouse,sizeof(UIDSIZ),0);
               movmem(input,kyrply->spouse,UIDSIZ);
               kyrply->flags|=MARRYD;
               kyrdsp();
          }
          break;
     case EDT008:
          if (!margc) {
               kyrdsp();
          }
          else if ((i=atoi(margv[0])) < 0 || i > 6) {
               prfmsg(BADCHO);
               prfmsg(EDT008);
          }
          else {
               if (kyrply->npobjs < i) {
                    for (j=kyrply->npobjs ; j < i ; j++) {
                         kyrply->gpobjs[j]=&gmobjs[2];
                    }
               }
               else {
                    for (j=i ; j < MXPOBS ; j++) {
                         kyrply->gpobjs[j]=NULL;
                    }
               }
               kyrply->npobjs=(SHORT)i;
               kyrdsp();
          }
          break;
     case EDT009:
          gi_kyrspl();
          kpmt(MODSPL);
          break;
     case EDT010:
     case EDT011:
     case EDT012:
     case EDT013:
     case EDT014:
     case EDT015:
          if (!margc) {
               kyrdsp();
          }
          else if ((i=atoi(margv[0])) < 1 || i > 240) {
               prfmsg(BADCHO);
               prfmsg(kyrasub);
          }
          else {
               kyrply->charms[grp]=(SHORT)i;
               kyrdsp();
          }
          break;
     case EDT016:
     case EDT017:
     case EDT018:
     case EDT019:
     case EDT020:
     case EDT021:
          if (!margc) {
               kyrdsp();
          }
          else {
               j=0;
               for (objptr=gmobjs ; objptr < gmobjs+45 ; objptr++) {
                    if (sameto(margv[0],objptr->name)) {
                         j=1;
                         kyrply->gpobjs[grp]=objptr;
                         kyrdsp();
                         break;
                    }
               }
               if (!j) {
                    prfmsg(NOSOBJ);
                    prfmsg(kyrasub);
               }
          }
          break;
     case EDT022:
          if (!margc) {
               kyrdsp();
          }
          else if ((i=atoi(margv[0])) < 0 || i > 4) {
               prfmsg(BADCHO);
               prfmsg(kyrasub);
          }
          else {
               kyrply->gemidx=(SHORT)i;
               kyrdsp();
          }
          break;
     case EDT023:
          if (!margc) {
               kyrdsp();
          }
          else if ((i=atoi(margv[0])) < 0 || i > 12) {
               prfmsg(BADCHO);
               prfmsg(kyrasub);
          }
          else {
               kyrply->stumpi=(SHORT)i;
               kyrdsp();
          }
          break;
     case MODSPL:
          if (!margc) {
               prfmsg(MODSPL);
          }
          else if (sameas(margv[0],"?")) {
               gi_kyrspl();
               prfmsg(MODSPL);
          }
          else if (sameas(margv[0],"x")) {
               kyrdsp();
          }
          else if ((i=atoi(margv[0])) < 1 || i > 67) {
               prfmsg(BADCHO);
               prfmsg(MODSPL);
          }
          else {
               chgspl(i);
               prfmsg(MODSPL);
          }
          break;
     }
     outprf(usrnum);
}

static VOID
kyrawho(VOID)                      /* Select User to Edit or Exit to game  */
{
     if (!margc) {
          prfmsg(KYREDT);
     }
     else if (sameas(margv[0],"x")) {
          free(kyrply);
          btupmt(usrnum,'>');
          btuxmt(usrnum,kyratr);
          entrgp(gmpptr->pgploc,gmpptr,"flown down from the heavens on a golden chariot");
          usrptr->substt=7;
          kinuse=kyrasub=0;
          btumil(usrnum,DFTIMX);
          prf("");
     }
     else {
          rstrin();
          makhdl(input);
          movmem(input,uid,UIDSIZ);
          if (sameas(uid,usaptr->userid)) {
               movmem(gmpptr,kyrply,sizeof(struct gmplyr));
               kpmt(KYRMNU);
               btumil(usrnum,DFTIMX);
          }
          else {
               dfaSetBlk(kbb);
               if (dfaAcqEQ(kyrply,uid,0)) {
                    gi_rest4p(kyrply);
                    kpmt(KYRMNU);
                    btumil(usrnum,DFTIMX);

               }
               else {
                    prfmsg(NOSUCH);
                    prfmsg(KYREDT);
               }
          }
     }
}

static VOID
kyramnu(VOID)                      /* Do what to the user selected?        */
{
     if (!margc) {
          kpmt(KYRMNU);
     }
     else {
          switch (toupper(*margv[0])) {
          case 'E':
               kyrdsp();
               break;
          case 'X':
               kyrsav();
               kpmt(KYREDT);
               break;
          case 'A':
               kpmt(KYREDT);
               setmem(kyrply,sizeof(struct gmplyr),0);
               break;
          case '?':
               prfmsg(KYRMNU,kyrply->plyrid);
               break;
          default:
               prfmsg(BADCHO);
               prfmsg(KYRMNU,kyrply->plyrid);
          }
     }
}

static VOID
kyrdsp(VOID)                       /* Display the users account info       */
{
     INT i;

     prfmsg(KYRAC1,kyrply->plyrid,kyrply->altnam,kyrply->attnam,
                   kyrply->level,kyrply->pgploc,gmlocs[kyrply->pgploc].brfdes,
                   kyrply->gold,kyrply->spts,kyrply->hitpts,
                   (kyrply->spouse[0] == '\0' ? "<None Yet>" : kyrply->spouse),
                   kyrply->npobjs);
     prfmsg(KYRAC2,kyrply->charms[0],kyrply->charms[1],kyrply->charms[2],
                   kyrply->charms[3],kyrply->charms[4],kyrply->charms[5]);
     for (i=0 ; i < 6 ; i++) {
          prfmsg(OBJLST,i+16,
                (i < kyrply->npobjs ? kyrply->gpobjs[i]->name : "---------"));
          if (i == 2 || i == 5) {
               prf("\r");
          }
     }
     prfmsg(KYRAC3,kyrply->gemidx,
             gmobjs[kyrply->stones[0]].name,gmobjs[kyrply->stones[1]].name,
             gmobjs[kyrply->stones[2]].name,gmobjs[kyrply->stones[3]].name,
             kyrply->stumpi);
     kpmt(CHGWCH);
}

static VOID
kyrchg(VOID)                       /* Change what aspect of the account    */
{
     INT i;

     if (!margc) {
          prfmsg(CHGWCH);
     }
     else if (sameas(margv[0],"x")) {
          kpmt(KYRMNU);
     }
     else if (sameas(margv[0],"?")) {
          kyrdsp();
     }
     else if ((i=atoi(margv[0])) < 1 || i > 23) {
          prfmsg(BADCHO);
          prfmsg(CHGWCH);
     }
     else if (i == 9) {
          gi_kyrspl();
          kpmt(MODSPL);
     }
     else {
          kpmt(EDT001+i-1);
          if (i > 9 && i < 16) {
               grp=i-10;
          }
          if (i > 15 && i < 22) {
               grp=i-16;
          }
     }
}

static VOID
instchg(                           /* Change the users alternate names     */
CHAR *altnam,
CHAR *attnam,
LONG flag)
{
     strcpy(kyrply->altnam,altnam);
     strcpy(kyrply->attnam,attnam);
     kyrply->flags&=~(INVISF+PEGASU+WILLOW+PDRAGN);
     if (flag) {
          kyrply->flags|=flag;
          if (kyrply->charms[ALTNAM] == 0) {
               kyrply->charms[ALTNAM]=4;
          }
     }
     else {
          kyrply->charms[ALTNAM]=0;
     }
     kyrdsp();
}

static VOID
gi_kyrspl(VOID)                    /* Display the spells the user has      */
{
     INT i;
     INT j;
     INT k=1;

     prf("\r");
     for (i=0 ; i < 13 ; i++) {
          for (j=0 ; j < 5 ; j++,k++) {
               prfmsg(SPLLST,k,spells[k-1].name,kyryn(k-1));
          }
     }
     for (j=0 ; j < 2 ; j++,k++) {
          prfmsg(SPLLST,k,spells[k-1].name,kyryn(k-1));
     }
     prf("\r");
     prfmsg(KSPLS0);
}

static CHAR
kyryn(                             /* Display a Y or N for a spell         */
INT i)
{
     CHAR retval;

     switch (spells[i].sbkref) {
     case 1:
          if (kyrply->offspls&(spells[i].bitdef)) {
               retval='Y';
          }
          else {
               retval='N';
          }
          break;
     case 2:
          if (kyrply->defspls&(spells[i].bitdef)) {
               retval='Y';
          }
          else {
               retval='N';
          }
          break;
     case 3:
          if (kyrply->othspls&(spells[i].bitdef)) {
               retval='Y';
          }
          else {
               retval='N';
          }
          break;
     default:
         retval = ' '; // this is an error condition!
     }
     return(retval);
}

static VOID
chgspl(                            /* Change the flags on a spell          */
INT num)
{
     num--;
     splptr=&spells[num];
     switch (splptr->sbkref) {
     case 1:
          if (kyrply->offspls&(splptr->bitdef)) {
               kyrply->offspls&=~(splptr->bitdef);
          }
          else {
               kyrply->offspls|=(splptr->bitdef);
          }
          break;
     case 2:
          if (kyrply->defspls&(splptr->bitdef)) {
               kyrply->defspls&=~(splptr->bitdef);
          }
          else {
               kyrply->defspls|=(splptr->bitdef);
          }
          break;
     case 3:
          if (kyrply->othspls&(splptr->bitdef)) {
               kyrply->othspls&=~(splptr->bitdef);
          }
          else {
               kyrply->othspls|=(splptr->bitdef);
          }
          break;
     }
}

static VOID
kyrsav(VOID)                       /* Save changes back to the account     */
{
     INT hldusn;

     dfaSetBlk(kbb);
     if (!onsysn(kyrply->uidnam,1) || !(gmparr[othusn].flags&LOADED)) {
          if (dfaAcqEQ(NULL,kyrply->uidnam,0)) {
               gi_prep4d(kyrply);
               dfaUpdate(kyrply);
               prfmsg(RECUPD);
          }
          else {
               prfmsg(RECNPD);
          }
     }
     else {
          hldusn=usrnum;
          beusr(othusn);
          if (usrptr->state == kyrstt && usrptr->substt == 7) {
               injax();
          }
          movmem(kyrply,gmpptr,sizeof(struct gmplyr));
          if (dfaAcqEQ(NULL,kyrply->uidnam,0)) {
               gi_prep4d(kyrply);
               dfaUpdate(kyrply);
          }
          beusr(hldusn);
          setmbk(ksmb);
          prfmsg(RECUPD);
     }
     setmem(kyrply,sizeof(struct gmplyr),0);
}

static VOID
beusr(                             /* act as a usrnum for a minute         */
INT usn)
{
     curusr(usn);
     gmpptr=&gmparr[usrnum];
}

static VOID
injax(VOID)                        /* inject an 'X' to current channel     */
{                                  /*    (re-prompt current text)          */
     usrptr->flags|=INJOIP;
     status=CRSTG;
     clrinp();
     strcpy(input,"x");
     parsin();
     hdlinp();
     usrptr->flags&=~INJOIP;
}

static VOID
kpmt(                              /* Print generic prompts and set substt */
INT news)
{
     switch (kyrasub=news) {
     case KYRMNU:
          prfmsg(news,uid);
          break;
     default:
          prfmsg(news);
     }
}
