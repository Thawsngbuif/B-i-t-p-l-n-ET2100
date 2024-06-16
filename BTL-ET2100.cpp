#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Khoi tao danh sach lop hoc
struct nodegv;

typedef struct
{
  char malop[10];
  char thu;
  char bd, kt;
  char diadiem[10];
  struct nodegv *gv[5];
} lop;

struct nodelh
{
  lop lh;
  nodelh *next;
};
typedef struct nodelh *pnodelh;
typedef struct nodelh *lllop;

// Khoi tao danh sach hoc phan
typedef struct
{
  char mahp[10];
  char tenhp[50];
  lllop dslop;
} hocphan;

struct nodehp
{
  hocphan hp;
  nodehp *next;
};
typedef struct nodehp *pnodehp;
typedef struct nodehp *llhp;

// Khoi tao danh sach lien ket giang vien - lop hoc
struct nodelk
{
  pnodehp hp;
  pnodelh lh;
  nodelk *next;
};
typedef struct nodelk *pnodelk;
typedef struct nodelk *lllk;

// Khoi tao danh sach giang vien
typedef struct
{
  char magv[10];
  char tengv[50];
  lllk lop;
} giangvien;

struct nodegv
{
  giangvien gv;
  nodegv *next;
};
typedef struct nodegv *pnodegv;
typedef struct nodegv *llgv;

// Goc danh sach hoc phan
llhp dshp;

// Goc danh sach giang vien
llgv dsgv;

// Ham sua loi xuong dong do input, loai bo ki tu \n
void fix(char *str) 
{
  int k = strlen(str);
  if (str[k - 1] == '\n')
    str[k - 1] = '\0';
}

// Tim hoc phan qua ma hoc phan
pnodehp findhp(char *mahp) 
{
  pnodehp cur = dshp;
  for (; cur != NULL && strcmp(mahp, cur->hp.mahp) != 0; cur = cur->next)
    ;
  if (cur == NULL)
    return NULL;
  return cur;
}

 // Them hoc phan vao cuoi danh sach
void addhp(pnodehp P)
{
  pnodehp cur;
  if (dshp == NULL)
    dshp = P;
  else
  {
    for (cur = dshp; cur->next != NULL; cur = cur->next) //them P vao cuoi danh sach
      ;
    cur->next = P;
  }
}

// Nhap hoc phan tu file
void finputhp() 
{
  FILE *fhp = fopen("hp.txt", "r");
  if (fhp == NULL)
    return;
  while (!feof(fhp))
  {
    //tao mot node hoc phan P, roi doc tu file lay du lieu cho P
    pnodehp P = new nodehp;
    fscanf(fhp, "%s\t", P->hp.mahp);
    fgets(P->hp.tenhp, 50, fhp);
    fix(P->hp.tenhp);
    P->hp.dslop = NULL;
    P->next = NULL;
    addhp(P);   //them hoc phan P vao cuoi danh sach hoc phan
  }
  fclose(fhp);
}

// Luu hoc phan vao file
void savehp() 
{
  FILE *fhp = fopen("hp.txt", "w+");
  pnodehp cur = dshp;
  while (cur != NULL)
  {
    fprintf(fhp, "%s\t%s", cur->hp.mahp, cur->hp.tenhp);
    cur = cur->next;
    if (cur != NULL)
      fprintf(fhp, "\n");
  }
  fclose(fhp);
}

// Nhap hoc phan tu ban phim
void inputhp() 
{
  int n; //So hoc phan muon them vao
  printf("So hoc phan muon them: ");
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
  {
    //tao mot hoc phan moi bang cach nhap tu ban phim
    pnodehp P = new nodehp;
    do
    { //kiem tra nguoi dung co nhap ma hoc phan moi hay khong
      printf("Nhap ma hoc phan: ");
      fflush(stdin);
      scanf("%s", P->hp.mahp);
      if (findhp(P->hp.mahp) != NULL)
        printf("Ma hoc phan da ton tai. Vui long nhap lai.\n");
      else
        break;
    } while (1);
    printf("Nhap ten hoc phan: ");
    fflush(stdin);
    fgets(P->hp.tenhp, 50, stdin);
    fix(P->hp.tenhp);
    P->hp.dslop = NULL;
    P->next = NULL;
    addhp(P); //them hoc phan moi vao cuoi danh sach hoc phan
    printf("\n");
  }
  savehp();
}

