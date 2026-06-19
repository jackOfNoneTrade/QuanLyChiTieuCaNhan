#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ngansach.h"

/* ===== Ham noi bo (static) ===== */
static void InMotNganSach(const NganSach *ns);

static void InMotNganSach(const NganSach *ns) {
    printf("%-15s %02d/%-7d %.2f\n", ns->danhMuc, ns->thang, ns->nam, ns->hanMuc);
}

/* ================================================================
   HAM CONG KHAI -- CHEN VAO CUOI DS
   Dung boi: ThietLapNganSach (noi bo) va ThemNganSachTruc (taodata)
   ================================================================ */

/* Nhiem vu : Them nut da duoc cap phat san vao cuoi danh sach ngan sach.
   Dau vao  : dauDS - dia chi con tro dau; ns - nut can chen
   Dau ra   : khong co */
void ThemNganSachTruc(NganSach **dauDS, NganSach *ns) {
    if (*dauDS == NULL) { *dauDS = ns; return; }
    NganSach *p = *dauDS;
    while (p->tiep != NULL) p = p->tiep;
    p->tiep = ns;
}

/* ================================================================
   CRUD
   ================================================================ */

void ThietLapNganSach(NganSach **dauDS) {
    printf("\n--- THIET LAP NGAN SACH ---\n");

    char danhMuc[DO_DAI_DANHMUC];
    NhapChuoi("Danh muc can dat ngan sach: ", danhMuc, DO_DAI_DANHMUC);
    int thang    = NhapSoNguyen("Thang ap dung (1-12): ", 1, 12);
    int nam      = NhapSoNguyen("Nam ap dung (2000-2100): ", 2000, 2100);
    double hanMuc = NhapSoThuc("Han muc chi tieu (> 0): ", 0.01, 1000000000.0);

    /* Cap nhat neu da ton tai, them moi neu chua co */
    NganSach *ns = TimNganSach(*dauDS, danhMuc, thang, nam);
    if (ns != NULL) {
        ns->hanMuc = hanMuc;
        printf("Da cap nhat han muc cho '%s' thang %d/%d.\n", danhMuc, thang, nam);
        return;
    }

    ns = (NganSach*) malloc(sizeof(NganSach));
    if (ns == NULL) { printf("Loi: khong du bo nho.\n"); return; }
    strncpy(ns->danhMuc, danhMuc, DO_DAI_DANHMUC - 1);
    ns->danhMuc[DO_DAI_DANHMUC - 1] = '\0';
    ns->thang = thang;
    ns->nam   = nam;
    ns->hanMuc = hanMuc;
    ns->tiep   = NULL;
    ThemNganSachTruc(dauDS, ns);
    printf("Da dat ngan sach moi cho '%s' thang %d/%d.\n", danhMuc, thang, nam);
}

/* Tra ve ptr co the sua -- khong the const */
NganSach* TimNganSach(NganSach *dauDS, const char *danhMuc, int thang, int nam) {
    NganSach *p = dauDS;
    while (p != NULL) {
        if (strcmp(p->danhMuc, danhMuc) == 0 &&
            p->thang == thang && p->nam == nam) return p;
        p = p->tiep;
    }
    return NULL;
}

int DemSoNganSach(const NganSach *dauDS) {
    int dem = 0;
    const NganSach *p = dauDS;
    while (p != NULL) { dem++; p = p->tiep; }
    return dem;
}

void InDanhSachNganSach(const NganSach *dauDS) {
    if (dauDS == NULL) { printf("Chua co ngan sach nao duoc thiet lap.\n"); return; }
    printf("\n%-15s %-10s %s\n", "Danh muc", "Thang/Nam", "Han muc");
    printf("--------------------------------------\n");
    const NganSach *p = dauDS;
    while (p != NULL) { InMotNganSach(p); p = p->tiep; }
}

void GiaiPhongNganSach(NganSach **dauDS) {
    NganSach *p = *dauDS;
    while (p != NULL) { NganSach *tiep = p->tiep; free(p); p = tiep; }
    *dauDS = NULL;
}

/* ================================================================
   FILE I/O
   Format: danhMuc|thang|nam|hanMuc
   ================================================================ */

int DocFileNganSach(NganSach **dauDS) {
    FILE *f = fopen(TEN_FILE_NGANSACH, "r");
    if (f == NULL) return 0;

    char dong[200];
    int soDong = 0;
    while (fgets(dong, sizeof(dong), f) != NULL) {
        NganSach *ns = (NganSach*) malloc(sizeof(NganSach));
        if (ns == NULL) { printf("Loi: khong du bo nho khi doc file.\n"); break; }

        int soPhanTu = sscanf(dong, "%29[^|]|%d|%d|%lf",
                              ns->danhMuc, &ns->thang, &ns->nam, &ns->hanMuc);
        if (soPhanTu != 4) { free(ns); continue; }
        ns->tiep = NULL;
        ThemNganSachTruc(dauDS, ns);
        soDong++;
    }
    fclose(f);
    return soDong;
}

int GhiFileNganSach(const NganSach *dauDS) {
    FILE *f = fopen(TEN_FILE_NGANSACH, "w");
    if (f == NULL) { printf("Loi: khong the mo file %s de ghi.\n", TEN_FILE_NGANSACH); return 0; }

    const NganSach *p = dauDS;
    int soDong = 0;
    while (p != NULL) {
        fprintf(f, "%s|%d|%d|%.2f\n", p->danhMuc, p->thang, p->nam, p->hanMuc);
        soDong++;
        p = p->tiep;
    }
    fclose(f);
    return soDong;
}