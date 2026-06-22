#include <stdio.h>
#include <string.h>
#include "tienich.h"

/* Doc va bo qua cac ky tu con sot lai trong bo dem ban phim cho den khi gap
   ky tu xuong dong hoac het file. Can dung sau moi lan scanf() doc so, de tranh
   con '\n' lam hong lan nhap chuoi/so ke tiep -- loi rat hay gap khi tron
   scanf va fgets. */
void LamSachBoDem(void) {
    int ky_tu;
    while ((ky_tu = getchar()) != '\n' && ky_tu != EOF) {
        /* khong lam gi, chi doc cho het */
    }
}

/* Nhap mot so nguyen tu ban phim, lap lai cho den khi nguoi dung nhap dung
   dinh dang va gia tri nam trong [gtMin, gtMax]. */
int NhapSoNguyen(const char *thongBao, int gtMin, int gtMax) {
    int giaTri;
    int soPhanTuDoc;
    while (1) {
        printf("%s", thongBao);
        soPhanTuDoc = scanf("%d", &giaTri);
        LamSachBoDem();
        if (soPhanTuDoc != 1) {
            printf("Loi: vui long nhap mot so nguyen.\n");
            continue;
        }
        if (giaTri < gtMin || giaTri > gtMax) {
            printf("Loi: gia tri phai trong khoang [%d, %d].\n", gtMin, gtMax);
            continue;
        }
        return giaTri;
    }
}

/* Nhap mot so thuc tu ban phim, lap lai cho den khi hop le. */
double NhapSoThuc(const char *thongBao, double gtMin, double gtMax) {
    double giaTri;
    int soPhanTuDoc;
    while (1) {
        printf("%s", thongBao);
        soPhanTuDoc = scanf("%lf", &giaTri);
        LamSachBoDem();
        if (soPhanTuDoc != 1) {
            printf("Loi: vui long nhap mot con so.\n");
            continue;
        }
        if (giaTri < gtMin || giaTri > gtMax) {
            printf("Loi: gia tri phai trong khoang [%.2f, %.2f].\n", gtMin, gtMax);
            continue;
        }
        return giaTri;
    }
}

/* Nhap mot chuoi ky tu tu ban phim, gioi han do dai, tu dong bo ky tu xuong
   dong cuoi chuoi. */
void NhapChuoi(const char *thongBao, char *ketQua, int doDaiToiDa) {
    printf("%s", thongBao);
    fgets(ketQua, doDaiToiDa, stdin);
    int doDai = (int) strlen(ketQua);
    if (doDai > 0 && ketQua[doDai - 1] == '\n') {
        ketQua[doDai - 1] = '\0';
    } else {
        LamSachBoDem();
    }
}

/* Kiem tra ngay/thang/nam co ton tai thuc su tren lich khong, co tinh ca nam
   nhuan. Day la vi du dien hinh cho ky thuat "kiem tra dieu kien bien". */
int KiemTraNgayHopLe(int ngay, int thang, int nam) {
    int soNgayTrongThang[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int namNhuan;
    int soNgayToiDa;

    if (nam < 2000 || nam > 2100) return 0;
    if (thang < 1 || thang > 12) return 0;

    namNhuan = (nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0);
    soNgayToiDa = soNgayTrongThang[thang - 1];
    if (thang == 2 && namNhuan) {
        soNgayToiDa = 29;
    }

    if (ngay < 1 || ngay > soNgayToiDa) return 0;
    return 1;
}

/* Nhap ngay/thang/nam tu ban phim, lap lai cho den khi ngay hop le. */
void NhapNgay(const char *thongBao, int *ngay, int *thang, int *nam) {
    int soPhanTuDoc;
    while (1) {
        printf("%s (dd mm yyyy): ", thongBao);
        soPhanTuDoc = scanf("%d %d %d", ngay, thang, nam);
        LamSachBoDem();
        if (soPhanTuDoc != 3) {
            printf("Loi: vui long nhap dung 3 so nguyen (ngay thang nam).\n");
            continue;
        }
        if (!KiemTraNgayHopLe(*ngay, *thang, *nam)) {
            printf("Loi: ngay/thang/nam khong hop le.\n");
            continue;
        }
        return;
    }
}
