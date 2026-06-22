#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "taodata.h"

/* ===== Ham tro giup noi bo ===== */

/* Nhiem vu : Cap phat va dien thong tin cho 1 GiaoDich mau, roi them vao DS.
              Dung ThemGiaoDichTruc thay vi viet lai logic chen cuoi.
   Dau vao  : ds - dia chi dau DS; cac truong du lieu
   Dau ra   : khong co */
static void ThemGDMau(GiaoDich **ds, int id, int ng, int th, int nam,
                      const char *loai, const char *dm,
                      double tien, const char *gc) {
    GiaoDich *gd = (GiaoDich*) malloc(sizeof(GiaoDich));
    if (gd == NULL) { printf("Loi: khong du bo nho khi tao du lieu mau.\n"); return; }

    gd->id    = id;
    gd->ngay  = ng;
    gd->thang = th;
    gd->nam   = nam;
    strncpy(gd->loai,    loai, DO_DAI_LOAI    - 1); gd->loai[DO_DAI_LOAI    - 1] = '\0';
    strncpy(gd->danhMuc, dm,   DO_DAI_DANHMUC - 1); gd->danhMuc[DO_DAI_DANHMUC - 1] = '\0';
    gd->soTien = tien;
    strncpy(gd->ghiChu,  gc,   DO_DAI_GHICHU  - 1); gd->ghiChu[DO_DAI_GHICHU  - 1] = '\0';
    gd->tiep = NULL;

    ThemGiaoDichTruc(ds, gd); /* dung ham public -- khong lap lai logic chen cuoi */
}

/* Nhiem vu : Cap phat va dien thong tin cho 1 NganSach mau, roi them vao DS.
   Dau vao  : ds - dia chi dau DS ngan sach; cac truong du lieu
   Dau ra   : khong co */
static void ThemNSMau(NganSach **ds, const char *dm, int th, int nam, double han) {
    NganSach *ns = (NganSach*) malloc(sizeof(NganSach));
    if (ns == NULL) { printf("Loi: khong du bo nho khi tao du lieu mau.\n"); return; }

    strncpy(ns->danhMuc, dm, DO_DAI_DANHMUC - 1);
    ns->danhMuc[DO_DAI_DANHMUC - 1] = '\0';
    ns->thang  = th;
    ns->nam    = nam;
    ns->hanMuc = han;
    ns->tiep   = NULL;

    ThemNganSachTruc(ds, ns); /* dung ham public -- khong lap lai logic chen cuoi */
}

/* ==================================================================
   KICH BAN 1: Sinh vien - 3 thang (4-5-6/2025), thang 5 vuot ngan sach
   ================================================================== */