// Tim giang vien qua ma giang vien
pnodegv findgv(char *magv) 
{
  pnodegv cur = dsgv;
  for (; cur != NULL && strcmp(magv, cur->gv.magv) != 0; cur = cur->next)
    ;
  if (cur == NULL)
    return NULL;
  return cur;
}

// Them giang vien vao cuoi danh sach
void addgv(pnodegv P) 
{
  pnodegv cur;
  if (dsgv == NULL)
    dsgv = P;
  else
  {
    for (cur = dsgv; cur->next != NULL; cur = cur->next); //them giang vien moi vao cuoi danh sach
    cur->next = P;
  }
}

// Nhap giang vien tu file
void finputgv() 
{
  FILE *fgv = fopen("gv.txt", "r");
  if (fgv == NULL)
    return;
  while (!feof(fgv))
  {
    //tao mot node giang vien moi, lay du lieu tu file
    pnodegv P = new nodegv;
    fscanf(fgv, "%s\t", P->gv.magv);
    fgets(P->gv.tengv, 50, fgv);
    fix(P->gv.tengv);
    P->gv.lop = NULL;
    P->next = NULL;
    addgv(P);   //them node giang vien moi vao cuoi danh sach
  }
  fclose(fgv);
}

// Luu giang vien vao file
void savegv() 
{
  FILE *fgv = fopen("gv.txt", "w+");
  pnodegv cur = dsgv;
  while (cur != NULL)
  {
    fprintf(fgv, "%s\t%s", cur->gv.magv, cur->gv.tengv);
    cur = cur->next;
    if (cur != NULL)
      fprintf(fgv, "\n");
  }
  fclose(fgv);
}

// Nhap giang vien tu ban phim
void inputgv() 
{
  int n; //so giang vien them moi
  printf("So giang vien: ");
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
  {
    //tao mot node giang vien moi bang cach nhap tu ban phim
    pnodegv P = new nodegv;
    do
    {
      //kiem tra xem nguoi dung nhap ma giang vien moi hay khong 
      printf("Nhap ma giang vien: ");
      fflush(stdin);
      scanf("%s", P->gv.magv);
      if (findgv(P->gv.magv) != NULL)
        printf("Ma giang vien da ton tai. Vui long nhap lai.\n");
      else
        break;
    } while (1);
    printf("Nhap ten giang vien: ");
    fflush(stdin);
    fgets(P->gv.tengv, 50, stdin);
    fix(P->gv.tengv);
    P->gv.lop = NULL;
    P->next = NULL;
    addgv(P); //them giang vien vao cuoi danh
    printf("\n");
  }
  savegv();
}

// Tim hoc phan dua tren ma lop
pnodehp findhplh(char *malop) 
{
  pnodehp curhp = dshp;
  pnodelh curlh;
  while (curhp != NULL)
  {
    for (curlh = curhp->hp.dslop; curlh != NULL && strcmp(malop, curlh->lh.malop) != 0; curlh = curlh->next)
      ;
    if (curlh != NULL)
      return curhp;
    curhp = curhp->next;
  }
  return NULL;
}

 // Tim lop hoc theo ma lop
pnodelh findlh(char *malop)
{
  pnodelh curlh;
  pnodehp curhp = findhplh(malop);
  if (curhp == NULL)
    return NULL;
  for (curlh = curhp->hp.dslop; curlh != NULL && strcmp(malop, curlh->lh.malop) != 0; curlh = curlh->next)
    ;
  if (curlh != NULL)
    return curlh;
  return NULL;
}

 // Tao lien ket giang vien - lop hoc
void link(pnodegv *listgv, int n, pnodehp Q, pnodelh P)
{
  pnodelk cur;
  for (int i = 0; i < n; i++)   //n la so giang vien cua lop
  {
    pnodelk S = new nodelk;
    S->hp = Q;
    S->lh = P;
    S->next = NULL;
    //lien ket giang vien vao lop hoc (them thong tin giang vien vao lop hoc)
    P->lh.gv[i] = listgv[i];
    //lien ket lop hoc voi giang vien (them thong tin lop hoc vao giang vien)
    if (listgv[i]->gv.lop == NULL)
      listgv[i]->gv.lop = S;
    else
    {
      for (cur = listgv[i]->gv.lop; cur->next != NULL; cur = cur->next)   //them lop hoc vao cuoi danh sach lop giang day cua giang vien
        ;
      cur->next = S;
    }
  }
  P->lh.gv[n] = NULL;
}

