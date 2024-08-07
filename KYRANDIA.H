/*****************************************************************************
 *                                                                           *
 *  KYRANDIA, Fantasy-world of Legends                     Version 7.20      *
 *                                                                           *
 *  KYRANDIA.H (K.H) - game structures, definitions, and declarations        *
 *                                                                           *
 *  Designed/Programmed by: Scott Brinker & Richard Skurnick   02/23/88      *
 *                                                                           *
 *                                     6.0 Conversion - E. Bush 3/12/92      *
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

#include "bbsutils.h"
#include "gamutils.h"

 // This is from V10, backporting it into WG32 build here
#ifndef CHAR_BUFFER
#define CHAR_BUFFER(name, size, lit)     CHAR name[size] = lit
#endif 

#define ansmsg(msgno) ((usaptr->ansifl&ANSON) ? msgno+1 : msgno)

#define OFFENS 1
#define DEFENS 2
#define OTHERS 3

#define APNSIZ 20        /* maximum size of alternate name for players     */
#define MXPOBS 6         /* maximum number of objects held by a player     */
#define MAXSPL 10        /* maximum number of spells memorized by player   */
#define NCHARM 6         /* number of "charm" timer-related stuff          */
#define NGSPLS 67        /* number of spells in wizards' spell array       */
#define NGOBJS 54        /* number of objects in game array                */

#define ALSSIZ 10        /* size of alias name for within game             */

#define CINVIS 0
#define FIRPRO 1
#define ICEPRO 2
#define LIGPRO 3
#define OBJPRO 4
#define ALTNAM 5

#define ZARHOM  302           /* Zar's "home" location number              */
#define BITE    0             /* Zar's next attack will be to bite player  */
#define BREATH  1             /* Zar's next attack will be to breath on gp */
#define CLAW    2             /* Zar's next attack will be to claw player  */
#define LIGHTN  3             /* Zar's next attack will be to lightning gp */

#define LOADED 0x00000001L    /* game record has been loaded into memory   */
#define FEMALE 0x00000002L    /* player is female in the game              */
#define INVISF 0x00000004L    /* player is invisible                       */
#define BRFSTF 0x00000008L
#define MARRYD 0x00000010L
#define PEGASU 0x00000020L
#define WILLOW 0x00000040L
#define GOTKYG 0x00000080L
#define PDRAGN 0x00000100L
#define BLESSD 0x00000200L

#define NEEDAN 0x0001    /* requires "an" instead of "a" flag              */
#define VISIBL 0x0002
#define PICKUP 0x0004
#define REDABL 0x0008
#define AIMABL 0x0010
#define THIABL 0x0020
#define RUBABL 0x0040
#define DRIABL 0x0080

#define NGLOCS 305       /* number of locations in game array              */
#define MXLOBS 6         /* maximum number of objects at a location        */

extern struct spell {         /* game spell/prayer structure definition    */
     CHAR name[10];           /*   spell/prayer's name/invocation          */
     VOID (*splrou)(VOID);    /*   routine invoked when spell is cast      */
     INT sbkref;
     LONG bitdef;
     INT level;               /*   level required of player to cast spell  */
} spells[NGSPLS],             /* general purpose pointer for spells        */
   *splptr;

extern struct gmplyr {        /* game player structure definition          */
     CHAR uidnam[UIDSIZ];     /*   player's name from User-ID              */
     CHAR plyrid[ALSSIZ];     /*   player's alias name within the game     */
     CHAR altnam[APNSIZ];     /*   player's alternate game name            */
     CHAR attnam[APNSIZ];     /*   player's attackable name                */
     struct gamobj *gpobjs[MXPOBS];/* array of player's objects            */
     SHORT nmpdes;            /*   player's description                    */
     SHORT modno;             /*   player's BREAKTHROUGH modem channel no. */
     SHORT level;             /*   player's experience "level"             */
     SHORT gamloc;            /*   player's current game location number   */
     SHORT pgploc;            /*   player's permanant game location        */
     LONG flags;              /*   player's gaming bit flags               */
     USHORT gold;             /*   number of gold pieces held by player    */
     SHORT npobjs;            /*   number of objects held by player        */
     SHORT obvals[MXPOBS];    /*   array of player's objects' values       */
     SHORT nspells;           /*   number of spells currently memorized    */
     SHORT spts;              /*   number of spell points available        */
     SHORT hitpts;            /*   player's "hit point" count              */
     SHORT charms[NCHARM];    /*   array of timer-related stuff (pros,invs)*/
     LONG offspls;            /*   spellbook's offensive spell bit flags   */
     LONG defspls;            /*   spellbook's defensive spell bit flags   */
     LONG othspls;            /*   spellbook's "other" spell bit flags     */
     struct spell *spells[MAXSPL];/* array of spells currently memorized    */
     SHORT gemidx;
     SHORT stones[4];         /*   player's four birthstones               */
     SHORT macros;
     SHORT stumpi;
     CHAR spouse[ALSSIZ];
} *gmparr,                    /* dynamically allocated player array        */
  *gmpptr,                    /* general purpose game player pointer       */
  *ogmptr,                    /* second general purpose game player ptr.   */
  *kyrply;                    /* general purpose pointer for player editor */

