#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "giaodich.h"

/* ===== Ham noi bo (static) ===== */
static void NhapLoai(char *loai);
static void NhapDanhMuc(char *danhMuc);
static void InMotGiaoDich(const GiaoDich *gd);

static void NhapLoai(char *loai) {
    while (1) {
        NhapChuoi("Loai giao dich (Thu/Chi): ", loai, DO_DAI_LOAI);
        if (strcmp(loai, "Thu") == 0 || strcmp(loai, "Chi") == 0) return;
        printf("Loi: chi nhap 'Thu' hoac 'Chi'.\n");
    }
}

static void NhapDanhMuc(char *danhMuc) {
    while (1) {
        NhapChuoi("Danh muc (vd: An uong, Luong, Hoc tap): ", danhMuc, DO_DAI_DANHMUC);
        if (strlen(danhMuc) > 0) return;
        printf("Loi: danh muc khong duoc de trong.\n");
    }
}

static void InMotGiaoDich(const GiaoDich *gd) {
    printf("[%3d] %02d/%02d/%04d  %-4s  %-14s  %10.2f  %s\n",
           gd->id, gd->ngay, gd->thang, gd->nam,
           gd->loai, gd->danhMuc, gd->soTien, gd->ghiChu);
}

/* ================================================================
   HAM CONG KHAI -- CHEN VAO CUOI DS
   Dung boi: ThemGiaoDich (noi bo) va ThemGiaoDichTruc (taodata)
   ================================================================ */

/* Nhiem vu : Them nut da duoc cap phat san vao cuoi danh sach.
              Ham public giup taodata.cpp tranh viet lai logic nay.
   Dau vao  : dauDS - dia chi con tro dau; gd - nut can chen
   Dau ra   : khong co */
void ThemGiaoDichTruc(GiaoDich **dauDS, GiaoDich *gd) {
    if (*dauDS == NULL) { *dauDS = gd; return; }
    GiaoDich *p = *dauDS;
    while (p->tiep != NULL) p = p->tiep;
    p->tiep = gd;
}

/* ================================================================
   CRUD
   ================================================================ */

void ThemGiaoDich(GiaoDich **dauDS) {
    printf("\n--- THEM GIAO DICH MOI ---\n");
    GiaoDich *gd = (GiaoDich*) malloc(sizeof(GiaoDich));
    if (gd == NULL) { printf("Loi: khong du bo nho.\n"); return; }

    gd->id = LayIDLonNhat(*dauDS) + 1;
    NhapNgay("Ngay giao dich", &gd->ngay, &gd->thang, &gd->nam);
    NhapLoai(gd->loai);
    NhapDanhMuc(gd->danhMuc);
    gd->soTien = NhapSoThuc("So tien (> 0): ", 0.01, 1000000000.0);
    NhapChuoi("Ghi chu (co the de trong): ", gd->ghiChu, DO_DAI_GHICHU);
    gd->tiep = NULL;

    ThemGiaoDichTruc(dauDS, gd);
    printf("Da them giao dich ID=%d thanh cong.\n", gd->id);
}

void SuaGiaoDich(GiaoDich *dauDS) {
    printf("\n--- SUA GIAO DICH ---\n");
    InDanhSachGiaoDich(dauDS);

    int id = NhapSoNguyen("Nhap ID giao dich can sua: ", 1, 2000000000);
    GiaoDich *gd = TimGiaoDich(dauDS, id);
    if (gd == NULL) { printf("Khong tim thay giao dich co ID=%d.\n", id); return; }

    printf("Thong tin cu:\n");
    InMotGiaoDich(gd);
    printf("Nhap thong tin moi (Enter de giu nguyen):\n");

    printf("Ngay hien tai: %02d/%02d/%04d\n", gd->ngay, gd->thang, gd->nam);
    if (!NhapSoNguyen("Giu nguyen ngay? (1=co, 0=doi): ", 0, 1))
        NhapNgay("Ngay moi", &gd->ngay, &gd->thang, &gd->nam);

    printf("Loai hien tai: %s\n", gd->loai);
    if (!NhapSoNguyen("Giu nguyen loai? (1=co, 0=doi): ", 0, 1))
        NhapLoai(gd->loai);

    printf("Danh muc hien tai: %s\n", gd->danhMuc);
    if (!NhapSoNguyen("Giu nguyen danh muc? (1=co, 0=doi): ", 0, 1))
        NhapDanhMuc(gd->danhMuc);

    printf("So tien hien tai: %.2f\n", gd->soTien);
    if (!NhapSoNguyen("Giu nguyen so tien? (1=co, 0=doi): ", 0, 1))
        gd->soTien = NhapSoThuc("So tien moi (> 0): ", 0.01, 1000000000.0);

    printf("Ghi chu hien tai: %s\n", gd->ghiChu);
    if (!NhapSoNguyen("Giu nguyen ghi chu? (1=co, 0=doi): ", 0, 1))
        NhapChuoi("Ghi chu moi: ", gd->ghiChu, DO_DAI_GHICHU);

    printf("Da cap nhat giao dich ID=%d.\n", id);
}