// Them lop hoc vao danh sach
void addlh(char mahp[10], pnodegv *listgv, int n, pnodelh P) 
{
  pnodehp Q = dshp;
  //tim den hoc phan co ma hoc phan cho truoc
  while (Q != NULL)
  {
    if (strcmp(Q->hp.mahp, mahp) == 0)
      break;
    else
      Q = Q->next;
  }
  if (Q == NULL)
    return;
  pnodelh cur;
  if (Q->hp.dslop == NULL)
    Q->hp.dslop = P;    //neu hoc phan chua co lop hoc thi lop hoc dau tien chinh la pnodelh P
  else
  {
    for (cur = Q->hp.dslop; cur->next != NULL; cur = cur->next) //them lop hoc vao cuoi danh sach
      ;
    cur->next = P;
  }
  link(listgv, n, Q, P);  //tao lien ket giang vien - lop hoc, thuong khi khoi tao lop hoc moi thi chua co lien ket nen n (so giang vien) va listgv se rong
}

// Nhap lop hoc tu file
void finputlh() 
{
  FILE *flp = fopen("lh.txt", "r");
  if (flp == NULL)
    return;
  while (!feof(flp))
  {
    //them moi lop hoc, lay du lieu tu file
    pnodelh P = new nodelh;
    char mahp[10];
    char magv[10];
    pnodegv listgv[5];
    fscanf(flp, "%s", P->lh.malop);
    fscanf(flp, "%s", mahp);
    fscanf(flp, "%d", &(P->lh.thu));
    fscanf(flp, "%d", &(P->lh.bd));
    fscanf(flp, "%d", &(P->lh.kt));
    fscanf(flp, "%s", P->lh.diadiem);
    char c = fgetc(flp);
    int i = 0;    //so giang vien cua lop hoc
    while ((c != '\n') && (!feof(flp)))
    {
      fscanf(flp, "%s", magv);
      listgv[i++] = findgv(magv);
      c = fgetc(flp);
    }
    P->next = NULL;
    addlh(mahp, listgv, i, P);  //them moi lop hoc vao cuoi danh sach
  }
  fclose(flp);
}

// Luu lop hoc vao file
void savelh() 
{
  FILE *flh = fopen("lh.txt", "w+");
  pnodehp curhp = dshp;
  bool flag = false;
  while (curhp != NULL)
  {
    pnodelh curlh = curhp->hp.dslop;
    while (curlh != NULL)
    {
      if (flag)
        fprintf(flh, "\n");
      else
        flag = true;
      fprintf(flh, "%s\t%s\t", curlh->lh.malop, curhp->hp.mahp);
      fprintf(flh, "%d\t%d\t%d\t", curlh->lh.thu, curlh->lh.bd, curlh->lh.kt);
      fprintf(flh, "%s", curlh->lh.diadiem);
      for (int i = 0; curlh->lh.gv[i] != NULL; i++)
        fprintf(flh, "\t%s", curlh->lh.gv[i]);
      curlh = curlh->next;
    }
    curhp = curhp->next;
  }
  fclose(flh);
}

 // Nhap lop hoc tu ban phim
void inputlh()
{
  int n;  //so lop hoc can them
  printf("So lop hoc: ");
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
  {
    //tao lop hoc moi, nhap du lieu tu ban phim
    pnodelh P = new nodelh;
    char mahp[10];
    do
    {
      //kiem tra xem ma lop nguoi dung nhap da ton tai chua
      printf("Nhap ma lop: ");
      fflush(stdin);
      scanf("%s", P->lh.malop);
      if (findhplh(P->lh.malop) != NULL)
        printf("Ma lop da ton tai. Vui long nhap lai.\n");
      else
        break;
    } while (1);
    do
    {
      //kiem tra dam bao ma hoc phan nguoi dung nhap phai la ma hoc phan da co, do danh sach lop nam trong danh sach hoc phan nen phai co hoc phan truoc
      printf("Nhap ma hoc phan: ");
      fflush(stdin);
      scanf("%s", mahp);
      if (findhp(mahp) == NULL)
        printf("Ma hoc phan khong ton tai. Vui long nhap lai.\n");
      else
        break;
    } while (1);
    printf("Thu: ");
    scanf("%d", &(P->lh.thu));
    printf("Tiet hoc bat dau: ");
    scanf("%d", &(P->lh.bd));
    printf("Tiet hoc ket thuc: ");
    scanf("%d", &(P->lh.kt));
    printf("Dia diem: ");
    fflush(stdin);
    scanf("%s", P->lh.diadiem);
    P->next = NULL;
    addlh(mahp, NULL, 0, P);    // them lop hoc vao cuoi danh sach
    printf("\n");
    savelh();
  }
}

