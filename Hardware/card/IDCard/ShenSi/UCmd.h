extern HINSTANCE hModule;



typedef int (PASCAL *pUCmmand1)(BYTE *pcmd,int *p1,int *p2,int *p3);
typedef int (PASCAL *pGetInfo)(BYTE *buf);

extern pUCmmand1		mycmd;

extern pGetInfo GetSAMIDToStr;
extern pGetInfo myGetName    ;     //��ȡ����
extern pGetInfo myGetSex     ;     //��ȡ�Ա�
extern pGetInfo myGetFolk    ;     //��ȡ����
extern pGetInfo myGetBirth   ;     //��ȡ����
extern pGetInfo myGetAddr    ;     //��ȡסַ
extern pGetInfo myGetIDNum   ;     //��ȡ������ݺ���
extern pGetInfo myGetDep     ;     //��ȡǩ������
extern pGetInfo myGetBegin   ;     //��ȡ��Ч����
extern pGetInfo myGetEnd     ;     //��ȡ��Ч��ֹ
extern pGetInfo myGetNewAddr ;     //��ȡ���µ�ַ
extern pGetInfo myGetPicPath ;     //��ȡͷ��ͼƬ·��

// extern BOOL LoadDll();
// extern void FreeDll();

BOOL LoadDll();
void FreeDll();