static void SinhKichBan1(GiaoDich **dsGD, NganSach **dsNS) {
    /* Thang 4/2025 */
    ThemGDMau(dsGD,  1,  1,4,2025,"Thu","Luong",      8000000,"Luong thang 4");
    ThemGDMau(dsGD,  2, 15,4,2025,"Thu","Phu cap",     500000,"Phu cap di lai");
    ThemGDMau(dsGD,  3, 20,4,2025,"Thu","Lam them",   1200000,"Gia su cuoi tuan");
    ThemGDMau(dsGD,  4,  2,4,2025,"Chi","An uong",      85000,"Com trua van phong");
    ThemGDMau(dsGD,  5,  3,4,2025,"Chi","An uong",     120000,"An toi voi ban");
    ThemGDMau(dsGD,  6,  5,4,2025,"Chi","Di chuyen",    50000,"Xe om di hoc");
    ThemGDMau(dsGD,  7,  7,4,2025,"Chi","Hoc tap",     350000,"Mua sach giao trinh");
    ThemGDMau(dsGD,  8, 10,4,2025,"Chi","An uong",     200000,"Sieu thi cuoi tuan");
    ThemGDMau(dsGD,  9, 12,4,2025,"Chi","Giai tri",    150000,"Xem phim");
    ThemGDMau(dsGD, 10, 14,4,2025,"Chi","Di chuyen",    80000,"Xang xe may");
    ThemGDMau(dsGD, 11, 16,4,2025,"Chi","Hoc tap",     500000,"Hoc phi khoa online");
    ThemGDMau(dsGD, 12, 18,4,2025,"Chi","An uong",      95000,"Cafe lam viec");
    ThemGDMau(dsGD, 13, 20,4,2025,"Chi","Sinh hoat",   200000,"Tien dien");
    ThemGDMau(dsGD, 14, 22,4,2025,"Chi","An uong",     180000,"An toi gia dinh");
    ThemGDMau(dsGD, 15, 25,4,2025,"Chi","Giai tri",    250000,"Sinh nhat ban");
    ThemGDMau(dsGD, 16, 27,4,2025,"Chi","Di chuyen",   120000,"Grab di ngoai thanh");
    ThemGDMau(dsGD, 17, 28,4,2025,"Chi","Sinh hoat",   150000,"Tien nuoc");
    ThemGDMau(dsGD, 18, 30,4,2025,"Chi","An uong",      90000,"Bua sang cuoi thang");
    /* Thang 5/2025 - chi nhieu, vuot ngan sach */
    ThemGDMau(dsGD, 19,  1,5,2025,"Thu","Luong",      8000000,"Luong thang 5");
    ThemGDMau(dsGD, 20, 10,5,2025,"Thu","Thuong",     1000000,"Thuong hoan thanh du an");
    ThemGDMau(dsGD, 21, 22,5,2025,"Thu","Lam them",    900000,"Freelance thiet ke");
    ThemGDMau(dsGD, 22,  2,5,2025,"Chi","An uong",     110000,"Com trua");
    ThemGDMau(dsGD, 23,  4,5,2025,"Chi","An uong",     320000,"Tiec cuoi ban");
    ThemGDMau(dsGD, 24,  6,5,2025,"Chi","Di chuyen",   200000,"Ve xe ve que");
    ThemGDMau(dsGD, 25,  8,5,2025,"Chi","An uong",     180000,"An uong ngay le");
    ThemGDMau(dsGD, 26, 10,5,2025,"Chi","Hoc tap",     800000,"Hoc phi hoc ky 2");
    ThemGDMau(dsGD, 27, 13,5,2025,"Chi","Giai tri",    300000,"Mua game Steam");
    ThemGDMau(dsGD, 28, 15,5,2025,"Chi","An uong",     250000,"BBQ cuoi tuan");
    ThemGDMau(dsGD, 29, 17,5,2025,"Chi","Di chuyen",    90000,"Xang xe may");
    ThemGDMau(dsGD, 30, 19,5,2025,"Chi","Sinh hoat",   220000,"Tien dien");
    ThemGDMau(dsGD, 31, 21,5,2025,"Chi","An uong",     130000,"Sieu thi");
    ThemGDMau(dsGD, 32, 23,5,2025,"Chi","Giai tri",    180000,"Karaoke");
    ThemGDMau(dsGD, 33, 25,5,2025,"Chi","An uong",      95000,"Cafe buoi sang");
    ThemGDMau(dsGD, 34, 27,5,2025,"Chi","Sinh hoat",   170000,"Tien nuoc + rac");
    ThemGDMau(dsGD, 35, 29,5,2025,"Chi","Hoc tap",     200000,"In an tai lieu");
    ThemGDMau(dsGD, 36, 31,5,2025,"Chi","An uong",     420000,"Tiet cuoi thang");
    /* Thang 6/2025 - hop ly, trong han muc */
    ThemGDMau(dsGD, 37,  1,6,2025,"Thu","Luong",      8500000,"Luong thang 6 tang");
    ThemGDMau(dsGD, 38,  5,6,2025,"Thu","Lam them",    600000,"Day kem cuoi tuan");
    ThemGDMau(dsGD, 39,  1,6,2025,"Chi","An uong",     100000,"Com trua dau thang");
    ThemGDMau(dsGD, 40,  3,6,2025,"Chi","Di chuyen",    60000,"Xe om di hoc");
    ThemGDMau(dsGD, 41,  5,6,2025,"Chi","Hoc tap",     450000,"Mua sach ky thuat");
    ThemGDMau(dsGD, 42,  7,6,2025,"Chi","An uong",     160000,"An toi voi nhom");
    ThemGDMau(dsGD, 43,  9,6,2025,"Chi","Sinh hoat",   210000,"Tien dien");
    ThemGDMau(dsGD, 44, 11,6,2025,"Chi","Giai tri",    120000,"Xem phim rap");
    ThemGDMau(dsGD, 45, 13,6,2025,"Chi","An uong",      85000,"Bua trua van phong");
    ThemGDMau(dsGD, 46, 15,6,2025,"Chi","Di chuyen",   100000,"Xang xe may");
    ThemGDMau(dsGD, 47, 17,6,2025,"Chi","An uong",     280000,"Hop nhom an toi");
    ThemGDMau(dsGD, 48, 19,6,2025,"Chi","Sinh hoat",   160000,"Tien nuoc");
    ThemGDMau(dsGD, 49, 21,6,2025,"Chi","Giai tri",    200000,"Sinh nhat ban than");
    ThemGDMau(dsGD, 50, 23,6,2025,"Chi","An uong",      75000,"Cafe sang");
    /* Ngan sach: thang 5 co 3 muc vuot */
    ThemNSMau(dsNS,"An uong",  5,2025, 600000); /* thuc chi ~1505k -> VUOT */
    ThemNSMau(dsNS,"Di chuyen",5,2025, 300000); /* thuc chi  290k  -> OK   */
    ThemNSMau(dsNS,"Hoc tap",  5,2025, 700000); /* thuc chi 1000k  -> VUOT */
    ThemNSMau(dsNS,"Giai tri", 5,2025, 400000); /* thuc chi  480k  -> VUOT */
    ThemNSMau(dsNS,"Sinh hoat",5,2025, 500000); /* thuc chi  390k  -> OK   */
    ThemNSMau(dsNS,"An uong",  6,2025, 800000);
    ThemNSMau(dsNS,"Di chuyen",6,2025, 300000);
    ThemNSMau(dsNS,"Hoc tap",  6,2025, 600000);
    ThemNSMau(dsNS,"Giai tri", 6,2025, 400000);
    ThemNSMau(dsNS,"Sinh hoat",6,2025, 500000);
    printf("  -> 50 giao dich, 10 ngan sach (3 thang: 4-5-6/2025)\n");
    printf("  -> Kiem thu canh bao vuot: Menu 8, thang 5/2025\n");
}