//in cac thong tin
void printinfohp(pnodehp P)
{
  printf("Ma hoc phan: %s\n", P->hp.mahp);
  printf("Ten hoc phan: %s\n", P->hp.tenhp);
}

void printinfogv(pnodegv P)
{
  printf("Ma giang vien: %s\n", P->gv.magv);
  printf("Ten giang vien: %s\n", P->gv.tengv);
}

void printinfolh(pnodelh P)
{
  printf("Ma lop hoc: %s\n", P->lh.malop);
  printf("Thu: %d\n", P->lh.thu);
  printf("Tiet bat dau: %d\n", P->lh.bd);
  printf("Tiet ket thuc: %d\n", P->lh.kt);
  printf("Dia diem: %s\n", P->lh.diadiem);
}

//in thong tin lop hoc
void printlh(pnodelh P)
{
  printinfohp(findhplh(P->lh.malop));
  printinfolh(P);
  if (P->lh.gv != NULL)
    for (int i = 0; P->lh.gv[i] != NULL; i++)
      printinfogv(P->lh.gv[i]);
  printf("\n");
}

//in thong tin giang vien
void printgv(pnodegv P)
{
  printinfogv(P);
  pnodelk Q = P->gv.lop;
  if (Q != NULL)
  {
    printf("Danh sach lop giang vien day:\n");
    while (Q != NULL)
    {
      printinfohp(Q->hp);
      printinfolh(Q->lh);
      printf("\n");
      Q = Q->next;
    }
  }
  else
    printf("\n");
}

//in thong tin hoc phan
void printhp(pnodehp P)
{
  printinfohp(P);
  pnodelh Q = P->hp.dslop;
  if (Q != NULL)
  {
    printf("Danh sach lop:\n");
    while (Q != NULL)
    {
      printinfolh(Q);
      printf("\n");
      Q = Q->next;
    }
  }
  else
    printf("\n");
}

// Khoi tao danh sach tu file
void init() 
{
  dshp = NULL;
  dsgv = NULL;
  finputhp();
  finputgv();
  finputlh();
}

// Luu toan bo du lieu vao file
void save() 
{
  savehp();
  savegv();
  savelh();
} 

// Chuc nang 1: them moi thong tin
void func1() 
{
  char option;
  printf("\nThem moi thong tin\n");
  printf("\t1. Them moi thong tin lop hoc\n");
  printf("\t2. Them moi thong tin hoc phan\n");
  printf("\t3. Them moi thong tin giang vien\n");
  do
  {
    printf("\nChon chuc nang: ");
    fflush(stdin);
    option = getchar();
    if (option < '1' || option > '3')
      printf("Chuc nang khong hop le. Vui long nhap lai.\n");
  } while (option < '1' || option > '3');
  switch (option)
  {
  case '1':
    inputlh();    //nhap lop hoc tu ban phim
    break;
  case '2':
    inputhp();    //nhap hoc phan tu ban phim
    break;
  case '3':
    inputgv();    //nhap giang vien tu ban phim
  }
}

// Phan cong giang vien giang day
void func2() 
{
  int n, m;   //n la so lop can phan cong, m la so giang vien phan cong
  char malop[10];
  char magv[10];
  pnodelh P;
  pnodegv listgv[5];
  printf("\nPhan cong giang vien\n");
  printf("So lop can phan cong: ");
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
  {
    do
    {
      //kiem tra ma lop nguoi dung nhap co ton tai khong
      printf("Nhap ma lop: ");
      scanf("%s", malop);
      P = findlh(malop);
      if (P == NULL)
        printf("Ma lop khong ton tai. Vui long nhap lai.\n");
      else
        break;
    } while (1);
    printf("So giang vien: ");
    scanf("%d", &m);
    for (int j = 0; j < m; j++)
    {
      do
      {
        //kiem tra ma giang vien nguoi dung nhap co ton tai khong
        printf("Nhap ma giang vien %d: ", j + 1);
        scanf("%s", magv);
        listgv[j] = findgv(magv);
        if (listgv[j] == NULL)
          printf("Ma giang vien khong ton tai. Vui long nhap lai.\n");
        else
          break;
      } while (1);
    }
    link(listgv, m, findhplh(malop), P);  //thuc hien lien ket giang vien - lop hoc
  }
  savelh();
}

