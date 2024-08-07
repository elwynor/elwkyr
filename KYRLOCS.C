/*****************************************************************************
 *                                                                           *
 *   KYRANDIA, Fantasy-world of Legends                     Version 7.20     *
 *                                                                           *
 *   KYRLOCS.C (LCRARR.C) - Array of room LONG desc. and routine vector      *
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
#include "elwkyrm.h"
#undef LEVEL6
#include "elwkyrl.h"


struct glcrou lcrous[NGLOCS]={
     {KRD000,willow},
     {KRD001,gi_nulrou},
     {KRD002,gi_nulrou},
     {KRD003,gi_nulrou},
     {KRD004,gi_nulrou},
     {KRD005,gi_nulrou},
     {KRD006,gi_nulrou},
     {KRD007,temple},
     {KRD008,getgol},
     {KRD009,buyspl},
     {KRD010,vhealr},
     {KRD011,gi_nulrou},
     {KRD012,gquest},
     {KRD013,gi_nulrou},
     {KRD014,gpcone},
     {KRD015,gi_nulrou},
     {KRD016,fearno},
     {KRD017,gi_nulrou},
     {KRD018,stumpr},
     {KRD019,fthick},
     {KRD020,rubies},
     {KRD021,gi_nulrou},
     {KRD022,gi_nulrou},
     {KRD023,gi_nulrou},
     {KRD024,silver},
     {KRD025,gi_nulrou},
     {KRD026,ashtre},
     {KRD027,swrock},
     {KRD028,gi_nulrou},
     {KRD029,gi_nulrou},
     {KRD030,gi_nulrou},
     {KRD031,gi_nulrou},
     {KRD032,spring},
     {KRD033,gi_nulrou},
     {KRD034,druids},
     {KRD035,terrac},
     {KRD036,waterf},
     {KRD037,gi_nulrou},
     {KRD038,magicf},
     {KRD039,gi_nulrou},
     {KRD040,gi_nulrou},
     {KRD041,gi_nulrou},
     {KRD042,gi_nulrou},
     {KRD043,gi_nulrou},
     {FOREST,gi_nulrou}, /* 044 */
     {FOREST,gi_nulrou}, /* 045 */
     {FOREST,gi_nulrou}, /* 046 */
     {FOREST,gi_nulrou}, /* 047 */
     {FOREST,gi_nulrou}, /* 048 */
     {FOREST,gi_nulrou}, /* 049 */
     {FOREST,gi_nulrou}, /* 050 */
     {FOREST,gi_nulrou}, /* 051 */
     {FOREST,gi_nulrou}, /* 052 */
     {FOREST,gi_nulrou}, /* 053 */
     {FOREST,gi_nulrou}, /* 054 */
     {FOREST,gi_nulrou}, /* 055 */
     {FOREST,gi_nulrou}, /* 056 */
     {FOREST,gi_nulrou}, /* 057 */
     {FOREST,gi_nulrou}, /* 058 */
     {FOREST,gi_nulrou}, /* 059 */
     {FOREST,gi_nulrou}, /* 060 */
     {FOREST,gi_nulrou}, /* 061 */
     {FOREST,gi_nulrou}, /* 062 */
     {FOREST,gi_nulrou}, /* 063 */
     {FOREST,gi_nulrou}, /* 064 */
     {FOREST,gi_nulrou}, /* 065 */
     {FOREST,gi_nulrou}, /* 066 */
     {FOREST,gi_nulrou}, /* 067 */
     {FOREST,gi_nulrou}, /* 068 */
     {FOREST,gi_nulrou}, /* 069 */
     {FOREST,gi_nulrou}, /* 070 */
     {FOREST,gi_nulrou}, /* 071 */
     {FOREST,gi_nulrou}, /* 072 */
     {FOREST,gi_nulrou}, /* 073 */
     {FOREST,gi_nulrou}, /* 074 */
     {FOREST,gi_nulrou}, /* 075 */
     {FOREST,gi_nulrou}, /* 076 */
     {FOREST,gi_nulrou}, /* 077 */
     {FOREST,gi_nulrou}, /* 078 */
     {FOREST,gi_nulrou}, /* 079 */
     {FOREST,gi_nulrou}, /* 080 */
     {FOREST,gi_nulrou}, /* 081 */
     {FOREST,gi_nulrou}, /* 082 */
     {FOREST,gi_nulrou}, /* 083 */
     {FOREST,gi_nulrou}, /* 084 */
     {FOREST,gi_nulrou}, /* 085 */
     {FOREST,gi_nulrou}, /* 086 */
     {FOREST,gi_nulrou}, /* 087 */
     {FOREST,gi_nulrou}, /* 088 */
     {FOREST,gi_nulrou}, /* 089 */
     {FOREST,gi_nulrou}, /* 090 */
     {FOREST,gi_nulrou}, /* 091 */
     {FOREST,gi_nulrou}, /* 092 */
     {FOREST,gi_nulrou}, /* 093 */
     {FOREST,gi_nulrou}, /* 094 */
     {FOREST,gi_nulrou}, /* 095 */
     {FOREST,gi_nulrou}, /* 096 */
     {FOREST,gi_nulrou}, /* 097 */
     {FOREST,gi_nulrou}, /* 098 */
     {FOREST,gi_nulrou}, /* 099 */
     {FOREST,gi_nulrou}, /* 100 */
     {KRD101,hnsrou},    /* 101 */
     {FOREST,gi_nulrou}, /* 102 */
     {FOREST,gi_nulrou}, /* 103 */
     {FOREST,gi_nulrou}, /* 104 */
     {FOREST,gi_nulrou}, /* 105 */
     {FOREST,gi_nulrou}, /* 106 */
     {FOREST,gi_nulrou}, /* 107 */
     {FOREST,gi_nulrou}, /* 108 */
     {FOREST,gi_nulrou}, /* 109 */
     {FOREST,gi_nulrou}, /* 110 */
     {FOREST,gi_nulrou}, /* 111 */
     {FOREST,gi_nulrou}, /* 112 */
     {FOREST,gi_nulrou}, /* 113 */
     {FOREST,gi_nulrou}, /* 114 */
     {FOREST,gi_nulrou}, /* 115 */
     {FOREST,gi_nulrou}, /* 116 */
     {FOREST,gi_nulrou}, /* 117 */
     {FOREST,gi_nulrou}, /* 118 */
     {FOREST,gi_nulrou}, /* 119 */
     {FOREST,gi_nulrou}, /* 120 */
     {FOREST,gi_nulrou}, /* 121 */
     {FOREST,gi_nulrou}, /* 122 */
     {FOREST,gi_nulrou}, /* 123 */
     {FOREST,gi_nulrou}, /* 124 */
     {FOREST,gi_nulrou}, /* 125 */
     {FOREST,gi_nulrou}, /* 126 */
     {FOREST,gi_nulrou}, /* 127 */
     {FOREST,gi_nulrou}, /* 128 */
     {FOREST,gi_nulrou}, /* 129 */
     {FOREST,gi_nulrou}, /* 130 */
     {FOREST,gi_nulrou}, /* 131 */
     {FOREST,gi_nulrou}, /* 132 */
     {FOREST,gi_nulrou}, /* 133 */
     {FOREST,gi_nulrou}, /* 134 */
     {FOREST,gi_nulrou}, /* 135 */
     {FOREST,gi_nulrou}, /* 136 */
     {FOREST,gi_nulrou}, /* 137 */
     {FOREST,gi_nulrou}, /* 138 */
     {FOREST,gi_nulrou}, /* 139 */
     {FOREST,gi_nulrou}, /* 140 */
     {FOREST,gi_nulrou}, /* 141 */
     {FOREST,gi_nulrou}, /* 142 */
     {FOREST,gi_nulrou}, /* 143 */
     {FOREST,gi_nulrou}, /* 144 */
     {FOREST,gi_nulrou}, /* 145 */
     {FOREST,gi_nulrou}, /* 146 */
     {FOREST,gi_nulrou}, /* 147 */
     {FOREST,gi_nulrou}, /* 148 */
     {FOREST,gi_nulrou}, /* 149 */
     {FOREST,gi_nulrou}, /* 150 */
     {FOREST,gi_nulrou}, /* 151 */
     {FOREST,gi_nulrou}, /* 152 */
     {FOREST,gi_nulrou}, /* 153 */
     {FOREST,gi_nulrou}, /* 154 */
     {FOREST,gi_nulrou}, /* 155 */
     {FOREST,gi_nulrou}, /* 156 */
     {FOREST,gi_nulrou}, /* 157 */
     {FOREST,gi_nulrou}, /* 158 */
     {FOREST,gi_nulrou}, /* 159 */
     {FOREST,gi_nulrou}, /* 160 */
     {FOREST,gi_nulrou}, /* 161 */
     {FOREST,gi_nulrou}, /* 162 */
     {FOREST,gi_nulrou}, /* 163 */
     {FOREST,gi_nulrou}, /* 164 */
     {FOREST,gi_nulrou}, /* 165 */
     {FOREST,gi_nulrou}, /* 166 */
     {FOREST,gi_nulrou}, /* 167 */
     {FOREST,gi_nulrou}, /* 168 */
     {DTPASS,gi_nulrou}, /* 169 */
     {KRD170,gi_nulrou}, /* 170 */
     {DTPASS,gi_nulrou}, /* 171 */
     {DTPASS,gi_nulrou}, /* 172 */
     {DTPASS,gi_nulrou}, /* 173 */
     {DTPASS,gi_nulrou}, /* 174 */
     {DTPASS,gi_nulrou}, /* 175 */
     {DTPASS,gi_nulrou}, /* 176 */
     {DTPASS,gi_nulrou}, /* 177 */
     {KRD178,gi_nulrou}, /* 178 */
     {KRD179,gi_nulrou}, /* 179 */
     {KRD180,gi_nulrou}, /* 180 */
     {KRD181,tashas},    /* 181 */
     {KRD182,refpoo},    /* 182 */
     {KRD183,panthe},    /* 183 */
     {KRD184,portal},    /* 184 */
     {KRD185,waller},    /* 185 */
     {KRD186,slotma},    /* 186 */
     {KRD187,gi_nulrou}, /* 187 */
     {KRD188,mistyr},    /* 188 */
     {KRD189,sanman},    /* 189 */
     {KRD190,gi_nulrou}, /* 190 */
     {GOLDEN,gi_nulrou}, /* 191 */
     {GOLDEN,gi_nulrou}, /* 192 */
     {GOLDEN,gi_nulrou}, /* 193 */
     {GOLDEN,gi_nulrou}, /* 194 */
     {GOLDEN,gi_nulrou}, /* 195 */
     {GOLDEN,gi_nulrou}, /* 196 */
     {GOLDEN,gi_nulrou}, /* 197 */
     {GOLDEN,gi_nulrou}, /* 198 */
     {KRD199,tulips},    /* 199 */
     {GOLDEN,gi_nulrou}, /* 200 */
     {KRD201,crystt},    /* 201 */
     {GOLDEN,gi_nulrou}, /* 202 */
     {GOLDEN,gi_nulrou}, /* 203 */
     {KRD204,rainbo},    /* 204 */
     {GOLDEN,gi_nulrou}, /* 205 */
     {GOLDEN,gi_nulrou}, /* 206 */
     {KRD207,gi_nulrou}, /* 207 */
     {GOLDEN,gi_nulrou}, /* 208 */
     {GOLDEN,gi_nulrou}, /* 209 */
     {GOLDEN,gi_nulrou}, /* 210 */
     {GOLDEN,gi_nulrou}, /* 211 */
     {GOLDEN,gi_nulrou}, /* 212 */
     {KRD213,sunshi},    /* 213 */
     {GOLDEN,gi_nulrou}, /* 214 */
     {GOLDEN,gi_nulrou}, /* 215 */
     {KRD216,gi_nulrou}, /* 216 */
     {KRD217,gi_nulrou}, /* 217 */
     {KRD218,demong},    /* 218 */
     {KRD219,gi_nulrou}, /* 219 */
     {KRD220,gi_nulrou}, /* 220 */
     {KRD221,gi_nulrou}, /* 221 */
     {KRD222,gi_nulrou}, /* 222 */
     {KRD223,gi_nulrou}, /* 223 */
     {KRD224,gi_nulrou}, /* 224 */
     {KRD225,gi_nulrou}, /* 225 */
     {KRD226,gi_nulrou}, /* 226 */
     {KRD227,gi_nulrou}, /* 227 */
     {KRD228,gi_nulrou}, /* 228 */
     {KRD229,gi_nulrou}, /* 229 */
     {KRD230,gi_nulrou}, /* 230 */
     {KRD231,gi_nulrou}, /* 231 */
     {KRD232,gi_nulrou}, /* 232 */
     {KRD233,gi_nulrou}, /* 233 */
     {KRD234,gi_nulrou}, /* 234 */
     {KRD235,gi_nulrou}, /* 235 */
     {KRD236,gi_nulrou}, /* 236 */
     {KRD237,gi_nulrou}, /* 237 */
     {KRD238,gi_nulrou}, /* 238 */
     {KRD239,gi_nulrou}, /* 239 */
     {KRD240,gi_nulrou}, /* 240 */
     {KRD241,gi_nulrou}, /* 241 */
     {KRD242,gi_nulrou}, /* 242 */
     {KRD243,gi_nulrou}, /* 243 */
     {KRD244,gi_nulrou}, /* 244 */
     {KRD245,gi_nulrou}, /* 245 */
     {KRD246,gi_nulrou}, /* 246 */
     {KRD247,gi_nulrou}, /* 247 */
     {KRD248,gi_nulrou}, /* 248 */
     {KRD249,gi_nulrou}, /* 249 */
     {KRD250,gi_nulrou}, /* 250 */
     {KRD251,gi_nulrou}, /* 251 */
     {KRD252,singer},    /* 252 */
     {KRD253,forgtr},    /* 253 */
     {KRD254,gi_nulrou}, /* 254 */
     {KRD255,oflove},    /* 255 */
     {KRD256,gi_nulrou}, /* 256 */
     {KRD257,believ},    /* 257 */
     {KRD258,gi_nulrou}, /* 258 */
     {KRD259,gi_nulrou}, /* 259 */
     {KRD260,gi_nulrou}, /* 260 */
     {KRD261,gi_nulrou}, /* 261 */
     {KRD262,gi_nulrou}, /* 262 */
     {KRD263,gi_nulrou}, /* 263 */
     {KRD264,philos},    /* 264 */
     {KRD265,gi_nulrou}, /* 265 */
     {KRD266,gi_nulrou}, /* 266 */
     {KRD267,gi_nulrou}, /* 267 */
     {KRD268,gi_nulrou}, /* 268 */
     {KRD269,gi_nulrou}, /* 269 */
     {KRD270,gi_nulrou}, /* 270 */
     {KRD271,gi_nulrou}, /* 271 */
     {KRD272,gi_nulrou}, /* 272 */
     {KRD273,gi_nulrou}, /* 273 */
     {KRD274,gi_nulrou}, /* 274 */
     {KRD275,gi_nulrou}, /* 275 */
     {KRD276,gi_nulrou}, /* 276 */
     {KRD277,gi_nulrou}, /* 277 */
     {KRD278,gi_nulrou}, /* 278 */
     {KRD279,gi_nulrou}, /* 279 */
     {KRD280,truthy},    /* 280 */
     {KRD281,gi_nulrou}, /* 281 */
     {KRD282,bodyma},    /* 282 */
     {KRD283,gi_nulrou}, /* 283 */
     {KRD284,gi_nulrou}, /* 284 */
     {KRD285,mindma},    /* 285 */
     {KRD286,gi_nulrou}, /* 286 */
     {KRD287,gi_nulrou}, /* 287 */
     {KRD288,heartm},    /* 288 */
     {KRD289,gi_nulrou}, /* 289 */
     {KRD290,gi_nulrou}, /* 290 */
     {KRD291,soulma},    /* 291 */
     {KRD292,gi_nulrou}, /* 292 */
     {KRD293,fanbel},    /* 293 */
     {KRD294,gi_nulrou}, /* 294 */
     {KRD295,devote},    /* 295 */
     {KRD296,gi_nulrou}, /* 296 */
     {KRD297,gi_nulrou}, /* 297 */
     {KRD298,gi_nulrou}, /* 298 */
     {KRD299,gi_nulrou}, /* 299 */
     {KRD300,gi_nulrou}, /* 300 */
     {KRD301,gi_nulrou}, /* 301 */
     {KRD302,wingam},    /* 302 */
     {KRD303,gi_nulrou}, /* 303 */
     {KRD304,gi_nulrou}  /* 304 */
}, *lcrptr;
