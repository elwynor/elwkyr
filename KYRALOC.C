/*****************************************************************************
 *                                                                           *
 *   KYRANDIA, Fantasy-world of Legends                     Version 7.20     *
 *                                                                           *
 *   KYRALOC.C (DYNALOC.C) - Dynamic allocation routines                     *
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
#include "kyrandia.h"

static CHAR *kgtaln(VOID);

#define LINSIZ 80

static CHAR klbuf[LINSIZ];
static CHAR *khbuf;
static FILE *klfp;

static CHAR *
kgtaln(VOID)                       /* get a line of text from a file       */
{
     CHAR *retval;

     retval=fgets(klbuf,LINSIZ,klfp);
     return(retval);
}

VOID
creatl(                            /* create location table from file      */
CHAR *locfil)
{
     INT locno;
     INT siz;
     INT i;
     INT jnk;
     INT gi_north;
     INT gi_east;
     INT gi_south;
     INT gi_west;
     INT obidx1;
     INT obidx2;
     INT obidx3;
     INT obidx4;
     INT obidx5;
     INT obidx6;

     usrnum=-1;
     if ((klfp=fopen(locfil,FOPRA)) == NULL) {
          catastro("ERROR OPENING \"%s\"",locfil);
     }
     gmlocs=(struct gamloc *)alcmem(siz=NGLOCS*sizeof(struct gamloc));
     setmem(gmlocs,siz,0);
     for (i=0 ; i < NGLOCS ; i++) {
          kgtaln();
          sscanf(&klbuf[0],"Location#: %d\n",&locno);
          if (locno >= NGLOCS || locno < 0) {
               fclose(klfp);
               catastro("LOCATION# %d OUT OF RANGE IN \"%s\"!",locno,locfil);
          }
          khbuf=kgtaln();
          khbuf+=11;
          siz=strlen(khbuf)-1;
          khbuf[siz]='\0';
          strcpy(gmlocs[locno].brfdes,khbuf);
          khbuf-=11;
          khbuf=kgtaln();
          khbuf+=11;
          siz=strlen(khbuf)-1;
          khbuf[siz]='\0';
          strcpy(gmlocs[locno].objlds,khbuf);
          khbuf-=11;
          kgtaln();
          sscanf(&klbuf[0],"# of Objs: %d\n",&jnk);
          gmlocs[locno].nlobjs=jnk;
          kgtaln();
          sscanf(&klbuf[0],"Objs' Idx: %d,%d,%d,%d,%d,%d\n",
               &obidx1,&obidx2,&obidx3,&obidx4,&obidx5,&obidx6);
          gmlocs[locno].lcobjs[0]=&gmobjs[obidx1];
          gmlocs[locno].lcobjs[1]=&gmobjs[obidx2];
          gmlocs[locno].lcobjs[2]=&gmobjs[obidx3];
          gmlocs[locno].lcobjs[3]=&gmobjs[obidx4];
          gmlocs[locno].lcobjs[4]=&gmobjs[obidx5];
          gmlocs[locno].lcobjs[5]=&gmobjs[obidx6];
          kgtaln();
          sscanf(&klbuf[0],"N:%d S:%d E:%d W:%d\n",
               &gi_north,&gi_south,&gi_east,&gi_west);
          gmlocs[locno].gi_north=gi_north;
          gmlocs[locno].gi_south=gi_south;
          gmlocs[locno].gi_east=gi_east;
          gmlocs[locno].gi_west=gi_west;
          kgtaln();
     }
     fclose(klfp);
}