//chuc nang 3: in thong tin
void func3()
{
  char option;
  printf("\nIn thong tin\n");
  printf("\t1. In thong tin lop hoc\n");
  printf("\t2. In thong tin hoc phan\n");
  printf("\t3. In thong tin giang vien\n");
  do
  {
    printf("\nChon chuc nang: ");
    fflush(stdin);
    option = getchar();
    if (option < '1' || option > '3')
      printf("Chuc nang khong hop le. Vui long nhap lai.\n");
  } while (option < '1' || option > '3');
  switch (option)
  {
  case '1':
    for (pnodehp P = dshp; P != NULL; P = P->next)
      for (pnodelh Q = P->hp.dslop; Q != NULL; Q = Q->next)
        printlh(Q);
    break;
  case '2':
    for (pnodehp P = dshp; P != NULL; P = P->next)
      printhp(P);
    break;
  case '3':
    for (pnodegv P = dsgv; P != NULL; P = P->next)
      printgv(P);
  }
}

//xoa thong tin lop
void deletelop(pnodelh P){
  pnodehp Q = findhplh(P->lh.malop);
  if (Q->hp.dslop == P) //truong hop P la phan tu dau danh sach lop hoc trong hoc phan Q
  {
    Q->hp.dslop = P->next;
  }
  else
  {
    pnodelh curlh = Q->hp.dslop;
    while (curlh->next != P )
    {
      curlh = curlh->next;
    }
    curlh->next = P->next;  //tao lien ket moi, curlh luc nay la pnodelh o truoc P, lien ket voi pnodelh sau P, bo qua P
  }
  for (int i = 0; P->lh.gv[i] != NULL; i++)   //xoa lien ket giang vien voi lop hoc
  {
    pnodelk R = P->lh.gv[i]->gv.lop;
    if (R->lh == P)   //neu P la pnodelh dau tien trong ds lop cua giang vien
    {
      P->lh.gv[i]->gv.lop = R->next;    //tao lien ket moi de xoa phan tu dau
    }
    else
    {
      while (R->next->lh != P)    //tim den phan tu lop hoc truoc P trong danh sach lop giang vien giang day
      {
        R = R->next;
      }
      pnodelk S = R;
      R = R->next;
      S->next = R->next;    //tao lien ket moi de xoa lien ket
    }
    delete(R);    //xoa lop trong danh sach lop giang vien giang day
  }
  delete(P);    //xoa lop
}

//chuc nang 4: Xoa thong tin lop
void func4()
{
  char malop[10];
  pnodelh P;
  printf("Xoa lop\n");
  printf("Nhap ma lop can xoa: ");
  scanf("%s",malop);
  P = findlh(malop);
  if (P == NULL)
  {
    printf("Ma lop khong ton tai.\n");
    return;
  }
  deletelop(P);
  savelh();
}

//chuc nang 5: tim kiem thong tin
void func5() {
  char option;
  printf("\nIn thong tin\n");
  printf("\t1. Tim kiem thong tin lop hoc\n");
  printf("\t2. Tim kiem thong tin hoc phan\n");
  printf("\t3. Tim kiem thong tin giang vien\n");
  do
  {
    printf("\nChon chuc nang: ");
    fflush(stdin);
    option = getchar();
    if (option < '1' || option > '3')
      printf("Chuc nang khong hop le. Vui long nhap lai.\n");
  } while (option < '1' || option > '3');
  switch (option)
  {
  case '1':{
    //tim kiem thong tin lop dua vao ma lop, su dung ham findlh da co tu tren
    char malop[10];
    pnodelh curlh;
    printf("Nhap ma lop hoc can tim: ");
    fflush(stdin);
    scanf("%s", malop);
    curlh = findlh(malop);
    if (curlh == NULL)
    {
        printf("Khong tim thay lop hoc.\n");
        return;
    }
    else printlh(curlh);
    break;    
  }
  case '2': {
    //tim kiem thong tin hoc phan dua vao ma hp, su dung ham findhp da co tu tren
    char mahp[10];
    pnodehp curhp;
    printf("Nhap ma hoc phan can tim: ");
    fflush(stdin);
    scanf("%s", mahp);
    curhp = findhp(mahp);
    if (curhp == NULL) 
    {
      printf("Khong tim thay hoc phan.\n");
      return;
    }
    else printhp(curhp);
    break;
  }
  case '3': {
    //tim kiem thong tin giang vien da co dua vao ma gv, su dung ham findgv da co tu tren
    char magv[10];
    pnodegv curgv;
    printf("Nhap ma gv can tim: ");
    fflush(stdin);
    scanf("%s", magv);
    curgv = findgv(magv);
    if (curgv == NULL)
    {
      printf("Khong tim thay giang vien.\n");
      return;
    }
    else printgv(curgv);
    break;
  }
  }
}

