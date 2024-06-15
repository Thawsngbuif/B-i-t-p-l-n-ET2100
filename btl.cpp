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
llhp hp;

// Goc danh sach giang vien
llgv gv;

void fix(char *str) // Ham sua loi xuong dong do input
{
  int k = strlen(str);
  if (str[k - 1] == '\n')
    str[k - 1] = '\0';
}

pnodehp findhp(char *mahp) // Tim hoc phan
{
  pnodehp cur = hp;
  for (; cur != NULL && strcmp(mahp, cur->hp.mahp) != 0; cur = cur->next)
    ;
  if (cur == NULL)
    return NULL;
  return cur;
}

void addhp(pnodehp P) // Them hoc phan vao danh sach
{
  pnodehp cur;
  if (hp == NULL)
    hp = P;
  else
  {
    for (cur = hp; cur->next != NULL; cur = cur->next)
      ;
    cur->next = P;
  }
}

void finputhp() // Nhap hoc phan tu file
{
  FILE *fhp = fopen("hp.txt", "r");
  if (fhp == NULL)
    return;
  while (!feof(fhp))
  {
    pnodehp P = new nodehp;
    fscanf(fhp, "%s\t", P->hp.mahp);
    fgets(P->hp.tenhp, 50, fhp);
    fix(P->hp.tenhp);
    P->hp.dslop = NULL;
    P->next = NULL;
    addhp(P);
  }
  fclose(fhp);
}

void savehp() // Luu hoc phan vao file
{
  FILE *fhp = fopen("hp.txt", "w+");
  pnodehp cur = hp;
  while (cur != NULL)
  {
    fprintf(fhp, "%s\t%s", cur->hp.mahp, cur->hp.tenhp);
    cur = cur->next;
    if (cur != NULL)
      fprintf(fhp, "\n");
  }
  fclose(fhp);
}

void inputhp() // Nhap hoc phan tu ban phim
{
  int n;
  printf("So hoc phan: ");
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
  {
    pnodehp P = new nodehp;
    do
    {
      printf("Ma hoc phan: ");
      fflush(stdin);
      scanf("%s", P->hp.mahp);
      if (findhp(P->hp.mahp) != NULL)
        printf("Ma hoc phan da ton tai. Vui long nhap lai.\n");
      else
        break;
    } while (true);
    printf("Ten hoc phan: ");
    fflush(stdin);
    fgets(P->hp.tenhp, 50, stdin);
    fix(P->hp.tenhp);
    P->hp.dslop = NULL;
    P->next = NULL;
    addhp(P);
    printf("\n");
  }
  savehp();
}

pnodegv findgv(char *magv) // Tim giao vien
{
  pnodegv cur = gv;
  for (; cur != NULL && strcmp(magv, cur->gv.magv) != 0; cur = cur->next)
    ;
  if (cur == NULL)
    return NULL;
  return cur;
}

void addgv(pnodegv P) // Them giao vien vao danh sach
{
  pnodegv cur;
  if (gv == NULL)
    gv = P;
  else
  {
    for (cur = gv; cur->next != NULL; cur = cur->next)
      ;
    cur->next = P;
  }
}

void finputgv() // Nhap giao vien tu file
{
  FILE *fgv = fopen("gv.txt", "r");
  if (fgv == NULL)
    return;
  while (!feof(fgv))
  {
    pnodegv P = new nodegv;
    fscanf(fgv, "%s\t", P->gv.magv);
    fgets(P->gv.tengv, 50, fgv);
    fix(P->gv.tengv);
    P->gv.lop = NULL;
    P->next = NULL;
    addgv(P);
  }
  fclose(fgv);
}

void savegv() // Luu giao vien vao file
{
  FILE *fgv = fopen("gv.txt", "w+");
  pnodegv cur = gv;
  while (cur != NULL)
  {
    fprintf(fgv, "%s\t%s", cur->gv.magv, cur->gv.tengv);
    cur = cur->next;
    if (cur != NULL)
      fprintf(fgv, "\n");
  }
  fclose(fgv);
}

void inputgv() // Nhap giao vien tu ban phim
{
  int n;
  printf("So giang vien: ");
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
  {
    pnodegv P = new nodegv;
    do
    {
      printf("Ma giang vien: ");
      fflush(stdin);
      scanf("%s", P->gv.magv);
      if (findgv(P->gv.magv) != NULL)
        printf("Ma giang vien da ton tai. Vui long nhap lai.\n");
      else
        break;
    } while (true);
    printf("Ten giang vien: ");
    fflush(stdin);
    fgets(P->gv.tengv, 50, stdin);
    fix(P->gv.tengv);
    P->gv.lop = NULL;
    P->next = NULL;
    addgv(P);
    printf("\n");
  }
  savegv();
}

