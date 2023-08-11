;--------------------------------------------------------
; File Created by SDCC : free open source ISO C Compiler 
; Version 4.3.0 #14184 (Linux)
;--------------------------------------------------------
	.module main
	.optsdcc -mz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl ___SMS__SDSC_signature
	.globl ___SMS__SDSC_descr
	.globl ___SMS__SDSC_name
	.globl ___SMS__SDSC_author
	.globl ___SMS__SEGA_signature
	.globl _main
	.globl _Scroll_Update
	.globl _Scroll_InitTilemap
	.globl _buildColumn
	.globl _Player_Update
	.globl _Animation_DrawFrame
	.globl _SMS_VRAMmemsetW
	.globl _SMS_VRAMmemcpy
	.globl _SMS_getKeysHeld
	.globl _SMS_loadSpritePalette
	.globl _SMS_loadBGPalette
	.globl _SMS_copySpritestoSAT
	.globl _SMS_addSprite_f
	.globl _SMS_initSprites
	.globl _SMS_loadTileMapColumnatAddr
	.globl _SMS_waitForVBlank
	.globl _SMS_setBackdropColor
	.globl _SMS_setBGScrollX
	.globl _SMS_VDPturnOnFeature
	.globl _Scroll_speed
	.globl _Scroll_updateMapColumn
	.globl _Scroll_vdpHorizontalScroll
	.globl _ScrollManager_horizontalScroll
	.globl _globalPalette
	.globl _Scroll_column
	.globl _SMS_SRAM
	.globl _SRAM_bank_to_be_mapped_on_slot2
	.globl _ROM_bank_to_be_mapped_on_slot0
	.globl _ROM_bank_to_be_mapped_on_slot1
	.globl _ROM_bank_to_be_mapped_on_slot2
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
_ROM_bank_to_be_mapped_on_slot2	=	0xffff
_ROM_bank_to_be_mapped_on_slot1	=	0xfffe
_ROM_bank_to_be_mapped_on_slot0	=	0xfffd
_SRAM_bank_to_be_mapped_on_slot2	=	0xfffc
_SMS_SRAM	=	0x8000
_Scroll_column::
	.ds 48
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _INITIALIZED
_globalPalette::
	.ds 16
_ScrollManager_horizontalScroll::
	.ds 2
_Scroll_vdpHorizontalScroll::
	.ds 1
_Scroll_updateMapColumn::
	.ds 1
_Scroll_speed::
	.ds 1
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area _DABS (ABS)
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area _HOME
	.area _GSINIT
	.area _GSFINAL
	.area _GSINIT
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area _HOME
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE
;source/main.c:15: void Animation_DrawFrame(const AnimationFrame* frame, short x, short y)
;	---------------------------------
; Function Animation_DrawFrame
; ---------------------------------
_Animation_DrawFrame::
	push	ix
	ld	ix,#0
	add	ix,sp
	push	af
	push	af
	dec	sp
	ld	c, l
	ld	b, h
	ld	-3 (ix), e
	ld	-2 (ix), d
;source/main.c:17: char loop = frame->numSprites;
	ld	e, c
	ld	d, b
	inc	de
	inc	de
	ld	a, (de)
	ld	-1 (ix), a
;source/main.c:18: const AnimationSprite* currentSprite = frame->sprites;
	ld	l, c
	ld	h, b
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;source/main.c:20: while (loop--)
00101$:
	ld	e, -1 (ix)
	dec	-1 (ix)
	ld	a, e
	or	a, a
	jr	Z, 00104$
;source/main.c:22: SMS_addSprite(x + currentSprite->xOffset, y + currentSprite->yOffset, currentSprite->tileIndex);
	ld	a, (bc)
	ld	e, a
	ld	d, #0x00
	ld	l, -3 (ix)
;	spillPairReg hl
;	spillPairReg hl
	ld	h, -2 (ix)
;	spillPairReg hl
;	spillPairReg hl
	add	hl, de
;	spillPairReg hl
;	spillPairReg hl
	ld	d, l
	ld	e, #0x00
	ld	l, c
;	spillPairReg hl
;	spillPairReg hl
	ld	h, b