//sap xep hoc phan theo ma hoc phan
void swaphp(pnodehp &P, pnodehp &Q)
{
	pnodehp temp = new nodehp;
	temp->hp = P->hp;
	P->hp = Q->hp;
	Q->hp = temp->hp;
}
void sapxephp()
{
	if(dshp == NULL) return;
	pnodehp P, Q;
	for (P = dshp; P != NULL; P = P->next){
		for (Q = P->next; Q != NULL; Q = Q->next){
			if(strcmp(P->hp.mahp, Q->hp.mahp) > 0) swaphp(P,Q);
    }
  }
}

//sap xep giang vien theo ma giang vien
void swapgv(pnodegv &P, pnodegv &Q)
{
  giangvien temp = P->gv;
  P->gv = Q->gv; 
  Q->gv = temp;
}
void sapxepgv()
{
  if(dsgv == NULL) return;
  pnodegv P,Q;
  for (P = dsgv; P != NULL; P = P->next)
  {
    for(Q = P->next; Q != NULL; Q = Q->next)
    {
      if(strcmp(P->gv.magv, Q->gv.magv) > 0) swapgv(P, Q);
    }
  }
}


//ham sap xep thong tin danh sach hoc phan theo thu tu bang chu cai
void func6(){
  char option;
  printf("\nSap xep thong tin\n");
  printf("\t1. Sap xep thong tin hoc phan theo ma hoc phan\n");
  printf("\t2. Sap xep thong tin giang vien theo ma giang vien\n");
  do
  {
    printf("\nChon chuc nang: ");
    fflush(stdin);
    option = getchar();
    if (option < '1' || option > '2')
      printf("Chuc nang khong hop le. Vui long nhap lai.\n");
  } while (option < '1' || option > '2');
  switch (option)
  {
  case '1':
  {
	  sapxephp();
	  savehp();
    printf("Da sap xep xong !\n");
    break;
  }
  case '2':
  {
    sapxepgv();
	  savegv();
    printf("Da sap xep xong !\n");
    break;
  }
  }
}
//luu thong tin vao file
void func7() {
  save();
  printf("Da luu !\n");
}

//menu chuong trinh
void menu()
{
  char option;
  printf("\nPHAN CONG GIANG DAY CHO GIANG VIEN:");
  printf("\nMENU\n");
  printf("\t1. Them moi thong tin\n");
  printf("\t2. Phan cong giang vien\n");
  printf("\t3. In thong tin\n");
  printf("\t4. Xoa lop\n");
  printf("\t5. Tim kiem thong tin\n");
  printf("\t6. Sap xep thong tin\n");
  printf("\t7. Luu thong tin\n");
  printf("\t8. Thoat chuong trinh\n\n");
  do
  {
    printf("Chon chuc nang: ");
    fflush(stdin);
    option = getchar();
    if (option < '1' || option > '8')
      printf("Chuc nang khong hop le. Vui long nhap lai.\n");
  } while (option < '1' || option > '8');
  switch (option)
  {
  case '1':
    func1();
    break;
  case '2':
    func2();
    break;
  case '3':
    func3();
    break;
  case '4':
    func4();
    break;
  case '5':
    func5();
    break;
  case '6':
    func6();
    break;
  case '7':
    func7();
  break;
  case '8':
    exit(0);
  }
}

int main()
{
  init();
  while (1)
    menu();
  return 0;
}


