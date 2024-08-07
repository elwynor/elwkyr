/*****************************************************************************
 *                                                                           *
 *   GAMUTILS.C                                                              *
 *                                                                           *
 *   Shared text adventure utility routines.                                 *
 *                                                                           *
 *                                            - S. Brinker 2/28/90           *
 *                            6.x Conversion  - E. Bush 3/12/92              *
 *                        Worldgroup 3.2 Conversion - R. Hadsall 4/24/2021   *
 *                          Major BBS 10 Conversion - R. Hadsall 4/18/2023   *
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

VOID
gi_bagthe(VOID)
{
     INT i;

     for (i=0 ; i < margc-1 ; i++) {
          if (sameas(margv[i],"the")
           || sameas(margv[i],"a")
           || sameas(margv[i],"an")) {
               *margn[i]=' ';
               margc--;
               movmem(&margv[i+1],&margv[i],(margc-i)*sizeof(CHAR *));
               movmem(&margn[i+1],&margn[i],(margc-i)*sizeof(CHAR *));
          }
     }
}

VOID
bagprep(VOID)
{
     INT i;

     for (i=0 ; i < margc-1 ; i++) {
          if (sameas(margv[i],"at")
           || sameas(margv[i],"to")
           || sameas(margv[i],"into")
           || sameas(margv[i],"through")
           || sameas(margv[i],"in")) {
               *margn[i]=' ';
               margc--;
               movmem(&margv[i+1],&margv[i],(margc-i)*sizeof(CHAR *));
               movmem(&margn[i+1],&margn[i],(margc-i)*sizeof(CHAR *));
          }
     }
}

VOID
bagwrd(
CHAR *word)
{
     INT i;

     for (i=0 ; i < margc-1 ; i++) {
          if (sameas(margv[i],word)) {
               *margn[i]=' ';
               margc--;
               movmem(&margv[i+1],&margv[i],(margc-i)*sizeof(CHAR *));
               movmem(&margn[i+1],&margn[i],(margc-i)*sizeof(CHAR *));
          }
     }
}

GBOOL
gi_nulrou(VOID)
{
     return(TRUE);
}

UINT
txt_rnd(VOID)
{
     static UINT seed=3974;

     return((seed=(UINT)((seed*62891L+871L))&0x7FFF));
}

VOID
fixmargc(VOID)                     /* Prevents GP's with invalid margv[x]  */
{
     strcpy(input,"A B C D E F G H I J K L M N O P Q R S T U V W X Y Z");
     parsin();
}