void XoaGiaoDich(GiaoDich **dauDS) {
    printf("\n--- XOA GIAO DICH ---\n");
    InDanhSachGiaoDich(*dauDS);

    int id = NhapSoNguyen("Nhap ID giao dich can xoa: ", 1, 2000000000);

    if (*dauDS != NULL && (*dauDS)->id == id) {
        GiaoDich *xoa = *dauDS;
        *dauDS = (*dauDS)->tiep;
        free(xoa);
        CapNhatIDTuanTu(*dauDS);   /* cap lai ID 1,2,3,... */
        printf("Da xoa giao dich ID=%d. ID da duoc cap nhat lai.\n", id);
        return;
    }

    GiaoDich *truoc = *dauDS;
    while (truoc != NULL && truoc->tiep != NULL) {
        if (truoc->tiep->id == id) {
            GiaoDich *xoa = truoc->tiep;
            truoc->tiep = xoa->tiep;
            free(xoa);
            CapNhatIDTuanTu(*dauDS);   /* cap lai ID 1,2,3,... */
            printf("Da xoa giao dich ID=%d. ID da duoc cap nhat lai.\n", id);
            return;
        }
        truoc = truoc->tiep;
    }
    printf("Khong tim thay giao dich co ID=%d.\n", id);
}

/* Tra ve ptr co the sua -- khong the const vi caller can sua nut tim duoc */
GiaoDich* TimGiaoDich(GiaoDich *dauDS, int id) {
    GiaoDich *p = dauDS;
    while (p != NULL) {
        if (p->id == id) return p;
        p = p->tiep;
    }
    return NULL;
}

/* ================================================================
   HAM TRO GIUP (chi doc -- tham so const)
   ================================================================ */

int LayIDLonNhat(const GiaoDich *dauDS) {
    int max = 0;
    const GiaoDich *p = dauDS;
    while (p != NULL) {
        if (p->id > max) max = p->id;
        p = p->tiep;
    }
    return max;
}

int DemSoGiaoDich(const GiaoDich *dauDS) {
    int dem = 0;
    const GiaoDich *p = dauDS;
    while (p != NULL) { dem++; p = p->tiep; }
    return dem;
}

void InDanhSachGiaoDich(const GiaoDich *dauDS) {
    if (dauDS == NULL) { printf("Chua co giao dich nao.\n"); return; }
    printf("\n%4s  %-10s  %-4s  %-14s  %10s  %s\n",
           "ID", "Ngay", "Loai", "Danh muc", "So tien", "Ghi chu");
    printf("----------------------------------------------------------------\n");
    const GiaoDich *p = dauDS;
    while (p != NULL) { InMotGiaoDich(p); p = p->tiep; }
    printf("----------------------------------------------------------------\n");
    printf("Tong so: %d giao dich.\n", DemSoGiaoDich(dauDS));
}

void GiaiPhongDanhSach(GiaoDich **dauDS) {
    GiaoDich *p = *dauDS;
    while (p != NULL) { GiaoDich *tiep = p->tiep; free(p); p = tiep; }
    *dauDS = NULL;
}

/* ================================================================
   FILE I/O
   Format: id|ngay|thang|nam|loai|danhMuc|soTien|ghiChu
   ================================================================ */

int DocFileGiaoDich(GiaoDich **dauDS) {
    FILE *f = fopen(TEN_FILE_GIAODICH, "r");
    if (f == NULL) return 0;

    char dong[300];
    int soDong = 0;
    while (fgets(dong, sizeof(dong), f) != NULL) {
        GiaoDich *gd = (GiaoDich*) malloc(sizeof(GiaoDich));
        if (gd == NULL) { printf("Loi: khong du bo nho khi doc file.\n"); break; }

        int soPhanTu = sscanf(dong,
            "%d|%d|%d|%d|%4[^|]|%29[^|]|%lf|%99[^\n]",
            &gd->id, &gd->ngay, &gd->thang, &gd->nam,
            gd->loai, gd->danhMuc, &gd->soTien, gd->ghiChu);

        if (soPhanTu < 7) { free(gd); continue; }
        if (soPhanTu == 7) gd->ghiChu[0] = '\0';
        gd->tiep = NULL;
        ThemGiaoDichTruc(dauDS, gd);
        soDong++;
    }
    fclose(f);
    return soDong;
}

