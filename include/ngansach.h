#ifndef NGANSACH_H
#define NGANSACH_H

#include "tienich.h"

#define TEN_FILE_NGANSACH "data/ngansach.txt"

/* Cau truc luu han muc ngan sach cho 1 danh muc trong 1 thang,
   dong thoi la 1 nut cua danh sach lien ket don */
typedef struct NganSach {
    char   danhMuc[DO_DAI_DANHMUC];
    int    thang, nam;
    double hanMuc;
    struct NganSach *tiep;
} NganSach;

void      ThietLapNganSach(NganSach **dauDS);
void      XoaNganSach(NganSach **dauDS);
NganSach* TimNganSach(NganSach *dauDS, const char *danhMuc, int thang, int nam);

int  DemSoNganSach(const NganSach *dauDS);
void InDanhSachNganSach(const NganSach *dauDS);
void GiaiPhongNganSach(NganSach **dauDS);

/* Ham cong khai de taodata dung: them nut da cap phat san vao cuoi DS */
void ThemNganSachTruc(NganSach **dauDS, NganSach *ns);

/* Lay danh sach cac ten danh muc duy nhat tu toan bo DS ngan sach.
   Tra ve so luong danh muc tim duoc (toi da soToiDa phan tu). */
int LayDanhMucDuy(const NganSach *dauDS, char ketQua[][DO_DAI_DANHMUC], int soToiDa);

int DocFileNganSach(NganSach **dauDS);
int GhiFileNganSach(const NganSach *dauDS);

#endif