/* ==================================================================
   KICH BAN 2: Di lam full-time - 1 thang (1/2025), tat ca trong han muc
   ================================================================== */
static void SinhKichBan2(GiaoDich **dsGD, NganSach **dsNS) {
    ThemGDMau(dsGD,  1,  1,1,2025,"Thu","Luong",    15000000,"Luong thang 1");
    ThemGDMau(dsGD,  2,  1,1,2025,"Chi","Nha o",     3500000,"Thue phong thang 1");
    ThemGDMau(dsGD,  3,  3,1,2025,"Chi","An uong",    150000,"Sieu thi dau tuan");
    ThemGDMau(dsGD,  4,  5,1,2025,"Chi","Di chuyen",  200000,"The xe bus thang");
    ThemGDMau(dsGD,  5,  7,1,2025,"Chi","An uong",    180000,"Com trua 3 ngay");
    ThemGDMau(dsGD,  6, 10,1,2025,"Chi","Giai tri",   250000,"Goi Netflix");
    ThemGDMau(dsGD,  7, 12,1,2025,"Chi","An uong",    320000,"Tet Nguyen Dan");
    ThemGDMau(dsGD,  8, 15,1,2025,"Chi","Sinh hoat",  500000,"Dien + nuoc + rac");
    ThemGDMau(dsGD,  9, 18,1,2025,"Chi","An uong",    200000,"Sieu thi giua thang");
    ThemGDMau(dsGD, 10, 20,1,2025,"Chi","Giai tri",   150000,"Sach doc thang nay");
    ThemGDMau(dsGD, 11, 22,1,2025,"Chi","Di chuyen",   80000,"Xang xe may");
    ThemGDMau(dsGD, 12, 25,1,2025,"Chi","An uong",    280000,"An toi gia dinh");
    ThemGDMau(dsGD, 13, 28,1,2025,"Chi","Sinh hoat",  120000,"Mua do dung gia dinh");
    ThemNSMau(dsNS,"Nha o",    1,2025,4000000);
    ThemNSMau(dsNS,"An uong",  1,2025,1500000);
    ThemNSMau(dsNS,"Di chuyen",1,2025, 400000);
    ThemNSMau(dsNS,"Giai tri", 1,2025, 500000);
    ThemNSMau(dsNS,"Sinh hoat",1,2025, 800000);
    printf("  -> 13 giao dich, 5 ngan sach (thang 1/2025)\n");
    printf("  -> Tat ca danh muc nam trong han muc\n");
}

