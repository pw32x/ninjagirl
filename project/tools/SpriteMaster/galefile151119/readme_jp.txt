-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
                               galefile.dll
                  Copyright 2009 HUMANBALANCE Co.,Ltd.
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


���\�t�g�T�v

�{�\�t�g�́AGraphicsGale�̃t�@�C���t�H�[�}�b�g(*.gal)���O���v���O��������
�������߂̃��C�u����(DLL)�ł��B


���֐�

LPVOID __stdcall ggOpen(LPCSTR apath);
�@�@�@�\�FGAL�t�@�C���J���B
�@���@���Fapath = �t�@�C���̃t���p�X
�@�߂�l�F���������ꍇ��Gale�I�u�W�F�N�g�̃|�C���^��Ԃ��B���s�����ꍇ��
�@�@�@�@�@NULL��Ԃ��B�|�C���^�𓾂���I������O��ggClose�ŕ���K�v����
�@�@�@�@�@��B

LONG __stdcall ggClose(LPVOID pFile);
�@�@�@�\�FGale�I�u�W�F�N�g��j������B
�@���@���FpFile = Gale�I�u�W�F�N�g
�@�߂�l�F���������ꍇ��1��Ԃ��B���s�����ꍇ��0��Ԃ��B

DWORD __stdcall ggGetLastError(void);
�@�@�@�\�F�ŐV�̃G���[�R�[�h��Ԃ��B�e�֐��ŃG���[����������ɌĂяo���B
�@���@���F�Ȃ�
�@�߂�l�F�G���[�R�[�h
�@�@�@�@�@�@1 = �t�@�C�������݂��Ȃ�
�@�@�@�@�@�@2 = �t�@�C���t�H�[�}�b�g���s��
�@�@�@�@�@�@3 = �t�@�C���N���[�Y�Ɏ��s
�@�@�@�@�@�@4 = Gale�I�u�W�F�N�g�̃|�C���^������
�@�@�@�@�@�@5 = ����������

DWORD __stdcall ggGetFrameCount(LPVOID pFile);
�@�@�@�\�F�t���[������Ԃ��B
�@���@���FpFile = Gale�I�u�W�F�N�g
�@�߂�l�FGale�I�u�W�F�N�g�̃t���[������Ԃ��B���s�����ꍇ��0��Ԃ��B

DWORD __stdcall ggGetLayerCount(LPVOID pFile,LONG frameNo);
�@�@�@�\�F���C���[����Ԃ��B
�@���@���FpFile = Gale�I�u�W�F�N�g
�@�@�@�@�@frameNo = 0����n�܂�t���[���C���f�b�N�X
�@�߂�l�FGale�I�u�W�F�N�g�̃��C���[����Ԃ��B���s�����ꍇ��0��Ԃ��B

LONG __stdcall ggGetInfo(LPVOID pFile,LONG nID);
�@�@�@�\�FGale�I�u�W�F�N�g�̊e�����Ԃ��B
�@���@���FpFile = Gale�I�u�W�F�N�g
�@�@�@�@�@nID = �擾������ID
�@�@�@�@�@�@1 = �w�i�F
�@�@�@�@�@�@2 = �V���O���p���b�g�Ȃ�1
�@�@�@�@�@�@3 = �ŉ��w���C���[�̓��ߋ֎~�Ȃ�1
�@�@�@�@�@�@4 = bpp(1,4,8,15,16,24)
�@�@�@�@�@�@5 = ��(�s�N�Z���P��)
�@�@�@�@�@�@6 = ����(�s�N�Z���P��)
�@�߂�l�FnID�ɉ������l��Ԃ��B

LONG __stdcall ggGetFrameInfo(LPVOID pFile,LONG frameNo,LONG nID);
�@�@�@�\�F�w��t���[���̊e�����Ԃ��B
�@���@���FpFile = Gale�I�u�W�F�N�g
�@�@�@�@�@frameNo = 0����n�܂�t���[���C���f�b�N�X
�@�@�@�@�@nID = �擾������ID
�@�@�@�@�@�@1 = ���ߐF
�@�@�@�@�@�@2 = �\������(�~���b�P��)
�@�@�@�@�@�@3 = �\���㏈��
�@�@�@�@�@�@�@0 = �w�肵�Ȃ�
�@�@�@�@�@�@�@1 = �������Ȃ�
�@�@�@�@�@�@�@2 = �w�i�F�œh��Ԃ�
�@�@�@�@�@�@�@3 = ���ɖ߂�
�@�߂�l�FnID�ɉ������l��Ԃ��B

LONG __stdcall ggGetFrameName(LPVOID pFile,LONG frameNo,LPSTR pName,LONG len);
�@�@�@�\�F�w��t���[���̖��O��Ԃ��B
�@���@���FpFile = Gale�I�u�W�F�N�g
�@�@�@�@�@frameNo = 0����n�܂�t���[���C���f�b�N�X
�@�@�@�@�@pName = ���O���󂯎��o�b�t�@�̃A�h���X�BNULL��n���ƕK�v�ȃo
�@�@�@�@�@�@�@�@�@�b�t�@�T�C�Y��Ԃ��B
�@�@�@�@�@len = �o�b�t�@�̃T�C�Y(�o�C�g�P��)
�@�߂�l�F���������ꍇ�̓R�s�[���ꂽ�o�C�g����Ԃ��B���s�����ꍇ��0��Ԃ��B

LONG __stdcall ggGetLayerInfo(LPVOID pFile,LONG frameNo,LONG layerNo,LONG nID);
�@�@�@�\�F�w�背�C���[�̊e�����Ԃ��B
�@���@���FpFile = Gale�I�u�W�F�N�g
�@�@�@�@�@frameNo = 0����n�܂�t���[���C���f�b�N�X
�@�@�@�@�@layerNo = 0����n�܂郌�C���[�C���f�b�N�X
�@�@�@�@�@nID = �擾������ID
�@�@�@�@�@�@1 = �\���Ȃ�1�A��\���Ȃ�0
�@�@�@�@�@�@2 = ���ߐF
�@�@�@�@�@�@3 = �s���ߓx(0�`255)
�@�@�@�@�@�@4 = �A���t�@�`�����l�����L���Ȃ�1
�@�߂�l�FnID�ɉ������l��Ԃ��B

LONG __stdcall ggGetLayerName(LPVOID pFile,LONG frameNo,LONG layerNo,LPSTR pName,LONG len);
�@�@�@�\�F�w�背�C���[�̖��O��Ԃ��B
�@���@���FpFile = Gale�I�u�W�F�N�g
�@�@�@�@�@frameNo = 0����n�܂�t���[���C���f�b�N�X
�@�@�@�@�@layerNo = 0����n�܂郌�C���[�C���f�b�N�X
�@�@�@�@�@pName = ���O���󂯎��o�b�t�@�̃A�h���X�BNULL��n���ƕK�v�ȃo
�@�@�@�@�@�@�@�@�@�b�t�@�T�C�Y��Ԃ��B
�@�@�@�@�@len = �o�b�t�@�̃T�C�Y(�o�C�g�P��)
�@�߂�l�F���������ꍇ�̓R�s�[���ꂽ�o�C�g����Ԃ��B���s�����ꍇ��0��Ԃ��B

HBITMAP __stdcall ggGetBitmap(LPVOID pFile,LONG frameNo,LONG layerNo);
�@�@�@�\�F�w��t���[���A�w�背�C���[�̉摜�̃r�b�g�}�b�v�n���h����Ԃ��B
�@�@�@�@�@�擾�����n���h����j�����Ă͂Ȃ�Ȃ��B
�@���@���FpFile = Gale�I�u�W�F�N�g
�@�@�@�@�@frameNo = 0����n�܂�t���[���C���f�b�N�X
�@�@�@�@�@layerNo = 0����n�܂郌�C���[�C���f�b�N�X�B-1�Ȃ獇�������摜
�@�߂�l�F���������ꍇ�̓r�b�g�}�b�v�n���h����Ԃ��B���s�����ꍇ��NULL��Ԃ��B

HBITMAP __stdcall ggGetAlphaChannel(LPVOID pFile,LONG frameNo,LONG layerNo);
�@�@�@�\�F�w��t���[���A�w�背�C���[�̃A���t�@�`�����l���̃r�b�g�}�b�v�n
�@�@�@�@�@���h����Ԃ��B
�@�@�@�@�@�擾�����n���h����j�����Ă͂Ȃ�Ȃ��B
�@���@���FpFile = Gale�I�u�W�F�N�g
�@�@�@�@�@frameNo = 0����n�܂�t���[���C���f�b�N�X
�@�@�@�@�@layerNo = 0����n�܂郌�C���[�C���f�b�N�X
�@�߂�l�F���������ꍇ�̓r�b�g�}�b�v�n���h����Ԃ��B���s�����ꍇ��NULL��Ԃ��B

HPALETTE __stdcall ggGetPalette(LPVOID pFile,LONG frameNo);
�@�@�@�\�F�w��t���[���̉摜�̃p���b�g�n���h����Ԃ��B
�@�@�@�@�@�擾�����n���h����j�����Ă͂Ȃ�Ȃ��B
�@���@���FpFile = Gale�I�u�W�F�N�g
�@�@�@�@�@frameNo = 0����n�܂�t���[���C���f�b�N�X
�@�߂�l�F���������ꍇ�̓p���b�g�n���h����Ԃ��B���s�����ꍇ��NULL��Ԃ��B

LONG __stdcall ggDrawBitmap(LPVOID pFile,LONG frameNo,LONG layerNo,HDC toDC,LONG toX,LONG toY);
�@�@�@�\�F�w��t���[���A�w�背�C���[�̉摜��`�悷��B
�@���@���FpFile = Gale�I�u�W�F�N�g
�@�@�@�@�@frameNo = 0����n�܂�t���[���C���f�b�N�X
�@�@�@�@�@layerNo = 0����n�܂郌�C���[�C���f�b�N�X�B-1�Ȃ獇�������摜
�@�@�@�@�@toDC = �`���̃f�o�C�X�R���e�L�X�g�̃n���h��
�@�@�@�@�@toX = �`����x���W
�@�@�@�@�@toY = �`����y���W
�@�߂�l�F���������ꍇ��1��Ԃ��B���s�����ꍇ��0��Ԃ��B

LONG __stdcall ggExportBitmap(LPVOID pFile,LONG frameNo,LONG layerNo,LPCSTR outPath);
�@�@�@�\�F�w��t���[���A�w�背�C���[�̉摜��BMP�t�@�C���ɏo�͂���B
�@���@���FpFile = Gale�I�u�W�F�N�g
�@�@�@�@�@frameNo = 0����n�܂�t���[���C���f�b�N�X
�@�@�@�@�@layerNo = 0����n�܂郌�C���[�C���f�b�N�X�B-1�Ȃ獇�������摜
�@�@�@�@�@outPath = �o�͂���t�@�C���̃t���p�X
�@�߂�l�F���������ꍇ��1��Ԃ��B���s�����ꍇ��0��Ԃ��B

LONG __stdcall ggExportAlphaChannel(LPVOID pFile,LONG frameNo,LONG layerNo,LPCSTR outPath);
�@�@�@�\�F�w��t���[���A�w�背�C���[�̃A���t�@�`�����l����BMP�t�@�C����
�@�@�@�@�@�o�͂���B
�@���@���FpFile = Gale�I�u�W�F�N�g
�@�@�@�@�@frameNo = 0����n�܂�t���[���C���f�b�N�X
�@�@�@�@�@layerNo = 0����n�܂郌�C���[�C���f�b�N�X
�@�@�@�@�@outPath = �o�͂���t�@�C���̃t���p�X
�@�߂�l�F���������ꍇ��1��Ԃ��B���s�����ꍇ��0��Ԃ��B


���g�p����

���̃\�t�g�E�F�A�́A�t���[�E�F�A�Ƃ��Ĕz�t����܂��B�����A�����Ŏg�p���A
�܂���O�҂ɔz�t���邱�Ƃ��ł��܂��B���̃\�t�g�E�F�A�̒��쌠�͗L����Ѓq
���[�}���o�����X�ɋA�����܂��B���p�ړI�ł̔z�t�ɂ͗L����Ѓq���[�}���o��
���X�̏������K�v�ł��B
���̃\�t�g�E�F�A��ݗ^�A���[�X�A�܂��A�C���A�ϊ��A�|��A���o�[�X�G���W�j
�A�����O�A�t�R���p�C���A��͂��邱�Ƃ͋ւ����Ă��܂��B���̋������̔@��
�Ȃ镔���ɂ���G�����ꍇ�ɂ́A���̃\�t�g�E�F�A���g�p���錠���͎����I�ɏ�
�ł��A���̃\�t�g�E�F�A�Ɋւ���S�Ẵt�@�C�����폜���Ȃ���΂Ȃ�܂���B
���̃\�t�g�E�F�A�y�ъ֘A���ނ́A�P���ɂ��̂܂܂̌`�ԂŒ񋟂������̂ł�
��A�����Ȃ�ۏ؂��t���Ă��܂���B�L����Ѓq���[�}���o�����X�́A�����I��
����Î��I�ł���A���̃\�t�g�E�F�A�̎g�p�Ɋւ��A��؂̕ۏ؂�������̂ł�
����܂���B
�܂��A�����Ȃ�󋵂ɂ����Ă��A�L����Ѓq���[�}���o�����X�́A���̃\�t�g�E
�F�A���g�p���邱�Ƃɂ���Ė����ꐶ�������Q�ɑ΂��A����ӔC�𕉂����̂ł�
����܂���B


���X�V����

��15.11.19
�E�V�t�@�C���`���ɑΉ�

��09.12.07
�EggGetBitmap��ggGetPalette���C��
�EggGetAlphaChannel��ggExportAlphaChannel��ǉ�

��09.06.30
�Ever.2�̃t�@�C���`���ɑΉ�

��09.03.08
�E�����J



�L����Ѓq���[�}���o�����X

gale@humanbalance.net
http://www.humanbalance.net/