pnodehp findhplh(char *malop) // Tim hoc phan dua tren ma lop
{
  pnodehp curhp = hp;
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

pnodelh findlh(char *malop) // Tim lop hoc
{
  pnodelh curlh;
  for (curlh = findhplh(malop)->hp.dslop; curlh != NULL && strcmp(malop, curlh->lh.malop) != 0; curlh = curlh->next)
    ;
  if (curlh != NULL)
    return curlh;
  return NULL;
}

void link(pnodegv *listgv, int n, pnodehp Q, pnodelh P) // Tao lien ket giang vien - lop hoc
{
  pnodelk cur;
  pnodelk S = new nodelk;
  S->hp = Q;
  S->lh = P;
  S->next = NULL;
  for (int i = 0; i < n; i++)
  {
    P->lh.gv[i] = listgv[i];
    if (listgv[i]->gv.lop == NULL)
      listgv[i]->gv.lop = S;
    else
    {
      for (cur = listgv[i]->gv.lop; cur->next != NULL; cur = cur->next)
        ;
      cur->next = S;
    }
  }
  P->lh.gv[n] = NULL;
}

void addlh(char mahp[10], pnodegv *listgv, int n, pnodelh P) // Them lop hoc vao danh sach
{
  pnodehp Q = hp;
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
    Q->hp.dslop = P;
  else
  {
    for (cur = Q->hp.dslop; cur->next != NULL; cur = cur->next)
      ;
    cur->next = P;
  }
  link(listgv, n, Q, P);
}

void finputlh() // Nhap lop hoc tu file
{
  FILE *flp = fopen("lh.txt", "r");
  if (flp == NULL)
    return;
  while (!feof(flp))
  {
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
    int i = 0;
    while ((c != '\n') && (!feof(flp)))
    {
      fscanf(flp, "%s", magv);
      listgv[i++] = findgv(magv);
      c = fgetc(flp);
    }
    P->next = NULL;
    addlh(mahp, listgv, i, P);
  }
  fclose(flp);
}

void savelh() // Luu lop hoc vao file
{
  FILE *flh = fopen("lh.txt", "w+");
  pnodehp curhp = hp;
  while (curhp != NULL)
  {
    pnodelh curlh = curhp->hp.dslop;
    while (curlh != NULL)
    {
      fprintf(flh, "%s\t%s\t", curlh->lh.malop, curhp->hp.mahp);
      fprintf(flh, "%d\t%d\t%d\t", curlh->lh.thu, curlh->lh.bd, curlh->lh.kt);
      fprintf(flh, "%s", curlh->lh.diadiem);
      for (int i = 0; curlh->lh.gv[i] != NULL; i++)
        fprintf(flh, "\t%s", curlh->lh.gv[i]);
      curlh = curlh->next;
      if (curhp->next != NULL && curhp->next->hp.dslop != NULL)
        fprintf(flh, "\n");
    }
    curhp = curhp->next;
  }
  fclose(flh);
}

void inputlh() // Nhap lop hoc tu ban phim
{
  int n;
  printf("So lop hoc: ");
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
  {
    pnodelh P = new nodelh;
    char mahp[10];
    do
    {
      printf("Ma lop: ");
      fflush(stdin);
      scanf("%s", P->lh.malop);
      if (findlh(P->lh.malop) != NULL)
        printf("Ma lop da ton tai. Vui long nhap lai.\n");
      else
        break;
    } while (true);
    do
    {
      printf("Ma hoc phan: ");
      fflush(stdin);
      scanf("%s", mahp);
      if (findhp(mahp) == NULL)
        printf("Ma hoc phan khong ton tai. Vui long nhap lai.\n");
      else
        break;
    } while (true);
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
    addlh(mahp, NULL, 0, P);
    printf("\n");
    savelh();
  }
}

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

void printlh(pnodelh P)
{
  printinfohp(findhplh(P->lh.malop));
  printinfolh(P);
  if (P->lh.gv != NULL)
    for (int i = 0; P->lh.gv[i] != NULL; i++)
      printinfogv(P->lh.gv[i]);
  printf("\n");
}

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

void init() // Khoi tao danh sach tu file
{
  hp = NULL;
  gv = NULL;
  finputhp();
  finputgv();
  finputlh();
}

void save() // Luu toan bo du lieu vao file
{
  savehp();
  savegv();
  savelh();
}

void func1() // Them moi thong tin
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
    inputlh();
    break;
  case '2':
    inputhp();
    break;
  case '3':
    inputgv();
  }
}

void func2() // Phan cong giang vien
{
  int n, m;
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
      printf("Ma lop: ");
      scanf("%s", malop);
      P = findlh(malop);
      if (P == NULL)
        printf("Ma lop khong ton tai. Vui long nhap lai.\n");
      else
        break;
    } while (true);
    printf("So giang vien: ");
    scanf("%d", &m);
    for (int j = 0; j < m; j++)
    {
      do
      {
        printf(" Ma giang vien %d: ", j + 1);
        scanf("%s", magv);
        listgv[j] = findgv(magv);
        if (listgv[j] == NULL)
          printf("Ma giang vien khong ton tai. Vui long nhap lai.\n");
        else
          break;
      } while (true);
    }
    link(listgv, m, findhplh(malop), P);
  }
  savelh();
}

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
    for (pnodehp P = hp; P != NULL; P = P->next)
      for (pnodelh Q = P->hp.dslop; Q != NULL; Q = Q->next)
        printlh(Q);
    break;
  case '2':
    for (pnodehp P = hp; P != NULL; P = P->next)
      printhp(P);
    break;
  case '3':
    for (pnodegv P = gv; P != NULL; P = P->next)
      printgv(P);
  }
}

void func4() {}
void func5() {}
void func6()
{
  save();
}

void menu()
{
  char option;
  printf("\nPHAN CONG GIANG DAY CHO GIANG VIEN:");
  printf("\nMENU\n");
  printf("\t1. Them moi thong tin\n");
  printf("\t2. Phan cong giang vien\n");
  printf("\t3. In thong tin\n");
  printf("\t4. Tim kiem lop\n");
  printf("\t5. Sap xep lop\n");
  printf("\t6. Luu thong tin\n");
  printf("\t7. Thoat chuong trinh\n\n");
  do
  {
    printf("Chon chuc nang: ");
    fflush(stdin);
    option = getchar();
    if (option < '1' || option > '7')
      printf("Chuc nang khong hop le. Vui long nhap lai.\n");
  } while (option < '1' || option > '7');
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
    exit(0);
  }
}

int main()
{
  init();
  while (true)
    menu();
  return 0;
}