/* ==================================================================
   KICH BAN 3: Toi thieu - 2 ban ghi, kiem thu dieu kien bien
   ================================================================== */
static void SinhKichBan3(GiaoDich **dsGD, NganSach **dsNS) {
    ThemGDMau(dsGD, 1,15,3,2025,"Thu","Luong",  5000000,"Thu nhap duy nhat");
    ThemGDMau(dsGD, 2,20,3,2025,"Chi","An uong",4800000,"Chi tieu duy nhat");
    ThemNSMau(dsNS,"An uong",3,2025,3000000); /* VUOT: 4.8M > 3M */
    printf("  -> 2 giao dich, 1 ngan sach (thang 3/2025)\n");
    printf("  -> So du gan 0, 1 danh muc vuot manh\n");
}

/* ================================================================
   HAM CONG KHAI
   ================================================================ */

/* Nhiem vu : Hoi kich ban, xoa DS cu, sinh du lieu mau vao bo nho.
              Chi quan ly du lieu trong bo nho -- viec ghi file do main dam nhiem.
   Dau vao  : dsGD, dsNS - dia chi con tro cac DS
   Dau ra   : khong co */
void TaoDuLieuMau(GiaoDich **dsGD, NganSach **dsNS) {
    printf("\n========== TAO DU LIEU MAU ==========\n");
    printf("Cac kich ban co san:\n");
    printf("  1. Sinh vien  - 3 thang (4-5-6/2025), 50 GD, co muc VUOT ngan sach\n");
    printf("  2. Di lam FT  - 1 thang (1/2025), 13 GD, tat ca OK\n");
    printf("  3. Toi thieu  - 2 GD (kiem thu dieu kien bien)\n");
    printf("  0. Huy\n");
    printf("=====================================\n");

    int kb = NhapSoNguyen("Chon kich ban (0-3): ", 0, 3);
    if (kb == 0) { printf("Da huy.\n"); return; }

    int soGD = DemSoGiaoDich(*dsGD);
    int soNS = DemSoNganSach(*dsNS);
    if (soGD > 0 || soNS > 0) {
        printf("\nCANH BAO: Hien co %d giao dich va %d ngan sach.\n", soGD, soNS);
        printf("Du lieu nay SE BI XOA va thay bang du lieu mau.\n");
        if (!NhapSoNguyen("Xac nhan? (1=co, 0=khong): ", 0, 1)) {
            printf("Da huy.\n"); return;
        }
    }

    GiaiPhongDanhSach(dsGD);
    GiaiPhongNganSach(dsNS);
    printf("\nDang sinh du lieu kich ban %d...\n", kb);

    switch (kb) {
        case 1: SinhKichBan1(dsGD, dsNS); break;
        case 2: SinhKichBan2(dsGD, dsNS); break;
        case 3: SinhKichBan3(dsGD, dsNS); break;
    }

    printf("Du lieu da san sang trong bo nho. Chon 0 de luu xuong file.\n");
    printf("=====================================\n");
}