;	spillPairReg hl
;	spillPairReg hl
	inc	hl
	inc	hl
	ld	l, (hl)
;	spillPairReg hl
;	spillPairReg hl
;	spillPairReg hl
	ld	h, #0x00
;	spillPairReg hl
;	spillPairReg hl
	ld	a, e
	or	a, l
	ld	-5 (ix), a
	ld	a, d
	or	a, h
	ld	-4 (ix), a
	ld	l, c
;	spillPairReg hl
;	spillPairReg hl
	ld	h, b
;	spillPairReg hl
;	spillPairReg hl
	inc	hl
	ld	e, (hl)
	ld	d, #0x00
	ld	l, 4 (ix)
;	spillPairReg hl
;	spillPairReg hl
	ld	h, 5 (ix)
;	spillPairReg hl
;	spillPairReg hl
	add	hl, de
	push	bc
	ld	e, -5 (ix)
	ld	d, -4 (ix)
	call	_SMS_addSprite_f
	pop	bc
;source/main.c:23: currentSprite++;
	inc	bc
	inc	bc
	inc	bc
	jr	00101$
00104$:
;source/main.c:26: }
	ld	sp, ix
	pop	ix
	pop	hl
	pop	af
	jp	(hl)
;source/main.c:38: void Player_Update(GameObject* gameObject)
;	---------------------------------
; Function Player_Update
; ---------------------------------
_Player_Update::
	push	ix
	ld	ix,#0
	add	ix,sp
	push	af
	push	af
	dec	sp
;source/main.c:44: unsigned int buttonState = SMS_getKeysHeld();
	push	hl
	call	_SMS_getKeysHeld
	pop	bc
	ld	-2 (ix), e
	ld	-1 (ix), d
;source/main.c:46: if (buttonState & PORT_A_KEY_LEFT)
	bit	2, -2 (ix)
	jr	Z, 00102$
;source/main.c:47: gameObject->x--;
	ld	l, c
	ld	h, b
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	dec	de
	ld	l, c
	ld	h, b
	ld	(hl), e
	inc	hl
	ld	(hl), d
00102$:
;source/main.c:49: if (buttonState & PORT_A_KEY_RIGHT)
	bit	3, -2 (ix)
	jr	Z, 00104$
;source/main.c:50: gameObject->x++;
	ld	l, c
	ld	h, b
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	inc	de
	ld	l, c
	ld	h, b
	ld	(hl), e
	inc	hl
	ld	(hl), d
00104$:
;source/main.c:53: gameObject->y--;
	ld	l, c
;	spillPairReg hl
;	spillPairReg hl
	ld	h, b
;	spillPairReg hl
;	spillPairReg hl
	inc	hl
	inc	hl
;source/main.c:52: if (buttonState & PORT_A_KEY_UP)
	bit	0, -2 (ix)
	jr	Z, 00106$
;source/main.c:53: gameObject->y--;
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	dec	hl
	dec	de
	ld	(hl), e
	inc	hl
	ld	(hl), d
	dec	hl
00106$:
;source/main.c:55: if (buttonState & PORT_A_KEY_DOWN)
	bit	1, -2 (ix)
	jr	Z, 00108$
;source/main.c:56: gameObject->y++;
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	dec	hl
	inc	de
	ld	(hl), e
	inc	hl
	ld	(hl), d
00108$:
;source/main.c:58: if (gameObject->animationTime == gameObject->currentAnimationFrame->frameTime)
	ld	hl, #0x000a
	add	hl, bc
	ex	(sp), hl
	pop	hl
	push	hl
	ld	e, (hl)
	ld	hl, #0x0007
	add	hl, bc
	ld	-3 (ix), l
	ld	-2 (ix), h
	ld	a, (hl)
	inc	hl
	ld	h, (hl)
;	spillPairReg hl
	ld	l, a
;	spillPairReg hl
;	spillPairReg hl
	inc	hl
	inc	hl
	inc	hl
	ld	a, (hl)
	sub	a, e
	jr	NZ, 00112$
;source/main.c:60: gameObject->currentAnimationFrameIndex++;
	ld	hl, #0x0009
	add	hl, bc
	ex	de, hl
	ld	a, (de)
	inc	a
	ld	-1 (ix), a
	ld	(de), a
