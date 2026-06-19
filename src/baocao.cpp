#include <stdio.h>
#include <string.h>
#include "baocao.h"

#define SO_DANHMUC_TOIDA 100

/* Nhiem vu : Thong ke ty le % chi tieu giua cac danh muc trong 1 thang,
              hien thi dang bieu do thanh ASCII.
   Dau vao  : dauDS (chi doc), thang, nam
   Dau ra   : in truc tiep ra man hinh */
void ThongKeTyLeDanhMuc(const GiaoDich *dauDS, int thang, int nam) {
    double tongChi = TinhTongTheoLoai(dauDS, "Chi", 0, thang, nam);
    if (tongChi <= 0) {
        printf("Khong co khoan chi nao trong thang %d/%d.\n", thang, nam);
        return;
    }
    printf("\n--- TY LE CHI TIEU THANG %d/%d (tong chi: %.2f) ---\n",
           thang, nam, tongChi);

    char danhMucDaIn[SO_DANHMUC_TOIDA][DO_DAI_DANHMUC];
    int soDaMIn = 0;

    const GiaoDich *p = dauDS;
    while (p != NULL) {
        if (strcmp(p->loai, "Chi") == 0 &&
            p->thang == thang && p->nam == nam) {
            int daIn = 0;
            for (int i = 0; i < soDaMIn; i++) {
                if (strcmp(danhMucDaIn[i], p->danhMuc) == 0) { daIn = 1; break; }
            }
            if (!daIn && soDaMIn < SO_DANHMUC_TOIDA) {
                double tongDM   = TinhTongTheoDanhMuc(dauDS, p->danhMuc, thang, nam);
                double tyLe     = tongDM / tongChi * 100.0;
                int    soVach   = (int)(tyLe / 2.0); /* moi 2% = 1 ky tu '#' */

                printf("%-15s %6.2f%% ", p->danhMuc, tyLe);
                for (int v = 0; v < soVach; v++) printf("#");
                printf("\n");

                strcpy(danhMucDaIn[soDaMIn++], p->danhMuc);
            }
        }
        p = p->tiep;
    }
}

/* Nhiem vu : Doi chieu ngan sach voi thuc chi, canh bao neu vuot han muc.
   Dau vao  : dsGD, dsNS (ca hai chi doc), thang, nam
   Dau ra   : in canh bao ra man hinh */
void KiemTraVuotNganSach(const GiaoDich *dsGD, const NganSach *dsNS,
                         int thang, int nam) {
    printf("\n--- CANH BAO NGAN SACH THANG %d/%d ---\n", thang, nam);
    int coVuot = 0;

    const NganSach *p = dsNS;
    while (p != NULL) {
        if (p->thang == thang && p->nam == nam) {
            double daChi = TinhTongTheoDanhMuc(dsGD, p->danhMuc, thang, nam);
            if (daChi > p->hanMuc) {
                printf("VUOT: '%s' da chi %.2f / han muc %.2f (vuot %.2f)\n",
                       p->danhMuc, daChi, p->hanMuc, daChi - p->hanMuc);
                coVuot = 1;
            }
        }
        p = p->tiep;
    }
    if (!coVuot) printf("Khong co danh muc nao vuot ngan sach.\n");
}

/* Nhiem vu : Ham "sep" -- tong hop bao cao thang: thu/chi/so du,
              bieu do ASCII, canh bao vuot ngan sach.
   Dau vao  : dsGD, dsNS (ca hai chi doc), thang, nam
   Dau ra   : khong co */
void BaoCaoTongHop(const GiaoDich *dsGD, const NganSach *dsNS,
                   int thang, int nam) {
    double tongThu = TinhTongTheoLoai(dsGD, "Thu", 0, thang, nam);
    double tongChi = TinhTongTheoLoai(dsGD, "Chi", 0, thang, nam);
    double soDu    = TinhSoDu(dsGD, thang, nam);

    printf("\n========== BAO CAO TONG HOP THANG %d/%d ==========\n", thang, nam);
    printf("Tong thu : %.2f\n", tongThu);
    printf("Tong chi : %.2f\n", tongChi);
    printf("So du    : %.2f\n", soDu);

    ThongKeTyLeDanhMuc(dsGD, thang, nam);
    KiemTraVuotNganSach(dsGD, dsNS, thang, nam);
    printf("===================================================\n");
}