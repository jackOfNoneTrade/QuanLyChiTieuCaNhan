#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ngansach.h"

/* Ham noi bo -- in thong tin 1 nut ngan sach kem so thu tu */
static void InMotNganSach(int stt, const NganSach *ns);

static void InMotNganSach(int stt, const NganSach *ns) {
    printf("[%2d] %-15s %02d/%-7d %.2f\n",
           stt, ns->danhMuc, ns->thang, ns->nam, ns->hanMuc);
}

/* Them nut da duoc cap phat san vao cuoi danh sach ngan sach.
   Dung boi ThietLapNganSach (noi bo) va ThemNganSachTruc (taodata). */
void ThemNganSachTruc(NganSach **dauDS, NganSach *ns) {
    if (*dauDS == NULL) { *dauDS = ns; return; }
    NganSach *p = *dauDS;
    while (p->tiep != NULL) p = p->tiep;
    p->tiep = ns;
}

/* Thiet lap ngan sach.
   Neu DS da co phan tu thi hien thi so thu tu, cho chon so de cap nhat
   hoac chon 0 de them moi. Neu DS rong hoac chon 0 thi nhap danh muc
   + thang + nam + han muc moi. */
void ThietLapNganSach(NganSach **dauDS) {
    printf("\n--- THIET LAP NGAN SACH ---\n");

    int soNS = DemSoNganSach(*dauDS);
    if (soNS > 0) {
        InDanhSachNganSach(*dauDS);
        printf("Nhap [0] de THEM MOI, hoac chon [1-%d] de CAP NHAT han muc: ", soNS);

        int chon = NhapSoNguyen("", 0, soNS);
        if (chon > 0) {
            NganSach *ns = *dauDS;
            for (int i = 1; i < chon; i++) ns = ns->tiep;
            double hanMucMoi = NhapSoThuc("Han muc moi (> 0): ", 0.01, 1000000000.0);
            ns->hanMuc = hanMucMoi;
            printf("Da cap nhat: '%s' thang %02d/%d -> %.2f\n",
                   ns->danhMuc, ns->thang, ns->nam, ns->hanMuc);
            return;
        }
    }

    /* Them moi */
    char danhMuc[DO_DAI_DANHMUC];
    NhapChuoi("Danh muc can dat ngan sach: ", danhMuc, DO_DAI_DANHMUC);
    int thang    = NhapSoNguyen("Thang ap dung (1-12): ", 1, 12);
    int nam      = NhapSoNguyen("Nam ap dung (2000-2100): ", 2000, 2100);
    double hanMuc = NhapSoThuc("Han muc chi tieu (> 0): ", 0.01, 1000000000.0);

    /* Phong truong hop nhap trung -- cap nhat neu (danh muc + thang + nam) da ton tai */
    NganSach *existing = TimNganSach(*dauDS, danhMuc, thang, nam);
    if (existing != NULL) {
        existing->hanMuc = hanMuc;
        printf("Da cap nhat han muc cho '%s' thang %02d/%d.\n", danhMuc, thang, nam);
        return;
    }

    NganSach *ns = (NganSach*) malloc(sizeof(NganSach));
    if (ns == NULL) { printf("Loi: khong du bo nho.\n"); return; }
    strncpy(ns->danhMuc, danhMuc, DO_DAI_DANHMUC - 1);
    ns->danhMuc[DO_DAI_DANHMUC - 1] = '\0';
    ns->thang  = thang;
    ns->nam    = nam;
    ns->hanMuc = hanMuc;
    ns->tiep   = NULL;
    ThemNganSachTruc(dauDS, ns);
    printf("Da dat ngan sach moi cho '%s' thang %02d/%d.\n", danhMuc, thang, nam);
}

/* Xoa mot ngan sach theo so thu tu hien thi.
   Hien thi danh sach co so thu tu, nguoi dung chon so can xoa.
   STT chi la bien dem trong vong lap khi in, khong luu trong struct,
   nen sau khi xoa, goi lai ham in se tu dong hien thi dung thu tu moi. */
void XoaNganSach(NganSach **dauDS) {
    printf("\n--- XOA NGAN SACH ---\n");
    if (*dauDS == NULL) { printf("Chua co ngan sach nao.\n"); return; }

    InDanhSachNganSach(*dauDS);
    int soNS = DemSoNganSach(*dauDS);
    int stt  = NhapSoNguyen("Chon so thu tu can xoa: ", 1, soNS);

    NganSach *xoa;
    if (stt == 1) {
        xoa    = *dauDS;
        *dauDS = (*dauDS)->tiep;
    } else {
        NganSach *truoc = *dauDS;
        for (int i = 1; i < stt - 1; i++) truoc = truoc->tiep;
        xoa         = truoc->tiep;
        truoc->tiep = xoa->tiep;
    }

    printf("Da xoa ngan sach [%d] '%s' thang %02d/%d.\n",
           stt, xoa->danhMuc, xoa->thang, xoa->nam);
    free(xoa);
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

/* In danh sach ngan sach kem so thu tu [N] o dau moi dong.
   STT chi la bien dem trong vong lap, khong duoc luu vao struct. */
void InDanhSachNganSach(const NganSach *dauDS) {
    if (dauDS == NULL) { printf("Chua co ngan sach nao duoc thiet lap.\n"); return; }
    printf("\n%4s  %-15s %-10s %s\n", "STT", "Danh muc", "Thang/Nam", "Han muc");
    printf("------------------------------------------\n");
    const NganSach *p = dauDS;
    int stt = 1;
    while (p != NULL) { InMotNganSach(stt++, p); p = p->tiep; }
    printf("------------------------------------------\n");
    printf("Tong so: %d ngan sach.\n", DemSoNganSach(dauDS));
}

void GiaiPhongNganSach(NganSach **dauDS) {
    NganSach *p = *dauDS;
    while (p != NULL) { NganSach *tiep = p->tiep; free(p); p = tiep; }
    *dauDS = NULL;
}

/* Lay danh sach ten danh muc duy nhat tu toan bo DS ngan sach.
   Moi ten chi xuat hien mot lan trong ket qua, thu tu theo thu tu trong DS.
   Tra ve so luong danh muc tim duoc (toi da soToiDa phan tu). */
int LayDanhMucDuy(const NganSach *dauDS, char ketQua[][DO_DAI_DANHMUC], int soToiDa) {
    int dem = 0;
    const NganSach *p = dauDS;
    while (p != NULL && dem < soToiDa) {
        int daCoSan = 0;
        for (int i = 0; i < dem; i++) {
            if (strcmp(ketQua[i], p->danhMuc) == 0) { daCoSan = 1; break; }
        }
        if (!daCoSan) {
            strncpy(ketQua[dem], p->danhMuc, DO_DAI_DANHMUC - 1);
            ketQua[dem][DO_DAI_DANHMUC - 1] = '\0';
            dem++;
        }
        p = p->tiep;
    }
    return dem;
}

/* File I/O -- Format: danhMuc|thang|nam|hanMuc */

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