extern struct gamloc {        /* game location structure definition        */
     CHAR brfdes[40];         /*   location's brief text description       */
     CHAR objlds[30];
     INT nlobjs;              /*   number of objects at location           */
     struct gamobj *lcobjs[MXLOBS];/* array of objects at location         */
     INT gi_north;            /*   location number to the north            */
     INT gi_south;            /*   location number to the south            */
     INT gi_east;             /*   location number to the east             */
     INT gi_west;             /*   location number to the west             */
} *gmlocs,                    /* dynamically allocated locations array     */
  *gmlptr,                    /* current player's location pointer         */
  *oglptr;                    /* general purpose location pointer          */

extern struct glcrou {        /* game location routine structure definition*/
     INT londes;
     GBOOL (*locrou)(VOID);   /*   location's specific routine handler     */
} lcrous[NGLOCS],             /* array of location routines (not dynamic)  */
  *lcrptr;                    /* current player's location routine pointer */

extern struct gamobj {        /* game object structure definition          */
     CHAR *name;              /*   object's name                           */
     INT objdes;              /*   object's description message number     */
     INT auxmsg;              /*   object's auxillary message number       */
     INT flags;               /*   object's bit "flags"                    */
     VOID (*objrou)(VOID);    /*   object's routine                        */
} gmobjs[NGOBJS],             /* array of game objects (not dynamic)       */
  *objptr;                    /* general purpose object pointer            */

struct cmdwrd {               /* command word structure definition         */ /* rick: removed extern for vs2019 warning 4/18/2023 */
     CHAR *command;           /*   command word                            */
     VOID (*cmdrou)(VOID);    /*   command's invoked routine               */
     INT payonl;              /*   for paying users only flag              */
};

extern struct binwrd {        /* command structure for bincmp()'s          */
     CHAR *word;              /*   word                                    */
     INT (*wrdrou)(VOID);     /*   word's specific invoked routine         */
} *wrdptr;                    /* general purpose bincmp() word pointer     */

extern INT objno;             /* used for an object's array position            */
extern INT objno2;            /* another object array position holder           */

extern INT givrcrd;           /* give system credits for game gold         */

extern CHAR *titles[26];      /* titles for player levels                  */

extern INT zloc;
extern INT dloc;
extern INT kyrasub;
extern INT chantd;
extern INT rockpr;
extern INT sesame;
extern INT kinuse;
extern INT kyrstt;

extern CHAR gamver[];

extern CHAR *kyratr;          /* attribute for displayed Kyrandia text          */

extern HMCVFILE kmb;
extern HMCVFILE klmb;
extern HMCVFILE ksmb;

extern DFAFILE *kbb;

/* KYRANDIA.C 12/03/92 16.07.16 */
VOID EXPORT init__galkyr(VOID);
GBOOL kyloin(VOID);
GBOOL kyrand(VOID);
VOID initgp(struct gmplyr *,CHAR *);
VOID kyhup(VOID);
VOID kydela(CHAR *);
VOID kysdn(VOID);

/* KYRALOC.C 12/03/92 14.15.00 */
VOID creatl(CHAR *);

/* KYRANIM.C 12/03/92 14.27.46 */
VOID inianm(VOID);
VOID animat(VOID);
VOID chkzar(VOID);
VOID zaritm(VOID);

/* KYRCMDS.C 12/03/92 14.41.50 */
VOID gi_north(VOID);
VOID gi_south(VOID);
VOID gi_east(VOID);
VOID gi_west(VOID);
VOID kyra(VOID);

/* KYRLOWR.C 12/03/92 14.56.34 */
VOID lowright(CHAR *);