;source/main.c:62: if (gameObject->currentAnimationFrameIndex == gameObject->animation->numFrames)
	inc	bc
	inc	bc
	inc	bc
	inc	bc
	ld	l, c
	ld	h, b
	ld	a, (hl)
	inc	hl
	ld	h, (hl)
;	spillPairReg hl
	ld	l, a
;	spillPairReg hl
;	spillPairReg hl
	inc	hl
	inc	hl
	inc	hl
	inc	hl
;	spillPairReg hl
	ld	a,-1 (ix)
	sub	a,(hl)
	jr	NZ, 00110$
;source/main.c:63: gameObject->currentAnimationFrameIndex = 0;
	xor	a, a
	ld	(de), a
00110$:
;source/main.c:65: gameObject->currentAnimationFrame = gameObject->animation->frames[gameObject->currentAnimationFrameIndex];
	ld	l, c
	ld	h, b
	ld	c, (hl)
	inc	hl
	ld	h, (hl)
;	spillPairReg hl
	ld	l, c
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	a, (de)
	ld	h, #0x00
;	spillPairReg hl
;	spillPairReg hl
	ld	l, a
	add	hl, hl
	add	hl, bc
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	pop	de
	pop	hl
	push	hl
	push	de
	ld	(hl), c
	inc	hl
	ld	(hl), b
;source/main.c:66: gameObject->animationTime = 0;
	pop	hl
	ld	(hl), #0x00
	push	hl
00112$:
;source/main.c:72: gameObject->animationTime++;
	pop	hl
	push	hl
	ld	a, (hl)
	inc	a
	pop	hl
	push	hl
	ld	(hl), a
;source/main.c:73: }
	ld	sp, ix
	pop	ix
	ret
;source/main.c:86: void buildColumn(unsigned short tileColumn)
;	---------------------------------
; Function buildColumn
; ---------------------------------
_buildColumn::
	push	ix
	ld	ix,#0
	add	ix,sp
	ld	iy, #-8
	add	iy, sp
	ld	sp, iy
