/*****************************************************************************
 *                                                                           *
 *   KYRANDIA, Fantasy-world of Legends                     Version 7.20     *
 *                                                                           *
 *   KYROBJS.C (GMOBJS.C) - Game objects                                     *
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

static VOID k_nulrou(VOID);

static VOID
k_nulrou(VOID)
{
}

struct gamobj gmobjs[NGOBJS]={
/* 000 */ {"ruby",KID000,KID000,
          VISIBL+PICKUP,
          k_nulrou},
/* 001 */ {"emerald",KID001,KID001,
          VISIBL+PICKUP+NEEDAN,
          k_nulrou},
/* 002 */ {"garnet",KID002,KID002,
          VISIBL+PICKUP,
          k_nulrou},
/* 003 */ {"pearl",KID003,KID003,
          VISIBL+PICKUP,
          k_nulrou},
/* 004 */ {"aquamarine",KID004,KID004,
          VISIBL+PICKUP+NEEDAN,
          k_nulrou},
/* 005 */ {"moonstone",KID005,KID005,
          VISIBL+PICKUP,
          k_nulrou},
/* 006 */ {"sapphire",KID006,KID006,
          VISIBL+PICKUP,
          k_nulrou},
/* 007 */ {"diamond",KID007,KID007,
          VISIBL+PICKUP,
          k_nulrou},
/* 008 */ {"amethyst",KID008,KID008,
          VISIBL+PICKUP+NEEDAN,
          k_nulrou},
/* 009 */ {"onyx",KID009,KID009,
          VISIBL+PICKUP+NEEDAN,
          k_nulrou},
/* 010 */ {"opal",KID010,KID010,
          VISIBL+PICKUP+NEEDAN,
          k_nulrou},
/* 011 */ {"bloodstone",KID011,KID011,
          VISIBL+PICKUP,
          k_nulrou},
/* 012 */ {"elixir",KID012,KID012,
          VISIBL+PICKUP+NEEDAN+DRIABL,
          k_nulrou},
/* 013 */ {"staff",KID013,KID013,
          VISIBL+PICKUP,
          k_nulrou},
/* 014 */ {"key",KID014,KID014,
          VISIBL+PICKUP,
          k_nulrou},
/* 015 */ {"locket",KID015,KID015,
          VISIBL+PICKUP,
          k_nulrou},
/* 016 */ {"amulet",KID016,KID016,
          VISIBL+PICKUP+NEEDAN,
          k_nulrou},
/* 017 */ {"pendant",KID017,KID017,
          VISIBL+PICKUP,
          k_nulrou},
/* 018 */ {"charm",KID018,KID018,
          VISIBL+PICKUP,
          k_nulrou},
/* 019 */ {"bracelet",KID019,KID019,
          VISIBL+PICKUP,
          k_nulrou},
/* 020 */ {"coronet",KID020,KID020,
          VISIBL+PICKUP,
          k_nulrou},
/* 021 */ {"tiara",KID021,KID021,
          VISIBL+PICKUP,
          k_nulrou},
/* 022 */ {"necklace",KID022,KID022,
          VISIBL+PICKUP,
          k_nulrou},
/* 023 */ {"broach",KID023,KID023,
          VISIBL+PICKUP,
          k_nulrou},
/* 024 */ {"sceptre",KID024,KID024,
          VISIBL+PICKUP,
          k_nulrou},
/* 025 */ {"rod",KID025,KID025,
          VISIBL+PICKUP,
          k_nulrou},
/* 026 */ {"wand",KID026,KID026,
          VISIBL+PICKUP,
          k_nulrou},
/* 027 */ {"trinket",KID027,KID027,
          VISIBL+PICKUP,
          k_nulrou},
/* 028 */ {"soulstone",KID028,KID028,
          VISIBL+PICKUP,
          k_nulrou},
/* 029 */ {"kyragem",KID029,KID029,
          VISIBL+PICKUP,
          k_nulrou},
/* 030 */ {"dragonstaff",KID030,KID030,
          VISIBL+PICKUP+RUBABL,
          zaritm},
/* 031 */ {"potion",KID031,KID031,
          VISIBL+PICKUP+DRIABL,
          k_nulrou},
/* 032 */ {"pinecone",KID032,KID032,
          VISIBL+PICKUP,
          k_nulrou},
/* 033 */ {"dagger",KID033,KID033,
          VISIBL+PICKUP,
          k_nulrou},
/* 034 */ {"sword",KID034,KID034,
          VISIBL+PICKUP,
          k_nulrou},
/* 035 */ {"scroll",KID035,KID035,
          VISIBL+PICKUP+REDABL,
          k_nulrou},
/* 036 */ {"codex",KID036,KID036,
          VISIBL+PICKUP+REDABL,
          k_nulrou},
/* 037 */ {"tome",KID037,KID037,
          VISIBL+PICKUP+REDABL,
          k_nulrou},
/* 038 */ {"parchment",KID038,KID038,
          VISIBL+PICKUP+REDABL,
          k_nulrou},
/* 039 */ {"ring",KID039,KID039,
          VISIBL+PICKUP,
          k_nulrou},
/* 040 */ {"rose",KID040,KID040,
          VISIBL+PICKUP,
          k_nulrou},
/* 041 */ {"lilac",KID041,KID041,
          VISIBL+PICKUP,
          k_nulrou},
/* 042 */ {"orchid",KID042,KID042,
          VISIBL+PICKUP+NEEDAN,
          k_nulrou},
/* 043 */ {"shard",KID043,KID043,
          VISIBL+PICKUP,
          k_nulrou},
/* 044 */ {"tulip",KID044,KID044,
          VISIBL+PICKUP,
          k_nulrou},
/* 045 */ {"dryad",KID045,AID045,
          0,
          k_nulrou},
/* 046 */ {"tree",KID046,AID046,         /* willow tree */
          0,
          k_nulrou},
/* 047 */ {"altar",KID047,AID047,        /* altar in temple */
          0,
          k_nulrou},
/* 048 */ {"sign",KID048,AID048,         /* sign at spell shop */
          0,
          k_nulrou},
/* 049 */ {"statue",KID049,AID049,       /* statue in forest */
          0,
          k_nulrou},
/* 050 */ {"shrine",KID050,AID050,       /* hidden shrine in forest */
          0,
          k_nulrou},
/* 051 */ {"machine",KID051,AID051,      /* slot machine in dark cave */
          0,
          k_nulrou},
/* 052 */ {"dragon",KID052,AID052,       /* Zar the Magic Dragon */
          0,
          k_nulrou},
/* 053 */ {"altar",KID053,AID053,        /* altar in chamber of life */
          0,
          k_nulrou}
}, *objptr;