int GhiFileGiaoDich(const GiaoDich *dauDS) {
    FILE *f = fopen(TEN_FILE_GIAODICH, "w");
    if (f == NULL) { printf("Loi: khong the mo file %s de ghi.\n", TEN_FILE_GIAODICH); return 0; }

    const GiaoDich *p = dauDS;
    int soDong = 0;
    while (p != NULL) {
        fprintf(f, "%d|%d|%d|%d|%s|%s|%.2f|%s\n",
                p->id, p->ngay, p->thang, p->nam,
                p->loai, p->danhMuc, p->soTien, p->ghiChu);
        soDong++;
        p = p->tiep;
    }
    fclose(f);
    return soDong;
}

/* ================================================================
   THONG KE (chi doc -- tham so const)
   ================================================================ */

double TinhTongTheoLoai(const GiaoDich *dauDS, const char *loai,
                        int ngay, int thang, int nam) {
    double tong = 0.0;
    const GiaoDich *p = dauDS;
    while (p != NULL) {
        int hopLoai  = (loai  == NULL || strcmp(p->loai,  loai)  == 0);
        int hopNgay  = (ngay  == 0    || p->ngay  == ngay);
        int hopThang = (thang == 0    || p->thang == thang);
        int hopNam   = (nam   == 0    || p->nam   == nam);
        if (hopLoai && hopNgay && hopThang && hopNam) tong += p->soTien;
        p = p->tiep;
    }
    return tong;
}

double TinhTongTheoDanhMuc(const GiaoDich *dauDS, const char *danhMuc,
                           int thang, int nam) {
    double tong = 0.0;
    const GiaoDich *p = dauDS;
    while (p != NULL) {
        if (strcmp(p->loai, "Chi") == 0 &&
            strcmp(p->danhMuc, danhMuc) == 0 &&
            p->thang == thang && p->nam == nam) {
            tong += p->soTien;
        }
        p = p->tiep;
    }
    return tong;
}

double TinhSoDu(const GiaoDich *dauDS, int thang, int nam) {
    return TinhTongTheoLoai(dauDS, "Thu", 0, thang, nam)
         - TinhTongTheoLoai(dauDS, "Chi", 0, thang, nam);
}

/* ================================================================
   CAP NHAT ID TUAN TU
   Sau khi xoa hoac sap xep, cap lai id = 1, 2, 3, ...
   theo thu tu hien tai cua danh sach.
   ================================================================ */

/* Nhiem vu : Di qua toan bo danh sach va gan lai id bat dau tu 1.
              Goi sau XoaGiaoDich hoac SapXepTheoSoTien de ID
              luon phan anh dung thu tu hien thi.
   Dau vao  : dauDS - dau danh sach (co the NULL)
   Dau ra   : khong co */
void CapNhatIDTuanTu(GiaoDich *dauDS) {
    int dem = 1;
    GiaoDich *p = dauDS;
    while (p != NULL) {
        p->id = dem++;
        p = p->tiep;
    }
}

/* ================================================================
   SAP XEP -- Selection Sort (sua du lieu, khong doi con tro)
   ================================================================ */

void SapXepTheoSoTien(GiaoDich *dauDS, int tangDan) {
    if (dauDS == NULL) return;
    for (GiaoDich *i = dauDS; i->tiep != NULL; i = i->tiep) {
        GiaoDich *chon = i;
        for (GiaoDich *j = i->tiep; j != NULL; j = j->tiep) {
            int doiCho = tangDan ? (j->soTien < chon->soTien)
                                 : (j->soTien > chon->soTien);
            if (doiCho) chon = j;
        }
        if (chon != i) {
            /* Khong hoan doi id -- id se duoc cap nhat lai tuyen tu
               bang CapNhatIDTuanTu() sau khi sort xong */
            int    tmpNgay  = i->ngay;    i->ngay  = chon->ngay;  chon->ngay  = tmpNgay;
            int    tmpThang = i->thang;   i->thang = chon->thang; chon->thang = tmpThang;
            int    tmpNam   = i->nam;     i->nam   = chon->nam;   chon->nam   = tmpNam;
            double tmpTien  = i->soTien;  i->soTien = chon->soTien; chon->soTien = tmpTien;

            char tmp[DO_DAI_DANHMUC > DO_DAI_GHICHU ? DO_DAI_DANHMUC : DO_DAI_GHICHU];

            strcpy(tmp, i->loai);    strcpy(i->loai,    chon->loai);    strcpy(chon->loai,    tmp);
            strcpy(tmp, i->danhMuc); strcpy(i->danhMuc, chon->danhMuc); strcpy(chon->danhMuc, tmp);
            strcpy(tmp, i->ghiChu);  strcpy(i->ghiChu,  chon->ghiChu);  strcpy(chon->ghiChu,  tmp);
        }
    }
}