/* KYROBJR.C 12/03/92 14.58.42 */
VOID youmsg(INT);
VOID rubber(VOID);
VOID thinkr(VOID);
VOID aimer(VOID);
VOID drinkr(VOID);

/* KYRPROT.C 12/03/92 15.08.38 */
INT loadkp(VOID);
VOID rights(VOID);
VOID gi_prep4d(struct gmplyr *);
VOID gi_rest4p(struct gmplyr *);

/* KYRROUS.C 12/03/92 15.31.36 */
GBOOL willow(VOID);
GBOOL getgol(VOID);
GBOOL buyspl(VOID);
GBOOL temple(VOID);
GBOOL vhealr(VOID);
GBOOL gquest(VOID);
GBOOL terrac(VOID);
GBOOL waterf(VOID);
GBOOL gpcone(VOID);
GBOOL stumpr(VOID);
GBOOL silver(VOID);
GBOOL rubies(VOID);
GBOOL druids(VOID);
GBOOL fthick(VOID);
GBOOL fearno(VOID);
GBOOL swrock(VOID);
GBOOL ashtre(VOID);
GBOOL spring(VOID);
GBOOL rosutl(VOID);
GBOOL magicf(VOID);
GBOOL hnsrou(VOID);
GBOOL tashas(VOID);
GBOOL refpoo(VOID);
GBOOL panthe(VOID);
GBOOL portal(VOID);
GBOOL waller(VOID);
GBOOL slotma(VOID);
GBOOL mistyr(VOID);
GBOOL sanman(VOID);
GBOOL tulips(VOID);
GBOOL crystt(VOID);
GBOOL rainbo(VOID);
GBOOL sunshi(VOID);
GBOOL demong(VOID);
GBOOL bodyma(VOID);
GBOOL mindma(VOID);
GBOOL heartm(VOID);
GBOOL soulma(VOID);
GBOOL devote(VOID);
GBOOL truthy(VOID);
GBOOL fouris(VOID);
GBOOL singer(VOID);
GBOOL forgtr(VOID);
GBOOL oflove(VOID);
GBOOL believ(VOID);
GBOOL philos(VOID);
GBOOL fanbel(VOID);
GBOOL wingam(VOID);

/* KYRSPEL.C 12/03/92 15.48.04 */
VOID insrtk(VOID);
VOID splrtk(VOID);
VOID hitoth(INT);
VOID msgutl2(INT,INT);
VOID shwpsp(VOID);
VOID seesbk(VOID);
VOID memori(VOID);
VOID caster(VOID);

/* KYRSYSP.C 12/03/92 15.53.24 */
VOID kyraedit(VOID);

/* KYRUTIL.C 12/03/92 15.58.54 */
VOID iniutl(VOID);
CHAR *himher(struct gmplyr *);
CHAR *kheshe(struct gmplyr *);
CHAR *hisher(struct gmplyr *);
GBOOL ckinvs(struct gmplyr *);
VOID sndoth(VOID);
VOID sndutl(const char *);
VOID sndbt2(VOID);
VOID sndcgp(struct gmplyr *);
VOID sndloc(INT);
VOID sndnear(VOID);
VOID sndgam(VOID);
VOID remvgp(struct gmplyr *,CHAR *);
VOID entrgp(INT,struct gmplyr *,CHAR *);
VOID locobjs(INT);
VOID gi_invrou(VOID);
VOID gi_invutl(struct gmplyr *,INT);
CHAR *dobutl(struct gamobj *);
VOID locogps(struct gmplyr *);
INT ngpscn(struct gmplyr *);
INT ngpslc(INT);
GBOOL findgp(CHAR *);
GBOOL fgamgp(CHAR *);
GBOOL chkobj(struct gamobj *);
struct gamobj *fndpobj(struct gmplyr *,CHAR *);
struct gamobj *fgmpobj(CHAR *);
struct gamobj *fndlobj(struct gamloc *,CHAR *);
struct gamobj *fgmlobj(CHAR *);
VOID takpobj(struct gmplyr *,INT);
VOID tgmpobj(INT);
VOID taklobj(struct gamloc *,INT);
VOID tgmlobj(INT);
VOID putpobj(struct gmplyr *,struct gamobj *,INT);
VOID pgmpobj(struct gamobj *,INT);
VOID putlobj(struct gamloc *,struct gamobj *);
VOID pgmlobj(struct gamobj *);
CHAR *upperc(CHAR *);
struct binwrd *binchk(CHAR *,struct binwrd [],INT);