;source/main.c:89: unsigned short metatileColumn = (tileColumn >> 1) % background_map.mapWidth;
	ld	-3 (ix), l
	ld	-2 (ix), h
	ld	c, l
	ld	b, h
	srl	b
	rr	c
	ld	a, (#(_background_map + 4) + 0)
	ld	e, a
	ld	d, #0x00
	ld	l, c
;	spillPairReg hl
;	spillPairReg hl
	ld	h, b
;	spillPairReg hl
;	spillPairReg hl
	call	__moduint
	inc	sp
	inc	sp
	push	de
;source/main.c:92: unsigned char metatileOffset = tileColumn & 1;
	ld	a, -3 (ix)
	and	a, #0x01
	ld	-6 (ix), a
;source/main.c:94: unsigned short* columnRunner = Scroll_column;
	ld	-5 (ix), #<(_Scroll_column)
	ld	-4 (ix), #>(_Scroll_column)
;source/main.c:97: for (unsigned char loop = 0; loop < background_map.mapHeight; loop++)
	ld	-1 (ix), #0x00
00103$:
	ld	hl, #_background_map + 5
	ld	a,-1 (ix)
	sub	a,(hl)
	jr	NC, 00105$
;source/main.c:100: unsigned short metatile_index = (background_map.metatileMap[metatileColumn + (loop * background_map.mapWidth)] * 4) + metatileOffset;
	ld	bc, (#_background_map + 0)
	ld	a, (#(_background_map + 4) + 0)
	push	bc
	ld	e, a
	ld	h, -1 (ix)
;	spillPairReg hl
;	spillPairReg hl
	ld	l, #0x00
	ld	d, l
	ld	b, #0x08
00118$:
	add	hl, hl
	jr	NC, 00119$
	add	hl, de
00119$:
	djnz	00118$
	pop	bc
	pop	de
	push	de
	add	hl, de
	add	hl, hl
	add	hl, bc
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ex	de, hl
	add	hl, hl
	add	hl, hl
	ld	c, -6 (ix)
	ld	b, #0x00
	add	hl, bc
	ex	de, hl
;source/main.c:103: *columnRunner = background_tileset.metatile_lut[metatile_index];
	ld	bc, (#(_background_tileset + 2) + 0)
	ld	l, e
	ld	h, d
	add	hl, hl
	add	hl, bc
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	l, -5 (ix)
	ld	h, -4 (ix)
	ld	(hl), c
	inc	hl
	ld	(hl), b
;source/main.c:104: columnRunner++;
	ld	c, -5 (ix)
	ld	b, -4 (ix)
	inc	bc
	inc	bc
;source/main.c:107: *columnRunner = background_tileset.metatile_lut[metatile_index + 2];
	ld	hl, (#(_background_tileset + 2) + 0)
	inc	de
	inc	de
	ex	de, hl
	add	hl, hl
	ex	de, hl
	add	hl, de
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	l, c
	ld	h, b
	ld	(hl), e
	inc	hl
	ld	(hl), d
;source/main.c:108: columnRunner++;
	inc	bc
	inc	bc
	ld	-5 (ix), c
	ld	-4 (ix), b
;source/main.c:97: for (unsigned char loop = 0; loop < background_map.mapHeight; loop++)
	inc	-1 (ix)
	jr	00103$
00105$:
;source/main.c:110: }
	ld	sp, ix
	pop	ix
	ret
;source/main.c:112: void Scroll_InitTilemap()
;	---------------------------------
; Function Scroll_InitTilemap
; ---------------------------------
_Scroll_InitTilemap::
;source/main.c:115: for (int loop = 1; loop < 32; loop++)
	ld	bc, #0x0001
00103$:
	ld	a, c
	sub	a, #0x20
	ld	a, b
	rla
	ccf
	rra
	sbc	a, #0x80
	jr	NC, 00101$
;source/main.c:117: buildColumn(loop);
	ld	l, c
;	spillPairReg hl
;	spillPairReg hl
	ld	h, b
;	spillPairReg hl
;	spillPairReg hl
	push	bc
	call	_buildColumn
	pop	bc
;source/main.c:118: SMS_loadTileMapColumn(loop, 0, Scroll_column, 24);
	ld	l, c
;	spillPairReg hl
;	spillPairReg hl
	ld	h, #0x00
;	spillPairReg hl
;	spillPairReg hl
	add	hl, hl
	ld	a, h
	or	a, #0x78
	ld	h, a
;	spillPairReg hl
;	spillPairReg hl
	push	bc
	ld	de, #0x0018
	push	de
	ld	de, #_Scroll_column
	call	_SMS_loadTileMapColumnatAddr
	pop	bc
;source/main.c:115: for (int loop = 1; loop < 32; loop++)
	inc	bc
	jr	00103$
00101$:
;source/main.c:125: buildColumn(32);
	ld	hl, #0x0020
	call	_buildColumn
;source/main.c:126: SMS_loadTileMapColumn(0, 0, Scroll_column, 24);
	ld	hl, #0x0018
	push	hl
	ld	de, #_Scroll_column
	ld	hl, #0x7800
	call	_SMS_loadTileMapColumnatAddr
;source/main.c:127: }
	ret
;source/main.c:129: void Scroll_Update(GameObject* gameObject)
;	---------------------------------
; Function Scroll_Update
; ---------------------------------
_Scroll_Update::
	push	ix
	ld	ix,#0
	add	ix,sp
	push	af
	push	af
;source/main.c:131: if (gameObject->x > ScrollManager_horizontalScroll + 128)
	ld	a, (hl)
	ld	-4 (ix), a
	inc	hl
	ld	a, (hl)
	ld	-3 (ix), a
	ld	hl, (_ScrollManager_horizontalScroll)
	ld	-2 (ix), l
	ld	-1 (ix), h
	ld	de, #0x0080
	add	hl, de
	pop	bc
	push	bc
	xor	a, a
	sbc	hl, bc
	jr	NC, 00102$
;source/main.c:133: Scroll_speed = gameObject->x - (ScrollManager_horizontalScroll + 128);
	ld	c, -4 (ix)
	ld	a, (_ScrollManager_horizontalScroll+0)
	add	a, #0x80
	ld	b, a
	ld	hl, #_Scroll_speed
	ld	a, c
	sub	a, b
	ld	(hl), a
	jr	00103$
00102$:
;source/main.c:137: Scroll_speed = 0;
	ld	hl, #_Scroll_speed
	ld	(hl), #0x00
00103$:
;source/main.c:141: ScrollManager_horizontalScroll += Scroll_speed; // scrolling towards the right into the map
	ld	a, (_Scroll_speed+0)
	ld	b, #0x00
	ld	c, a
	ld	l, -2 (ix)
	ld	h, -1 (ix)
	add	hl, bc
	ld	(_ScrollManager_horizontalScroll), hl
;source/main.c:142: Scroll_vdpHorizontalScroll -= Scroll_speed; // vdp scrolls backwards in comparison
	ld	hl, #_Scroll_speed
	push	de
	ld	de, #_Scroll_vdpHorizontalScroll
	ld	a, (de)
	sub	a, (hl)
	ld	(de), a
	pop	de
;source/main.c:144: ScrollManager_horizontalScroll %= (background_map.mapWidth * 16); // clamp the scrolling to the pixel width of the map.
	ld	a, (#(_background_map + 4) + 0)
	ld	h, #0x00
;	spillPairReg hl
;	spillPairReg hl
	ld	l, a
;	spillPairReg hl
;	spillPairReg hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	ex	de,hl
	ld	hl, (_ScrollManager_horizontalScroll)
	call	__moduint
	ld	(_ScrollManager_horizontalScroll), de
;source/main.c:146: if (ScrollManager_horizontalScroll % 8 == 0 && Scroll_speed) // when we hit a 8 pixel boundary, prep a new column to display
	ld	hl, (_ScrollManager_horizontalScroll)
	ld	a, l
	and	a, #0x07
	jr	NZ, 00107$
	ld	a, (_Scroll_speed+0)
	or	a, a
	jr	Z, 00107$
;source/main.c:149: unsigned short tileColumn = (ScrollManager_horizontalScroll >> 3) + 32; 
	ld	hl, (_ScrollManager_horizontalScroll)
	srl	h
	rr	l
	srl	h
	rr	l
	srl	h
	rr	l
	ld	bc, #0x0020
	add	hl, bc
;source/main.c:150: buildColumn(tileColumn);
	call	_buildColumn
;source/main.c:152: Scroll_updateMapColumn = TRUE;
	ld	hl, #_Scroll_updateMapColumn
	ld	(hl), #0x01
00107$:
;source/main.c:154: }
	ld	sp, ix
	pop	ix
	ret
;source/main.c:156: void main(void)
;	---------------------------------
; Function main
; ---------------------------------
_main::
	push	ix
	ld	ix,#0
	add	ix,sp
	ld	hl, #-11
	add	hl, sp
	ld	sp, hl
;source/main.c:159: SMS_VRAMmemsetW(0, 0x0000, 16384);
	ld	hl, #0x4000
	push	hl
	ld	de, #0x0000
	ld	h, l
	call	_SMS_VRAMmemsetW
;source/main.c:161: SMS_loadBGPalette(globalPalette);
	ld	hl, #_globalPalette
	call	_SMS_loadBGPalette
;source/main.c:162: SMS_loadSpritePalette(globalPalette);
	ld	hl, #_globalPalette
	call	_SMS_loadSpritePalette
;source/main.c:165: SMS_loadTiles(ninja_girl.tileData, 256, ninja_girl.totalTileCount * 32);
	ld	a, (#_ninja_girl + 8)
	ld	l, a
;	spillPairReg hl
;	spillPairReg hl
	ld	h, #0x00
;	spillPairReg hl
;	spillPairReg hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	ld	c, l
	ld	b, h
	ld	de, (#_ninja_girl + 2)
	push	bc
	ld	hl, #0x6000
	call	_SMS_VRAMmemcpy
;source/main.c:168: SMS_loadTiles(background_tileset.tiles, 0, background_tileset.numTiles * 32);
	ld	a, (#_background_tileset + 4)
	ld	l, a
;	spillPairReg hl
;	spillPairReg hl
	ld	h, #0x00
;	spillPairReg hl
;	spillPairReg hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	ld	c, l
	ld	b, h
	ld	de, (#_background_tileset + 0)
	push	bc
	ld	hl, #0x4000
	call	_SMS_VRAMmemcpy
;source/main.c:170: Scroll_updateMapColumn = FALSE;
	ld	hl, #_Scroll_updateMapColumn
	ld	(hl), #0x00
;source/main.c:172: SMS_VDPturnOnFeature(VDPFEATURE_LEFTCOLBLANK);
	ld	hl, #0x0020
	call	_SMS_VDPturnOnFeature
;source/main.c:173: Scroll_InitTilemap();
	call	_Scroll_InitTilemap
;source/main.c:177: player.x = 122;
	ld	-11 (ix), #0x7a
	ld	-10 (ix), #0
;source/main.c:178: player.y = 88;
	ld	-9 (ix), #0x58
	xor	a, a
	ld	-8 (ix), a
;source/main.c:179: player.animation = &ninja_girl;
	ld	-7 (ix), #<(_ninja_girl)
	ld	-6 (ix), #>(_ninja_girl)
;source/main.c:180: player.currentAnimationFrameIndex = 0;
	ld	-2 (ix), #0x00
;source/main.c:181: player.currentAnimationFrame = ninja_girl.frames[player.currentAnimationFrameIndex];
	ld	hl, (#_ninja_girl + 0)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	-4 (ix), c
	ld	-3 (ix), b
;source/main.c:182: player.animationTime = 0;
	ld	-1 (ix), #0x00
;source/main.c:183: player.animationVdpTileIndex = 0;
	ld	-5 (ix), #0x00
;source/main.c:187: SMS_displayOn();
	ld	hl, #0x0140
	call	_SMS_VDPturnOnFeature
;source/main.c:188: SMS_waitForVBlank ();
	call	_SMS_waitForVBlank
00104$:
;source/main.c:193: SMS_setBackdropColor(6);
	ld	l, #0x06
;	spillPairReg hl
;	spillPairReg hl
	call	_SMS_setBackdropColor
;source/main.c:196: SMS_initSprites();
	call	_SMS_initSprites
;source/main.c:197: SMS_setBackdropColor(7);
	ld	l, #0x07
;	spillPairReg hl
;	spillPairReg hl
	call	_SMS_setBackdropColor
;source/main.c:199: Player_Update(&player);
	ld	hl, #0
	add	hl, sp
	call	_Player_Update
;source/main.c:200: SMS_setBackdropColor(8);
	ld	l, #0x08
;	spillPairReg hl
;	spillPairReg hl
	call	_SMS_setBackdropColor
;source/main.c:202: Scroll_Update(&player);
	ld	hl, #0
	add	hl, sp
	call	_Scroll_Update
;source/main.c:203: SMS_setBackdropColor(9);
	ld	l, #0x09
;	spillPairReg hl
;	spillPairReg hl
	call	_SMS_setBackdropColor
;source/main.c:208: Animation_DrawFrame(player.currentAnimationFrame, player.x - ScrollManager_horizontalScroll, player.y);
	pop	hl
	pop	bc
	push	bc
	ex	de,hl
	push	de
	ld	hl, #_ScrollManager_horizontalScroll
	ld	a, e
	sub	a, (hl)
	inc	hl
	ld	e, a
	ld	a, d
	sbc	a, (hl)
	ld	d, a
	ld	l, -4 (ix)
;	spillPairReg hl
;	spillPairReg hl
	ld	h, -3 (ix)
;	spillPairReg hl
;	spillPairReg hl
	push	bc
	call	_Animation_DrawFrame
;source/main.c:209: SMS_setBackdropColor(0);
	ld	l, #0x00
;	spillPairReg hl
;	spillPairReg hl
	call	_SMS_setBackdropColor
;source/main.c:214: SMS_waitForVBlank ();
	call	_SMS_waitForVBlank
;source/main.c:215: SMS_setBackdropColor(11);
	ld	l, #0x0b
;	spillPairReg hl
;	spillPairReg hl
	call	_SMS_setBackdropColor
;source/main.c:216: SMS_setBGScrollX(Scroll_vdpHorizontalScroll);
	ld	a, (_Scroll_vdpHorizontalScroll+0)
	ld	l, a
;	spillPairReg hl
;	spillPairReg hl
	call	_SMS_setBGScrollX
;source/main.c:218: if (Scroll_updateMapColumn)
	ld	a, (_Scroll_updateMapColumn+0)
	or	a, a
	jr	Z, 00102$
;source/main.c:220: Scroll_updateMapColumn = FALSE;
	ld	hl, #_Scroll_updateMapColumn
	ld	(hl), #0x00
;source/main.c:221: unsigned char scrollMapColumn = Scroll_vdpHorizontalScroll >> 3;
	ld	a, (#_Scroll_vdpHorizontalScroll + 0)
	ld	c, a
	srl	c
	srl	c
	srl	c
;source/main.c:222: SMS_loadTileMapColumn((32 - scrollMapColumn) & 31, 0, Scroll_column, 24);
	ld	a, #0x20
	sub	a, c
	and	a, #0x1f
	ld	h, #0x00
;	spillPairReg hl
;	spillPairReg hl
	ld	l, a
	add	hl, hl
	ld	a, h
	or	a, #0x78
	ld	h, a
;	spillPairReg hl
;	spillPairReg hl
	ld	de, #0x0018
	push	de
	ld	de, #_Scroll_column
	call	_SMS_loadTileMapColumnatAddr
00102$:
;source/main.c:225: SMS_copySpritestoSAT();
	call	_SMS_copySpritestoSAT
;source/main.c:226: SMS_setBackdropColor(0);
	ld	l, #0x00
;	spillPairReg hl
;	spillPairReg hl
	call	_SMS_setBackdropColor
;source/main.c:228: }
	jp	00104$
	.area _CODE
__str_0:
	.ascii "pw"
	.db 0x00
__str_1:
	.ascii "basicsmsproject"
	.db 0x00
__str_2:
	.ascii "A basic SMS example project with devkitSMS"
	.db 0x00
	.area _INITIALIZER
__xinit__globalPalette:
	.db #0x00	; 0
	.db #0x01	; 1
	.db #0x10	; 16
	.db #0x15	; 21
	.db #0x06	; 6
	.db #0x04	; 4
	.db #0x17	; 23
	.db #0x15	; 21
	.db #0x39	; 57	'9'
	.db #0x0b	; 11
	.db #0x2a	; 42
	.db #0x09	; 9
	.db #0x2b	; 43
	.db #0x3d	; 61
	.db #0x1f	; 31
	.db #0x3f	; 63
__xinit__ScrollManager_horizontalScroll:
	.dw #0x0000
__xinit__Scroll_vdpHorizontalScroll:
	.db #0x00	; 0
__xinit__Scroll_updateMapColumn:
	.db #0x00	; 0
__xinit__Scroll_speed:
	.db #0x00	; 0
	.area _CABS (ABS)
	.org 0x7FF0
___SMS__SEGA_signature:
	.db #0x54	; 84	'T'
	.db #0x4d	; 77	'M'
	.db #0x52	; 82	'R'
	.db #0x20	; 32
	.db #0x53	; 83	'S'
	.db #0x45	; 69	'E'
	.db #0x47	; 71	'G'
	.db #0x41	; 65	'A'
	.db #0xff	; 255
	.db #0xff	; 255
	.db #0xff	; 255
	.db #0xff	; 255
	.db #0x99	; 153
	.db #0x99	; 153
	.db #0x00	; 0
	.db #0x4c	; 76	'L'
	.org 0x7FDD
___SMS__SDSC_author:
	.ascii "pw"
	.db 0x00
	.org 0x7FCD
___SMS__SDSC_name:
	.ascii "basicsmsproject"
	.db 0x00
	.org 0x7FA2
___SMS__SDSC_descr:
	.ascii "A basic SMS example project with devkitSMS"
	.db 0x00
	.org 0x7FE0
___SMS__SDSC_signature:
	.db #0x53	; 83	'S'
	.db #0x44	; 68	'D'
	.db #0x53	; 83	'S'
	.db #0x43	; 67	'C'
	.db #0x01	; 1
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0xdd	; 221
	.db #0x7f	; 127
	.db #0xcd	; 205
	.db #0x7f	; 127
	.db #0xa2	; 162
	.db #0x7f	; 127
